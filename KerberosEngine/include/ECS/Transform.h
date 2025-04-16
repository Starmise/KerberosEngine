#pragma once
#include "Prerequisites.h"
#include "ECS/Component.h"
#include "utilities/Vectors/Vector3.h"

class
Transform : public Component {
public:
  /**
   * @brief  Constructor that initializes position, rotation, and scale with default values.
   */
  Transform() : position(),
                rotation(),
                scale(),
                matrix(),
                Component(ComponentType::TRANSFORM) {}

  /**
   * @brief Initializes transform data
   */
  void
  init();

  /**
   * @brief Updates the Transform object based on the elapsed time.
   * @param deltaTime Time elapsed since the last update.
   */
  void
  update(float deltaTime) override;

  /**
   * @brief Renders the Transform object.
   * @param window Window where the object will be rendered.
   */
  void
  render(DeviceContext& deviceContext) override {};

  /**
   * @brief Releases resources and destroys the Transform.
   */
  void
  destroy() {}

  /**
   * @brief Access the position data
   * @return The current position
   */
  const EngineUtilities::Vector3& 
  getPosition() const { return position; }
  
  /**
   * @brief Sets the new position
   */
  void
  setPosition(const EngineUtilities::Vector3& newPos) { position = newPos; }

  /**
   * @brief Access the rotation data
   * @return The current rotation
   */
  const EngineUtilities::Vector3& 
  getRotation() const { return rotation; }

  /**
   * @brief Sets the new rotation
   */
  void
  setRotation(const EngineUtilities::Vector3& newRot) { rotation = newRot; }

  /**
   * @brief Access the scale data
   * @return The current scale
   */
  const EngineUtilities::Vector3& 
  getScale() const { return scale; }

  /**
   * @brief Sets the new scale
   */
  void
  setScale(const EngineUtilities::Vector3& newScale) { scale = newScale; }

  /*
  * @brief Sets the transformation values; position, rotation and scale
  */
  void
  setTransform(const EngineUtilities::Vector3& newPos, 
               const EngineUtilities::Vector3& newRot,
               const EngineUtilities::Vector3& newSca);

private:
  EngineUtilities::Vector3 position;
  EngineUtilities::Vector3 rotation;
  EngineUtilities::Vector3 scale;

public:
  XMMATRIX matrix;
};