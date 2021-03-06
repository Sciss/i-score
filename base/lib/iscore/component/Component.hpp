#pragma once
#include <iscore/tools/NotifyingMap.hpp>
#include <iscore/plugins/customfactory/UuidKey.hpp>
namespace iscore
{

#define COMPONENT_METADATA(TheType) \
    public: \
    static const Component::Key& static_key() { \
      static const Component::Key& s \
      { #TheType }; \
      return s; \
    } \
    \
    const Component::Key& key() const final override { \
      return static_key(); \
    } \
    private:


class ISCORE_LIB_BASE_EXPORT Component : public IdentifiedObject<Component>
{
    public:
        using IdentifiedObject<Component>::IdentifiedObject;
        using Key = UuidKey<Component>;
        virtual const Key& key() const = 0;

        virtual ~Component();
};

using Components = NotifyingMap<Component>;
}
