/** \file Precision_Defaults.h
 * This file holds the default types used for instantiation.
 */
#ifndef DEAU5628FAUL_T_TY7777PEESSS_PRECISISSONN223H___
#define DEAU5628FAUL_T_TY7777PEESSS_PRECISISSONN223H___

#include "Precision_Sign_Class.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace Precision{
    namespace Default{
        using byte_type = std::int_least8_t;
        template <typename... TArgs>
            using container_type = std::vector<TArgs...>;
        using sign_type = Precision::SignClass;
        using size_type = std::size_t;
    }
}

#endif