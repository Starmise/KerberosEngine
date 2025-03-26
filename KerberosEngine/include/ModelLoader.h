#pragma once
#include  "Prerequisites.h"
#include  "MeshComponent.h"
#include "fbxsdk.h"

class
ModelLoader {
public:
  /**
   * @brief Default constructor and destructor.
   */
  ModelLoader() = default;
  ~ModelLoader() = default;

  /**
   * @brief
   */
  bool
  LoadFBXModel(const std::string& filePath);

  /**
   * @brief
   */
  void
  ProcessFBXNode(FbxNode* node);

  /**
   * @brief
   */
  void
  ProcessFBXMesh(FbxNode* node);

  /**
   * @brief
   */
  std::vector<std::string>
  ProcessFBXMaterials() const { return textureFileNames; }

private:
  FbxManager* lSdkManager;
  FbxScene* lScene;
  std::vector<std::string> textureFileNames;
public:
  std::vector<MeshComponent> meshes;
};