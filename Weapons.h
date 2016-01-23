#ifndef WEAPONS_H
#define WEAPONS_H

#include <Box2D\Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
using namespace std;

//float PIXELS_TO_METERS = 0.03333; //number of meters in one pixel
//float METERS_TO_PIXELS = 30.0; //number of pixels in one meter

struct Projectile
{
	//sf::CircleShape shape; //circle shape used with the projectile type
	int type; //determines which shape is outputted when drawn
	b2Body *particle_body; 
	sf::Vector2f velocity;
	//maybe have one particle group per projectile. After this is implemented, the vector 'shape' won't be needed.
};

//DON'T PUT A SHAPE INSIDE THE PROJECTILE CLASS. PUT A TYPE AND USE THE TYPE TO DETERMINE WHICH SHAPE TO USE
//WITH THE VECTOR SHAPE MEMBER VARIABLE
class Weapons
{
private:
	Projectile temp_projectile;
	//weapon type lifetime
	//particle system type
	vector<sf::CircleShape *> shape; //one shape per TYPE of weapon
	vector<float> max_effect_duration; //the longest amount of time the effect will last before being destroyed

	b2ParticleSystem *particle_system; //all the particle effects run in this particle system

	//one vector per projectile type that stores all the box2d bodies from the projectile class
	//vector<b2Body *> particles_single_shot;
	vector<Projectile *> projectile_single_shot;
	
	//since the projectile class has only one member variable, it might make sense just to create the
	//b2body* inside this class and forget the projectile class for now.																														
	

public:
	float PIXELS_TO_METERS; //number of meters in one pixel
	float METERS_TO_PIXELS; //number of pixels in one meter

	enum TYPE{ SINGLE_SHOT };

	enum entity_category{
	PLAYER = 0x0001,
	BOUNDARY = 0x0002,
	PLAYER_WEAPON = 0x0004,
	ENEMY_WEAPON = 0x0008,
	};

	//Weapons(); //not used
	Weapons(b2World *world);

	//create particles
	//void singleShot(b2World *world, const b2Vec2 &pos); //creates this projectile particle group

	//uses angle to fire projectile
	void singleShot(b2World *world, const sf::Vector2f &player_pos, sf::Vector2i &mouse_pos);

	//update particles
	void updateSingleShot();

	vector<Projectile *> getSingleShotProjectile();
	vector<sf::CircleShape *> getParticleShapes();

	


};

#endif