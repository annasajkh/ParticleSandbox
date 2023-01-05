#include <SFML/Graphics.hpp>
#include <shapes/Particle.h>

bool mouseDown = false;

sf::Vector2i mousePosition;
sf::Mouse::Button button;
Particle::Type particleTypeHeld = Particle::TYPE_STONE;

float delayCounter = 0;
