#include "experiments.h"
#include "load_files.h"
#include "ui.h"

template <typename T> void log_object(const std::string title, T& object)
{
    std::cout << title << " (" << object.getSize().x << ", "
        << object.getSize().y << ")\n";
}

/**
 * Example of a window with moving objects.
 * SMFL lib is used
 */
void exp_smfl_only()
{
    GameConfig game_config;
    SharedVecOfEntity entities;
    load_from_file("config.txt", game_config, entities);
    EntityManager manager(game_config);

    // set up window
    sf::RenderWindow window(
        sf::VideoMode(game_config.window.width, game_config.window.height),
        "Exp1!");
    log_object("Window", window);
    window.setFramerateLimit(60); // limit frame rate top 60 fps

    load_font(game_config.font);
    sf::Text sample_text(
        "Let's check the text",
        game_config.font.sf_font,
        game_config.font.size);
    sample_text.setPosition(0, 0);

    manager.add_entities(entities);

    // run the program as long as the window is open
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            manage_events(event, window, entities);
        }

        // animation
        manager.move_entities();

        window.clear();
        manager.render_entities(window);

        window.draw(sample_text);
        window.display();
    }
}
