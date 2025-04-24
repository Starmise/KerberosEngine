#include "ModelLoader.h"
#include "OBJ_Loader.h"

bool
ModelLoader::InitializeFBXManager() {
  lSdkManager = FbxManager::Create();
  if (!lSdkManager) {
    ERROR("ModelLoader", "FbxManager:: Create()", "Unable to create FBX Manager!");
    return false;
  }
  else {
    MESSAGE("ModelLoader", "ModelLoader", "Autodesk FBX SDK Version" << lSdkManager->GetVersion())
  }

  // Create an IOSettings object
  FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
  lSdkManager->SetIOSettings(ios);

  // Create an FBX scene
  lScene = FbxScene::Create(lSdkManager, "myScene");
  return true;
}

bool
ModelLoader::LoadFBXModel(const std::string& filePath) {
  // 00. Init the SDK from FBX Manager
  if (InitializeFBXManager()) {

    // 01. Create an importer using the SDK manager
    FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

    // 02. Use the first argument as the filename for the importer
    if (!lImporter->Initialize(filePath.c_str(), -1, lSdkManager->GetIOSettings())) {
      ERROR("ModelLoader", "LoadFBXModel", "Unable to initialize FBX importer for file: " << filePath.c_str());
      ERROR("ModelLoader", "LoadFBXModel", "Error returned: " << lImporter->GetStatus().GetErrorString());
      return false;
    }

    // 03. Import the scene
    if (!lImporter->Import(lScene)) {
      ERROR("ModelLoader", "lImporter->Import", "Unable to import the FBX scene from file: " << filePath.c_str());
      lImporter->Destroy();
      return false;
    }

    // 04. Destroy the importer
    lImporter->Destroy();
    MESSAGE("ModelLoader", "LoadFBXModel", "Successfully imported the FBX scene from file: " << filePath.c_str());

    // 05. Process the scene
    FbxNode* lRootNode = lScene->GetRootNode();

    if (lRootNode) {
      for (int i = 0; i < lRootNode->GetChildCount(); i++) {
        ProcessFBXNode(lRootNode->GetChild(i));
      }
    }

    // 06. Process the mats
    int materialCount = lScene->GetMaterialCount();
    for (int i = 0; i < materialCount; i++) {
      FbxSurfaceMaterial* material = lScene->GetMaterial(i);
      ProcessFBXMaterials(material);
    }
    
    return true;
  }
  return false;
}

void
ModelLoader::ProcessFBXNode(FbxNode* node) {
  // 01. Process all the node's meshes
  if (node->GetNodeAttribute()) {
    if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh) {
      ProcessFBXMesh(node);
    }
  }

  // 02. Recursively process each child node
  for (int i = 0; i < node->GetChildCount(); i++) {
    ProcessFBXNode(node->GetChild(i));
  }
}

void
ModelLoader::ProcessFBXMesh(FbxNode* node) {
  // 01. Get the mesh from the node. If there is no mesh, exit early.
  FbxMesh* mesh = node->GetMesh();
  if (!mesh) return;

  std::vector<SimpleVertex> vertices;
  std::vector<unsigned int> indices;

  // 02. Process vertices: extract positions from control points.
  for (int i = 0; i < mesh->GetControlPointsCount(); i++) {
    SimpleVertex vertex;
    FbxVector4* controlPoint = mesh->GetControlPoints();
    vertex.Pos = XMFLOAT3((float)controlPoint[i][0],
      (float)controlPoint[i][1],
      (float)controlPoint[i][2]);
    vertices.push_back(vertex);
  }

  // 03. Process UV coordinates if available.
  if (mesh->GetElementUVCount() > 0) {
    FbxGeometryElementUV* uvElement = mesh->GetElementUV(0);
    FbxGeometryElement::EMappingMode mappingMode = uvElement->GetMappingMode();
    FbxGeometryElement::EReferenceMode referenceMode = uvElement->GetReferenceMode();
    int polyIndexCounter = 0; // Counter for polygon vertex indexing when mapping by polygon vertex

    // 03.1 Iterate through each polygon in the mesh.
    for (int polyIndex = 0; polyIndex < mesh->GetPolygonCount(); polyIndex++) {
      int polySize = mesh->GetPolygonSize(polyIndex);

      // 03.1.1 Process each vertex in the polygon.
      for (int vertIndex = 0; vertIndex < polySize; vertIndex++) {
        int controlPointIndex = mesh->GetPolygonVertex(polyIndex, vertIndex);
        int uvIndex = -1;

        // 03.1.1.1 Handle UV mapping mode: by control point.
        if (mappingMode == FbxGeometryElement::eByControlPoint) {
          if (referenceMode == FbxGeometryElement::eDirect) {
            uvIndex = controlPointIndex;
          }
          else if (referenceMode == FbxGeometryElement::eIndexToDirect) {
            uvIndex = uvElement->GetIndexArray().GetAt(controlPointIndex);
          }
        }
        // 03.1.1.2 Handle UV mapping mode: by polygon vertex.
        else if (mappingMode == FbxGeometryElement::eByPolygonVertex) {
          if (referenceMode == FbxGeometryElement::eDirect || referenceMode == FbxGeometryElement::eIndexToDirect) {
            uvIndex = uvElement->GetIndexArray().GetAt(polyIndexCounter);
            polyIndexCounter++;
          }
        }

        //03 1.1.3 If a valid UV index is found, set the texture coordinate
        if (uvIndex != -1) {
          FbxVector2 uv = uvElement->GetDirectArray().GetAt(uvIndex);
          vertices[controlPointIndex].Tex = XMFLOAT2((float)uv[8], -(float)uv[1]);
        }
      }
    }
  }

  // 04. Process indices: store each polygon vertex index
  for (int i = 0; i < mesh->GetPolygonCount(); i++) {
    for (int j = 0; j < mesh->GetPolygonSize(i); j++) {
      indices.push_back(mesh->GetPolygonVertex(i, j));
    }
  }

  // 05. Create a MeshComponent to store the processed mesh data.
  MeshComponent meshData;
  meshData.m_name = node->GetName();
  meshData.m_vertex = vertices;
  meshData.m_index = indices;
  meshData.m_numVertex = vertices.size();
  meshData.m_numIndex = indices.size();

  // 06. Add the processed mesh data to the collection.
  meshes.push_back(meshData);
}

void
ModelLoader::ProcessFBXMaterials(FbxSurfaceMaterial* material) {
  if (material) {
    FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
    if (prop.IsValid()) {
      int textureCount = prop.GetSrcObjectCount<FbxTexture>();
      for (int i = 0; i < textureCount; ++i) {
        FbxTexture* texture = FbxCast<FbxTexture>(prop.GetSrcObject<FbxTexture>(i));
        if (texture) {
          textureFileNames.push_back(texture->GetName());
        }
      }
    }
  }
}

bool ModelLoader::LoadOBJ_model(const std::string& filePath) {
  objl::Loader loader;
  if (!loader.LoadFile(filePath)) {
    ERROR("ModelLoader", "LoadOBJ_model", "No se pudo cargar el archivo OBJ: " << filePath.c_str());
    return false;
  }

  meshes.clear();

  for (const auto& mesh : loader.LoadedMeshes) {
    MeshComponent meshData;
    meshData.m_name = mesh.MeshName;

    for (const auto& v : mesh.Vertices) {
      SimpleVertex sv;
      sv.Pos = XMFLOAT3(v.Position.X, v.Position.Y, v.Position.Z);
      sv.Tex = XMFLOAT2(v.TextureCoordinate.X, -v.TextureCoordinate.Y); // invertir eje Y de textura
      meshData.m_vertex.push_back(sv);
    }

    meshData.m_index = mesh.Indices;
    meshData.m_numVertex = meshData.m_vertex.size();
    meshData.m_numIndex = meshData.m_index.size();

    meshes.push_back(meshData);
    MESSAGE("ModelLoader", "OBJ", ("Submesh OBJ: " + meshData.m_name).c_str());
  }

  return true;
}

LoadDataOBJ 
ModelLoader::LoadOBJ(std::string objFileName) {
  LoadDataOBJ LD; 
  objl::Loader loader;

  loader.LoadFile(objFileName);
  LD.name = objFileName;

  // Load and set data to custom structure
  LD.vertex.resize(loader.LoadedVertices.size());

  for (int i = 0; i < LD.vertex.size(); i++) 
  {
    LD.vertex[i].Pos.x = loader.LoadedVertices[i].Position.X;
    LD.vertex[i].Pos.y = loader.LoadedVertices[i].Position.Y;
    LD.vertex[i].Pos.z = loader.LoadedVertices[i].Position.Z;

    LD.vertex[i].Tex.x = loader.LoadedVertices[i].TextureCoordinate.X;
    LD.vertex[i].Tex.y = loader.LoadedVertices[i].TextureCoordinate.Y;
  }

  LD.index.resize(loader.LoadedIndices.size());
  for (int i = 0; i < LD.index.size(); i++) 
  {
    LD.index[i] = loader.LoadedIndices[i];
  }

  LD.numVertex = LD.vertex.size();
  LD.numIndex = LD.index.size();

  return LD;
}
