#include <shapes/Particle.h>
#include <iostream>
#include <utils/Constants.h>



Particle::Particle(float x, float y, float width, float height, Type particleType)
    : rectangle(sf::RectangleShape(sf::Vector2f(width, height))),
      i(x / particleSize),
      j(y / particleSize),
      particleType(particleType)
{ 
    rectangle.setPosition(x, y);

    Particle::updateConfig();
}

void Particle::updateConfig()
{
    switch(this->particleType)
    {
        case TYPE_STONE:
            rectangle.setFillColor(sf::Color(136, 140, 141));
            break;
        
        case TYPE_SAND:
            rectangle.setFillColor(sf::Color(255, 191, 146));
            break;

        case TYPE_WATER:
            rectangle.setFillColor(sf::Color(0, 94, 184));
            break;

        case TYPE_NONE:
            break;
    }
}

void Particle::update(const sf::RenderWindow& renderWindow,
                      const std::array<std::array<std::unique_ptr<Particle>, countSize>, countSize>& particles,
                      const std::array<std::array<std::unique_ptr<Particle>, countSize>, countSize>& particleBufffers)
{


    if(i > 0 && i < countSize - 1 && j > 0 && j < countSize - 1)
    {
        switch(this->particleType)
        {
            case TYPE_STONE:
                break;
            
            case TYPE_SAND:
                if(particleBufffers[i][j + 1]->particleType == TYPE_WATER)
                {   
                    Type temp = particleBufffers[i][j + 1]->particleType;

                    particleBufffers[i][j + 1]->particleType = particleBufffers[i][j]->particleType;
                    particleBufffers[i][j]->particleType = temp;
                    
                }

                if(particleBufffers[i][j + 1]->particleType == TYPE_NONE)
                {
                    particleBufffers[i][j + 1]->particleType = this->particleType;
                    particleBufffers[i][j]->particleType = TYPE_NONE;
                }
                else if(particleBufffers[i + 1][j + 1]->particleType == TYPE_NONE &&
                        particleBufffers[i - 1][j + 1]->particleType == TYPE_NONE &&
                        particleBufffers[i - 1][j]->particleType == TYPE_NONE &&
                        particleBufffers[i - 1][j]->particleType == TYPE_NONE)
                {
                    if(rand() % 2)
                    {
                        particleBufffers[i + 1][j + 1]->particleType = this->particleType;
                        particleBufffers[i][j]->particleType = TYPE_NONE;
                    }
                    else
                    {
                        particleBufffers[i - 1][j + 1]->particleType = this->particleType;
                        particleBufffers[i][j]->particleType = TYPE_NONE;
                    }
                }
                else if(particleBufffers[i + 1][j + 1]->particleType == TYPE_NONE &&
                        particleBufffers[i + 1][j]->particleType == TYPE_NONE)
                {
                    particleBufffers[i + 1][j + 1]->particleType = this->particleType;
                    particleBufffers[i][j]->particleType = TYPE_NONE;
                }
                else if(particleBufffers[i - 1][j + 1]->particleType == TYPE_NONE &&
                        particleBufffers[i - 1][j]->particleType == TYPE_NONE)
                {
                    particleBufffers[i - 1][j + 1]->particleType = this->particleType;
                    particleBufffers[i][j]->particleType = TYPE_NONE;
                }
                break;

            case TYPE_WATER:
                if(particleBufffers[i][j + 1]->particleType == TYPE_NONE)
                {
                    particleBufffers[i][j + 1]->particleType = this->particleType;
                    particleBufffers[i][j]->particleType = TYPE_NONE;
                }
                else if(particleBufffers[i + 1][j]->particleType == TYPE_NONE &&
                        particleBufffers[i - 1][j]->particleType == TYPE_NONE)
                {
                    if(rand() % 2)
                    {
                        particleBufffers[i + 1][j]->particleType = this->particleType;
                        particleBufffers[i][j]->particleType = TYPE_NONE;
                    }
                    else
                    {
                        particleBufffers[i - 1][j]->particleType = this->particleType;
                        particleBufffers[i][j]->particleType = TYPE_NONE;
                    }
                }
                else if(particleBufffers[i + 1][j]->particleType == TYPE_NONE)
                {
                    particleBufffers[i + 1][j]->particleType = this->particleType;
                    particleBufffers[i][j]->particleType = TYPE_NONE;
                }
                else if(particleBufffers[i - 1][j]->particleType == TYPE_NONE)
                {
                    particleBufffers[i - 1][j]->particleType = this->particleType;
                    particleBufffers[i][j]->particleType = TYPE_NONE;
                }
                break;

            case TYPE_NONE:

                break;
        }
    }
}

void Particle::draw(sf::RenderWindow& renderWindow)
{
    Particle::updateConfig();

    if(this->particleType != TYPE_NONE)
    {
        renderWindow.draw(rectangle);
    }
}

Particle::~Particle()
{
    
}