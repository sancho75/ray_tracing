#Tchakounte Nzoumeni Yvan Landry (SM3201458)

#ifndef SCENE_H
#define SCENE_H

typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

typedef struct {
    Vector3 center;
    float radius;
    unsigned char r, g, b;
} Sphere;

typedef struct {
    Sphere *spheres;
    int sphere_count;
    Vector3 camera;
    float viewport_width;
    float viewport_height;
    float viewport_distance;
} Scene;

typedef struct {
    unsigned char r, g, b;
} Color;
// Funzioni
int load_scene(const char *filename, Scene *scene);
void free_scene(Scene *scene);
Ray generate_ray(Scene *scene, int i, int j, int width, int height);
Color trace_ray(Scene *scene, Ray *ray);

#endif // SCENE_H