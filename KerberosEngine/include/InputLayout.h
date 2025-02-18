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
   * @brief
   */
  HRESULT
  init(Device& device,
      std::vector<D3D11_INPUT_ELEMENT_DESC>& Layout,
      ID3DBlob* VertexShaderData);

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
  ID3D11InputLayout* m_inputLayout = nullptr;
};