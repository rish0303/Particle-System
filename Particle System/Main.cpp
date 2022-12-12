#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"Shader.hpp"
#include"VAO.hpp"
#include"VBO.hpp"
#include"EBO.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "OpenGLErrorCheck.hpp"


#pragma once


const int WIDTH = 1200, HEIGHT = 1200;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 1200, 1200);



	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// If the camera moved this function would need to be called again
	glm::vec3 cameraPos(0.0f, 0.0f, 1.0f);
	// Create a view matrix using the camera position
	glm::mat4 view = glm::lookAt(cameraPos, glm::vec3(cameraPos.x, cameraPos.y, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// Create a 2D orthogonal projection matrix
	glm::mat4 projection = glm::ortho(
		cameraPos.x - (WIDTH / 2.0f), cameraPos.x + (WIDTH / 2.0f),
		cameraPos.y - (HEIGHT / 2.0f), cameraPos.y + (HEIGHT / 2.0f)
	);

	// create the scale matrix using the scale value for both X and Y
	glm::mat4 scaleMatrix = glm::scale(glm::vec3(10, 10, 1.0f));
	// create the rotation matrix by translating the rotation degrees into radians
	glm::mat4 rotationMatrix = glm::rotate(glm::radians(0.0f), glm::vec3(0, 0, 1));
	// create a translation matrix from the position
	glm::mat4 translationMatrix = glm::translate(glm::vec3(0, 0, 0));
	// create the transformation matrix by combining all three
	glm::mat4 transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	GLint projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
	GLint viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
	GLint transformLoc = glGetUniformLocation(shaderProgram.ID, "world");

	shaderProgram.Activate();

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	CheckError();

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	CheckError();


	double prevTime = 0.0;
	double crntTime = 0.0;
	double deltaTime;
	unsigned int counter = 0;


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		crntTime = glfwGetTime();
		deltaTime = crntTime - prevTime;
		++counter;
		if (deltaTime >= 1.0 / 30.0)
		{
			std::string FPS = std::to_string((1.0 / deltaTime) * counter);
			std::string ms = std::to_string((deltaTime / counter) * 1000);
			std::string newTitle = "Particle System - " + FPS + " FPS / " + ms + " ms";
			glfwSetWindowTitle(window, newTitle.c_str());
		}

		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		CheckError();

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}