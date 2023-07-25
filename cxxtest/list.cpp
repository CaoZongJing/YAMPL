/*
 * Copyright (c) 1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#include "../metalist.h"

#include <iostream>

inline void Clist_test() {

    using namespace zampl;
    using namespace zampl::list;

    using my_list = zampl::list::make_list<int_<323232>, int_<100>, int_<1000>, int_<10000>>;
    using clear_list = typename clear<my_list>::type;

    using begin_my_list = typename begin<my_list>::type;
    using deref_begin_list = typename deref<begin_my_list>::type;
    using push_back_list = push_back<my_list, int_<30>>::type;
    using next_begin_list = typename next<begin_my_list>::type;

    using push_front_list = typename zampl::list::push_front<my_list, int_<10>>::type;
    using value_type = typename deref<begin_my_list>::type;

    using pop_back_list = typename pop_back<my_list>::type;


    using insert_list = typename insert<my_list, int_<10>, next_begin_list>::type;
    using begin_insert_list = typename deref<typename begin<insert_list>::type>::type;
    std::cout << begin_insert_list::value << std::endl;

    using end_value_list_size = typename int_<size<insert_list>::type::value - 1>::type;
    using index_list = typename index<insert_list, end_value_list_size>::deref_type;

    std::cout << index_list::value << "\n";
}

int main(int argc, char* argv[]) {

    Clist_test();

    return 0;
}