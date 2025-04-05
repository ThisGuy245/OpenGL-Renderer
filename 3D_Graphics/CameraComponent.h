#pragma once
#include "Camera.h"  // Your existing Camera class

struct CameraComponent {
    Camera camera;  // Your existing Camera
    bool isMainCamera = false;  // Mark as the active camera
};