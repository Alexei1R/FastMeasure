#include "FastMeasure/Application.h"


int main() {
    Atom::Application* app = new Atom::Application();
    app->Run();
    delete app;
    return 0;
}