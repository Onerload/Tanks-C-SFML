#include <SFML/Graphics.hpp>
#include "Header.h"

using namespace sf;

int main()
{
    int Map();
    //tank
    Vector2f posPlayer;
    Vector2f moveRec;
    Texture texplayer;
    texplayer.loadFromFile("Images/tank1.png");
    RectangleShape player(Vector2f(52, 52));
    player.setTexture(&texplayer);
    player.setPosition(0, 0);
    RenderWindow window(VideoMode(900, 900), "Tanks");

    //icone
    Image icon;
    icon.loadFromFile("Images/icon.jpg");
    window.setIcon(300, 300, icon.getPixelsPtr());

    Clock clock;
    float time, timePlayer;

   
    while (window.isOpen())
    {
        Event event;
        time = clock.getElapsedTime().asMicroseconds();
        timePlayer = time / 60000;
        clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            switch (event.type)
            {
            case Event::KeyPressed:
                if (event.key.code == Keyboard::W) moveRec.y = -timePlayer;
                if (event.key.code == Keyboard::S) moveRec.y = timePlayer;
                if (event.key.code == Keyboard::A) moveRec.x = -timePlayer;
                if (event.key.code == Keyboard::D) moveRec.x = timePlayer;
                break;
            case Event::KeyReleased:
                if (event.key.code == Keyboard::W) moveRec.y = 0;
                if (event.key.code == Keyboard::S) moveRec.y = 0;
                if (event.key.code == Keyboard::A) moveRec.x = 0;
                if (event.key.code == Keyboard::D) moveRec.x = 0;

            default:
                break;
            }
        }
        player.move(moveRec);
        posPlayer = player.getPosition();
        if (posPlayer.x > 848) player.setPosition(848, posPlayer.y);
        if (posPlayer.x < 0) player.setPosition(50, posPlayer.y);
        if (posPlayer.y > 848) player.setPosition(posPlayer.x, 848);
        if (posPlayer.y < 0) player.setPosition(posPlayer.x, 0);

        if ((posPlayer.x > 848) && (posPlayer.y > 848)) player.setPosition(848, 848);
        if ((posPlayer.x > 848) && (posPlayer.y < 50)) player.setPosition(848, 50);
        if ((posPlayer.x < 0) && (posPlayer.y > 848)) player.setPosition(0, 848);
        if ((posPlayer.x < 0) && (posPlayer.y < 50)) player.setPosition(0, 0);
        window.clear();
        window.draw(tile_1);
        window.draw(player);
        window.display();
    }

    return 0;
}