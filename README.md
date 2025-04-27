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

El GameLoop principal de main ha sido traspasado a la clase BaseApp, donde se le agregaron métodos de ResizeWindow, para redimensioanr la pantalla sin distorcionar los elementos renderizados; UpdateCamera para la lógica que actualiza la posicón y orientación de la cámara, junto a updateTranslationByKey, que actualiza la posicón del cubo y de la cámara utilizando las llamadas a teclas, eventos que gestiona el main desde WndProc.
Se agregó ImGui para poder gestionar elementos de UI, actualmente tiene Docking y una pestaña encargada de actualizar y poder manipular los elementos de Transform del cubo.

![image](https://github.com/user-attachments/assets/607946d7-4b01-424b-b05d-fc7ca7f8ae33)

### Tercer Parcial
- `MeshComponent.h` - Representa un componente de malla, almacenando vértices e índices de una malla 3D y permite su renderización y actualización dentro del sistema ECS.
- `ModelLoader.h` - Maneja la carga de modelos 3D, soporta formatos FBX y OBJ. Inicializa un gestor de FBX, importa y procesa mallas, vértices, índices, y materiales, mediante el uso de la librería OBJ_Loader y el SDK de FBX.
-  `Component.h` - Parte del ECS, proporciona métodos virtuales puros para actualizar y renderizar, y un método para obtener el tipo del componente.
-  `Entity.h` - Parte del ECS, define la interfaz básica para entidades del juego, permitiendo agregar, obtener componentes y realizar actualizaciones y renderizados.
-  `Actor.h` - Parte de ECS y hereda de Entity, representando un actor en escena con componentes como mallas y texturas, y proporciona métodos para y gestionar componentes.
-  `Actor.h` - Parte de ECS y hereda de Component, gestiona la posición, rotación y escala de un objeto, permitiendo actualizar estos valores y aplicarlos a la matriz de transformación de los actores.

Actualmente, el proyecto está diseñado para cargar, mostrar y gestionar actores representados por modelos 3D en formatos FBX y OBJ, con soporte completo para texturas. Cada actor es representado por una serie de componentes que permiten una mayor flexibilidad y escalabilidad en su gestión dentro del proyecto. La arquitectura del proyecto está basada en un sistema de Entity-Component-System (ECS), lo que facilita la adición, eliminación y manipulación de diferentes tipos de componentes asociados a un actor, pues es una estructura modular.

![Captura de pantalla 2025-04-26 210419](https://github.com/user-attachments/assets/809ad806-5a6c-46f2-bd57-660be5ca0bf9)
