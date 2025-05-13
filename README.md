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

## 🛠 Instalación

1. Clona el repositorio:

   ```bash
   git clone https://github.com/theposi/Get-Next-Line.git
   ```

2. Accede al directorio del proyecto:

   ```bash
   cd Get-Next-Line
   ```

3. Agrega el archivo `main.c` con el siguiente contenido:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *buffer;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nombre_del_archivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int invalid_fd = 42;
    printf("Intentando leer de un fd arbitrario (%d):\n", invalid_fd);
    buffer = get_next_line(invalid_fd);

    if (buffer == NULL) {
        printf("gnl devolvió NULL para el fd arbitrario %d, como esperaba\n", invalid_fd);
    } else {
        printf("gnl devolvió algo inesperado para el fd arbitrario %d.\n", invalid_fd);
        free(buffer);
    }

    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
```

4. Compila los archivos con:

   ```bash
    cc -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c -o gnl_test
   ```

   Esto generará los objetos necesarios para probar el comportamiento de la función.

## ▶️ Uso

Ejecuta el programa con un archivo de texto:

```bash
./gnl_test archivo.txt
```

## 💡 Ejemplo de Ejecución

```bash
$ ./gnl_test ejemplo.txt
Intentando leer de un fd arbitrario (42):
gnl devolvió NULL para el fd arbitrario 42, como esperaba
```

## 📁 Estructura del Proyecto

- `get_next_line.c` – Función principal.
- `get_next_line_utils.c` – Funciones auxiliares.
- `get_next_line.h` – Header principal.
- `get_next_line_bonus.c` / `.h` / `_utils_bonus.c` – Versión con soporte para múltiples FDs.

## 📜 Licencia

Este proyecto está bajo la licencia MIT. Consulta el archivo `LICENSE` para más información.
