#version 410 core
layout(quads, equal_spacing, ccw) in;
uniform sampler2D tex1;
uniform mat4 mvp;
uniform mat4 matrixShadow;

in vec3 normalizedLightDirection_tcs[];
in vec3 halfVector_tcs[];
in vec2 texCoord_tcs[];

out vec3 normalizedLightDirection_tes;
out vec4 lightView_Position_tes;
out vec3 halfVector_tes;
out vec2 texCoord_tes;

vec4 interpolate( vec4 v0, vec4 v1, vec4 v2, vec4 v3 )
{
   vec4 v1 = mix( v0, v1, gl_TessCoord.x );
   vec4 v2 = mix( v3, v2, gl_TessCoord.x );
    
   return mix( v1, v2, gl_TessCoord.y );
}
void main()
{
    vec4 newPos = interpolate( gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position, gl_in[3].gl_Position);
    
    vec4 displacement_tex =  texture(tex1, gl_TessCoord.xy);
    gl_Position = mvp * vec4(newPos.xy,newPos.z - (displacement_tex.r * 3.0),newPos.w); //displacement
    
    normalizedLightDirection_tes = normalizedLightDirection_tcs[0];
    halfVector_tes = halfVector_tcs[0];
    
    texCoord_tes =  gl_TessCoord.xy;
    lightView_Position_tes = matrixShadow * vec4(newPos.xy,newPos.z - (displacement_tex.r * 3.0),newPos.w);
}
