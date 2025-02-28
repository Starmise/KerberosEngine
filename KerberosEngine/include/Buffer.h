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
   */
  HRESULT
  init(Device& device, MeshComponent& mesh, unsigned int bindFlag);

  /**
   * @brief Initializes constant buffers
   */
  HRESULT
  init(Device& device, unsigned int ByteWidth);

  /**
   * @brief Updates the logic of the constant buffers each frame
   */
  void
  update(DeviceContext& deviceContext,
         unsigned int DstSubresource,
         const D3D11_BOX* pDstBox,
         const void* pSrcData,
         unsigned int SrcRowPitch,
         unsigned int SrcDepthPitch);

  /**
   * @brief Updates the render of Vertex, Index and Constant Buffer
   */
  void
  render(DeviceContext& deviceContext, 
         unsigned int StarSlot, 
         unsigned int NumBuffers,
         bool setPixelShader = false,
         DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN
         );

  /**
   * @brief
   */
  void
  destroy();

private:
  /**
   * @brief
   */
  HRESULT
  createBuffer(Device& device,
                 D3D11_BUFFER_DESC& desc,
                 D3D11_SUBRESOURCE_DATA* initData);

  ID3D11Buffer* m_buffer = nullptr;
  unsigned int m_bindFlags = 0;
  unsigned int m_stride = 0;
  unsigned int m_offset = 0;
};