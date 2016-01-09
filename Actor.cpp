#include "Actor.h"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

const float PIXELS_TO_METERS = 0.03333; //number of meters in one pixel
const float METERS_TO_PIXELS = 30.0; //number of pixels in one meter

Actor::Actor(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type)
{
	this->robot_base = new Object( window, world, fixture, texture, current_index, body_type, shape_type );

	this->jump_limit = 1.0; //the player is able to jump as often as this (in seconds)
}

void Actor::createRobotBody(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type)
{
	this->robot_body = new Object( window, world, fixture, texture, current_index, body_type, shape_type );
	this->robot_body->getBody()->SetTransform( b2Vec2( this->robot_base->getBody()->GetPosition().x, this->robot_base->getBody()->GetPosition().y + ((texture.getSize().x / 2.1) * PIXELS_TO_METERS) ), 0);
	
	this->robot_body->getBody()->SetFixedRotation( true );
	
	b2RevoluteJointDef revolute_joint_def;

	revolute_joint_def.bodyA = this->robot_base->getBody();
	revolute_joint_def.localAnchorA.Set( 0, 0 );

	revolute_joint_def.bodyB = this->robot_body->getBody();
	revolute_joint_def.localAnchorB.Set( 0, -1 );

	revolute_joint_def.collideConnected = false;
	world->CreateJoint( &revolute_joint_def );
	//connect robot body to robot base using the revolute joint. Also update the sprite position
}

void Actor::createRobotNeck(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture1, sf::Texture &texture2, int current_index, int body_type, int shape_type)
{
	//robot_neck 1 - connects to robot_neck 2 and the robot head
	this->robot_neck1 = new Object( window, world, fixture, texture1, current_index, body_type, shape_type );

	//robot neck 2 - connects to robot neck 1 and the robot body
	this->robot_neck2 = new Object( window, world, fixture, texture2, current_index, body_type, shape_type );

	
}

void Actor::playerUpdate()
{
	this->robot_base->updateSpritePos(); //updates the player sprite to the box2d object position
	this->robot_body->updateSpritePos();
	//REMOVE THE SET TRANSFORM CALL FOR THE BODY ONCE THE JOINT IS WORKING.
	//this->robot_base_body->getBody()->SetTransform( b2Vec2( this->robot_base->getBody()->GetPosition().x, this->robot_base->getBody()->GetPosition().y + (55 * PIXELS_TO_METERS) ), 0 );

	//this->robot_base_body->updateSpritePos();
	this->jump_clock.update(); //used to determine if the player can jump
	this->keyboardControl(); //used to control player movement
}

void Actor::keyboardControl()
{
	this->jump_clock.update(); //must be called every iteration to stay accurate!

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) //moving right
	{
		b2Vec2 current_velocity = this->robot_base->getBody()->GetLinearVelocity();
		float desired_velocity = 250 * PIXELS_TO_METERS;
		float velocity_change = desired_velocity - current_velocity.x;

		float impulse = this->robot_base->getBody()->GetMass() * velocity_change;

		this->robot_base->getBody()->ApplyLinearImpulse( b2Vec2(impulse, 0), this->robot_base->getBody()->GetWorldCenter(), true );
	}

	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) //moving left
	{
		b2Vec2 current_velocity = this->robot_base->getBody()->GetLinearVelocity();
		float desired_velocity = -250 * PIXELS_TO_METERS;
		float velocity_change = desired_velocity - current_velocity.x;
		float impulse = this->robot_base->getBody()->GetMass() * velocity_change;

		this->robot_base->getBody()->ApplyLinearImpulse( b2Vec2( impulse, 0 ), this->robot_base->getBody()->GetWorldCenter(), true );
	}

	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) //stop and drop
	{
		b2Vec2 velocity;

		velocity.x = 0.0; //cancels out velocity on the x axis
		velocity.y = this->robot_base->getBody()->GetLinearVelocity().y * 1.2; //increases the velocity that you're falling

		velocity.y = ( velocity.y > 0 ) ? -velocity.y : velocity.y; //if player is traveling up, reverses the velocity

		this->robot_base->getBody()->SetLinearVelocity( velocity );
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ) //player jump
	{
		if( this->jump_clock.getElapsedTime() >= this->jump_limit )
		{
			b2Vec2 current_velocity = this->robot_base->getBody()->GetLinearVelocity();
			float impulse = this->getEntity()->getBody()->GetMass() * 12;

			this->robot_base->getBody()->SetLinearVelocity( b2Vec2( current_velocity.x, 0 ) ); //cancels out y velocity before jumping
			this->robot_base->getBody()->ApplyLinearImpulse( b2Vec2( 0, impulse ), this->robot_base->getBody()->GetWorldCenter(), true );

			this->jump_clock.restartClock();
		}
		
	}
}

Object* Actor::getEntity()
{
	return( this->robot_base );
}

Object* Actor::getRobotBody()
{
	return( this->robot_body );
}
