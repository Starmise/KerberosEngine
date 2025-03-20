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
   * @brief Initializes and sets up the shader program.
   */
  HRESULT
  init(Device& device,
      const std::string& fileName,
      std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /**
   * @brief Updates the shader program.
   */
  void
  update();

  /**
   * @brief Sets the input layout, vertex shader, and pixel shader in the device context.
   */
  void
  render(DeviceContext& DeviceContext);

  /**
   * @brief Destroys the shader program and releases resources.
   */
  void
  destroy();

  /**
   * @brief Creates the input layout using the provided device and input layout description.
   * @param device Reference to the device.
   * @param Layout Vector containing the input layout description.
   */
  HRESULT
  CreateInputLayout(Device& device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /**
   * @brief Creates a shader (vertex or pixel) based on the specified type.
   * @param device Reference to the device.
   * @param type Type of shader to create (vertex or pixel).
   */
  HRESULT
  CreateShader(Device& device, ShaderType type);

  /**
   * @brief Reads and compiles a shader file using the specified entry point and shader.
   * @param szFileName Name of the shader file.
   * @param szEntryPoint Entry point function in the shader.
   * @param szShaderModel Shader model to be used.
   * @param ppBlobOut Output pointer to the shader data.
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