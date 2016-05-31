#include "Particle.hpp"


Particle::Particle()
    : m_radius(3.0)
    , m_mass(10.0)
    , m_position{}
    , m_velocity{}
    , m_gravity(-9.8)
    , m_outlineThickness(0.0)
    , m_outlineColor(sf::Color::Blue)
    , m_fillColor(sf::Color::Blue)
    , m_particle(m_radius)
{
    m_particle.setOutlineThickness(m_outlineThickness);
    m_particle.setOutlineColor(m_outlineColor);
    m_particle.setFillColor(m_fillColor);
    m_particle.setOrigin(m_position.xPosition, m_position.yPosition);
}

void Particle::updatePosition(const float &dt)
{
    m_position.xPosition = m_position.xPosition + (m_velocity.xVelocity*dt);
    m_position.yPosition = m_position.yPosition + (m_velocity.yVelocity*dt);

    m_velocity.yVelocity = m_velocity.yVelocity - (m_gravity*dt);

    m_particle.setPosition(m_position.xPosition,m_position.yPosition);

    //Check collisions
    CheckCollisions();
}

void Particle::CheckCollisions()
{
    //Check left wall contact
    if(m_position.xPosition < 0)
    {
        m_velocity.xVelocity = std::abs(m_velocity.xVelocity);
    }
    //Check right wall contact
    if(m_position.xPosition > m_walls.x)
    {
        m_velocity.xVelocity = -std::abs(m_velocity.xVelocity);
    }

    //Check cieling
    if(m_position.yPosition < 0)
    {
        m_velocity.yVelocity = std::abs(m_velocity.yVelocity);
    }
    //Check floor
    if(m_position.yPosition > m_walls.y)
    {
        m_velocity.yVelocity = -std::abs(m_velocity.yVelocity);
    }

}

float Particle::CalculateNewPosition(const float &forceIn, const float& velocityIn, const float& postion, const float &dt)
{
    return (0.5*(forceIn/m_mass)*std::pow(dt,2)) + (velocityIn*dt) + postion;
}
