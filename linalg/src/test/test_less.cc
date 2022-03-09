#include "linalg/linalg.hh"
#include <cassert>

int main() {
    using T = float;
    Array<T> a{1,2,3}, b{4,1,6};
    Array<char> c(a<b);
    for (int i = 0; i < 3; i++) {
        assert((a(i) < b(i)) == c(i));
    }
    return 0;
}