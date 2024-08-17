#include <iostream>

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

void initial_code()
{
    // create a new window of size w*h pixels
    // top-left of the window is (0, 0) and bottom-right is (w, h)
    // you will have to read these from the config file
    const int k_width = 800;
    const int k_height = 600;

    sf::RenderWindow window(sf::VideoMode(k_width, k_height), "Game!");
    window.setFramerateLimit(60); // limit frame rate top 60 fps

    // initialize IMGUI and create a clock used for its internal timing
    std::ignore = ImGui::SFML::Init(window);
    sf::Clock delta_clock; // how much time passed between frames

    // scale the imgui ui by a given factor, does not affect text size
    ImGui::GetStyle().ScaleAllSizes(1.5f);

    // the imgui color {r,g,b} wheel for Circle(!)
    // requires floats from 0-1 instead of ints from 0-255
    float c[3] = {0.0f, 1.0f, 1.0f};

    // let's make a shape that will draw to the screen
    float circle_radius = 50; // radius to draw the circle
    int circle_segments = 32; // number of segments to draw the circle with
    float circle_speed_x = 1.0f; // we will use this to move the circle later
    float circle_speed_y = 0.5f; // you will read these values from the file
    bool draw_circle = true; // whether or not to draw the circle
    bool draw_text = true; // whether or not to draw the text

    // create the sfml cirlce shape based on our parameters
    sf::CircleShape circle(circle_radius, circle_segments); // create a circle shape with radius 50
    circle.setPosition(10.0f, 10.0f); // set the top-left position of the circle

    // let's load a font so we can display some text
    sf::Font my_font{};

    // attempt to load the font from a file
    // if (!my_font.loadFromFile("fonts/DroidSans.ttf")) // in build/bin/
    if (!my_font.loadFromFile("../../assets/fonts/VV2Nightclub.otf"))
    {
        // if we can't load the font, print an error to the error console and exit
        std::cerr << "Could not load font!\n";
        exit(-1);
    }


    // set up text object that will be drawn to the screen
    sf::Text text("Sample Text", my_font, 24);

    // position to the top-left corner of the text so that the text aligns on the botton
    // text charachter size is in pixels, so move the text up from the bottom by its height
    text.setPosition(10, k_height - (float)text.getCharacterSize() * 3);

    // set up a character array to set the text
    char display_string[255] = "Sample Text";

    // main loop - continues for each frame while window is open
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // event handling
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event{};
        while (window.pollEvent(event))
        {
            // pass the event to imgui to be parsed
            ImGui::SFML::ProcessEvent(window, event);

            // this event triggers when the window is closed
            if (event.type == sf::Event::Closed)
            {
                // "close requested" event: we close the window
                window.close();
            }

            // this event is triggered when a key is pressed
            if (event.type == sf::Event::KeyPressed)
            {
                // pring the key that was pressed to the console
                std::cout << "Key pressed with code = " << event.key.code << "\n";

                // example, what happens when x is pressed
                if (event.key.code == sf::Keyboard::X)
                {
                    // reverse the x direction of the circle on the screen
                    circle_speed_x *= -1.0f;
                }

                if (event.key.code == sf::Keyboard::Y)
                {
                    // reverse the y direction of the circle on the screen
                    circle_speed_y *= -1.0f;
                }
            }
        }

        // update imgui for this frame with the time that the last frame took
        ImGui::SFML::Update(window, delta_clock.restart());

        // draw the UI
        ImGui::Begin("Window title");
        ImGui::Text("Window text!");
        ImGui::Checkbox("Draw Circle", &draw_circle);
        ImGui::SameLine();
        ImGui::Checkbox("Draw text", &draw_text);
        ImGui::SliderFloat("Radius", &circle_radius, 0.0f, 300.0f);
        ImGui::SliderInt("Sides", &circle_segments, 3, 64);
        ImGui::ColorEdit3("Color Circle", c);
        ImGui::InputText("Text", display_string, 255);

        if (ImGui::Button("Set Text"))
        {
            text.setString(display_string);
        }
        ImGui::SameLine();

        if (ImGui::Button("Reset Circle"))
        {
            circle.setPosition(0, 0);
        }

        // ImGui::ShowDemoWindow();
        // ImGui::ShowDebugLogWindow();

        ImGui::End();

        // set the circle properties, because they may have been updated with the ui
        circle.setFillColor(sf::Color(c[0]*255, c[1]*255, c[2]*255));
        circle.setPointCount(circle_segments);
        circle.setRadius(circle_radius);

        // basic animation - move the each frame if it's still in frame
        circle.setPosition(circle.getPosition().x + circle_speed_x,
            circle.getPosition().y + circle_speed_y);

        // basic rendering function calls
        window.clear(); // clear the window of anything previously drawn
        if (draw_circle) // draw the circle if the boolean is true
        {
            window.draw(circle);
        }
        if (draw_text) // draw the text if the boolean is true
        {
            window.draw(text);
        }
        ImGui::SFML::Render(window); // draw the ui last so it's on top
        window.display(); // call the window display function
    }
}
