#ifndef ECS_MOVEMENT_SYSTEM_H
#define ECS_MOVEMENT_SYSTEM_H


#include "ecs/entities/entityManager.hpp"
#include "ecs/systems/unit/unitSystem.hpp"



class MovementSystem{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

    static bool between(float,float,float);
    static void checkColisions(Unit* unit,Unit* unit2,bool& up,bool& down,bool& left,bool& right,float deltaTime);
    static void checkObstacles(Unit* unit,glm::vec3& objetive,bool& up,bool& down,bool& left,bool& right,float deltaTime);


    static void move(Unit* unit,float deltaTime);
    static void moveDirection(Unit* unit,glm::vec3 objetive,bool& up,bool& down,bool& left,bool& right);
    static void moveRight(Unit*,glm::vec3 objetive,float deltaTime);
    static void moveLeft(Unit*,glm::vec3 objetive,float deltaTime);
    static void moveUp(Unit*,glm::vec3 objetive,float deltaTime);
    static void moveDown(Unit*,glm::vec3 objetive,float deltaTime);
    static void setExtremes(Unit*,float&,float&,float&,float&);

    static float getXdis(Unit*,glm::vec3 objetive);
    static float getYdis(Unit*,glm::vec3 objetive);
    static float getDistance(Unit*,glm::vec3 objetive);
};

#endif