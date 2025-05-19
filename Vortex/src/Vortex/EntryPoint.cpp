#include "Application.h"
#include "Log.h"
#include "Event/Event.h"
#include "Event/KeyEvent.h"
//#include "Event/EventFormatter.h"

extern Vortex::Application* Vortex::CreateApplication();

int main()
{
	Vortex::Application* App = Vortex::CreateApplication();
	std::cout << "Hello Core\n";
	Vortex::KeyPressedEvent event(1, 10);
	std::cout << event << std::endl;
	VTX_TRACE("{}", event);
	App->Run();
	return 0;
}