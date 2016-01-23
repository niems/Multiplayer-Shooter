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