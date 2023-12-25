//
// Created by toor on 12/9/23.
//
#ifndef FASTMEASURE_APPLICATION_H
#define FASTMEASURE_APPLICATION_H

#include "FastMeasure/fastmeasurepch.h"
#include "FastMeasure/EmbededPlatform/LidarReadLayer.h"
#include "FastMeasure/Display/DisplayData.h"
#include "FastMeasure/UI/UI.h"
#include "FastMeasure/Algorithm/FindLines.h"

namespace Atom {
    class Application {
    public:
        Application();
        ~Application();
        void Run();
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        static Application* s_Instance;
        inline static Application& GetApp() { return *s_Instance; }

    private:
        sf::RenderWindow* m_Window;
        sf::Clock deltaClock;
        sf::Event event;
        LidarReadLayer* m_LidarReadLayer;
        DisplayData* m_DisplayData;
        sf::RenderTexture m_RenderTexture;
        UILayer* m_UILayer;
        LayerStack m_LayerStack;
        sf::Vector2i m_InitialMousePosition;
        bool m_IsDragging = false;
        sf::Vector2i m_CurrentMousePosition;
        sf::Vector2i m_DeltaDrag;
        float m_DeltaScroll = 0.0f;
        float m_DefaultScalingFactor = 4.0f;

        LineDetector* m_FindLines;
    };
}

#endif //FASTMEASURE_APPLICATION_H
