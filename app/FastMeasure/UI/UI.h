//
// Created by toor on 12/18/23.
//

#ifndef FASTMEASURE_UI_H
#define FASTMEASURE_UI_H
#include "FastMeasure/fastmeasurepch.h"


namespace Atom {
    class UILayer : public Layer {
    public:
        UILayer();
        ~UILayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnFixedUpdate() override;
        virtual void OnImGuiRender() override;

        void Partcles();
        void Decoration();


    private:
        int m_tabs;

    };


}


#endif //FASTMEASURE_UI_H
