#include "DeviceContext.h"

void 
DeviceContext::OMSetRenderTargets(unsigned int NumViews, 
                                  ID3D11RenderTargetView* const* ppRenderTargetViews, 
                                  ID3D11DepthStencilView* pDepthStencilView) {
  // Validar los parámetros
  if (!ppRenderTargetViews && !pDepthStencilView) {
    ERROR("DeviceContext", "OMSetRenderTargets",
      "Both ppRenderTargetViews and pDepthStencilView are nullptr");
    return;
  }

  if (NumViews > 0 && !ppRenderTargetViews) {
    ERROR("DeviceContext", "OMSetRenderTargets",
      "ppRenderTargetViews is nullptr, but NumViews > 0");
    return;
  }

  // Asignar los render targets y el depth stencil
  m_deviceContext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}

void 
DeviceContext::RSSetViewports(unsigned int NumViewports, 
                              const D3D11_VIEWPORT* pViewports) {
  if (!pViewports) {
    ERROR("DeviceContext", "RSSetViewports", "pViewports is nullptr");
    return;
  }

  m_deviceContext->RSSetViewports(NumViewports, pViewports);
}

void 
DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout) {
  if (!pInputLayout) {
    ERROR("DeviceContext", "IASetInputLayout", "pInputLayout is nullptr");
    return;
  }

  m_deviceContext->IASetInputLayout(pInputLayout);
}

void 
DeviceContext::IASetVertexBuffers(unsigned int StartSlot, 
                                  unsigned int NumBuffers, 
                                  ID3D11Buffer* const* ppVertexBuffers, 
                                  const unsigned int* pStrides, 
                                  const unsigned int* pOffsets) {
  if (!ppVertexBuffers || !pStrides || !pOffsets) {
    ERROR("DeviceContext", "IASetVertexBuffers",
      "Invalid arguments: ppVertexBuffers, pStrides, or pOffsets is nullptr");
    return;
  }

  m_deviceContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void 
DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer, 
                                DXGI_FORMAT Format, 
                                unsigned int Offset) {
  if (!pIndexBuffer) {
    ERROR("DeviceContext", "IASetIndexBuffer", "pIndexBuffer is nullptr");
    return;
  }

  m_deviceContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

void 
DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology){
  // Validar el parámetro Topology
  if (Topology == D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED) {
    ERROR("DeviceContext", "IASetPrimitiveTopology",
      "Topology is D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED");
    return;
  }

  // Asignar la topología al Input Assembler
  m_deviceContext->IASetPrimitiveTopology(Topology);
}

void 
DeviceContext::UpdateSubresource(ID3D11Resource* pDstResource, 
                                unsigned int DstSubresource, 
                                const D3D11_BOX* pDstBox, 
                                const void* pSrcData,
                                unsigned int SrcRowPitch, 
                                unsigned int SrcDepthPitch) {
}

void 
DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, 
                                    const FLOAT ColorRGBA[4]) {
}

void 
DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView, 
                                    FLOAT Depth, 
                                    UINT8 Stencil) {
}

void 
DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader, 
                          ID3D11ClassInstance* 
                          const* ppClassInstances, 
                          unsigned int NumClassInstances) {
}

void 
DeviceContext::VSSetConstantBuffers(unsigned int StartSlot, 
                                    unsigned int NumBuffers, 
                                    ID3D11Buffer* const* ppConstantBuffers) {
}

void 
DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader, 
                          ID3D11ClassInstance* const* ppClassInstances, 
                          unsigned int NumClassInstances) {
}

void 
DeviceContext::PSSetConstantBuffers(unsigned int StartSlot, 
                                    unsigned int NumBuffers, 
                                    ID3D11Buffer* const* ppConstantBuffers) {
}

void 
DeviceContext::PSSetShaderResources(unsigned int StartSlot, 
                                    unsigned int NumViews, 
                                    ID3D11ShaderResourceView* const* ppShaderResourceViews) {
}

void 
DeviceContext::PSSetSamplers(unsigned int StartSlot, 
                            unsigned int NumSamplers, 
                            ID3D11SamplerState* const* ppSamplers) {
}

void 
DeviceContext::DrawIndexed(unsigned int IndexCount, 
                          unsigned int StartIndexLocation, 
                          INT BaseVertexLocation) {
}