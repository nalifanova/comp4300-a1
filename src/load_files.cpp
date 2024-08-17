#include "load_files.h"

#include <fstream>
#include <string>

/**
 * Get path to defined file in assets
 * @param filename filename or filepath
 * @param is_font includes/excludes 'data' folder
 * @return string path
 */
std::string get_full_path(const std::string& filename, bool is_font)
{
    const std::filesystem::path cwd = std::filesystem::current_path();
    const std::filesystem::path paragraph_dir = cwd.parent_path().parent_path()
                                                / "assets";
    std::string folder = "/data/";
    if (is_font)
        folder = "/";
    std::string filename_ = paragraph_dir.string() + folder + filename;
    return filename_;
}

void load_font(FontConfig& font)
{
    const auto filepath_ = font.filepath;
    auto filepath = get_full_path(filepath_, true);
    if (!font.sf_font.loadFromFile(filepath)) {
        std::cerr << "Could not load font!\n";
        exit(-1);
    }
}

void load_from_file(
    const std::string& filename, GameConfig& game,
    SharedVecOfEntity& entities)
{
    const std::string filename_ = get_full_path(filename);
    std::cout << "Loading data from: " << filename_ << "\n";
    std::ifstream fin(filename_);
    std::string type = "none";

    while (fin >> type) {
        std::string shape_name;
        float x, y; // for position

        if (type == k_config_window) {
            // type width height
            fin >> game.window.width >> game.window.height;

            // DEBUG ------------------
            std::cout << "Window (" << game.window.width << ", "
                << game.window.height << ")\n";
            //
        } else if (type == k_config_font) {
            // type filepath size R G B
            fin >> game.font.filepath >> game.font.size >> game.font.color.red
                >> game.font.color.green >> game.font.color.blue;
            // DEBUG ------------------
            std::cout << "Font color (" << game.font.color.red << ", "
                << game.font.color.green << ", "
                << game.font.color.blue << ")\n";
            //
        }
        // Shapes
        else if (type == k_shape_cirle) {
            auto e = std::make_shared<Entity>();

            // type shape_name X Y SX SY RGB R
            fin >> shape_name;
            auto p_circle_shape = std::make_shared<sf::CircleShape>();

            e->title = std::make_shared<sf::Text>(
                shape_name,
                game.font.sf_font,
                game.font.size
                );
            e->title->setFillColor(sf::Color::Black);

            // coordinates
            fin >> x >> y;
            p_circle_shape->setPosition(x, y);

            // speed
            fin >> e->speed.x >> e->speed.y;

            // shape color
            Color c;
            fin >> c.red >> c.green >> c.blue;
            p_circle_shape->setFillColor(sf::Color(c.red, c.green, c.blue));

            // radius
            float radius;
            fin >> radius;
            p_circle_shape->setRadius(radius);

            e->shape = p_circle_shape;
            entities.push_back(e);

            // DEBUG ------------------
            std::cout << type << " " << shape_name << " X Y SX SY RGB R: ("
                << e->shape->getPosition().x << ", "
                << e->shape->getPosition().y << "), ("
                << e->speed.x << ", " << e->speed.y << ")\n";
            //
        } else if (type == k_shape_rectangle) {
            auto e = std::make_shared<Entity>();
            // type shape_name X Y SX SY RGB W H
            fin >> shape_name;

            auto p_rec_shape = std::make_shared<sf::RectangleShape>();

            e->title = std::make_shared<sf::Text>(
                shape_name,
                game.font.sf_font,
                game.font.size
                );

            e->title->setFillColor(sf::Color::Black);

            // coordinates
            fin >> x >> y;
            p_rec_shape->setPosition(x, y);

            // speed
            fin >> e->speed.x >> e->speed.y;

            // shape color
            Color c;
            fin >> c.red >> c.green >> c.blue;
            p_rec_shape->setFillColor(sf::Color(c.red, c.green, c.blue));

            Size size;
            fin >> size.width >> size.height;
            p_rec_shape->setSize(sf::Vector2(size.width, size.height));

            e->shape = p_rec_shape;
            entities.push_back(e);

            // DEBUG ------------------
            std::cout << type << " " << shape_name << " X Y SX SY RGB R: ("
                << e->shape->getPosition().x << ", "
                << e->shape->getPosition().y << "), ("
                << e->speed.x << ", " << e->speed.y << ")\n";
            //
        }
    }
    std::string dash_line(30, '-');
    std::cout << "Config data imported \n" << dash_line << "\n";
}
