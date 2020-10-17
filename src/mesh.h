#pragma once

#include "vector.h"
#include "triangle.h"

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2)

vec3_t cube_vertices[N_CUBE_VERTICES];
face_t cube_faces[N_CUBE_FACES];

//Define a struct for dynamic size meshes
typedef struct
{
    vec3_t *vertices; //dynamic array of vertices
    face_t *faces;    //dynamic array of faces
    vec3_t rotation;  //rotation with x,y and z values
} mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data(void);
void load_obj_file_data(char *filePath);