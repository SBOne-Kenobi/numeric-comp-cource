#include "linalg/linalg.hh"
#include <cassert>

int main() {
    using T = float;
    Array<T> a{1,2,7}, b{4,5,6}, c{7,8,9};
    assert(where(any(b < a), a + b, b + c) == a + b);
    assert(where(all(b < a), a + b, b + c) == b + c);
    return 0;
}