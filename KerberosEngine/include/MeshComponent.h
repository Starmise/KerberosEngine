#pragma once
#include "Prerequisites.h"
#include "DeviceContext.h"

class
MeshComponent {
public:
  /**
   * @brief Constructor initializing by default the Vertex and Index number in 0
   */
  MeshComponent() : m_numVertex(0), m_numIndex(0) {};

  /**
   * @brief Virtual destructor.
   */
  //virtual
  ~MeshComponent() = default;

  /*void
    update(float deltaTime) override{}

  void
    render(DeviceContext deviceContext) override {}*/

  std::string m_name;
  std::vector<SimpleVertex> m_vertex; // Vértices de la malla
  std::vector<unsigned int> m_index; // ïndices de la malla
  int m_numVertex;
  int m_numIndex;
};