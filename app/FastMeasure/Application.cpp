//
// Created by toor on 12/9/23.
//

#include "Application.h"


namespace Atom {


    Application *Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = (Application *) this;


        sf::Vector2u windowSize(1080, 720);
        m_Window = new sf::RenderWindow(sf::VideoMode(windowSize), "FastMeasure");

        m_LidarReadLayer = new LidarReadLayer("/dev/ttyACM0");
        PushLayer(m_LidarReadLayer);

        m_DisplayData = new DisplayData(*m_Window, *m_LidarReadLayer);
        PushLayer(m_DisplayData);




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


        while (m_Window->isOpen()) {
            m_Window->clear(sf::Color::Black);


            for (Layer *layer: m_LayerStack) {
                layer->OnUpdate();
            }

            sf::Event event;
            while (m_Window->pollEvent(event))
            {
                // Close window on close event
                if (event.type == sf::Event::Closed)
                    m_Window->close();
                    m_IsRuning = false;
            }



            m_Window->display();


        }
    }





}