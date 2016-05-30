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
    m_position.yPosition = m_position.yPosition + m_velocity.yVelocity*dt;
    m_velocity.yVelocity = m_velocity.yVelocity-m_gravity*dt;

    m_particle.setPosition(m_position.xPosition, m_position.yPosition);
}
