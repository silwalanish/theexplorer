#include <iostream>

#include <core/Application.hpp>
#include <game/ShowcaseScene.hpp>

int main(int argc, char const* argv[])
{
    try {
        texplr::Application app;
        std::shared_ptr<texplr::Scene> scene = std::static_pointer_cast<texplr::Scene>(std::make_shared<texplr::ShowcaseScene>(app.getEventBus()));
        app.setScene(scene);
        app.run();

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
