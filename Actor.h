#ifndef ACTOR_H
#define ACTOR_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <math.h>
#include "Object.h"
#include "Health.h"
#include "Image.h"
#include "Timer.h"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class Actor
{
private:
	Object *robot_base; 
	Object *robot_body; 
	Object *robot_neck;
	Object *robot_head;
	Object *robot_arm;
	Health *healthbar;
	//Object *body_connector; //connects the base to the body (no sprite used for this)
	//Object *entity_body; //body of the robot
	
	Timer jump_clock; //used to keep track of how long it has been since the player has jumped
	float jump_limit; //how often the player can jump (in seconds)

	//health bar

public:
	Actor(); //does nothing
	Actor(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type);

	//creates the robot body, connecting it with a joint to the robot base
	void createRobotBody(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type);

	//creates the robot neck, connecting both disks(the neck) to each other, and the bottom one connected to the robot body
	void createRobotNeck(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture1, int current_index, int body_type, int shape_type);

	//creates the robot head, connecting it with a joint to the robot neck
	void createRobotHead(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type);

	//creates the robot arm, connecting it with a revolute joint from the robot body
	void createRobotArm(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, sf::Texture &robot_body_texture, int current_index, int body_type, int shape_type);

	void updateArmRotation(sf::RenderWindow &window); //updates the current angle of the arm using box2d - DOESN'T WORK RIGHT NOW
	void playerUpdate(sf::RenderWindow &window); //called every iteration to update everything that has to do with the player. All other calls are inside this function.
	void keyboardControl(); //WASD movement update

	Object* getRobotBase(); //returns the entity
	Object* getRobotBody();
	Object* getRobotNeck();
	Object* getRobotHead();
	Object* getRobotArm();
	Health* getHealthBar();

};


#endif