#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

static void printFPS(float deltaTime)
{
    static float consoleTimer = 0.f;
    static int timerCounter = 0;

    consoleTimer += deltaTime;
    timerCounter++;
    if (consoleTimer > 1.f)
    {
        std::cout << "FPS: " << timerCounter / consoleTimer << std::endl;
        consoleTimer = 0.f;
        timerCounter = 0;
    }
}

int main()
{
    RenderWindow window(VideoMode({1200u, 900u}), "CMake SFML Project");
    //window.setFramerateLimit(100);
    
    Game game;
    Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
            else if (const Event::Resized* resized = event->getIf<Event::Resized>())
            {
                window.setSize({ resized->size.y * 4 / 3, resized->size.y });
                clock.restart();
            }
        }

        float deltaTime = clock.restart().asSeconds();
        if (deltaTime > 0.033)  // for when the window hangs when moved
            deltaTime = 0.f;
       
        printFPS(deltaTime);

        game.update(deltaTime);

        window.clear();
        window.draw(game);
        window.display();
    }
}
