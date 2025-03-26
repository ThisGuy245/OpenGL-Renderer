#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

class Scene {
public:
    Scene(const std::string& name = "Scene");
    ~Scene();

    // Scene management
    void Update(float deltaTime);
    void Render(Shader& shader);

    // GameObject management
    GameObject* CreateGameObject(const std::string& name = "GameObject");
    void DestroyGameObject(GameObject* gameObject);

    // Hierarchy operations
    GameObject* GetRootObject() const { return m_rootObject.get(); }
    const std::vector<GameObject*>& GetAllGameObjects() const { return m_gameObjects; }

    // Find operations
    GameObject* FindGameObjectByName(const std::string& name) const;
    std::vector<GameObject*> FindGameObjectsByTag(const std::string& tag) const;

    // Scene properties
    const std::string& GetName() const { return m_name; }
    void SetName(const std::string& name) { m_name = name; }

    // Serialization
    void SaveToFile(const std::string& filePath);
    void LoadFromFile(const std::string& filePath);

private:
    std::string m_name;
    std::unique_ptr<GameObject> m_rootObject; // Root of the scene hierarchy
    std::vector<GameObject*> m_gameObjects;   // Flat list for easy iteration
    std::unordered_map<std::string, GameObject*> m_nameLookup; // For fast name lookup

    // Private helpers
    void AddGameObject(GameObject* gameObject);
    void RemoveGameObject(GameObject* gameObject);
    void BuildNameLookup();
    void ClearScene();
};

#endif // SCENE_H