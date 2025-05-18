#include <iostream>

#include "Application.h"
	
class SandboxApp : public Vortex::Application
{
public:
	SandboxApp()
	{

	}
	~SandboxApp()
	{

	}
};

Vortex::Application* Vortex::CreateApplication()
{
	return new SandboxApp();
}