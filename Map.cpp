#include"Map.h"
Map::Map()
{
	//tile
	TextureObject.loadFromFile("Images/Tile_1.png");
	SpaceObject.setTexture(TextureObject);
	RectangleShape Sprite(Vector2f(64, 64));
}
Map::~Map()
{
	//1 tile
	TextureObject.loadFromFile("Images/texture.png");
	RectangleShape tile_1(Vector2f(64, 64));
	tile_1.setTexture(&tile1);
	tile_1.setPosition(100, 0);
	
}