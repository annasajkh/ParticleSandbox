#include <iostream>
#include <SFML/Graphics.hpp>
#include <shapes/Particle.h>
#include <utils/Constants.h>



extern sf::Vector2i mousePosition;
extern sf::Mouse::Button button;
extern Particle::Type particleTypeHeld;
extern bool mouseDown;
extern float delayCounter;

static std::array<std::array<std::unique_ptr<Particle>, countSize>, countSize> particles;
static std::array<std::array<std::unique_ptr<Particle>, countSize>, countSize> particleBuffers;


void init()
{
    for(size_t i = 0; i < countSize; i++)
    {
        for(size_t j = 0; j < countSize; j++)
        {
            particles[i][j] = std::make_unique<Particle>(i * particleSize, j * particleSize, particleSize, particleSize, Particle::TYPE_NONE);
        }
        
    }

    for(size_t i = 0; i < countSize; i++)
    {
        for(size_t j = 0; j < countSize; j++)
        {
            if(i == 0 || i == countSize - 1 || j == 0 || j == countSize - 1)
            {
                particleBuffers[i][j] = std::make_unique<Particle>(i * particleSize, j * particleSize, particleSize, particleSize, Particle::TYPE_STONE);

            }
            else
            {
                particleBuffers[i][j] = std::make_unique<Particle>(i * particleSize, j * particleSize, particleSize, particleSize, Particle::TYPE_NONE);
            }
        }
        
    }
}

void getInput(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed && !mouseDown)
    {
        if(event.key.code == sf::Keyboard::Num1)
        {
            particleTypeHeld = Particle::TYPE_STONE;
        }
        else if(event.key.code == sf::Keyboard::Num2)
        {
            particleTypeHeld = Particle::TYPE_SAND;
        }
        else if(event.key.code == sf::Keyboard::Num3)
        {
            particleTypeHeld = Particle::TYPE_WATER;
        }

        if(event.key.code == sf::Keyboard::Delete)
        {
            init();
        }
    }

    if(event.type == sf::Event::MouseButtonPressed)
    {
        mouseDown = true;
        button = event.mouseButton.button;
    }
    
    if (event.type == sf::Event::MouseButtonReleased)
    {
        mouseDown = false;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "ParticleSandbox");
    sf::Vector2u windowSize = window.getSize();
    sf::Clock deltaClock;


    init();
    
    while(window.isOpen())
    {   
        sf::Event event;
        sf::Time deltaTime = deltaClock.restart();

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            getInput(event);
        }

        if(mouseDown)
        {   
            mousePosition = sf::Mouse::getPosition(window);

            size_t i = mousePosition.x / particleSize;
            size_t j = mousePosition.y / particleSize;

            if(i > 0 && i < countSize - 1 && j > 0 && j < countSize - 1)
            {
                if(button == sf::Mouse::Left)
                {
                    particleBuffers[i][j]->particleType = particleTypeHeld;
                }
                else if(button == sf::Mouse::Right)
                {
                    particleBuffers[i][j]->particleType = Particle::TYPE_NONE;
                }
            }
        }

        if(delayCounter > delay)
        {            
            for(size_t i = 0; i < countSize; i++)
            {
                for(size_t j = 0; j < countSize; j++)
                {
                    particles[i][j]->update(window, particles, particleBuffers);
                }
            }

            for(size_t i = 0; i < countSize; i++)
            {
                for(size_t j = 0; j < countSize; j++)
                {
                    particles[i][j]->particleType = particleBuffers[i][j]->particleType;
                }
            }

            delayCounter = 0;
        }

        delayCounter += deltaTime.asSeconds();

        window.clear();
        for(size_t i = 0; i < countSize; i++)
        {
            for(size_t j = 0; j < countSize; j++)
            {
                particles[i][j]->draw(window);
            }
        }
        window.display();
    }

}
