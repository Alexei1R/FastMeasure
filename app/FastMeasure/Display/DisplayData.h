// Created by toor on 12/10/23.

#ifndef DISPLAYDATA_H
#define DISPLAYDATA_H

#include "FastMeasure/fastmeasurepch.h"
#include "FastMeasure/EmbededPlatform/LidarReadLayer.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "FastMeasure/Algorithm/FindLines.h"

namespace Atom {
    class DisplayData : public Layer {
    public:
        DisplayData(sf::RenderWindow& window, Atom::LidarReadLayer& lidarReadLayer, LineDetector& findLines);
        ~DisplayData();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnFixedUpdate() override;
        void OnImGuiRender() override;

        void SetOffset(float x, float y);
        void SetScalingFactor(float scalingFactor);

    private:
        sf::Font font;
        float m_OffsetX = 0.0f;
        float m_OffsetY = 0.0f;
        LineDetector& m_FindLines;
        sf::Vector2f m_CenterPoint;
        sf::RenderWindow& m_Window;
        sf::Vector2i m_ViewPortSize;
        float m_ScalingFactor = 4.0f;
        sf::RenderTexture m_RenderTexture;
        std::vector<double> m_OutDistanceList;
        double m_LargestDistanceAverage = 0.0;
        Atom::LidarReadLayer& m_LidarReadLayer;
        std::vector<std::pair<double, double>> m_CoordinatesList;
        std::vector<std::vector<std::pair<double, double>>> m_AverageCoordinatesList;
    };
}

#endif //DISPLAYDATA_H
