#include <iostream>

class f {
public:
    int operator()()
    {
        return i++;
    }

private:
    int i = 0;
};

int main(int argc, char **argv)
{
#if 0
    auto f1 = [i = 0]() {
        return i++;
    };
#else
    f f1;
#endif

    std::cout << f1() << std::endl << f1() << std::endl << f1() << std::endl;

    return 0;
}
