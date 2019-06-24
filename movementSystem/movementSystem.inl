void MovementSystem::init()
{
    //
}

void MovementSystem::update(float deltaTime)
{
    Unit* unit;
    List<BaseComponent*>& memory = ComponentManager::getComponentMemory<Transform>();
    List<BaseComponent*>::iterator i;
    
    for(i = memory.begin(); i != memory.end(); ++i)
    {
        
        if((*i)->entity->type != UNIT_ENTITY)
            continue;
        unit = (Unit*)((*i)->entity);
        if( unit->transform->position==unit->transform->targetpoint)
            continue;
        
        move(unit,deltaTime);
    }
}

void MovementSystem::destroy()
{
    //
}

void MovementSystem::move(Unit* unit,float deltaTime)
{
    bool left=false;
    bool right=false;
    bool up=false;
    bool down=false;

    glm::vec3 objetive=unit->transform->targetpoint;
    moveDirection(unit,objetive,up,down,left,right);
    checkObstacles(unit,objetive,up,down,left,right,deltaTime);
    if(up)
        moveUp(unit,objetive,deltaTime);
    if(down)
        moveDown(unit,objetive,deltaTime);
    if(left)
        moveLeft(unit,objetive,deltaTime);
    if(right)
        moveRight(unit,objetive,deltaTime);
}

void MovementSystem::moveDirection(Unit* unit,glm::vec3 objetive,bool& up,bool& down,bool& left,bool& right)
{
    glm::vec3 click=objetive;
    left=false;
    right=false;
    up=false;
    down=false;
    if(unit->transform->position.x>click.x)
        left=true;
    else if(unit->transform->position.x<click.x)
        right=true;
    if(unit->transform->position.z>click.z)
        up=true;
    else if(unit->transform->position.z<click.z)
        down=true;
}

void MovementSystem::moveUp(Unit* unit,glm::vec3 objetive,float deltaTime)
{
    float speed=unit->stats->velocity* deltaTime;
    float balancedspeed=(getYdis(unit,objetive)/getDistance(unit,objetive))*speed;
    if(balancedspeed<getYdis(unit,objetive))
        unit->transform->position.z-=balancedspeed;
    else
        unit->transform->position.z=objetive.z;
}

void MovementSystem::moveDown(Unit* unit,glm::vec3 objetive,float deltaTime)
{
    float speed=unit->stats->velocity* deltaTime;
    float balancedspeed=getYdis(unit,objetive)/getDistance(unit,objetive)*speed;
    if(balancedspeed<getYdis(unit,objetive))
        unit->transform->position.z+=balancedspeed;
    else
        unit->transform->position.z=objetive.z;
}
void MovementSystem::moveRight(Unit* unit,glm::vec3 objetive,float deltaTime)
{
    float speed=unit->stats->velocity* deltaTime;
    float balancedspeed=getXdis(unit,objetive)/getDistance(unit,objetive)*speed;
    if(balancedspeed<getXdis(unit,objetive))
        unit->transform->position.x+=balancedspeed;
    else
        unit->transform->position.x=objetive.x;
}

void MovementSystem::moveLeft(Unit* unit,glm::vec3 objetive,float deltaTime)
{
    float speed=unit->stats->velocity* deltaTime;
    float balancedspeed=getXdis(unit,objetive)/getDistance(unit,objetive)*speed;
    if(balancedspeed<getXdis(unit,objetive))
        unit->transform->position.x-=balancedspeed;
    else
        unit->transform->position.x=objetive.x;
}

float MovementSystem::getXdis(Unit* unit,glm::vec3 objetive)
{
    return abs(unit->transform->position.x-objetive.x);
}

float MovementSystem::getYdis(Unit* unit,glm::vec3 objetive)
{
    return abs(unit->transform->position.z-objetive.z);
}


float MovementSystem::getDistance(Unit* unit,glm::vec3 objetive)
{
    float xdis=getXdis(unit,objetive);
    float ydis=getYdis(unit,objetive);
    return sqrt(pow(xdis,2)+pow(ydis,2));
}

void MovementSystem::setExtremes(Unit* unit,float& up,float& down,float& left,float& right)
{
    glm::vec3 size=unit->boxcollider->size;
    glm::vec3 position=unit->transform->position;

    up=position.z-size.z/2;
    down=position.z+size.z/2;
    left=position.x-size.x/2;
    right=position.x+size.x/2;

}

bool MovementSystem::between(float point,float MIN,float MAX)
{
    return point>MIN&&point<MAX;
}


void MovementSystem::checkColisions(Unit* unit,Unit* unit2,bool& up,bool& down,bool& left,bool& right,float deltaTime)
{
    glm::vec3 objetive=unit->transform->targetpoint;
    glm::vec3 position=unit->transform->position;
    float up2,down2,left2,right2;

    float speed=unit->stats->velocity* deltaTime;
    float speedx=getXdis(unit,objetive)/getDistance(unit,objetive)*speed;
    float speedy=getYdis(unit,objetive)/getDistance(unit,objetive)*speed;
    setExtremes(unit2,up2,down2,left2,right2);
    if(between(position.x,left2,right2)&&position.z-speedy<down2&&position.z-speedy>up2){
        up=false;
    }
        
    if(between(position.x,left2,right2)&&between(position.z+speedy,up2,down2)){
        down=false;
    }
        
    if(between(position.z,up2,down2)&&position.x-speedx<right2&&position.x-speedx>left2){
        left=false;
    }
        
    if(between(position.z,up2,down2)&&between(position.x+speedx,left2,right2)){
        right=false;
    }
        
}

void MovementSystem::checkObstacles(Unit* unit,glm::vec3& objetive,bool& up,bool& down,bool& left,bool& right,float deltaTime)
{
    Unit* unit2;
    List<BaseComponent*>& memory = ComponentManager::getComponentMemory<Transform>();
    List<BaseComponent*>::iterator i;
    for(i = memory.begin(); i != memory.end(); ++i)
    {
        if((*i)->entity->type != UNIT_ENTITY)
            continue;
        unit2 = (Unit*)((*i)->entity);
        if(unit==unit2)
            continue;
        checkColisions(unit,unit2,up,down,left,right,deltaTime);
    }
}
