#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Map
{
	Map();   // �����������
	~Map();  // ����������

	void move(float& time);                   // ����������� �������
	void draw(RenderWindow& window);          // ��������� �������
	void animation();                         // �������� �������
	bool Collision(FloatRect object);       // ������������ � ��������

	Sprite SpaceObject;                   // ������
	Texture TextureObject;                // �������� �������
};