#ifndef EDITOR_H
#define EDITOR_H

#include "dinamicarray.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include "camera.h"
#include <learnopengl/model.h>
#include <fstream>
#include <string>
#include <vector>
#include <learnopengl/elements.h>
#include <learnopengl/elements.cpp>

class EditorData {
		ElementData data;
		Model* model;
	public:
		EditorData();
		void viewmodels(GLFWwindow* window,  Camera* camara,Model *ourmodel);
		void selectmodel(Model* ourmodel);

};

class Editor{
	private:

		EditorData data;
		Arbol arbol;

		glm::mat4 modelpos;
		Model* currentmodel;
		
		int interfaz;
		int dimension;
		float cuadrante;

		DinamicArray<float> vertices;
		DinamicArray<unsigned int> indices;

		int index;
		bool* memorystatus;
		std::vector<Model> objects;
		std::vector<int> memory;

		void drawObjects(GLFWwindow*, Shader*, Camera*);
		void addModel(float xpos,float ypos);
		void deleteModel();
	public:
		Editor();
		
		bool isinside(GLFWwindow* window,Camera* camara);
		void use(GLFWwindow* window,Camera* camara,Shader *modelshader);	
		
		
		int getVerticesSize();
		int getIndicesSize();
		float* getVerticesArray();
		unsigned int* getIndicesArray();

		~Editor();
	
};


#endif
