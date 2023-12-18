//
// Created by toor on 12/15/23.
//

#include "HoughTransform.h"



namespace Atom {
    HoughTransorm::HoughTransorm(Atom::LidarReadLayer& lidarReadLayer)
            : Layer("HoughTransorm") , m_LidarReadLayer(lidarReadLayer)
    {




    }

    HoughTransorm::~HoughTransorm() {

    }

    void HoughTransorm::OnAttach() {}

    void HoughTransorm::OnDetach() {}



    void HoughTransorm::OnUpdate() {


    }




    void HoughTransorm::OnFixedUpdate() {
    }
}
