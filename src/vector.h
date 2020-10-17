#pragma once

typedef struct
{
    float x;
    float y;
} vec2_t;

typedef struct
{
    float x;
    float y;
    float z;
} vec3_t;

vec3_t vec3_rotate_x(vec3_t v, float angle);
vec3_t vec3_rotate_y(vec3_t v, float angle);
vec3_t vec3_rotate_z(vec3_t v, float angle);

vec2_t vec2_add(vec2_t vectorA, vec2_t vectorB);
vec3_t vec3_add(vec3_t vectorA, vec3_t vectorB);

vec2_t vec2_sub(vec2_t vectorA, vec2_t vectorB);
vec3_t vec3_sub(vec3_t vectorA, vec3_t vectorB);

vec2_t vec2_mult(vec2_t vectorA, float scalar);
vec3_t vec3_mult(vec3_t vectorA, float scalar);

vec2_t vec2_div(vec2_t vectorA, float scalar);
vec3_t vec3_div(vec3_t vectorA, float scalar);

vec3_t vec3_cross(vec3_t vectorA, vec3_t vectorB);

float vec2_dot(vec2_t vectorA, vec2_t vectorB);
float vec3_dot(vec3_t vectorA, vec3_t vectorB);

vec2_t vec2_normalize(vec2_t vector);
vec3_t vec3_normalize(vec3_t vector);

float vec2_length(vec2_t vector);
float vec3_length(vec3_t vector);
