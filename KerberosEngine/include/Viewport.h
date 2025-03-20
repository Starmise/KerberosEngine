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
   * @brief Initializes the viewport using a Window instance.
   * @param window Reference to the Window object.
   */
  HRESULT
  init(const Window& window);

  /**
   * @brief Initializes the viewport with the specified dimensions.
   * @param width The width of the viewport.
   * @param height The height of the viewport.
   */
  HRESULT
  init(unsigned int width, unsigned int height);

  /**
   * @brief Updates the viewport settings when any changes to the dimensions are required.
   */
  void
  update();

  /**
   * @brief Renders the viewport using the given DeviceContext method.
   * @param deviceContext Reference to the DeviceContext used for rendering.
   */
  void
  render(DeviceContext& deviceContext);

  /**
   * @brief Releases the resources from the viewport.
   */
  void
  destroy();

private:
  D3D11_VIEWPORT m_viewport;
};