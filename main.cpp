#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include "Object.h"
#include "Image.h"
#include "Actor.h"
#include "Timer.h"

using namespace std;

const float PIXELS_TO_METERS = 0.03333; //number of meters in one pixel
const float METERS_TO_PIXELS = 30.0; //number of pixels in one meter

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

enum {STATIC, DYNAMIC, KINEMATIC}; //determines which type of box2d object to create
enum {POLY_SHAPE, CIRCLE_SHAPE}; //determines which type of box2d shape to create

enum entity_category{
	PLAYER = 0x0001,
	BOUNDARY = 0x0002,
};

void updatePosition(b2Body *body, sf::Sprite *sprite_body); //updates the position of the sprite
void background(sf::RenderWindow &window, sf::Sprite &tile, sf::Vector2u &window_size, sf::Vector2i &background_source, sf::Vector2i &tile_size);

int main()
{
    sf::RenderWindow window( sf::VideoMode(1440, 900), "Shooter" );
	sf::Vector2u window_size = sf::Vector2u(window.getSize().x, window.getSize().y);
	window.setFramerateLimit(60);

	Image images; //loads all textures and sprites

	//////WORLD SETUP////////////////////
	b2Vec2 gravity(0, -18.0);
	b2World *world = new b2World(gravity);

	float32 timeStep = 1 / 60.0; //the length of time passed to simulate in seconds
	int32 velocity_iterations = 8; //how strongly to correct velocity
	int32 position_iterations = 3; //how strongly to correct position

	/////END WORLD SETUP/////////////////



	///////BACKGROUND SETUP///////////////////////
	sf::Vector2i background_source(0, 0);
	sf::Vector2i background_tile_size = sf::Vector2i( images.getBackgroundTextures()[Image::BACKGROUND::SKY1].getSize().x, images.getBackgroundTextures()[Image::BACKGROUND::SKY1].getSize().y );

	cout << "background.x: " << background_tile_size.x << endl;
	cout << "background.y: " << background_tile_size.y << endl;

	///////////END BACKGROUND SETUP///////////////////////////

	//NEW PLAYER SETUP////////////////////////////
<<<<<<< HEAD
	sf::Texture player_base_texture;
	sf::Texture player_body_texture;
	sf::Texture player_head_texture;
	sf::Texture player_neck_texture1;
	sf::Texture player_neck_texture2;

=======
>>>>>>> player_body
	b2FixtureDef player_fixture;
	b2FixtureDef player_body_fixture;

	player_fixture.filter.categoryBits = entity_category::PLAYER;
	player_fixture.filter.maskBits = entity_category::BOUNDARY;
	player_fixture.density = 1;
	player_fixture.friction = 0.5;
	player_fixture.restitution = 0;

	player_body_fixture.filter.categoryBits = entity_category::PLAYER;
	player_body_fixture.filter.maskBits = entity_category::BOUNDARY;
	player_body_fixture.density = 0.01;
	player_body_fixture.restitution = 0;

<<<<<<< HEAD
	if( !player_base_texture.loadFromFile("images//wheel6.png") )
	{
		cout << "Failed to load player base texture on line: " << __LINE__ << endl;
	}

	if( !player_body_texture.loadFromFile("images//robot_body.png") )
	{
		cout << "Failed to load player body texture on line: " << __LINE__ << endl;
	}

	if( !player_head_texture.loadFromFile("images//robot_head.png") )
	{
		cout << "Failed to load player head texture on line: " << __LINE__ << endl;
	}

	if( !player_neck_texture1.loadFromFile("images//robot_neck1.png") )
	{
		cout << "Failed to load player neck disk 1 texture on line: " << __LINE__ << endl;
	}

	if( !player_neck_texture2.loadFromFile("images//robot_neck2.png") )
	{
		cout << "Failed to load player neck disk 2 texture on line: " << __LINE__ << endl;
	}

	Actor player(window, world, player_fixture, player_base_texture, -1, DYNAMIC, CIRCLE_SHAPE);
	player.getEntity()->getBody()->SetTransform( b2Vec2( (window_size.x / 2.0) * PIXELS_TO_METERS, -100 * PIXELS_TO_METERS ), 0 );
	player.getEntity()->getBody()->SetAngularVelocity( 50 * PIXELS_TO_METERS );

	//player.createActorBody( window, world, player_body_fixture, player_head_texture, -1, DYNAMIC, POLY_SHAPE );
=======
	Actor player(window, world, player_fixture, images.getPlayerTextures()[Image::PLAYER::ROBOT_BASE], -1, DYNAMIC, CIRCLE_SHAPE);
	player.getRobotBase()->getBody()->SetTransform( b2Vec2( (window_size.x / 2.0) * PIXELS_TO_METERS, -100 * PIXELS_TO_METERS ), 0 );
	player.getRobotBase()->getBody()->SetAngularVelocity( -500 * PIXELS_TO_METERS );
>>>>>>> player_body

	player.createRobotBody( window, world, player_body_fixture, images.getPlayerTextures()[Image::PLAYER::ROBOT_BODY], -1, DYNAMIC, POLY_SHAPE );
	player.createRobotHead( window, world, player_body_fixture, images.getPlayerTextures()[Image::PLAYER::ROBOT_HEAD], -1, DYNAMIC, POLY_SHAPE );
	player.createRobotArm( window, world, player_body_fixture, images.getPlayerTextures()[Image::PLAYER::ROBOT_ARM], images.getPlayerTextures()[Image::ROBOT_BODY], -1, DYNAMIC, POLY_SHAPE );

	//END NEW PLAYER SETUP////////////////////////

	//NEW GROUND SETUP///////////////////////////
	b2FixtureDef ground_fixture;

	ground_fixture.filter.categoryBits = entity_category::BOUNDARY;
	ground_fixture.filter.maskBits = entity_category::PLAYER;
	ground_fixture.density = 1;
	ground_fixture.friction = 0.3;
	ground_fixture.restitution = 0.3;		

	Object ground_object(window, world, ground_fixture, images.getPlatformTextures()[Image::PLATFORM::GROUND], -1, STATIC, POLY_SHAPE);
	ground_object.getBody()->SetTransform( b2Vec2( (window_size.x / 2.0) * PIXELS_TO_METERS, -(window_size.y / 1.5) * PIXELS_TO_METERS ), 0 );
	ground_object.updateSpritePos();

	//END NEW GROUND SETUP///////////////////////

	Timer damage_clock;
	

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
		damage_clock.update();
		
		player.playerUpdate(window); //updates everything to do with the player


		if( damage_clock.getElapsedTime() >= 0.1 )
		{
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::R ) )
			{
				player.getHealthBar()->damage(10);
				damage_clock.restartClock();
			}

			else if( sf::Keyboard::isKeyPressed( sf::Keyboard::T ) )
			{
				player.getHealthBar()->heal(10);
				damage_clock.restartClock();
			}
		}
		
		

		//draw to display
		window.clear( sf::Color(150, 150, 150) );

        //tile background
		background(window, images.getBackgroundSprites()[Image::BACKGROUND::SKY1], window_size, background_source, background_tile_size);

		//draw ground
		window.draw( *ground_object.getSprite() );

		//draw player
<<<<<<< HEAD
		window.draw( *player.getEntity()->getSprite() );
		//window.draw( *player.getEntityBody()->getSprite() );
=======
		//window.draw( *player.getRobotNeck()->getSprite() );
		window.draw( *player.getRobotBase()->getSprite() );
		window.draw( *player.getRobotBody()->getSprite() );
		window.draw( *player.getRobotHead()->getSprite() );
		window.draw( *player.getRobotArm()->getSprite() );

		window.draw( *player.getHealthBar()->getBar() );
		
>>>>>>> player_body
		

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