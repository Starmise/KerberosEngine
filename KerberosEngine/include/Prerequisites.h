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

// Librer�as de ImGUI
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_internal.h>
#include "imgui_impl_win32.h"

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

enum
  ComponentType {
  NONE = 0,     ///< Tipo de componente no especificado.
  TRANSFORM = 1,///< Componente de transformaci�n.
  MESH = 2,     ///< Componente de malla.
  MATERIAL = 3  ///< Componente de material.
};

struct
  Camera {
  XMFLOAT3 position; 
  XMFLOAT3 target;  // Punto al que mira

  XMFLOAT3 up;      // Vector hacia arriba
  XMFLOAT3 forward; // Direcci�n adelante
  XMFLOAT3 right;   // Direci�n a la derecha

  float yaw;        // Rotaci�n en el eje Y
  float pitch;      // Rotaci�n en el eje X

  Camera() {
    position = XMFLOAT3(0.0f, 1.0f, -5.0f);
    target = XMFLOAT3(0.0f, 1.0f, 0.0f);
    up = XMFLOAT3(0.0f, 1.0f, 0.0f);
    forward = XMFLOAT3(0.0f, 0.0f, 1.0f);
    right = XMFLOAT3(1.0f, 0.0f, 0.0f);
    yaw = 0.0f;
    pitch = 0.0f;
  }
};

