#pragma once

#include <d3d11.h>
#include <wrl/client.h>

struct HWND__;

namespace Vortex
{
	class DX11Context
	{
	public:
		DX11Context(HWND__* windowHandle);
		~DX11Context();

		void Init();
		void SwapBuffers();
		void SetVSync(bool enabled) { m_VSync = enabled; }
		bool IsVSync() const { return m_VSync; }
		void ResizeBuffers(uint32_t width, uint32_t height);

	private:
		HWND__* m_WindowHandle = nullptr;
		bool m_VSync = true;

		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
		
		void CreateDeviceAndSwapChain();
		void CreateRenderTarget();
		void CleanupRenderTarget();
	};
}