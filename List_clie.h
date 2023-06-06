/*
 * Copyright (c) 1997   -zorjen122
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

#include "Commom components.h"

namespace zampl {
    struct iterator_tag {};

    template<class _Ty, class _Tn, class _B = void, class _BB = void, class _BBB = void>
    struct iterator {
        using type = _Ty;     using index = _Tn;
        using backup = _B;     using backup2 = _BB;
        using backup3 = _BBB;

        //* By compatible bedefine such non-template of data structure
        using tag = iterator_tag;
    };

    template <class T>
    struct sequence_tag {
        using type = typename T::tag;
    };

    struct forward_iterator_tag {};

    template <class _Ty>
    struct iterator_sequence_tag {
        using type = typename _Ty::tag;
    };


    template <class Tag>    struct begin_impl {};
    template <class Tag>    struct end_impl {};

    template <class Tag>    struct size_impl {};
    template<class _Tag>    struct insert_impl {};
    template<class _Tag>    struct index_impl {};


    template <class Tag>    struct next_impl {};
    template <class Tag>    struct prior_impl {};

    template <class Tag>    struct deref_impl {};
    template <class Tag>    struct clear_impl {};


    template <class Tag>    struct advance_impl {};
    template <class Tag>    struct distance_impl {};


    template <class Tag>    struct push_back_impl {};
    template<class _Tag>    struct push_front_impl {};
    template<class _Tag>    struct pop_back_impl {};
    template<class _Tag>    struct pop_front_impl {};


    template<class _Tag>    struct sort_impl {};


    template <class T> struct begin
        : begin_impl<typename sequence_tag<T>::type>::template apply<T> {};

    template <class T> struct end
        : end_impl<typename sequence_tag<T>::type>::template apply<T> {};

    template <class T> struct size
        : size_impl<typename sequence_tag<T>::type>::template apply<T> {};


    template <class T> struct next
        : next_impl<typename iterator_sequence_tag<T>::type>::template apply<T> {};

    template <class T> struct prior
        : prior_impl<typename iterator_sequence_tag<T>::type>::template apply<T> {};

    template <class T> struct deref
        : deref_impl<typename iterator_sequence_tag<T>::type>::template apply<T> {};


    template <class T> struct clear
        : clear_impl<typename sequence_tag<T>::type>::template apply<T> {};


    template <class T, class N> struct advance
        : advance_impl<typename iterator_sequence_tag<T>::type>::template
        apply<T, N> {};


    template <class T, class U> struct distance
        : distance_impl<typename iterator_sequence_tag<T>::type>::template apply<
        T, U> {};


    template <class T, class U> struct push_back
        : push_back_impl<typename sequence_tag<T>::type>::template apply<T, U> {};

    template<class _Ty, class _Tv>
    struct push_front
        : push_front_impl<typename sequence_tag<_Ty>::type>::template apply<_Ty, _Tv>{};


    template<class _Ty> struct pop_back
        : pop_back_impl<typename sequence_tag<_Ty>::type>::template apply<_Ty>{};


    template<class _Ty>
    struct pop_front
        : pop_front_impl<typename sequence_tag<_Ty>::type>::template apply<_Ty>{};


    template <class T, class U, class B>
    struct insert
        : insert_impl<typename sequence_tag<T>::type>::template apply<T, B, U> {};


    template<class _Ty, class _N>
    struct index
        : index_impl<typename iterator_sequence_tag<_Ty>::type>::template apply<_Ty, _N>{};

    template<class _Ty, int N>
    struct index_value
        : index_impl<typename iterator_sequence_tag<_Ty>::type>::template apply_value<_Ty, N>{};


    template<class _Ty>struct sort
        : sort_impl<typename sequence_tag<_Ty>::type>::template apply<_Ty>{};


    struct list_tag {};

    template <class... Args>
    struct list {
        using iterator_category_tag = forward_iterator_tag;
        using tag = list_tag;
    };

    template<>
    struct begin_impl<list_tag> {
        template<class _Ty>
        struct apply;

        template<template<class...>class _Ty, class... _args>
        struct apply<_Ty<_args...>> {
            using type = iterator<_Ty<_args...>,
                integral_const<int, 0>, _Ty<_args...>>;
        };
    };

    template<>
    struct end_impl<list_tag> {
        template<class _Ty>
        struct apply;

        template<class _Ty>
        struct apply_element;

        template<template<class...>class _Ty, class... _args>
        struct apply<_Ty<_args...>> {
            using type = iterator<_Ty<>,
                integral_const<int, sizeof...(_args)>,
                _Ty<_args...>>;
        };
    };


    template <>
    struct size_impl<list_tag> {
        template <class _Ty>
        struct apply;

        template <template <class...> class _Ty, class... _args>
        struct apply<_Ty<_args...>> {
            using type = integral_const<int, sizeof...(_args)>;
        };
    };


    template<>
    struct clear_impl<list_tag> {
        template<class _Ty>
        struct apply;

        template <template <class...> class _Ty, class... _args>
        struct apply<_Ty<_args...>> {
            using type = _Ty<>;
        };
    };


    template <>
    struct push_back_impl<list_tag> {
        template <class _Ty, class _Tv>
        struct apply;

        template <template <class...> class _Ty, class _Tv, class... _args>
        struct apply<_Ty<_args...>, _Tv> {
            using type = _Ty<_args..., _Tv>;
        };
    };


    template<>
    struct next_impl<iterator_tag> {
        template<class _Ty>
        struct apply;

        template<template<class...>class _Ty, class _Tn, class _Tv, class _Tp, class... _args>
        struct apply<iterator<_Ty<_Tv, _args...>, _Tn, _Tp>> {
            using type = iterator<_Ty<_args...>, typename _Tn::next_type, _Tp>;
        };

        //* only one
        template<template<class...>class _Ty, class _Tn, class _Tv, class _Tp>
        struct apply<iterator<_Ty<_Tv>, _Tn, _Tp>> {
            using type = iterator<_Ty<>, typename _Tn::next_type, _Tp>;
        };
    };


    struct none_tag {};
    struct none { using tag = none_tag; };


    template<>
    struct deref_impl<iterator_tag> {
        template<class _Ty>
        struct apply;

        template<template<class...>class _Ty, class _Tn, class _Tv,
            class _Tp, class... _args>
        struct apply<iterator<_Ty<_Tv, _args...>, _Tn, _Tp>> {
            using type = _Tv;
        };

        template<template<class...>class _Ty, class _Tn, class _Tp>
        struct apply<iterator<_Ty<>, _Tn, _Tp>> {
            using type = none;
        };
    };



    template<>
    struct push_front_impl<list_tag> {
        template<class _Ty, class _Tv_begin, class _Tv_end>
        struct apply_impl {
            using inner = typename push_back<_Ty, typename deref<_Tv_begin>::type>::type;
            using type = typename apply_impl<inner, typename next<_Tv_begin>::type, _Tv_end>::type;
        };

        template<class _Ty, class _Tv_end>
        struct apply_impl<_Ty, _Tv_end, _Tv_end> { using type = _Ty; };

        template<class _Ty, class _Tv>
        struct apply {
            using init = typename push_back<typename clear<_Ty>::type, _Tv>::type;
            using type = typename apply_impl<init,
                typename begin<_Ty>::type,
                typename end<_Ty>::type>::type;
        };
    };


    template<>
    struct pop_back_impl<list_tag> {
        template<class _Ty, class _Tv_begin, class _Tv_N, class _Tv_end>
        struct apply_impl {
            using inner = typename push_back<_Ty, typename deref<_Tv_begin>::type>::type;
            using type = typename apply_impl<inner, typename next<_Tv_begin>::type,
                typename next<_Tv_N>::type, _Tv_end>::type;
        };

        template<class _Ty, class _Tv_P, class _Tv_end>
        struct apply_impl<_Ty, _Tv_P, _Tv_end, _Tv_end> { using type = _Ty; };

        template<class _Ty>
        struct apply {
            using init = typename clear<_Ty>::type;
            using type = typename apply_impl<init,
                typename begin<_Ty>::type,
                typename next<typename begin<_Ty>::type>::type,
                typename end<_Ty>::type>::type;
        };
    };

    template<>
    struct pop_front_impl<list_tag> {
        template<class _Ty, class _Tv_begin, class _Tv_end>
        struct apply_impl {
            using inner = typename push_back<_Ty, typename deref<_Tv_begin>::type>::type;
            using type = typename apply_impl<inner, typename next<_Tv_begin>::type, _Tv_end>::type;
        };

        template<class _Ty, class _Tv_end>
        struct apply_impl<_Ty, _Tv_end, _Tv_end> { using type = _Ty; };

        template<class _Ty>
        struct apply {
            using init = typename clear<_Ty>::type;
            using type = typename apply_impl<init,
                typename next<typename begin<_Ty>::type>::type,
                typename end<_Ty>::type>::type;
        };
    };


    template<>
    struct insert_impl<list_tag> {
        template <class R, class U, class B, class I, class E>
        struct apply_impl {
            using inner = typename push_back<R, typename deref<I>::type>::type;
            using type =
                typename apply_impl<inner, U, B, typename next<I>::type, E>::type;
        };

        template <class R, class U, class I, class E>
        struct apply_impl<R, U, I, I, E> {
            using inner = typename push_back<R, U>::type;
            using inner2 = typename push_back<inner, typename deref<I>::type>::type;
            using type = typename apply_impl<inner2, I, U, typename next<I>::type, E>::type;
        };

        template <class R, class U, class B, class E>
        struct apply_impl<R, U, B, E, E> {
            using type = R;
        };

        template <class R, class U, class E>
        struct apply_impl<R, U, E, E, E> {
            using type = typename push_back<R, U>::type;
        };

        template <class T, class B, class U>
        struct apply {
            using init = typename clear<T>::type;
            using type = typename apply_impl<init, U, B, typename begin<T>::type,
                typename end<T>::type>::type;
        };
    };


    template<>
    struct index_impl<list_tag> {

        template<class _Ty, int N>
        struct apply_impl { using type = typename apply_impl<typename next<_Ty>::type, N - 1>::type; };

        template<class _Ty> struct apply_impl<_Ty, 0> { using type = _Ty; };


        template<class _Ty, class _N>struct apply {
            using type = typename apply_impl<typename begin<_Ty>::type, _N::value>::type;
            using deref_type = typename deref<type>::type;
        };

        template<class _Ty, int _N>
        struct apply_value {
            using type = typename apply_impl<typename begin<_Ty>::type, _N>::type;
            using deref_type = typename deref<type>::type;
        };
    };


    // TODO
    template<>
    struct sort_impl<list_tag> {

        template<class _Ty, class _Tv, class _Tn, class _To, class _Tp, class _TY>
        struct apply_impl {
            using trans = _Tv;  using type = _Ty;
            using _PP = typename begin<_Ty>::type;

      //* ERROR 
            using get = typename if_<typename logical
                ::greater<typename deref<trans>::type, typename deref<_Tn>::type>::type,
                typename apply_impl<type, _Tn, trans, typename next<_To>::type, _Tp, _TY>::get,
                typename apply_impl<type, trans, typename next<_Tn>::type, _To, _Tp, _TY>::get>::type;
        };
        template<class _Ty, class _Tv, class _Tn, class _Tp, class _TY>
        struct apply_impl<_Ty, _Tv, _Tn, _Tp, _Tp, _TY> {
            using _PP = typename begin<_Ty>::type;
            using trans = typename next<_Tv>::type;
            using type = typename push_back<_Ty, typename deref<_Tv>::type>::type;

            using get = typename if_<typename
                logical::greater<typename deref<trans>::type, typename deref<_Tn>::type>::type,
                typename apply_impl<type, _Tn, trans, _PP, _Tp, _TY>::get,
                typename apply_impl<type, trans, typename next<_Tn>::type, _PP, _Tp, _TY>::get>::type;
        };

        template<class _Ty, class _Tv, class _Tp, class _TY>
        struct apply_impl<_Ty, _Tv, _Tp, _Tp, _Tp, _TY> {

            using get = typename if_<typename logical::greater<typename deref<_Tv>::type,
                typename deref<typename next<_Tv>::type>::type>::type, typename next<_Tv>::type, _Tv>::type;

            using type = typename push_back<_Ty, typename deref<get>::type>::type;
        };


        template<class _Ty>
        struct apply {
            using init = typename clear<_Ty>::type;
            using iter_start = typename begin<_Ty>::type;
            using iter_end = typename index<_Ty, typename size<_Ty>::type>::type;
            using type = typename apply_impl<init,
                iter_start,
                typename next<iter_start>::type,
                iter_end,
                typename end<_Ty>::type, _Ty>::type;
        };
    };


};      // namespace zampl
