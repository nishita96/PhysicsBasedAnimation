#version 410 core
layout(quads, equal_spacing, ccw) in;
uniform sampler2D tex1;
uniform mat4 mvp;

vec4 interpolate( vec4 v0, vec4 v1, vec4 v2, vec4 v3 )
{
   vec4 v1 = mix( v0, v1, gl_TessCoord.x );
   vec4 v2 = mix( v3, v2, gl_TessCoord.x );
    
   return mix( v1, v2, gl_TessCoord.y );
}
void main()
{
    gl_Position = interpolate( gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position, gl_in[3].gl_Position);
    
    vec4 displacement_tex =  texture(tex1, gl_TessCoord.xy);
    gl_Position = mvp * vec4(gl_Position.x, gl_Position.y, gl_Position.z - (displacement_tex.r * 3.0),gl_Position.w);
}

