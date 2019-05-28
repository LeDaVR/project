#include "editor.h"

EditorData::EditorData() {
	//model = &arbol;
}

void EditorData::viewmodels(GLFWwindow *window,Camera* camara,Model *ourmodel) {
	double posx, posy;
	glfwGetCursorPos(window, &posx, &posy);
	//model = int(posy / 300 );
}

void EditorData::selectmodel(Model *ourmodel) {
	ourmodel = model;
}


Editor::Editor(){
	
	interfaz = 0;
	dimension=40;
	cuadrante=1.0f;
	memorystatus = new bool[dimension * dimension];
	for (int i = 0; i < dimension * dimension; i++) {
		memorystatus[i] = true;
	}
	for(int i=0;i<=dimension;i++){
		for(int j=0;j<=dimension;j++){
			vertices.push_back(float(j)*cuadrante);
			vertices.push_back(float(i)*cuadrante);
			vertices.push_back(0.0f);
		}
	}
	
	int cont=0;
	for(int i=0;i<dimension;i++){
		for(int j=0;j<dimension;j++){
			indices.push_back(cont);
			indices.push_back(cont+1);
			indices.push_back(cont+dimension+2);
			indices.push_back(cont+dimension+1);
			indices.push_back(cont);	
			cont++;
		}
		indices.push_back(cont+dimension);
		cont++;
	}
	currentmodel = arbol.getModel();
}

bool Editor::isinside(GLFWwindow* window,Camera* camara){
	double xpos,ypos;
	xpos=camara->get3dposX(window);
	ypos=camara->get3dposY(window);
	if(xpos>=0&&xpos<=dimension*cuadrante&&ypos>=0&&ypos<=dimension*cuadrante)
		return true;
	return false;
}

void Editor::drawObjects(GLFWwindow *window ,Shader *modelshader,Camera *camara) {
	for (int i = 0; i < memory.size(); i++) {
		int xpos, ypos;
		xpos = memory[i] % dimension;
		ypos = memory[i] / dimension +1;
		modelshader->use();
		camara->camera_protection(modelshader);
		camara->camera_transformation(modelshader);
		modelpos = glm::mat4(1.0f);
		modelpos = glm::translate(modelpos, glm::vec3(xpos+cuadrante/2.0f, ypos-cuadrante/2.0f, 0.0f));
		modelpos = glm::rotate(modelpos, glm::radians(90.0f), glm::vec3(1, 0, 0));
		modelshader->setMat4("model", modelpos);
		objects[i].Draw(*modelshader);
	}
	
	
	//model2 = glm::scale(model2, glm::vec3(0.02f, 0.02f, 0.02f));


}

void Editor::addModel(float posx,float posy) {
	memorystatus[this->index] = false;
	memory.push_back(this->index);
	objects.push_back(*currentmodel);
}

void Editor::deleteModel(){
	for (int i = 0; i < memory.size(); i++) {
		if (memory[i] == index) {
			memory.erase(memory.begin()+i);
			objects.erase(objects.begin() + i);
			break;
		}
	}
	memorystatus[this->index] = true;
}

void Editor::use(GLFWwindow* window,Camera* camara,Shader *modelshader){
	switch (interfaz)
	{
		case (0): {
			drawObjects(window, modelshader, camara);
			if (isinside(window,camara)){
				int leftclick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
				int rightclick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
				double xpos, ypos;
				xpos = camara->get3dposX(window);
				ypos = camara->get3dposY(window);
				float cx, cy;
				cx = int(xpos / cuadrante) + (cuadrante / 2.0f);
				cy = int(ypos / cuadrante) + 1 - (cuadrante / 2.0f);
				index = int(xpos / cuadrante) + dimension * int(ypos / cuadrante);
				if (leftclick == GLFW_PRESS) {
					if (memorystatus[index]) {
						addModel(cx, cy);
					}

				}
				if (rightclick == GLFW_PRESS) {
					if (!memorystatus[index]) {
						deleteModel();
					}
				}
			}
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
				interfaz = 1;
			}
			break;
		}
		case (1): {
			int leftclick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
			if (leftclick == GLFW_PRESS) {
				data.viewmodels(window,camara,currentmodel);
				data.selectmodel(currentmodel);
				interfaz = 0;
			}
			break;
		}
		default:
			break;
	}
}

int Editor::getVerticesSize(){
	return vertices.getSize();
}

int Editor::getIndicesSize(){
	return indices.getSize();
}

float* Editor::getVerticesArray(){
	return vertices.arr;
}
unsigned int* Editor::getIndicesArray(){
	return indices.arr;
}

Editor::~Editor(){
	delete[] memorystatus;
}

