#include "Vortex/Application.h"


extern Vortex::Application* Vortex::CreateApplication();

int main()
{
	Vortex::Application* App = Vortex::CreateApplication();
	std::cout << "Hello Core\n";
	App->Run();
	return 0;
}