


#version 330 core
layout(location = 0) out vec4 color;

uniform sampler2D shadow;

in vec4 lightview_Position;
void main()
{
//    color = vec4(1,0,0,1);
    color = textureProj(shadow, lightview_Position);
}
