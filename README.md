# OpenGL-Cube

The famlous rotating cube demo that everyone does! It seems this used to be quite popular but since modern OpenGL (3.1) people have stopped doing it and now seem to do the rainbow pyramid instead so when I decided to do this one I could not find any examples online using modern OpenGL so I decided to leave this one here.

In order to compile this you need OpenGL in memory.

If you are comiling with gcc then link the file like this

g++ main.cpp GLWindow.cpp Mesh.cpp Shader.cpp -o cube -lGL -lglfw -lGLEW

This file includes a working GLFW window class and a mesh and shader class. The GLFW window class should work with any other project. The Mesh class likewise will work with any other project providing you use index (element) draws you will also need to interleave you vertices in the same way I have. The shader class works with two shaders (it can be adjusted to work with more)

The source code was written on a linux machine (on a text editor) and compiled in gcc. It also works on windows. I will put a windows Binary here in due course.

This code is obviously based on many examples which I used as I was learning. I am greatful to those who produced this code and enabled me to do this.
