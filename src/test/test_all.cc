#include "linalg/linalg.hh"
#include <cassert>

int main() {
    using T = float;
    Array<T> a{1,2,3}, b{4,5,6};
    Array<char> c(a<b);
    assert(evaluate(all(c)));
    return 0;
}