//
// Created by mazur on 19.11.2020.
//

#ifndef INC_3DGRAPHICSEXAMPLES_CAMERACONTROLER_H
#define INC_3DGRAPHICSEXAMPLES_CAMERACONTROLER_H


#include "camera.h"

class CameraController {
public:

    CameraController(Camera *camera) : camera_(camera),
                                       scale_(0.01f),
                                       LMB_pressed(false) {}

    void set_camera(Camera *camera);

    void rotate_camera(float dx, float dy);

    void mouse_moved(float x, float y);

    void LMB_isPressed(float x, float y);

    void LMB_isReleased(float x, float y);

private:
    Camera *camera_;
    float scale_;
    float x_;
    float y_;

    bool LMB_pressed;
};

#endif //INC_3DGRAPHICSEXAMPLES_CAMERACONTROLER_H
