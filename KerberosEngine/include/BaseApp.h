#pragma once
#include "Prerequisites.h"

class BaseApp
{
public:
  /**
   * @brief Default constructor and destructor 
   */
  BaseApp() = default;
  ~BaseApp() = default;

  /**
   * @brief Initializes the application by setting up the necessary resources.
   * @return HRESULT indicating success or failure of the initialization.
   */
  HRESULT
  init();

  /**
   * @brief  Updates the application logic for each frame.
   */
  void
  update();

  /**
   * @brief Renders the elements on the window.
   */
  void
  render();

  /**
   * @brief Releases resources and elements before exiting to free memory.
   */
  void
  destroy();

  /**
   * @brief Runs the application from the main entry point.
   * @param hInstance Handle to the instance of the program.
   * @param hPrevInstance Handle to the previous instance.
   * @param lpCmdLine Command-line as a string.
   * @param nCmdShow Indicate how the window should be displayed.
   * @param wndproc Pointer to the window function for handling messages.
   */
  int
  run(HINSTANCE hInstance,
      HINSTANCE hPrevInstance,
      LPWSTR lpCmdLine,
      int nCmdShow,
      WNDPROC wndproc);

private:

};