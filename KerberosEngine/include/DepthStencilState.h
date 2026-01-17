#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;

class DepthStencilState {
public:
  /**
   * @brief Default constructor and destructor.
   */
  DepthStencilState() = default;
  ~DepthStencilState() = default;

  /**
   * @brief Initializes the depth stencil state.
   * @param device Reference to the device.
   * @param depthEnable Enable depth testing.
   * @param depthWriteMask Depth write mask.
   * @param depthFunc Depth comparison function.
   * @param stencilEnable Enable stencil testing.
   */
  HRESULT init(Device& device,
               bool depthEnable = true,
               D3D11_DEPTH_WRITE_MASK depthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,
               D3D11_COMPARISON_FUNC depthFunc = D3D11_COMPARISON_LESS,
               bool stencilEnable = false);

  /**
   * @brief Sets the depth stencil state for rendering.
   * @param deviceContext Reference to the device context.
   * @param stencilRef Stencil reference value.
   * @param reset If true, resets the depth stencil state.
   */
  void render(DeviceContext& deviceContext,
              unsigned int stencilRef = 0,
              bool reset = false);

  /**
   * @brief Releases the depth stencil state resources.
   */
  void destroy();

private:
  ID3D11DepthStencilState* m_depthStencilState = nullptr;
};