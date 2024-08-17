#include "entities.h"

#include <iostream>

void Entity::set_id(const int value) { m_id = value; }

size_t Entity::get_id() const { return m_id; }

EntityManager::EntityManager(GameConfig game_config)
    : m_game_config(std::move(game_config)) {}

void EntityManager::add_entities(const SharedVecOfEntity& entities)
{
    std::cout << "Add entities to a Manager\n";
    for (size_t i = 0; i < entities.size(); i++) {
        auto e = entities[i];
        e->set_id(i + 1);
        bound_text(*e);
        m_entities.push_back(e);
    }
}

void EntityManager::move_entities() const
{
    for (auto& entity: m_entities) {
        move_entity(*entity);
        bound_text(*entity);
    }
}

void EntityManager::render_entities(sf::RenderWindow& win) const
{
    for (const auto& m_entitie: m_entities) {
        if (m_entitie->is_alive) {
            win.draw(*m_entitie->shape);
            win.draw(*m_entitie->title);
        }
    }
}

void EntityManager::move_entity(Entity& entity) const
{
    auto sf_object = entity.shape;
    // basic animation - move the each frame if it's still in frame
    sf_object->setPosition(
        sf_object->getPosition().x + entity.speed.x,
        sf_object->getPosition().y + entity.speed.y
        );
    auto position = sf_object->getPosition();
    auto bounds = sf_object->getLocalBounds();

    // check width boundaries
    if (position.x + bounds.width >= static_cast<float>(
            m_game_config.window.width)
        || position.x + bounds.width <= bounds.width) {
        entity.speed.x *= -1.0f;
    }

    // check height boundaries
    if (position.y + bounds.height >= static_cast<float>(
            m_game_config.window.height)
        || position.y + bounds.height == bounds.height) {
        entity.speed.y *= -1.0f;
    }
}

void EntityManager::bound_text(const Entity& entity)
{
    auto sf_object = entity.shape;
    auto obj_size = sf_object->getLocalBounds();
    const auto font_size = static_cast<int>(
        obj_size.width / static_cast<float>(
            entity.title->getString().getSize()));
    entity.title->setCharacterSize(font_size); // size in pixels

    // centering
    auto text_size = entity.title->getLocalBounds();
    entity.title->setOrigin(text_size.width / 2, text_size.height / 2);

    entity.title->setPosition(
        sf_object->getPosition().x + obj_size.width / 2.0f,
        sf_object->getPosition().y + obj_size.height / 2.1f
        );
}
