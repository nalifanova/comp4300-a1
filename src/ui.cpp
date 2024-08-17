#include "ui.h"

void manage_events(
    const sf::Event& event, sf::RenderWindow& window,
    SharedVecOfEntity& entities)
{
    switch (event.type) {
        // "close requested" event: we close the window
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Keyboard::X:
            for (const auto& entity: entities) { entity->speed.x *= -1.0f; }
            break;
        case sf::Keyboard::Y:
            for (const auto& entity: entities) { entity->speed.y *= -1.0f; }
            break;
        default:
            break;
    }
}
