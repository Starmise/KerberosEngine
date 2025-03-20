#pragma once
#include "Prerequisites.h"

// Forward Declations
class Device;
class DeviceContext;
class MeshComponent;

class 
Buffer {
public:
  /**
   * @brief Default constructor and destructor.
   */
  Buffer() = default;
  ~Buffer() = default;

  /**
   * @brief Initializes Vertex and Index Buffers
   * @param device Reference to the device.
   * @param mesh Reference to the mesh component containing vertex and index data.
   * @param bindFlag Flag indicating whether the buffer is a vertex or index buffer.
   */
  HRESULT
  init(Device& device, MeshComponent& mesh, unsigned int bindFlag);

  /**
   * @brief Initializes constant buffers
   * @param device Reference to the device.
   * @param ByteWidth Size of the buffer.
   */
  HRESULT
  init(Device& device, unsigned int ByteWidth);

  /**
   * @brief Updates the logic of the constant buffers each frame.
   * @param deviceContext Reference to the device context.
   * @param DstSubresource Index of the destination subresource.
   * @param pDstBox Pointer to a box defining the updated region.
   * @param pSrcData Pointer to the source data.
   * @param SrcRowPitch Size of a row of data.
   * @param SrcDepthPitch Size of a depth of data.
   */
  void
  update(DeviceContext& deviceContext,
         unsigned int DstSubresource,
         const D3D11_BOX* pDstBox,
         const void* pSrcData,
         unsigned int SrcRowPitch,
         unsigned int SrcDepthPitch);

  /**
   * @brief Updates the render of Vertex, Index and Constant Buffer.
   * @param deviceContext Reference to the device context.
   * @param StartSlot Starting slot for the buffer binding.
   * @param NumBuffers Number of buffers.
   * @param setPixelShader If true, binds the buffer to the pixel shader.
   * @param format Format of the index buffer.
   */
  void
  render(DeviceContext& deviceContext, 
         unsigned int StartSlot, 
         unsigned int NumBuffers,
         bool setPixelShader = false,
         DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN
         );

  /**
   * @brief Releases the buffer resources.
   */
  void
  destroy();

private:
  /**
   * @brief Creates a D3D11 buffer.
   * @param device Reference to the device used for buffer creation.
   * @param desc Structure describing the buffer properties.
   * @param initData Pointer to the initial data for the buffer.
   */
  HRESULT
  createBuffer(Device& device,
                 D3D11_BUFFER_DESC& desc,
                 D3D11_SUBRESOURCE_DATA* initData);

  ID3D11Buffer* m_buffer = nullptr;
  unsigned int m_bindFlag = 0;
  unsigned int m_stride = 0;
  unsigned int m_offset = 0;
};