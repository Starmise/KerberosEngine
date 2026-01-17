#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;

class BlendState {
public:
  /**
   * @brief Default constructor and destructor.
   */
  BlendState() = default;
  ~BlendState() = default;

  /**
   * @brief Initializes the blend state for alpha blending.
   * @param device Reference to the device.
   */
  HRESULT init(Device& device);

  /**
   * @brief Sets the blend state for rendering.
   * @param deviceContext Reference to the device context.
   * @param blendFactor Blend factors.
   * @param sampleMask Sample mask.
   * @param reset If true, resets the blend state.
   */
  void render(DeviceContext& deviceContext,
              float* blendFactor = nullptr,
              unsigned int sampleMask = 0xffffffff,
              bool reset = false);

  /**
   * @brief Releases the blend state resources.
   */
  void destroy();

private:
  ID3D11BlendState* m_blendState = nullptr;
};