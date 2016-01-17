#ifndef WEAPONS_H
#define WEAPONS_H

#include <Box2D\Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

struct Gun
{
	sf::CircleShape shape; //circle shape used with the projectile type
	b2Body *particle_body; 
};

class Weapons
{
private:
	//weapon type lifetime
	//particle system type
	vector<sf::CircleShape> shape; //one shape per TYPE of weapon
	vector<float> max_effect_duration; //the longest amount of time the effect will last before being destroyed

	b2ParticleSystem *particle_system; //all the particle effects run in this particle system

	//one vector per projectile type that stores all the box2d bodies from the projectile class
	//vector<b2Body *> particles_single_shot;
	vector<Gun> projectile_single_shot;
	
	//since the projectile class has only one member variable, it might make sense just to create the
	//b2body* inside this class and forget the projectile class for now.																														
	

public:
	enum TYPE{ SINGLE_SHOT };

	Weapons(b2World *world);

	void singleShot(); //creates this projectile particle group




};

#endif