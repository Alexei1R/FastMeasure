//
// Created by toor on 12/15/23.
//

#ifndef FASTMEASURE_HOUGHTRANSFORM_H
#define FASTMEASURE_HOUGHTRANSFORM_H
#include "FastMeasure/EmbededPlatform/LidarReadLayer.h"
#include "FastMeasure/fastmeasurepch.h"



namespace Atom {
    class HoughTransorm : public Layer {
    public:
        HoughTransorm(Atom::LidarReadLayer& lidarReadLayer);
        ~HoughTransorm();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnFixedUpdate() override;

    private:
    LidarReadLayer& m_LidarReadLayer;



    };


}


#endif //FASTMEASURE_HOUGHTRANSFORM_H
