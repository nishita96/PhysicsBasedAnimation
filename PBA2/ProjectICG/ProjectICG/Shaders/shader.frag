//og8
#version 330 core
layout(location = 0) out vec4 color;
uniform mat4 mvp;
uniform mat4 mv;
uniform mat3 normalMatrix;
uniform vec3 itemColour;
in vec3 normalizedLightDirection;
in vec3 halfVector;
in vec3 normalizedNormal;

uniform vec3 lightDirection;
uniform float shine;
in vec2 texCoord_tes;
uniform sampler2D tex0;
uniform sampler2DShadow shadow;
in vec4 lightView_Position;
void main()
{
   float cosTheta = max(dot(normalize(normalizedLightDirection), normalize(normalizedNormal)), 0.0);
   float cosPhi = max(dot(normalize(normalizedNormal), normalize(halfVector)), 0.0);
   float specular = pow(cosPhi, shine);
   vec3 intensity = vec3(1,1,1);
   vec3 p = lightView_Position.xyz / lightView_Position.w;
    
    vec3 diffuseColor = vec3(intensity * cosTheta * vec3(0.5,0.5,0.5));
    vec3 ambientColor = itemColour;
    vec3 specularColor = vec3(intensity * specular * vec3(1,1,1));
    
    vec3 clr = vec3(diffuseColor + specularColor + ambientColor);
    color = vec4(clr,1);
}
