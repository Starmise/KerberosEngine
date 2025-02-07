#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;

class
DepthStencilView {
public:
  DepthStencilView() = default;
  ~DepthStencilView() = default;

  void
  init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

  void
  update();

  void
  render(DeviceContext& deviceContext);

  void
  destroy();

private:
  ID3D11DepthStencilView* m_depthStencilView = nullptr;
};
