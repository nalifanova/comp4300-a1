#ifndef UI_H
#define UI_H

#include <SFML/Window.hpp>
#include "load_files.h"

void manage_events(
    const sf::Event& event, sf::RenderWindow& window,
    SharedVecOfEntity& entities);

#endif //UI_H
