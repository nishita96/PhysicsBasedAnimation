//#version 330 core
//layout(location = 0) out vec4 color; //output of frag shader, location = 0 : can have many output images
//void main(){
//    color = vec4(1,0,0,1);
//}
////change this, copy that file in location ()which is done by compile here in Debug folder), and then press F6

#version 330 core
layout(location =0) out vec4 color;

uniform mat4 mvp;
uniform mat4 mv;
uniform float shine;
uniform vec3 lightDirection;
//uniform sampler2D tex;

//in vec2 texCoord;
in vec3 normalizedNormal;
in vec3 normalizedLightDirection;
in vec3 halfVector;
void main()
{
    float cosTheta = max(dot(normalize(normalizedLightDirection), normalize(normalizedNormal)), 0.0);
    float cosPhi = max(dot(normalize(normalizedNormal), normalize(halfVector)), 0.0);
    
    vec3 intensity = vec3(1,1,1);
    vec3 diffuse = vec3(intensity * cosTheta * vec3(1,0,1));
    vec3 specular = vec3(intensity * pow(cosPhi, shine) * vec3(1,1,1));
    vec3 ambient = vec3(intensity * vec3(0.05,0.05,0.05)); //this is diff
    
    vec3 clr = vec3(diffuse + specular + ambient);
    color = vec4(clr,1);
//    color = texture(tex, texCoord);
}
