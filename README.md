# KerberosEngine
Este es un compendio de las clases vistas en la materia de Arquitectura de Motores Graficos. El objetivo de la materia es generar un motor gráfico usando DirectX. Este motor busca proporcionar un entorno para poder renderizar modelos y objetos 3D en tiempo real dentro de una ventana.

## Clases Implementadas
### Primer Parcial
- `Window.h` - Se encarga de inicializar y configurar la ventana del proyecto.
- `Device.h` - Se encarga de la creación de recursos esenciales para presentar en pantalla.
- `DeviceContext.h` - Se encarga de setear y limpiar los recursos creados por Device para el renderizado.
- `Texture.h` - Es la clase que contiene la lógica para poder administrar la carga de texturas DDS y PNG.
- `SwapChain.h` - Maneja los buffers del render.
- `RenderTargetView.h` - Es la clase encargada de manejar la vista del render en pantalla.
- `DepthStencilView.h` - Es la clase encargada de manejar la posición en profundidad de los objetos.

![Captura de pantalla 2025-02-13 231458](https://github.com/user-attachments/assets/555abefd-5378-41b3-855a-ffd32413d1a6)

### Segundo Parcial
- `Viewport` - Define el área de visualización del render en la pantalla.
- `InputLayout.h` - Se encarga del formato de los vértices usados en el render pipeline.
- `ShaderProgram.h` -  Maneja la creación y vinculación de Shaders en la GPU.
- `Buffer.h` - Clase que administra los Vertex, Index y Constant Buffers esenciales para la renderización.
- `SamplerState.h` - Controla la forma en que las texturas son mostreadas dentro del programa.
- `UserInterface.h` - Clase que implementa la interfaz de usuario basada en ImGui, desde el estilo hasta la lógica de cada tab.

Actualmente, el GameLoop principal de main ha sido traspasado a la clase BaseApp, donde se le agregaron métodos de ResizeWindow, para redimensioanr la pantalla sin distorcionar los elementos renderizados; UpdateCamera para la lógica que actualiza la posicón y orientación de la cámara, junto a updateTranslationByKey, que actualiza la posicón del cubo y de la cámara utilizando las llamadas a teclas, eventos que gestiona el main desde WndProc.
Se agregó ImGui para poder gestionar elementos de UI, actualmente tiene Docking y una pestaña encargada de actualizar y poder manipular los elementos de Transform del cubo.

![image](https://github.com/user-attachments/assets/607946d7-4b01-424b-b05d-fc7ca7f8ae33)

