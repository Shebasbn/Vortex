#include "Application.h"


namespace Vortex
{
	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		VTX_CORE_ASSERT(!s_Instance, "Application allready exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		if (m_Window) m_Running = true;
		m_Window->SetEventCallback(VTX_BIND_EVENT_FN(Application::OnEvent));
	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		VTX_CORE_TRACE("{}", e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(VTX_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(VTX_BIND_EVENT_FN(Application::OnWindowResize));

	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate(0.0f);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		m_Window->ResizeWindow(e.GetWidth(), e.GetHeight());
		return true;
	}
}