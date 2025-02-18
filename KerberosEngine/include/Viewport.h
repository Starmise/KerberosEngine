#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Window;
class DeviceContext;

class
Viewport {
public:
  /**
   * @brief Default constructor and destructor.
   */
  Viewport() = default;
  ~Viewport() = default;

  /**
   * @brief
   */
  HRESULT
  init(const Window& window);

  /**
   * @brief
   */
  HRESULT
  init(unsigned int width, unsigned int height);

  /**
   * @brief
   */
  void
  update();

  /**
   * @brief
   */
  void
  render(DeviceContext& deviceContext);

  /**
   * @brief
   */
  void
  destroy();

private:
  D3D11_VIEWPORT m_viewport;
};