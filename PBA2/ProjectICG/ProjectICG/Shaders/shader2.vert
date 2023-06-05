
//proj6
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

uniform mat4 mvp;
uniform mat4 mv;
uniform mat3 normalMatrix;
uniform vec3 lightDirection;
uniform vec3 camera;
uniform mat3 cameraNormalMatrix; 
uniform mat4 modelPosition;

out vec3 normalizedNormal;
out vec3 normalizedLightDirection;
out vec3 halfVector;
out vec3 reflectionVector;
void main()
{
    vec3 viewNormal = normalMatrix * normal; //ask
    vec3 viewVec = vec3(mv * vec4(pos,1));
    normalizedNormal = normalize(viewNormal);
    normalizedLightDirection = normalize(lightDirection);
    
    vec3 modelLocation = vec3(modelPosition * vec4(pos,1));
    vec3 cameraViewDirection = normalize( camera - modelLocation);
    
    vec3 cameraViewNormal = normalize(cameraNormalMatrix * normal);

    reflectionVector = reflect( -cameraViewDirection, cameraViewNormal);
    
    halfVector = normalize(normalizedLightDirection + normalize(-viewVec));
    gl_Position = mvp * vec4(pos,1);
}
