#version 330 core
in vec2 TexCoords;
in vec3 v_Normal;
in vec3 v_FragPos;
uniform sampler2D texture1;

out vec4 fragColor;



void main() {
    vec4 tex = texture(texture1, TexCoords);

    vec3 lightPos = vec3(10, 10, 10);
    vec3 diffuseColor = vec3(1, 1, 1);

    vec3 N = normalize(v_Normal);
    vec3 lightDir = normalize(lightPos - v_FragPos);
    float diff = max(dot(N, lightDir), 0.0);
    vec3 diffuse = diffuseColor * diff;

    vec3 lighting = diffuse;
    fragColor = vec4(lighting, 1) * tex;

}
