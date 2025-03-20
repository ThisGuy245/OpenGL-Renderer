#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;
    void unbind() const; 

    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec3(const std::string& name, const glm::vec3& vec);
    void setMat4(const std::string& name, const glm::mat4& mat);

private:
    GLuint m_programID;
    std::unordered_map<std::string, GLint> m_uniformLocationCache;

    std::string readFile(const std::string& filepath);
    GLuint compileShader(GLenum type, const std::string& source);
    GLint getUniformLocation(const std::string& name);
};

#endif // SHADER_H
