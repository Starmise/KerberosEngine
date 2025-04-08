#include "UserInterface.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "BaseApp.h"

void 
UserInterface::init(void* window, 
                    ID3D11Device* device, 
                    ID3D11DeviceContext* deviceContext) {
  IMGUI_CHECKVERSION(); // Check ImGUI version
  ImGui::CreateContext(); // Initialize the context
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  // Setup GUI Style
  setupGUIStyle();

  // / When viewports are enabled we tweak WindowRounding/WindoBg so platform windows can look identical to regular ones.
  ImGuiStyle& style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // Setup Platform and Renderer bindings
  ImGui_ImplWin32_Init(window);
  ImGui_ImplDX11_Init(device, deviceContext);

}

void 
UserInterface::update() {
  // Start the Dear ImGui frame
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

void 
UserInterface::render() {
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
  ImGuiIO& io = ImGui::GetIO();

  // Update and Render additional Platform Windows
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault(); // Update default platform for Windows
    //if (ImGui::DragFloat3("Posición", reinterpret_cast<float*>(&g_bApp.position), 0.1f)) {
  }
}

void 
UserInterface::destroy() {
  // Cleanup
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}

void
UserInterface::setupGUIStyle() {
  ImGuiStyle& style = ImGui::GetStyle();

  // Ajuste de bordes
  style.WindowBorderSize = 2.0f;
  style.FrameBorderSize = 2.0f;
  style.WindowRounding = 4.0f;
  style.FrameRounding = 4.0f;
  style.ScrollbarRounding = 3.0f;
  style.GrabRounding = 3.0f;

  // Colores con mayor contraste
  ImVec4 yellow = ImVec4(0.95f, 0.75f, 0.05f, 1.00f);       // Amarillo principal con más brillo
  ImVec4 yellowHover = ImVec4(1.00f, 0.7f, 0.15f, 1.00f);   // Amarillo más oscuro al hacer hover
  ImVec4 yellowActive = ImVec4(1.00f, 0.5f, 0.1f, 1.00f);   // Amarillo tirando a naranja al hacer clic

  ImVec4 darkBlue = ImVec4(0.05f, 0.05f, 0.2f, 1.00f);        // Azul oscuro más profundo para el título
  ImVec4 darkBlueActive = ImVec4(0.1f, 0.1f, 0.3f, 1.00f);    // Azul más brillante al estar activo

  ImVec4* colors = style.Colors;

  // Fondo de la ventana más oscuro
  colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.08f, 0.08f, 1.00f);

  // Títulos con azul oscuro
  colors[ImGuiCol_TitleBg] = darkBlue;
  colors[ImGuiCol_TitleBgActive] = darkBlueActive;
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.04f, 0.04f, 0.2f, 1.00f);

  // Bordes con amarillo más brillante
  colors[ImGuiCol_Border] = yellow;

  // Elementos interactivos con mayor contraste
  colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = yellowHover;
  colors[ImGuiCol_FrameBgActive] = yellowActive;

  // Botones
  colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);  // Fondo más oscuro para resaltar el amarillo al pasar hover
  colors[ImGuiCol_ButtonHovered] = yellowHover;
  colors[ImGuiCol_ButtonActive] = yellowActive;

  // Checkboxes y sliders
  colors[ImGuiCol_CheckMark] = yellow;
  colors[ImGuiCol_SliderGrab] = yellow;
  colors[ImGuiCol_SliderGrabActive] = yellowHover;

  // Headers
  colors[ImGuiCol_Header] = darkBlue;
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.45f, 0.65f, 1.0f); // Azul más claro
  colors[ImGuiCol_HeaderActive] = darkBlueActive;

  // Líneas de gráficos
  colors[ImGuiCol_PlotLines] = yellow;
  colors[ImGuiCol_PlotHistogram] = yellow;

  // Textos
  colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);  // Texto más claro para mejor visibilidad
}

void 
UserInterface::GUITab(const std::string& tabName) {
  ImGui::Begin(tabName.c_str());
  ImGui::End();
}

void 
UserInterface::TransformGUI(Transform& transform) {

  ImGui::Begin("Transform"); 

  // Ahora se obtienen los valores antes de manipularlos
  EngineUtilities::Vector3 position = transform.getPosition();
  EngineUtilities::Vector3 rotation = transform.getRotation();
  EngineUtilities::Vector3 scale = transform.getScale();

  // Se editan los valores en ImGui
  if (ImGui::DragFloat3("Position", &position.x, 0.1f)) {
    transform.setPosition(position);
  }
  if (ImGui::DragFloat3("Rotation", &rotation.x, 0.1f)) {
    transform.setRotation(rotation);
  }
  if (ImGui::DragFloat3("Scale", &scale.x, 0.1f)) {
    transform.setScale(scale);
  }

  ImGui::End();
}

void
UserInterface::vec3Control(const std::string& label, 
                                float* values, 
                                float resetValues,
                                float columnWidth) {
  ImGuiIO& io = ImGui::GetIO();
  auto boldFont = io.Fonts->Fonts[0];

  ImGui::PushID(label.c_str());

  ImGui::Columns(2);
  ImGui::SetColumnWidth(0, columnWidth);
  ImGui::Text(label.c_str());
  ImGui::NextColumn();

  ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

  float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
  ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
  ImGui::PushFont(boldFont);
  if (ImGui::Button("X", buttonSize)) values[0] = resetValues;
  ImGui::PopFont();
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::DragFloat("##X", &values[0], 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
  ImGui::PushFont(boldFont);
  if (ImGui::Button("Y", buttonSize)) values[1] = resetValues;
  ImGui::PopFont();
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::DragFloat("##Y", &values[1], 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PopStyleVar();
  ImGui::Columns(1);

  ImGui::PopID();
}
