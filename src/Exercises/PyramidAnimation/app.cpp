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
    set_controler(new CameraController(camera));

    pyramid_ = new Pyramid();

    int w, h;
    std::tie(w, h) = frame_buffer_size();
    aspect_ = (float) w / h;
    fov_ = glm::pi<float>() / 4.0;
    near_ = 0.1f;
    far_ = 100.0f;
    camera_->perspective(fov_, aspect_, near_, far_); //P
    camera_->look_at(glm::vec3(0.0f, 25.0f, 0.1f),
                     glm::vec3(0.0f, 0.0f, 0.0f),
                     glm::vec3(0.0f, 1.0f, 0.0f)); //V
    M_ = glm::mat4(1.0f);

    glGenBuffers(1, &u_pvm_buffer_);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, u_pvm_buffer_);
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer_);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 1);

    //PVM
    auto u_matrices_index = glGetUniformBlockIndex(program, "Matrices");
    if (u_matrices_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Matrices uniform block in program" << std::endl;
    } else { glUniformBlockBinding(program, u_matrices_index, 1); }

    start_ = std::chrono::steady_clock::now();
    rotation_period_ = 4.0f;
    earth_rotation_period_ = 20.0f;
    moon_rotation_period_ = 10.0f;
    satellite_rotation_period_ = 2.0f;

    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glUseProgram(program);
}

void SimpleShapeApplication::frame() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<float>>(now - start_).count();

    glm::mat4 R_earth = get_self_rotation(elapsed_time, rotation_period_);
    glm::mat4 O_earth = glm::translate(M_, {10.0f * cos(get_rotation_angle(elapsed_time, earth_rotation_period_)),
                                            0.0f,
                                            8.0f * sin(get_rotation_angle(elapsed_time, earth_rotation_period_))});
    glm::mat4 PVM = camera_->projection() * camera_->view() * O_earth * R_earth * M_;

    glm::mat4 S_moon = glm::scale(M_, glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 R_moon = get_self_rotation(elapsed_time, -moon_rotation_period_);
    glm::mat4 O_moon = glm::translate(M_, {3.0f * cos(get_rotation_angle(elapsed_time, moon_rotation_period_)),
                                           0.0f,
                                           3.0f * sin(get_rotation_angle(elapsed_time, moon_rotation_period_))});
    glm::mat4 PVM_moon = camera_->projection() * camera_->view() * O_earth * O_moon * R_moon * S_moon;

    glm::mat4 S_satellite = glm::scale(M_, glm::vec3(0.25f, 0.25f, 0.25f));
    glm::mat4 R_satellite = get_self_rotation(elapsed_time, satellite_rotation_period_);
    glm::mat4 O_satellite = glm::translate(M_, {1.5 * cos(get_rotation_angle(elapsed_time, satellite_rotation_period_)),
                                                1.5 * sin(get_rotation_angle(elapsed_time, satellite_rotation_period_)),
                                                0.0f});
    glm::mat4 PVM_satellite = camera_->projection() * camera_->view() * O_earth * O_satellite * R_satellite * S_satellite;

    drawPyramid(PVM);
    drawPyramid(PVM_moon);
    drawPyramid(PVM_satellite);
}

float SimpleShapeApplication::get_rotation_angle(float elapsed_time, float rotation_period) {
    return 2.0f * glm::pi<float>() * elapsed_time / rotation_period;
}

glm::mat4 SimpleShapeApplication::get_self_rotation(float elapsed_time, float rotation_period) {
    return glm::rotate(M_, get_rotation_angle(elapsed_time, rotation_period), axisY_);
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

void SimpleShapeApplication::mouse_button_callback(int button, int action, int mods) {
    Application::mouse_button_callback(button, action, mods);

    if (controller_) {
        double x, y;
        glfwGetCursorPos(window_, &x, &y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            controller_->LMB_isPressed(x, y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            controller_->LMB_isReleased(x, y);
    }

}

void SimpleShapeApplication::cursor_position_callback(double x, double y) {
    Application::cursor_position_callback(x, y);
    if (controller_) {
        controller_->mouse_moved(x, y);
    }
}

void SimpleShapeApplication::drawPyramid(glm::mat4 PVM){
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &PVM);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    pyramid_->draw();
}
