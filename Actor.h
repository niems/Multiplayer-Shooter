#ifndef ACTOR_H
#define ACTOR_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include "Object.h"
#include "Timer.h"


class Actor
{
private:
	Object *entity;

	Timer jump_clock; //used to keep track of how long it has been since the player has jumped
	float jump_limit; //how often the player can jump (in seconds)

	//health bar

public:
	Actor(); //does nothing
	Actor(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type);

	void playerUpdate(); //called every iteration to update everything that has to do with the player. All other calls are inside this function.
	void keyboardControl(); //WASD movement update

	Object* getEntity(); //returns the entity
};


#endif