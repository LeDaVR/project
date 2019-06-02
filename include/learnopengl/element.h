#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/model.h>

class Element{
	private:
		std::string elementID;
		// position of model
		glm::vec3 position;
		glm::vec3 rotate;
		float angle;
		glm::vec3 scale;

		//info
		vector<std::string> info;

		void refreshinfo();
		void setModel();
		
	public:
		Model model;

		Element();
		Element(std::string, glm::vec3, glm::vec3,float angle, glm::vec3 );

		void setID(std::string ID);
		void setPosition(glm::vec3 position);
		void setRotation(glm::vec3 rotation, float angle);
		void setScale(glm::vec3 scale);
		void setData(std::string, glm::vec3 , glm::vec3 , float , glm::vec3 );

		std::string getID();
		std::string getInfo();
		glm::vec3 getPosition();
		glm::vec3 getRotate();
		glm::vec3 getScale();

};


#endif