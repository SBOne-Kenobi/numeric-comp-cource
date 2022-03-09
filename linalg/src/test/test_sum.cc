#include "linalg/linalg.hh"
#include <cassert>

int main() {
    using T = float;
    Array<T> a{1,2,3}, b{4,5,6}, c{7,8,9};
    Array<T> d(a+b+c);
    Array<T> exp{12, 15, 18};
    assert(d == exp);
    return 0;
}