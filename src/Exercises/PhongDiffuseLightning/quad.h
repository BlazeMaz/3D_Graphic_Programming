//
// Created by mazur on 11/01/2021.
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
    void draw(glm::mat4 &PVM, GLuint u_pvm_buffer_);
private:
    GLuint vao_;
    GLuint diffuse_texture_;

    std::vector<GLfloat> vertices = {
            -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, //0
            1.0f, 0.0f, -1.0f, 1.0f, 0.0f, //1
            1.0f, 0.0f, 1.0f, 1.0f, 1.0f, //2
            -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, //3 base
    };

    std::vector<GLushort> indices = {
            0,1,2,
            0,2,3,
    };
};

#endif INC_3DGRAPHICSEXAMPLES_QUAD_H
