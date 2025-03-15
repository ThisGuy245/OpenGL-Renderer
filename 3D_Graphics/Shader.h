#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader {
private:
    GLuint m_programID;
    std::unordered_map<std::string, GLint> m_uniformLocationCache;

    GLint getUniformLocation(const std::string& name);
    std::string readFile(const std::string& filepath);
    GLuint compileShader(GLenum type, const std::string& source);

public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec3(const std::string& name, const glm::vec3& vec);
    void setMat4(const std::string& name, const glm::mat4& mat);
};

#endif // SHADER_H
