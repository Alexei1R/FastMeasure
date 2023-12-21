// Created by toor on 12/10/23.

#ifndef DISPLAYDATA_H
#define DISPLAYDATA_H

#include "FastMeasure/fastmeasurepch.h"
#include "FastMeasure/EmbededPlatform/LidarReadLayer.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace Atom {
    class DisplayData : public Layer {
    public:
        DisplayData(sf::RenderWindow& window, Atom::LidarReadLayer& lidarReadLayer);
        ~DisplayData();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnFixedUpdate() override;
        void OnImGuiRender() override;

        void SetOffset(float x, float y);
        void SetScalingFactor(float scalingFactor);
    private:
        sf::RenderWindow& m_Window;
        sf::RenderTexture m_RenderTexture;
        Atom::LidarReadLayer& m_LidarReadLayer;
        std::vector<std::pair<double, double>> m_CoordinatesList;
        std::vector<std::vector<std::pair<double, double>>> m_AverageCoordinatesList;
        std::vector<double> m_OutDistanceList;
        sf::Font font;
        sf::Vector2i m_ViewPortSize;
        double m_LargestDistanceAverage = 0.0;
        float m_ScalingFactor = 4.0f;
        sf::Vector2f m_CenterPoint;
        float m_OffsetX = 0.0f;
        float m_OffsetY = 0.0f;
        float m_DeltaScroll = 0.0f;

    };
}

#endif //DISPLAYDATA_H
