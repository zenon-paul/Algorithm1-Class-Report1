#include"GL/glut.h"
#include"GLFW/glfw3.h"
#include <stdio.h>
#include<stdlib.h>
#include"list.h"
#include"binary_tree.h"
#include"utility.h"


#define WINDOW_HIGHT 640
#define WINDOW_WIDTH 640
GLFWwindow* window1;
GLFWwindow* window2;

int window_hight = WINDOW_HIGHT;
int window_width = WINDOW_WIDTH;

int window_hight2 = WINDOW_HIGHT;
int window_width2 = WINDOW_WIDTH;


void render1(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)w, 0.0, (double)h);
	window_hight = h;
	window_width = w;

	glClearColor(0.0, 0.21, 0.38, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glClearColor(0, 0, 0, 1);
	glBegin(GL_QUADS);
	glColor3d(0, 1, 1);
	glVertex2i(0,0);
	glColor3d(1, 0, 1);
	glVertex2i(0,200);
	glColor3d(1, 1, 0);
	glVertex2i(200,200);
	glColor3d(0, 0, 0);
	glVertex2i(200,0);
	glEnd();
	glFlush();
}

void render2(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)w, 0.0, (double)h);
	window_hight2 = h;
	window_width2 = w;

	glClearColor(0.3, 0.21, 0.38, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3d(0, 1, 1);
	glVertex2i(0, 0);
	glColor3d(1, 0, 1);
	glVertex2i(0, 200);
	glColor3d(1, 1, 0);
	glVertex2i(200, 200);
	glColor3d(0, 0, 0);
	glVertex2i(200, 0);
	glEnd();
	glFlush();
}

void mouse_callback(GLFWwindow* pwin, int button, int action, int mods) {
	if (action != GLFW_PRESS) {
		return;
	}


	if (window1 == pwin) {
		printf("window 1 ");
	}
	if (window2 == pwin) {
		printf("window 2 ");
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		printf("L - down\n");
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		printf("R - down\n");
	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
		printf("M - down\n");
	}
	else {
		printf("\n");
	}
}

void key_callback(GLFWwindow* pwin, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS)
		return;


	if (window1 == pwin) {
		printf("window 1 ");
	}
	if (window2 == pwin) {
		printf("window 2 ");
	}

	if (key == GLFW_KEY_UP) {
		printf("key up\n");
	}
	else if (key == GLFW_KEY_DOWN) {
		printf("key down\n");
	}
	else if (key == GLFW_KEY_LEFT) {
		printf("key left\n");
	}
	else if (key == GLFW_KEY_RIGHT) {
		printf("key right\n");
	}
	else {
		printf("\n");
	}
}

void glfwMainLoop() {
	while (glfwWindowShouldClose(window1) == GL_FALSE) {
		int width, height;

		////////////////////////////////////////////////////////
		glfwGetFramebufferSize(window1, &width, &height);
		glfwMakeContextCurrent(window1);
		render1(width, height);
		glfwSwapBuffers(window1);
		////////////////////////////////////////////////////////
		glfwGetFramebufferSize(window2, &width, &height);
		glfwMakeContextCurrent(window2);
		render2(width, height);
		glfwSwapBuffers(window2);
		////////////////////////////////////////////////////////

		glfwWaitEvents();
	}
}

int main(){
	if (glfwInit() == GL_FALSE) return 0;
	window1 = glfwCreateWindow(WINDOW_HIGHT,WINDOW_WIDTH, "window1", NULL, NULL);
	window2 = glfwCreateWindow(WINDOW_HIGHT,WINDOW_WIDTH, "window2", NULL, NULL);

	//glfwSetKeyCallback(window1, key_callback);
	//glfwSetKeyCallback(window2, key_callback);

	//glfwSetMouseButtonCallback(window1, mouse_callback);
	//glfwSetMouseButtonCallback(window2, mouse_callback);

	glfwMainLoop();
	glfwTerminate();
	/*int n = 4;
	Tree* result = get_different_trees(n);

	for(int i = 0;result[i] != NULL;i++){
		printf("[%d\n",i);
		search_pre_with_depth(result[i],0);
		putchar('\n');
	}*/

}