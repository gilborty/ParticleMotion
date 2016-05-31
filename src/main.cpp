#include <iostream>
#include <random>
#include <string>
#include <unistd.h>

#include <SFML/Graphics.hpp>
#include "Particle.hpp"

#define BIG_G 6.67e-11

std::random_device randDevice;
std::mt19937 gen(randDevice());
std::uniform_real_distribution<> dist(0,5);

float MapToRange(float valueToBeMapped, float lowInputRange = 0.0, int highInputRange = 600.0, int lowDestRange = 0.0, int highDestRange = 255.0)
{
    return lowDestRange + ( valueToBeMapped - lowInputRange ) * ( highDestRange - lowDestRange ) / ( highInputRange - lowInputRange );
}

float CalculateGravitationalForce(const float& massOne, const float& massTwo, const float& radius)
{
    return BIG_G * ((massOne - massTwo)/std::pow(radius,2));
}

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Motion", sf::Style::Default);

    sf::Clock deltaTime;
    float dt = 0.00000001;

    Particle blackHole;
    blackHole.setMass(1e14);
    blackHole.setRadius(10.0);
    blackHole.setFillColor(sf::Color::Black);
    blackHole.setOutlineColor(sf::Color::Black);
    blackHole.setPosition({window.getSize().x/2.0,window.getSize().y/2.0});

    Particle body;

    while(window.isOpen())
    {
        window.clear(sf::Color::White);

        //Handle events
        sf::Event event;
        while(window.pollEvent(event))
        {
            //Window closed or escape key pressed: Exit
            if((event.type == sf::Event::Closed) or
                    ((event.type == sf::Event::KeyPressed) and (event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                Position updatedPos;
                updatedPos.xPosition = blackHole.getPosition().xPosition - 10;
                updatedPos.yPosition = blackHole.getPosition().yPosition;
                blackHole.setPosition(updatedPos);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                Position updatedPos;
                updatedPos.xPosition = blackHole.getPosition().xPosition + 10;
                updatedPos.yPosition = blackHole.getPosition().yPosition;
                blackHole.setPosition(updatedPos);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                Position updatedPos;
                updatedPos.yPosition = blackHole.getPosition().yPosition - 10;
                updatedPos.xPosition = blackHole.getPosition().xPosition;
                blackHole.setPosition(updatedPos);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                Position updatedPos;
                updatedPos.yPosition = blackHole.getPosition().yPosition + 10;
                updatedPos.xPosition = blackHole.getPosition().xPosition;
                blackHole.setPosition(updatedPos);
            }
        }

        Force newForce;

        auto radiusX = std::abs(body.getPosition().xPosition - blackHole.getPosition().xPosition);
        auto radiusY = std::abs(body.getPosition().yPosition - blackHole.getPosition().yPosition);

        auto newForceX = -CalculateGravitationalForce(body.getMass(), blackHole.getMass(), radiusX);
        auto newForceY = -CalculateGravitationalForce(body.getMass(), blackHole.getMass(), radiusY);

        newForce = {newForceX, newForceY};

        body.updatePosition(newForce, dt);

        window.draw(body.getParticle());
        window.draw(blackHole.getParticle());

        window.display();

        dt = deltaTime.restart().asSeconds();
    }



    return EXIT_SUCCESS;
}
