#include "Application.h"

extern Vortex::Application* Vortex::CreateApplication();

int main()
{
	Vortex::Log::Init();
	auto App = Vortex::CreateApplication();
	std::cout << "Hello Core\n";
	App->Run();
	delete App;
	return 0;
}