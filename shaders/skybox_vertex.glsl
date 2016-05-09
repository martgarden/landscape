#version 330

in vec3 position;

uniform mat4 pv_matrix;

out vec3 VS_tex_coord_ws;

void main()
{
    vec3 scale = vec3(500.0, 500.0, 500.0);
    VS_tex_coord_ws = position;
    gl_Position = pv_matrix * vec4((scale * position), 1.0);
}
