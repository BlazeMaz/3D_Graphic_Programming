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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    void set_controler(CameraControler *controler) { controler_ = controler; }

    Camera *camera() { return camera_; }

    CameraControler *controler(Camera camera) {return controler_;}

private:
    GLuint vao_;
    GLuint u_pvm_buffer_;

    float fov_;
    float aspect_;
    float near_;
    float far_;

    glm::mat4 P_;
    glm::mat4 V_;
    glm::mat4 M_;

    Camera *camera_;
    CameraControler *controler_;
};