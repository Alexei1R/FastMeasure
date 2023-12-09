#include "FastMeasure/Application.h"
#include <filesystem>

int main(){
    Atom::Application* app = new Atom::Application();
    app->Run();
    delete app;
}