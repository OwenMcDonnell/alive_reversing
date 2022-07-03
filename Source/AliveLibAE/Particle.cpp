#include "stdafx.h"
#include "Particle.hpp"
#include "Function.hpp"
#include "ResourceManager.hpp"
#include "stdlib.hpp"
#include "BaseAliveGameObject.hpp"

Particle::Particle(FP xpos, FP ypos, AnimId animId, u8** ppAnimData, bool explosionSizeHack)
    : BaseAnimatedWithPhysicsGameObject(0)
{
    SetType(ReliveTypes::eParticle);

    ResourceManager::Inc_Ref_Count_49C310(ppAnimData);

    field_10_resources_array.Push_Back(ppAnimData);

    mBaseAnimatedWithPhysicsGameObject_RGB.SetRGB(128, 128, 128);

    if (!explosionSizeHack)
    {
        Animation_Init(animId, ppAnimData);
    }
    else
    {
        // AnimId::Explosion_Small and AnimId::Explosion have different width/height but for some reason
        // OG inits both with the AnimId::Explosion width and height in Explosion.cpp
        const AnimRecord& rec = AnimRec(animId);
        Animation_Init(rec.mFrameTableOffset, 202, 91, ppAnimData);
    }

    if (mBaseGameObjectFlags.Get(Options::eListAddFailed_Bit1))
    {
        mBaseGameObjectFlags.Set(Options::eDead);
    }

    mBaseAnimatedWithPhysicsGameObject_YPos = ypos;
    mBaseAnimatedWithPhysicsGameObject_XPos = xpos;
    field_F4_scale_amount = FP_FromInteger(0);
}

void Particle::VUpdate()
{
    mBaseAnimatedWithPhysicsGameObject_XPos += mBaseAnimatedWithPhysicsGameObject_VelX;
    mBaseAnimatedWithPhysicsGameObject_YPos += mBaseAnimatedWithPhysicsGameObject_VelY;
    mBaseAnimatedWithPhysicsGameObject_SpriteScale += field_F4_scale_amount;

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mBaseGameObjectFlags.Set(Options::eDead);
    }
}

Particle* New_DestroyOrCreateObject_Particle(FP xpos, FP ypos, FP scale)
{
    const AnimRecord& rec = AnimRec(AnimId::DeathFlare_2);
    u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, rec.mResourceId, FALSE, FALSE);
    auto pParticle = relive_new Particle(xpos, ypos, AnimId::DeathFlare_2, ppRes);

    if (!pParticle)
    {
        return nullptr;
    }

    pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderMode = TPageAbr::eBlend_1;
    pParticle->mBaseAnimatedWithPhysicsGameObject_SpriteScale = FP_FromRaw(scale.fpValue * 2);

    if (scale == FP_FromInteger(1))
    {
        pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Above_FG1_39;
    }
    else
    {
        pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_Half_17;
    }

    pParticle->mVisualFlags.Clear(BaseAnimatedWithPhysicsGameObject::VisualFlags::eApplyShadowZoneColour);

    return pParticle;
}

Particle* New_Orb_Particle(FP xpos, FP ypos, FP velX, FP velY, FP scale, Layer layer, u8 r, u8 b, u8 g)
{
    const AnimRecord& orbRec = AnimRec(AnimId::ChantOrb_Particle);
    u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, orbRec.mResourceId, 0, 0);
    auto pParticle = relive_new Particle(xpos, ypos, AnimId::ChantOrb_Particle, ppRes);
    if (!pParticle)
    {
        return nullptr;
    }

    pParticle->mBaseAnimatedWithPhysicsGameObject_RGB.SetRGB(r, g, b);

    pParticle->mBaseAnimatedWithPhysicsGameObject_VelY = velY;
    pParticle->mBaseAnimatedWithPhysicsGameObject_VelX = velX;

    pParticle->mVisualFlags.Clear(BaseAnimatedWithPhysicsGameObject::VisualFlags::eApplyShadowZoneColour);

    pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderMode = TPageAbr::eBlend_1;

    if (layer != Layer::eLayer_0)
    {
        pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = layer;
    }
    else
    {
        if (scale == FP_FromInteger(1))
        {
            pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_36;
        }
        else
        {
            pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_Half_17;
        }
    }

    pParticle->mBaseAnimatedWithPhysicsGameObject_SpriteScale = scale;

    return pParticle;
}

Particle* New_TintChant_Particle(FP xpos, FP ypos, FP scale, Layer layer)
{
    return New_Orb_Particle(xpos, ypos, FP_FromInteger(0), FP_FromInteger(0), scale, layer, 128u, 128u, 128u);
}

// Fart/dust cloud particle spawner
void New_Smoke_Particles(FP xpos, FP ypos, FP scale, s16 count, u8 r, u8 g, u8 b)
{
    FP velYCounter = {};
    for (s32 i = 0; i < count; i++)
    {
        FP randX = (FP_FromInteger(Math_RandomRange(-3, 3)) * scale) + xpos;
        FP particleY = (FP_FromInteger(6 * (i + 1) / 2 * (1 - 2 * (i % 2))) * scale) + ypos;
        const AnimRecord& squibSmokeRec = AnimRec(AnimId::SquibSmoke_Particle);
        u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, squibSmokeRec.mResourceId, 0, 0);
        auto pParticle = relive_new Particle(randX, particleY, AnimId::SquibSmoke_Particle, ppRes);
        if (pParticle)
        {
            pParticle->mVisualFlags.Clear(BaseAnimatedWithPhysicsGameObject::VisualFlags::eApplyShadowZoneColour);
            pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Clear(AnimFlags::eBit16_bBlending);
            pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Set(AnimFlags::eBit15_bSemiTrans);
            pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderMode = TPageAbr::eBlend_3;

            pParticle->mBaseAnimatedWithPhysicsGameObject_RGB.SetRGB(r, g, b);

            pParticle->mBaseAnimatedWithPhysicsGameObject_VelX = (scale * FP_FromInteger(Math_RandomRange(-10, 10))) / FP_FromInteger(10);
            pParticle->mBaseAnimatedWithPhysicsGameObject_VelY = ((scale * velYCounter) * FP_FromInteger(Math_RandomRange(50, 50))) / FP_FromInteger(100);
            pParticle->mBaseAnimatedWithPhysicsGameObject_SpriteScale = scale;

            if (scale == FP_FromInteger(1))
            {
                pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_36;
            }
            else
            {
                pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_Half_17;
            }

            pParticle->field_F4_scale_amount = scale * FP_FromDouble(0.03);
            pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mFrameDelay = static_cast<u16>((i + 3) / 2);
            if (Math_NextRandom() < 127)
            {
                pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Set(AnimFlags::eBit5_FlipX);
            }
        }
        velYCounter -= FP_FromInteger(1);
    }
}

void New_RandomizedChant_Particle(BaseAliveGameObject* pObj)
{
    const FP ypos = pObj->mBaseAnimatedWithPhysicsGameObject_YPos - (pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(Math_RandomRange(30, 60)));
    const FP xpos = (pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale * FP_FromInteger(Math_RandomRange(-20, 20))) + pObj->mBaseAnimatedWithPhysicsGameObject_XPos;
    New_TintChant_Particle(xpos, ypos, pObj->mBaseAnimatedWithPhysicsGameObject_SpriteScale, Layer::eLayer_0);
}

Particle* New_TintShiny_Particle(FP xpos, FP ypos, FP scale, Layer layer)
{
    return New_Orb_Particle(xpos, ypos, FP_FromInteger(0), FP_FromInteger(0), scale, layer, 100u, 100u, 100u);
}

void New_ShootingZFire_Particle(FP xpos, FP ypos, FP scale)
{
    const AnimRecord& ZFireRec = AnimRec(AnimId::ShootingZFire_Particle);
    u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, ZFireRec.mResourceId, 0, 0);
    auto pParticle = relive_new Particle(xpos, ypos, AnimId::ShootingZFire_Particle, ppRes);
    if (pParticle)
    {
        pParticle->mVisualFlags.Clear(BaseAnimatedWithPhysicsGameObject::VisualFlags::eApplyShadowZoneColour);
        pParticle->mBaseAnimatedWithPhysicsGameObject_RGB.SetRGB(55, 55, 55);
        pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderMode = TPageAbr::eBlend_1;
        if (scale == FP_FromInteger(1))
        {
            pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_36;
        }
        else
        {
            pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_Half_17;
        }
        pParticle->mBaseAnimatedWithPhysicsGameObject_SpriteScale = scale;
    }
}

void New_ShootingFire_Particle(FP xpos, FP ypos, s8 direction, FP scale)
{
    const AnimRecord& shootingFireRec = AnimRec(AnimId::ShootingFire_Particle);
    u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, shootingFireRec.mResourceId, 0, 0);
    auto pParticle = relive_new Particle(xpos, ypos, AnimId::ShootingFire_Particle, ppRes);
    if (pParticle)
    {
        pParticle->mVisualFlags.Clear(BaseAnimatedWithPhysicsGameObject::VisualFlags::eApplyShadowZoneColour);
        pParticle->mBaseAnimatedWithPhysicsGameObject_RGB.SetRGB(55, 55, 55);
        pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderMode = TPageAbr::eBlend_1;

        if (scale == FP_FromInteger(1))
        {
            pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_36;
        }
        else
        {
            pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_Foreground_Half_17;
        }

        pParticle->mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Set(AnimFlags::eBit5_FlipX, direction & 1);
        pParticle->mBaseAnimatedWithPhysicsGameObject_SpriteScale = scale;
    }
}
