#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Model.h"
#include "Texture.h"
#include <memory>
#include <string>

class Player : public GameObject {
public:
    Player(const std::string& modelPath, const std::string& texturePath);

    void Move(const glm::vec3& direction);
    void Rotate(float angle, const glm::vec3& axis);
    void SetScale(const glm::vec3& newScale);

    void Update();

private:
    std::unique_ptr<Model> m_model;
    std::unique_ptr<Texture> m_texture;
};

#endif // PLAYER_H