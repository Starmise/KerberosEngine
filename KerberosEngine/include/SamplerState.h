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
   * @brief Initializes the sampler state, which defines how textures are sampled in rendering.
   * @param device Reference to the device
   */
  HRESULT
  init(Device& device);

  /**
   * @brief Updates the sampler state.
   */
  void
  update();

  /**
   * @brief Sets the sampler state in the device context, for texture sampling.
 *
 * @param deviceContext Reference to the device context.
 * @param StartSlot The first slot to bind the sampler to.
 * @param numSamplers Number of sampler states to set.
   */
  void
  render(DeviceContext& deviceContext, 
           unsigned int StartSlot, 
           unsigned int numSamplers);

  /**
   * @brief Releases the sampler state resources.
   */
  void
  destroy();

private:
  ID3D11SamplerState* m_samplerState = nullptr;
};