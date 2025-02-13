#Tchakounte Nzoumeni Yvan Landry (SM3201458)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include "ppm.h"

int save_ppm(const char *filename, unsigned char *image, int width, int height) {
    int fd = open(filename, O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("Failed to open image file");
        return 1;
    }

    size_t image_size = 3 * width * height;
    size_t file_size = image_size + 15; // Header size

    if (ftruncate(fd, file_size) != 0) {
        perror("Failed to set file size");
        close(fd);
        return 1;
    }

    char *map = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("Failed to mmap file");
        close(fd);
        return 1;
    }

    int header_size = snprintf(map, 15, "P6\n%d %d\n255\n", width, height);
    memcpy(map + header_size, image, image_size);

    munmap(map, file_size);
    close(fd);
    return 0;
}
