#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
public:
    // Default constructor with initial values for position, rotation, and scale
    Transform()
        : position(glm::vec3(0.0f, 0.0f, 0.0f)),
        rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
        scale(glm::vec3(1.0f, 1.0f, 1.0f)) {}

    // Method to calculate and return the model matrix for this transform
    glm::mat4 GetModelMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);  // Identity matrix
        model = glm::translate(model, position); // Apply translation
        model *= glm::mat4_cast(rotation); // Apply rotation (quaternion)
        model = glm::scale(model, scale);  // Apply scale
        return model;
    }

    // Transform properties
    glm::vec3 position;
    glm::quat rotation;  // Rotation as a quaternion
    glm::vec3 scale;
};

#endif
