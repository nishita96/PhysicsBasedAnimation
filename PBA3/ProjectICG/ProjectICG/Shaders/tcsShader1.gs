#version 410 core
layout(vertices = 4) out;
uniform int tesLevel;

void main(void)
{
    gl_TessLevelOuter[0] = tesLevel;
    gl_TessLevelOuter[1] = tesLevel;
    gl_TessLevelOuter[2] = tesLevel;
    gl_TessLevelOuter[3] = tesLevel;
    gl_TessLevelInner[0] = tesLevel;
    gl_TessLevelInner[1] = tesLevel;
    
   gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}

