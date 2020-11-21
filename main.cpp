#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLWindow.h"
#include "Mesh.h"
#include "Shader.h"

using namespace std;

const float toRadians = 3.141592654f / 180.0f;

// vertex and fragement shader filenames
const char* pVSFilename ="Shaders/vertex.shr";
const char* pFSFilename = "Shaders/fragment.shr";

Mesh mesh;

void createObject()
{
	unsigned int indices[] {
		0, 1, 2,
		1, 2, 3,
		4, 5, 6,
		4, 7, 5,
		8, 9, 10,
		8, 11, 9,
		12, 13, 14,
		13, 14, 15,
		16, 17, 18,
		16, 18, 19,
		20, 21, 22,
		20, 22, 23
	};


	GLfloat vertices[] = {
	//	   x      y     z               r     g     b     
		-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 0.0f,	//	0
		-1.0f, -1.0f, -1.0f,		1.0f, 0.0f, 0.0f,	//	1
		1.0f, -1.0f, 1.0f, 		1.0f, 0.0f, 0.0f,	//	2
		1.0f, -1.0f, -1.0f,		1.0f, 0.0f, 0.0f,	//	3
		
		-1.0f, -1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	//	4
		-1.0f, 1.0f, 1.0f, 		0.0f, 1.0f, 0.0f,	//	5
		-1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 0.0f,	//	6
		-1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	//	7

		1.0f, -1.0f, -1.0f,		1.0f, 0.83f, 0.0f,	//	8
		1.0f, 1.0f, 1.0f, 		1.0f, 0.83f, 0.0f,	//	9
		1.0f, -1.0f, 1.0f,		1.0f, 0.83f, 0.0f,	//	10
		1.0f, 1.0f, -1.0f,		1.0f, 0.83f, 0.0f,	//	11
		
		-1.0f, 1.0f, 1.0f,		1.0f, 0.0f, 0.6f,	//	12
		-1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.6f,	//	13
		1.0f, 1.0f, 1.0f,		1.0f, 0.0f, 0.6f,	//	14
		1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.6f,	//	15
		
		-1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 1.0f,	//	16
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 1.0f,	//	17
		1.0f, 1.0f, -1.0f,		0.0f, 0.0f, 1.0f,	//	18
		-1.0f, 1.0f, -1.0f,		0.0f, 0.0f, 1.0f,	//	19
		
		-1.0f, -1.0f, 1.0f,		1.0f, 0.36, 0.07f,	//	20
		1.0f, -1.0f, 1.0f,		1.0f, 0.36, 0.07f,	//	21
		1.0f, 1.0f, 1.0f,		1.0f, 0.36, 0.07f,	//	22
		-1.0f, 1.0f, 1.0f,		1.0f, 0.36, 0.07f	//	23
	};
	
	unsigned int verticesSize = sizeof(vertices) / sizeof(vertices[0]);	
	unsigned int indicesSize = sizeof(indices) / sizeof(indices[0]);
	
	mesh = Mesh();
	mesh.createMesh(vertices, verticesSize, indices, indicesSize);	
}


int main()
{
	float rotateAngle = 0.0f; // rotation for cube will be changed later

	GLWindow theWindow = GLWindow(1024,768, "Simon's Window");
	theWindow.init();
   	theWindow.openWindow();
	//theWindow.openFullscreen();	I am not currently using this but its here for info
		
	createObject();
	Shader shader = Shader();
	shader.compileShader(pVSFilename, pFSFilename);
	
	GLuint uniformProjection = 0, uniformModel = 0;
	
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, 100.0f);
	
	// loop until window closed
	while(!theWindow.getShouldClose())
	{
		// get and handle user input events
		theWindow.pollEvents();
		
		rotateAngle += 0.01f;
		if (rotateAngle >= 360)
		{
			rotateAngle -= 360;
		}
		
		// clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader.useShaderProgramme();
		uniformModel = shader.getModelLocation();
		uniformProjection = shader.getProjectionLocation();
		
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::rotate(model, rotateAngle * toRadians, glm::vec3(1.0f, 1.0f, 1.0f)); 
		// imagine a poll stretching out in the x, y, and z direction then rotate spin around that poll.
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		
		mesh.drawMesh();
		shader.clearShaderProgramme();
		theWindow.swapBuffers();
	}
	
	return 0;
}
