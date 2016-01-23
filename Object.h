#ifndef OBJECT_H
#define OBJECT_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp> 

class Object
{
private:
	b2Body *body; //box2d body
	sf::Sprite sprite; //sprite for the box2d body
	int index;

public:
	Object(); //does nothing
	Object(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type); //uses a texture

	Object(sf::RenderWindow &window, b2World *world, sf::Texture &texture, int current_index); //creates an object without the box2d object

	Object(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Vector2f size, int current_index, int body_type, int shape_type); //creates body without a sprite

	void updateSpritePos(); //updates the sprite position to the box2d body position
	static void updatePosition(Object &object); //used to update a single object (like the player)

	sf::Sprite* getSprite(); //returns the sprite
	b2Body* getBody(); //returns the box2d body

};



#endif