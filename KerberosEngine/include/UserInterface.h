#pragma once
#include "Prerequisites.h"
#include "ImGuizmo.h"
#include "ECS/Transform.h"

// Forward Declarations
class Window;
class Device;
class DeviceContext;

class
UserInterface {
public:
  /**
   * @brief Default constructor and destructor.
   */
  UserInterface() = default;
  ~UserInterface() = default;

  /**
   * @brief Initializes the user interface elements.
   */
  void
  init(void* window,
       ID3D11Device* device,
       ID3D11DeviceContext* deviceContext);

  /**
   * @brief Updates the status of the user interface.
   */
  void
  update();

  /**
   * @brief Renders the user interface in the window.
   */
  void
  render();

  /**
   * @brief Frees up resources used by the user interface.
   */
  void
  destroy();

  /**
   * @brief Set the style and colors of the UI using ImGUI
   */
  void
  setupGUIStyle();

  /**
   * @brief Place holder method, contains the user interface components to be displayed in the ImGui tab
   */
  void
  GUITab(const std::string& tabName);

  /**
   * @brief Place holder method, contains the user interface components to be displayed in the ImGui tab
   */
  void
  TransformGUI(Transform& transform);

  /**
   * @brief Allows you to manipulate three float values in the GUI
   * @param label Label to be displayed next to the control.
   * @param values Pointer to the two floating values (X, Y, Z) to be manipulated.
   * @param resetValues Default value to reset the values.
   * @param columnWidth Width of the column to arrange the interface elements.
   */
  void
  vec3Control(const std::string& label,
             float* values,
             float resetValues = 0.0f,
             float columnWidth = 100.0f);

private:
};