#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
public:
    Transform()
        : position(glm::vec3(0.0f, 0.0f, 0.0f)),
        rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
        scale(glm::vec3(1.0f, 1.0f, 1.0f)) {}

    glm::mat4 GetModelMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model *= glm::mat4_cast(rotation);
        model = glm::scale(model, scale); 
        return model;
    }
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
};

#endif
