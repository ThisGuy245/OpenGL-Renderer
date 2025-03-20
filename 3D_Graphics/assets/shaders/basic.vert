#version 330 core
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 a_Normal;

out vec2 TexCoords;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    TexCoords = texCoord;
    gl_Position = projection * view * model * vec4(a_Pos, 1.0);

    v_Normal = mat3(model) * a_Normal;
    v_FragPos = vec3(model * vec4(a_Pos, 1.0));
}


