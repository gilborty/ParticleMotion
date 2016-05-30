#pragma once

#include <SFML/Graphics.hpp>

struct Position
{
    float xPosition;
    float yPosition;
};

struct Velocity
{
    float xVelocity;
    float yVelocity;
};

class Particle
{
public:

    Particle();

    void updatePosition(const float& dt);


    void setMass(const float& massIn)
    {
        m_mass = massIn;
    }

    void setPosition(const Position& positionIn)
    {
        m_position = positionIn;
    }

    void setOutlineThickness(const float& outlineThicknessIn)
    {
        m_outlineThickness = outlineThicknessIn;
    }

    void setRadius(const float& radiusIn)
    {
        m_radius = radiusIn;
    }

    void setOutlineColor(const sf::Color& outlineColorIn)
    {
        m_outlineColor = outlineColorIn;
    }

    void setFillColor(const sf::Color& fillColorIn)
    {
        m_fillColor = fillColorIn;
        m_particle.setFillColor(m_fillColor);
    }

    void setVelocity(const Velocity& velocityIn)
    {
        m_velocity = velocityIn;
    }

    void setGravity(const float& gravityIn)
    {
        m_gravity = gravityIn;
    }

    sf::CircleShape getParticle() const
    {
        return m_particle;
    }

    Position getPosition() const
    {
        return m_position;
    }


private:
    float m_gravity;
    float m_radius;
    float m_mass;
    Position m_position;
    Velocity m_velocity;

    sf::CircleShape m_particle;

    float m_outlineThickness;
    sf::Color m_outlineColor;
    sf::Color m_fillColor;
};
