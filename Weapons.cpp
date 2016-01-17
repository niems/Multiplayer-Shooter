#include "Weapons.h"

Weapons::Weapons(b2World *world)
{
	b2ParticleSystemDef world_particle_system_def;


	//single shot setup
	this->max_effect_duration.back() = 5.0; //seconds before particles

	this->shape.back() = sf::CircleShape(10.0);
	this->shape.back().setFillColor( sf::Color( 255, 0, 0 ) );
	this->shape.back().setOutlineColor( sf::Color( 0, 0, 255 ) );
	this->shape.back().setOrigin( 10, 10 );

	
}