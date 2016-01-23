#ifndef DRAW_H
#define DRAW_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Weapons.h"
#include <vector>
using namespace std;


 
class Draw
{
public:
	static void drawParticles( sf::RenderWindow &window, vector<Projectile> &particles );

	static void drawSingleShotProjectiles( sf::RenderWindow &window, vector<Projectile *> projectiles, vector<sf::CircleShape *> shapes );
};

#endif