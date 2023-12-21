//
// Created by toor on 12/18/23.
//

#ifndef FASTMEASURE_WIDGETS_H
#define FASTMEASURE_WIDGETS_H
#include "FastMeasure/fastmeasurepch.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))



namespace  ImGui {

    typedef ImDrawFlags ImDrawCornerFlags;
    enum ImDrawCornerFlags_
    {
        ImDrawCornerFlags_None      = ImDrawFlags_RoundCornersNone,         // Was == 0 prior to 1.82, this is now == ImDrawFlags_RoundCornersNone which is != 0 and not implicit
        ImDrawCornerFlags_TopLeft   = ImDrawFlags_RoundCornersTopLeft,      // Was == 0x01 (1 << 0) prior to 1.82. Order matches ImDrawFlags_NoRoundCorner* flag (we exploit this internally).
        ImDrawCornerFlags_TopRight  = ImDrawFlags_RoundCornersTopRight,     // Was == 0x02 (1 << 1) prior to 1.82.
        ImDrawCornerFlags_BotLeft   = ImDrawFlags_RoundCornersBottomLeft,   // Was == 0x04 (1 << 2) prior to 1.82.
        ImDrawCornerFlags_BotRight  = ImDrawFlags_RoundCornersBottomRight,  // Was == 0x08 (1 << 3) prior to 1.82.
        ImDrawCornerFlags_All       = ImDrawFlags_RoundCornersAll,          // Was == 0x0F prior to 1.82
        ImDrawCornerFlags_Top       = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight,
        ImDrawCornerFlags_Bot       = ImDrawCornerFlags_BotLeft | ImDrawCornerFlags_BotRight,
        ImDrawCornerFlags_Left      = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_BotLeft,
        ImDrawCornerFlags_Right     = ImDrawCornerFlags_TopRight | ImDrawCornerFlags_BotRight
    };


    bool Rendertab(const char *icon, const char *label, bool selected ) {
        ImGuiWindow *window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext &g = *GImGui;
        const ImGuiStyle &style = g.Style;
        const ImGuiID id = window->GetID(icon);
        const ImVec2 label_size = ImGui::CalcTextSize(icon);

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = {135, 30};

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ImGui::ItemSize(size, 0);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

        if (hovered || held)
            ImGui::SetMouseCursor(9);

        static std::map<ImGuiID, float> hover_animation;
        auto it_hover = hover_animation.find(id);
        if (it_hover == hover_animation.end()) {
            hover_animation.insert({id, 0.f});
            it_hover = hover_animation.find(id);
        }
        it_hover->second = ImClamp(
                it_hover->second + (0.2f * ImGui::GetIO().DeltaTime * (hovered || IsItemActive() ? 1.f : -1.f)), 0.0f,
                0.15f);
        it_hover->second *= min(GetStyle().Alpha * 1.2, 1.f);

        static std::map<ImGuiID, float> filled_animation;
        auto it_filled = filled_animation.find(id);
        if (it_filled == filled_animation.end()) {
            filled_animation.insert({id, 0.f});
            it_filled = filled_animation.find(id);
        }
        it_filled->second = ImClamp(
                it_filled->second + (2.55f * ImGui::GetIO().DeltaTime * (ImGui::IsItemHovered() ? 1.f : -1.0f)),
                it_hover->second, 1.f);
        it_filled->second *= min(GetStyle().Alpha * 1.2, 1.f);

        static std::map<ImGuiID, float> fill_animation;
        auto it_fill = fill_animation.find(id);
        if (it_fill == fill_animation.end()) {
            fill_animation.insert({id, 0.f});
            it_fill = fill_animation.find(id);
        }
        it_fill->second = ImClamp(it_fill->second + (2.55f * ImGui::GetIO().DeltaTime * (selected ? 1.f : -1.0f)),
                                  it_hover->second, 1.f);
        it_fill->second *= min(GetStyle().Alpha * 1.2, 1.f);

        GetWindowDrawList()->AddText( ImVec2(bb.Min.x + 40, bb.Min.y + 5),
                                     ImColor(65, 65, 65, int(255 * GetStyle().Alpha)), label);
        GetWindowDrawList()->AddText( ImVec2(bb.Min.x + 10, bb.Min.y + 5),
                                     ImColor(65, 65, 65, int(255 * GetStyle().Alpha)), icon);

        if (selected) {
            GetWindowDrawList()->AddRectFilled(ImVec2(bb.Min.x, bb.Min.y), ImVec2(bb.Max.x, bb.Max.y),
                                               ImColor(41, 41, 41, int(255 * it_fill->second)), 5);
            GetWindowDrawList()->AddRectFilled(ImVec2(pos.x, pos.y + 5),
                                               ImVec2(pos.x + it_fill->second * 2, pos.y + 25),
                                               ImColor(174, 139, 148, int(255 * GetStyle().Alpha)), 10.f,
                                               ImDrawCornerFlags_Right);

            GetWindowDrawList()->AddText(ImVec2(bb.Min.x + 10, bb.Min.y + 5),
                                         ImColor(255, 255, 255, int(255 * it_fill->second)), icon);
            GetWindowDrawList()->AddText( ImVec2(bb.Min.x + 40, bb.Min.y + 5),
                                         ImColor(255, 255, 255, int(255 * it_fill->second)), label);
        }

        if (ImGui::IsItemHovered()) {
            GetWindowDrawList()->AddRect(ImVec2(bb.Min.x - 1, bb.Min.y), ImVec2(bb.Max.x, bb.Max.y),
                                         ImColor(75, 75, 75, int(255 * it_filled->second)), 5);
        }

        return pressed;
    }



    void rage_tab()
    {
//        ImGui::SetCursorPos(ImVec2(169, 38));
//        ImGui::MenuChild("Override config", ImVec2(320, 57));
//        {
//            const char* type[] = { "Auto Snipers (G3SG1, SCAR-20, SC...)", "Types", "Select" };
//            static int combo;
//
//            ImGui::Combo(" ", &combo, type, IM_ARRAYSIZE(type));
//        }
//        ImGui::EndChild();
//
//        ImGui::SetCursorPos(ImVec2(169, 134));
//        ImGui::MenuChild("General", ImVec2(320, 240));
//        {
//            static bool active = true;
//            static bool inactive = false;
//
//            ImGui::Spacing();
//            ImGui::Checkbox("Enable Particles", &particles);
//
//            static int procent = 60;
//            ImGui::SliderInt("Fov", &procent, 0, 100, "%d%%");
//
//            ImGui::Checkbox("Autofire", &inactive);
//            ImGui::Checkbox("Autowall", &active);
//            ImGui::Checkbox("Silent aim", &active);
//            ImGui::Checkbox("Quick peek", &active);
//        }
//        ImGui::EndChild();
//
//        ImGui::SetCursorPos(ImVec2(169, 413));
////        ImGui::MenuChild("Exploits", ImVec2(320, 107));
//        {
//            static bool active = true;
//            static bool inactive = false;
//
//            ImGui::Spacing();
//            ImGui::Checkbox("Lag Peek", &active);
//            ImGui::Checkbox("Hide Shots", &active);
//            ImGui::Checkbox("Double Tab", &active);
//        }
//        ImGui::EndChild();
//
//        ImGui::SetCursorPos(ImVec2(505, 38));
//        ImGui::MenuChild("Accuracy", ImVec2(320, 286));
//        {
//            static bool active = true;
//            static bool inactive = false;
//
//            const char* type[] = { "Type", "Types", "Select" };
//            static int combo;
//
//            ImGui::Spacing();
//            ImGui::Checkbox("Automatic stop", &active);
//
//            ImGui::Combo("Combo", &combo, type, IM_ARRAYSIZE(type));
//
//            ImGui::Checkbox("Hitchance", &active);
//
//            static int procentw = 60;
//            ImGui::SliderInt("Hitchance value", &procentw, 0, 100, "%d%%");
//
//            static int procente = 20;
//            ImGui::SliderInt("Damage value", &procente, 0, 100, "%d%%");
//
//            static int procent = 56;
//            ImGui::SliderInt("Damage override value", &procent, 0, 100, "%d%%");
//        }
//        ImGui::EndChild();
//
//        ImGui::SetCursorPos(ImVec2(505, 363));
////        ImGui::M("Misc", ImVec2(320, 157));
////        {
////            static bool active = true;
////            static bool inactive = false;
////
////            ImGui::Spacing();
////            ImGui::Checkbox("Prefer a pont", &inactive);
////            ImGui::Checkbox("Prefer body aim", &active);
////            ImGui::Checkbox("ignore limbs when moving", &active);
////        }
//        ImGui::EndChild();

    }
}

#endif //FASTMEASURE_WIDGETS_H
