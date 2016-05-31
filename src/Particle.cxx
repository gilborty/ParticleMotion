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

void Particle::updatePosition(const Force& forceIn, const float &dt)
{
    //This can perhaps be faster (or at least less cluttered) if we use sf::Vector2f to represent forces
    Position newPosition;
    auto previousPosition = m_position;

    newPosition.xPosition = CalculateNewPosition(forceIn.xForce, m_velocity.xVelocity, m_position.xPosition, dt);
    newPosition.yPosition = CalculateNewPosition(forceIn.yForce, m_velocity.yVelocity, m_position.xPosition, dt);

    m_position = newPosition;

    m_particle.setPosition(m_position.xPosition, m_position.yPosition);

    m_velocity.xVelocity = (m_position.xPosition - previousPosition.xPosition)/dt;
    m_velocity.yVelocity = (m_position.yPosition - previousPosition.yPosition)/dt;

}

float Particle::CalculateNewPosition(const float &forceIn, const float& velocityIn, const float& postion, const float &dt)
{
    return (0.5*(forceIn/m_mass)*std::pow(dt,2)) + (velocityIn*dt) + postion;
}
