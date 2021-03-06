#include <Device/Node/DeviceNode.hpp>
#include <iscore/serialization/DataStreamVisitor.hpp>
#include <iscore/serialization/JSONVisitor.hpp>
#include <iscore/tools/VariantSerialization.hpp>

namespace Device {
struct AddressSettings;
struct DeviceSettings;
}  // namespace iscore

template<>
void Visitor<Reader<DataStream>>::readFrom(const Device::DeviceExplorerNode& n)
{
    readFrom(n.m_data);
    insertDelimiter();
}

template<>
void Visitor<Writer<DataStream>>::writeTo(Device::DeviceExplorerNode& n)
{
    writeTo(n.m_data);
    checkDelimiter();
}

template<>
void Visitor<Reader<JSONObject>>::readFrom(const Device::DeviceExplorerNode& n)
{
    readFrom(n.m_data);
}

template<>
void Visitor<Writer<JSONObject>>::writeTo(Device::DeviceExplorerNode& n)
{
    writeTo(n.m_data);
}
