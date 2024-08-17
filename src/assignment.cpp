#include "assignment.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "load_files.h"
#include "ui.h"

sf::Text show_text(GameConfig& game_config)
{
    sf::Text sample_text(
        "Shapes play",
        game_config.font.sf_font,
        game_config.font.size);
    sample_text.setPosition(0, 0);
    return sample_text;
}

void update_shape(
    std::shared_ptr<Entity>& entity, const float& scale,
    const float velocity[2],
    const Uint8 color[3], std::string shape_name)
{
    entity->shape->setScale(scale, scale);
    entity->speed.x = velocity[0];
    entity->speed.y = velocity[1];
    entity->shape->setFillColor(sf::Color(color[0], color[1], color[2]));
    entity->title->setString(shape_name);
}

void show_combo_box(
    SharedVecOfEntity& entities, std::shared_ptr<Entity>& selected_entity)
{
    std::string entity_title;
    static const char* title_c = "Choose the shape";

    if (selected_entity) {
        entity_title = selected_entity->title->getString();
        title_c = entity_title.c_str();
    }

    if (ImGui::BeginCombo("Shapes##Selector", title_c)) {
        for (const auto& e: entities) {
            entity_title = e->title->getString();
            char* char_name = &entity_title[0];

            if (ImGui::Selectable(char_name, selected_entity == e)) {
                selected_entity = e;
            }
            title_c = entity_title.c_str();
        }
        ImGui::EndCombo();
    }
}

void change_properties_window(std::shared_ptr<Entity>& entity)
{
    ImGui::Checkbox("Draw Shape", &entity->is_alive);
    // Scale 0 .. 4
    float scale = entity->shape->getScale().x;
    ImGui::SliderFloat("Scale", &scale, 0.0f, 4.0f);

    float v[2] = {entity->speed.x, entity->speed.y};
    ImGui::SliderFloat2("Velocity", v, -8.0f, 8.0f);

    const float r = static_cast<float>(entity->shape->getFillColor().r) /
                    255.0f;
    const float g = static_cast<float>(entity->shape->getFillColor().g) /
                    255.0f;
    const float b = static_cast<float>(entity->shape->getFillColor().b) /
                    255.0f;
    float col[3] = {r, g, b};

    ImGui::ColorEdit3("Color", col);
    const Uint8 color[3] = {
        static_cast<Uint8>(col[0] * 255), static_cast<Uint8>(col[1] * 255),
        static_cast<Uint8>(col[2] * 255)
    };

    std::string title = entity->title->getString();
    auto shape_name = &(title[0]);
    ImGui::InputText("Name", shape_name, 255);

    update_shape(entity, scale, v, color, shape_name);
}

void draw_shape_window(
    SharedVecOfEntity& entities, std::shared_ptr<Entity>& selected_entity)
{
    ImGui::Begin("Shape properties"); // Open window

    show_combo_box(entities, selected_entity);

    if (selected_entity) { change_properties_window(selected_entity); }

    ImGui::End(); // close window
}

void run_assignment()
{
    GameConfig game_config;
    SharedVecOfEntity entities;
    load_from_file("config.txt", game_config, entities);
    EntityManager manager(game_config);

    // set up window
    sf::RenderWindow window(
        sf::VideoMode(game_config.window.width, game_config.window.height),
        "Assignment 01!");
    window.setFramerateLimit(60); // limit frame rate top 60 fps
    load_font(game_config.font); // load font for all texts

    // initialize IMGUI and create a clock used for its internal timing
    std::ignore = ImGui::SFML::Init(window);
    sf::Clock delta_clock; // how much time passed between frames
    ImGui::GetStyle().ScaleAllSizes(1.5f);
    //  IMGUI -------- //

    // prepare data
    manager.add_entities(entities);
    std::shared_ptr<Entity> selected_entity = entities[0]; // initial

    // run the program as long as the window is open
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // pass the event to imgui to be parsed
            ImGui::SFML::ProcessEvent(window, event);
            manage_events(event, window, entities);
        }

        // update imgui for this frame with the time that the last frame took
        ImGui::SFML::Update(window, delta_clock.restart());

        draw_shape_window(entities, selected_entity);

        // animation
        manager.move_entities();

        window.clear();
        manager.render_entities(window);

        auto sample_text = show_text(game_config);
        window.draw(sample_text);
        ImGui::SFML::Render(window); // draw the ui last so it's on top
        window.display();
    }
    ImGui::SFML::Shutdown();
}

