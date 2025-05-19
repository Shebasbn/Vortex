#pragma once
#include "Window.h"
#include "Vortex/Event/Event.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/ApplicationEvent.h"

namespace Vortex
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool Application::OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		static Application* s_Instance;
		bool m_Running = false;
	};

	Application* CreateApplication();
}