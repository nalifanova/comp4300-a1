#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "entities.h"

typedef unsigned char Uint8; // this type is used for rgb in sf::Color

sf::Text show_text(GameConfig& game_config);

void update(
    std::shared_ptr<Entity>& entity, sf::Color color, float& value1,
    float& value2);

void show_combo_box(
    SharedVecOfEntity& entities, std::shared_ptr<Entity>& selected_entity);

void change_properties_window(std::shared_ptr<Entity>& entity);

void draw_shape_window(
    SharedVecOfEntity& entities, std::shared_ptr<Entity>& selected_entity);

void run_assignment();

#endif //ASSIGNMENT_H
