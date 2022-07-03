#include "stdafx_ao.h"
#include "Function.hpp"
#include "DoorLight.hpp"
#include "SwitchStates.hpp"
#include "ResourceManager.hpp"
#include "Math.hpp"
#include "Game.hpp"
#include "stdlib.hpp"
#include "MusicTrigger.hpp"
#include "Abe.hpp"
#include "Midi.hpp"
#include "ScreenManager.hpp"
#include "CameraSwapper.hpp"

namespace AO {

ALIVE_VAR(1, 0x4C30A8, s32, gNextDoorLightUpdate_4C30A8, -1);
ALIVE_VAR(1, 0x4FC8A4, s32, gDoorLightUpdateTimer_4FC8A4, 0);

DoorLight::DoorLight(Path_LightEffect* pTlv, s32 tlvInfo)
{
    field_E4_tlvInfo = tlvInfo;
    field_E8_width = pTlv->field_1A_size;
    field_EA_height = pTlv->field_1A_size;

    mBaseGameObjectTypeId = ReliveTypes::eNone;
    field_EC_bHasID = 0;
    field_F0_switch_id = pTlv->field_1C_switch_id;
    field_EE_switch_value = SwitchStates_Get(pTlv->field_1C_switch_id);

    s32 xOff = 0;
    switch (pTlv->field_18_type)
    {
        case Path_LightEffect::Type::GoldGlow_1:
        {
            const AnimRecord& goldRec = AO::AnimRec(AnimId::GoldGlow);
            Animation_Init(AnimId::GoldGlow, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, goldRec.mResourceId, 1, 0));
            break;
        }

        case Path_LightEffect::Type::GreenGlow_2:
        {
            const AnimRecord& greenRec = AO::AnimRec(AnimId::GreenGlow);
            Animation_Init(AnimId::GreenGlow, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, greenRec.mResourceId, 1, 0));
            break;
        }

        case Path_LightEffect::Type::FlintGlow_3:
        {
            const AnimRecord& flintRec = AO::AnimRec(AnimId::FlintGlow);
            Animation_Init(AnimId::FlintGlow, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, flintRec.mResourceId, 1, 0));
            field_EC_bHasID = 1;
            break;
        }

        case Path_LightEffect::Type::Switchable_RedGreenDoorLights_4:
        {
            field_E8_width = 0;
            field_EA_height = 0;
            if (SwitchStates_Get(pTlv->field_1C_switch_id))
            {
                const AnimRecord& greenRec = AO::AnimRec(AnimId::GreenDoorLight);
                Animation_Init(AnimId::GreenDoorLight, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, greenRec.mResourceId, 1, 0));
            }
            else
            {
                const AnimRecord& redRec = AO::AnimRec(AnimId::RedDoorLight);
                Animation_Init(AnimId::RedDoorLight, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, redRec.mResourceId, 1, 0));
                xOff = 6;
            }
            break;
        }

        case Path_LightEffect::Type::Switchable_RedGreenHubLight_5:
        {
            field_E8_width = 0;
            field_EA_height = 0;
            if (SwitchStates_Get(pTlv->field_1C_switch_id))
            {
                const AnimRecord& greenRec = AO::AnimRec(AnimId::GreenHubLight);
                Animation_Init(AnimId::GreenHubLight, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, greenRec.mResourceId, 1, 0));
            }
            else
            {
                const AnimRecord& redRec = AO::AnimRec(AnimId::RedHubLight);
                Animation_Init(AnimId::RedHubLight, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, redRec.mResourceId, 1, 0));
            }
            break;
        }

        default:
            break;
    }

    mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Set(AnimFlags::eBit5_FlipX, pTlv->field_1E_direction == XDirection_short::eLeft_0);

    if (gNextDoorLightUpdate_4C30A8 < 0)
    {
        gNextDoorLightUpdate_4C30A8 = sGnFrame;
        gDoorLightUpdateTimer_4FC8A4 = gNextDoorLightUpdate_4C30A8 + Math_RandomRange(30, 45);
    }

    mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Set(AnimFlags::eBit20_use_xy_offset);

    mVisualFlags.Clear(VisualFlags::eApplyShadowZoneColour);
    mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_Half_17;
    mBaseAnimatedWithPhysicsGameObject_Anim.mRenderMode = TPageAbr::eBlend_3;

    mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Clear(AnimFlags::eBit16_bBlending);
    mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Set(AnimFlags::eBit15_bSemiTrans);

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(pTlv->mTopLeft.x - xOff);
    }
    else
    {
        mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(xOff + pTlv->mTopLeft.x);
    }

    mBaseAnimatedWithPhysicsGameObject_SpriteScale = FP_FromInteger(1);
    mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(pTlv->mTopLeft.y);
}

DoorLight::~DoorLight()
{
    gMap.TLV_Reset(field_E4_tlvInfo, -1, 0, 0);
}

void DoorLight::VScreenChanged()
{
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    gNextDoorLightUpdate_4C30A8 = -1;
}

void DoorLight::VUpdate()
{
    if (static_cast<s32>(sGnFrame) > gDoorLightUpdateTimer_4FC8A4)
    {
        gNextDoorLightUpdate_4C30A8 = sGnFrame + Math_RandomRange(6, 20);
        gDoorLightUpdateTimer_4FC8A4 = gNextDoorLightUpdate_4C30A8 + Math_RandomRange(30, 45);
        mBaseAnimatedWithPhysicsGameObject_RGB.SetRGB(32, 32, 32);
    }
    else if (static_cast<s32>(sGnFrame) >= gNextDoorLightUpdate_4C30A8)
    {
        const FP lightAngle = (FP_FromInteger(128) * FP_FromInteger(sGnFrame - gNextDoorLightUpdate_4C30A8) / FP_FromInteger(gDoorLightUpdateTimer_4FC8A4 - gNextDoorLightUpdate_4C30A8));

        const FP lightAngleCosine = -Math_Cosine_4510A0(FP_GetExponent(lightAngle) & 0xFF);
        const s32 rgbVal = FP_GetExponent(FP_FromInteger(255) * lightAngleCosine) + 32;

        u8 rgb = 0;
        if (rgbVal <= 255)
        {
            rgb = rgbVal & 0xFF;
        }
        else
        {
            rgb = 255;
        }

        if (field_EC_bHasID)
        {
            if (SwitchStates_Get(field_F0_switch_id))
            {
                if (field_EE_switch_value == 0)
                {
                    field_EE_switch_value = 1;

                    if (sControlledCharacter_50767C == sActiveHero_507678)
                    {
                        relive_new MusicTrigger(MusicTriggerMusicType::eSecretAreaShort_6, TriggeredBy::eTouching_1, 0, 15);
                    }
                    else
                    {
                        SND_SEQ_Play_477760(SeqId::eSaveTriggerMusic_45, 1, 127, 127);
                    }
                }
                mBaseAnimatedWithPhysicsGameObject_RGB.SetRGB(32, rgb, 32);
            }
            else
            {
                mBaseAnimatedWithPhysicsGameObject_RGB.SetRGB(rgb, 32, 32);
            }
        }
        else
        {
            mBaseAnimatedWithPhysicsGameObject_RGB.SetRGB(rgb, rgb, rgb);
        }
    }
}

void DoorLight::VRender(PrimHeader** ppOt)
{
    if (sNumCamSwappers_507668 == 0)
    {
        const FP xpos = FP_FromInteger(pScreenManager->mCamXOff) + mBaseAnimatedWithPhysicsGameObject_XPos - pScreenManager->mCamPos->x;
        const FP ypos = FP_FromInteger(pScreenManager->mCamYOff) + mBaseAnimatedWithPhysicsGameObject_YPos - pScreenManager->mCamPos->y;

        mBaseAnimatedWithPhysicsGameObject_Anim.mRed = static_cast<u8>(mBaseAnimatedWithPhysicsGameObject_RGB.r);
        mBaseAnimatedWithPhysicsGameObject_Anim.mGreen = static_cast<u8>(mBaseAnimatedWithPhysicsGameObject_RGB.g);
        mBaseAnimatedWithPhysicsGameObject_Anim.mBlue = static_cast<u8>(mBaseAnimatedWithPhysicsGameObject_RGB.b);

        mBaseAnimatedWithPhysicsGameObject_Anim.VRender(
            FP_GetExponent(FP_FromInteger((FP_GetExponent(xpos) - field_E8_width / 2))),
            FP_GetExponent(FP_FromInteger((FP_GetExponent(ypos) - field_EA_height / 2))),
            ppOt,
            field_E8_width,
            field_EA_height);

        PSX_RECT rect = {};
        mBaseAnimatedWithPhysicsGameObject_Anim.Get_Frame_Rect(&rect);
        pScreenManager->InvalidateRectCurrentIdx(
            rect.x,
            rect.y,
            rect.w,
            rect.h);
    }
}

} // namespace AO
