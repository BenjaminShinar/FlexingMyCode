#pragma once

#include <string>
#include <string_view>
#include <type_traits>
#include <initializer_list>
#include <algorithm>
#include <utility>
#include <vector>
namespace mockmon
{   
    //needed because we are skipping braced initilization.
    template <typename T>
    using vector_type_T=std::vector<T>;
    
    /**
     * @brief 
     * returns true/false if any element in the container matches the predicate
     * should eventually be replaced by simpler use?
     * @tparam T 
     * @tparam UnaryPredicate 
     * @param v a vector 
     * @param p a predicate on T
     * @return true 
     * @return false 
     */
    template<typename T,class UnaryPredicate>
    bool VectorContains(const std::vector<T> & v,const UnaryPredicate & p)
    {
    return std::any_of(std::begin(v),std::end(v),[&](const T & e){return p(e);});   
    }

    std::string AppendAll(const std::initializer_list<std::string_view> &words);

    template <typename T, std::enable_if_t<std::is_enum_v<T>, bool> = true>
    class IdentifiybleModule
    {
    public:
        explicit IdentifiybleModule(T &t) : m_identifier(t) {}
        explicit IdentifiybleModule(T &&t) : m_identifier(t) {}

        IdentifiybleModule(const IdentifiybleModule &other) : m_identifier(other.m_identifier) {}
        virtual ~IdentifiybleModule() = default;
        bool IsSameAs(T t) const {return m_identifier == t;}
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
    // no idea why it sometimes works ans sometimes doesnt, has maybe const, may double ref...
    // this requires a public ctor... maybe i can make this a friend class/function?
    template <typename T,typename K, typename ... Args,std::enable_if_t<std::is_constructible_v<T,K,Args ...>,bool> = true>
    std::pair<K,T> MakeDictionaryPair(const K & key,const Args ... args)
    {       
        const T t(key,args ...);
        return (std::pair<K,T>(key,t));
    }

}