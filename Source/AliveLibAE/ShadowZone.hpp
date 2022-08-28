#pragma once

#include "../relive_lib/BaseGameObject.hpp"
#include "Path.hpp"
#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/MapWrapper.hpp"
#include "../relive_lib/BaseAnimatedWithPhysicsGameObject.hpp"

enum class ShadowZoneScale : s16
{
    eBoth_0 = 0,
    eHalf_1 = 1,
    eFull_2 = 2,
};

struct Path_ShadowZone final : public Path_TLV
{
    s16 field_10_center_w;
    s16 field_12_center_h;
    u16 mRed;
    u16 mGreen;
    u16 mBlue;
    s16 field_1A_switch_id;
    ShadowZoneScale mScale;
    s16 field_1E_pad;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_ShadowZone, 0x20);

enum class LevelIds : s16;

class ShadowZone final : public BaseGameObject
{
public:
    ShadowZone(relive::Path_ShadowZone* pTlv, Path* pPath, const TLVUniqueId& tlvId);
    ~ShadowZone();

    virtual void VUpdate() override;
    virtual void VScreenChanged() override;

    static void ShadowZones_Calculate_Colour(s32 xpos, s32 ypos, Scale scale, s16* r, s16* g, s16* b);

private:
    s16 ApplysToScale(Scale scale);
    FP* GetColourAmount(FP* pOut, s16 xpos, s16 ypos);

private:
    s32 field_20_tlvInfo = 0;

    EReliveLevelIds field_24_level = EReliveLevelIds::eNone;
    s16 field_26_path = 0;

    s16 field_28_centre_x = 0;
    s16 field_2A_center_y = 0;

    s16 field_2C_centre_mid_x = 0;
    s16 field_2E_centre_mid_y = 0;

    s16 field_30_mid_x = 0;
    s16 field_32_mid_y = 0;

    relive::Path_ShadowZone::Scale field_36_scale = relive::Path_ShadowZone::Scale::eBoth;

    FP field_38_r = {};
    FP field_3C_g = {};
    FP field_40_b = {};
};
ALIVE_ASSERT_SIZEOF(ShadowZone, 0x44);
