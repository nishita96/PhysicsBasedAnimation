
#version 410 core
layout(vertices = 4) out;
uniform int tesLevel;

in vec3 normalizedLightDirection[];
in vec4 lightView_Position[];
in vec3 halfVector[];
in vec2 texCoord[];

out vec3 normalizedLightDirection_tcs[];
out vec3 halfVector_tcs[];
void main(void)
{
   gl_TessLevelOuter[0] = tesLevel;
   gl_TessLevelOuter[1] = tesLevel;
   gl_TessLevelOuter[2] = tesLevel;
   gl_TessLevelOuter[3] = tesLevel;
   gl_TessLevelInner[0] = tesLevel;
   gl_TessLevelInner[1] = tesLevel;
    
   gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    
   normalizedLightDirection_tcs[gl_InvocationID] = normalizedLightDirection[gl_InvocationID];
   halfVector_tcs[gl_InvocationID] = halfVector[gl_InvocationID];

}

