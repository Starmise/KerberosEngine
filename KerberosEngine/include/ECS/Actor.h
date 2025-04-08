#pragma once
#include "Prerequisites.h"
#include "ECS/Entity.h"
#include "Buffer.h"
#include "Texture.h"
#include "SamplerState.h"
#include "Transform.h"
using namespace std;

// Forward Declarations
class Device;
class Component;

class Actor : Entity {
public:
  /*
  * @brief Default Constructor
  */
  Actor() = default;

  /*
  * @brief Constructor that initializes the actor with a Device
  */
  Actor(Device& device);

  /*
  * @brief Virtual destructor
  */
  virtual ~Actor() = default;

  /*
  * @brief Updates the actor
  * @param deltaTime The time elapsed since the last update
  * @param deviceContext Reference to the device context used for update.
  */
  void
  update(float deltaTime, DeviceContext& deviceContext) override;

  /*
  * @brief Renders the actor
  * @param deviceContext Reference to the device context used for rendering.
  */
  void
  render(DeviceContext& deviceContext) override;

  /**
   * @brief Destroys the actor and releases associated resources.
   */
  void
  destroy();

  /**
   * @brief Sets the mesh of the actor.
   * @param device Reference to the device.
   * @param meshes Vector of Mesh Components objects representing meshes.
   */
  void 
  setMesh(Device& device, std::vector<MeshComponent> meshes);

  /**
  * @brief Sets the textures of the actor.
  * @param textures Vector of Texture objects.
  */
  void 
  setTextures(vector<Texture> textures) {
    m_textures = textures;
  }

  /**
   * @brief Function to get only the actor's name
   */
  string
  getName() {
    return m_name;
  }

  /*
  * @brief Actor using the type of the specific component as template arguments.
  */
  template<typename T>
  EngineUtilities::TSharedPointer<T>
  getComponent();

private:
  vector<MeshComponent> m_meshes;
  vector<Texture> m_textures;
  vector<Buffer> m_vertexBuffers;
  vector<Buffer> m_indexBuffers;
  vector<Buffer> m_buffers;

  Buffer m_modelBuffer;
  SamplerState m_sampler;
  CBChangesEveryFrame m_changeEveryFrame;
  string m_name = "Actor";
};

/*
  * The purpose of this function is to search for and return a specific component of an actor using the specific component type as template arguments.
  * actor using the type of the specific component as template arguments.
  * If the component is not found, the function returns nullptr.
  */
template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
  for (auto& component : m_components) {
    EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
    if (specificComponent) {
      return specificComponent;
    }
  }
  // Returns an empty TSharedPointer if the component is not found.
  return EngineUtilities::TSharedPointer<T>();
}