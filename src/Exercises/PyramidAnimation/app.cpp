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

    //PVM
    auto u_matrices_index = glGetUniformBlockIndex(program, "Matrices");
    if (u_matrices_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Matrices uniform block in program" << std::endl;
    } else { glUniformBlockBinding(program, u_matrices_index, 1); }

    start_ = std::chrono::steady_clock::now();
    rotation_period_ = 4.0f;
    moon_rotation_period_ = 10.0f;
    satelite_rotation_period_ = 2.0f;

    glGenBuffers(1, &ubo_handle_pvm);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, ubo_handle_pvm);

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
    auto rotation_angle = 2.0f * glm::pi<float>() * elapsed_time / rotation_period_;
    glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 R = glm::rotate(M_, rotation_angle, axis);
    glm::mat4 O = glm::translate(M_, {10.0f * cos(rotation_angle), 0.0f, 6.0f * sin(rotation_angle)});

    float r_moon = 3.0f;
    glm::mat4 O_moon = glm::translate(M_, {r_moon * cos(rotation_angle), 0.0f, r_moon * sin(rotation_angle)});
    glm::mat4 Scale_moon = glm::scale(M_, glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 R_moon = glm::rotate(M_, 2.0f * glm::pi<float>() * elapsed_time / moon_rotation_period_, axis);

    float r_satelite = 1.5f;
    glm::vec3 satelite_axis = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::mat4 O_satelite = glm::translate(M_,{r_satelite * cos(rotation_angle), r_satelite * sin(rotation_angle), 0.0f});
    glm::mat4 Scale_satelite = glm::scale(M_, glm::vec3(0.25f, 0.25f, 0.25f));
    glm::mat4 R_satelite = glm::rotate(M_, 2.0f * glm::pi<float>() * elapsed_time / satelite_rotation_period_,
                                       satelite_axis);

    glm::mat4 PVM = camera_->projection() * camera_->view() * O * M_ * R;
    glm::mat4 PVMoon = camera_->projection() * camera_->view() * O * O_moon * Scale_moon * R_moon;
    glm::mat4 PVMSatelite = camera_->projection() * camera_->view() * O * O_satelite * R_satelite * Scale_satelite;

    pyramid_->draw(PVM, ubo_handle_pvm);
    pyramid_->draw(PVMoon, ubo_handle_pvm);
    pyramid_->draw(PVMSatelite, ubo_handle_pvm);
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
