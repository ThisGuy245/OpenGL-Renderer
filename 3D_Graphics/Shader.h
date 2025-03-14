#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    ~Shader();

    void use();
    void setUniformMatrix4fv(const std::string& name, const float* matrix);

private:
    GLuint programId;
    GLuint compileShader(GLenum type, const std::string& source);
};

#endif // SHADER_H