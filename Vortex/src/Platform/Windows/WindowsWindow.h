#pragma once
#include "Vortex/Window.h"
#include "Vortex/Event/Event.h"
#include "Vortex/Event/ApplicationEvent.h"
#include "Vortex/Event/KeyEvent.h"
#include "Vortex/Event/MouseEvent.h"
#include <d3d11.h>
#include "DX11Context.h"

namespace Vortex
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();

		virtual void OnUpdate(float dt) override;
		virtual uint32_t GetWidth() const override { return m_Data.Width; }
		virtual uint32_t GetHeight() const override { return m_Data.Height; }
		virtual void ResizeWindow(uint32_t width, uint32_t height) override 
		{ 
			m_Data.Width = width; 
			m_Data.Height = height;
			m_DX11Context->ResizeBuffers(width, height);
		}
		void HandleEvent(Event& event) { if (m_Data.callback) m_Data.callback(event); }

		// Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.callback = callback; }
		virtual void SetVSync(bool enabled) override 
		{ 
			m_Data.VSync = enabled; 
			m_DX11Context->SetVSync(enabled);
		}
		virtual bool IsVSync() const override { return m_Data.VSync; }

		virtual void* GetNativeWindow() override { return m_Window; }

	private:
		void Init(const WindowProps& props);
		void Shutdown();

		HWND m_Window;
		HINSTANCE m_Instance;

		std::unique_ptr<DX11Context> m_DX11Context;

	private:
		struct WindowData
		{
			EventCallbackFn callback;
			std::string Title;
			uint32_t Width, Height;
			bool VSync;
		};

		WindowData m_Data;
		//bool m_Running = false;
	};
}