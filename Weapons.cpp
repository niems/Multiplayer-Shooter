#include "Weapons.h"

Weapons::Weapons(b2World *world)
{
	b2ParticleSystemDef world_particle_system_def;
	b2ParticleSystem *world_particle_system;
	sf::CircleShape *shape = new sf::CircleShape( 10.0 );
	
	world_particle_system_def.density = 1;
	world_particle_system_def.radius = 10  * 0.03333;
	world_particle_system_def.maxCount = 1000; //total number of particles allowed in the system at any given time

	this->particle_system = world->CreateParticleSystem( &world_particle_system_def );	


	//single shot setup
	this->max_effect_duration.push_back( 5.0 ); //seconds before particles

	this->shape.push_back( shape );
	this->shape.back()->setFillColor( sf::Color( 255, 0, 0 ) );
	this->shape.back()->setOutlineColor( sf::Color( 0, 0, 255 ) );
	this->shape.back()->setOrigin( this->shape.back()->getRadius(), this->shape.back()->getRadius() );
	
}

void Weapons::singleShot(b2World *world, const b2Vec2 &pos) //creates single shot projectile
{
	b2BodyDef body_def;
	b2CircleShape body_shape;
	b2FixtureDef body_fixture;
	b2Body *body;
	Projectile *temp_projectile = new Projectile();

	body_def.type = b2_dynamicBody;
	body_def.bullet = true;
	body_def.position.Set( pos.x, pos.y );

	body_shape.m_radius = 10 * 0.03333;
	
	body_fixture.shape = &body_shape;
	body_fixture.density = 0.5;
	body_fixture.filter.categoryBits = entity_category::PLAYER_WEAPON;
	body_fixture.filter.maskBits = entity_category::BOUNDARY;
	//body_fixture.filter;

	body = world->CreateBody( &body_def );
	body->CreateFixture( &body_fixture );

	temp_projectile->particle_body = body;
	temp_projectile->type = TYPE::SINGLE_SHOT;
	this->projectile_single_shot.push_back( temp_projectile );

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