#include <iostream>
#include <random>
#include <string>
#include <unistd.h>

#include <SFML/Graphics.hpp>
#include "Particle.hpp"

std::random_device randDevice;
std::mt19937 gen(randDevice());
std::uniform_real_distribution<> dist(0,5);

float MapToRange(float valueToBeMapped, float lowInputRange = 0.0, int highInputRange = 600.0, int lowDestRange = 0.0, int highDestRange = 255.0)
{
    return lowDestRange + ( valueToBeMapped - lowInputRange ) * ( highDestRange - lowDestRange ) / ( highInputRange - lowInputRange );
}

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Motion", sf::Style::Default);

    sleep(25);
    sf::Clock deltaTime;
    float dt = 0.00000001;

    int numberOfParticles = 800;
    int imageCounter = 0;

    std::vector<Particle> particles;

    for(size_t i = 0; i < numberOfParticles; ++i)
    {

        Particle particle;
        Position initialPosition;

        initialPosition.xPosition = (window.getSize().x / numberOfParticles)*i;
        initialPosition.yPosition = 0.0f;
        particle.setPosition(initialPosition);

        particle.setFillColor(sf::Color(0,0,100));
        auto gravFactor = dist(gen);
        float gravity = static_cast<float>(-9.8*gravFactor);

        particle.setGravity(gravity);

        particles.push_back(particle);
    }

    while(window.isOpen())
    {
        window.clear(sf::Color::White);
        ++imageCounter;

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
        
        //sf::Image image = window.capture();
        //std::string imagePath = "images/image" + std::to_string(imageCounter) + ".jpg";
        //image.saveToFile(imagePath);

        dt = deltaTime.restart().asSeconds();
    }



    return EXIT_SUCCESS;
}
