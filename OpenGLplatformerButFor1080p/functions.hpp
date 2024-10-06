#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <iostream>

//______________________________________________________________________________________________________________________VARIABLES+ OTHERS

extern GLint falling;
extern GLfloat squareSize;
extern GLuint VAO, VBO, shader, blackShaderProgram, lavaShaderProgram;
extern GLfloat squareSize;
extern glm::vec2 pos;
extern glm::vec2 vel;
extern glm::vec2 LastVal;

// Vertex Shader code
static const char* vShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 pos;											  \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = vec4(pos.x / 1.92, pos.y / 1.08, pos.z, 1.0);			      \n\
}";

// Fragment Shader
static const char* fShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 colour;                                                              \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);                                        \n\
}";
// Black Fragment Shader
static const char* blackShader = "                                            \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 colour;                                                              \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(0.0, 0.0, 0.0, 1.0);                                        \n\
}";
// Black Fragment Shader
static const char* LavaShader = "                                             \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 colour;                                                              \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(1.0, 0.84, 0.2, 1.0);                                       \n\
}";

//______________________________________________________________________________________________________________________LEVEL VERTICES

GLfloat LV1[] = {
	1.92 - squareSize * 2, (-1.08 + 1.2 + squareSize), 0.0,
	1.92 - squareSize * 2, (-1.08 + squareSize)		 , 0.0,
	1.92			,      (-1.08 + squareSize)		 , 0.0,
	1.92			   	 , -1.08 + squareSize	   , 0.0,
	1.92				 , -1.08 + squareSize + 1.2, 0.0,
	1.92 - squareSize * 2, -1.08 + squareSize + 1.2, 0.0,
	1.92 - (squareSize * 4), (-1.08 + 0.6 + squareSize), 0.0,
	1.92 - (squareSize * 4), (-1.08 + squareSize)	   , 0.0,
	1.92 - (squareSize * 2), (-1.08 + squareSize)	   , 0.0,
	1.92 - (squareSize * 2)  , -1.08 + squareSize, 0.0,
	1.92 - (squareSize * 2)  , -1.08 + squareSize + 0.6, 0.0,
	1.92 - (squareSize * 4), -1.08 + squareSize + 0.6, 0.0

};

GLfloat LV2[] = {
	//first block
	1.77, 0.74, 0.0,
	1.77, -0.93,0.0,
	1.92, -0.93,0.0,
	1.92, -0.93,0.0,
	1.92, 0.74, 0.0,
	1.77, 0.74, 0.0,
	//second block
	1.77, 0.74, 0.0,
	1.77, 0.66, 0.0,
	1.48, 0.74, 0.0,
	1.48, 0.74, 0.0,
	1.48, 0.66, 0.0,
	1.77, 0.66, 0.0,
	//third block
	1.46, 0.23, 0.0,
	0.25, 0.23, 0.0,
	0.25, 0.10, 0.0,
	1.46, 0.23, 0.0,
	1.46, 0.10, 0.0,
	0.25, 0.10, 0.0,
	//fourth block
	-0.5, 0.00, 0.0,
	-0.9, 0.00, 0.0,
	-0.9,-0.20, 0.0,
	-0.5, 0.00, 0.0,
	-0.5,-0.20, 0.0,
	-0.9,-0.20, 0.0
};

//______________________________________________________________________________________________________________________LEVEL RENDERING

void renderLV1() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(LV1), LV1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Bind the VAO and draw the square
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 12);  // 12 vertices 4 triangles
	glBindVertexArray(0);  // Unbind the VAO

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
void renderLV2() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(LV2), LV2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Bind the VAO and draw the square
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 24);
	glBindVertexArray(0);  // Unbind the VAO

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

//______________________________________________________________________________________________________________________RENDERING

// both triangles for a square
void tri2(GLfloat xpos, GLfloat ypos) {
	GLfloat vertices[] = {
		squareSize + xpos, -squareSize + ypos, 0.0,
	   -squareSize + xpos, -squareSize + ypos, 0.0,
	   -squareSize + xpos,  squareSize + ypos, 0.0
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
void tri1(GLfloat xpos, GLfloat ypos) {
	GLfloat vertices[] = {
	   -squareSize + xpos,  squareSize + ypos, 0.0,
		squareSize + xpos,  squareSize + ypos, 0.0,
		squareSize + xpos, -squareSize + ypos, 0.0
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void renderFloor(GLfloat xpos, GLfloat ypos) {
	GLfloat vertices[] = {
		// First triangle
	   -1.92 + xpos,  squareSize + ypos, 0.0,  // Top-left
		1.92 + xpos,  squareSize + ypos, 0.0,  // Top-right
		1.92 + xpos, -squareSize + ypos, 0.0,  // Bottom-right

		// Second triangle
	   -1.92 + xpos,  squareSize + ypos, 0.0,  // Top-left
		1.92 + xpos, -squareSize + ypos, 0.0,  // Bottom-right
	   -1.92 + xpos, -squareSize + ypos, 0.0   // Bottom-left
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Bind the VAO and draw the square
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);  //6 verices 2 triangles
	glBindVertexArray(0);  // Unbind the VAO

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO); // delete vao+vbo info so you dont get piling up stuff
}

//______________________________________________________________________________________________________________________COLLISIONS
bool OnFloor() {
	if (pos.y <= -1.08 + squareSize * 3) {
		return true;
	}
	else {
		return false;
	}
}
bool OnCeiling() {
	if (pos.y >= 1.08 - squareSize) {
		return true;
	}
	else {
		return false;
	}
}
bool TouchingBack() {
	if (pos.x < -1.92 + squareSize) {
		return true;
	}
	else {
		return false;
	}
}

bool AABB(float playerX, float playerY, float playerSize, GLfloat* blocks, size_t blockCount) {
	for (size_t i = 0; i < blockCount; i += 6) {
		// Get the coordinates of the two triangles that form the block
		GLfloat x1 = blocks[i];     // First triangle, bottom-left x
		GLfloat y1 = blocks[i + 1]; // First triangle, bottom-left y
		GLfloat x2 = blocks[i + 3]; // Second triangle, bottom-right x
		GLfloat y2 = blocks[i + 4]; // Second triangle, bottom-right y

		// Calculate the edges of the block
		float blockLeft = std::min(x1, x2);
		float blockRight = std::max(x1, x2) + squareSize;
		float blockBottom = std::min(y1, y2);
		float blockTop = std::max(y1, y2) + squareSize;

		// Check for collision
		if (playerX + playerSize > blockLeft && playerX < blockRight && playerY + playerSize > blockBottom && playerY < blockTop) {
			return true; // Collision detected
		}
	}
	return false; // No collision
}


//______________________________________________________________________________________________________________________SHADERS
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void CompileShaders()
{
	shader = glCreateProgram();

	if (!shader)
	{
		printf("Failed to create shader\n");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

}

GLuint CompileBlackShader()
{
	GLuint blackShaderProgram = glCreateProgram();

	if (!blackShaderProgram)
	{
		printf("Failed to create black shader program\n");
		return 0;
	}

	// Use the same vertex shader
	AddShader(blackShaderProgram, vShader, GL_VERTEX_SHADER);

	// Add the black fragment shader
	AddShader(blackShaderProgram, blackShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(blackShaderProgram);
	glGetProgramiv(blackShaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(blackShaderProgram, sizeof(eLog), NULL, eLog);
		printf("Error linking black shader program: '%s'\n", eLog);
		return 0;
	}

	glValidateProgram(blackShaderProgram);
	glGetProgramiv(blackShaderProgram, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(blackShaderProgram, sizeof(eLog), NULL, eLog);
		printf("Error validating black shader program: '%s'\n", eLog);
		return 0;
	}

	return blackShaderProgram;
}
//compile lava colour shader
GLuint CompileLavaShader()
{
	GLuint lavaShaderProgram = glCreateProgram();

	if (!lavaShaderProgram)
	{
		printf("Failed to create black shader program\n");
		return 0;
	}

	// Use the same vertex shader
	AddShader(lavaShaderProgram, vShader, GL_VERTEX_SHADER);

	// Add the black fragment shader
	AddShader(lavaShaderProgram, LavaShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(lavaShaderProgram);
	glGetProgramiv(lavaShaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(lavaShaderProgram, sizeof(eLog), NULL, eLog);
		printf("Error linking black shader program: '%s'\n", eLog);
		return 0;
	}

	glValidateProgram(lavaShaderProgram);
	glGetProgramiv(lavaShaderProgram, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(lavaShaderProgram, sizeof(eLog), NULL, eLog);
		printf("Error validating black shader program: '%s'\n", eLog);
		return 0;
	}

	return lavaShaderProgram;
}