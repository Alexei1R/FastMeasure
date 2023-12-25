#include "FindLines.h"
#include <algorithm>
#include <set>
#include <iostream>
#include <sstream>
#include "FindLines.h"
#include <algorithm>
#include <set>
#include <iostream>
#include <sstream>

namespace Atom {

    LineDetector::LineDetector(LidarReadLayer& lidarLayer)
        : Layer("LineDetector"), lidarLayer(lidarLayer) {

        pointCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
        segmentation.setOptimizeCoefficients(true);
        segmentation.setModelType(pcl::SACMODEL_LINE);
        segmentation.setMethodType(pcl::SAC_RANSAC);
        segmentation.setDistanceThreshold(distanceThreshold);
    }

    LineDetector::~LineDetector() = default;

    void LineDetector::OnAttach() {
        // Implementation if required
    }

    void LineDetector::OnDetach() {
        // Implementation if required
    }

    void LineDetector::OnUpdate() {
        if(lidarLayer.IsOnline()) {
            lidarPoints = lidarLayer.GetCoordinatesList();

            if(distanceThreshold != lastDistanceThreshold) {
                lastDistanceThreshold = distanceThreshold;
                segmentation.setDistanceThreshold(distanceThreshold);
            }

            for(auto& point : lidarPoints) {
                pointCloud->push_back(pcl::PointXYZ(point.first, point.second, 0.0));
            }

            linesFromPoints.clear();

            while (!pointCloud->empty()) {
                pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
                pcl::PointIndices::Ptr inliers(new pcl::PointIndices);

                segmentation.setInputCloud(pointCloud);
                segmentation.segment(*inliers, *coefficients);

                if (inliers->indices.empty()) {
                    break;
                }

                if (inliers->indices.size() >= minPointsForLine) {
                    pcl::PointCloud<pcl::PointXYZ>::Ptr lineCloud(new pcl::PointCloud<pcl::PointXYZ>);
                    std::vector<std::pair<double, double>> pointsOnLine;

                    for (size_t i = 0; i < inliers->indices.size(); ++i) {
                        lineCloud->push_back(pointCloud->points[inliers->indices[i]]);
                    }

                    for (auto& point : lineCloud->points) {
                        pointsOnLine.emplace_back(point.x, point.y);
                    }

                    linesFromPoints.push_back(pointsOnLine);
                    PrintLinePoints(pointsOnLine);
                }

                pcl::ExtractIndices<pcl::PointXYZ> extract;
                extract.setInputCloud(pointCloud);
                extract.setIndices(inliers);
                extract.setNegative(true);
                extract.filter(*pointCloud);
            }
        }
    }

    void LineDetector::PrintLinePoints(const std::vector<std::pair<double, double>>& linePoints) {
        for (const auto& point : linePoints) {
            std::cout << "Line Point: x = " << point.first << ", y = " << point.second << std::endl;
        }
    }

    void LineDetector::OnFixedUpdate() {
        // Implement if needed
    }

    void LineDetector::OnImGuiRender() {
        ImGui::Begin("Line Detector Settings");

        ImGui::SliderFloat("Distance Threshold", &distanceThreshold, 0, 30);
        ImGui::SliderInt("Minimum Points for Line", &minPointsForLine, 0, 30);

        if(ImGui::Button("Apply")) {
        }

        ImGui::End();
    }



    std::vector<std::vector<std::pair<double,double>>> LineDetector::GetLinesFromPoints() const {
        return linesFromPoints;
    }



} // namespace Atom
