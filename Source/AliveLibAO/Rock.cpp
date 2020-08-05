#include "stdafx_ao.h"
#include "Function.hpp"
#include "Rock.hpp"
#include "stdlib.hpp"
#include "ResourceManager.hpp"
#include "Shadow.hpp"
#include "Grenade.hpp"
#include "ThrowableArray.hpp"
#include "Math.hpp"
#include "Events.hpp"
#include "Sfx.hpp"
#include "Abe.hpp"

START_NS_AO

void RockSack::VUpdate()
{
    VUpdate_4575F0();
}

void RockSack::VUpdate_4575F0()
{
    if (Event_Get_417250(kEventDeathReset_4))
    {
        field_6_flags.Set(BaseGameObject::eDead_Bit3);
    }

    if (field_10_anim.field_92_current_frame == 2)
    {
        if (field_114_can_play_wobble_sound)
        {
            if (Math_NextRandom() < 40u || field_116_force_wobble_sound)
            {
                field_114_can_play_wobble_sound = 0;
                field_116_force_wobble_sound = 0;
                SFX_Play_43AE60(34u, 24, Math_RandomRange_450F20(-2400, -2200), 0);
            }
        }
    }
    else
    {
        field_114_can_play_wobble_sound = 1;
    }

    if (field_110)
    {
        if (field_110 == 1)
        {
            if (field_10_anim.field_4_flags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                field_10_anim.Set_Animation_Data_402A40(13756, 0);
                field_110 = 0;
            }
        }
    }
    else
    {
        if (field_10_anim.field_E_frame_change_counter == 0)
        {
            field_10_anim.field_E_frame_change_counter = Math_RandomRange_450F20(2, 10);
        }

        PSX_RECT bPlayerRect = {};
        sActiveHero_507678->VGetBoundingRect(&bPlayerRect, 1);

        PSX_RECT bRect = {};
        VGetBoundingRect(&bRect, 1);

        if (bRect.x <= bPlayerRect.w
            && bRect.w >= bPlayerRect.x
            && bRect.h >= bPlayerRect.y
            && bRect.y <= bPlayerRect.h
            && field_BC_sprite_scale == sActiveHero_507678->field_BC_sprite_scale)
        {
            if (!gpThrowableArray_50E26C || !gpThrowableArray_50E26C->field_10_count)
            {
                if (!gpThrowableArray_50E26C)
                {
                    gpThrowableArray_50E26C = ao_new<ThrowableArray>();
                    if (gpThrowableArray_50E26C)
                    {
                        gpThrowableArray_50E26C->ctor_453EE0();
                    }
                }

                gpThrowableArray_50E26C->Add_453F70(field_112_num_rocks);

                auto pRock = ao_new<Rock>();
                if (pRock)
                {
                    pRock->ctor_456960(
                        field_A8_xpos,
                        field_AC_ypos - FP_FromInteger(30),
                        field_112_num_rocks);
                }
                pRock->VThrow(field_118_x_vel, field_11C_y_vel);

                SFX_Play_43AD70(30u, 0, 0);
                Abe_SFX_2_42A220(7u, 0, 0x7FFF, 0);
            }

            if (sActiveHero_507678->field_FC_current_motion == eAbeStates::State_33_RunJumpMid_426FA0)
            {
                field_10_anim.Set_Animation_Data_402A40(13708, 0);
            }
            else
            {
                field_10_anim.Set_Animation_Data_402A40(13780, 0);
            }

            field_110 = 1;
        }
    }
}

void RockSack::VScreenChanged()
{
    VScreenChanged_457890();
}

RockSack* RockSack::Vdtor_4578A0(signed int flags)
{
    dtor_457580();
    if (flags & 1)
    {
        ao_delete_free_447540(this);
    }
    return this;
}

BaseGameObject* RockSack::VDestructor(signed int flags)
{
    return Vdtor_4578A0(flags);
}

BaseGameObject* RockSack::dtor_457580()
{
    SetVTable(this, 0x4BC120);
    gMap_507BA8.TLV_Reset_446870(field_10C_tlvInfo, -1, 0, 0);
    return dtor_401000();
}

RockSack* RockSack::ctor_4573F0(Path_RockSack* pTlv, int tlvInfo)
{
    ctor_401090();
    SetVTable(this, 0x4BC120);

    field_4_typeId = Types::eRockSack_71;

    BYTE** ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, 1002, 1, 0);

    //  Set RockSack idle anim speed
    auto pAnimationHeader = reinterpret_cast<AnimationHeader*>(*ppRes + 6878);
    pAnimationHeader->field_0_fps = 0;

    Animation_Init_417FD0(13756, 71, 60, ppRes, 1);

    field_10_anim.field_4_flags.Clear(AnimFlags::eBit15_bSemiTrans);

    field_10C_tlvInfo = tlvInfo;
    field_110 = 0;
    field_CC_bApplyShadows &= ~1u;
    field_A8_xpos = FP_FromInteger(pTlv->field_C_sound_pos.field_0_x);
    field_AC_ypos = FP_FromInteger(pTlv->field_C_sound_pos.field_2_y);
    field_118_x_vel = FP_FromRaw(pTlv->field_1A_x_vel << 8);
    field_11C_y_vel = FP_FromRaw(-256 * pTlv->field_1C_y_vel);

    if (!pTlv->field_18_side)
    {
        field_118_x_vel = -field_118_x_vel;
    }

    if (pTlv->field_1E_scale == 1)
    {
        field_BC_sprite_scale = FP_FromDouble(0.5);
        field_C6_scale = 0;
    }
    else
    {
        field_BC_sprite_scale = FP_FromInteger(1);
        field_C6_scale = 1;
    }

    field_112_num_rocks = pTlv->field_20_num_rocks;
    field_114_can_play_wobble_sound = 1;
    field_116_force_wobble_sound = 1;

    if (gMap_507BA8.field_0_current_level == LevelIds::eStockYards_5 || gMap_507BA8.field_0_current_level == LevelIds::eStockYardsReturn_6)
    {
        BYTE** ppPal = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Palt, 1002, 0, 0);
        field_10_anim.LoadPal_403090(ppPal, 0);
    }

    field_D0_pShadow = ao_new<Shadow>();
    if (field_D0_pShadow)
    {
        field_D0_pShadow->ctor_461FB0();
    }

    return this;
}

void RockSack::VScreenChanged_457890()
{
    field_6_flags.Set(BaseGameObject::eDead_Bit3);
}


Rock* Rock::ctor_456960(FP xpos, FP ypos, __int16 count)
{
    ctor_401090();
    SetVTable(this, 0x4BC0A8);
    field_4_typeId = Types::eRock_70;

    field_10E_bDead = 0;

    BYTE** ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, 350, 1, 0);
    Animation_Init_417FD0(
        500,
        18,
        9,
        ppRes,
        1);

    field_6_flags.Clear(Options::eInteractive_Bit8);
    field_10_anim.field_4_flags.Clear(AnimFlags::eBit3_Render);
    field_10_anim.field_4_flags.Clear(AnimFlags::eBit15_bSemiTrans);

    field_A8_xpos = xpos;
    field_11C_xpos = xpos;
    field_AC_ypos = ypos;
    field_120_ypos = ypos;
    field_B4_velx = FP_FromInteger(0);
    field_B8_vely = FP_FromInteger(0);
    field_10C_count = count;
    field_110_state = 0;

    BYTE** ppPal = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Palt, 350, 0, 0);
    if (ppPal)
    {
        field_10_anim.LoadPal_403090(ppPal, 0);
    }
    else
    {
        const FrameInfoHeader* pFrameInfo = field_10_anim.Get_FrameHeader_403A00(-1);

        const FrameHeader* pFrameHeader = reinterpret_cast<const FrameHeader*>(&(*field_10_anim.field_20_ppBlock)[pFrameInfo->field_0_frame_header_offset]);

        field_10_anim.LoadPal_403090(
            field_10_anim.field_20_ppBlock,
            pFrameHeader->field_0_clut_offset);
    }

    field_118 = 0;

    field_D0_pShadow = ao_new<Shadow>();
    if (field_D0_pShadow)
    {
        field_D0_pShadow->ctor_461FB0();
    }
    return this;
}

BaseGameObject* Rock::dtor_456A90()
{
    SetVTable(this, 0x4BC0A8);
    if (!gInfiniteGrenades_5076EC && !field_10E_bDead)
    {
        if (gpThrowableArray_50E26C)
        {
            gpThrowableArray_50E26C->Remove_4540D0(field_10C_count >= 1u ? field_10C_count : 1);
        }
    }
    return dtor_401000();
}

BaseGameObject* Rock::VDestructor(signed int flags)
{
    return Vdtor_4573D0(flags);
}

Rock* Rock::Vdtor_4573D0(signed int flags)
{
    dtor_456A90();
    if (flags & 1)
    {
        ao_delete_free_447540(this);
    }
    return this;
}

void Rock::VScreenChanged()
{
    VScreenChanged_457310();
}


void Rock::VScreenChanged_457310()
{
    if (gMap_507BA8.field_2_current_path != gMap_507BA8.field_C_path
        || gMap_507BA8.field_0_current_level != gMap_507BA8.field_A_level)
    {
        field_6_flags.Set(BaseGameObject::eDead_Bit3);
    }
}

void Rock::VThrow(FP velX, FP velY)
{
    VThrow_456B20(velX, velY);
}

void Rock::VThrow_456B20(FP velX, FP velY)
{
    field_B4_velx = velX;
    field_B8_vely = velY;

    field_10_anim.field_4_flags.Set(AnimFlags::eBit3_Render);

    if (field_10C_count == 0)
    {
        field_110_state = 4;
    }
    else
    {
        field_110_state = 1;
    }
}

__int16 Rock::VCanThrow()
{
    return VCanThrow_4573C0();
}

__int16 Rock::VCanThrow_4573C0()
{
    return field_110_state == 4;
}

END_NS_AO
