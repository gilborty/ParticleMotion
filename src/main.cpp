#include <iostream>
#include <random>
#include <string>
#include <unistd.h>

#include <SFML/Graphics.hpp>
#include "Particle.hpp"

std::random_device randDevice;
std::mt19937 gen(randDevice());

std::uniform_real_distribution<> dist(0,5);
std::uniform_real_distribution<> startingDist(0, 1);

float MapToRange(float valueToBeMapped, float lowInputRange = 0.0, int highInputRange = 600.0, int lowDestRange = 0.0, int highDestRange = 255.0)
{
    return lowDestRange + ( valueToBeMapped - lowInputRange ) * ( highDestRange - lowDestRange ) / ( highInputRange - lowInputRange );
}

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Motion", sf::Style::Default);

    sf::Clock deltaTime;
    float dt = 0.00000001;

    int numberOfParticles = 1000;
    std::vector<Particle> particles;

    for(size_t i = 0; i < numberOfParticles; ++i)
    {
        Position initialPosition;
        Velocity initialVelocity;

        //Get random intial positions
        initialPosition.xPosition = std::round(MapToRange(startingDist(gen),0.0,1.0,0.0,800.0));
        initialPosition.yPosition = std::round(MapToRange(startingDist(gen),0.0,1.0,0.0,600.0));

        //Get random intial velocity
        initialVelocity.xVelocity = MapToRange(startingDist(gen),0.0,1.0,-20.0,20.0);
        initialVelocity.yVelocity = MapToRange(startingDist(gen),0.0,1.0,-20.0,20.0);

        Particle particle(initialPosition, initialVelocity);

        particle.setFillColor(sf::Color(0,0,100));
        auto gravFactor = dist(gen);
        float gravity = static_cast<float>(-9.8*gravFactor);

        particle.setGravity(gravity);

        particle.setWalls(window.getSize());
        particles.push_back(particle);
    }


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
        }

        for(auto& particle : particles)
        {
            particle.updatePosition(dt);
            auto position = particle.getPosition();

            auto redColorValue = MapToRange(position.yPosition);
            particle.setFillColor(sf::Color(redColorValue, 0, 100));

            window.draw(particle.getParticle());
         }

        window.display();

        dt = deltaTime.restart().asSeconds();
    }



    return EXIT_SUCCESS;
}
