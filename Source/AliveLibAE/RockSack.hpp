#pragma once

#include "BaseAliveGameObject.hpp"
#include "Path.hpp"

struct Path_RockSack final : public Path_TLV
{
    XDirection_short mRockFallDirection;
    u16 mVelX;
    u16 mVelY;
    Scale_short mScale;
    s16 mRockAmount;
    s16 field_1A_padding;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_RockSack, 0x1C);

class RockSack final : public BaseAliveGameObject
{
public:
    RockSack(Path_RockSack* pTlv, s32 tlvInfo);
    ~RockSack();
    
    virtual void VScreenChanged() override;
    virtual void VUpdate() override;

private:
    s32 field_118_tlvInfo = 0;
    s16 field_11C_has_been_hit = 0;
    s16 field_11E_rock_amount = 0;
    s16 field_120_can_play_wobble_sound = 0;
    s16 field_122_force_wobble_sound = 0; // Makes sure RockSacks play the sound when you first encounter them. Unused afterwards. -- Nemin (6/7/2020)
    FP field_124_x_vel = {};
    FP field_128_y_vel = {};
};
ALIVE_ASSERT_SIZEOF(RockSack, 0x12C);
