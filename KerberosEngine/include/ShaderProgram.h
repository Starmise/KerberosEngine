#pragma once
#include "Prerequisites.h"
#include "InputLayout.h"

class Device;
class DeviceContext;

class 
ShaderProgram {
public:
  /**
   * @brief Default constructor and destructor.
   */
  ShaderProgram() = default;
  ~ShaderProgram() = default;

  /**
   * @brief
   */
  HRESULT
  init(Device& device,
      const std::string& fileName,
      std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /**
   * @brief
   */
  void
  update();

  /**
   * @brief
   */
  void
  render(DeviceContext& DeviceContext);

  /**
   * @brief
   */
  void
  destroy();

  /**
   * @brief
   */
  HRESULT
  CreateInputLayout(Device& device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /**
   * @brief
   */
  HRESULT
  CreateShader(Device& device, ShaderType type);

  /**
   * @brief
   */
  HRESULT
  CompileShaderFromFile(char* szFileName,
                        LPCSTR szEntryPoint,
                        LPCSTR szShaderModel,
                        ID3DBlob** ppBlobOut);

  ID3D11VertexShader* m_VertexShader = nullptr;
  ID3D11PixelShader* m_PixelShader = nullptr;
  InputLayout m_inputLayout;

private:
  std::string m_shaderFileName;
  ID3DBlob* m_vertexShaderData = nullptr;
  ID3DBlob* m_pixelShaderData = nullptr;
};