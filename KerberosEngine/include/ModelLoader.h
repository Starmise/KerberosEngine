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
  InitializeFBXManager();

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
  void
  ProcessFBXMaterials(FbxSurfaceMaterial* material);

  /**
   * @brief
   */
  std::vector<std::string>
  GetTextureFileNames() const { return textureFileNames; }

private:
  FbxManager* lSdkManager;
  FbxScene* lScene;
  std::vector<std::string> textureFileNames;
public:
  std::vector<MeshComponent> meshes;
};


/*
* No se añadieron los archivos alembic-mt.lib, libfbxsdk-md.lib y libfbxsdk-mt.lib del path:
* ...\KerberosEngine\KerberosEngine\lib\fbxlibs, debido a su peso mayor a 100mb
*/