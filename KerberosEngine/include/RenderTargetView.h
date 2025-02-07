#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

class 
RenderTargetView {
public:
  RenderTargetView() = default;
  ~RenderTargetView() = default;

  /*
  */
  void
  init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

  void
  update();

  void
  render(DeviceContext& deviceContext, DepthStencilView& depthStencilView, unsigned int numOfViews, float clearColor[4]);

  void
  destroy();

private:
  ID3D11RenderTargetView* m_renderTargetView = nullptr;
};