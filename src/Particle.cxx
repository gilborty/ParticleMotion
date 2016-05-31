#include "Particle.hpp"

Particle::Particle(const float& radius, const sf::Vector2f &pos, const sf::Vector2f &vel, const float &mass, const float &gravity)
    : Particle::CircleShape(radius)
    , m_gravity(gravity)
    , m_mass(mass)
    , m_velocity(vel)
{
    this->setPosition(pos);

}

void Particle::updatePosition(const float &dt)
{
    float xPos = this->getPosition().x;
    float yPos = this->getPosition().y;

    float xVel = this->getVelocity().x;
    float yVel = this->getVelocity().y;

    xPos = xPos + (xVel*dt);
    yPos = yPos + (yVel*dt);

    yVel = yVel - (m_gravity*dt);

    this->setPosition(xPos, yPos);

    //Check collisions
    CheckCollisions();
}

void Particle::CheckCollisions()
{
    float xPos = this->getPosition().x;
    float yPos = this->getPosition().y;

    float xVel = this->getVelocity().x;
    float yVel = this->getVelocity().y;

    //Check left wall contact
    if(xPos < 0)
    {
        m_velocity.x = std::abs(xVel);
    }
    //Check right wall contact
    if(xPos > m_walls.x - this->getRadius())
    {
        m_velocity.x = -std::abs(xVel);
    }

    //Check cieling
    if(yPos < 0)
    {
        m_velocity.y = std::abs(yVel);
    }
    //Check floor
    if(yPos > m_walls.y- this->getRadius())
    {
        m_velocity.y = -std::abs(yVel);
    }
}
