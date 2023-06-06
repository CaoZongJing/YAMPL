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

#pragma once

#include<algorithm>
#include<type_traits>
#include<iterator>

#define P_TYPE_INTEGRAL_CONST(_Ty)                                  \
    template<_Ty val>                                               \
    struct integral_const<_Ty,val>{                                 \
    using value_type = _Ty;                                         \
    using type = integral_const;                                    \
    static constexpr value_type  value = val;                       \
    using init_type = integral_const<_Ty,val>;                      \
    using point_type = integral_const<_Ty, val - 1>;                \
    using next_type = integral_const<_Ty, val + 1>;                 \
    };


/* Comom arithmetic */
#define P_MULT_ARITHMETIC_OP(name, op)                                         \
  template <class N1, class N2, class... Nargs>                                \
  struct name {                                                                \
    using inner = name<N2, Nargs...>;                                          \
    using value_type = typename largest_int<typename N1::value_type,           \
                                            typename inner::value_type>::type; \
    using type = integral_const<value_type, N1::value op inner::value>;        \
    static constexpr value_type value = type::value;                           \
  };                                                                           \
  template <class N1, class N2>                                                \
  struct name<N1, N2> {                                                        \
    using value_type = typename largest_int<typename N1::value_type,           \
                                            typename N2::value_type>::type;    \
    using type = integral_const<value_type, (N1::value op N2::value)>;         \
    static constexpr value_type value = type::value;                           \
  };


// some arithmetic only make non-mult meta-function for such which.
#define P_ONE_ARITHMETIC_OP(name,op)                                        \
  template <class N1, class N2>                                             \
  struct name {                                                             \
    using value_type = typename largest_int<typename N1::value_type,        \
                                            typename N2::value_type>::type; \
    using type = integral_const<value_type, (N1::value op N2::value)>;      \
    static constexpr value_type value = type::value;                        \
  };


/* relational operation */
#define P_ONE_RELATIONAL_OP_BOOL(name, op)                             \
  template <class N1, class N2>                                        \
  struct name {                                                        \
    using value_type = bool;                                           \
    using type = integral_const<value_type, (N1::value op N2::value)>; \
    static constexpr value_type value = type::value;                   \
  };


/* Mult logical */
#define P_MULT_RELATIONAL_OP_BOOL(name,op)                                    \
  template<class _Ty, class _Tys, class... _Args>                             \
  struct name {                                                               \
    using value_type = bool;                                                  \
    using liner = name<_Tys, _Args...>;                                       \
    using type = integral_const<value_type, (_Ty::value op liner::value)>;    \
    static constexpr value_type value = type::value;                          \
  };                                                                          \
  template<class _Ty, class _Tys>                                             \
  struct name<_Ty, _Tys> {                                                    \
      using value_type = bool;                                                \
      using type = integral_const<value_type, (_Ty::value op _Tys::value)>;   \
      static constexpr value_type value = type::value;                        \
  };


namespace zampl {

  template<class _Ty1, class _Ty2, class _Ty3>
  struct type_convert {};

  // change type of function
  template<class _Ty, class _By_Ty>
  struct type_convert < _Ty, _Ty, _By_Ty> { using type = _By_Ty; };


  template<class _Ty, _Ty val>struct integral_const {};

  //* exist head and next
  template<bool val>
  struct integral_const<bool, val> {
    using value_type = bool;
    using type = integral_const;
    static constexpr value_type value = val;
  };


  P_TYPE_INTEGRAL_CONST(int);
  P_TYPE_INTEGRAL_CONST(unsigned int);
  P_TYPE_INTEGRAL_CONST(long long);


  template<int N>    using int_ = integral_const<int, N>;

  template<unsigned int N>using uint_ = integral_const<unsigned int, N>;

  template<long long N>using ll_ = integral_const<long long, N>;

  template<short N>  using short_ = integral_const<short, N>;

  template<bool N>  using bool_ = integral_const<bool, N>;


  template<class... Args>
  struct seq {};
  template<class _S, class _T>struct seq_push_back;

  template<class _T, class... Args>
  struct seq_push_back<seq<Args...>, _T> {
    using type = seq<Args..., _T>;
  };


  using true_type = bool_<true>;
  using false_type = bool_<false>;


  template<bool Judge, class _T, class _Ty>
  struct if_bool_ { using type = _T; };

  template<class _T, class _Ty>
  struct if_bool_<false, _T, _Ty> { using type = _Ty; };

  template<class Judge_space, class _T, class _Ty>
  struct if_ {
    using type = typename if_bool_<!!Judge_space::value, _T, _Ty>::type;
  };


  //* Type grade

  template <typename T>
  struct integral_rank;

  template <> struct integral_rank<bool> : uint_<1> {};
  template <> struct integral_rank<signed char> : uint_<2> {};
  template <> struct integral_rank<char> : uint_<3> {};
  template <> struct integral_rank<unsigned char> : uint_<4> {};
  template <> struct integral_rank<wchar_t> : uint_<5> {};
  template <> struct integral_rank<char16_t> : uint_<6> {};
  template <> struct integral_rank<short> : uint_<7> {};
  template <> struct integral_rank<unsigned short> : uint_<8> {};
  template <> struct integral_rank<char32_t> : uint_<9> {};
  template <> struct integral_rank<int> : uint_<10> {};
  template <> struct integral_rank<unsigned int> : uint_<11> {};
  template <> struct integral_rank<long> : uint_<12> {};
  template <> struct integral_rank<unsigned long> : uint_<13> {};
  template <> struct integral_rank<long long> : uint_<14> {};
  template <> struct integral_rank<unsigned long long> : uint_<15> {};


  // since if_ immediate using value such will cannot operator in non-computea field.
  template <class T1, class T2>
  using largest_int = if_bool_<integral_rank<T1>::value
    >=
    integral_rank<T2>::value, T1, T2>;


  namespace Arithmetic {

    template <class T>
    struct negate {
      using value_type = typename T::value_type;
      using type = integral_const<value_type, -T::value>;
      static constexpr value_type value = type::value;
    };

    P_MULT_ARITHMETIC_OP(plus, +);
    P_MULT_ARITHMETIC_OP(sub, -);
    P_MULT_ARITHMETIC_OP(mult, *);
    P_MULT_ARITHMETIC_OP(bitand_, &);
    P_MULT_ARITHMETIC_OP(bitor_, | );
    P_MULT_ARITHMETIC_OP(bitxor_, ^);

    P_ONE_ARITHMETIC_OP(minus, *);
    P_ONE_ARITHMETIC_OP(divides, / );
    P_ONE_ARITHMETIC_OP(modulus, %);
    P_ONE_ARITHMETIC_OP(left_shift, << );
    P_ONE_ARITHMETIC_OP(right_shift, >> );

  };


  namespace logical {

    P_ONE_RELATIONAL_OP_BOOL(equal_to, == );
    P_ONE_RELATIONAL_OP_BOOL(not_equal_to, != );
    P_ONE_RELATIONAL_OP_BOOL(greater, > );
    P_ONE_RELATIONAL_OP_BOOL(greater_equal, >= );
    P_ONE_RELATIONAL_OP_BOOL(less, < );
    P_ONE_RELATIONAL_OP_BOOL(less_equal, <= );

    P_MULT_RELATIONAL_OP_BOOL(and_, &&);
    P_MULT_RELATIONAL_OP_BOOL(or_, || );

    template<class _Ty>
    struct not_ {
      using value_type = bool;
      using type = integral_const<value_type, !_Ty::value>;
      static constexpr value_type value = type::value;
    };

  };


  template <class T>
  struct func_helper_type {
    using cond = typename logical::or_<typename std::is_scalar<T>::type,
      typename std::is_reference<T>::type>;

    using type = typename if_<typename cond::type, T,
      typename std::add_lvalue_reference<T>::type>::type;
  };


  template<class _Ty>struct is_refence_ { static constexpr bool value = false; };

  template<class _Ty> struct is_refence_<_Ty&> {
    static constexpr bool value = true;
  };


};    // namespace zampl
