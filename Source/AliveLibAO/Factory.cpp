#include "stdafx_ao.h"
#include "Factory.hpp"
#include "../relive_lib/Function.hpp"
#include "GasCountDown.hpp"
#include "ResourceManager.hpp"
#include "../AliveLibAE/stdlib.hpp"
#include "RollingBallStopper.hpp"
#include "Game.hpp"
#include "Abe.hpp"
#include "Elum.hpp"
#include "PauseMenu.hpp"
#include "ZBall.hpp"
#include "SligSpawner.hpp"
#include "Slig.hpp"
#include "Bat.hpp"
#include "BellHammer.hpp"
#include "LiftMover.hpp"
#include "BackgroundAnimation.hpp"
#include "DoorLight.hpp"
#include "LightEffect.hpp"
#include "TimedMine.hpp"
#include "ChimeLock.hpp"
#include "CreditsController.hpp"
#include "Meat.hpp"
#include "ElectricWall.hpp"
#include "Dove.hpp"
#include "Math.hpp"
#include "MusicTrigger.hpp"
#include "SecurityOrb.hpp"
#include "SecurityClaw.hpp"
#include "BeeSwarmHole.hpp"
#include "BeeNest.hpp"
#include "Honey.hpp"
#include "HoneySack.hpp"
#include "TimerTrigger.hpp"
#include "PullRingRope.hpp"
#include "InvisibleSwitch.hpp"
#include "FallingItem.hpp"
#include "FootSwitch.hpp"
#include "HoistRocksEffect.hpp"
#include "RollingBall.hpp"
#include "Lever.hpp"
#include "SecurityDoor.hpp"
#include "BackgroundGlukkon.hpp"
#include "Well.hpp"
#include "ZzzSpawner.hpp"
#include "BirdPortal.hpp"
#include "SlogSpawner.hpp"
#include "DoorFlame.hpp"
#include "BoomMachine.hpp"
#include "GasEmitter.hpp"
#include "MotionDetector.hpp"
#include "LCDStatusBoard.hpp"
#include "FlintLockFire.hpp"
#include "MeatSaw.hpp"
#include "TrapDoor.hpp"
#include "Abe.hpp"
#include "Mudokon.hpp"
#include "HintFly.hpp"
#include "Door.hpp"
#include "Mine.hpp"
#include "SlingMudokon.hpp"
#include "MainMenu.hpp"
#include "DDCheat.hpp"
#include "Slog.hpp"
#include "LCDScreen.hpp"
#include "UXB.hpp"
#include "Scrab.hpp"
#include "Paramite.hpp"
#include "MovingBomb.hpp"
#include "../relive_lib/GameObjects/ShadowZone.hpp"
#include "LiftPoint.hpp"
#include "RockSack.hpp"
#include "MeatSack.hpp"

#include "StringHashCollection.hpp"
#include <functional>

namespace AO {

static constexpr AnimId kAbeGibs[3] = {
    AnimId::Abe_Head_Gib,
    AnimId::Abe_Arm_Gib,
    AnimId::Abe_Body_Gib};

static constexpr AnimId kSlogGibs[2] = {
    AnimId::Slog_Head_Gib,
    AnimId::Slog_Body_Gib};

static constexpr AnimId kElumGibs[3] = {
    AnimId::Elum_Head_Gib,
    AnimId::Elum_Arm_Gib,
    AnimId::Elum_Body_Gib};

static constexpr AnimId kSligGibs[3] = {
    AnimId::Slig_Head_Gib,
    AnimId::Slig_Arm_Gib,
    AnimId::Slig_Body_Gib};

void Factory::Factory_Hoist(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eRuptureFarms:
            case EReliveLevelIds::eRuptureFarmsReturn:
                ResourceManagerWrapper::PendAnimation(AnimId::RuptureFarms_HoistRock1);
                ResourceManagerWrapper::PendAnimation(AnimId::RuptureFarms_HoistRock2);
                ResourceManagerWrapper::PendAnimation(AnimId::RuptureFarms_HoistRock3);
                break;

            default:
                ResourceManagerWrapper::PendAnimation(AnimId::AO_HoistRock1);
                ResourceManagerWrapper::PendAnimation(AnimId::AO_HoistRock2);
                ResourceManagerWrapper::PendAnimation(AnimId::AO_HoistRock3);
                break;
        }
    }
    else
    {
        auto pHoistTlv = static_cast<relive::Path_Hoist*>(pTlv);
        if (pHoistTlv->mHoistType == relive::Path_Hoist::Type::eOffScreen)
        {
            relive_new HoistRocksEffect(pHoistTlv, tlvId);
            // OG issue, no reset on failure ??
        }
        else
        {
            Path::TLV_Reset(tlvId, -1, 0, 0);
        }
    }
}

void Factory::Factory_Edge(relive::Path_TLV* /*pTlv*/, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        // Empty
    }
    else
    {
        Path::TLV_Reset(tlvId, -1, 0, 0);
    }
}

void Factory::Factory_Door(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eRuptureFarms:
            case EReliveLevelIds::eBoardRoom:
            case EReliveLevelIds::eRuptureFarmsReturn:
                ResourceManagerWrapper::PendAnimation(AnimId::Door_RuptureFarms_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::Door_RuptureFarms_Closed);
                break;

            case EReliveLevelIds::eLines:
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Lines_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Lines_Closed);
                break;

            case EReliveLevelIds::eDesert:
            case EReliveLevelIds::eDesertTemple:
            case EReliveLevelIds::eDesertEscape:
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Desert_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Desert_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::HubDoor_Desert_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::HubDoor_Desert_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::FinalTestDoor_Desert_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::FinalTestDoor_Desert_Closed);
                break;

            default:
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Forest_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Forest_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::HubDoor_Forest_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::HubDoor_Forest_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::FinalTestDoor_Forest_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::FinalTestDoor_Forest_Closed);
                break;
        }
    }
    else
    {
        relive_new Door(static_cast<relive::Path_Door*>(pTlv), tlvId);
    }
}

void Factory::Factory_ShadowZone(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new ShadowZone(static_cast<relive::Path_ShadowZone*>(pTlv), tlvId);
    }
}

void Factory::Factory_LiftPoint(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eRuptureFarms:
            case EReliveLevelIds::eBoardRoom:
            case EReliveLevelIds::eRuptureFarmsReturn:
                ResourceManagerWrapper::PendAnimation(AnimId::Rope_R1);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftPlatform_RuptureFarms);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftBottomWheel_RuptureFarms);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftTopWheel_RuptureFarms);
                break;

            case EReliveLevelIds::eLines:
                ResourceManagerWrapper::PendAnimation(AnimId::Rope_Lines);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftPlatform_Lines);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftBottomWheel_Lines);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftTopWheel_Lines);
                break;

            case EReliveLevelIds::eDesert:
                ResourceManagerWrapper::PendAnimation(AnimId::Rope_R1);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftPlatform_Desert);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftBottomWheel_Desert);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftTopWheel_Desert);
                break;

            case EReliveLevelIds::eDesertTemple:
            case EReliveLevelIds::eDesertEscape:
                ResourceManagerWrapper::PendAnimation(AnimId::Rope_R1);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftPlatform_Desert2);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftBottomWheel_Desert2);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftTopWheel_Desert2);
                break;

            default:
                ResourceManagerWrapper::PendAnimation(AnimId::Rope_Lines);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftPlatform_Forest);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftBottomWheel_Forest);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftTopWheel_Forest);
                break;
        }
    }
    else
    {
        for (s32 idx = 0; idx < gBaseGameObjects->Size(); idx++)
        {
            BaseGameObject* pObjIter = gBaseGameObjects->ItemAt(idx);
            if (!pObjIter)
            {
                break;
            }

            if (!pObjIter->GetDead() && pObjIter->Type() == ReliveTypes::eLiftPoint)
            {
                auto pLiftObj = static_cast<LiftPoint*>(pObjIter);

                const s16 xpos_i = FP_GetExponent(pLiftObj->mXPos);
                if (pTlv->mTopLeftX <= xpos_i
                    && xpos_i <= pTlv->mBottomRightX
                    && pLiftObj->mCurrentLevel == gMap.mCurrentLevel
                    && pLiftObj->mCurrentPath == gMap.mCurrentPath)
                {
                    Path::TLV_Reset(tlvId, -1, 0, 0);
                    return;
                }
            }
        }

        if (pTlv->mTlvSpecificMeaning & 2 || (pTlv->mTlvSpecificMeaning == 0 && static_cast<relive::Path_LiftPoint*>(pTlv)->mIsStartPoint == relive::reliveChoice::eYes))
        {
            relive_new LiftPoint(static_cast<relive::Path_LiftPoint*>(pTlv), tlvId);
        }
        else
        {
            relive::Path_TLV* pTlvIter = nullptr;
            s16 pointNumber = 1;
            while (pointNumber < 8)
            {
                pTlvIter = gMap.Get_First_TLV_For_Offsetted_Camera(
                    0,
                    pointNumber / 2 * (pointNumber % 2 != 0 ? -1 : 1));
                while (pTlvIter)
                {
                    if (pTlvIter->mTlvType == ReliveTypes::eLiftPoint)
                    {
                        const auto tlv_x = pTlv->mTopLeftX;
                        const auto absX = pTlvIter->mTopLeftX - tlv_x >= 0 ? pTlvIter->mTopLeftX - tlv_x : tlv_x - pTlvIter->mTopLeftX;
                        if (absX < 5)
                        {
                            if (pTlvIter->mTlvSpecificMeaning & 2 || (pTlvIter->mTlvSpecificMeaning == 0 && static_cast<relive::Path_LiftPoint*>(pTlvIter)->mIsStartPoint == relive::reliveChoice::eYes))
                            {
                                relive_new LiftPoint(static_cast<relive::Path_LiftPoint*>(pTlvIter), tlvId);
                                return;
                            }
                        }
                    }
                    pTlvIter = Path_TLV::Next_446460(pTlvIter);
                }
                pointNumber++;
            }

            relive_new LiftPoint(static_cast<relive::Path_LiftPoint*>(pTlv), tlvId);
        }
    }
}

void Factory::Factory_Well(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Well_Leaf);
    }
    else
    {
        const FP xpos = FP_FromInteger(pTlv->mTopLeftX);
        const FP ypos = FP_FromInteger(pTlv->mTopLeftY);
        relive_new Well(static_cast<relive::Path_WellBase*>(pTlv), xpos, ypos, tlvId);
    }
}

void Factory::Factory_Dove(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        auto pDoveTlv = static_cast<relive::Path_Dove*>(pTlv);

        const s16 width = pDoveTlv->Width();
        const s16 height = pDoveTlv->Height();

        for (s32 i = 0; i < pDoveTlv->mDoveCount; i++)
        {
            auto pDove = relive_new Dove(
                AnimId::Dove_Idle,
                tlvId,
                pDoveTlv->mScale != relive::reliveScale::eFull ? FP_FromDouble(0.5) : FP_FromInteger(1));

            if (pDove)
            {
                s16 ypos = 0;
                if (pDoveTlv->mPixelPerfect == relive::reliveChoice::eYes)
                {
                    pDove->mXPos = FP_FromInteger(pDoveTlv->mTopLeftX);
                    ypos = pDoveTlv->mTopLeftY;
                }
                else
                {
                    pDove->mXPos = FP_FromInteger(pDoveTlv->mTopLeftX + width * Math_NextRandom() / 256);
                    ypos = pDoveTlv->mTopLeftY + height * Math_NextRandom() / 256;
                }

                pDove->mYPos = FP_FromInteger(ypos) + FP_FromInteger(10);
            }
        }
    }
    else
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Dove_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::Dove_Flying);
    }
}

void Factory::Factory_RockSack(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Rock);
        ResourceManagerWrapper::PendAnimation(AnimId::RockSack_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::RockSack_SoftHit);
        ResourceManagerWrapper::PendAnimation(AnimId::RockSack_HardHit);

        if (gMap.mCurrentLevel == EReliveLevelIds::eStockYards || gMap.mCurrentLevel == EReliveLevelIds::eStockYardsReturn)
        {
        }
    }
    else
    {
        relive_new RockSack(static_cast<relive::Path_RockSack*>(pTlv), tlvId);
    }
}

void Factory::Factory_ZBall(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Swinging_Ball_Fast);
        ResourceManagerWrapper::PendAnimation(AnimId::Swinging_Ball_Normal);
        ResourceManagerWrapper::PendAnimation(AnimId::Swinging_Ball_Slow);
    }
    else
    {
        relive_new ZBall(static_cast<relive::Path_ZBall*>(pTlv), tlvId);
    }
}

void Factory::Factory_FallingItem(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Stick_Gib);
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eRuptureFarms:
            case EReliveLevelIds::eRuptureFarmsReturn:
                ResourceManagerWrapper::PendAnimation(AnimId::FallingMeat_Waiting);
                ResourceManagerWrapper::PendAnimation(AnimId::FallingMeat_Falling);
                ResourceManagerWrapper::PendAnimation(AnimId::Meat_Gib);
                break;

            case EReliveLevelIds::eLines:
            case EReliveLevelIds::eBoardRoom:
            case EReliveLevelIds::eStockYards:
            case EReliveLevelIds::eDesert:
            case EReliveLevelIds::eDesertTemple:
            case EReliveLevelIds::eDesertEscape:
                ResourceManagerWrapper::PendAnimation(AnimId::AO_FallingRock_Falling);
                ResourceManagerWrapper::PendAnimation(AnimId::AO_FallingRock_Waiting);
                ResourceManagerWrapper::PendAnimation(AnimId::Rock_Gib);
                break;

            default:
                ResourceManagerWrapper::PendAnimation(AnimId::AO_FallingRock_Falling);
                ResourceManagerWrapper::PendAnimation(AnimId::AO_FallingRock_Waiting);
                ResourceManagerWrapper::PendAnimation(AnimId::Rock_Gib);
                break;
        }
    }
    else
    {
        relive_new FallingItem(static_cast<relive::Path_FallingItem*>(pTlv), tlvId);
    }
}

void Factory::Factory_PullRingRope(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eRuptureFarms:
            case EReliveLevelIds::eBoardRoom:
            case EReliveLevelIds::eRuptureFarmsReturn:
                ResourceManagerWrapper::PendAnimation(AnimId::Rope_R1);
                ResourceManagerWrapper::PendAnimation(AnimId::Pullring_Farms_Idle);
                ResourceManagerWrapper::PendAnimation(AnimId::Pullring_Farms_UseBegin);
                ResourceManagerWrapper::PendAnimation(AnimId::Pullring_Farms_UseEnd);
                break;

            case EReliveLevelIds::eDesert:
            case EReliveLevelIds::eDesertTemple:
                ResourceManagerWrapper::PendAnimation(AnimId::Rope_R1);
                ResourceManagerWrapper::PendAnimation(AnimId::Pullring_Desert_Idle);
                ResourceManagerWrapper::PendAnimation(AnimId::Pullring_Desert_UseBegin);
                ResourceManagerWrapper::PendAnimation(AnimId::Pullring_Desert_UseEnd);
                break;

            default:
                ResourceManagerWrapper::PendAnimation(AnimId::Rope_Lines);
                ResourceManagerWrapper::PendAnimation(AnimId::Pullring_Desert_Idle);
                ResourceManagerWrapper::PendAnimation(AnimId::Pullring_Desert_UseBegin);
                ResourceManagerWrapper::PendAnimation(AnimId::Pullring_Desert_UseEnd);
                break;
        }
    }
    else
    {
        relive_new PullRingRope(static_cast<relive::Path_PullRingRope*>(pTlv), tlvId);
    }
}

void Factory::Factory_BackgroundAnimation(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        auto pBgAnim = static_cast<relive::Path_BackgroundAnimation*>(pTlv);
        // ResourceManagerWrapper::PendAnimation(static_cast<AnimId>(pBgAnim->mAnimId));
        relive_new BackgroundAnimation(pBgAnim, tlvId);
    }
}

void Factory::Factory_Honey(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Honey);
        ResourceManagerWrapper::PendAnimation(AnimId::Honey_Drip);
    }
    else
    {
        const auto midPoint = pTlv->Width() / 2;
        auto pHoney = relive_new Honey(
            FP_FromInteger(midPoint + pTlv->mTopLeftX),
            FP_FromInteger(pTlv->mTopLeftY + 24));
        if (pHoney)
        {
            pHoney->mTlvInfo = tlvId;
        }
    }
}

void Factory::Factory_TimedMine(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pTimedMineTlv = static_cast<relive::Path_TimedMine*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
        ResourceManagerWrapper::PendAnims(kElumGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::TimedMine_Activated);
        ResourceManagerWrapper::PendAnimation(AnimId::TimedMine_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::Bomb_Flash);
        ResourceManagerWrapper::PendAnimation(AnimId::Bomb_RedGreenTick);
        ResourceManagerWrapper::PendAnimation(AnimId::Rock_Gib);
        ResourceManagerWrapper::PendAnimation(AnimId::GroundExplosion);
        if (gMap.mCurrentLevel == EReliveLevelIds::eStockYards || gMap.mCurrentLevel == EReliveLevelIds::eStockYardsReturn)
        {
        }
    }
    else
    {
        relive_new TimedMine(pTimedMineTlv, tlvId);
    }
}

static void LoadWalkingSligResources(LoadMode loadMode, BitField16<SligFlags_DisabledRes> disabledResources)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Slig::sSligMotionAnimIds);
        ResourceManagerWrapper::PendAnims(kSligGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::ObjectShadow);
        ResourceManagerWrapper::PendAnimation(AnimId::ShootingZFire_Particle);
        ResourceManagerWrapper::PendAnimation(AnimId::ShootingFire_Particle);
        ResourceManagerWrapper::PendAnimation(AnimId::Bullet_Shell);

        if (gMap.mCurrentLevel == EReliveLevelIds::eStockYards || gMap.mCurrentLevel == EReliveLevelIds::eStockYardsReturn)
        {
        }
    }
    else
    {
        if (!(disabledResources.Get(eDisabledRes_Bit1_SligLever)))
        {
        }

        if (!(disabledResources.Get(eDisabledRes_Bit2_SligLift)))
        {
        }

        if (!(disabledResources.Get(eDisabledRes_Bit3_SligZ)))
        {
        }

        if (!(disabledResources.Get(eDisabledRes_Bit7_SligSleep)))
        {
        }

        if (!(disabledResources.Get(eDisabledRes_Bit9_SligEdge)))
        {
        }

        if (!(disabledResources.Get(eDisabledRes_Bit10_SligSmash)))
        {
        }

        if (!(disabledResources.Get(eDisabledRes_Bit11_SligBeat)))
        {
        }

        if (!(disabledResources.Get(eDisabledRes_Bit8_SligKnfd)))
        {
        }
    }
}

void Factory::Factory_Slig(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pSligTlv = static_cast<relive::Path_Slig*>(pTlv);
    LoadWalkingSligResources(loadMode, pSligTlv->mData.mDisabledResourcesAO);

    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        // Do nothing
    }
    else
    {
        relive_new Slig(pSligTlv, tlvId);
    }
}

void Factory::Factory_Slog(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Slog::sSlogMotionAnimIds);
    }
    else
    {
        relive_new Slog(static_cast<relive::Path_Slog*>(pTlv), tlvId);
    }
}

void Factory::Factory_Lever(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eRuptureFarms:
            case EReliveLevelIds::eStockYards:
            case EReliveLevelIds::eStockYardsReturn:
            case EReliveLevelIds::eBoardRoom:
            case EReliveLevelIds::eRuptureFarmsReturn:
                ResourceManagerWrapper::PendAnimation(AnimId::RuptureFarms_Lever_Idle);
                ResourceManagerWrapper::PendAnimation(AnimId::RuptureFarms_Lever_Pull_Left);
                ResourceManagerWrapper::PendAnimation(AnimId::RuptureFarms_Lever_Pull_Release_Left);
                ResourceManagerWrapper::PendAnimation(AnimId::RuptureFarms_Lever_Pull_Right);
                ResourceManagerWrapper::PendAnimation(AnimId::RuptureFarms_Lever_Pull_Release_Right);
                break;

            case EReliveLevelIds::eLines:
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_Lever_Idle);
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_Lever_Pull_Left);
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_Lever_Pull_Release_Left);
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_Lever_Pull_Right);
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_Lever_Pull_Release_Right);
                break;

            case EReliveLevelIds::eDesert:
            case EReliveLevelIds::eDesertTemple:
            case EReliveLevelIds::eDesertEscape:
                ResourceManagerWrapper::PendAnimation(AnimId::Lever_Idle);
                ResourceManagerWrapper::PendAnimation(AnimId::Lever_Pull_Left);
                ResourceManagerWrapper::PendAnimation(AnimId::Lever_Pull_Release_Left);
                ResourceManagerWrapper::PendAnimation(AnimId::Lever_Pull_Right);
                ResourceManagerWrapper::PendAnimation(AnimId::Lever_Pull_Release_Right);
                break;

            default:
                ResourceManagerWrapper::PendAnimation(AnimId::Lever_Idle);
                ResourceManagerWrapper::PendAnimation(AnimId::Lever_Pull_Left);
                ResourceManagerWrapper::PendAnimation(AnimId::Lever_Pull_Release_Left);
                ResourceManagerWrapper::PendAnimation(AnimId::Lever_Pull_Right);
                ResourceManagerWrapper::PendAnimation(AnimId::Lever_Pull_Release_Right);
                break;
        }
    }
    else
    {
        relive_new Lever(static_cast<relive::Path_Lever*>(pTlv), tlvId);
    }
}

void Factory::Factory_BellHammer(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new BellHammer(static_cast<relive::Path_BellHammer*>(pTlv), tlvId);
    }
    else
    {
        ResourceManagerWrapper::PendAnimation(AnimId::BellHammer_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::BellHammer_Smashing);
        ResourceManagerWrapper::PendAnims(Elum::gElumMotionAnimIds);
    }
}

void Factory::Factory_SecurityOrb(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pSecurityOrbTlv = static_cast<relive::Path_SecurityOrb*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Security_Orb);
        ResourceManagerWrapper::PendAnimation(AnimId::Zap_Line_Blue);
        ResourceManagerWrapper::PendAnimation(AnimId::Zap_Line_Red);
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
        ResourceManagerWrapper::PendAnims(kElumGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::Metal_Gib);
        ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion);
    }
    else
    {
        relive_new SecurityOrb(pSecurityOrbTlv, tlvId);
    }
}

void Factory::Factory_LiftMudokon(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Mudokon::sMudMotionAnimIds);
    }
    else
    {
        relive_new Mudokon(pTlv, tlvId);
    }
}

void Factory::Factory_BeeSwarmHole(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Bee_Swarm);
        if (gMap.mCurrentLevel == EReliveLevelIds::eForest || gMap.mCurrentLevel == EReliveLevelIds::eDesert)
        {
        }
    }
    else
    {
        relive_new BeeSwarmHole(static_cast<relive::Path_BeeSwarmHole*>(pTlv), tlvId);
    }
}

void Factory::Factory_HoneySack(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Honey);
        ResourceManagerWrapper::PendAnimation(AnimId::Honey_Drip);
        ResourceManagerWrapper::PendAnimation(AnimId::HoneySack_Hanging);
        ResourceManagerWrapper::PendAnimation(AnimId::HoneySack_OnGround);
        ResourceManagerWrapper::PendAnimation(AnimId::HoneySack_Falling);
        ResourceManagerWrapper::PendAnimation(AnimId::HoneySack_FallingToSmashed);
    }
    else
    {
        relive_new HoneySack(static_cast<relive::Path_HoneySack*>(pTlv), tlvId);
    }
}

void Factory::Factory_AbeStart(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& /*tlvId*/, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2 && !gAttract)
    {
        if (!gPauseMenu)
        {
            gPauseMenu = relive_new PauseMenu();
        }

        if (!sActiveHero)
        {
            sActiveHero = relive_new Abe();
            if (sActiveHero)
            {
                sActiveHero->mXPos = FP_FromInteger(pTlv->mTopLeftX + 12);
                sActiveHero->mYPos = FP_FromInteger(pTlv->mTopLeftY);
            }
        }
    }
    else
    {
        ResourceManagerWrapper::PendAnims(Abe::sAbeMotionAnimIds);
    }
}

void Factory::Factory_ElumWall(relive::Path_TLV* /*pTlv*/, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
    }
    else
    {
        Path::TLV_Reset(tlvId, -1, 0, 0);
    }
}

void Factory::Factory_SlingMud(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new SlingMudokon(static_cast<relive::Path_SlingMudokon*>(pTlv), tlvId);
    }
    else
    {
        ResourceManagerWrapper::PendAnims(SlingMudokon::sSlingMudMotionAnimIds);
        // kSparksAOResID was loaded but there is no AnimId entry for it?...
    }
}

void Factory::Factory_BeeNest(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Bee_Swarm);
    }
    else
    {
        relive_new BeeNest(static_cast<relive::Path_BeeNest*>(pTlv), tlvId);
    }
}

void Factory::Factory_Mine(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pMineTlv = static_cast<relive::Path_Mine*>(pTlv);

    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
        ResourceManagerWrapper::PendAnims(kElumGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::Mine);
        ResourceManagerWrapper::PendAnimation(AnimId::Mine_Flash);
        ResourceManagerWrapper::PendAnimation(AnimId::Rock_Gib);
        ResourceManagerWrapper::PendAnimation(AnimId::GroundExplosion);
        if (gMap.mCurrentLevel == EReliveLevelIds::eStockYards || gMap.mCurrentLevel == EReliveLevelIds::eStockYardsReturn)
        {
        }
    }
    else
    {
        relive_new Mine(pMineTlv, tlvId);
    }
}

void Factory::Factory_Uxb(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pUxbTlv = static_cast<relive::Path_UXB*>(pTlv);

    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
        ResourceManagerWrapper::PendAnims(kElumGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::UXB_Active);
        ResourceManagerWrapper::PendAnimation(AnimId::UXB_Toggle);
        ResourceManagerWrapper::PendAnimation(AnimId::UXB_Disabled);
        ResourceManagerWrapper::PendAnimation(AnimId::Bomb_Flash);
        ResourceManagerWrapper::PendAnimation(AnimId::Bomb_RedGreenTick);
        ResourceManagerWrapper::PendAnimation(AnimId::Rock_Gib);
        ResourceManagerWrapper::PendAnimation(AnimId::GroundExplosion);
        if (gMap.mCurrentLevel == EReliveLevelIds::eStockYards || gMap.mCurrentLevel == EReliveLevelIds::eStockYardsReturn)
        {
        }
    }
    else
    {
        relive_new UXB(pUxbTlv, tlvId);
    }
}

void Factory::Factory_Paramite(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Paramite::sParamiteMotionAnimIds);
        ResourceManagerWrapper::PendAnimation(AnimId::ParamiteWeb);
        return;
    }
    relive_new Paramite(static_cast<relive::Path_Paramite*>(pTlv), tlvId);
}

void Factory::Factory_Bat(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Bat_Flying);
        ResourceManagerWrapper::PendAnimation(AnimId::Bat);
        ResourceManagerWrapper::PendAnimation(AnimId::Bat_Unknown);
    }
    else
    {
        relive_new Bat(static_cast<relive::Path_Bat*>(pTlv), tlvId);
    }
}

void Factory::Factory_RingMudokon(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Mudokon::sMudMotionAnimIds);
    }
    else
    {
        relive_new Mudokon(pTlv, tlvId);
    }
}

void Factory::Factory_BirdPortal(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pBirdPortalTlv = static_cast<relive::Path_BirdPortal*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::BirdPortal_TerminatorShrink);
        ResourceManagerWrapper::PendAnimation(AnimId::BirdPortal_TerminatorIdle);
        ResourceManagerWrapper::PendAnimation(AnimId::BirdPortal_TerminatorGrow);
        ResourceManagerWrapper::PendAnimation(AnimId::BirdPortal_TerminatorShrink);
        ResourceManagerWrapper::PendAnimation(AnimId::BirdPortal_Sparks);
        ResourceManagerWrapper::PendAnimation(AnimId::BirdPortal_Flash);

        if (pBirdPortalTlv->mPortalType == relive::Path_BirdPortal::PortalType::eShrykull)
        {
            ResourceManagerWrapper::PendAnimation(AnimId::ShrykullStart);
            ResourceManagerWrapper::PendAnimation(AnimId::ShrykullTransform);
            ResourceManagerWrapper::PendAnimation(AnimId::ShrykullDetransform);
            ResourceManagerWrapper::PendAnimation(AnimId::Zap_Line_Blue);
            ResourceManagerWrapper::PendAnimation(AnimId::Zap_Line_Red);
        }
    }
    else
    {
        relive_new BirdPortal(pBirdPortalTlv, tlvId);
    }
}

void Factory::Factory_BellSongStone(relive::Path_TLV* /*pTlv*/, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        Path::TLV_Reset(tlvId, -1, 0, 0);
    }
}

void Factory::Factory_TrapDoor(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eRuptureFarms:
            case EReliveLevelIds::eBoardRoom:
            case EReliveLevelIds::eRuptureFarmsReturn:
                ResourceManagerWrapper::PendAnimation(AnimId::R1_TrapDoor_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::R1_TrapDoor_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::R1_TrapDoor_Opening);
                ResourceManagerWrapper::PendAnimation(AnimId::R1_TrapDoor_Closing);
                break;
            case EReliveLevelIds::eLines:
            case EReliveLevelIds::eStockYards:
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_TrapDoor_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_TrapDoor_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_TrapDoor_Opening);
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_TrapDoor_Closing);
                break;
            case EReliveLevelIds::eDesert:
            case EReliveLevelIds::eDesertTemple:
            case EReliveLevelIds::eDesertEscape:
                ResourceManagerWrapper::PendAnimation(AnimId::Desert_TrapDoor_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::Desert_TrapDoor_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::Desert_TrapDoor_Opening);
                ResourceManagerWrapper::PendAnimation(AnimId::Desert_TrapDoor_Closing);
                break;
            default:
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_TrapDoor_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_TrapDoor_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_TrapDoor_Opening);
                ResourceManagerWrapper::PendAnimation(AnimId::Lines_TrapDoor_Closing);
                break;
        }
    }
    else
    {
        relive_new TrapDoor(static_cast<relive::Path_TrapDoor*>(pTlv), tlvId);
    }
}

void Factory::Factory_RollingBall(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Stone_Ball);
        ResourceManagerWrapper::PendAnimation(AnimId::Stone_Ball_Rolling);
        ResourceManagerWrapper::PendAnimation(AnimId::Rock_Gib);
    }
    else
    {
        relive_new RollingBall(static_cast<relive::Path_RollingBall*>(pTlv), tlvId);
    }
}

static relive::Path_TLV* FindMatchingSligTLV(relive::Path_TLV* pTlvIter, relive::Path_SligBound* pTlv)
{
    while (pTlvIter)
    {
        if (pTlvIter->mTlvType == ReliveTypes::eSlig && pTlv->mSligBoundId == static_cast<relive::Path_Slig*>(pTlvIter)->mData.mSligBoundId && !pTlvIter->mTlvFlags.Get(relive::TlvFlags::eBit2_Destroyed))
        {
            return pTlvIter;
        }
        pTlvIter = Path_TLV::Next_446460(pTlvIter);
    }
    return nullptr;
}

void Factory::Factory_SligBoundLeft(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pBound = static_cast<relive::Path_SligBound*>(pTlv);
    LoadWalkingSligResources(loadMode, pBound->mDisabledResourcesAO);

    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        // Do nothing, handled in LoadSligResources
    }
    else
    {
        pBound->mTlvFlags.Clear(relive::TlvFlags::eBit1_Created);
        pBound->mTlvFlags.Clear(relive::TlvFlags::eBit2_Destroyed);

        for (s16 camX_idx = -2; camX_idx < 3; camX_idx++)
        {
            relive::Path_TLV* pTlvIter = gMap.Get_First_TLV_For_Offsetted_Camera(camX_idx, 0);
            pTlvIter = FindMatchingSligTLV(pTlvIter, pBound);
            if (pTlvIter)
            {
                pTlvIter->mTlvFlags.Set(relive::TlvFlags::eBit1_Created);
                pTlvIter->mTlvFlags.Set(relive::TlvFlags::eBit2_Destroyed);
                // AO OG bug tlvId not recalculated??
                relive_new Slig(static_cast<relive::Path_Slig*>(pTlvIter), tlvId);
                return;
            }
        }
    }
}

void Factory::Factory_RollingBallStopper(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Stone_Ball_Stopper);
    }
    else
    {
        relive_new RollingBallStopper(static_cast<relive::Path_RollingBallStopper*>(pTlv), tlvId);
    }
}

void Factory::Factory_FootSwitch(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Foot_Switch_Temple);
        ResourceManagerWrapper::PendAnimation(AnimId::Foot_Switch_Temple_Pressed);
    }
    else
    {
        relive_new FootSwitch(static_cast<relive::Path_FootSwitch*>(pTlv), tlvId);
    }
}

void Factory::Factory_SecurityClaw(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pSecurityClawTlv = static_cast<relive::Path_SecurityClaw*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Security_Claw_Lower_Open);
        ResourceManagerWrapper::PendAnimation(AnimId::Security_Claw_Lower_Close);
        ResourceManagerWrapper::PendAnimation(AnimId::Security_Claw_Lower_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::Security_Claw_Upper_Rotating);
        ResourceManagerWrapper::PendAnimation(AnimId::Security_Claw_Upper_NoRotation);
        ResourceManagerWrapper::PendAnimation(AnimId::Zap_Line_Blue);
        ResourceManagerWrapper::PendAnimation(AnimId::Zap_Line_Red);
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
        ResourceManagerWrapper::PendAnims(kElumGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::Metal_Gib);
        ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion);
    }
    else
    {
        relive_new SecurityClaw(pSecurityClawTlv, tlvId);
    }
}

void Factory::Factory_MotionDetector(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new MotionDetector(static_cast<relive::Path_MotionDetector*>(pTlv), tlvId);
    }
    else
    {
        ResourceManagerWrapper::PendAnimation(AnimId::MotionDetector_Flare);
        ResourceManagerWrapper::PendAnimation(AnimId::MotionDetector_Laser);
    }
}

void Factory::Factory_SligSpawner(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pSligTlv = static_cast<relive::Path_SligSpawner*>(pTlv);
    LoadWalkingSligResources(loadMode, pSligTlv->mData.mDisabledResourcesAO);

    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        // Do nothing, handled in LoadSligResources
    }
    else
    {
        relive_new SligSpawner(pTlv, &pSligTlv->mData, tlvId);
    }
}

void Factory::Factory_ElectricWall(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new ElectricWall(static_cast<relive::Path_ElectricWall*>(pTlv), tlvId);
    }
    else
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Electric_Wall);
    }
}

void Factory::Factory_LiftMover(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new LiftMover(static_cast<relive::Path_LiftMover*>(pTlv), tlvId);
    }
}

void Factory::Factory_ChimeLock(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new ChimeLock(static_cast<relive::Path_ChimeLock*>(pTlv), tlvId);
    }
    else
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Chime_Ball);
        ResourceManagerWrapper::PendAnimation(AnimId::BigChime);
        ResourceManagerWrapper::PendAnimation(AnimId::MediumChime);
        ResourceManagerWrapper::PendAnimation(AnimId::SmallChime);
        ResourceManagerWrapper::PendAnimation(AnimId::BigChime_Moving);
        ResourceManagerWrapper::PendAnimation(AnimId::MediumChime_Moving);
        ResourceManagerWrapper::PendAnimation(AnimId::SmallChime_Moving);
    }
}

void Factory::Factory_Elum(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Elum::gElumMotionAnimIds);
    }
    else
    {
        Elum::Spawn(tlvId);
        gElum->mXPos = FP_FromInteger(pTlv->mTopLeftX);
        gElum->mYPos = FP_FromInteger(pTlv->mTopLeftY);
    }
}

void Factory::Factory_MeatSack(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Meat);
        ResourceManagerWrapper::PendAnimation(AnimId::MeatSack_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::MeatSack_Hit);
    }
    else
    {
        relive_new MeatSack(static_cast<relive::Path_MeatSack*>(pTlv), tlvId);
    }
}

void Factory::Factory_Scrab(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Scrab::sScrabMotionAnimIds);
        return;
    }
    relive_new Scrab(static_cast<relive::Path_Scrab*>(pTlv), tlvId);
}

void Factory::Factory_FlintLockFire(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Fire);
        ResourceManagerWrapper::PendAnimation(AnimId::FlintLock_Gourd);
        ResourceManagerWrapper::PendAnimation(AnimId::FlintLock_Hammers_Disabled);
        ResourceManagerWrapper::PendAnimation(AnimId::FlintLock_Hammers_Activating);
    }
    else
    {
        relive_new FlintLockFire(static_cast<relive::Path_FlintLockFire*>(pTlv), tlvId);
    }
}

void Factory::Factory_SligBoundRight(relive::Path_TLV* pTlv, Map* pMap, const Guid& tlvId, LoadMode loadMode)
{
    Factory_SligBoundLeft(pTlv, pMap, tlvId, loadMode);
}

void Factory::Factory_InvisibleSwitch(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new InvisibleSwitch(static_cast<relive::Path_InvisibleSwitch*>(pTlv), tlvId);
    }
}

void Factory::Factory_WorkerMudokon(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pMudTlv = static_cast<relive::Path_Mudokon*>(pTlv);
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        switch (pMudTlv->mJob)
        {
            case relive::Path_Mudokon::MudJobs::eStandScrub:
                break;

            case relive::Path_Mudokon::MudJobs::eSitChant:
                break;
        }

        relive_new Mudokon(pTlv, tlvId);
    }
    else
    {
        ResourceManagerWrapper::PendAnims(Mudokon::sMudMotionAnimIds);
        switch (pMudTlv->mJob)
        {
            case relive::Path_Mudokon::MudJobs::eStandScrub:
            {
            }
            break;

            case relive::Path_Mudokon::MudJobs::eSitScrub:
            {
            }
            break;

            case relive::Path_Mudokon::MudJobs::eSitChant:
            {
            }
            break;
        }
    }
}

void Factory::Factory_DoorFlame(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Fire);
        ResourceManagerWrapper::PendAnimation(AnimId::Door_FireBackgroundGlow);
    }
    else
    {
        relive_new DoorFlame(static_cast<relive::Path_DoorFlame*>(pTlv), tlvId);
    }
}

void Factory::Factory_MovingBomb(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pMovingBombTlv = static_cast<relive::Path_MovingBomb*>(pTlv);

    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::MovingBomb);
        ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion);
        ResourceManagerWrapper::PendAnimation(AnimId::Metal_Gib);
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnims(kElumGibs);

        if (gMap.mCurrentLevel == EReliveLevelIds::eStockYards || gMap.mCurrentLevel == EReliveLevelIds::eStockYardsReturn)
        {
        }
    }
    else
    {
        relive_new MovingBomb(pMovingBombTlv, tlvId);
    }
}

void Factory::Factory_MeatSaw(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::MeatSawMotor);
        ResourceManagerWrapper::PendAnimation(AnimId::MeatSaw_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::MeatSaw_Moving);
        ResourceManagerWrapper::PendAnims(kAbeGibs);
    }
    else
    {
        relive_new MeatSaw(static_cast<relive::Path_MeatSaw*>(pTlv), tlvId);
    }
}

void Factory::Factory_MainMenuController(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (gMainMenuInstanceCount == 0)
    {
        if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
        {
            ResourceManagerWrapper::PendAnims(Menu::kAnims);
        }
        else
        {
            relive_new Menu(pTlv, tlvId);
        }
    }
}

void Factory::Factory_HintFly(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new HintFly(static_cast<relive::Path_HintFly*>(pTlv), tlvId);
    }
    else
    {
        ResourceManagerWrapper::PendAnimation(AnimId::HintFly);
    }
}

void Factory::Factory_TimerTrigger(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new TimerTrigger(static_cast<relive::Path_TimerTrigger*>(pTlv), tlvId);
    }
}

void Factory::Factory_SecurityDoor(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Security_Door_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::Security_Door_Speak);
    }
    else
    {
        relive_new SecurityDoor(static_cast<relive::Path_SecurityDoor*>(pTlv), tlvId);
    }
}

void Factory::Factory_BoomMachine(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pBoomMachineTlv = static_cast<relive::Path_BoomMachine*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Grenade);
        ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion);
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::Metal_Gib);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::BoomMachine_Nozzle_DropGrenade);
        ResourceManagerWrapper::PendAnimation(AnimId::BoomMachine_Nozzle_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::BoomMachine_Button_Off);
        ResourceManagerWrapper::PendAnimation(AnimId::BoomMachine_Button_On);
        return;
    }

    relive_new BoomMachine(pBoomMachineTlv, tlvId);
}

void Factory::Factory_LCDScreen(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
    }
    else
    {
        relive_new LCDScreen(static_cast<relive::Path_LCDScreen*>(pTlv), tlvId);
    }
}

void Factory::Factory_HandStone(relive::Path_TLV* /*pTlv*/, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Circular_Fade);
    }
    else
    {
        Path::TLV_Reset(tlvId, -1, 0, 0);
    }
}

void Factory::Factory_CreditsController(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        if (!gCreditsControllerExists)
        {
            relive_new CreditsController(static_cast<relive::Path_CreditsController*>(pTlv), tlvId);
        }
    }
}

void Factory::Factory_LCDStatusBoard(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
    }
    else
    {
        relive_new LCDStatusBoard(static_cast<relive::Path_LCDStatusBoard*>(pTlv), tlvId);
    }
}

void Factory::Factory_SwitchStateBooleanLogic(relive::Path_TLV* /*pTlv*/, Map* /*pMap*/, const Guid& /*tlvId*/, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        LOG_WARNING("Factory_SwitchStateBooleanLogic_487B80 tlv converter not implemented");
        // relive_new SwitchStateBooleanLogic(static_cast<relive::Path_SwitchStateBooleanLogic*>(pTlv), tlvId);
    }
}

void Factory::Factory_MusicTrigger(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new MusicTrigger(static_cast<relive::Path_MusicTrigger*>(pTlv), tlvId);
    }
}

void Factory::Factory_LightEffect(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    auto pPathLightTlv = static_cast<relive::Path_LightEffect*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        switch (pPathLightTlv->mType)
        {
            case relive::Path_LightEffect::Type::Star:
                ResourceManagerWrapper::PendAnimation(AnimId::Star);
                break;

            case relive::Path_LightEffect::Type::GoldGlow:
                ResourceManagerWrapper::PendAnimation(AnimId::GoldGlow);
                break;

            case relive::Path_LightEffect::Type::GreenGlow:
                ResourceManagerWrapper::PendAnimation(AnimId::GreenGlow);
                break;

            case relive::Path_LightEffect::Type::FlintGlow:
                ResourceManagerWrapper::PendAnimation(AnimId::FlintGlow);
                break;

            case relive::Path_LightEffect::Type::Switchable_RedGreenDoorLights:
                ResourceManagerWrapper::PendAnimation(AnimId::RedDoorLight);
                ResourceManagerWrapper::PendAnimation(AnimId::GreenDoorLight);
                break;

            case relive::Path_LightEffect::Type::Switchable_RedGreenHubLight:
                ResourceManagerWrapper::PendAnimation(AnimId::RedHubLight);
                ResourceManagerWrapper::PendAnimation(AnimId::GreenHubLight);
                break;

            default:
                return;
        }
    }
    else
    {
        switch (pPathLightTlv->mType)
        {
            case relive::Path_LightEffect::Type::Star:
            {
                relive_new LightEffect(pPathLightTlv, tlvId);
                break;
            }

            case relive::Path_LightEffect::Type::GoldGlow:
            {
                relive_new DoorLight(pPathLightTlv, tlvId);
                break;
            }

            case relive::Path_LightEffect::Type::GreenGlow:
            {
                relive_new DoorLight(pPathLightTlv, tlvId);
                break;
            }

            case relive::Path_LightEffect::Type::FlintGlow:
            {
                relive_new DoorLight(pPathLightTlv, tlvId);
                break;
            }

            case relive::Path_LightEffect::Type::Switchable_RedGreenDoorLights:
            case relive::Path_LightEffect::Type::Switchable_RedGreenHubLight:
            {
                relive_new DoorLight(pPathLightTlv, tlvId);
                break;
            }

            default:
                return;
        }
    }
}

void Factory::Factory_SlogSpawner(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Slog::sSlogMotionAnimIds);
    }
    else
    {
        relive_new SlogSpawner(static_cast<relive::Path_SlogSpawner*>(pTlv), tlvId);
    }
}

void Factory::Factory_GasCountdown(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
    }
    else
    {
        relive_new GasCountDown(static_cast<relive::Path_GasCountDown*>(pTlv), tlvId);
    }
}

void Factory::Factory_RingCancel(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        auto pRingCancel = static_cast<relive::Path_RingCancel*>(pTlv);
        if (pRingCancel->mRemovesShrykull)
        {
            if (sActiveHero->field_168_ring_pulse_timer)
            {
                if (sActiveHero->field_16C_bHaveShrykull)
                {
                    sActiveHero->field_168_ring_pulse_timer = 0;
                }
            }
        }
        else
        {
            if (!sActiveHero->field_16C_bHaveShrykull)
            {
                sActiveHero->field_168_ring_pulse_timer = 0;
            }
        }
        Path::TLV_Reset(tlvId, -1, 0, 0);
    }
}


void Factory::Factory_GasEmitter(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new GasEmitter(static_cast<relive::Path_GasEmitter*>(pTlv), tlvId);
    }
}


void Factory::Factory_ZzzSpawner(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new ZzzSpawner(static_cast<relive::Path_ZzzSpawner*>(pTlv), tlvId);
    }
}


void Factory::Factory_BackgroundGlukkon(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Background_Glukkon_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::Background_Glukkon_Laugh);
        ResourceManagerWrapper::PendAnimation(AnimId::Background_Glukkon_KillHim1);
        ResourceManagerWrapper::PendAnimation(AnimId::Background_Glukkon_KillHim2);
        ResourceManagerWrapper::PendAnimation(AnimId::Background_Glukkon_Dying);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion);
    }
    else
    {
        relive_new BackgroundGlukkon(static_cast<relive::Path_BackgroundGlukkon*>(pTlv), tlvId);
    }
}


void Factory::Factory_KillUnsavedMuds(relive::Path_TLV* /*pTlv*/, Map* pMap, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        // OG bug fix - added an extra check that checks if the map has changed
        // which prevents that the killed mudokon count becomes inaccurate or even negative.
        if (!gbKillUnsavedMudsDone && pMap->mMapChanged)
        {
            gbKillUnsavedMudsDone = true;
            sKilledMudokons = 28 - sRescuedMudokons;
            Path::TLV_Reset(tlvId, -1, 0, 1);
        }
    }
}

Factory::Factory()
{
    mMap[ReliveTypes::eHoist] = &Factory::Factory_Hoist;
    mMap[ReliveTypes::eEdge] = &Factory::Factory_Edge;
    mMap[ReliveTypes::eDoor] = &Factory::Factory_Door;
    mMap[ReliveTypes::eShadowZone] = &Factory::Factory_ShadowZone;
    mMap[ReliveTypes::eLiftPoint] = &Factory::Factory_LiftPoint;
    mMap[ReliveTypes::eWellExpress] = &Factory::Factory_Well;
    mMap[ReliveTypes::eWellLocal] = &Factory::Factory_Well;
    mMap[ReliveTypes::eDove] = &Factory::Factory_Dove;
    mMap[ReliveTypes::eRockSack] = &Factory::Factory_RockSack;
    mMap[ReliveTypes::eZBall] = &Factory::Factory_ZBall;
    mMap[ReliveTypes::eFallingItem] = &Factory::Factory_FallingItem;
    mMap[ReliveTypes::ePullRingRope] = &Factory::Factory_PullRingRope;
    mMap[ReliveTypes::eBackgroundAnimation] = &Factory::Factory_BackgroundAnimation;
    mMap[ReliveTypes::eHoney] = &Factory::Factory_Honey;
    mMap[ReliveTypes::eTimedMine] = &Factory::Factory_TimedMine;
    mMap[ReliveTypes::eSlig] = &Factory::Factory_Slig;
    mMap[ReliveTypes::eSlog] = &Factory::Factory_Slog;
    mMap[ReliveTypes::eLever] = &Factory::Factory_Lever;
    mMap[ReliveTypes::eBellHammer] = &Factory::Factory_BellHammer;
    mMap[ReliveTypes::eSecurityOrb] = &Factory::Factory_SecurityOrb;
    mMap[ReliveTypes::eLiftMudokon] = &Factory::Factory_LiftMudokon;
    mMap[ReliveTypes::eBeeSwarmHole] = &Factory::Factory_BeeSwarmHole;
    mMap[ReliveTypes::eHoneySack] = &Factory::Factory_HoneySack;
    mMap[ReliveTypes::eAbeStart] = &Factory::Factory_AbeStart;
    mMap[ReliveTypes::eElumWall] = &Factory::Factory_ElumWall;
    mMap[ReliveTypes::eSlingMud] = &Factory::Factory_SlingMud;
    mMap[ReliveTypes::eBeeNest] = &Factory::Factory_BeeNest;
    mMap[ReliveTypes::eMine] = &Factory::Factory_Mine;
    mMap[ReliveTypes::eUXB] = &Factory::Factory_Uxb;
    mMap[ReliveTypes::eParamite] = &Factory::Factory_Paramite;
    mMap[ReliveTypes::eBat] = &Factory::Factory_Bat;
    mMap[ReliveTypes::eRingMudokon] = &Factory::Factory_RingMudokon;
    mMap[ReliveTypes::eBirdPortal] = &Factory::Factory_BirdPortal;
    mMap[ReliveTypes::eBellSongStone] = &Factory::Factory_BellSongStone;
    mMap[ReliveTypes::eTrapDoor] = &Factory::Factory_TrapDoor;
    mMap[ReliveTypes::eRollingBall] = &Factory::Factory_RollingBall;
    mMap[ReliveTypes::eSligBoundLeft] = &Factory::Factory_SligBoundLeft;
    mMap[ReliveTypes::eRollingBallStopper] = &Factory::Factory_RollingBallStopper;
    mMap[ReliveTypes::eFootSwitch] = &Factory::Factory_FootSwitch;
    mMap[ReliveTypes::eSecurityClaw] = &Factory::Factory_SecurityClaw;
    mMap[ReliveTypes::eMotionDetector] = &Factory::Factory_MotionDetector;
    mMap[ReliveTypes::eSligSpawner] = &Factory::Factory_SligSpawner;
    mMap[ReliveTypes::eElectricWall] = &Factory::Factory_ElectricWall;
    mMap[ReliveTypes::eLiftMover] = &Factory::Factory_LiftMover;
    mMap[ReliveTypes::eChimeLock] = &Factory::Factory_ChimeLock;
    mMap[ReliveTypes::eElum] = &Factory::Factory_Elum;
    mMap[ReliveTypes::eMeatSack] = &Factory::Factory_MeatSack;
    mMap[ReliveTypes::eScrab] = &Factory::Factory_Scrab;
    mMap[ReliveTypes::eFlintLockFire] = &Factory::Factory_FlintLockFire;
    mMap[ReliveTypes::eSligBoundRight] = &Factory::Factory_SligBoundRight;
    mMap[ReliveTypes::eInvisibleSwitch] = &Factory::Factory_InvisibleSwitch;
    mMap[ReliveTypes::eMudokon] = &Factory::Factory_WorkerMudokon;
    mMap[ReliveTypes::eDoorFlame] = &Factory::Factory_DoorFlame;
    mMap[ReliveTypes::eMovingBomb] = &Factory::Factory_MovingBomb;
    mMap[ReliveTypes::eMeatSaw] = &Factory::Factory_MeatSaw;
    mMap[ReliveTypes::eMainMenuController] = &Factory::Factory_MainMenuController;
    mMap[ReliveTypes::eHintFly] = &Factory::Factory_HintFly;
    mMap[ReliveTypes::eTimerTrigger] = &Factory::Factory_TimerTrigger;
    mMap[ReliveTypes::eSecurityDoor] = &Factory::Factory_SecurityDoor;
    mMap[ReliveTypes::eBoomMachine] = &Factory::Factory_BoomMachine;
    mMap[ReliveTypes::eLCDScreen] = &Factory::Factory_LCDScreen;
    mMap[ReliveTypes::eHandStone] = &Factory::Factory_HandStone;
    mMap[ReliveTypes::eCreditsController] = &Factory::Factory_CreditsController;
    mMap[ReliveTypes::eLCDStatusBoard] = &Factory::Factory_LCDStatusBoard;
    // mMap[ReliveTypes2::eSwitchStateBooleanLogic] = &Factory::Factory_SwitchStateBooleanLogic; // unused object not implemented yet
    mMap[ReliveTypes::eMusicTrigger] = &Factory::Factory_MusicTrigger;
    mMap[ReliveTypes::eLightEffect] = &Factory::Factory_LightEffect;
    mMap[ReliveTypes::eSlogSpawner] = &Factory::Factory_SlogSpawner;
    mMap[ReliveTypes::eGasCountdown] = &Factory::Factory_GasCountdown;
    mMap[ReliveTypes::eRingCancel] = &Factory::Factory_RingCancel;
    mMap[ReliveTypes::eGasEmitter] = &Factory::Factory_GasEmitter;
    mMap[ReliveTypes::eZzzSpawner] = &Factory::Factory_ZzzSpawner;
    mMap[ReliveTypes::eBackgroundGlukkon] = &Factory::Factory_BackgroundGlukkon;
    mMap[ReliveTypes::eKillUnsavedMuds] = &Factory::Factory_KillUnsavedMuds;
}

void Factory::ConstructTLVObject(relive::Path_TLV* pTlv, Map* pMap, const Guid& tlvInfo, LoadMode loadMode)
{
    auto it = mMap.find(pTlv->mTlvType);

    if (it != std::end(mMap))
    {
        TFactoryFunction fn = it->second;
        (this->*fn)(pTlv, pMap, tlvInfo, loadMode);
    }
}

} // namespace AO
