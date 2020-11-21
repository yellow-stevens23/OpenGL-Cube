#ifndef GLWINDOW_H
#define GLWINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

class GLWindow
{
    public:
        GLWindow(GLint width = 800, GLint height = 600,  char *windowTitle = "Test Window");
        void openFullscreen();
        void init();
        void openWindow();
        bool getShouldClose();
        void pollEvents();
        void setColour();
        void swapBuffers();
        ~GLWindow();


    private:
    	void setup();
    	void createCallBacks();
    	static void keyHandler(GLFWwindow *window, int key, int code, int action, int mode);
        GLFWwindow *myWindow;
        char *m_windowName;
        GLint m_width;
        GLint m_height;
        int bufferWidth, bufferHeight;
        bool keys[1024];
};

#endif // GLWINDOW_H

