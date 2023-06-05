//og8
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
//layout(location = 2) in vec2 txc;

uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightDirection;
uniform vec3 cameraPos; //might not be needed
uniform mat4 matrixShadow;

out vec3 normalizedLightDirection;
out vec3 halfVector;
out vec4 lightView_Position;
out vec3 normalizedNormal;

void main(){
    vec3 viewNormal = normalMatrix * normal;
    vec3 viewVector = vec3(mv * vec4(pos,1));//viewVector
    normalizedNormal = normalize(viewNormal);
    
//    normalizedLightDirection = vec3(normalize(vec4(lightDirection,0))); // may need this
    normalizedLightDirection = normalize(lightDirection);
    halfVector = normalize(normalizedLightDirection + normalize(-viewVector));

    gl_Position = mvp * vec4(pos,1);
    lightView_Position = matrixShadow * vec4(pos,1);
}
