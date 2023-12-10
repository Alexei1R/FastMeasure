//
// Created by toor on 12/10/23.
//

#include "DisplayData.h"


namespace Atom {
    DisplayData::DisplayData(sf::RenderWindow& window,Atom::LidarReadLayer& lidarReadLayer)
    : Layer("DisplayData") , m_Window(window) , m_LidarReadLayer(lidarReadLayer)
    {



    }

    DisplayData::~DisplayData() {

    }

    void DisplayData::OnAttach() {}

    void DisplayData::OnDetach() {}



    void DisplayData::OnUpdate() {

        m_CoordinatesList = m_LidarReadLayer.GetCoordinatesList();

        // Calculate the center of the window
        sf::Vector2u windowSize = m_Window.getSize();
        sf::Vector2f windowCenter(windowSize.x / 2.0f, windowSize.y / 2.0f);

        for (const auto& point : m_CoordinatesList)
        {
            // Create a small circle shape to represent the point
            sf::CircleShape dot(2); // Radius of 2 pixels
            dot.setFillColor(sf::Color::Red);

            // Shift point coordinates from corner to window center
            sf::Vector2f centeredPosition(windowCenter.x + static_cast<float>(point.first),
                                          windowCenter.y + static_cast<float>(point.second));
            dot.setPosition(centeredPosition);

            // Draw the dot using m_Window
            m_Window.draw(dot);
        }
    }




    void DisplayData::OnFixedUpdate() {
    }
}
