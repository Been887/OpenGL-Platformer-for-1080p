#pragma once
#include "functions.hpp"

GLint width = 1920, height = 1080, falling;
GLuint VAO, VBO, shader, blackShaderProgram, lavaShaderProgram;
GLfloat squareSize = 0.15;

glm::vec2 pos(0.0, 0.0);
glm::vec2 vel(0.0, 0.0);
glm::vec2 LastVal;

int main() {	// ______________________________________________________________________________________ MAIN
	pos.x = -1.3;
	GLfloat gravity = 0.000125;
	int LV = 0;

	if (glfwInit() != GL_TRUE) {
		std::cout << "GLFW initilisation failed!\n";
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(width, height, "OpenGL Platformer", NULL, NULL);

	if (!mainWindow) {
		std::cout << "Window Creation failed!\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	int bufferHeight, bufferWidth;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW initialisation failed!\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);

	CompileShaders();
	blackShaderProgram = CompileBlackShader();
	lavaShaderProgram = CompileLavaShader();

	while (!glfwWindowShouldClose(mainWindow)) {


		//practical
		glfwPollEvents();

		if (glfwGetKey(mainWindow, GLFW_KEY_LEFT)) {// ____________ inputs
			vel.x -= 0.00025;
		}
		if (glfwGetKey(mainWindow, GLFW_KEY_RIGHT)) {
			vel.x += 0.00025;
		}
		if (glfwGetKey(mainWindow, GLFW_KEY_UP) && falling < 2) {
			vel.y = 0.015;
		}

		falling++;
		vel.y -= gravity;
		vel.x = vel.x * 0.975;//friction

		//rendering
		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		tri1(pos.x, pos.y);

		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		tri2(pos.x, pos.y);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		glUseProgram(blackShaderProgram);

		renderFloor(0.0, (-1.08 + squareSize));

		//switch statement for rendering
		switch (LV) {
		case 1:
			renderLV1();
			break;
		case 2:
			renderLV2();
			break;
		case 3:
			//renderLV3();
			break;
		}

		//_________________________________________________________________________________________COLLISION + OTHER STUFF
		if (pos.x >= 1.92 - squareSize) {
			LV++;
			pos.x = -0.8, pos.y = -0.5;
		}

		LastVal.y = pos.y;
		pos.y += vel.y;

		if (OnFloor()) {
			pos.y = LastVal.y;
			vel.y = 0.0;
			falling = 0.0;
		}
		if (OnCeiling()) {
			pos.y = LastVal.y;
			vel.y = 0.0;
		}
		switch (LV) {// for vertical collisions
		case 1:
			if (AABB(pos.x, pos.y, squareSize, LV1, sizeof(LV1) / sizeof(GLfloat))) {
				pos.y = LastVal.y;
				if (vel.y < 0.0) {
					falling = 0;
				}
				vel.y = 0.0;
			}
			break;
		case 2:
			if (AABB(pos.x, pos.y, squareSize, LV2, sizeof(LV2) / sizeof(GLfloat))) {
				pos.y = LastVal.y;
				if (vel.y < 0.0) {
					falling = 0;
				}
				vel.y = 0.0;
			}
			break;
		}

		LastVal.x = pos.x;
		pos.x += vel.x;
		if (TouchingBack()) {
			pos.x = LastVal.x;
			vel.x = 0.0;
		}
		switch (LV) {//for horizontal collisions
		case 1:
			if (AABB(pos.x, pos.y, squareSize, LV1, sizeof(LV1) / sizeof(GLfloat))) {
				pos.x = LastVal.x;
				vel.x = 0.0;
			}
			break;
		case 2:
			if (AABB(pos.x, pos.y, squareSize, LV2, sizeof(LV2) / sizeof(GLfloat))) {
				pos.x = LastVal.x;
				vel.x = 0.0;
			}
			break;
		}


		glUseProgram(0);
		glfwSwapBuffers(mainWindow);

	}
	return 0;
}