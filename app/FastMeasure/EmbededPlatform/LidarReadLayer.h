//
// Created by toor on 12/9/23.
//

#ifndef FASTMEASURE_LIDARREADLAYER_H
#define FASTMEASURE_LIDARREADLAYER_H
#include "FastMeasure/fastmeasurepch.h"

#include "Communication/ord_lidar_c_api_driver.h"
#include "Communication/ord_lidar_driver.h"

namespace Atom {
    class LidarReadLayer : public Layer {
    public:
        LidarReadLayer(std::string port);
        ~LidarReadLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnFixedUpdate() override;

        std::vector<std::pair<double, double>> GetCoordinatesList() { return m_CoordinatesList; }

    private:
        ordlidar::OrdlidarDriver* m_Device;
        full_scan_data_st m_ScanData;
        unsigned int m_MotorSpeed = 10;

        std::pair<double, double> m_Coordinates;
        std::vector<std::pair<double, double>> m_CoordinatesList;

    };


}



#endif //FASTMEASURE_LIDARREADLAYER_H
