#ifndef ENTITIES_H
#define ENTITIES_H

#include <SFML/Graphics.hpp>

struct Color
{
    int16_t red = 0;
    int16_t green = 0;
    int16_t blue = 0;
};

struct Position
{
    float x = 0.0;
    float y = 0.0;
};

struct Speed
{
    float x = 0.0;
    float y = 0.0;
};

struct Size
{
    float width = 0.0;
    float height = 0.0;
};

class Entity final
{
public:
    // virtual destructor for polymorphism (to make dynamic_cast work)
    // virtual ~Entity() = default;
    std::shared_ptr<sf::Shape> shape;
    std::shared_ptr<sf::Text> title;
    Speed speed;
    [[nodiscard]] size_t get_id() const;
    void set_id(int value = 0);

    bool is_alive = true;
private:
    size_t m_id = 0;
};

struct WindowConfig
{
    std::string name = "WindowConfig";
    int width = 800;
    int height = 600;
};

struct FontConfig
{
    std::string filepath = "none";
    sf::Font sf_font = sf::Font();
    int size = 10;
    Color color;
};

struct GameConfig
{
    WindowConfig window;
    FontConfig font;

    GameConfig() = default;
    ~GameConfig() = default;
};

typedef std::vector<std::shared_ptr<Entity>> SharedVecOfEntity;

class EntityManager
{
public:
    explicit EntityManager(GameConfig game_config);
    ~EntityManager() = default;

    void add_entities(const SharedVecOfEntity& entities);

    void move_entities() const;

    void render_entities(sf::RenderWindow& win) const;

    void move_entity(Entity& entity) const;

    static void bound_text(const Entity& entity);

    static std::shared_ptr<sf::Text> create_text(
        const std::string& name, const sf::Font& font)
    {
        auto text_ptr = std::make_shared<sf::Text>(name, font);
        text_ptr->setFont(font);
        text_ptr->setFillColor(sf::Color::Black);
        text_ptr->setPosition(10, 10);
        text_ptr->setStyle(sf::Text::Bold);
        return text_ptr;
    }

private:
    GameConfig m_game_config;
    SharedVecOfEntity m_entities;
};

#endif //ENTITIES_H
