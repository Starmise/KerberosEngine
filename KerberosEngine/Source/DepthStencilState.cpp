#include "DepthStencilState.h"
#include "Device.h"
#include "DeviceContext.h"

HRESULT
DepthStencilState::init(Device& device,
                        bool depthEnable,
                        D3D11_DEPTH_WRITE_MASK depthWriteMask,
                        D3D11_COMPARISON_FUNC depthFunc,
                        bool stencilEnable) {
  if (!device.m_device) {
    ERROR("DepthStencilState", "init", "Device is null.");
    return E_POINTER;
  }

  D3D11_DEPTH_STENCIL_DESC dsDesc = {};
  dsDesc.DepthEnable = depthEnable;
  dsDesc.DepthWriteMask = depthWriteMask;
  dsDesc.DepthFunc = depthFunc;
  dsDesc.StencilEnable = stencilEnable;
  if (stencilEnable) {
    // Default stencil settings if enabled
    dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
    dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
    dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    dsDesc.BackFace = dsDesc.FrontFace;
  }

  HRESULT hr = device.m_device->CreateDepthStencilState(&dsDesc, &m_depthStencilState);
  if (FAILED(hr)) {
    ERROR("DepthStencilState", "init",
      ("Failed to create depth stencil state. HRESULT: " + std::to_string(hr)).c_str());
    return hr;
  }

  return S_OK;
}

void
DepthStencilState::render(DeviceContext& deviceContext,
                          unsigned int stencilRef,
                          bool reset) {
  if (!deviceContext.m_deviceContext) {
    ERROR("DepthStencilState", "render", "DeviceContext is nullptr.");
    return;
  }
  if (!m_depthStencilState && !reset) {
    ERROR("DepthStencilState", "render", "DepthStencilState is not initialized.");
    return;
  }

  if (!reset) {
    deviceContext.m_deviceContext->OMSetDepthStencilState(m_depthStencilState, stencilRef);
  }
  else {
    deviceContext.m_deviceContext->OMSetDepthStencilState(nullptr, stencilRef);
  }
}

void
DepthStencilState::destroy() {
  SAFE_RELEASE(m_depthStencilState);
}