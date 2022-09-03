#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/BaseGameObject.hpp"
#include "Psx.hpp"

namespace AO {

class BaseAliveGameObject;
class PalleteOverwriter;

class Electrocute final : public ::BaseGameObject
{
public:
    Electrocute(BaseAliveGameObject* pTargetObj, s32 bExtraOverwriter);
    ~Electrocute();

    virtual void VScreenChanged() override;
    virtual void VUpdate() override;

    void Stop();

    BaseAliveGameObject* field_10_obj_target = nullptr;
    s16 field_14_overwriter_count = 0;
    PalleteOverwriter* field_18_pPalOverwriters[3] = {};
    s16 field_24_extraOverwriter = 0;
    u16* field_28_pPalData = nullptr;
    s16 field_2C_r = 0;
    s16 field_2E_g = 0;
    s16 field_30_b = 0;
    enum class States : s16
    {
        eSetNewColour_0 = 0,
        eAlphaFadeout_1 = 1,
        eHandleDamage_2 = 2,
        eKillElectrocute_3 = 3
    };
    States field_32_state = States::eSetNewColour_0;
    PSX_RECT field_38_pal_rect = {};
};
ALIVE_ASSERT_SIZEOF(Electrocute, 0x40);

} // namespace AO
