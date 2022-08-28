#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "BaseAliveGameObject.hpp"
#include "Path.hpp"

struct Path_DoorBlocker final : public Path_TLV
{
    Scale_short mScale;
    s16 mSwitchId;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_DoorBlocker, 0x14);

class DoorBlocker final : public BaseAliveGameObject
{
public:
    DoorBlocker(relive::Path_DoorBlocker* pTlv, const TLVUniqueId& tlvId);
    ~DoorBlocker();

    virtual void VUpdate() override;

private:
    s16 field_118_bDone = 0;
    s16 field_11A_switch_id = 0;
    TLVUniqueId field_11C_tlvInfo;
};
ALIVE_ASSERT_SIZEOF(DoorBlocker, 0x124);
