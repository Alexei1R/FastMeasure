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

        m_FindLines = new LineDetector(*m_LidarReadLayer);
        PushLayer(m_FindLines);

        m_DisplayData = new DisplayData(*m_Window, *m_LidarReadLayer, *m_FindLines);
        PushLayer(m_DisplayData);

//        m_UILayer = new UILayer();
//        PushOverlay(m_UILayer);


        m_Window->setFramerateLimit(60);
        ImGui::SFML::Init(*m_Window);

        auto& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        m_RenderTexture.create(sf::Vector2u(600, 600));
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
                switch (event.type) {
                    case sf::Event::Closed:
                        m_Window->close();
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            m_InitialMousePosition = sf::Mouse::getPosition(*m_Window);
                            m_IsDragging = true;
                        }
                        break;
                    case sf::Event::MouseMoved:
                        if (m_IsDragging) {
                            m_CurrentMousePosition = sf::Mouse::getPosition(*m_Window);
                            m_DeltaDrag = m_CurrentMousePosition - m_InitialMousePosition;
                            //print
//                            std::cout << "Delta Drag: " << m_DeltaDrag.x << ", " << m_DeltaDrag.y << std::endl;
                            m_DisplayData->SetOffset(m_DeltaDrag.x, m_DeltaDrag.y);
                        }
                        break;
                    case sf::Event::MouseButtonReleased:
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            m_IsDragging = false;
                            m_DeltaDrag = sf::Vector2i(0, 0);
                        }
                        break;
                    case sf::Event::MouseWheelScrolled:
                        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                            m_DeltaScroll = m_DeltaScroll + (event.mouseWheelScroll.delta * 0.2);
                            std::cout << "Delta Scroll: " << m_DeltaScroll << std::endl;
                            m_DisplayData->SetScalingFactor(m_DeltaScroll);
                        }
                        break;

                    case sf::Keyboard::R:
                        m_DisplayData->SetOffset(0, 0);
                        m_DeltaScroll = m_DefaultScalingFactor;

                        break;
                    break;

                }
            }

            ImGui::SFML::Update(*m_Window, deltaClock.restart());
            m_Window->clear(sf::Color::Red);

            for (Layer *layer: m_LayerStack) {
                layer->OnUpdate();
            }

            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();
            for (Layer *layer: m_LayerStack) {
                layer->OnImGuiRender();
            }

            ImGui::SFML::Render(*m_Window);
            m_Window->display();
        }
    }
}
