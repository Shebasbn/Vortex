#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Vortex
{
	Window* Window::Create(const WindowProps& props)
	{
#ifdef VTX_WINDOWS_PLATFORM
		return new WindowsWindow(props);
#else
#endif
	}
}