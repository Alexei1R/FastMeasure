//
// Created by toor on 12/9/23.
//

#ifndef FASTMEASURE_LAYERSTACK_H
#define FASTMEASURE_LAYERSTACK_H

#include "FastMeasure/fastmeasurepch.h"

namespace Atom {
    class LayerStack:public Layer{
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);
        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<Layer*> m_Layers;
        unsigned int m_LayerInsertIndex = 0;

    };



}




#endif //FASTMEASURE_LAYERSTACK_H
