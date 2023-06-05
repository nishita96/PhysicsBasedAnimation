
//shader.frag similar 
#version 330 core
layout(location =0) out vec4 color;

uniform mat4 mvp;
uniform mat4 mv;
uniform float shine;
uniform vec3 lightDirection;

in vec3 normalizedNormal;
in vec3 normalizedLightDirection;
in vec3 halfVector;
in vec3 reflectionVector;

uniform samplerCube env;

void main()
{
        float cosTheta = max(dot(normalize(normalizedLightDirection), normalize(normalizedNormal)), 0.0);
        float cosPhi = max(dot(normalize(normalizedNormal), normalize(halfVector)), 0.0);

//        vec3 intensity = vec3(1,1,1);
        vec3 diffuse = vec3(vec3(1,1,1) * cosTheta * vec3(0.1,0.1,0.1));
        vec3 specular = vec3(vec3(1,1,1) * pow(cosPhi, shine) * vec3(0.1,0.1,0.1));
        vec3 ambient = vec3( vec3(1,1,1) * vec3(0.1,0.1,0.1));


    vec4 envColor = texture( env, reflectionVector );
    color =  vec4(specular,1) + vec4(ambient,1) + envColor; //vec4(diffuse,1) +

//    color = vec4(clr,1);
}
