#include "Image.h"


Image::Image()
{
	//LOADS ALL PLAYER TEXTURES////////////////////////////////////////
	sf::Texture robot_base_texture;
	sf::Sprite robot_base_sprite;

	sf::Texture robot_body_texture;
	sf::Sprite robot_body_sprite;

	sf::Texture robot_neck_texture;
	sf::Sprite robot_neck_sprite;

	sf::Texture robot_neck_texture2;
	sf::Sprite robot_neck_sprite2;

	sf::Texture robot_head_texture;
	sf::Sprite robot_head_sprite;

	sf::Texture robot_arm_texture;
	sf::Sprite robot_arm_sprite;

	if( !robot_base_texture.loadFromFile("images//wheel8.png") )
	{
		cout << "Failed to load robot base texture on line: " << __LINE__ << endl;
	}

	this->player_textures.push_back( robot_base_texture );	
	robot_base_sprite.setTexture( this->player_textures.back() );
	robot_base_sprite.setOrigin( this->player_textures.back().getSize().x / 2.0, this->player_textures.back().getSize().y / 2.0 );
	this->platform_sprites.push_back( robot_base_sprite );


	if( !robot_body_texture.loadFromFile("images//robot_body14.png") )
	{
		cout << "Failed to load robot body texture on line: " << __LINE__ << endl;
	}

	this->player_textures.push_back( robot_body_texture );	
	robot_body_sprite.setTexture( this->player_textures.back() );
	robot_body_sprite.setOrigin( this->player_textures.back().getSize().x / 2.0, this->player_textures.back().getSize().y / 2.0 );
	this->player_sprites.push_back( robot_body_sprite );


	if( !robot_neck_texture.loadFromFile("images//robot_neck1.png") )
	{
		cout << "Failed to load robot neck 1 texture on line: " << __LINE__ << endl;
	}

	this->player_textures.push_back( robot_neck_texture );
	robot_neck_sprite.setTexture( this->player_textures.back() );
	robot_neck_sprite.setOrigin( this->player_textures.back().getSize().x / 2.0, this->player_textures.back().getSize().y / 2.0 ); 
	this->player_sprites.push_back( robot_neck_sprite );

	if( !robot_head_texture.loadFromFile("images//robot_head3.png") )
	{
		cout << "Failed to load robot head texture on line: " << __LINE__ << endl;
	}

	this->player_textures.push_back( robot_head_texture );
	robot_head_sprite.setTexture( this->player_textures.back() );
	robot_head_sprite.setOrigin( this->player_textures.back().getSize().x / 2.0, this->player_textures.back().getSize().y / 2.0 );
	this->player_sprites.push_back( robot_head_sprite );	

	if( !robot_arm_texture.loadFromFile("images//robot_arm6.png") )
	{
		cout << "Failed to load robot arm texture on line: " << __LINE__ << endl;
	}

	this->player_textures.push_back( robot_arm_texture );
	robot_arm_sprite.setTexture( this->player_textures.back() );
	robot_arm_sprite.setOrigin( this->player_textures.back().getSize().x / 2.0, 0.0 ); //top middle of sprite
	this->player_sprites.push_back( robot_arm_sprite );

	////////////////////////////////////////////////////////////////////////


	//LOADS ALL BACKGROUND TEXTURES/////////////////////////////////////////
	sf::Texture sky_texture1;
	sf::Sprite sky_sprite1;

	if( !sky_texture1.loadFromFile("images//sky2.png") )
	{
		cout << "Failed to load sky1 texture on line: " << __LINE__ << endl;
	}

	this->background_textures.push_back( sky_texture1 );
	sky_sprite1.setTexture( this->background_textures.back() );
	//sky_sprite1.setOrigin( sky_texture1.getSize().x / 2.0, sky_texture1.getSize().y / 2.0 );
	this->background_sprites.push_back( sky_sprite1 );

	///////////////////////////////////////////////////////////////////////////


	//LOADS ALL PLATFORM TEXTURES////////////////////////////////////////////
	sf::Texture ground_texture1;
	sf::Sprite ground_sprite1;

	if( !ground_texture1.loadFromFile("images//ground.png") )
	{
		cout << "Failed to load ground texture 1 on line: " << __LINE__ << endl;
	}

	this->platform_textures.push_back( ground_texture1 );
	ground_sprite1.setTexture( this->platform_textures.back() );
	ground_sprite1.setOrigin( this->platform_textures.back().getSize().x / 2.0, this->platform_textures.back().getSize().y / 2.0 );
	this->platform_sprites.push_back( ground_sprite1 );

	/////////////////////////////////////////////////////////////////////////

}

vector<sf::Texture>& Image::getPlayerTextures()
{
	return( this->player_textures );
}

vector<sf::Texture>& Image::getBackgroundTextures()
{
	return( this->background_textures );
}

vector<sf::Texture>& Image::getPlatformTextures()
{
	return( this->platform_textures );
}


vector<sf::Sprite>& Image::getPlayerSprites()
{
	return( this->player_sprites );
}

vector<sf::Sprite>& Image::getBackgroundSprites()
{
	return( this->background_sprites );
}

vector<sf::Sprite>& Image::getPlatformSprites()
{
	return( this->platform_sprites );
}