#pragma once

// Librerias STD
#include <windows.h>
#include <sstream>
#include <vector>
#include <string>
#include <xnamath.h>

#include <iostream>

// #include memory
#include <thread>

// Librerias DirectX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "resource.h"
#include "Resource.h"

// MACROS
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

#define ERROR( classObj, method, errorMSG )  \
{                                            \
   std::wostringstream os_;                  \
   os_ << "ERROR : " << classObj << "::" << method << " : " << "  Error in data from params [" << errorMSG << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
   exit(1);                                  \
}

// Structures
struct
  SimpleVertex {
  XMFLOAT3 Pos;
  XMFLOAT2 Tex;
};

struct
  CBNeverChanges {
  XMMATRIX mView;
};

struct
  CBChangeOnResize {
  XMMATRIX mProjection;
};

struct
  CBChangesEveryFrame {
  XMMATRIX mWorld;
  XMFLOAT4 vMeshColor;
};

enum
  ExtensionType {
  DDS = 0,
  PNG = 1,
  JPG = 2
};

enum
  ShaderType {
  VERTEX_SHADER = 0,
  PIXEL_SHADER = 1
};

