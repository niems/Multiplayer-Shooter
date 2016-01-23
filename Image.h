#ifndef IMAGE_H
#define IMAGE_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
using namespace std;

//THIS CLASS ALSO CENTERS SPRITES INSTEAD OF USING THE OBJECT CLASS FOR THAT 


class Image
{
private:
	vector<sf::Texture> player_textures; //all textures associated with the player
	vector<sf::Sprite> player_sprites; //all sprites associated with the player

	vector<sf::Texture> background_textures; //all textures associated with the background
	vector<sf::Sprite> background_sprites; //all sprites associated with the background

	vector<sf::Texture> platform_textures; //all textures associated with platforms
	vector<sf::Sprite> platform_sprites; //all sprites associated with platforms

public:
	//references the textures stored in the vectors
	enum PLAYER{ROBOT_BASE, ROBOT_BODY, ROBOT_NECK, ROBOT_HEAD, ROBOT_ARM};
	enum BACKGROUND{SKY1};
	enum PLATFORM{GROUND};

	Image(); //used to load in all the textures

	vector<sf::Texture>& getPlayerTextures(); //returns the vector of player textures
	vector<sf::Texture>& getBackgroundTextures(); //returns the vector of background textures
	vector<sf::Texture>& getPlatformTextures(); //returns the vector of platform textures

	vector<sf::Sprite>& getPlayerSprites(); //returns the vector of player sprites
	vector<sf::Sprite>& getBackgroundSprites(); //returns the vector of background sprites
	vector<sf::Sprite>& getPlatformSprites(); //returns the vector of platform sprites

	

};


#endif