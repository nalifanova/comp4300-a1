#include "img_gui_play.h"

#include <vector>
#include <imgui.h>
#include <imgui-SFML.h>

void create_circles(std::vector<std::shared_ptr<Circle>>& circles)
{
    // Create 2 circles
    Circle circle1(50.0f, sf::Color::Green);
    circle1.shape.setPosition(100.0, 200.0);
    circles.push_back(std::make_shared<Circle>(circle1));
    Circle circle2(75.0f, sf::Color::Blue);
    circle2.shape.setPosition(200.0, 350.0);
    circles.push_back(std::make_shared<Circle>(circle2));
}

void show_combo(
    std::shared_ptr<Circle>& selected_circle,
    const std::vector<std::shared_ptr<Circle>>& circles)
{
    if (ImGui::BeginCombo(
        "Select Circle",
        selected_circle ? "Circle Selected" : "None")) {
        for (size_t i = 0; i < circles.size(); i++) {
            if (ImGui::Selectable(
                ("Circle" + std::to_string(i + 1)).c_str(),
                selected_circle == circles[i])) { selected_circle = circles[i]; }
            if (selected_circle) { ImGui::SetItemDefaultFocus(); }
        }
        ImGui::EndCombo();
    }
}

void show_elemens(std::shared_ptr<Circle>& selected_circle)
{
    if (selected_circle) {
        float r, g, b;
        r = selected_circle->shape.getFillColor().r;
        g = selected_circle->shape.getFillColor().g;
        b = selected_circle->shape.getFillColor().b;

        ImGui::SliderFloat("##r", &r, 0.0f, 255.0f);
        ImGui::SliderFloat("##g", &g, 0.0f, 255.0f);
        ImGui::SliderFloat("##b", &b, 0.0f, 255.0f);
        ImGui::SliderFloat("Radius", &selected_circle->radius, 10.0f, 200.0f);

        selected_circle->color.r = r;
        selected_circle->color.g = g;
        selected_circle->color.b = b;
        selected_circle->update();
    }
}

void show_imgui_features()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "ImGui + SFML Example");
    window.setFramerateLimit(60);
    std::ignore = ImGui::SFML::Init(window);

    sf::Clock delta_clock;
    ImGui::GetStyle().ScaleAllSizes(1.0f);

    // Prepare data
    std::vector<std::shared_ptr<Circle>> circles;
    std::shared_ptr<Circle> selected_circle;
    create_circles(circles);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) { window.close(); }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // All ui elements will be in the `Circle Example` window
        ImGui::Begin("Circles Example"); // ---- Open window
        // Choose the circle
        show_combo(selected_circle, circles);
        // make changes window
        show_elemens(selected_circle);

        ImGui::End(); // ---- Close current window
        window.clear();

        // render circles
        for (const auto c: circles) { window.draw(c->shape); }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
