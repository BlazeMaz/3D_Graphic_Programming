//
// Created by pbialas on 05.08.2020.
//


#pragma once

#include <vector>


#include "Application/application.h"
#include "Application/utils.h"

#include "glad/glad.h"
#include "camera.h"
#include "cameraControler.h"
#include "pyramid.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

class time_point;

class SimpleShapeApplication : public xe::Application {
public:
    SimpleShapeApplication(int width, int height, std::string title, int major = 4, int minor = 1) :
            Application(width, height, title, major, minor) {}

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

    void scroll_callback(double xoffset, double yoffset);

    void mouse_button_callback(int button, int action, int mods);

    void cursor_position_callback(double x, double y);

    void set_camera(Camera *camera) { camera_ = camera; }

    void set_controler(CameraController *controler) { controller_ = controler; }

    Camera *camera() { return camera_; }

    CameraController *controler(Camera camera) {return controller_;}

    Pyramid *pyramid() {return pyramid_;}

private:
    GLuint vao_;
    GLuint ubo_handle_pvm;

    float fov_;
    float aspect_;
    float near_;
    float far_;

    glm::mat4 P_;
    glm::mat4 V_;
    glm::mat4 M_;

    Camera *camera_;
    CameraController *controller_;
    Pyramid *pyramid_;

    std::chrono::steady_clock::time_point start_;
    float rotation_period_;
    float moon_rotation_period_;
    float satelite_rotation_period_;
};