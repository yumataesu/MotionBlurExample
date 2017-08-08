#version 410

uniform sampler2D tex;

smooth in vec4 v_world;
smooth in vec4 v_preworld;
in vec2 v_texcoord;
in vec4 v_normal;


layout (location = 0) out vec4 gAlbedo;
layout (location = 1) out vec4 gVelocity;

void main()
{
    //Compute velocity
    vec2 a = (v_world.xy / v_world.w) * 0.5 + 0.5;
    vec2 b = (v_preworld.xy / v_preworld.w) * 0.5 + 0.5;
    vec2 vel = a - b;
    
    
    vec3 color = textureLod(tex, v_texcoord, 0.0).rgb;

    gAlbedo = vec4(color, 1.0);
    gVelocity = vec4(vel, 0.0, 1.0);
}
