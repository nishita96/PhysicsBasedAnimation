//#version 330 core
//layout(location = 0) in vec3 pos; //the input vertex data is 3D data
//uniform mat4 mvp; //model view projection
//void main(){
//    //gl_Position = vec4(0.03 * pos,1) ;
//    gl_Position = mvp * vec4(pos,1) ; //conversion to canonical view volume
//}

#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex;

uniform mat4 mvp;
uniform mat4 mv;
uniform mat3 normalMatrix;
uniform vec3 lightDirection;

//out vec2 texCoord;
out vec3 normalizedNormal;
out vec3 normalizedLightDirection;
out vec3 halfVector;
void main()
{
    vec3 viewNormal = normalMatrix * normal;
    vec3 viewVec = vec3(mv * vec4(pos,1));
    normalizedNormal = normalize(viewNormal);
    
//    vec3 normalizedView = normalize(-viewVec);
//    normalizedLightDirection = vec3(normalize(vec4(lightDirection,1))) - viewVec; //traps the shine
//    normalizedLightDirection = vec3(normalize(vec4(lightDirection,0)));
    
    normalizedLightDirection = normalize(lightDirection);
    
//    normalizedLightDirection = vec3(normalize(vec4(lightDirection,0)));
//    halfVector = normalize(normalizedLightDir + normalizedView);
    halfVector = normalize(normalizedLightDirection + normalize(-viewVec));
    gl_Position = mvp * vec4(pos,1);
//    texCoord = tex;
}
