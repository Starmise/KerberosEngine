#include "ECS/Actor.h"
#include "MeshComponent.h"
#include "Device.h"

Actor::Actor(Device& device) {
  EngineUtilities::TSharedPointer mesh = EngineUtilities::MakeShared<MeshComponent>();
  addComponent(mesh);

  HRESULT hr;
  string classNameType = "Actor -> " + m_name;

  hr = m_modelBuffer.init(device, sizeof(CBChangesEveryFrame));
  if (FAILED(hr)) {
    ERROR("Actor", classNameType.c_str(), "Failed to create new CBChanges EveryFrame");
  }

  hr = m_sampler.init(device);
  if (FAILED(hr)) {
    ERROR("Actor", classNameType.c_str(), "Failed to SamplerState");
  }
}

void
Actor::update(float deltaTime, DeviceContext& deviceContext) {

  // Update Atributes
  m_modelBuffer.update(deviceContext, 0, nullptr, &m_changeEveryFrame, 0, 0);
}

void
Actor::render(DeviceContext& deviceContext) {

  // Update Buffers for each mesh on the actor
  for (unsigned int i = 0; i < m_meshes.size(); i++) {
    m_vertexBuffers[i].render(deviceContext, 0, 1);
    m_indexBuffers[i].render(deviceContext, 0, 1, false, DXGI_FORMAT_R32_UINT);

    if (m_textures.size() > 0) {
      if (i <= m_textures.size() - 1) {
        m_textures[i].render(deviceContext, 0, 1);
      }
    }

    m_modelBuffer.render(deviceContext, 2, 1);

    deviceContext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext.DrawIndexed(m_meshes[i].m_numIndex, 0, 0);
  }
}

void
Actor::destroy() {
  for (auto& vertexBuffer : m_vertexBuffers) {
    vertexBuffer.destroy();
  }

  for (auto& indexBuffer : m_indexBuffers) {
    indexBuffer.destroy();
  }

  for (auto& tex : m_textures) {
    tex.destroy();
  }

  m_modelBuffer.destroy();
  //n_rasterizer.destroy();
  //n_blendstate.destroy();
  m_sampler.destroy();
}

void
Actor::setMesh(Device& device, std::vector<MeshComponent> meshes) {
  m_meshes = meshes;
  HRESULT hr;

  for (auto& mesh : m_meshes) {
    // Crear vertex buffer
    Buffer vertexBuffer;
    hr = vertexBuffer.init(device, mesh, D3D11_BIND_VERTEX_BUFFER);
    if (FAILED(hr)) {
      ERROR("Actor", "setMessh", "Failed to create new vertexBuffer");
    }
    else {
      m_vertexBuffers.push_back(vertexBuffer);
    }

    // Crear index buffer
    Buffer indexBuffer;
    hr = indexBuffer.init(device, mesh, D3D11_BIND_INDEX_BUFFER);
    if (FAILED(hr)) {
      ERROR("Actor", "setMesh", "Failed to create new indexBuffer");
    }
    else {
      m_indexBuffers.push_back(indexBuffer);
    }
  }
}