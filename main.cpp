#include "includes/Interface.h"

int main() {
    auto i = Interface::getInstance();
    i->startApp();
    return 0;
}
