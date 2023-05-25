#include <core/Application.hpp>
#include <iostream>

int main(int argc, char const* argv[])
{
    try {
        texplr::Application app;
        app.run();

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
