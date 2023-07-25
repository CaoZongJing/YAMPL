#pragma once

#define META_ITER_H
#ifdef META_ITER_H

#include "integral.h"
#include "type_traits.h"
#include "utility.h"

#define ITERATOR_BASE(NAME,TAG)                     \
    struct NAME {                                   \
        using iteartor_category = TAG;              \
    };

#define CHECK_ITERATOR_TAG(NAME,TAG)                \
    template<class _Ty>                             \
    using NAME = zampl::is_same<_Ty, TAG>;          \
    template<class _Ty>                             \
    using NAME##_t = typename NAME<_Ty>::type;      \
    template<class _Ty>                             \
    constexpr bool NAME##_v = NAME<_Ty>::value;

#define CONCEPT_PRE_ITERATOR_TAG(ITERATOR_TAG)                        \
    template<class _Ty>                                               \
    concept pre_concept_##ITERATOR_TAG = ::std::is_base_of<           \
    typename iterator_traits<_Ty>::iteartor_category,ITERATOR_TAG     \
    >::value;                                                         \

#define ENABLE_PRE_ITERATOR_TAG(ITERATOR_TAG)                         \
    template<class _Ty>                                               \
    using pre_##ITERATOR_TAG = enable_if<::std::is_base_of<           \
        typename iterator_traits<_Ty>::iteartor_category,             \
        ITERATOR_TAG>::value                                          \
    >;


namespace zampl {

    namespace iter {

        template<class _Ty>
        using check_type = typename Tvcheck::is_integral_t<typename _Ty::value_type>;


        struct input_iterator_tag {};
        struct output_iterator_tag {};
        struct forward_iterator_tag : public input_iterator_tag {};
        struct bidirectional_iterator_tag : public forward_iterator_tag {};
        struct random_access_iterator_tag : public bidirectional_iterator_tag {};

        // This definition is to realize the judgment of random iterator tag when using is_base_of.
        struct random_access_base_iterator_tag : public random_access_iterator_tag {};

        // Maintain a check on the unified hierarchy and remind programmers.
        ITERATOR_BASE(input_iterator, input_iterator_tag);
        ITERATOR_BASE(output_iterator, output_iterator_tag);
        ITERATOR_BASE(forward_iterator, forward_iterator_tag);
        ITERATOR_BASE(bidirectional_iterator, bidirectional_iterator_tag);
        ITERATOR_BASE(random_access_iterator, random_access_iterator_tag);

        // check
        CHECK_ITERATOR_TAG(is_input_iterator, input_iterator_tag);
        CHECK_ITERATOR_TAG(is_output_iterator, output_iterator_tag);
        CHECK_ITERATOR_TAG(is_forward_iterator, forward_iterator_tag);
        CHECK_ITERATOR_TAG(is_bidirectional_iterator, bidirectional_iterator_tag);
        CHECK_ITERATOR_TAG(is_random_access_iterator, random_access_iterator_tag);


        template<class _Iterator>
        struct iterator_traits {
            using iteartor_category = typename _Iterator::iteartor_category;
        };


        template<class _Ty, class _Tn, class _B = void, class _BB = void, class _BBB = void>
        struct iterator {
            using type = _Ty;     using index = _Tn;
            using backup = _B;     using backup2 = _BB;
            using backup3 = _BBB;

            //* By compatible bedefine such non-template of data structure
            using tag = typename _Ty::iteartor_category;
        };


        template<class _Container, class _Tn, class _B = void, class _BB = void, class _BBB = void>
        using make_iterator = zampl::enable_if<check_type<typename _Container::value_type>::value,
            iterator<_Container, _Tn, _B, _BB, _BBB>>;

        using type = iterator<forward_iterator, int_<10>, void>::type;
        using tag = iterator<forward_iterator, int_<10>, void>::tag;



        // Specialized type, To overload the function.
        #if __cplusplus <= 201102L
        static_assert(false);
        #elif __cplusplus >= 202002L
        CONCEPT_PRE_ITERATOR_TAG(input_iterator_tag);
        CONCEPT_PRE_ITERATOR_TAG(output_iterator_tag);
        CONCEPT_PRE_ITERATOR_TAG(bidirectional_iterator_tag);
        CONCEPT_PRE_ITERATOR_TAG(random_access_iterator_tag);

        ENABLE_PRE_ITERATOR_TAG(input_iterator_tag);
        ENABLE_PRE_ITERATOR_TAG(output_iterator_tag);
        ENABLE_PRE_ITERATOR_TAG(bidirectional_iterator_tag);
        ENABLE_PRE_ITERATOR_TAG(random_access_iterator_tag);

        #else
        ENABLE_PRE_ITERATOR_TAG(input_iterator_tag);
        ENABLE_PRE_ITERATOR_TAG(output_iterator_tag);
        ENABLE_PRE_ITERATOR_TAG(bidirectional_iterator_tag);
        ENABLE_PRE_ITERATOR_TAG(random_access_iterator_tag);
        #endif

    };  // namespace iter

};  // namespace zampl

#endif
