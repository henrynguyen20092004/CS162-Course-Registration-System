#include "Function/Function.h"
#include "Function/Input/Input.h"

int main() {
    try {
        std::cout << nameInput() << '\n';
    } catch (std::exception &error) {
        std::cout << error.what();
    }
    system("pause");
    return 0;
}
