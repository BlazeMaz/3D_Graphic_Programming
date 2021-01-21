//
// Created by mazur on 20.11.2020.
//

#ifndef INC_3DGRAPHICSEXAMPLES_QUAD_H
#define INC_3DGRAPHICSEXAMPLES_QUAD_H

#include <glad/glad.h>
#include <vector>
#include <glm/fwd.hpp>

class Quad {
public:
    Quad();

    ~Quad();

    void draw();

private:
    GLuint vao_;
    GLuint diffuse_texture_;

    std::vector<GLfloat> vertices = {
            -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 1.0f, 0.0f,0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, -1.0f, 1.0f, 1.0f,0.0f, 1.0f, 0.0f,
            -1.0f, 0.0f, -1.0f, 0.0f, 1.0f,0.0f, 1.0f, 0.0f,
    };

    std::vector<GLushort> indices = {
            0, 1, 2,
            2, 3, 0
    };

};

#endif //INC_3DGRAPHICSEXAMPLES_QUAD_H
