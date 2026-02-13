#include "UI/SdlUi.hpp"

int main(int argc, char* argv[]) {
    // Suppress unused parameter warnings
    (void)argc;
    (void)argv;
    
    SdlUi ui;
    ui.run();

    return 0;
}
