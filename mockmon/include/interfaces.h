#pragma once

#include <string>
#include <string_view>
#include <type_traits>
#include <initializer_list>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>

namespace mockmon
{

    //needed because we are skipping braced initilization.
    template <typename T>
    using vector_type_T = std::vector<T>;

    template <typename V, typename T>
    [[nodiscard]] static auto constexpr MakePredicator(const T &t)
    {
        return ([&t](const V &el)
                { return el.IsSameAs(t); });
    }

    /**
     * @brief 
     * returns true/false if any element in the container matches the predicate
     * should eventually be replaced by simpler use?
     * how can i use this for any container type
     * @tparam T 
     * @tparam UnaryPredicate 
     * @param v a vector 
     * @param p a predicate on T
     * @return true 
     * @return false 
     */
    template <typename T, class UnaryPredicate>
    [[nodiscard]] bool constexpr ContainerHas(const std::vector<T> &v, const UnaryPredicate &p)
    {
        return std::any_of(std::begin(v), std::end(v), [&](const T &e)
                           { return p(e); });
    }

    [[nodiscard]] std::string AppendAll(const std::initializer_list<std::string_view> &words);

    template <typename T, std::enable_if_t<std::is_enum_v<T>, bool> = true>
    class IdentifiybleModule
    {
    public:
        explicit IdentifiybleModule(T &t) : m_identifier(t) {}
        explicit IdentifiybleModule(T &&t) : m_identifier(t) {}

        IdentifiybleModule(const IdentifiybleModule &other) : m_identifier(other.m_identifier) {}
        virtual ~IdentifiybleModule() = default;
        [[nodiscard]] bool constexpr IsSameAs(T t) const { return m_identifier == t; }
        [[nodiscard]] const T constexpr Identifier() const { return m_identifier; }

    private:
        const T m_identifier;
    };

    template <typename T, std::enable_if_t<std::is_enum_v<T>, bool> = true>
    class DescribleModule : public IdentifiybleModule<T>
    {
    public:
        explicit DescribleModule(T &t) : IdentifiybleModule<T>(t) {}
        explicit DescribleModule(T &&t) : IdentifiybleModule<T>(t) {}

        DescribleModule(const DescribleModule &other) : IdentifiybleModule<T>(other.Identifier()) {}
        DescribleModule(const DescribleModule &&other) : IdentifiybleModule<T>(other.Identifier()) {}

        virtual ~DescribleModule() = default;
        [[nodiscard]] virtual std::string Describe() const = 0;
    };

    //creates dictionary items when the key is the first argument for the object
    // no idea why it sometimes works ans sometimes doesnt, has maybe const, may double ref...
    // this requires a public ctor... maybe i can make this a friend class/function?
    template <typename T, typename K, typename... Args, std::enable_if_t<std::is_constructible_v<T, K, Args...>, bool> = true>
    [[nodiscard]] std::pair<K, T> constexpr MakeDictionaryPair(const K &key, const Args... args)
    {
        const T t(key, args...);
        return (std::pair<K, T>(key, t));
    }

}