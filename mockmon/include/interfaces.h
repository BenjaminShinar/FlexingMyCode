#pragma once
#include <string>
#include <type_traits>

template <typename T,std::enable_if_t<std::is_enum_v<T>,bool> = true>
class IdentifiybleModule
{
    public:
    explicit IdentifiybleModule(T& t): m_identifier(t){}
    explicit IdentifiybleModule(T&& t): m_identifier(t){}

    IdentifiybleModule(const IdentifiybleModule & other) : m_identifier(other.m_identifier){}
    virtual ~IdentifiybleModule() = default;
    const T Identifier() const {return m_identifier;}

    private:
    const T m_identifier;
};


template <typename T,std::enable_if_t<std::is_enum_v<T>,bool> = true>
class DescribleModule : public IdentifiybleModule<T>
{
    public:
    explicit DescribleModule(T& t):IdentifiybleModule<T>(t){}
    explicit DescribleModule(T&& t): IdentifiybleModule<T>(t){}

    DescribleModule(const DescribleModule & other): IdentifiybleModule<T>(other.Identifier()){}
    DescribleModule(const DescribleModule && other): IdentifiybleModule<T>(other.Identifier()){}
    
    virtual ~DescribleModule() = default;
    virtual std::string Describe() const = 0;
};