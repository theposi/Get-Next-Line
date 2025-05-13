#include "get_next_line.h"

int main(int argc, char *argv[])
{
    char *buffer;

    if (argc == 2) {
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            perror("open");
            return EXIT_FAILURE;
        }

        printf("Leyendo desde el archivo: %s\n\n", argv[1]);
        while ((buffer = get_next_line(fd)) != NULL) {
            printf("%s", buffer);
            free(buffer);
        }

        if (close(fd) == -1) {
            perror("close");
            return EXIT_FAILURE;
        }
    }
    else {
        int invalid_fd = 42;
        printf("No se proporcionó un archivo. Probando con fd inválido (%d):\n", invalid_fd);

        buffer = get_next_line(invalid_fd);
        if (buffer == NULL) {
            printf("get_next_line devolvió NULL como se esperaba para fd %d\n", invalid_fd);
        } else {
            printf("get_next_line devolvió algo inesperado para fd %d\n", invalid_fd);
            free(buffer);
        }
    }

    return 0;
}

