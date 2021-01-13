//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void SimpleShapeApplication::init() {
    auto program = xe::create_program(std::string(PROJECT_DIR) + "/shaders/base_vs.glsl",
                                      std::string(PROJECT_DIR) + "/shaders/base_fs.glsl");

    if (!program) {
        std::cerr << "Cannot create program from " << std::string(PROJECT_DIR) + "/shaders/base_vs.glsl" << " and ";
        std::cerr << std::string(PROJECT_DIR) + "/shaders/base_fs.glsl" << " shader files" << std::endl;
    }

    auto *camera = new Camera();
    set_camera(camera);

    quad_ = new Quad();

    int w, h;
    std::tie(w, h) = frame_buffer_size();
    aspect_ = (float) w / h;
    fov_ = glm::pi<float>() / 4.0;
    near_ = 0.1f;
    far_ = 100.0f;
    camera_->perspective(fov_, aspect_, near_, far_); //P
    camera_->look_at(glm::vec3(0.5f, 2.8f, 1.5f),
                     glm::vec3(0.0f, 0.0f, 0.0f),
                     glm::vec3(0.0f, 1.0f, 0.0f)); //V
    M_ = glm::mat4(1.0f);

    //PVM
    auto u_matrices_index = glGetUniformBlockIndex(program, "Matrices");
    if (u_matrices_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Matrices uniform block in program" << std::endl;
    } else { glUniformBlockBinding(program, u_matrices_index, 0); }

    glGenBuffers(1, &u_pvm_buffer_);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, u_pvm_buffer_);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + 3 * sizeof(glm::vec4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, u_pvm_buffer_);

    //Light
    light_.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    light_.a = glm::vec4(1.0f, 0.0f, 1.0f, 0.0f);

    //Light buffor
    auto u_light_index = glGetUniformBlockIndex(program, "Light");
    if (u_light_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Matrices uniform block in program" << std::endl;
    } else { glUniformBlockBinding(program, u_light_index, 2); }

    glGenBuffers(1, &u_light_buffer_);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, u_light_buffer_);
    glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec4) + sizeof(glm::vec3), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, u_light_buffer_);


    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glUseProgram(program);

    auto  u_diffuse_map_location = glGetUniformLocation(program,"diffuse_map");
    if(u_diffuse_map_location==-1) {
        std::cerr<<"Cannot find uniform diffuse_map\n";
    } else {
        glUniform1ui(u_diffuse_map_location,0);
    }
}

void SimpleShapeApplication::frame() {
    glm::mat4 P = camera_->projection();
    glm::mat4 VM = camera_->view()*M_;
    glm::mat4 N = glm::transpose((glm::inverse(glm::mat3(VM))));

    light_.position = VM * glm::vec4 (0.0f, 0.5f, 0.0f, 1.0f);

    quad_->draw(P,VM,N, u_pvm_buffer_);


}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0, 0, w, h);
    camera_->set_aspect((float) w / (float) h);
}

void SimpleShapeApplication::scroll_callback(double xoffset, double yoffset) {
    Application::scroll_callback(xoffset, yoffset);
    camera()->zoom(yoffset / 10.0f);
}
