//
// Created by toor on 12/9/23.
//

#include "Application.h"


namespace Atom {


    Application *Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = (Application *) this;

        m_LidarReadLayer = new LidarReadLayer("/dev/ttyACM0");
        PushLayer(m_LidarReadLayer);


    }


    Application::~Application() {
    }


    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
    }


    void Application::Run() {


        while (m_IsRuning) {

            for (Layer *layer: m_LayerStack) {
                layer->OnUpdate();
            }


        }
    }





}