#pragma once
#include <SFML/Graphics.hpp>
#include <utils/Constants.h>


class Particle
{
public:
    enum Type
    {
        TYPE_STONE,
        TYPE_SAND,
        TYPE_WATER,
        TYPE_NONE
    };

public:
    Type particleType = TYPE_NONE;

private:
    size_t i, j;

protected:
    sf::RectangleShape rectangle;

public:
    Particle(float x, float y, float width, float height, Type particleType);
    ~Particle();

    void updateConfig();
    void update(const sf::RenderWindow& renderWindow, 
                const std::array<std::array<std::unique_ptr<Particle>, countSize>, countSize>& particles,
                const std::array<std::array<std::unique_ptr<Particle>, countSize>, countSize>& particleBufffers);
    void draw(sf::RenderWindow& renderWindow);
};