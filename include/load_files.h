#ifndef CONFIGS_H
#define CONFIGS_H

#include <iostream>
#include "entities.h"

inline std::string k_shape_cirle = "Circle";
inline std::string k_shape_rectangle = "Rectangle";
inline std::string k_config_window = "Window";
inline std::string k_config_font = "Font";

std::string get_full_path(const std::string& filename, bool is_font = false);

void load_font(FontConfig& font);

void load_from_file(
    const std::string& filename, GameConfig& game,
    SharedVecOfEntity& entities);

#endif //CONFIGS_H
