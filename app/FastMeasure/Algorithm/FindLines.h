//
// Created by toor on 12/23/23.
//


#ifndef FASTMEASURE_FINDLINES_H
#define FASTMEASURE_FINDLINES_H

#include "FastMeasure/fastmeasurepch.h"
#include "FastMeasure/EmbededPlatform/LidarReadLayer.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <pcl/point_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/extract_indices.h>

namespace Atom {

    struct Line {
        double startX;
        double startY;
        double endX;
        double endY;
    };

    class LineDetector : public Layer {
    public:
        explicit LineDetector(LidarReadLayer& lidarLayer);
        ~LineDetector() override;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnFixedUpdate() override;
        void OnImGuiRender() override;

        void PrintLinePoints(const std::vector<std::pair<double, double>>& linePoints);


        // std::vector<Line> GetDetectedLines() const;
        std::vector<std::vector<std::pair<double,double>>> GetLinesFromPoints()const ;

    private:
        LidarReadLayer& lidarLayer;
        std::vector<std::pair<double, double>> lidarPoints;

        std::vector<std::vector<std::pair<double,double>>> linesFromPoints;

        pcl::PointCloud<pcl::PointXYZ>::Ptr pointCloud;
        pcl::SACSegmentation<pcl::PointXYZ> segmentation;
        int minPointsForLine = 20;
        float distanceThreshold = 3.0f;
        float lastDistanceThreshold = 0.0f;
    };

} // namespace Atom

#endif //FASTMEASURE_FINDLINES_H
