﻿#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;

// Структура для хранения свойств снаряда
struct Bullet
{
    CircleShape shape;
    Vector2f velocity;

    Bullet(Vector2f pos, Vector2f vel)
    {
        shape.setPosition(pos);
        shape.setRadius(5.f);
        shape.setFillColor(Color::Red);
        velocity = vel;
    }

    void update(float dt)
    {
        shape.move(velocity * dt);
    }
};

int main()
{
    //window
    const unsigned WINDOW_WIDTH = 900;
    const unsigned WINDOW_HEIGHT = 900;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tanks");
    window.setFramerateLimit(120);

    //icone
    Image icon;
    icon.loadFromFile("Images/icon.jpg");
    window.setIcon(300, 300, icon.getPixelsPtr());

    //хз, переменные мб
    float dt;
    Clock dt_clock;
    Texture TexturePlayer;
    Texture TextureWall;
    Texture Walls;
    const float gridSixe = 50.f;

    //player
    const float movementSpeed = 100.f;
    const float bulletSpeed = 300.f;
    Vector2f velocity;

    Image playerImage;
    playerImage.loadFromFile("Images/Tank.png");
    TexturePlayer.loadFromImage(playerImage);
    Sprite player;
    player.setTexture(TexturePlayer);
    player.setTextureRect(IntRect(0, 0, 52, 52));
    player.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    float time = dt_clock.getElapsedTime().asMicroseconds();
    dt_clock.restart();
    time = time / 800;

    //Walls
    std::vector<RectangleShape> walls;
    TextureWall.loadFromFile("Images/texture.png");
    RectangleShape wall(Vector2f(64, 64));
    wall.setTexture(&TextureWall);
    wall.setPosition(500, 500);
    walls.push_back(wall);

    //Collision
    FloatRect nextPos;

    float CurrentFrame = 0;

    // Вектор для хранения снарядов
    std::vector<Bullet> bullets;

    while (window.isOpen())
    {
        dt = dt_clock.restart().asSeconds();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //Player movement
        velocity.y = 0.f;
        velocity.x = 0.f;

        // Process vertical movement first
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            velocity.y = -movementSpeed * dt;
            player.setTextureRect(IntRect(0, 0, 52, 52));
            CurrentFrame += 0.005f * time;
            if (CurrentFrame > 2) CurrentFrame -= 2;
            player.setTextureRect(IntRect(52 * int(CurrentFrame), 0, 52, 52));
        }
        else if (Keyboard::isKeyPressed(Keyboard::S))
        {
            velocity.y = movementSpeed * dt;
            player.setTextureRect(IntRect(0, 104, 52, 52));
            CurrentFrame += 0.005f * time;
            if (CurrentFrame > 2) CurrentFrame -= 2;
            player.setTextureRect(IntRect(52 * int(CurrentFrame), 104, 52, 52));
        }
        else if (Keyboard::isKeyPressed(Keyboard::A))
        {
            velocity.x = -movementSpeed * dt;
            player.setTextureRect(IntRect(0, 52, 52, 52));
            CurrentFrame += 0.005f * time;
            if (CurrentFrame > 2) CurrentFrame -= 2;
            player.setTextureRect(IntRect(52 * int(CurrentFrame), 52, 52, 52));
        }
        else if (Keyboard::isKeyPressed(Keyboard::D))
        {
            velocity.x = movementSpeed * dt;
            player.setTextureRect(IntRect(0, 156, 52, 52));
            CurrentFrame += 0.005f * time;
            if (CurrentFrame > 2) CurrentFrame -= 2;
            player.setTextureRect(IntRect(52 * int(CurrentFrame), 156, 52, 52));
        }

        // Fire bullet
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            Vector2f bulletPos = player.getPosition();
            Vector2f bulletVel;

            // Определяем направление пули в зависимости от направления движения игрока
            if (velocity.x != 0.f)
                bulletVel = Vector2f((velocity.x > 0 ? 1 : -1) * bulletSpeed, 0.f);
            else if (velocity.y != 0.f)
                bulletVel = Vector2f(0.f, (velocity.
                    y > 0 ? 1 : -1) * bulletSpeed);

            bullets.push_back(Bullet(bulletPos, bulletVel));
        }

        // Update bullets
        for (auto& bullet : bullets)
        {
            bullet.update(dt);
        }

        //Collision 
        {
            FloatRect playerBounds = player.getGlobalBounds();
            FloatRect wallBounds = wall.getGlobalBounds();
            nextPos = playerBounds;
            nextPos.left += velocity.x;
            nextPos.top += velocity.y;

            if (wallBounds.intersects(nextPos))
            {
                //Bottom collision
                if (playerBounds.top < wallBounds.top
                    && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                    && playerBounds.left < wallBounds.left + wallBounds.width
                    && playerBounds.left + playerBounds.width > wallBounds.left)
                {
                    velocity.y = 0.f;
                    player.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                }
                //Top collision
                else if (playerBounds.top > wallBounds.top
                    && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                    && playerBounds.left < wallBounds.left + wallBounds.width
                    && playerBounds.left + playerBounds.width > wallBounds.left)
                {
                    velocity.y = 0.f;
                    player.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                }
                //Right collision
                if (playerBounds.left < wallBounds.left
                    && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                    && playerBounds.top < wallBounds.top + wallBounds.height
                    && playerBounds.top + playerBounds.height > wallBounds.top)
                {
                    velocity.x = 0.f;
                    player.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                }
                //Left collision
                else if (playerBounds.left > wallBounds.left
                    && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                    && playerBounds.top < wallBounds.top + wallBounds.height
                    && playerBounds.top + playerBounds.height > wallBounds.top)
                {
                    velocity.x = 0.f;
                    player.setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
                }
            }
        }
        player.move(velocity);

        //Collision screen
        //Left collision
        if (player.getPosition().x < 0.f)
            player.setPosition(0.f, player.getPosition().y);
        //Top collision
        if (player.getPosition().y < 0.f)
            player.setPosition(player.getPosition().x, 0.f);
        //Right collision 
        if (player.getPosition().x + player.getGlobalBounds().width > WINDOW_WIDTH)
            player.setPosition(WINDOW_WIDTH - player.getGlobalBounds().width, player.getPosition().y);
        //Bottom collision 
        if (player.getPosition().y + player.getGlobalBounds().height > WINDOW_WIDTH)
            player.setPosition(player.getPosition().x, WINDOW_HEIGHT - player.getGlobalBounds().height);

        //Render
        window.clear();
        window.draw(player);

        for (auto& i : walls)
        {
            window.draw(i);
        }

        for (auto& bullet : bullets)
        {
            window.draw(bullet.shape);
        }

        window.display();
    }
}
