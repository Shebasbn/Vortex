#include "WindowsWindow.h"
#include <Windows.h>
#include <windowsx.h>

namespace Vortex
{
	static bool s_WindowClassInitialized = false;

	static LRESULT CALLBACK WndProcW(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		switch (message)
		{
			case WM_DESTROY: PostQuitMessage(0); break;
			case WM_SIZE: 
			{
				if (window)
				{
					uint32_t width = LOWORD(lParam);
					uint32_t height = HIWORD(lParam);
					window->HandleEvent(WindowResizeEvent(width, height));
				}
				return 0;
			}
			case WM_CLOSE:
			{
				if (window)
				{
					WindowCloseEvent event;
					window->HandleEvent(event);
				}
				return 0;
			}
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			{
				if (window)
				{
					KeyPressedEvent event(static_cast<uint32_t>(wParam), (lParam & 0x40000000) ? 1 : 0);
					window->HandleEvent(event);
				}
				return 0;
			}
			case WM_KEYUP:
			case WM_SYSKEYUP:
			{
				if (window)
				{
					KeyReleasedEvent event(static_cast<uint32_t>(wParam));
					window->HandleEvent(event);
				}
				return 0;
			}
			case WM_MOUSEMOVE:
			{
				if (window)
				{
					float x = static_cast<float>(GET_X_LPARAM(lParam));
					float y = static_cast<float>(GET_Y_LPARAM(lParam));

					MouseMovedEvent event(x, y);
					window->HandleEvent(event);
				}
				return 0;
			}
			case WM_MOUSEWHEEL:
			{
				if (window)
				{
					float delta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam)) / WHEEL_DELTA;
					MouseScrolledEvent event(0.0f, delta);
					window->HandleEvent(event);
				}
				return 0;
			}
			case WM_LBUTTONDOWN:
			{
				if (window)
				{
					MouseButtonPressedEvent event(0);
					window->HandleEvent(event);
				}
				return 0;
			}
			case WM_LBUTTONUP:
			{
				if (window)
				{
					MouseButtonReleasedEvent event(0);
					window->HandleEvent(event);
				}
				return 0;
			}
			case WM_RBUTTONDOWN:
			{
				if (window)
				{
					MouseButtonPressedEvent event(1);
					window->HandleEvent(event);
				}
				return 0;
			}
			case WM_RBUTTONUP:
			{
				if (window)
				{
					MouseButtonReleasedEvent event(1);
					window->HandleEvent(event);
				}
				return 0;
			}
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}
	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;
		m_Data.VSync = props.VSync;

		if (!s_WindowClassInitialized)
		{
			WNDCLASSW wc{};
			wc.lpfnWndProc = WndProcW;
			wc.hInstance = GetModuleHandleW(nullptr);
			wc.lpszClassName = L"VortexWindowClass";

			RegisterClassW(&wc);
			s_WindowClassInitialized = true;
		}

		HINSTANCE hInstance = GetModuleHandle(nullptr);
		m_Instance = hInstance;

		RECT rect = { 0, 0, static_cast<LONG>(props.Width), static_cast<LONG>(props.Height) };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		m_Window = CreateWindowExW(
			0,
			L"VortexWindowClass",
			std::wstring(props.Title.begin(), props.Title.end()).c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);

		if (!m_Window) 
		{
			VTX_CORE_ERROR("Failed to create window."); 
			return;
		}

		SetWindowLongPtr(m_Window, GWLP_USERDATA, (LONG_PTR)this);

		AllowSetForegroundWindow(ASFW_ANY);
		ShowWindow(m_Window, SW_SHOW);
		UpdateWindow(m_Window);
		SetForegroundWindow(m_Window);
		SetFocus(m_Window);

		m_DX11Context = std::make_unique<DX11Context>(m_Window);
		m_DX11Context->Init();
		m_DX11Context->SetVSync(m_Data.VSync);

		//m_Running = true;
	}

	void WindowsWindow::OnUpdate(float dt)
	{
		MSG msg;
		while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		m_DX11Context->SwapBuffers();
	}

	void WindowsWindow::Shutdown()
	{
		DestroyWindow(m_Window);
		m_Window = nullptr;
		m_DX11Context.reset();
	}
}