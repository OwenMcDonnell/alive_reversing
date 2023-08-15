#pragma once

#include "data_conversion/guid.hpp"

class BaseGameObject;
class StringHash;

using TObjectId_KeyType = Guid;


class BaseGameObject;

class ObjectIds final
{
public:
    ~ObjectIds();
    ObjectIds();
    void Insert(TObjectId_KeyType objCount, BaseGameObject* pGameObj);
    s16 Remove(TObjectId_KeyType idToRemove);

    // Use the "checked" Find() so the types are verified where possible (i.e its to a specific single derived type
    BaseGameObject* Find_Impl(TObjectId_KeyType idToFind);

public:
    BaseGameObject* Find(TObjectId_KeyType idToFind, const StringHash& reliveType);

private:
    std::map<TObjectId_KeyType, BaseGameObject*> mMap;
};

extern ObjectIds sObjectIds;
