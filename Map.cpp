#include"Map.h"
Map::Map()
{
	//1 tile 
	TextureObject.loadFromFile("Images/texture.png");
	RectangleShape tile_1(Vector2f(64, 64)); 
	tile_1.setTexture(&TextureObject);
	tile_1.setPosition(150, 150);
}
Map::~Map()
{

}

	void Map::draw(RenderWindow &window)
	{
		window.draw(tile_1);
	}
