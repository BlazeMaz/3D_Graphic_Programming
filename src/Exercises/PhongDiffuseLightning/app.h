//
// Created by pbialas on 05.08.2020.
//


#pragma once

#include <vector>


#include "Application/application.h"
#include "Application/utils.h"

#include "glad/glad.h"
#include "camera.h"
#include "quad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Light {
    glm::vec4 position;
    glm::vec4 color;
    glm::vec4 a;
};

class SimpleShapeApplication : public xe::Application {
public:
    SimpleShapeApplication(int width, int height, std::string title, int major = 4, int minor = 1) :
            Application(width, height, title, major, minor) {}

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

    void scroll_callback(double xoffset, double yoffset);

    void set_camera(Camera *camera) { camera_ = camera; }

    Camera *camera() { return camera_; }

    Quad *quad() { return quad_; }

private:
    GLuint vao_;
    GLuint u_pvm_buffer_;
    GLuint u_light_buffer_;

    float fov_;
    float aspect_;
    float near_;
    float far_;

    glm::mat4 P_;
    glm::mat4 V_;
    glm::mat4 M_;

    Camera *camera_;
    Quad *quad_;

    Light light_{};
};
