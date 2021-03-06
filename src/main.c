#include <stdio.h>
#include <stdint.h>
#include "display.h"
#include "vector.h"
#include "array.h"
#include "mesh.h"

triangle_t *triangles_to_render = NULL;

vec3_t camera_position = {0, 0, 0};
vec3_t translate_vector = {0, 0, 5};
bool rotate = true;
float fov_factor = 640.0;

bool isRunning = true;
int previous_frame_time = 0;
void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            isRunning = false;
            break;
        }
        if (event.key.keysym.sym == SDLK_UP)
        {
            translate_vector.z -= 3;
        }
        if (event.key.keysym.sym == SDLK_DOWN)
        {
            translate_vector.z += 3;
        }
        if (event.key.keysym.sym == SDLK_LCTRL)
        {
            rotate = !rotate;
        }
    }
}
void setup(void)
{
    color_buffer = (uint32_t *)malloc(window_width * window_height * sizeof(uint32_t));

    color_buffer_texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             window_width,
                                             window_height);
    //load_cube_mesh_data();
    load_obj_file_data("./src/assets/monkey.obj");
}

vec2_t project(vec3_t point)
{
    vec2_t projected_point = {
        .x = (fov_factor * point.x) / point.z,
        .y = (fov_factor * point.y) / point.z};
    return projected_point;
}

void update(void)
{

    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
    {
        SDL_Delay(time_to_wait);
    }

    triangles_to_render = NULL;

    previous_frame_time = SDL_GetTicks();

    if (rotate == true)
    {
        mesh.rotation.x += 0.005;
        mesh.rotation.y += 0.005;
        mesh.rotation.z += 0.005;
    }

    //Loop all triangles faces of our mesh

    int num_faces = array_length(mesh.faces);
    for (int i = 0; i < num_faces; i++)
    {
        face_t mesh_face = mesh.faces[i];

        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.c - 1];

        vec3_t transformed_vertices[3];
        //Loop all the vertices of the current face and apply the transformations
        for (int j = 0; j < 3; j++)
        {
            vec3_t transformed_vertex = face_vertices[j];

            transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);

            //Translate the vertices away from the camera
            transformed_vertex.z += translate_vector.z;

            //Save transformed vertex in the array of transformed vertices
            transformed_vertices[j] = transformed_vertex;
        }

        //check backface culling
        vec3_t vector_a = transformed_vertices[0];
        vec3_t vector_b = transformed_vertices[1];
        vec3_t vector_c = transformed_vertices[2];

        vec3_t vector_ab = vec3_sub(vector_b, vector_a);
        vec3_t vector_ac = vec3_sub(vector_c, vector_a);

        vec3_t normal = vec3_cross(vector_ab, vector_ac);
        vec3_t camera_ray = vec3_sub(camera_position, vector_a);

        float dot_normal_camera = vec3_dot(camera_ray, normal);

        if (dot_normal_camera < 0)
        {
            continue;
        }

        triangle_t projected_triangle;

        for (int j = 0; j < 3; j++)
        {

            //project the current  vertex
            vec2_t projected_point = project(transformed_vertices[j]);

            // Scale and translate the project points to the middle of the screen
            projected_point.x += (window_width / 2);
            projected_point.y += (window_height / 2);

            projected_triangle.points[j] = projected_point;
        }
        //save the projected triangle in the array of triangles to render
        //triangles_to_render[i] = projected_triangle;
        array_push(triangles_to_render, projected_triangle);
    }

    // for (int i = 0; i < N_POINTS; i++)
    // {
    //     vec3_t point = cube_points[i];

    //     vec3_t transform_point = vec3_rotate_x(point, cube_rotation.x);
    //     transform_point = vec3_rotate_y(transform_point, cube_rotation.y);
    //     transform_point = vec3_rotate_z(transform_point, cube_rotation.z);

    //     transform_point.z -= camera_position.z;

    //     vec2_t projected_point = project(transform_point);

    //     projected_points[i] = projected_point;
    // }
}

void render(void)
{
    draw_grid();

    draw_triangle(50, 100, 75, 400, 500, 550, 0xFF00FF00);

    //draw_line(100, 200, 300, 50, 0xFF00FF00);

    //Loop al projected trianges end render then
    // int num_triangles = array_length(triangles_to_render);
    // for (int i = 0; i < num_triangles; i++)
    // {
    //     triangle_t triangle = triangles_to_render[i];
    //     // draw_rect(triangle.points[0].x,
    //     //           triangle.points[0].y,
    //     //           3,
    //     //           3,
    //     //           0xFFFFFF00);
    //     // draw_rect(triangle.points[1].x,
    //     //           triangle.points[1].y,
    //     //           3,
    //     //           3,
    //     //           0xFFFFFF00);
    //     // draw_rect(triangle.points[2].x,
    //     //           triangle.points[2].y,
    //     //           3,
    //     //           3,
    //     //           0xFFFFFF00);
    //     draw_line(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, 0xFF00FF00);
    //     draw_line(triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, 0xFF00FF00);
    //     draw_line(triangle.points[2].x, triangle.points[2].y, triangle.points[0].x, triangle.points[0].y, 0xFF00FF00);
    // }

    //for drid like points
    // for (int i = 0; i < N_POINTS; i++)
    // {
    //     vec2_t projected_point = projected_points[i];
    //     draw_rect(projected_point.x + (window_width / 2),
    //               projected_point.y + (window_height / 2),
    //               4,
    //               4,
    //               0xFFFFFF00);
    // }

    array_free(triangles_to_render);

    render_color_buffer();

    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

void free_resources(void)
{
    free(color_buffer);
    array_free(mesh.faces);
    array_free(mesh.vertices);
}

int main(void)
{
    isRunning = initialize_window();

    setup();

    while (isRunning)
    {
        process_input();
        update();
        render();
    }

    destroy_window();
    free_resources();
    return 0;
}