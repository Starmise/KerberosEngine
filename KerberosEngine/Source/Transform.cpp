#include "ECS/Transform.h"
#include "DeviceContext.h"

void 
Transform::init() {
  scale.oneVal();

  matrix = XMMatrixIdentity();
}

void 
Transform::update(float deltaTime) {
  // Apply Scale
  XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);
  // Aplicar rotation
  XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
  // Aplicar translation
  XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, position.z);

  // Compose the final matrix in the next orden: scale -> rotation -> translation
  matrix = scaleMatrix * rotationMatrix * translationMatrix;
}

void 
Transform::setTransform(const EngineUtilities::Vector3& newPos, 
                        const EngineUtilities::Vector3& newRot, 
                        const EngineUtilities::Vector3& newSca) {
  position = newPos;
  rotation = newRot;
  scale = newSca;
}
