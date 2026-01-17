#include "BaseApp.h"
#include "UserInterface.h"

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
BaseApp g_bApp;

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK
WndProc(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;

  if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    return true;

  switch (message) {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;

  case WM_SIZE:
    g_bApp.ResizeWindow(hWnd, lParam);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  case WM_KEYDOWN:
    g_bApp.keys[wParam] = true;
    break;

  case WM_KEYUP:
    g_bApp.keys[wParam] = false;
    break;

  case WM_RBUTTONDOWN:
    g_bApp.mouseRightDown = true;
    break;

  case WM_RBUTTONUP:
    g_bApp.mouseRightDown = false;
    break;

  case WM_MBUTTONDOWN:
    g_bApp.mouseMiddleDown = true;
    break;

  case WM_MBUTTONUP:
    g_bApp.mouseMiddleDown = false;
    break;

  case WM_MOUSEMOVE:
    if (g_bApp.mouseRightDown) {
      int x = LOWORD(lParam);
      int y = HIWORD(lParam);
      g_bApp.RotateCamera(x, y);
    } else if (g_bApp.mouseMiddleDown) {
      int x = LOWORD(lParam);
      int y = HIWORD(lParam);
      g_bApp.PanCamera(x, y);
    }
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
  return g_bApp.run(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc);
}