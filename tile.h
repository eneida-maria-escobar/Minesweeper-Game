#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "texturemanager.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;

class Tile
{
public:
	bool debug_enabled;
	bool disabled;
	int neighbor_mine_count;
	bool tile_has_bomb;
	bool tile_is_flagged;
	bool tile_is_revealed;
	
	int tile_index;
	vector<Tile*> neighbors;
	vector<Tile*> neighborsCopy;

	
	int x, y; // Location of tile for display purposes. X and Y coordinates.


	Sprite backgroundOfTile; // Tile revealed
	Sprite overlayOfTile; // Tile hidden

	Sprite image_flag; // Flag icon
	Sprite image_actual; // This is the number or the bomb


	Tile(); // Default constructor. This is not used and is only here from when I first designed the program.
	Tile(bool revealed, float _x, float _y, bool isBomb); // Four argument constructor, this is used in every case. 

	
	bool reveal(int& count);
	void setToggle_Icon_Number(string number);
	void tile_draw_one(sf::RenderWindow& wind);

	bool Toggle_Icon_Flag();
	void printTile();
	void debugTile();

	void Toggle_Icon_Mine();
	void Toggle_Icon_Number();
	

private:
	void printFirst();
};
