#ifndef IMG_GUI_PLAY_H
#define IMG_GUI_PLAY_H

#include <SFML/Graphics.hpp>

struct Circle {
    sf::CircleShape shape;
    sf::Color color;
    float radius;

    Circle(float r, sf::Color c) : shape(r), color(c), radius(r) {
        shape.setFillColor(color);
    }

    void update() {
        shape.setRadius(radius);
        shape.setFillColor(color);
        // shape.setOrigin(radius, radius); // set position
    }
};

void create_circles(std::vector<std::shared_ptr<Circle>>& circles);

void show_combo(std::shared_ptr<Circle>& selected_circle,
    const std::vector<std::shared_ptr<Circle>>& circles);

void show_imgui_features();

#endif //IMG_GUI_PLAY_H
