#version 410

uniform mat4 previousViewMat;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform mat4 previousModel;

in vec3 position;
in vec2 texcoord;
in vec3 normal;

smooth out vec4 v_world;
smooth out vec4 v_preposition;
out vec2 v_texcoord;
out vec4 v_normal;
out vec3 v_position;

void main()
{
    v_texcoord = texcoord;
    v_normal = transpose(inverse(view * model)) * vec4(normal, 1.0);
    
    v_position = (view * model * vec4(position, 1.0)).xyz;
    v_world = projection * view * model * vec4(position, 1.0);
    v_preposition = projection * previousViewMat * previousModel * vec4(position, 1.0);
    
    gl_Position = v_world;
}

