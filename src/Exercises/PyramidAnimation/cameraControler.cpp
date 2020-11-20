//
// Created by mazur on 19.11.2020.
//

#include "cameraControler.h"

void CameraController::set_camera(Camera *camera) {
    camera_ = camera;
}

void CameraController::rotate_camera(float dx, float dy) {
    camera_->rotate_around_center(-scale_ * dy, camera_->x());
    camera_->rotate_around_center(-scale_ * dx, glm::vec3{0.0f, 0.0f, 1.0f});
}

void CameraController::mouse_moved(float x, float y) {
    if (LMB_pressed) {
        auto dx = x - x_;
        auto dy = y - y_;
        x_ = x;
        y_ = y;

        rotate_camera(dx, dy);
    }
}

void CameraController::LMB_isPressed(float x, float y) {
    LMB_pressed = true;
    x_ = x;
    y_ = y;
}

void CameraController::LMB_isReleased(float x, float y) {
    LMB_pressed = false;
    auto dx = x - x_;
    auto dy = y - y_;

    rotate_camera(dx, dy);
}
