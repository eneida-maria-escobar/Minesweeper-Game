#include "texturemanager.h"
map<string, sf::Texture> TextureManager:: textureMap;
Texture& TextureManager::textureGetter(string directory)
{
	if (textureMap.find(directory) == textureMap.end())
	{
		LoadMap(directory);
	}

	return textureMap[directory];
}

void TextureManager::Clear()
{
	textureMap.clear();
}

void TextureManager::LoadMap(string directory)
{
	string path = "";
	path = "files/images/" + directory;
	path += ".png"; // All files must be pngs for this to work. Could take in an argument for other file types if needed
	textureMap[directory].loadFromFile(path);
}
