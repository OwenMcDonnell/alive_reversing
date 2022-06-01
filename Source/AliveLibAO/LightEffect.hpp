#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "DoorLight.hpp"

namespace AO {

class LightEffect final : public BaseAnimatedWithPhysicsGameObject
{
public:
    LightEffect(Path_LightEffect* pTlv, s32 tlvInfo);
    ~LightEffect();

    virtual void VRender(PrimHeader** ppOt) override;
    virtual void VScreenChanged() override;
    virtual void VUpdate() override;

    s32 field_D4;
    s32 field_D8;
    s32 field_DC;
    s32 field_E0;

    s32 field_E4_tlvInfo;
    s16 field_E8;
    s16 field_EA;
    s32 field_EC_rnd1;
    s32 field_F0_rnd2;
    s32 field_F4_rnd3;
    s32 field_F8_rnd4;
};
ALIVE_ASSERT_SIZEOF(LightEffect, 0xFC);

} // namespace AO
