#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

void md5sum(const char *str, char *output) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)str, strlen(str), digest);

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(&output[i * 2], "%02x", (unsigned int)digest[i]);
    }
}

int main() {
    char input[256]; // Define un tamaño de búfer adecuado para la entrada
    printf("Introduce una frase y te la convierto a md5: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error al leer la entrada.\n");
        return 1;
    }

    // Eliminar el salto de línea al final, si existe
    input[strcspn(input, "\n")] = 0;

    char output[MD5_DIGEST_LENGTH * 2 + 1]; // Dos caracteres por byte + carácter nulo
    md5sum(input, output);

    printf("MD5 de '%s' es: %s\n", input, output);
    return 0;
}
