#ifndef LIBVEC_H
# define LIBVEC_H

# include <math.h>
# include <stdio.h>

typedef struct 	s_mat4
{
	float		value[4][4];
}				t_mat4;

typedef struct s_vec3i
{
	int		x;
	int		y;
	int		z;
}				t_vec3i;

typedef struct s_vec3f
{
	float	x;
	float	y;
	float	z;
}				t_vec3f;

typedef struct s_vec4f
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_vec4f;

typedef struct s_vec2f
{
	float	x;
	float	y;
}				t_vec2f;


// Vectors Utils
t_vec3f		vec3f_init(void);
t_vec3f		vec_add(t_vec3f u, t_vec3f v);
t_vec3f		vec_sub(t_vec3f u, t_vec3f v);
t_vec3f		vec_cross(t_vec3f u, t_vec3f v);
t_vec3f		vec_multf(t_vec3f u, float f);
t_vec3f		vec_normalize(t_vec3f u);
float		vec_dot(t_vec3f u, t_vec3f v);
float		vec_length(t_vec3f *u);

// Matrices Utils

// matrice.c
t_mat4		m4_init(void);
t_mat4 	    m4_mult(t_mat4 a, t_mat4 b);
t_mat4		m4_mult3(t_mat4 rotation, t_mat4 scale, t_mat4 translate);


t_mat4		m4_rotation(float x, float y, float z);
t_mat4		m4_rotation_around_center(t_vec3f center, float x, float y, float z);
t_mat4		m4_scale(float x, float y, float z);
t_mat4		m4_translate(float x, float y, float z);

t_mat4		m4_perspective(float fov, float aspect, float near, float far);
t_mat4		m4_orthogonal(float nearz, float farz, float left, float right, float bottom, float top);
t_mat4		m4_look_at(t_vec3f from, t_vec3f to, t_vec3f upv);

t_vec3f		m4_mult_vec3f(t_mat4 mat, t_vec3f vec);
t_vec4f		m4_mult_vec4f(t_mat4 mat, t_vec4f vec);

t_mat4		m4_viewmat(float x, float y, float z, t_mat4 translate);
void		m4_print(t_mat4 mat);

#endif