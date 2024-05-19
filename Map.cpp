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

}