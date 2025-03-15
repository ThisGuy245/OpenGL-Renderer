#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <vector>

class Model {
public:
    Model();
    Model(const std::string& _path);
    Model(const Model& _copy);
    Model& operator=(const Model& _assign);
    virtual ~Model();

    void Draw();

    GLsizei vertex_count() const;
    GLuint vao_id();

private:
    struct Vertex {
        Vertex();
        glm::vec3 position;
        glm::vec2 texcoord;
        glm::vec3 normal;
    };

    struct Face {
        Vertex a;
        Vertex b;
        Vertex c;
    };

    std::vector<Face> m_faces;
    GLuint m_vaoid;
    GLuint m_vboid;
    bool m_dirty;

    void split_string_whitespace(const std::string& _input, std::vector<std::string>& _output);
    void split_string(const std::string& _input, char _splitter, std::vector<std::string>& _output);
};

#endif
