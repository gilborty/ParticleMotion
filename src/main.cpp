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

const float STARTING_VEL = 100.0;


float MapToRange(float valueToBeMapped, float lowInputRange = 0.0, int highInputRange = 600.0, int lowDestRange = 0.0, int highDestRange = 255.0)
{
    return lowDestRange + ( valueToBeMapped - lowInputRange ) * ( highDestRange - lowDestRange ) / ( highInputRange - lowInputRange );
}

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Motion", sf::Style::Default);

    sf::Clock deltaTime;
    float dt = 0.00000001;

    int numberOfParticles = 100;
    std::vector<Particle> particles;

    for(size_t i = 0; i < numberOfParticles; ++i)
    {
        //Set the radius
        auto radius = MapToRange(startingDist(gen), 0.0, 1.0, 1.0, 5.0);

        //Get random intial positions
        sf::Vector2f initialPosition;
        initialPosition.x = std::round(MapToRange(startingDist(gen),0.0,1.0,0.0,800.0));
        initialPosition.y = std::round(MapToRange(startingDist(gen),0.0,1.0,0.0,600.0));

        //Get random intial velocity
        sf::Vector2f initialVelocity;
        initialVelocity.x = MapToRange(startingDist(gen),0.0,1.0,-STARTING_VEL,STARTING_VEL);
        initialVelocity.y = MapToRange(startingDist(gen),0.0,1.0,-STARTING_VEL,STARTING_VEL);

        //Set the mass of the particle
        auto mass = 10.0;

        //Set the gravity
        auto gravFactor = dist(gen);
        float gravity = static_cast<float>(-9.8*gravFactor);

        //Create the particle
        Particle particle(radius, initialPosition, initialVelocity, mass, gravity);

        particle.setFillColor(sf::Color(0,0,100));
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

            auto redColorValue = MapToRange(position.y);
            particle.setFillColor(sf::Color(redColorValue, 0, 100));

            window.draw(particle);
         }

        window.display();

        dt = deltaTime.restart().asSeconds();
    }



    return EXIT_SUCCESS;
}
