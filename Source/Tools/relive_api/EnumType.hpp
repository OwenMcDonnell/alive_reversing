#pragma once

#include "ITypeBase.hpp"
#include "relive_api.hpp"

#include <jsonxx/jsonxx.h>

#include <map>
#include <string>
#include <typeinfo>

template<class T>
class EnumType : public ITypeBase
{
public:
    explicit EnumType(const std::string& typeName)
        : ITypeBase(typeName), mTypeIndex(typeid(T))
    {
    }

    void Add(T enumValue, const std::string& name)
    {
        mMapping[enumValue] = name;
    }

    [[nodiscard]] const std::type_index& TypeIndex() const override
    {
        return mTypeIndex;
    }

    [[nodiscard]] T ValueFromString(const std::string& valueString) const
    {
        for (const auto [key, value] : mMapping)
        {
            if (value == valueString)
            {
                return key;
            }
        }

        throw ReliveAPI::UnknownEnumValueException(valueString);
    }

    [[nodiscard]] const std::string& ValueToString(T valueToFind) const
    {
        for (const auto [key, value] : mMapping)
        {
            if (key == valueToFind)
            {
                return value;
            }
        }

        throw ReliveAPI::UnknownEnumValueException();
    }

    [[nodiscard]] bool IsBasicType() const override
    {
        return false;
    }

    void ToJson(jsonxx::Array& obj) const override
    {
        jsonxx::Array enumVals;
        for (const auto& [key, value] : mMapping)
        {
            enumVals << value;
        }

        jsonxx::Object enumObj;
        enumObj << "name" << Name();
        enumObj << "values" << enumVals;

        obj << enumObj;
    }

private:
    std::map<T, std::string> mMapping;
    std::type_index mTypeIndex;
};
