//
// Created by toor on 12/9/23.
//

#include "Application.h"



namespace Atom {


    Application *Application::s_Instance = nullptr;

    Application::Application() {


        s_Instance = this;

        sf::Vector2u windowSize(1080, 720);
        m_Window = new sf::RenderWindow(sf::VideoMode(windowSize), "FastMeasure");

        m_LidarReadLayer = new LidarReadLayer("/dev/ttyACM0");
        PushLayer(m_LidarReadLayer);

        m_DisplayData = new DisplayData(*m_Window, *m_LidarReadLayer);
        PushLayer(m_DisplayData);

        m_Window->setFramerateLimit(60);
        ImGui::SFML::Init(*m_Window);

        auto& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        const sf::Vector2u size(600,600);

        m_RenderTexture.create(size);

    }


    Application::~Application() {
        ImGui::SFML::Shutdown();
        delete m_Window;
        delete m_LidarReadLayer;
        delete m_DisplayData;
    }


    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
    }


    void Application::Run() {


        while (m_Window->isOpen()) {
            while (m_Window->pollEvent(event)) {
                ImGui::SFML::ProcessEvent(*m_Window, event);
                if (event.type == sf::Event::Closed) {
                    m_Window->close();
                    m_IsRuning = false;
                }
            }

            ImGui::SFML::Update(*m_Window, deltaClock.restart());
            m_Window->clear(sf::Color::Red);


            for (Layer *layer: m_LayerStack) {
                layer->OnUpdate();
            }


            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();
            for (Layer *layer: m_LayerStack){
                layer->OnImGuiRender();
            }

            ImGui::SFML::Render(*m_Window);
            m_Window->display();

        }
    }





}