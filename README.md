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
