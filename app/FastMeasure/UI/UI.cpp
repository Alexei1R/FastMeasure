//
// Created by toor on 12/18/23.
//
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "widgets.h"

#include "UI.h"
#include "logo.h"


namespace Atom {
    UILayer::UILayer()
            : Layer("UILayer")
    {




    }

    UILayer::~UILayer() {

    }

    void UILayer::OnAttach() {}

    void UILayer::OnDetach() {}



    void UILayer::OnUpdate() {

    }



    void UILayer::OnImGuiRender() {

        Partcles();
        Decoration();
    }




    void UILayer::OnFixedUpdate() {
    }

    void UILayer::Partcles() {
        ImGui::Begin("Particles");
//

        ImVec2 screen_size = ImGui::GetIO().DisplaySize;

        static ImVec2 partile_pos[100];
        static ImVec2 partile_target_pos[100];
        static float partile_speed[100];
        static float partile_radius[100];


        for (int i = 1; i < 50; i++)
        {
            if (partile_pos[i].x == 0 || partile_pos[i].y == 0)
            {
                partile_pos[i].x = rand() % (int)screen_size.x + 1;
                partile_pos[i].y = 15.f;
                partile_speed[i] = 1 + rand() % 25;
                partile_radius[i] = rand() % 4;

                partile_target_pos[i].x = rand() % (int)screen_size.x;
                partile_target_pos[i].y = screen_size.y * 2;
            }

            partile_pos[i] = ImLerp(partile_pos[i], partile_target_pos[i], ImGui::GetIO().DeltaTime * (partile_speed[i] / 60));

            if (partile_pos[i].y > screen_size.y)
            {
                partile_pos[i].x = 0;
                partile_pos[i].y = 0;
            }

            ImGui::GetWindowDrawList()->AddCircleFilled(partile_pos[i], partile_radius[i], ImColor(174, 139, 148, 255 / 2));
        }
        ImGui::End();

    }

    void UILayer::Decoration() {

    }
}
