#include "Application.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace Vortex
{
	Application::Application()
	{
		spdlog::info("Welcom to spdlog!");
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