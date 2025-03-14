// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Player {
public:
    Player();

    void update();
    void move(float deltaTime);
    void scale(float factor);
    void rotate(float angle);

    glm::mat4 getTransform() const;
    glm::vec3 getPosition() const;

private:
    glm::vec3 position;
    float size;  // For scaling
    float rotationAngle;
};

#endif
