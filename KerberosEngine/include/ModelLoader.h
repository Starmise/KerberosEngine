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
   * @brief Initializes the FBX manager, IO settings, and creates a new scene.
   */
  bool
  InitializeFBXManager();

  /**
   * @brief Loads an FBX model from a given file path and processes its contents.
   * @param filePath Path to the .fbx file to load.
   */
  bool
  LoadFBXModel(const std::string& filePath);

  /**
   * @brief Uses recusivity to process a node in the FBX scene graph.
   * @param node Pointer to the FBX node to process.
   */
  void
  ProcessFBXNode(FbxNode* node);

  /**
   * @brief Extracts vertex, index, and UV data from a mesh node.
   * @param node Node containing the mesh to process.
   */
  void
  ProcessFBXMesh(FbxNode* node);

  /**
   * @brief Extracts texture file names from a surface material.
   * @param material Pointer to the FBX surface material to extract data from.
   */
  void
  ProcessFBXMaterials(FbxSurfaceMaterial* material);

  /**
   * @brief  Returns the list of texture file names from the FBX.
   */
  std::vector<std::string>
  GetTextureFileNames() const { return textureFileNames; }

  /**
  * @brief Uses the `objl::Loader` to parse the file and extract mesh data.
  * @param filePath The path to the .obj file to load.
  */
  bool 
  LoadOBJ_model(const std::string& filePath);

  /**
   * @brief Loads an OBJ model and returns the data as a LoadDataOBJ structure.
   * @param objFileName Path to the .obj file to load.
   */
  LoadDataOBJ
  LoadOBJ(std::string objFileName);

private:
  FbxManager* lSdkManager;
  FbxScene* lScene;
  std::vector<std::string> textureFileNames;
public:
  std::vector<MeshComponent> meshes;
  std::string modelName;
};


/*
* No se añadieron los archivos alembic-mt.lib, libfbxsdk-md.lib y libfbxsdk-mt.lib del path:
* ...\KerberosEngine\KerberosEngine\lib\fbxlibs, debido a su peso mayor a 100mb
*/