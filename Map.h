#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Map
{
public:
	Map();   // �����������
	~Map();  // ����������
	void draw(RenderWindow& window);          // ��������� �������
protected:
	Sprite tile_1;                   // ������
	Texture TextureObject;           // �������� �������
};//