#include "Actor.h"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

const float PIXELS_TO_METERS = 0.03333; //number of meters in one pixel
const float METERS_TO_PIXELS = 30.0; //number of pixels in one meter

Actor::Actor(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type)
{
	this->entity = new Object( window, world, fixture, texture, current_index, body_type, shape_type );

	this->jump_limit = 1.0; //the player is able to jump as often as this (in seconds)
}

void Actor::createActorBody(sf::RenderWindow &window, b2World *world, b2FixtureDef &fixture, sf::Texture &texture, int current_index, int body_type, int shape_type)
{
	this->entity_body = new Object( window, world, fixture, texture, current_index, body_type, shape_type );
	this->entity_body->getBody()->SetFixedRotation( true );	

	//set position of robot body first, then connect the joint
	this->entity_body->getBody()->SetTransform( b2Vec2( this->entity->getBody()->GetPosition().x, this->entity->getBody()->GetPosition().y + (115 * PIXELS_TO_METERS) ), 0 );
	this->entity_body->updateSpritePos();

	//used to connect the body to the base. No sprite used with this
	sf::Vector2f connector_size;
	connector_size.x = 15; // this->entity->getSprite()->getPosition().x - this->entity_body->getSprite()->getPosition().x;
	connector_size.y = this->entity->getSprite()->getPosition().y - this->entity_body->getSprite()->getPosition().y;
	this->body_connector = new Object( window, world, fixture, connector_size, current_index, body_type, shape_type );

	b2RevoluteJointDef revolute_joint_def;
	revolute_joint_def.bodyA = this->entity->getBody();
	revolute_joint_def.localAnchorA.Set( 0, 0 );

	revolute_joint_def.bodyB = this->body_connector->getBody();
	revolute_joint_def.localAnchorB.Set( 0, -1 );
	revolute_joint_def.collideConnected = false;
	world->CreateJoint( &revolute_joint_def );

	b2WeldJointDef weld_joint_def;
	weld_joint_def.bodyA = this->entity_body->getBody();
	weld_joint_def.localAnchorA.Set( 0, -1 );
	
	weld_joint_def.bodyB = this->body_connector->getBody();
	weld_joint_def.localAnchorB.Set( 0, 1 );
	weld_joint_def.collideConnected = false;
	world->CreateJoint( &weld_joint_def );

}

void Actor::playerUpdate()
{
	this->entity->updateSpritePos(); //updates the player sprite to the box2d object position

	//REMOVE THE SET TRANSFORM CALL FOR THE BODY ONCE THE JOINT IS WORKING.
	//this->entity_body->getBody()->SetTransform( b2Vec2( this->entity->getBody()->GetPosition().x, this->entity->getBody()->GetPosition().y + (55 * PIXELS_TO_METERS) ), 0 );

	this->entity_body->updateSpritePos();
	this->jump_clock.update(); //used to determine if the player can jump
	this->keyboardControl(); //used to control player movement
}

void Actor::keyboardControl()
{
	this->jump_clock.update(); //must be called every iteration to stay accurate!

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) //moving right
	{
		b2Vec2 current_velocity = this->entity->getBody()->GetLinearVelocity();
		float desired_velocity = 250 * PIXELS_TO_METERS;
		float velocity_change = desired_velocity - current_velocity.x;

		float impulse = this->entity->getBody()->GetMass() * velocity_change;

		this->entity->getBody()->ApplyLinearImpulse( b2Vec2(impulse, 0), this->entity->getBody()->GetWorldCenter(), true );
	}

	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) //moving left
	{
		b2Vec2 current_velocity = this->entity->getBody()->GetLinearVelocity();
		float desired_velocity = -250 * PIXELS_TO_METERS;
		float velocity_change = desired_velocity - current_velocity.x;
		float impulse = this->entity->getBody()->GetMass() * velocity_change;

		this->entity->getBody()->ApplyLinearImpulse( b2Vec2( impulse, 0 ), this->entity->getBody()->GetWorldCenter(), true );
	}

	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) //stop and drop
	{
		b2Vec2 velocity;

		velocity.x = 0.0; //cancels out velocity on the x axis
		velocity.y = this->entity->getBody()->GetLinearVelocity().y * 1.2; //increases the velocity that you're falling

		velocity.y = ( velocity.y > 0 ) ? -velocity.y : velocity.y; //if player is traveling up, reverses the velocity

		this->entity->getBody()->SetLinearVelocity( velocity );
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ) //player jump
	{
		if( this->jump_clock.getElapsedTime() >= this->jump_limit )
		{
			b2Vec2 current_velocity = this->entity->getBody()->GetLinearVelocity();
			float impulse = this->getEntity()->getBody()->GetMass() * 12;

			this->entity->getBody()->SetLinearVelocity( b2Vec2( current_velocity.x, 0 ) ); //cancels out y velocity before jumping
			this->entity->getBody()->ApplyLinearImpulse( b2Vec2( 0, impulse ), this->entity->getBody()->GetWorldCenter(), true );

			this->jump_clock.restartClock();
		}
		
	}
}

Object* Actor::getEntity()
{
	return( this->entity );
}

Object* Actor::getEntityBody()
{
	return( this->entity_body );
}

