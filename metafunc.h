#pragma once

#define META_FUNC_H
#ifdef META_FUNC_H

#include "type_traits.h"
#include "utility.h"

namespace zampl {

    template<class _Ret>
    struct function;

    template<template<class...>class _F, class... _Args>
    struct function<_F<_Args...>> {

        template<class... T>
        using Ret_type = decltype(_F<_Args...>::oper(T::value...));

        template<class... T>
        using value_type = integral_const<Ret_type<T...>,
            _F<_Args...>::oper(T::value...)>;

        template<class... T>
        static constexpr Ret_type<T...> value = value_type<T...>::value;
    };

};      // namesapce zampl

#endif