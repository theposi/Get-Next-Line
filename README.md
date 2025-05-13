# Get Next Line

Este proyecto implementa una función en C llamada `get_next_line`, cuyo objetivo es leer una línea completa desde un descriptor de archivo, incluyendo el salto de línea si existe. La función puede ser llamada múltiples veces para leer línea por línea de un archivo, sin perder el contexto entre llamadas.

## Tabla de Contenidos

- [Descripción](#descripción)
- [Instalación](#instalación)
- [Uso](#uso)
- [Ejemplo de Ejecución](#ejemplo-de-ejecución)
- [Estructura del Proyecto](#estructura-del-proyecto)
- [Licencia](#licencia)

## 📄 Descripción

`get_next_line(int fd)` lee y devuelve una línea de un descriptor de archivo dado. Este proyecto implica manejar variables estáticas y garantizar una gestión adecuada de la memoria, evitando al mismo tiempo dificultades comunes como `segmentation faults` o `memory leaks`. La implementación admite funciones regulares y de bonus, incluido el manejo simultáneo de múltiples descriptores de archivos.

## 📁 Estructura del Proyecto

- `get_next_line.c` – Función principal.
- `get_next_line_utils.c` – Funciones auxiliares.
- `get_next_line.h` – Header principal.
- `docs/` – Archivos de prueba 
- `get_next_line_bonus.c` / `.h` / `_utils_bonus.c` – Versión con soporte para múltiples FDs.

## 🛠 Instalación

1. Clona el repositorio:

   ```bash
   git clone https://github.com/theposi/Get-Next-Line.git
   ```

2. Accede al directorio del proyecto:

   ```bash
   cd Get-Next-Line
   ```

3. Compila los archivos con:

   ```bash
    cc -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c -o gnl_test
   ```

   Esto generará los objetos necesarios para probar el comportamiento de la función.

## ▶️ Uso

#### Con archivo

```bash
$ ./gnl_test ./docs/random.txt 

Leyendo desde el archivo: ejemplo.txt

Hola, mundo.
Esta es una prueba de get_next_line.
¡Funciona línea por línea!

```

#### Sin archivo

```bash
$ ./gnl_test 

No se proporcionó un archivo. Probando con fd inválido (42):
get_next_line devolvió NULL como se esperaba para fd 42
```

## 📜 Licencia

Este proyecto está bajo la licencia MIT. Consulta el archivo `LICENSE` para más información.
