//
// Created by toor on 12/9/23.
//

#ifndef FASTMEASURE_LAYER_H
#define FASTMEASURE_LAYER_H
#include <string>


namespace Atom {
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnFixedUpdate() {}
        virtual void OnImGuiRender() {}


        inline const std::string& GetName() const { return m_Name; }
    protected:
        std::string m_Name;
    };

}

#endif //FASTMEASURE_LAYER_H
