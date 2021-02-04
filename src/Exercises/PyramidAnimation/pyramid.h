//
// Created by mazur on 20.11.2020.
//

#ifndef INC_3DGRAPHICSEXAMPLES_PYRAMID_H
#define INC_3DGRAPHICSEXAMPLES_PYRAMID_H

#include <glad/glad.h>
#include <vector>
#include <glm/fwd.hpp>

class Pyramid {
public:
    Pyramid();
    ~Pyramid();
    void draw();
private:
    GLuint vao_;
    GLuint buffer_[2];

    std::vector<GLfloat> vertices = {
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, //base

            -0.5f,-0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, // front

            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, // right

            0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, // back

            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, // left
    };

    std::vector<GLushort> indices = {
            0, 1, 2,
            2, 3, 0,
            4, 5, 6,
            7, 8, 9,
            10, 11, 12,
            13, 14, 15
    };
};

#endif //INC_3DGRAPHICSEXAMPLES_PYRAMID_H
