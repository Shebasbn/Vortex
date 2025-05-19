#include "DX11Context.h"
#include <dxgi.h>
#include <dxgi1_2.h>

namespace Vortex
{
	DX11Context::DX11Context(HWND__* windowHandle)
		: m_WindowHandle(windowHandle)
	{
	}
	DX11Context::~DX11Context()
	{
		CleanupRenderTarget();
	}

	void DX11Context::Init()
	{
		CreateDeviceAndSwapChain();
		CreateRenderTarget();
	}
	void DX11Context::SwapBuffers()
	{
		// Present the frame with VSync (1) or as fast as possible (0)
		HRESULT hr = m_SwapChain->Present(m_VSync ? 1 : 0, 0);
		if (FAILED(hr))
		{
			VTX_CORE_ERROR("SwapChain::Present failed. HRESULT: {}", hr);
		}
	}
	void DX11Context::ResizeBuffers(uint32_t width, uint32_t height)
	{
		if (!m_SwapChain)
			return;

		// Release existing render target
		CleanupRenderTarget();

		// Resize the swap chain buffers
		HRESULT hr = m_SwapChain->ResizeBuffers(
			0,            // Buffer count (0 = preserve)
			width,
			height,
			DXGI_FORMAT_UNKNOWN, // Keep existing format
			0                   // Flags
		);

		if (FAILED(hr))
		{
			VTX_CORE_ERROR("Failed to resize swap chain buffers. HRESULT: {}", hr);
			throw std::runtime_error("ResizeBuffers failed.");
		}

		// Recreate the render target with new backbuffer size
		CreateRenderTarget();
	}
	void DX11Context::CreateDeviceAndSwapChain()
	{
		DXGI_SWAP_CHAIN_DESC scDesc = {};
		scDesc.BufferCount = 2;
		scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scDesc.OutputWindow = m_WindowHandle;
		scDesc.SampleDesc.Count = 1;
		scDesc.Windowed = TRUE;
		scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT createDeviceFlags = 0;
#ifdef DEBUG_BUILD
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0
		};

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			createDeviceFlags,
			featureLevels,
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,
			&scDesc,
			m_SwapChain.GetAddressOf(),
			m_Device.GetAddressOf(),
			&featureLevel,
			m_DeviceContext.GetAddressOf()
		);

		if (FAILED(hr))
		{
			VTX_CORE_FATAL("Failed to create D3D11 device and swap chain! HRESULT: {}", hr);
			throw std::runtime_error("D3D11CreateDeviceAndSwapChain failed.");
		}
	}
	void DX11Context::CreateRenderTarget()
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		HRESULT hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

		if (FAILED(hr))
		{
			VTX_CORE_FATAL("Failed to get swap chain back buffer. HRESULT: {}", hr);
			throw std::runtime_error("GetBuffer failed.");
		}

		hr = m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_RenderTargetView.GetAddressOf());
		if (FAILED(hr))
		{
			VTX_CORE_FATAL("Failed to create render target view. HRESULT: {}", hr);
			throw std::runtime_error("CreateRenderTargetView failed.");
		}

		m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
	}
	void DX11Context::CleanupRenderTarget()
	{
		if (m_DeviceContext && m_RenderTargetView)
			m_DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

		m_RenderTargetView.Reset();
	}
}