#pragma once
#ifdef VTX_WINDOWS_PLATFORM
extern Vortex::Application* Vortex::CreateApplication();

int main(int argc, char** argv)
{
	Vortex::Log::Init();
	auto App = Vortex::CreateApplication();
	App->Run();
	delete App;
}
#endif
