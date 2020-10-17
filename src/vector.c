#include <math.h>
#include "vector.h"

//Vector addtion
vec2_t vec2_add(vec2_t vectorA, vec2_t vectorB)
{
    vec2_t add = {vectorA.x + vectorB.x, vectorA.y + vectorB.y};
    return add;
}

vec3_t vec3_add(vec3_t vectorA, vec3_t vectorB)
{
    vec3_t add = {vectorA.x + vectorB.x, vectorA.y + vectorB.y, vectorA.z + vectorB.z};
    return add;
}

//Vector Subtraction
vec2_t vec2_sub(vec2_t vectorA, vec2_t vectorB)
{
    vec2_t sub = {vectorA.x - vectorB.x, vectorA.y - vectorB.y};
    return sub;
}

vec3_t vec3_sub(vec3_t vectorA, vec3_t vectorB)
{
    vec3_t sub = {vectorA.x - vectorB.x, vectorA.y - vectorB.y, vectorA.z - vectorB.z};
    return sub;
}

//Vector Multiplication
vec2_t vec2_mult(vec2_t vectorA, float scalar)
{
    vec2_t mult = {vectorA.x * scalar, vectorA.y * scalar};
    return mult;
}

vec3_t vec3_mult(vec3_t vectorA, float scalar)
{
    vec3_t mult = {vectorA.x * scalar, vectorA.y * scalar, vectorA.z * scalar};
    return mult;
}

//Vector Division
vec2_t vec2_div(vec2_t vectorA, float scalar)
{
    vec2_t div = {vectorA.x / scalar, vectorA.y / scalar};
    return div;
}

vec3_t vec3_div(vec3_t vectorA, float scalar)
{
    vec3_t div = {vectorA.x / scalar, vectorA.y / scalar, vectorA.z / scalar};
    return div;
}

//Vector Normalization
vec2_t vec2_normalize(vec2_t vector)
{
    float mag = vec2_length(vector);
    vec2_t normalized = {vector.x / mag, vector.y / mag};
    return normalized;
}

vec3_t vec3_normalize(vec3_t vector)
{
    float mag = vec3_length(vector);
    vec3_t normalized = {vector.x / mag, vector.y / mag, vector.z / mag};
    return normalized;
}

//Vector cross product / normal
vec3_t vec3_cross(vec3_t vectorA, vec3_t vectorB)
{
    vec3_t cross = {
        vectorA.y * vectorB.z - vectorA.z * vectorB.y,
        vectorA.z * vectorB.x - vectorA.x * vectorB.z,
        vectorA.x * vectorB.y - vectorA.y * vectorB.x,
    };
    return cross;
}

//Vector dot product
float vec3_dot(vec3_t vectorA, vec3_t vectorB)
{
    return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z;
}

float vec2_dot(vec2_t vectorA, vec2_t vectorB)
{
    return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

//Vector Magnitude
float vec2_length(vec2_t vector)
{
    return sqrt((vector.x * vector.x + vector.y * vector.y));
}

float vec3_length(vec3_t vector)
{
    return sqrt((vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}

vec3_t vec3_rotate_x(vec3_t v, float angle)
{
    float co = cos(angle);
    float si = sin(angle);
    vec3_t rotated_vector = {
        .x = v.x,
        .y = v.y * co - v.z * si,
        .z = v.y * si + v.z * co};
    return rotated_vector;
}
vec3_t vec3_rotate_y(vec3_t v, float angle)
{
    float co = cos(angle);
    float si = sin(angle);
    vec3_t rotated_vector = {
        .x = v.x * co - v.z * si,
        .y = v.y,
        .z = v.x * si + v.z * co};
    return rotated_vector;
}
vec3_t vec3_rotate_z(vec3_t v, float angle)
{
    float co = cos(angle);
    float si = sin(angle);
    vec3_t rotated_vector = {
        .x = v.x * co - v.y * si,
        .y = v.x * si + v.y * co,
        .z = v.z};
    return rotated_vector;
}