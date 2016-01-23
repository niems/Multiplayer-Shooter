#include "Object.h"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

const float PIXELS_TO_METERS = 0.03333; //number of meters in one pixel
const float METERS_TO_PIXELS = 30.0; //number of pixels in one meter

enum {STATIC, DYNAMIC, KINEMATIC}; //determines which type of box2d object to create
enum {POLY_SHAPE, CIRCLE_SHAPE}; //determines which type of box2d shape to create

Object::Object(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type)
{
	sf::Sprite sprite;
	b2BodyDef body_def;

	//only one of the shapes are used
	b2PolygonShape poly_shape;
	b2CircleShape circle_shape;

	sprite.setTexture( texture );
	sprite.setOrigin( texture.getSize().x / 2.0, texture.getSize().y / 2.0 ); //centers the origin
	this->sprite = sprite;
	this->index = current_index;

	if(body_type == DYNAMIC)
		body_def.type = b2_dynamicBody;

	else if(body_type == STATIC)
		body_def.type = b2_staticBody;

	else if(body_type == KINEMATIC)
		body_def.type = b2_kinematicBody;

	body_def.position.Set(0, 0); //default starting position (top left of the screen)

	if(shape_type == POLY_SHAPE)
	{
		poly_shape.SetAsBox( (texture.getSize().x / 2.0) * PIXELS_TO_METERS, (texture.getSize().y / 2.0) * PIXELS_TO_METERS );
		fixture.shape = &poly_shape;
	}

	else if(shape_type == CIRCLE_SHAPE)
	{
		circle_shape.m_radius = (texture.getSize().x / 2.0) * PIXELS_TO_METERS;
		fixture.shape = &circle_shape;
	}

	b2Body *body = world->CreateBody( &body_def );
	body->CreateFixture( &fixture );
	this->body = body;	
}

Object::Object(sf::RenderWindow &window, b2World *world, sf::Texture &texture, int current_index)
{
	sf::Sprite sprite;

	sprite.setTexture( texture );
	sprite.setOrigin( texture.getSize().x / 2.0, texture.getSize().y / 2.0 );
}

Object::Object(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Vector2f size, int current_index, int body_type, int shape_type)
{
	b2BodyDef body_def;

	//only one of the shapes are used
	b2PolygonShape poly_shape;
	b2CircleShape circle_shape;

	this->index = current_index;

	if(body_type == DYNAMIC)
		body_def.type = b2_dynamicBody;

	else if(body_type == STATIC)
		body_def.type = b2_staticBody;

	else if(body_type == KINEMATIC)
		body_def.type = b2_kinematicBody;

	body_def.position.Set(0, 0); //default starting position (top left of the screen)
	 
	if(shape_type == POLY_SHAPE)
	{
		poly_shape.SetAsBox( (size.x / 2.0) * PIXELS_TO_METERS, (size.y / 2.0) * PIXELS_TO_METERS );
		fixture.shape = &poly_shape;
	}

	else if(shape_type == CIRCLE_SHAPE)
	{
		circle_shape.m_radius = (size.x / 2.0) * PIXELS_TO_METERS;
		fixture.shape = &circle_shape;
	}

	b2Body *body = world->CreateBody( &body_def );
	body->CreateFixture( &fixture );
	this->body = body;	
}

void Object::updateSpritePos()
{
	this->sprite.setPosition( this->body->GetPosition().x * METERS_TO_PIXELS, -this->body->GetPosition().y * METERS_TO_PIXELS );
	this->sprite.setRotation( -this->body->GetAngle() * RADTODEG );
}

void Object::updatePosition(Object &object)
{
	object.updateSpritePos(); //updates the position of the current sprite to match the box2d body
}


sf::Sprite* Object::getSprite()
{
	return( &this->sprite );
}

b2Body* Object::getBody()
{
	return( this->body );
}