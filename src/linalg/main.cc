#include <iostream>

#include <linalg/linalg.hh>

int main(int argc, char* argv[]) {
    using T = float;
    Array<T> a{1,2,3}, b{4,5,6}, c{7,8,9};
    Array<T> d(a+b+c);
    std::cout << (a+b+c) << std::endl;
    std::cout << evaluate(a+b+c) << std::endl;
    std::cout << d << std::endl;
    return 0;
}
