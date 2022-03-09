#include "linalg/linalg.hh"
#include <cassert>

int main() {
    using T = float;
    Array<T> a{1,2,7}, b{4,5,6};
    assert(evaluate(any(b < a)));
    return 0;
}