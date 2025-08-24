#pragma once

#include <cassert>
#include <boost/preprocessor/tuple.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/stringize.hpp>

#define GENENUM_MACRO_DELIM(r, data, elem) BOOST_PP_STRINGIZE(elem) ,
#define GENENUM_MACRO_CAT(elem) elem
#define GENENUM_MACRO_ENUM_DELIM(r, data, elem) GENENUM_MACRO_CAT(elem),

#define GENENUM(enumSize, enumType, ...)                                                                        \
    using enumType = enumSize;                                                                                  \
    class enumType##s                                                                                           \
    {                                                                                                           \
    public:                                                                                                     \
        using baseType = enumType;                                                                              \
                                                                                                                \
    private:                                                                                                    \
        static constexpr baseType kElemCount = BOOST_PP_VARIADIC_SIZE(__VA_ARGS__);                             \
                                                                                                                \
        static constexpr const std::array<std::string_view, kElemCount> kSourcesStringList = {                  \
            BOOST_PP_SEQ_FOR_EACH(GENENUM_MACRO_DELIM, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))};               \
                                                                                                                \
        static constexpr std::string_view kEnumName = #enumType;                                                \
                                                                                                                \
    public:                                                                                                     \
        enumType##s() = delete;                                                                                 \
        enum : baseType                                                                                         \
        {                                                                                                       \
            BOOST_PP_SEQ_FOR_EACH(GENENUM_MACRO_ENUM_DELIM, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))            \
        };                                                                                                      \
                                                                                                                \
        [[nodiscard]] static constexpr inline baseType getSize() noexcept                                       \
        {                                                                                                       \
            return kElemCount;                                                                                  \
        }                                                                                                       \
                                                                                                                \
        [[nodiscard]] static constexpr inline std::string_view toString(enumType source) noexcept               \
        {                                                                                                       \
            assert(source < kElemCount);                                                                        \
            return kSourcesStringList.at(source);                                                               \
        }                                                                                                       \
        [[nodiscard]] static constexpr inline bool fromString(std::string_view source, enumType& type) noexcept \
        {                                                                                                       \
            for (enumType i = 0; i < kElemCount; ++i)                                                           \
            {                                                                                                   \
                if (kSourcesStringList.at(i) == source)                                                         \
                {                                                                                               \
                    type = i;                                                                                   \
                    return true;                                                                                \
                }                                                                                               \
            }                                                                                                   \
                                                                                                                \
            return false;                                                                                       \
        }                                                                                                       \
        [[nodiscard]] static constexpr size_t maxSourceStringLength() noexcept                                  \
        {                                                                                                       \
            uint64_t maxLength = 0;                                                                             \
            for (enumType source = 0; source != kElemCount; ++source)                                           \
            {                                                                                                   \
                maxLength = std::max(maxLength, toString(source).size());                                       \
            }                                                                                                   \
                                                                                                                \
            return maxLength;                                                                                   \
        }                                                                                                       \
        [[nodiscard]] static constexpr std::string_view getEnumName()                                           \
        {                                                                                                       \
            return kEnumName;                                                                                   \
        }                                                                                                       \
    }
