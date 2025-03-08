#version 120

attribute vec3 a_position;
attribute vec3 a_normal;

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_projection_matrix;

varying vec4 v_position;
varying vec4 v_normal;

void main(void)
{
	vec4 position = vec4(a_position.x, a_position.y, a_position.z, 1.0);
	vec4 normal = vec4(a_normal.x, a_normal.y, a_normal.z, 0.0);

	v_position = u_model_matrix * position;
	v_normal = normalize(u_model_matrix * normal);

	gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * position;
}