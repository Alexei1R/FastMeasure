//
// Created by toor on 12/10/23.
//

#ifndef DISPLAYDATA_H
#define DISPLAYDATA_H
#include "FastMeasure/fastmeasurepch.h"
#include "FastMeasure/EmbededPlatform/LidarReadLayer.h"

namespace Atom {
    class DisplayData : public Layer {
    public:
        DisplayData(sf::RenderWindow& window ,Atom::LidarReadLayer& lidarReadLayer);
        ~DisplayData();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnFixedUpdate() override;

    private:
        sf::RenderWindow& m_Window;
        Atom::LidarReadLayer& m_LidarReadLayer;
        std::vector<std::pair<double, double>> m_CoordinatesList;
        std::vector<std::vector<std::pair<double, double>>> m_AverageCoordinatesList;
        std::vector<std::pair<double, double>> m_OutCoordinatesList;
        std::vector<double> m_OutDistanceList;
        sf::Font font;

        double m_LargestDistanceAverage = 0.0;
        std::string m_OutString;
        float m_ScalingFactor = 4.0f;

    };


}




#endif //DISPLAYDATA_H
