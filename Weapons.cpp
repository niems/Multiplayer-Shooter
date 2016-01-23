#include "Weapons.h"

Weapons::Weapons(b2World *world)
{
	this->PIXELS_TO_METERS = 0.03333;
	this->METERS_TO_PIXELS = 30.0;
	b2ParticleSystemDef world_particle_system_def;
	b2ParticleSystem *world_particle_system;
	sf::CircleShape *shape = new sf::CircleShape( 5.0 );
	
	world_particle_system_def.density = 1;
	world_particle_system_def.radius = shape->getRadius() * PIXELS_TO_METERS;
	world_particle_system_def.maxCount = 1000; //total number of particles allowed in the system at any given time

	this->particle_system = world->CreateParticleSystem( &world_particle_system_def );	


	//single shot setup
	this->max_effect_duration.push_back( 5.0 ); //seconds before particles

	this->shape.push_back( shape );
	this->shape.back()->setFillColor( sf::Color( 0, 255, 255 ) );
	this->shape.back()->setOutlineColor( sf::Color( 128, 255, 255 ) );
	this->shape.back()->setOutlineThickness( 2 );
	this->shape.back()->setOrigin( this->shape.back()->getRadius(), this->shape.back()->getRadius() );
	
}

//pass player position and mouse position so the angle can be calculated
void Weapons::singleShot(b2World *world, const b2Vec2 &pos) //creates single shot projectile
{
	b2BodyDef body_def;
	b2CircleShape body_shape;
	b2FixtureDef body_fixture;
	b2Body *body;
	Projectile *temp_projectile = new Projectile();

	body_def.type = b2_dynamicBody;
	body_def.bullet = true;
	body_def.gravityScale = 0.1;
	body_def.position.Set( pos.x, pos.y );

	body_shape.m_radius = 10 * PIXELS_TO_METERS;
	
	body_fixture.shape = &body_shape;
	body_fixture.density = 0.5;
	body_fixture.filter.categoryBits = entity_category::PLAYER_WEAPON;
	body_fixture.filter.maskBits = entity_category::BOUNDARY | entity_category::ENEMY_WEAPON;
	//body_fixture.filter;

	body = world->CreateBody( &body_def );
	body->CreateFixture( &body_fixture );

	temp_projectile->particle_body = body;
	temp_projectile->type = TYPE::SINGLE_SHOT;
	this->projectile_single_shot.push_back( temp_projectile );

	this->projectile_single_shot.back()->particle_body->ApplyLinearImpulse( b2Vec2( 140 * PIXELS_TO_METERS, -50 * -PIXELS_TO_METERS ), this->projectile_single_shot.back()->particle_body->GetWorldCenter(), true );

}

void singleShot(b2World *world, const b2Vec2 &player_pos, sf::Vector2i &mouse_pos)
{

}

void Weapons::updateSingleShot() //used to update this type of projectile every
{

	/*
	for( int i = 0; i < this->projectile_single_shot.size(); i++ ) //updates all of the particle sprites
	{
		this->projectile_single_shot[i]->shape.setPosition( sf::Vector2f(this->projectile_single_shot[i]->particle_body->GetPosition().x * 30.0, this->projectile_single_shot[i]->particle_body->GetPosition().y * -30.0) );
	}
	*/
}

vector<Projectile *> Weapons::getSingleShotProjectile()
{
	return( this->projectile_single_shot );
}

vector<sf::CircleShape *> Weapons::getParticleShapes()
{
	return( this->shape );
}