// Created by toor on 12/10/23.

#include "DisplayData.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

namespace Atom {
    DisplayData::DisplayData(sf::RenderWindow& window, Atom::LidarReadLayer& lidarReadLayer, LineDetector& findLines)
            : Layer("DisplayData"), m_Window(window), m_LidarReadLayer(lidarReadLayer) , m_FindLines(findLines){
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cout << "Error loading font" << std::endl;
        }
    }

    DisplayData::~DisplayData() {
    }

    void DisplayData::OnAttach() {
    }

    void DisplayData::OnDetach() {
    }

    void DisplayData::OnUpdate() {
        m_RenderTexture.clear(sf::Color::Black);
        m_LargestDistanceAverage = 0; // Reset the average distance
        if(m_ViewPortSize.x > 0 && m_ViewPortSize.y > 0) {
            if (m_ViewPortSize.x != m_RenderTexture.getSize().x || m_ViewPortSize.y != m_RenderTexture.getSize().y) {
                m_RenderTexture.create(sf::Vector2u (m_ViewPortSize.x , m_ViewPortSize.y ));
            }
            if (m_LidarReadLayer.IsOnline()) {
                m_CoordinatesList = m_LidarReadLayer.GetCoordinatesList();
                m_AverageCoordinatesList.push_back(m_CoordinatesList);
                if (m_AverageCoordinatesList.size() > 50) {
                    m_AverageCoordinatesList.erase(m_AverageCoordinatesList.begin());
                }
                m_OutDistanceList.push_back(m_LidarReadLayer.GetLargestDistance());
                if (m_OutDistanceList.size() > 150) {
                    m_OutDistanceList.erase(m_OutDistanceList.begin());
                }
                if (!m_OutDistanceList.empty()) { // Check if the list is not empty
                    for (const auto& distance : m_OutDistanceList) {
                        m_LargestDistanceAverage += distance;
                    }
                    m_LargestDistanceAverage /= m_OutDistanceList.size();
                }
                sf::Vector2u windowSize = m_RenderTexture.getSize();
                m_CenterPoint =  sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f) + sf::Vector2f(m_OffsetX, m_OffsetY);
                float scale = m_LargestDistanceAverage != 0 ? m_ScalingFactor / m_LargestDistanceAverage : 1;
                for (const auto& coordinatesList : m_AverageCoordinatesList) {
                    if (!m_CoordinatesList.empty()) {
                        const float maxLineLength = 20;

                        for (size_t i = 0; i < m_CoordinatesList.size() - 1; ++i) {
                            sf::Vector2f point1(m_CenterPoint.x + static_cast<float>(m_CoordinatesList[i].first) * scale,
                                                m_CenterPoint.y + static_cast<float>(m_CoordinatesList[i].second) * scale);
                            sf::Vector2f point2(m_CenterPoint.x + static_cast<float>(m_CoordinatesList[i + 1].first) * scale,
                                                m_CenterPoint.y + static_cast<float>(m_CoordinatesList[i + 1].second) * scale);
                            float lineLength = std::sqrt(std::pow(point2.x - point1.x, 2) + std::pow(point2.y - point1.y, 2));
                            if (lineLength <= maxLineLength) {
                                sf::Vertex line[] = {
                                        sf::Vertex(point1),
                                        sf::Vertex(point2)
                                };
                                m_RenderTexture.draw(line, 2, sf::PrimitiveType::Lines);
                            }
                        }
                    }
                }
                std::vector<std::vector<std::pair<double,double>> > linesFormedfromPoints = m_FindLines.GetLinesFromPoints();
                if(linesFormedfromPoints.size() > 0) {
                    for(int i = 0; i < linesFormedfromPoints.size(); ++i) {
                        std::vector<std::pair<double,double>> linePoints  = linesFormedfromPoints[i];

                        // if is a moltiplu of one set color red , if is a multiple of 2 set color green , if is a multiple of 3 set color blue
                        sf::Color color;
                        if(i % 2) {
                            color = sf::Color::Red;
                        }
                        else if(i % 3) {
                            color = sf::Color::Green;
                        }
                        else {
                            color = sf::Color::Blue;
                        }


                        for(auto& point : linePoints) {
                            sf::CircleShape dot(2); // Radius of 2 pixels
                            dot.setFillColor(color);
                            sf::Vector2f centeredPosition(m_CenterPoint.x + static_cast<float>(point.first) * scale,
                                                          m_CenterPoint.y + static_cast<float>(point.second) * scale);
                            dot.setPosition(centeredPosition);
                            m_RenderTexture.draw(dot);
                        }
                    }
                }
                sf::Text text(font, "Largest Distance Average: " + std::to_string(m_LargestDistanceAverage) + "Scaling factor " + std::to_string(m_ScalingFactor), 24);
                text.setFillColor(sf::Color::White);
                m_RenderTexture.draw(text);
            } else {
                sf::Text text(font, "Lidar Offline please wait", 24);
                text.setFillColor(sf::Color::White);
                sf::FloatRect textRect = text.getGlobalBounds();
                sf::Vector2f textOrigin = sf::Vector2f(textRect.width / 2.0f, textRect.height / 2.0f);
                text.setOrigin(textOrigin);
                text.setPosition(sf::Vector2f(m_RenderTexture.getSize().x / 2.0f, m_RenderTexture.getSize().y / 2.0f));

                m_RenderTexture.draw(text);
            }
            m_RenderTexture.display();
        }
    }

    void DisplayData::OnImGuiRender() {
        ImGui::Begin("DisplayData");
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 contentAreaSize = ImGui::GetContentRegionAvail();
        float topPanelHeight = windowSize.y - contentAreaSize.y;
        m_ViewPortSize = sf::Vector2i(windowSize.x, windowSize.y - topPanelHeight -5);
        ImTextureID texID = reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(m_RenderTexture.getTexture().getNativeHandle()));
        ImGui::Image(texID, ImVec2(windowSize.x, windowSize.y - topPanelHeight -5), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }

    void DisplayData::OnFixedUpdate() {
    }
    void DisplayData::SetOffset(float x, float y) {
        m_OffsetX = x;
        m_OffsetY = y;
    }
    void DisplayData::SetScalingFactor(float scalingFactor){
        m_ScalingFactor = scalingFactor;
    }
}
