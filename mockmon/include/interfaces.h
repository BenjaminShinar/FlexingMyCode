#pragma once

#include <string>
#include <string_view>
#include <type_traits>
#include <initializer_list>
#include <utility>
#include <vector>
namespace mockmon
{   
    //needed in type effectivness chart file, because we are skipping braced initilization.
    template <typename T>
    using vector_type_T=std::vector<T>;
    
    std::string AppendAll(const std::initializer_list<std::string_view> &words);

    template <typename T, std::enable_if_t<std::is_enum_v<T>, bool> = true>
    class IdentifiybleModule
    {
    public:
        explicit IdentifiybleModule(T &t) : m_identifier(t) {}
        explicit IdentifiybleModule(T &&t) : m_identifier(t) {}

        IdentifiybleModule(const IdentifiybleModule &other) : m_identifier(other.m_identifier) {}
        virtual ~IdentifiybleModule() = default;
        const T Identifier() const { return m_identifier; }

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
        virtual std::string Describe() const = 0;
    };

    //creates dictionary items when the key is the first argument for the object
    // no idea why it sometimes works ans sometimes doesnt
    // this requires a public ctor... maybe i can make this a friend class/function?
    template <typename T,typename K, typename ... Args,std::enable_if_t<std::is_constructible_v<T,K,Args ...>,bool> = true>
    const std::pair<K,T> MakeDictionaryPair(const K & key,const Args ... args)
    {       
        const T t(key,args ...);
        return (std::pair<K,T>(key,t));
    }

}