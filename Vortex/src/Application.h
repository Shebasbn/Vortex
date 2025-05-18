#pragma once

namespace Vortex
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();
		
	};

	Application* CreateApplication();
}