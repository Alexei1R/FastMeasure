//
// Created by toor on 12/9/23.
//

#include "LidarReadLayer.h"



namespace Atom {
    LidarReadLayer::LidarReadLayer(std::string port)
    : Layer("LidarReadLayer"), m_Port(port)
    {



        m_Running = true;
        m_LidarThread = std::thread(&LidarReadLayer::ReadLidarDataThread, this);



    }

    LidarReadLayer::~LidarReadLayer() {
        if (m_Running) {
            m_Running = false;
            if (m_LidarThread.joinable()) {
                m_LidarThread.join();
            }
        }

    }

    void LidarReadLayer::OnAttach() {}

    void LidarReadLayer::OnDetach() {}

    void LidarReadLayer::OnUpdate() {
        if(isOnline) {
            std::cout << "Lidar is online" << std::endl;
        } else {
            std::cout << "Lidar is offline" << std::endl;
        }

    }

    void LidarReadLayer::OnFixedUpdate() {

    }

    void LidarReadLayer::ReadLidarDataThread() {


        m_Device = new ordlidar::OrdlidarDriver(ORADAR_TYPE_SERIAL , ORADAR_MS200);
        m_Device->SetSerialPort(m_Port.c_str() ,baudrate);

        std::cout << "Attempting to connect to LIDAR at port: " << m_Port << " with baudrate: " << baudrate << std::endl;

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

        double largestDistance = 0.0;
        while (m_Running) {

            if(m_Device->GrabFullScanBlocking(m_ScanData ,4000)) {
                isOnline = true;
                largestDistance = 0.0;

                std::vector<std::pair<double, double>> localCoordinatesList;

                for (int i = 0; i < m_ScanData.vailtidy_point_num; i++) {
                    double range = m_ScanData.data[i].distance * 0.001;
                    double angle = m_ScanData.data[i].angle *  M_PI / 180.0;
                    if(range > largestDistance) {
                        largestDistance = range;
                    }

                    double x = range * cos(angle) * 100;
                    double y = range * sin(angle) * 100;
                    localCoordinatesList.push_back(std::make_pair(x, y));
                }

                // Lock the mutex before updating the shared resource
                std::lock_guard<std::mutex> lock(m_CoordinatesListMutex);
                m_CoordinatesList = localCoordinatesList;
                m_LargestDistance = largestDistance;
            }
        }

    }
}
