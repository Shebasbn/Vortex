#include "Application.h"
#include "Log.h"


namespace Vortex
{
	Application::Application()
	{
		Log::Init();
		Vortex::KeyPressedEvent event(1, 10);
		std::cout << event << std::endl;
		VTX_TRACE("{}", event);
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		while (true)
		{
		}
	}
}