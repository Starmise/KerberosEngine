#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;

class 
InputLayout {
public:
  /**
   * @brief Default constructor and destructor.
   */
  InputLayout() = default;
  ~InputLayout() = default;

  /**
   * @brief Sets the input layout using the device, input layout description
   * and vertex shader data.
   * @param device Reference to the device used to create the input layout.
   * @param Layout Vector of D3D11_INPUT_ELEMENT_DESC structure for the input layout.
   * @param VertexShaderData Pointer to the vertex shader.
   */
  HRESULT
  init(Device& device,
      std::vector<D3D11_INPUT_ELEMENT_DESC>& Layout,
      ID3DBlob* VertexShaderData);

  /**
   * @brief Updates the input layout state for any runtime modifications
   */
  void
  update();

  /**
   * @brief Binds the input layout to the rendering pipeline.
   */
  void
  render(DeviceContext& deviceContext);

  /**
   * @brief Releases the resources of the input layout.
   */
  void
  destroy();

public:
  ID3D11InputLayout* m_inputLayout = nullptr;
};