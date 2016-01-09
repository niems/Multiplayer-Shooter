#ifndef ACTOR_H
#define ACTOR_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include "Object.h"
#include "Image.h"
#include "Timer.h"


class Actor
{
private:
	Object *robot_base; 
	Object *robot_body; 
	Object *robot_neck1;
	Object *robot_neck2;
	//Object *body_connector; //connects the base to the body (no sprite used for this)
	//Object *entity_body; //body of the robot
	
	Timer jump_clock; //used to keep track of how long it has been since the player has jumped
	float jump_limit; //how often the player can jump (in seconds)

	//health bar

public:
	Actor(); //does nothing
	Actor(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type);

	//Actor(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Sprite &sprite, sf::Vector2u &texture_size, int current_index, int body_type, int shape_type); //NEW - corresponds to new Object() constructor

	//void createActorBody(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type);

	//creates the robot body, connecting it with a joint to the robot base
	void createRobotBody(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type);

	//creates the robot neck, connecting both disks(the neck) to each other, and the bottom one connected to the robot body
	void createRobotNeck(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture1, sf::Texture &texture2, int current_index, int body_type, int shape_type);

	void playerUpdate(); //called every iteration to update everything that has to do with the player. All other calls are inside this function.
	void keyboardControl(); //WASD movement update

	Object* getEntity(); //returns the entity
	Object* getRobotBody();
	//Object* getEntityBody(); //returns the body instead of the base
};


#endif