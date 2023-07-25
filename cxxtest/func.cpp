#include "../metafunc.h"

#include <iostream>

template<class A, class B>
struct ADD {
    static constexpr A oper(A a, B b) {
        return a + b;
    }
};
int main() {
    using t = zampl::function<ADD<int, int>>::value_type<zampl::int_<10>, zampl::int_<10>>;
    static constexpr unsigned int v = t::value;

    int arr[v];

    std::cout << sizeof(arr) << "\t" << v << "\n";
    return 0;
}