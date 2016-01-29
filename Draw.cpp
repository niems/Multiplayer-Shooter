#include "Draw.h"

const float PIXELS_TO_METERS = 0.03333; //number of meters in one pixel
const float METERS_TO_PIXELS = 30.0; //number of pixels in one meter
 
void Draw::drawParticles( sf::RenderWindow &window, vector<Projectile> &particles ) //draws all particles of the current type
{
	for( int i = 0; i < particles.size(); i++ )
	{
		if( particles[i].type == Weapons::TYPE::SINGLE_SHOT )
		{
			
		}
	}
}

void Draw::drawSingleShotProjectiles( sf::RenderWindow &window, vector<Projectile *> projectiles, vector<sf::CircleShape *> shapes )
{
	for( int i = 0; i < projectiles.size(); i++ )
	{
		shapes[Weapons::TYPE::SINGLE_SHOT]->setPosition( projectiles[i]->particle_body->GetPosition().x * METERS_TO_PIXELS, projectiles[i]->particle_body->GetPosition().y * -METERS_TO_PIXELS );
		window.draw( *( shapes[Weapons::TYPE::SINGLE_SHOT] ) );
	}
}

void Draw::drawSingleShotParticles( sf::RenderWindow &window, vector<b2ParticleSystem *> particle_systems, vector<sf::CircleShape *> shapes )
{
	//shapes[Weapons::TYPE::SINGLE_SHOT]->setRadius( particle_systems[Weapons::TYPE::SINGLE_SHOT]->GetRadius() * METERS_TO_PIXELS );

	b2Vec2 pos;
	for( int i = 0; i < particle_systems[Weapons::TYPE::SINGLE_SHOT]->GetParticleCount(); i++ )
	{
		pos = particle_systems[Weapons::TYPE::SINGLE_SHOT]->GetPositionBuffer()[i];

		if( &pos != NULL )
		{
			shapes[Weapons::TYPE::SINGLE_SHOT]->setPosition( pos.x * METERS_TO_PIXELS, pos.y * -METERS_TO_PIXELS );
			window.draw( *shapes[Weapons::TYPE::SINGLE_SHOT] );
		}
		
	}
}