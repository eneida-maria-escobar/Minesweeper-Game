#include "Tile.h"


Tile::Tile()
{
	tile_has_bomb = false;
	tile_is_revealed = false;
	tile_is_flagged = false;
	debug_enabled = false;
	disabled = false;
	x = 0;
	y = 0;
	tile_index = 0;
}


Tile::Tile(bool revealed, float _x, float _y, bool isBomb)
{

	x = _x;
	y = _y;
	tile_index = 0;

	tile_is_revealed = false;
	tile_has_bomb = isBomb;
	tile_is_flagged = false;
	debug_enabled = false;
	disabled = false;

	overlayOfTile.setTexture(TextureManager::textureGetter("tile_hidden"));
	image_flag.setTexture(TextureManager::textureGetter("flag"));
	backgroundOfTile.setTexture(TextureManager::textureGetter("tile_revealed"));
	

	

}

bool Tile::reveal(int& count)
{

	if (!tile_is_revealed && !tile_is_flagged)
	{
		if(tile_index != -1)
		{
		count += 1;
		tile_is_revealed = true;
		
		Color blank(255, 255, 255, 0);
		overlayOfTile.setColor(sf::Color(255, 255, 255, 0));
		Color filled(255, 255, 255, 255);
		image_actual.setColor(sf::Color(255, 255, 255, 255));
		Color image_actual_color;

		if (neighbor_mine_count == 0 && !tile_has_bomb)
		{
			image_actual_color = image_actual.getColor();
			int neighborCount = 8;
			for (unsigned int i = 0; i < neighborCount; i+=1)
			{
				if (neighbors[i] != nullptr && !neighbors[i]->tile_has_bomb)
				{
					neighbors[i]->reveal(count);
				}
			}
		}

		}

	}
	return tile_has_bomb;
}

void Tile::setToggle_Icon_Number(string number)
{
	string path = "number_";
	path += number;

	image_actual.setTexture(TextureManager::textureGetter(path));

}

void Tile::tile_draw_one(sf::RenderWindow& wind)
{
	backgroundOfTile.setPosition(x, y);

	overlayOfTile.setPosition(x, y);

	image_actual.setPosition(x, y);

	image_flag.setPosition(x, y);

	wind.draw(backgroundOfTile);
	wind.draw(overlayOfTile);
	wind.draw(image_actual);
	wind.draw(image_flag);

}


void Tile::printFirst()
{
	for (int i = 0; i < neighbors.size(); i+=1)
	{
		cout << "Neighbor 0 has bomb: " << neighbors[0]->tile_has_bomb;
		cout << endl;
		cout << "Neighbor 0 has flag: " << neighbors[0]->tile_is_flagged;
		cout << endl;
		cout << "Neighbor 0 debug enabled: " << neighbors[0]->debug_enabled;
		cout << endl;
		cout << "Neighbor 0 is revealed: " << neighbors[0]->tile_is_revealed;
		cout << endl;
		cout << "Neighbor 0 is disabled: " << neighbors[0]->disabled;
	}
}


bool Tile::Toggle_Icon_Flag()
{
	int debug_count = 0;
	if (!tile_is_revealed)//if it isnt revealed. It cannot be flagged if revealed
	{
		if (tile_is_flagged == true)
		{
			tile_is_flagged = false;
			debug_count += 1;
			image_flag.setColor(sf::Color(255, 255, 255, 0));
		}
		else
		{
			tile_is_flagged = true;
			debug_count -= 1;
			image_flag.setColor(sf::Color(255, 255, 255, 255));
		}
	}
	return tile_is_flagged;
}

void Tile::printTile()
{
	cout << "Tile has bomb: " << tile_has_bomb;
	cout << endl;
	cout << "Tile has flag: " << tile_is_flagged;
	cout << endl;
	cout << "Tile debug enabled: " << debug_enabled;
	cout << endl;
	cout << "Tile is revealed: " << tile_is_revealed;
	cout << endl;
	cout << "Tile is disabled: " << disabled;
}



void Tile::Toggle_Icon_Mine()
{
	if (tile_has_bomb && !tile_is_revealed)
	{
		if (debug_enabled)
		{
			debug_enabled = false;
			image_actual.setColor(sf::Color(255, 255, 255, 0));
		}
		else
		{
			debug_enabled = true;
			image_actual.setColor(sf::Color(255, 255, 255, 255));
		}
	}
}

void Tile::debugTile()
{

}

void Tile::Toggle_Icon_Number()
{
	neighbor_mine_count = 0;
	int maximum_neighbors;
	maximum_neighbors = 8;

	for (unsigned int index = 0; index < maximum_neighbors; index+=1)
	{
		if (neighbors[index] != nullptr && neighbors[index]->tile_has_bomb)
		{
			neighbor_mine_count += 1;
		}
	}

	if (!tile_has_bomb)
	{
		switch (neighbor_mine_count)
		{
		case 1:
			if (neighbor_mine_count > 0)
			{
				setToggle_Icon_Number("1");
			}
			break;
		case 2:
			if (neighbor_mine_count > 0)
			{
				setToggle_Icon_Number("2");
			}
			
			break;
		case 3:
			if (neighbor_mine_count > 0)
			{
				setToggle_Icon_Number("3");
			}
			break;
		case 4:
			if (neighbor_mine_count > 0)
			{
				setToggle_Icon_Number("4");
			}
			break;
		case 5:
			if (neighbor_mine_count > 0)
			{
				setToggle_Icon_Number("5");
			}
			break;
		case 6:
			if (neighbor_mine_count > 0)
			{
				setToggle_Icon_Number("6");
			}
			break;
		case 7:
			if (neighbor_mine_count > 0)
			{
				setToggle_Icon_Number("7");
			}
			break;;
		case 8:
			if (neighbor_mine_count > 0)
			{
				setToggle_Icon_Number("8");
			}
			break;
		default:
			//cout << "Something messed up! Neighbor mine count is not being set correctly. Check tile.cpp";
			string revealed_path;
			revealed_path = "tile_revealed";
			image_actual.setTexture(TextureManager::textureGetter(revealed_path));
			if (neighbor_mine_count < 0)
			{
				cout << "Something messed up! Neighbor mine count is not being set correctly. Check tile.cpp";
			}
			break;
		}
	}


}
