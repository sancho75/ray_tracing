#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scene.h"
#include "constants.h"


// Funzione per sottrarre due vettori
Vector3 vector_sub(Vector3 a, Vector3 b) {
    return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

// Funzione per normalizzare un vettore
Vector3 vector_normalize(Vector3 v) {
    float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return (Vector3){v.x / length, v.y / length, v.z / length};
}

// Genera un raggio partendo dalla camera verso un pixel del viewport
Ray generate_ray(Scene *scene, int i, int j, int width, int height) {
    float u = (i + 0.5f) - width / 2.0f;
    float v = (j + 0.5f) - height / 2.0f;

    u *= scene->viewport_width / width;
    v *= scene->viewport_height / height;

    Vector3 direction = vector_normalize((Vector3){u, v, -scene->viewport_distance});
    return (Ray){scene->camera, direction};
}

// Carica la scena dal file
int load_scene(const char *filename, Scene *scene) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open scene file");
        return 1;
    }

    // Legge il viewport
    if (fscanf(file, "VP %f %f %f\n", &scene->viewport_width, &scene->viewport_height, &scene->viewport_distance) != 3) {
        fprintf(stderr, "Error reading viewport dimensions\n");
        fclose(file);
        return 1;
    }

    // Ignora il colore di sfondo (non usato in questa implementazione)
    if (fscanf(file, "BG %*d %*d %*d\n") != 0) {
        fprintf(stderr, "Error reading background color\n");
        fclose(file);
        return 1;
    }

    // Legge il numero di sfere
    if (fscanf(file, "OBJ_N %d\n", &scene->sphere_count) != 1) {
        fprintf(stderr, "Error reading object count\n");
        fclose(file);
        return 1;
    }

    // Alloca memoria per le sfere
    scene->spheres = malloc(scene->sphere_count * sizeof(Sphere));
    if (!scene->spheres) {
        perror("Failed to allocate memory for spheres");
        fclose(file);
        return 1;
    }

    // Legge le sfere
    for (int i = 0; i < scene->sphere_count; i++) {
        if (fscanf(file, "S %f %f %f %f %hhu %hhu %hhu\n",
                   &scene->spheres[i].center.x, &scene->spheres[i].center.y, &scene->spheres[i].center.z,
                   &scene->spheres[i].radius,
                   &scene->spheres[i].r, &scene->spheres[i].g, &scene->spheres[i].b) != 7) {
            fprintf(stderr, "Error reading sphere data\n");
            free(scene->spheres);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Libera la memoria allocata per la scena
void free_scene(Scene *scene) {
    free(scene->spheres);
}

// Traccia un raggio per determinare il colore di un pixel
Color trace_ray(Scene *scene, Ray *ray) {
    float closest_t = INFINITY;
    Sphere *closest_sphere = NULL;

    for (int i = 0; i < scene->sphere_count; i++) {
        // Calcolo dell'intersezione con la sfera
        Vector3 oc = vector_sub(ray->origin, scene->spheres[i].center);
        float a = 1.0f; // Ray direction è normalizzato
        float b = 2.0f * (oc.x * ray->direction.x + oc.y * ray->direction.y + oc.z * ray->direction.z);
        float c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - scene->spheres[i].radius * scene->spheres[i].radius;
        float discriminant = b * b - 4 * a * c;

        if (discriminant >= 0) {
            float t = (-b - sqrtf(discriminant)) / (2.0f * a);
            if (t > 0 && t < closest_t) {
                closest_t = t;
                closest_sphere = &scene->spheres[i];
            }
        }
    }

    if (closest_sphere) {
        return (Color){closest_sphere->r, closest_sphere->g, closest_sphere->b};
    }

    return (Color){BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B};
}
