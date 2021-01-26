#include <iostream>

int add(int a, int b) {
    return a + b;
}

void test_add(void) {
    std::cout << 11 << " + " << 22 << " = " << add(11, 22) << std::endl;
    std::cout << -11 << " + " << -22 << " = " << add(-11, -22) << std::endl;
    std::cout << 123 << " + " << -321 << " = " << add(123, -321) << std::endl;
}

int main(int argc, char **argv) {
    test_add();

    return 0;
}

