//
// Created by toor on 12/9/23.
//

#ifndef FASTMEASURE_APPLICATION_H
#define FASTMEASURE_APPLICATION_H

#include "FastMeasure/fastmeasurepch.h"
#include "FastMeasure/EmbededPlatform/LidarReadLayer.h"
#include "FastMeasure/Display/DisplayData.h"

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
        bool m_IsRuning = true;
        LayerStack m_LayerStack;
        bool isConnected = false;


        sf::RenderWindow* m_Window;
        sf::Clock deltaClock{};
        sf::Event event{};

        LidarReadLayer* m_LidarReadLayer;
        DisplayData* m_DisplayData;

        sf::RenderTexture m_RenderTexture;



    };
}


#endif //FASTMEASURE_APPLICATION_H
