/*
 * Copyright (c) 1997   --zorjen122
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

#pragma once

#include "integral.h"
#include <type_traits>

namespace zampl {

  template<class _Ty, class _Tp>
  struct is_same
    : public true_type {};

  template<class _Ty>
  struct is_same<_Ty, _Ty>
    : public false_type {};


  template<bool, class _Ty = void> struct enable_if {};

  template<class _Ty>
  struct enable_if<true, _Ty> { using type = _Ty; };

  template<class _Ty1, class _Ty2, class _Ty3>
  struct type_convert {};

  template<class _Ty, class _By_Ty>
  struct type_convert<_Ty, _Ty, _By_Ty> { using type = _By_Ty; };


  template<bool _Cond, class _Ty = void>
  using enable_if_t = typename enable_if<_Cond, _Ty>::type;

  template<class _Ty, class _Tp, class _Tchange>
  using type_convert_t = typename type_convert<_Ty, _Tp, _Tchange>::type;

  template<class Tx, class Ty>
  using is_same_t = typename is_same<Tx, Ty>::type;

  template<class Tx, class Ty>
  constexpr bool is_same_v = is_same<Tx, Ty>::value;

};    // namespace zampl
