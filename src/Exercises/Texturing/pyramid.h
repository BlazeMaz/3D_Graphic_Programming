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

    void draw(glm::mat4 &PVM, GLuint u_pvm_buffer_);

private:
    GLuint vao_;
    GLuint diffuse_texture_;

    std::vector<GLfloat> vertices = {
            -0.5f, -0.5f, 0.5f, 0.5f, 0.191f, // 0
            0.5f, -0.5f, 0.5f, 0.809f, 0.5f,  // 1
            0.5f, -0.5f, -0.5f, 0.5f, 0.809f, // 2
            -0.5f, -0.5f, -0.5f, 0.191f, 0.5f,  // 3 base
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, // 4
            0.0f, 0.5f, 0.0f, 1.0f, 1.0f, // 5
            0.0f, 0.5f, 0.0f, 0.0f, 1.0f, // 6
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, // 7
    };

    std::vector<GLushort> indices = {
            0, 2, 1,
            0,3,2,
            0, 1, 4,
            1, 2, 5,
            2, 3, 6,
            3, 0, 7,
    };

};

#endif //INC_3DGRAPHICSEXAMPLES_PYRAMID_H
