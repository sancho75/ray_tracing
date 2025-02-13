#Tchakounte Nzoumeni Yvan Landry (SM3201458)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "constants.h"
#include <math.h>
#include <omp.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "scene.h"
#include "ppm.h"

int main(int argc, char *argv[]) {
    // Controllo dei parametri di input
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <scene_file> <output_image> <width> <height>\n", argv[0]);
        return 1;
    }

    const char *scene_file = argv[1];
    const char *output_image = argv[2];
    int width = atoi(argv[3]);
    int height = atoi(argv[4]);

    if (width <= 0 || height <= 0) {
        fprintf(stderr, "Width and height must be positive integers.\n");
        return 1;
    }

    // Caricamento della scena
    Scene scene;
    if (load_scene(scene_file, &scene) != 0) {
        fprintf(stderr, "Error loading scene from file: %s\n", scene_file);
        return 1;
    }

    // Allocazione della memoria per l'immagine
    unsigned char *image = (unsigned char *)malloc(3 * width * height);
    if (!image) {
        perror("Failed to allocate memory for the image");
        free_scene(&scene);
        return 1;
    }

    // Generazione dei raggi e calcolo dei colori in parallelo
    #pragma omp parallel for collapse(2)
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            Ray ray = generate_ray(&scene, i, j, width, height);
            Color color = trace_ray(&scene, &ray);

            int index = 3 * (j * width + i);
            image[index] = color.r;
            image[index + 1] = color.g;
            image[index + 2] = color.b;
        }
    }

    // Salvataggio dell'immagine in formato PPM
    if (save_ppm(output_image, image, width, height) != 0) {
        fprintf(stderr, "Error saving image to file: %s\n", output_image);
        free(image);
        free_scene(&scene);
        return 1;
    }

    // Liberazione delle risorse
    free(image);
    free_scene(&scene);

    printf("Rendering completed successfully. Image saved to %s\n", output_image);
    return 0;
}