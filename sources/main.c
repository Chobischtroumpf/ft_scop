#include "scop.h"

void drop_callback(GLFWwindow *window, int count, const char **paths)
{
	(void)window;
	(void)count;
	//check if file dropped is a .obj file
	if (ft_strstr(paths[0], ".ppm") != NULL || ft_strstr(paths[0], ".PPM") != NULL)
	{
		//load the file
		t_ppm_img *img = load_PPM(paths[0]);
		//check if the file was loaded
		if (img == NULL)
		{
			printf("Error: Could not load image, exiting.\n");
			return ;
		}
	}
}

void processInput(GLFWwindow *window, scop_t *context)
{
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	//object selection
	{
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && context->amount_objects > 0){
			context->working_object = 0;
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && context->amount_objects > 1){
			context->working_object = 1;
		}
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && context->amount_objects > 2){
			context->working_object = 2;
		}
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && context->amount_objects > 3){
			context->working_object = 3;
		}
		if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && context->amount_objects > 4){
			context->working_object = 4;
		}
		if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && context->amount_objects > 5){
			context->working_object = 5;
		}
		if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && context->amount_objects > 6){
			context->working_object = 6;
		}
		if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && context->amount_objects > 7){
			context->working_object = 7;
		}
		if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS && context->amount_objects > 8){
			context->working_object = 8;
		}
		if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS && context->amount_objects > 9){
			context->working_object = 9;
		}
	}

	//object manipulation
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			context->objects[context->working_object]->should_rotate = 1;
		if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
			context->objects[context->working_object]->should_rotate = 0;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS  || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
			context->objects[context->working_object]->translation_vector.x += 0.005;
			context->objects[context->working_object]->center_vector.x += 0.005;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
			context->objects[context->working_object]->translation_vector.x -= 0.005;
			context->objects[context->working_object]->center_vector.x -= 0.005;
			}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
			context->objects[context->working_object]->translation_vector.y += 0.005;
			context->objects[context->working_object]->center_vector.y += 0.005;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
			context->objects[context->working_object]->translation_vector.y -= 0.005;
			context->objects[context->working_object]->center_vector.y -= 0.005;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && context->objects[context->working_object]->translation_vector.z < 2.0){
			context->objects[context->working_object]->translation_vector.z += 0.005;
			context->objects[context->working_object]->center_vector.z += 0.005;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && context->objects[context->working_object]->translation_vector.z > -2.0){
			context->objects[context->working_object]->translation_vector.z -= 0.005;
			context->objects[context->working_object]->center_vector.z -= 0.005;
		}
	}
}

void set_window_framebuffer(GLFWwindow *window, int width, int height)
{
	(void)window;
	printf("monitor width = %d\n monitor height = %d\n", width, height);
	glViewport(0, 0, width, height);
}

int	init_context(scop_t *context, char **obj, int argc)
{
	int i = 2;

	// glfw: initialize and configure
	if (!glfwInit())
	{
		printf("glfwInit failed\n");
		return (0);
	}
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// glfw window creation
	context->primary = glfwGetPrimaryMonitor();
	context->video_mode = glfwGetVideoMode(context->primary);
	
	// allocating memory for object filenames
	if (!(context->obj = (char **)malloc(sizeof(char*) * (argc-1)))){
		printf("malloc failed\n");
		exit(-1);
	}

	// getting texture path
	context->tex_path = ft_strdup(obj[1]);
	// copying object filenames
	while (i < argc)
	{
		if (!(context->obj[i-1] = ft_strdup(obj[i])))
		{
			printf("strdup failed\n");
			exit(-1);
		}
		i++;
	}
	
	context->amount_objects = i - 1;

	// allocating memory for objects and their data
	if (!(context->objects = (object_t**)calloc(context->amount_objects, sizeof(object_t*)))){
		printf("calloc 1 failed\n");
		exit(-1);
	}
	i = 0;
		context->shader_program = 0;
	while( i < context->amount_objects)
	{
		if (!(context->objects[i] = (object_t*)calloc(1, sizeof(object_t)))){
			printf("calloc 2 failed\n");
			exit(-1);
		}
		// setting default values
		context->objects[i]->angle_in_radians = 0.0f;
		context->objects[i]->delta = 0.002f;
		context->objects[i]->vertices = NULL;
		context->objects[i]->amount_faces = 0;
		context->objects[i]->amount_coordinates = 0;
		context->objects[i]->should_rotate = 1;
		context->objects[i]->VBO = 0;
		context->objects[i]->EBO = 0;
		context->objects[i]->VAO = 0;
		context->objects[i]->translation_vector = vec3f_init();
		context->objects[i]->center_vector = vec3f_init();
		context->objects[i]->rotation_vector = vec3f_init();
		context->objects[i]->rotation_matrice = m4_init();
		context->objects[i]->color_matrice = m4_init();
		context->objects[i]->lighting_matrice = m4_init();
		i++;
	}
	return (1); 
}

int load_image(scop_t *context)
{
	// load image
	context->texture = load_PPM(context->tex_path);
	if (!context->texture)
	{
		printf("load_PPM failed\n");
		return (0);
	}
	// generate texture
	for (int i = 0; i < context->amount_objects; i++)
	{
		glGenTextures(1, &context->objects[i]->texture);
		glBindTexture(GL_TEXTURE_2D, context->objects[i]->texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, context->texture->width, context->texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, (float*)context->texture->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	return (0);
}

void main_loop(scop_t *context)
{
	while (!glfwWindowShouldClose(context->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.8, 0.8, 0.8, 1.0f);
		for (int i = 0; i < context->amount_objects; i++)
		{
			glfwPollEvents();
			processInput(context->window, context);
			/* Render here */
			// coloring(context);
			glUseProgram(context->shader_program);
			update_buffers(context);
			glBindVertexArray(context->objects[i]->VAO);
			glDrawElements(GL_TRIANGLES, context->objects[i]->amount_faces, GL_UNSIGNED_INT, 0);
			/* Swap front and back buffers */
			glfwSwapBuffers(context->window);
			if (context->objects[i]->should_rotate)
			{
				// make rotation matrice
				context->objects[i]->angle_in_radians += context->objects[i]->delta; // adds the Δangle to angle, in radians
				if (context->objects[i]->angle_in_radians >= 2 * PI) // if angle is greater than 2π, reset it to 0
					context->objects[i]->angle_in_radians = 0.0f;
				// sets the rotation matrice to the angle it will have to rotate by
				context->objects[i]->rotation_matrice.value[0][0] = cosf(context->objects[i]->angle_in_radians); 
				context->objects[i]->rotation_matrice.value[0][2] = -sinf(context->objects[i]->angle_in_radians);
				context->objects[i]->rotation_matrice.value[1][1] = 1.0f;
				context->objects[i]->rotation_matrice.value[2][0] = sinf(context->objects[i]->angle_in_radians);
				context->objects[i]->rotation_matrice.value[2][2] = cosf(context->objects[i]->angle_in_radians);
				context->objects[i]->rotation_matrice.value[3][3] = 1.0f;
			}

			// add translation vector to rotation matrice
			context->objects[i]->rotation_matrice.value[3][0] = context->objects[i]->translation_vector.x;
			context->objects[i]->rotation_matrice.value[3][1] = context->objects[i]->translation_vector.y;
			context->objects[i]->rotation_matrice.value[3][2] = context->objects[i]->translation_vector.z;

			// send rotation matrice to shader
			int rotation = glGetUniformLocation(context->shader_program, "rotation");
			glUniformMatrix4fv(rotation, 1, GL_FALSE,
				(float *)context->objects[i]->rotation_matrice.value);
		}
		usleep(1700);
	}
}

int main(int argc, char **argv)
{
	scop_t *context;

	context = ft_get_context();
	if (argc >= 3)
	{
		// initializing context
		if (!init_context(context, argv, argc))
			return (0);
		// parsing files
		if (parse_files(context) < 0)
			return (1);
		context->window = glfwCreateWindow(WIDTH, HEIGHT, "Scop", NULL, NULL);
		if (!context->window){
			glfwTerminate();
			return (2);
		}
		load_image(context);
		glfwMakeContextCurrent(context->window);
		#ifdef __linux__
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
			printf("Failed to initialize OpenGL context\n");
			return -1;
		}
		#endif
		set_window_framebuffer(context->window, context->video_mode->width, context->video_mode->height);
		glfwSetFramebufferSizeCallback(context->window, set_window_framebuffer);
		glfwSetDropCallback(context->window, drop_callback);
		if (compile_shader_progs(context) < 0){
			printf("compile_shader_progs failed\n");
			exit(-1);
		}
		create_buffers(context->objects);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		main_loop(context);
		
		for (int i = 0; i < context->amount_objects; i++)
		{
			glDeleteVertexArrays(1, &(context->objects[i]->VAO));
			glDeleteBuffers(1, &(context->objects[i]->VBO));
			glDeleteBuffers(1, &(context->objects[i]->EBO));
		}
		glDeleteProgram(context->shader_program);
		glfwTerminate();
		printf("end of loop\n");
		exit(0);
		return 0;
	}
	else
		write(1, "wrong amount of arguments to the program:\n\tusage: ./scop [texture.ppm] [*.obj]\n", 79);
}
