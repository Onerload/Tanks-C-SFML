#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Map
{
	Map();   // конструктор
	~Map();  // Деструктор

	void move(float& time);                   // перемещение объекта
	void draw(RenderWindow& window);          // отрисовка объекта
	void animation();                         // анимация объекта
	bool Collision(FloatRect object);       // столкновение с объектом

	Sprite SpaceObject;                   // объект
	Texture TextureObject;                // текстура объекта
};