//
// Created by mazur on 11.11.2020.
//

#ifndef INC_3DGRAPHICSEXAMPLES_CAMERA_H
#define INC_3DGRAPHICSEXAMPLES_CAMERA_H

#endif //INC_3DGRAPHICSEXAMPLES_CAMERA_H

#pragma once

#include <cmath>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
class Camera {
public:

    void look_at(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);

    void perspective(float fov, float aspect, float near, float far);

    void set_aspect(float aspect);

    void rotate_around_point(float angle, const glm::vec3 &axis, const glm::vec3 &c);

    void rotate_around_center(float angle, const glm::vec3 &axis);

    glm::mat4 view() const;

    glm::mat4 projection() const;

    glm::vec3 position() const;
    glm::vec3 center() const;
    glm::vec3 x() const;
    glm::vec3 y() const;
    glm::vec3 z() const;

    void zoom(float y_offset);

private:
    float fov_;
    float aspect_;
    float near_;
    float far_;

    //V
    glm::vec3 position_;
    glm::vec3 center_;
    glm::vec3 x_;
    glm::vec3 y_;
    glm::vec3 z_;
};

static float logistic(float y) {
    return 1.0f / (1.0f + std::exp(-y));
}

static float inverse_logistics(float x) {
    return std::log(x / (1.0f - x));
}
