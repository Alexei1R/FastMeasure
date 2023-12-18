//
// Created by toor on 12/10/23.
//

#include "DisplayData.h"
#include <deque>


namespace Atom {
    DisplayData::DisplayData(sf::RenderWindow& window,Atom::LidarReadLayer& lidarReadLayer)
    : Layer("DisplayData") , m_Window(window) , m_LidarReadLayer(lidarReadLayer)
    {


        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cout << "Error loading font" << std::endl;
        }


    }

    DisplayData::~DisplayData() {

    }

    void DisplayData::OnAttach() {}

    void DisplayData::OnDetach() {}



    void DisplayData::OnUpdate() {
        m_RenderTexture.clear(sf::Color::Black);
        m_LargestDistanceAverage = 0; // Reset the average distance
        ImVec2 viewportSize = ImGui::GetMainViewport()->Size;
        if (viewportSize.x != m_RenderTexture.getSize().x || viewportSize.y != m_RenderTexture.getSize().y) {
            m_RenderTexture.create(sf::Vector2u (viewportSize.x , viewportSize.y ));
        }


        if (m_LidarReadLayer.IsOnline()) {
            m_CoordinatesList = m_LidarReadLayer.GetCoordinatesList();
            m_AverageCoordinatesList.push_back(m_CoordinatesList);
            if (m_AverageCoordinatesList.size() > 8) {
                m_AverageCoordinatesList.erase(m_AverageCoordinatesList.begin());
            }
            m_OutDistanceList.push_back(m_LidarReadLayer.GetLargestDistance());
            if (m_OutDistanceList.size() > 75) {
                m_OutDistanceList.erase(m_OutDistanceList.begin());
            }
            if (!m_OutDistanceList.empty()) { // Check if the list is not empty
                for (const auto& distance : m_OutDistanceList) {
                    m_LargestDistanceAverage += distance;
                }
                m_LargestDistanceAverage /= m_OutDistanceList.size();
            }
            sf::Vector2u windowSize = m_RenderTexture.getSize();
            sf::Vector2f windowCenter(windowSize.x / 2.0f, windowSize.y / 2.0f);
            float scale = m_LargestDistanceAverage != 0 ? m_ScalingFactor / m_LargestDistanceAverage : 1;
            for (const auto& coordinatesList : m_AverageCoordinatesList) {
                for (const auto& point : coordinatesList) {
                    sf::CircleShape dot(2); // Radius of 2 pixels
                    dot.setFillColor(sf::Color(100, 255, 255));
                    sf::Vector2f centeredPosition(windowCenter.x + static_cast<float>(point.first) * scale,
                                                  windowCenter.y + static_cast<float>(point.second) * scale);
                    dot.setPosition(centeredPosition);
                    m_RenderTexture.draw(dot);
                }
            }
            sf::Text text(font, "Largest Distance Average: " + std::to_string(m_LargestDistanceAverage), 24);
            text.setFillColor(sf::Color::White);
            m_RenderTexture.draw(text);
        } else {
            sf::Text text(font, "Lidar Offline please wait", 24);
            text.setFillColor(sf::Color::White);
            m_RenderTexture.draw(text);
        }
        m_RenderTexture.display();
    }



    void DisplayData::OnImGuiRender() {
        ImGui::Begin("DisplayData");
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 contentAreaSize = ImGui::GetContentRegionAvail();
        float topPanelHeight = windowSize.y - contentAreaSize.y;
        ImVec2 viewportSize;
        viewportSize.x = m_RenderTexture.getSize().x;
        viewportSize.y = m_RenderTexture.getSize().y - topPanelHeight;
        ImTextureID texID = reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(m_RenderTexture.getTexture().getNativeHandle()));
        ImGui::Image(texID, ImVec2(viewportSize.x, viewportSize.y));
        ImGui::End();
    }




    void DisplayData::OnFixedUpdate() {
    }
}
