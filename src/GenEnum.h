#ifndef GEN_ENUM_H
#define GEN_ENUM_H

#include <cassert>
#include <cstdint>
#include <string_view>
#include <boost/preprocessor/tuple.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/stringize.hpp>

#define GENENUM_MACRO_DELIM(r, data, elem) BOOST_PP_STRINGIZE(elem) ,
#define GENENUM_MACRO_CAT(elem) elem
#define GENENUM_MACRO_ENUM_DELIM(r, data, elem) GENENUM_MACRO_CAT(elem),

#define GENENUM(enumSize, enumType, ...)                                                                         \
    using enumType = enumSize;                                                                                   \
    class enumType##s                                                                                            \
    {                                                                                                            \
    public:                                                                                                      \
        using baseType = enumType;                                                                               \
                                                                                                                 \
    private:                                                                                                     \
        static constexpr const std::string_view kSourcesStringList[] = {                                         \
            BOOST_PP_SEQ_FOR_EACH(GENENUM_MACRO_DELIM, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))};                \
                                                                                                                 \
        static constexpr baseType ElemCount = sizeof(kSourcesStringList) / sizeof(*kSourcesStringList);          \
                                                                                                                 \
    public:                                                                                                      \
        enumType##s() = delete;                                                                                  \
        enum : baseType                                                                                          \
        {                                                                                                        \
            BOOST_PP_SEQ_FOR_EACH(GENENUM_MACRO_ENUM_DELIM, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))             \
        };                                                                                                       \
                                                                                                                 \
        [[nodiscard]] static constexpr inline baseType getSize() noexcept                                        \
        {                                                                                                        \
            return ElemCount;                                                                                    \
        }                                                                                                        \
                                                                                                                 \
        [[nodiscard]] static constexpr inline std::string_view to_string(enumType source) noexcept               \
        {                                                                                                        \
            assert(source < ElemCount);                                                                          \
            return kSourcesStringList[source];                                                                   \
        }                                                                                                        \
        [[nodiscard]] static constexpr inline bool from_string(std::string_view source, enumType& type) noexcept \
        {                                                                                                        \
            for (enumType i = 0; i < ElemCount; ++i)                                                             \
            {                                                                                                    \
                if (kSourcesStringList[i] == source)                                                             \
                {                                                                                                \
                    type = i;                                                                                    \
                    return true;                                                                                 \
                }                                                                                                \
            }                                                                                                    \
                                                                                                                 \
            return false;                                                                                        \
        }                                                                                                        \
        [[nodiscard]] static constexpr size_t maxSourceStringLength() noexcept                                   \
        {                                                                                                        \
            uint64_t maxLength = 0;                                                                              \
            for (enumType source = 0; source != ElemCount; ++source)                                             \
            {                                                                                                    \
                maxLength = std::max(maxLength, to_string(source).size());                                       \
            }                                                                                                    \
                                                                                                                 \
            return maxLength;                                                                                    \
        }                                                                                                        \
    }

#define GENENUM_MACRO_DELIM_K(r, data, elem) BOOST_PP_STRINGIZE(elem) ,
#define GENENUM_MACRO_CAT_K(elem) k##elem
#define GENENUM_MACRO_ENUM_DELIM_K(r, data, elem) GENENUM_MACRO_CAT_K(elem),

#define GENENUMK(enumSize, enumType, ...)                                                                        \
    using enumType = enumSize;                                                                                   \
    class enumType##s                                                                                            \
    {                                                                                                            \
    public:                                                                                                      \
        using baseType = enumType;                                                                               \
                                                                                                                 \
    private:                                                                                                     \
        static constexpr const std::string_view kSourcesStringList[] = {                                         \
            BOOST_PP_SEQ_FOR_EACH(GENENUM_MACRO_DELIM_K, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))};              \
                                                                                                                 \
        static constexpr baseType ElemCount = sizeof(kSourcesStringList) / sizeof(*kSourcesStringList);          \
                                                                                                                 \
    public:                                                                                                      \
        enumType##s() = delete;                                                                                  \
        enum : baseType                                                                                          \
        {                                                                                                        \
            BOOST_PP_SEQ_FOR_EACH(GENENUM_MACRO_ENUM_DELIM_K, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))           \
        };                                                                                                       \
                                                                                                                 \
        [[nodiscard]] static constexpr inline baseType getSize() noexcept                                        \
        {                                                                                                        \
            return ElemCount;                                                                                    \
        }                                                                                                        \
                                                                                                                 \
        [[nodiscard]] static constexpr inline std::string_view to_string(enumType source) noexcept               \
        {                                                                                                        \
            assert(source < ElemCount);                                                                          \
            return kSourcesStringList[source];                                                                   \
        }                                                                                                        \
        [[nodiscard]] static constexpr inline bool from_string(std::string_view source, enumType& type) noexcept \
        {                                                                                                        \
            for (enumType i = 0; i < ElemCount; ++i)                                                             \
            {                                                                                                    \
                if (kSourcesStringList[i] == source)                                                             \
                {                                                                                                \
                    type = i;                                                                                    \
                    return true;                                                                                 \
                }                                                                                                \
            }                                                                                                    \
                                                                                                                 \
            return false;                                                                                        \
        }                                                                                                        \
        [[nodiscard]] static constexpr size_t maxSourceStringLength() noexcept                                   \
        {                                                                                                        \
            uint64_t maxLength = 0;                                                                              \
            for (enumType source = 0; source != ElemCount; ++source)                                             \
            {                                                                                                    \
                maxLength = std::max(maxLength, to_string(source).size());                                       \
            }                                                                                                    \
                                                                                                                 \
            return maxLength;                                                                                    \
        }                                                                                                        \
    }

#endif  // GEN_ENUM_H
