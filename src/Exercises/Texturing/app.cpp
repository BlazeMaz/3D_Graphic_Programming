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

    pyramid_ = new Pyramid();

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
    } else { glUniformBlockBinding(program, u_matrices_index, 1); }

    glGenBuffers(1, &u_pvm_buffer_);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, u_pvm_buffer_);

    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glFrontFace(GL_CW);
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
    glm::mat4 PVM = camera_->projection() * camera_->view() * M_;
    pyramid_->draw(PVM, u_pvm_buffer_);
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
