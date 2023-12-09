//
// Created by toor on 12/9/23.
//

#include "LidarReadLayer.h"



namespace Atom {
    LidarReadLayer::LidarReadLayer(std::string port)
            : Layer("LidarReadLayer") {
        int baudrate = 230400;

        m_Device = new ordlidar::OrdlidarDriver(ORADAR_TYPE_SERIAL , ORADAR_MS200);
        m_Device->SetSerialPort(port.c_str() ,baudrate);

        std::cout << "Attempting to connect to LIDAR at port: " << port << " with baudrate: " << baudrate << std::endl;

        if (m_Device->Connect()) {
            std::cout << "LIDAR connected successfully." << std::endl;
        } else {
            std::cerr << "Failed to connect to LIDAR." << std::endl;
            return;
        }

        double min_thr = (double)m_MotorSpeed - ((double)m_MotorSpeed * 0.1);
        double max_thr = (double)m_MotorSpeed + ((double)m_MotorSpeed * 0.1);
        double cur_speed = m_Device->GetRotationSpeed();
        if (cur_speed < min_thr || cur_speed > max_thr) {
            m_Device->SetRotationSpeed(m_MotorSpeed);
        }


    }

    LidarReadLayer::~LidarReadLayer() {

    }

    void LidarReadLayer::OnAttach() {}

    void LidarReadLayer::OnDetach() {}

    void LidarReadLayer::OnUpdate() {

        if(m_Device->GrabFullScanBlocking(m_ScanData ,1000)) {

            m_CoordinatesList.clear();
            for (int i = 0; i < m_ScanData.vailtidy_point_num; i++) {
                double range = m_ScanData.data[i].distance * 0.001;
                double angle = m_ScanData.data[i].angle *  M_PI / 180.0;

                double x = range * cos(angle) * 100;
                double y = range * sin(angle) * 100;
                m_CoordinatesList.push_back(std::make_pair(x, y));
            }



        }

    }

    void LidarReadLayer::OnFixedUpdate() {
    }
}
