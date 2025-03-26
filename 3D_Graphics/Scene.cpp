#include "Scene.h"
#include "Component.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Log.h"

Scene::Scene(const std::string& name)
    : m_name(name) {
    // Create root object
    m_rootObject = std::make_unique<GameObject>("Root");
    m_gameObjects.push_back(m_rootObject.get());
}

Scene::~Scene() {
    ClearScene();
}

void Scene::Update(float deltaTime) {
    // Update all game objects (breadth-first)
    for (auto& gameObject : m_gameObjects) {
        gameObject->Update(deltaTime);
    }
}

void Scene::Render(Shader& shader) {
    // Render all game objects
    for (auto& gameObject : m_gameObjects) {
        if (gameObject != m_rootObject.get()) { // Skip root object
            gameObject->Render(shader);
        }
    }
}

GameObject* Scene::CreateGameObject(const std::string& name) {
    auto gameObject = new GameObject(name);
    gameObject->SetParent(m_rootObject.get());
    AddGameObject(gameObject);
    return gameObject;
}

void Scene::DestroyGameObject(GameObject* gameObject) {
    if (!gameObject || gameObject == m_rootObject.get()) {
        return; // Can't destroy root or null
    }

    // Remove from parent first
    if (gameObject->GetParent()) {
        gameObject->GetParent()->RemoveChild(gameObject);
    }

    // Destroy all children recursively
    auto children = gameObject->GetChildren();
    for (auto child : children) {
        DestroyGameObject(child);
    }

    RemoveGameObject(gameObject);
    delete gameObject;
}

GameObject* Scene::FindGameObjectByName(const std::string& name) const {
    auto it = m_nameLookup.find(name);
    if (it != m_nameLookup.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<GameObject*> Scene::FindGameObjectsByTag(const std::string& tag) const {
    std::vector<GameObject*> result;
    for (auto gameObject : m_gameObjects) {
        // You'll need to add GetTag()/SetTag() to GameObject
        if (gameObject->GetTag() == tag) {
            result.push_back(gameObject);
        }
    }
    return result;
}

void Scene::SaveToFile(const std::string& filePath) {
    // Basic serialization stub - implement with your preferred format (JSON, binary, etc.)
    std::ofstream file(filePath);
    if (!file.is_open()) {
        Log::error("Failed to save scene to: " + filePath);
        return;
    }

    // TODO: Implement proper serialization
    file << "Scene: " << m_name << "\n";
    file << "GameObjects: " << m_gameObjects.size() << "\n";

    file.close();
}

void Scene::LoadFromFile(const std::string& filePath) {
    // Basic deserialization stub
    std::ifstream file(filePath);
    if (!file.is_open()) {
        Log::error("Failed to load scene from: " + filePath);
        return;
    }

    ClearScene();

    // TODO: Implement proper deserialization
    std::string line;
    while (std::getline(file, line)) {
        // Parse scene data
    }

    file.close();
}

// Private helpers
void Scene::AddGameObject(GameObject* gameObject) {
    m_gameObjects.push_back(gameObject);
    m_nameLookup[gameObject->GetName()] = gameObject;
}

void Scene::RemoveGameObject(GameObject* gameObject) {
    m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), gameObject),
        m_gameObjects.end());
    m_nameLookup.erase(gameObject->GetName());
}

void Scene::BuildNameLookup() {
    m_nameLookup.clear();
    for (auto gameObject : m_gameObjects) {
        m_nameLookup[gameObject->GetName()] = gameObject;
    }
}

void Scene::ClearScene() {
    // Destroy all objects except root
    auto objects = m_gameObjects; // Copy to avoid modification during iteration
    for (auto gameObject : objects) {
        if (gameObject != m_rootObject.get()) {
            DestroyGameObject(gameObject);
        }
    }

    m_gameObjects = { m_rootObject.get() };
    m_nameLookup = { {m_rootObject->GetName(), m_rootObject.get()} };
}