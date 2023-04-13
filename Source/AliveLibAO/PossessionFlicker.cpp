#include "stdafx_ao.h"
#include "Function.hpp"
#include "PossessionFlicker.hpp"
#include "stdlib.hpp"
#include "Game.hpp"
#include "BaseAliveGameObject.hpp"
#include "ObjectIds.hpp"

namespace AO {

void PossessionFlicker::VUpdate()
{
    VUpdate_41A9B0();
}

void PossessionFlicker::VScreenChanged_41AA40()
{
    auto pObj = static_cast<BaseAliveGameObject*>(sObjectIds_5C1B70.Find_449CF0(field_10_pObj));
    if (!pObj)
    {
        field_10_pObj = -1;
        field_6_flags.Set(Options::eDead_Bit3);
    }
}

void PossessionFlicker::VScreenChanged()
{
    VScreenChanged_41AA40();
}

PossessionFlicker* PossessionFlicker::vdtor_41AA70(s32 flags)
{
    dtor_41A940();
    if (flags & 1)
    {
        ao_delete_free_447540(this);
    }
    return this;
}

BaseGameObject* PossessionFlicker::VDestructor(s32 flags)
{
    return vdtor_41AA70(flags);
}

BaseGameObject* PossessionFlicker::dtor_41A940()
{
    SetVTable(this, 0x4BAC58);

    auto pObj = static_cast<BaseAliveGameObject*>(sObjectIds_5C1B70.Find_449CF0(field_10_pObj));
    if (pObj)
    {
        pObj->field_10_anim.field_B_render_mode = TPageAbr::eBlend_0;

        pObj->field_C0_r = field_1E_old_r;
        pObj->field_C2_g = field_20_old_g;
        pObj->field_C4_b = field_22_old_b;
    }
    return dtor_487DF0();
}

PossessionFlicker* PossessionFlicker::ctor_41A8C0(BaseAliveGameObject* pToApplyFlicker, s32 duration, s16 r, s16 g, s16 b)
{
    ctor_487E10(1);
    SetVTable(this, 0x4BAC58);

    field_10_pObj = pToApplyFlicker->field_8_object_id;

    field_18_r = r;
    field_1A_g = g;
    field_1C_b = b;

    field_1E_old_r = pToApplyFlicker->field_C0_r;
    field_20_old_g = pToApplyFlicker->field_C2_g;
    field_22_old_b = pToApplyFlicker->field_C4_b;

    pToApplyFlicker->field_10_anim.field_B_render_mode = TPageAbr::eBlend_1;

    field_14_time_to_flicker = gnFrameCount_507670 + duration;

    return this;
}


void PossessionFlicker::VUpdate_41A9B0()
{
    bool bFlicker = false;
    auto pObj = static_cast<BaseAliveGameObject*>(sObjectIds_5C1B70.Find_449CF0(field_10_pObj));
    if (!pObj)
    {
        field_10_pObj = -1;
        field_6_flags.Set(BaseGameObject::eDead_Bit3);
        bFlicker = false;
    }
    else
    {
        bFlicker = true;
    }

    if (bFlicker)
    {
        if (gnFrameCount_507670 % 2)
        {
            pObj->field_C0_r = field_1E_old_r;
            pObj->field_C2_g = field_20_old_g;
            pObj->field_C4_b = field_22_old_b;
        }
        else
        {
            pObj->field_C0_r = field_18_r;
            pObj->field_C2_g = field_1A_g;
            pObj->field_C4_b = field_1C_b;
        }

        if (static_cast<s32>(gnFrameCount_507670) > field_14_time_to_flicker)
        {
            field_6_flags.Set(BaseGameObject::eDead_Bit3);
        }
    }
}

} // namespace AO
