#include"../metaiter.h"
#include<iostream>

using namespace std;

using namespace zampl;
using namespace zampl::iter;

#if __cplusplus >= 202002L
template<pre_concept_bidirectional_iterator_tag T>
constexpr int pluser(int a, int b) {
    return a + b;
}

#endif

template<class _Ty, class = pre_bidirectional_iterator_tag<_Ty>>
constexpr int mult(int a, int b) {
    return a * b;
}


int main() {

    struct A {};
    struct B :A {};
    struct C : B {};
    static_assert(::std::is_base_of<A, B>::value == true);

    constexpr int b = mult<zampl::iter::bidirectional_iterator>(10, 20);


    static_assert(b == 200);

    #if __cplusplus >= 202002L
    constexpr int c = pluser<zampl::iter::bidirectional_iterator>(10, 20);
    static_assert(c == 30);
    cout << c << endl;
    #endif


    cout << "hello world" << endl;
    return 0;

}