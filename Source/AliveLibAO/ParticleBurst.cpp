#include "stdafx_ao.h"
#include "../relive_lib/Function.hpp"
#include "ParticleBurst.hpp"
#include "Math.hpp"
#include "../AliveLibAE/stdlib.hpp"
#include "Map.hpp"
#include "Game.hpp"
#include "../relive_lib/GameObjects/ScreenManager.hpp"
#include "../relive_lib/PsxDisplay.hpp"
#include "../AliveLibAE/Game.hpp"
#include "../relive_lib/Events.hpp"
#include "Sfx.hpp"
#include "BaseAliveGameObject.hpp"
#include "Grid.hpp"
#include "../relive_lib/AnimationUnknown.hpp"

namespace AO {

struct ParticleBurst_Item final
{
    FP x;
    FP y;
    FP field_8_z;
    FP field_C_x_speed;
    FP field_10_y_speed;
    FP field_14_z_speed;
    AnimationUnknown field_18_animation;
};

static inline FP Random_Speed(FP scale)
{
    return FP_FromRaw((static_cast<u32>(Math_NextRandom()) - 128) << 13) * scale;
}

ParticleBurst::ParticleBurst(FP xpos, FP ypos, s32 particleCount, FP scale, BurstType type)
    : BaseAnimatedWithPhysicsGameObject(0)
{
    SetType(ReliveTypes::eParticleBurst);
    SetSpriteScale(scale);

    mParticleItems = relive_new ParticleBurst_Item[particleCount];
    if (mParticleItems)
    {
        mType = type;
        switch (type)
        {
            case BurstType::eFallingRocks_0:
            {
                mLoadedAnims.push_back(ResourceManagerWrapper::LoadAnimation(AnimId::Rock_Gib));
                Animation_Init(GetAnimRes(AnimId::Rock_Gib));
                GetAnimation().SetSemiTrans(false);
                GetAnimation().SetBlending(true);
                break;
            }

            case BurstType::eSticks_1:
            {
                mLoadedAnims.push_back(ResourceManagerWrapper::LoadAnimation(AnimId::Stick_Gib));
                Animation_Init(GetAnimRes(AnimId::Stick_Gib));
                scale = FP_FromDouble(0.4) * scale;
                GetAnimation().SetSemiTrans(false);
                GetAnimation().SetBlending(true);
                break;
            }

            case BurstType::eBigPurpleSparks_2:
            {
                mLoadedAnims.push_back(ResourceManagerWrapper::LoadAnimation(AnimId::DeathFlare_2));
                Animation_Init(GetAnimRes(AnimId::DeathFlare_2));
                GetAnimation().SetSemiTrans(true);
                GetAnimation().SetBlending(true);
                GetAnimation().SetBlendMode(relive::TBlendModes::eBlend_1);
                break;
            }

            case BurstType::eBigRedSparks_3:
            {
                mLoadedAnims.push_back(ResourceManagerWrapper::LoadAnimation(AnimId::DeathFlare_2));
                Animation_Init(GetAnimRes(AnimId::DeathFlare_2));

                GetAnimation().SetBlendMode(relive::TBlendModes::eBlend_1);
                GetAnimation().SetSemiTrans(true);
                GetAnimation().SetBlending(false);

                GetAnimation().SetRGB(254, 148, 18);
                break;
            }

            case BurstType::eMeat_4:
            {
                mLoadedAnims.push_back(ResourceManagerWrapper::LoadAnimation(AnimId::Meat_Gib));
                Animation_Init(GetAnimRes(AnimId::Meat_Gib));
                GetAnimation().SetSemiTrans(false);
                GetAnimation().SetBlending(true);
                break;
            }

            default:
                break;
        }

        if (GetListAddFailed())
        {
            SetDead(true);
        }
        else
        {
            if (GetSpriteScale() == FP_FromInteger(1))
            {
                SetScale(Scale::Fg);
                GetAnimation().SetRenderLayer(Layer::eLayer_Above_FG1_39);
            }
            else
            {
                SetScale(Scale::Bg);
                GetAnimation().SetRenderLayer(Layer::eLayer_Above_FG1_Half_20);
            }

            mParticleCount = static_cast<s16>(particleCount);
            mAliveTimer = MakeTimer(91);
            mXPos = xpos;
            mYPos = ypos;

            for (s32 i = 0; i < particleCount; i++)
            {
                mParticleItems[i].field_18_animation.mAnimPtr = &GetAnimation();
                mParticleItems[i].field_18_animation.SetRenderLayer(GetAnimation().GetRenderLayer());
                mParticleItems[i].field_18_animation.mSpriteScale = FP_FromDouble(0.95) * GetSpriteScale();

                mParticleItems[i].field_18_animation.SetRender(true);

                mParticleItems[i].field_18_animation.SetSemiTrans(GetAnimation().GetSemiTrans());

                mParticleItems[i].field_18_animation.SetBlending(GetAnimation().GetBlending());

                if (type == BurstType::eBigPurpleSparks_2)
                {
                    if (i % 2)
                    {
                        mParticleItems[i].field_18_animation.SetBlending(true);
                    }
                }

                const auto rgb = GetAnimation().GetRgb();
                mParticleItems[i].field_18_animation.SetRGB(rgb.r, rgb.g, rgb.b);

                mParticleItems[i].x = xpos;
                mParticleItems[i].y = ypos;
                mParticleItems[i].field_8_z = FP_FromInteger(0);

                mParticleItems[i].field_C_x_speed = Random_Speed(scale);
                mParticleItems[i].field_10_y_speed = -Random_Speed(scale);
                mParticleItems[i].field_14_z_speed = -FP_Abs(Random_Speed(scale));
            }

            if (gMap.mCurrentLevel == EReliveLevelIds::eStockYards || gMap.mCurrentLevel == EReliveLevelIds::eStockYardsReturn)
            {
                mRGB.SetRGB(60, 60, 60);
            }
        }
    }
    else
    {
        SetDead(true);
    }
}

ParticleBurst::~ParticleBurst()
{
    relive_delete[] mParticleItems;
}

void ParticleBurst::VUpdate()
{
    for (s32 i = 0; i < mParticleCount; i++)
    {
        ParticleBurst_Item* pItem = &mParticleItems[i];

        pItem->x += pItem->field_C_x_speed;
        pItem->y += pItem->field_10_y_speed;
        pItem->field_8_z += pItem->field_14_z_speed;

        pItem->field_10_y_speed += FP_FromDouble(0.25);

        u16 result = 0;
        pItem->x = CamX_VoidSkipper(pItem->x, pItem->field_C_x_speed, 16, &result);
        pItem->y = CamY_VoidSkipper(pItem->y, pItem->field_10_y_speed, 16, &result);

        if (pItem->field_8_z + FP_FromInteger(300) < FP_FromInteger(15))
        {
            pItem->field_14_z_speed = -pItem->field_14_z_speed;
            pItem->field_8_z += pItem->field_14_z_speed;

            if (mType == BurstType::eMeat_4)
            {
                if (gMap.Is_Point_In_Current_Camera(
                        gMap.mCurrentLevel,
                        gMap.mCurrentPath,
                        pItem->x,
                        pItem->y,
                        0))
                {
                    SFX_Play_Pitch(relive::SoundEffects::KillEffect, 50, Math_RandomRange(-900, -300));
                }
            }
            else
            {
                // TODO: Never used by OG ??
                // Math_RandomRange(-64, 46);

                const s16 volume = static_cast<s16>(Math_RandomRange(-10, 10) + ((mAliveTimer - sGnFrame) / 91) + 25);

                const u8 next_rand = Math_NextRandom();
                if (next_rand < 43)
                {
                    SFX_Play_Camera(relive::SoundEffects::ParticleBurst, volume, CameraPos::eCamLeft_3);
                }
                else if (next_rand >= 85)
                {
                    SFX_Play_Camera(relive::SoundEffects::ParticleBurst, volume, CameraPos::eCamRight_4);
                }
                else
                {
                    SFX_Play_Camera(relive::SoundEffects::ParticleBurst, volume, CameraPos::eCamCurrent_0);
                }
            }
        }
    }

    if (sGnFrame > mAliveTimer)
    {
        SetDead(true);
    }

    if (EventGet(kEventDeathReset))
    {
        SetDead(true);
    }
}

void ParticleBurst::VRender(OrderingTable& ot)
{
    if (gNumCamSwappers != 0)
    {
        return;
    }

    GetAnimation().SetSpriteScale(GetSpriteScale());

    const FP_Point* pCamPos = gScreenManager->mCamPos;
    const FP screen_left = pCamPos->x - FP_FromInteger(gScreenManager->mCamXOff);
    const FP screen_right = pCamPos->x + FP_FromInteger(gScreenManager->mCamXOff);

    const FP screen_top = pCamPos->y + FP_FromInteger(gScreenManager->mCamYOff);
    const FP screen_bottom = pCamPos->y - FP_FromInteger(gScreenManager->mCamYOff);

    bool bFirst = true;
    for (s32 i = 0; i < mParticleCount; i++)
    {
        ParticleBurst_Item* pItem = &mParticleItems[i];
        if (pItem->x >= screen_left && pItem->x <= screen_right)
        {
            if (pItem->y >= screen_bottom && pItem->y <= screen_top)
            {
                if (bFirst)
                {
                    GetAnimation().SetSpriteScale(FP_FromInteger(100) / (pItem->field_8_z + FP_FromInteger(300)));
                    GetAnimation().VRender(
                        FP_GetExponent(PsxToPCX(pItem->x - screen_left, FP_FromInteger(11))),
                        FP_GetExponent(pItem->y - screen_bottom),
                        ot, 0, 0);
                    bFirst = false;
                }
                else
                {
                    pItem->field_18_animation.mSpriteScale = FP_FromInteger(100) / (pItem->field_8_z + FP_FromInteger(300));
                    pItem->field_18_animation.VRender(
                        FP_GetExponent(PsxToPCX(pItem->x - screen_left, FP_FromInteger(11))),
                        FP_GetExponent(pItem->y - screen_bottom),
                        ot, 0, 0);
                }
            }
        }
    }
}

} // namespace AO
