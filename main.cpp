#include "includes/Interface.h"

int main() {
    auto i = Interface::getInstance();
    i->startApp();
    Interface::free();
    return 0;
}
