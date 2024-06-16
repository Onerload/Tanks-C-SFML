#include <SFML/Graphics.hpp>


using namespace sf;


int main()
{   

    //window
    const unsigned WINDOW_WIDTH = 900;
    const unsigned WINDOW_HEIGHT = 900;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tanks");
    window.setFramerateLimit(10000000);


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
    Vector2f velocity;

    TexturePlayer.loadFromFile("Images/tank1.png");
    RectangleShape player(Vector2f(52, 52));
    player.setTexture(&TexturePlayer);


    //Walls
    //Wall
    std::vector<RectangleShape> walls;

    TextureWall.loadFromFile("Images/texture.png");
    RectangleShape wall(Vector2f(64, 64));
    wall.setTexture(&TextureWall);
    wall.setPosition(500, 500);

    walls.push_back(wall);

    //Collision
    FloatRect nextPos;
    RectangleShape nextBox;
    nextBox.setSize(Vector2f(gridSixe, gridSixe));
    nextBox.setFillColor(Color::Transparent);
    nextBox.setOutlineThickness(1.f);

    //хз
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
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            velocity.y += -movementSpeed * dt;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            velocity.y += movementSpeed * dt;
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            velocity.x += -movementSpeed * dt;
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            velocity.x += movementSpeed * dt;
        }

        //Collision 
        for (auto& wall : walls)
        {
            FloatRect playerBounds = player.getGlobalBounds();
            FloatRect wallBounds = wall.getGlobalBounds();

            nextPos = playerBounds;
            nextPos.left += velocity.x * 30;
            nextPos.top += velocity.y * 30;
            nextBox.setPosition(nextPos.left, nextPos.top);

            if (wallBounds.intersects(nextPos))
            {

            }
        }

        player.move(velocity); 


        //Collision screen
        //Left collision
        if (player.getPosition().x < 0.f)
            player.setPosition(0.f, player.getPosition().y);
        //Top collosoin
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

        for (auto & i : walls)
        {
            window.draw(i);
        }
        
        window.draw(nextBox);

        window.display();
    }













}