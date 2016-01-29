#include "Weapons.h"

Weapons::Weapons(b2World *world)
{
	this->PIXELS_TO_METERS = 0.03333;
	this->METERS_TO_PIXELS = 30.0;
	b2ParticleSystemDef world_particle_system_def;
	b2ParticleSystem *world_particle_system;
	sf::CircleShape *shape = new sf::CircleShape( 3.0 );


	//SINGLE SHOT SYSTEM SETUP//////////////////////
	b2ParticleSystem *single_shot_system = NULL; //holds particles of the single shot type
	b2ParticleSystemDef single_shot_system_def;

	single_shot_system_def.radius = shape->getRadius() * this->PIXELS_TO_METERS;
	single_shot_system_def.destroyByAge = true;
	//single_shot_system_def.lifetimeGranularity = 0.5; //number of seconds the particle lives for

	this->particle_systems.push_back( single_shot_system );
	this->particle_systems.back() = world->CreateParticleSystem( &single_shot_system_def );
	this->particle_systems.back()->SetDestructionByAge( true );
	


	//END SINGLE SHOT SYSTEM SETUP///////////////////	
	world_particle_system_def.density = 1;
	world_particle_system_def.radius = shape->getRadius() * PIXELS_TO_METERS;
	world_particle_system_def.maxCount = 100; //total number of particles allowed in the system at any given time

	this->particle_system = world->CreateParticleSystem( &world_particle_system_def );	
	this->particle_system->SetDestructionByAge( true );
	this->particle_system->SetParticleLifetime( 0, 0.5 );
	
	


	//single shot setup
	this->max_effect_duration.push_back( 5.0 ); //seconds before particles

	this->shape.push_back( shape );
	this->shape.back()->setFillColor( sf::Color( 0, 255, 255 ) );
	this->shape.back()->setOutlineColor( sf::Color( 128, 255, 255 ) );
	this->shape.back()->setOutlineThickness( 1 );
	this->shape.back()->setOrigin( this->shape.back()->getRadius(), this->shape.back()->getRadius() );
	
}

/*
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

} */

void Weapons::singleShot(b2World *world, const sf::Vector2f &player_pos, sf::Vector2i &mouse_pos)
{
	b2BodyDef body_def;
	b2CircleShape body_shape;
	b2FixtureDef body_fixture;
	b2Body *body;
	Projectile *temp_projectile = new Projectile();
	b2ParticleGroupDef particle_group_def;

	

	float velocity = 130; //in pixels per second


	//find angle
	float distance = sqrt( pow( mouse_pos.x - player_pos.x, 2 ) + pow( mouse_pos.y - player_pos.y, 2 ) );
	temp_projectile->velocity.x = velocity * ( ( mouse_pos.x - player_pos.x ) / distance );
	temp_projectile->velocity.y = velocity * ( ( mouse_pos.y - player_pos.y ) / distance );

	body_def.type = b2_dynamicBody;
	body_def.bullet = true;
	body_def.gravityScale = 0.4;
	body_def.position.Set( player_pos.x * PIXELS_TO_METERS, player_pos.y * -METERS_TO_PIXELS );

	body_shape.m_radius = 10 * PIXELS_TO_METERS;
	
	body_fixture.shape = &body_shape;
	body_fixture.density = 0.5;
	body_fixture.filter.categoryBits = entity_category::PLAYER_WEAPON;
	body_fixture.filter.maskBits = entity_category::BOUNDARY | entity_category::ENEMY_WEAPON;
	

	body = world->CreateBody( &body_def );
	body->CreateFixture( &body_fixture );

	temp_projectile->particle_body = body;
	temp_projectile->type = TYPE::SINGLE_SHOT;
	this->projectile_single_shot.push_back( temp_projectile );

	this->projectile_single_shot.back()->particle_body->SetTransform( b2Vec2( player_pos.x * PIXELS_TO_METERS, player_pos.y * -PIXELS_TO_METERS ), 0 );
	this->projectile_single_shot.back()->particle_body->ApplyLinearImpulse( b2Vec2( temp_projectile->velocity.x * PIXELS_TO_METERS, temp_projectile->velocity.y * -PIXELS_TO_METERS ), this->projectile_single_shot.back()->particle_body->GetWorldCenter(), true );

	particle_group_def.shape = &body_shape;
	particle_group_def.flags = b2_elasticParticle;
	particle_group_def.angle = -0.5f;
	particle_group_def.angularVelocity = 2.0f;
	particle_group_def.position.Set( projectile_single_shot.back()->particle_body->GetPosition().x, projectile_single_shot.back()->particle_body->GetPosition().y );

	//this->particle_system->CreateParticleGroup( particle_group_def );
	this->particle_system->GetPositionBuffer()[0];
}

void Weapons::particleSingleShot(b2World *world, const sf::Vector2f &player_pos, sf::Vector2i &mouse_pos)
{
	b2ParticleDef particle_def;
	particle_def.lifetime = 0.5;
	particle_def.position.Set( player_pos.x * this->PIXELS_TO_METERS, player_pos.y * -this->PIXELS_TO_METERS );
	particle_def.flags = b2_elasticParticle;

	this->particle_systems[Weapons::TYPE::SINGLE_SHOT]->CreateParticle(particle_def);
	this->particle_systems[Weapons::TYPE::SINGLE_SHOT];
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

vector<b2ParticleSystem *> Weapons::getParticleSystems()
{
	return( this->particle_systems );
}