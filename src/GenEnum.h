#ifndef GEN_ENUM_HPP
#define GEN_ENUM_HPP

#include <string_view>
#include <cstdint>
#include <cassert>
#include <boost/preprocessor/tuple.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/stringize.hpp>

#define GENENUM_MACRO_DELIM(r, data, elem) BOOST_PP_STRINGIZE(elem) ,
#define GENENUM_MACRO_CAT_K(elem) k##elem
#define GENENUM_MACRO_ENUM_DELIM(r, data, elem) GENENUM_MACRO_CAT_K(elem),

#define GENENUM(enumSize, enumType, ...)                                                                         \
    using enumType = enumSize;                                                                                   \
    class enumType##s                                                                                            \
    {                                                                                                            \
    private:                                                                                                     \
        static constexpr const std::string_view kSourcesStringList[] = {                                         \
            BOOST_PP_SEQ_FOR_EACH(GENENUM_MACRO_DELIM, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))};                \
                                                                                                                 \
    public:                                                                                                      \
        enumType##s()  = delete;                                                                                 \
        using baseType = enumType;                                                                               \
        enum : baseType                                                                                          \
        {                                                                                                        \
            BOOST_PP_SEQ_FOR_EACH(GENENUM_MACRO_ENUM_DELIM, _, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))             \
        };                                                                                                       \
        static constexpr baseType kCount = sizeof(kSourcesStringList) / sizeof(*kSourcesStringList);             \
                                                                                                                 \
        [[nodiscard]] static constexpr inline std::string_view to_string(enumType source) noexcept               \
        {                                                                                                        \
            assert(source < kCount);                                                                             \
            return kSourcesStringList[source];                                                                   \
        }                                                                                                        \
        [[nodiscard]] static constexpr inline bool from_string(std::string_view source, enumType& type) noexcept \
        {                                                                                                        \
            for (enumType i = 0; i < kCount; ++i)                                                                \
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
            auto maxFn         = [](uint64_t a, uint64_t b) { return (a < b) ? b : a; };                         \
            for (enumType source = 0; source != kCount; ++source)                                                \
            {                                                                                                    \
                maxLength = maxFn(maxLength, to_string(source).size());                                          \
            }                                                                                                    \
                                                                                                                 \
            return maxLength;                                                                                    \
        }                                                                                                        \
    }

#endif
