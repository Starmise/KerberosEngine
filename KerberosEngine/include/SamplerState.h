#pragma once
#include "Prerequisites.h"

// Forward declaraitons
class Device;
class DeviceContext;

class
SamplerState {
public:
  /**
   * @brief Default constructor and destructor.
   */
  SamplerState() = default;
  ~SamplerState() = default;

  /**
   * @brief
   */
  HRESULT
  init(Device& device);

  /**
   * @brief
   */
  void
  update();

  /**
   * @brief
   */
  void
  render(DeviceContext& deviceContext, 
           unsigned int StartSlot, 
           unsigned int numSamplers);

  /**
   * @brief
   */
  void
  destroy();

private:
  ID3D11SamplerState* m_samplerState = nullptr;
};