#include <iostream>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>
#include "Communication/ord_lidar_c_api_driver.h"
#include "Communication/ord_lidar_driver.h"

using namespace std;
using namespace ordlidar;
using namespace cv;

#define Degree2Rad(X) ((X)*M_PI / 180.)

int main(int argc, char **argv) {
    std::string port = "/dev/ttyACM0"; // default port
    int baudrate = 230400; // default baudrate
    int motor_speed = 10; // default motor speed

    // Define LIDAR model and type
    uint8_t type = ORADAR_TYPE_SERIAL;
    int model = ORADAR_MS200;

    OrdlidarDriver device(type, model);

    // Attempt to connect to the LIDAR
    if (!port.empty()) {
        device.SetSerialPort(port, baudrate);
        std::cout << "Attempting to connect to LIDAR at port: " << port << " with baudrate: " << baudrate << std::endl;

        if (device.Connect()) {
            std::cout << "LIDAR connected successfully." << std::endl;
        } else {
            std::cerr << "Failed to connect to LIDAR." << std::endl;
            return -1;
        }
    } else {
        std::cerr << "LIDAR port not specified." << std::endl;
        return -1;
    }

    full_scan_data_st scan_data;

    // Set and validate the motor speed
    double min_thr = (double)motor_speed - ((double)motor_speed * 0.1);
    double max_thr = (double)motor_speed + ((double)motor_speed * 0.1);
    double cur_speed = device.GetRotationSpeed();
    if (cur_speed < min_thr || cur_speed > max_thr) {
        device.SetRotationSpeed(motor_speed);
    }

    // OpenCV Window
    const int window_size = 600;
    namedWindow("LiDAR Data", WINDOW_AUTOSIZE);
    Mat image = Mat::zeros(window_size, window_size, CV_8UC3);

    // Main loop to grab and visualize LIDAR data
    while (true) {
        if (device.GrabFullScanBlocking(scan_data, 1000)) {
            image = Mat::zeros(window_size, window_size, CV_8UC3); // Clear the image for each scan

            for (int i = 0; i < scan_data.vailtidy_point_num; i++) {
                float range = scan_data.data[i].distance * 0.0005; // convert to meters
                float angle = Degree2Rad(scan_data.data[i].angle);

                // Convert polar coordinates to Cartesian for visualization
                int x = static_cast<int>((range * cos(angle)) * 100) + window_size / 2;
                int y = static_cast<int>((range * sin(angle)) * 100) + window_size / 2;

                circle(image, Point(x, y), 2, Scalar(255, 255, 255), -1); // Red circle for each point
            }

            imshow("LiDAR Data", image);
            if (waitKey(30) >= 0) break; // Break the loop if any key is pressed
        } else {
            std::cerr << "Failed to retrieve scan data." << std::endl;
        }
    }

    // Disconnect the device when done
    device.Disconnect();
    std::cout << "Disconnected LIDAR device." << std::endl;

    return 0;
}
