#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include "Object.h"
#include "Actor.h"
#include "Timer.h"

using namespace std;

const float PIXELS_TO_METERS = 0.03333; //number of meters in one pixel
const float METERS_TO_PIXELS = 30.0; //number of pixels in one meter

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

enum {STATIC, DYNAMIC, KINEMATIC}; //determines which type of box2d object to create
enum {POLY_SHAPE, CIRCLE_SHAPE}; //determines which type of box2d shape to create

void updatePosition(b2Body *body, sf::Sprite *sprite_body); //updates the position of the sprite
void background(sf::RenderWindow &window, sf::Sprite &tile, sf::Vector2u &window_size, sf::Vector2i &background_source, sf::Vector2i &tile_size);

int main()
{
    sf::RenderWindow window( sf::VideoMode(1440, 900), "Shooter" );
	sf::Vector2u window_size = sf::Vector2u(window.getSize().x, window.getSize().y);
	window.setFramerateLimit(60);

	//////WORLD SETUP////////////////////
	b2Vec2 gravity(0, -18.0);
	b2World *world = new b2World(gravity);

	float32 timeStep = 1 / 60.0; //the length of time passed to simulate in seconds
	int32 velocity_iterations = 8; //how strongly to correct velocity
	int32 position_iterations = 3; //how strongly to correct position

	/////END WORLD SETUP/////////////////



	///////BACKGROUND SETUP///////////////////////
	sf::Vector2i background_source(0, 0);

	sf::Texture background_texture;
	sf::Sprite background_sprite;
	sf::Vector2i background_tile_size;

	if(!background_texture.loadFromFile("images//sky2.png") )
	{
		cout << "ERROR: grid.png unable to load. Line: " << __LINE__ << endl;
		window.close();
	}

	else
	{
		background_sprite.setTexture(background_texture);
		background_tile_size = sf::Vector2i(background_texture.getSize().x, background_texture.getSize().y);
	}
	///////////END BACKGROUND SETUP///////////////////////////

	//NEW PLAYER SETUP////////////////////////////
	sf::Texture player_base_texture;
	sf::Texture player_body_texture;
	b2FixtureDef player_fixture;
	b2FixtureDef player_body_fixture;

	player_fixture.density = 1;
	player_fixture.friction = 0.5;
	player_fixture.restitution = 0;

	player_body_fixture.density = 0.01;
	player_body_fixture.restitution = 0;

	if( !player_base_texture.loadFromFile("images//wheel6.png") )
	{
		cout << "Failed to load player base texture on line: " << __LINE__ << endl;
	}

	if( !player_body_texture.loadFromFile("images//robot_head.png") )
	{
		cout << "Failed to load player body texture on line: " << __LINE__ << endl;
	}

	Actor player(window, world, player_fixture, player_base_texture, -1, DYNAMIC, CIRCLE_SHAPE);
	player.getEntity()->getBody()->SetTransform( b2Vec2( (window_size.x / 2.0) * PIXELS_TO_METERS, -100 * PIXELS_TO_METERS ), 0 );
	player.getEntity()->getBody()->SetAngularVelocity( 100 * PIXELS_TO_METERS );

	player.createActorBody( window, world, player_body_fixture, player_body_texture, -1, DYNAMIC, POLY_SHAPE );


	//END NEW PLAYER SETUP////////////////////////

	//NEW GROUND SETUP///////////////////////////
	sf::Texture ground_texture;
	b2FixtureDef ground_fixture;

	ground_fixture.density = 1;
	ground_fixture.friction = 0.3;
	ground_fixture.restitution = 0.3;

	if( !ground_texture.loadFromFile("images//ground.png") )
	{
		cout << "Failed to load ground texture on line: " << __LINE__ << endl;
	}

	Object ground_object(window, world, ground_fixture, ground_texture, -1, STATIC, POLY_SHAPE);
	ground_object.getBody()->SetTransform( b2Vec2( (window_size.x / 2.0) * PIXELS_TO_METERS, -(window_size.y / 1.5) * PIXELS_TO_METERS ), 0 );
	ground_object.updateSpritePos();

	//END NEW GROUND SETUP///////////////////////

	

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.setSize( sf::Vector2u(window.getSize().x / 2.0, window.getSize().y / 2.0) ); // D:

			else if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
				window.close();
        }

		world->Step( timeStep, velocity_iterations, position_iterations );

		//update clocks
		
		player.playerUpdate(); //updates everything to do with the player
		

		//draw to display
		window.clear();

        //tile background
		background(window, background_sprite, window_size, background_source, background_tile_size);

		//draw ground
		window.draw( *ground_object.getSprite() );

		//draw player
		window.draw( *player.getEntity()->getSprite() );
		window.draw( *player.getEntityBody()->getSprite() );
		

        window.display();
    }

    return 0;
}

void updatePosition(b2Body *body, sf::Sprite *sprite_body)
{
	sprite_body->setPosition( body->GetPosition().x * METERS_TO_PIXELS, -body->GetPosition().y * METERS_TO_PIXELS );
	sprite_body->setRotation( body->GetAngle() * -RADTODEG );
}

void background(sf::RenderWindow &window, sf::Sprite &tile, sf::Vector2u &window_size, sf::Vector2i &background_source, sf::Vector2i &tile_size)
{
	for(background_source.y = 0; background_source.y < window_size.y; background_source.y += tile_size.y)
	{
		for(background_source.x = 0; background_source.x < window_size.x; background_source.x += tile_size.x)
		{
			tile.setPosition( background_source.x, background_source.y );
			window.draw( tile );
		}
	}
}