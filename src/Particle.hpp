#pragma once
#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

#define OUTPUT(x) std::cout << #x"=" << x << std::endl
class Particle : public sf::CircleShape
{
public:
    Particle(const float& radius, const sf::Vector2f& pos, const sf::Vector2f& vel, const float& mass, const float& gravity);

    //Methods
    void updatePosition(const float &dt);

    //Setters
    void setGravity(const float& gravityIn)
    {
        m_gravity = gravityIn;
    }
    void setMass(const float& massIn)
    {
        m_mass = massIn;
    }
    void setVelocity(const sf::Vector2f& velocityIn)
    {
        m_velocity = velocityIn;
    }
    void setWalls(const sf::Vector2u& walls)
    {
        m_walls = walls;
    }

    //Getters
    float getGravity() const
    {
        return m_gravity;
    }
    float getMass() const
    {
        return m_mass;
    }
    sf::Vector2f getVelocity() const
    {
        return m_velocity;
    }
    sf::Vector2u getWalls() const
    {
        return m_walls;
    }

private:

    //Attributes
    float m_mass;
    float m_gravity;
    sf::Vector2f m_velocity;

    //Collision checking attributes
    sf::Vector2u m_walls;

    //Methods
    void CheckCollisions();
};
