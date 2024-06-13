#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Map
{
public:
	 Map();   // конструктор
	~Map();  // Деструктор
	void draw(RenderWindow& window);          // отрисовка объекта
	bool Collision(FloatRect object);       // столкновение с объектом
protected:

	Sprite tile_1;                   // объект
	Texture TextureObject;           // текстура объекта
};