#include "stdafx.h"
#include "Factory.hpp"
#include "../relive_lib/Function.hpp"
#include "MainMenu.hpp"
#include "Map.hpp"
#include "LCDScreen.hpp"
#include "UXB.hpp"
#include "Mine.hpp"
#include "TimedMine.hpp"
#include "LCDStatusBoard.hpp"
#include "BackgroundAnimation.hpp"
#include "HoistRocksEffect.hpp"
#include "Alarm.hpp"
#include "Door.hpp"
#include "WorkWheel.hpp"
#include "StatusLight.hpp"
#include "WheelSyncer.hpp"
#include "LevelLoader.hpp"
#include "InvisibleSwitch.hpp"
#include "Lever.hpp"
#include "MultiSwitchController.hpp"
#include "../relive_lib/GameObjects/ShadowZone.hpp"
#include "Drill.hpp"
#include "Teleporter.hpp"
#include "Well.hpp"
#include "Water.hpp"
#include "SlamDoor.hpp"
#include "MusicTrigger.hpp"
#include "PauseMenu.hpp"
#include "Abe.hpp"
#include "LiftPoint.hpp"
#include "PullRingRope.hpp"
#include "LiftMover.hpp"
#include "TrapDoor.hpp"
#include "TimerTrigger.hpp"
#include "CreditsController.hpp"
#include "FootSwitch.hpp"
#include "BrewMachine.hpp"
#include "FallingItem.hpp"
#include "MineCar.hpp"
#include "ElectricWall.hpp"
#include "GasEmitter.hpp"
#include "DemoPlayback.hpp"
#include "SecurityOrb.hpp"
#include "Greeter.hpp"
#include "MotionDetector.hpp"
#include "FlyingSlig.hpp"
#include "FlyingSligSpawner.hpp"
#include "Mudokon.hpp"
#include "BirdPortal.hpp"
#include "TorturedMudokon.hpp"
#include "Dove.hpp"
#include "DoorBlocker.hpp"
#include "SlapLock.hpp"
#include "Glukkon.hpp"
#include "MovingBomb.hpp"
#include "Slurg.hpp"
#include "DoorFlame.hpp"
#include "CrawlingSlig.hpp"
#include "Scrab.hpp"
#include "Paramite.hpp"
#include "Fleech.hpp"
#include "Slog.hpp"
#include "Slig.hpp"
#include "GasCountDown.hpp"
#include "GlukkonSwitch.hpp"
#include "CrawlingSligButton.hpp"
#include "SligGetPantsAndWings.hpp"
#include "BoomMachine.hpp"
#include "Meat.hpp"
#include "Bone.hpp"
#include "RockSack.hpp"
#include "SligSpawner.hpp"
#include "ScrabSpawner.hpp"
#include "SlogSpawner.hpp"
#include "ZzzSpawner.hpp"
#include "ParamiteWebLine.hpp"
#include "ExplosionSet.hpp"
#include "ColourfulMeter.hpp"
#include "SecurityDoor.hpp"
#include "LaughingGas.hpp"
#include "ResourceManager.hpp"
#include "Game.hpp"
#include "MeatSack.hpp"
#include "BoneBag.hpp"

static constexpr AnimId kAbeGibs[3] = {
    AnimId::Abe_Head_Gib,
    AnimId::Abe_Arm_Gib,
    AnimId::Abe_Body_Gib};

static constexpr AnimId kSlogGibs[2] = {
    AnimId::Slog_Head_Gib,
    AnimId::Slog_Body_Gib};

static constexpr AnimId kSligGibs[3] = {
    AnimId::Slig_Head_Gib,
    AnimId::Slig_Arm_Gib,
    AnimId::Slig_Body_Gib};

void Factory::Factory_MainMenuController(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode)
{
    if (sMainMenuObjectCounter_BB4400 == 0)
    {
        if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
        {
            for (const auto& info : MainMenuController::sMainMenuFrameTable_561CC8)
            {
                if (info.field_0_animation != AnimId::None)
                {
                    ResourceManagerWrapper::PendAnimation(info.field_0_animation);
                }
            }
            ResourceManagerWrapper::PendAnims(MainMenuController::kMenuAnims);

            // Originally loaded in the PauseMenu::Init()
            ResourceManagerWrapper::PendAnimation(AnimId::NormalMudIcon);
            ResourceManagerWrapper::PendAnimation(AnimId::AngryMudIcon);
            ResourceManagerWrapper::PendAnimation(AnimId::HappyMudIcon);

            // Originally loaded in Game_Init_LoadingIcon()
            ResourceManagerWrapper::PendAnimation(AnimId::Loading_Icon2);
        }
        else
        {
            relive_new MainMenuController(pTlv, tlvId);
        }
    }
}

void Factory::Factory_Hoist(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode)
{
    relive::Path_Hoist* pHoistTlv = static_cast<relive::Path_Hoist*>(pTlv);
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::HoistRock1);
        ResourceManagerWrapper::PendAnimation(AnimId::HoistRock2);
        ResourceManagerWrapper::PendAnimation(AnimId::HoistRock3);
    }
    else if (pHoistTlv->mHoistType == relive::Path_Hoist::Type::eOffScreen)
    {
        // Its an off screen hoist so create the falling rocks effect
        relive_new HoistRocksEffect(pHoistTlv, tlvId);
    }
    else
    {
        Path::TLV_Reset(tlvId, -1, 0, 0);
    }
}

void Factory::Factory_Edge(relive::Path_TLV* /*pTlv*/, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        // Empty
    }
    else
    {
        Path::TLV_Reset(tlvId, -1, 0, 0);
    }
}

void Factory::Factory_Door(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eNecrum:
            case EReliveLevelIds::eMudomoVault:
            case EReliveLevelIds::eMudancheeVault:
            case EReliveLevelIds::eMudancheeVault_Ender:
            case EReliveLevelIds::eMudomoVault_Ender:
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Temple_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Temple_Open);
                break;

            case EReliveLevelIds::eFeeCoDepot:
            case EReliveLevelIds::eFeeCoDepot_Ender:
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Feeco_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Feeco_Open);
                break;

            case EReliveLevelIds::eBarracks:
            case EReliveLevelIds::eBarracks_Ender:
                if (gMap.mOverlayId == 108)
                {
                    ResourceManagerWrapper::PendAnimation(AnimId::Door_BarracksMetal_Closed);
                    ResourceManagerWrapper::PendAnimation(AnimId::Door_BarracksMetal_Open);
                }
                else
                {
                    ResourceManagerWrapper::PendAnimation(AnimId::Door_Barracks_Closed);
                    ResourceManagerWrapper::PendAnimation(AnimId::Door_Barracks_Open);
                }
                break;

            case EReliveLevelIds::eBonewerkz:
            case EReliveLevelIds::eBonewerkz_Ender:
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Bonewerkz_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Bonewerkz_Open);
                break;

            case EReliveLevelIds::eBrewery:
            case EReliveLevelIds::eBrewery_Ender:
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Brewery_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Brewery_Open);
                break;

            default:
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Mines_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::Door_Mines_Open);
                break;
        }
    }
    else
    {
        relive_new Door(static_cast<relive::Path_Door*>(pTlv), tlvId);
    }
}

void Factory::Factory_ShadowZone(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode != LoadMode::LoadResourceFromList_1 && loadmode != LoadMode::LoadResource_2)
    {
        relive_new ShadowZone(static_cast<relive::Path_ShadowZone*>(pTlv), tlvId);
    }
}

void Factory::Factory_LiftPoint(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::AE_Rope);
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eNecrum:
            case EReliveLevelIds::eMudomoVault:
            case EReliveLevelIds::eMudomoVault_Ender:
            case EReliveLevelIds::eMudancheeVault:
            case EReliveLevelIds::eMudancheeVault_Ender:
                ResourceManagerWrapper::PendAnimation(AnimId::LiftPlatform_Necrum);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftBottomWheel_Necrum);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftTopWheel_Necrum);
                break;

            case EReliveLevelIds::eFeeCoDepot:
            case EReliveLevelIds::eFeeCoDepot_Ender:
            case EReliveLevelIds::eBarracks:
            case EReliveLevelIds::eBarracks_Ender:
            case EReliveLevelIds::eBonewerkz:
            case EReliveLevelIds::eBonewerkz_Ender:
            case EReliveLevelIds::eBrewery:
            case EReliveLevelIds::eBrewery_Ender:
                ResourceManagerWrapper::PendAnimation(AnimId::LiftPlatform_Mines);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftBottomWheel_Mines);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftTopWheel_Mines);
                break;

            default:
                ResourceManagerWrapper::PendAnimation(AnimId::LiftPlatform_Mines);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftBottomWheel_Mines);
                ResourceManagerWrapper::PendAnimation(AnimId::LiftTopWheel_Mines);
                break;
        }
    }
    else
    {
        relive::Path_LiftPoint* pLiftTlv = static_cast<relive::Path_LiftPoint*>(pTlv);
        for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
        {
            BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
            if (!pObj)
            {
                break;
            }

            if (!(pObj->GetDead()) && pObj->Type() == ReliveTypes::eLiftPoint)
            {
                // Is there already an existing LiftPoint object for this TLV?
                LiftPoint* pLiftPoint = static_cast<LiftPoint*>(pObj);
                const s16 xpos = FP_GetExponent(pLiftPoint->mXPos);
                if (pTlv->mTopLeftX <= xpos && xpos <= pTlv->mBottomRightX && pLiftPoint->mLiftPointId == pLiftTlv->mLiftPointId && pLiftPoint->mCurrentLevel == gMap.mCurrentLevel && pLiftPoint->mCurrentPath == gMap.mCurrentPath)
                {
                    // Yes so just reset its data
                    Path::TLV_Reset(tlvId, -1, 0, 0);
                    return;
                }
            }
        }

        // TODO: Meaning of the data in mTlvSpecificMeaning for lift point
        if (pLiftTlv->mTlvSpecificMeaning & 2 || (pLiftTlv->mTlvSpecificMeaning == 0 && pLiftTlv->mIsStartPoint == relive::reliveChoice::eYes))
        {
            relive_new LiftPoint(pLiftTlv, tlvId);
            return;
        }
        else
        {
            // Find out where to create the lift point
            s16 pointNumber = 1;
            while (pointNumber < 8)
            {
                relive::Path_TLV* pTlvIter = gPathInfo->Get_First_TLV_For_Offsetted_Camera(
                    0,
                    pointNumber / 2 * (pointNumber % 2 != 0 ? -1 : 1));

                while (pTlvIter)
                {
                    if (pTlvIter->mTlvType == ReliveTypes::eLiftPoint)
                    {
                        auto pLiftPointIter = static_cast<relive::Path_LiftPoint*>(pTlvIter);

                        const s32 tlvX = pTlv->mTopLeftX;
                        const s32 absX = pTlvIter->mTopLeftX - tlvX >= 0 ? pTlvIter->mTopLeftX - tlvX : tlvX - pTlvIter->mTopLeftX;

                        if (absX < 5 && pLiftPointIter->mLiftPointId == pLiftTlv->mLiftPointId && (pLiftPointIter->mTlvSpecificMeaning & 2 || pLiftPointIter->mTlvSpecificMeaning == 0) && pLiftPointIter->mIsStartPoint == relive::reliveChoice::eYes)
                        {
                            relive_new LiftPoint(pLiftPointIter, tlvId);
                            return;
                        }
                    }

                    pTlvIter = Path::Next_TLV(pTlvIter);
                }
                pointNumber++;
            }

            // Default to original
            relive_new LiftPoint(pLiftTlv, tlvId);
        }
    }
}

void Factory::Factory_Well(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Well_Leaf);
    }
    else
    {
        relive::Path_WellBase* pWellTlv = static_cast<relive::Path_WellBase*>(pTlv);
        const FP xpos = FP_FromInteger(pWellTlv->mTopLeftX);
        const FP ypos = FP_FromInteger(pWellTlv->mTopLeftY + 5);
        relive_new Well(pWellTlv, xpos, ypos, tlvId);
    }
}

void Factory::Factory_Dove(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
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

            s16 ypos = 0;
            if (pDoveTlv->mPixelPerfect == relive::reliveChoice::eYes)
            {
                pDove->mXPos = FP_FromInteger(pTlv->mTopLeftX);
                ypos = pTlv->mTopLeftY;
            }
            else
            {
                pDove->mXPos = FP_FromInteger(pTlv->mTopLeftX + width * Math_NextRandom() / 256);
                ypos = pTlv->mTopLeftY + height * Math_NextRandom() / 256;
            }
            pDove->mYPos = FP_FromInteger(ypos) + FP_FromInteger(10);
        }
    }
}

void Factory::Factory_RockSack(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Rock);
        ResourceManagerWrapper::PendAnimation(AnimId::RockSack_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::RockSack_SoftHit);
        ResourceManagerWrapper::PendAnimation(AnimId::RockSack_HardHit);
    }
    else
    {
        relive_new RockSack(static_cast<relive::Path_RockSack*>(pTlv), tlvId);
    }
}

void Factory::Factory_FallingItem(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Explosion_Sticks);
        ResourceManagerWrapper::PendAnimation(AnimId::ObjectShadow);
        ResourceManagerWrapper::PendAnimation(AnimId::Explosion_Rocks);
        if (gMap.mCurrentLevel == EReliveLevelIds::eBonewerkz)
        {
            ResourceManagerWrapper::PendAnimation(AnimId::FallingCrate_Falling);
            ResourceManagerWrapper::PendAnimation(AnimId::FallingCrate_Waiting);
            ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion);
        }
        else
        {
            ResourceManagerWrapper::PendAnimation(AnimId::AE_FallingRock_Falling);
            ResourceManagerWrapper::PendAnimation(AnimId::AE_FallingRock_Waiting);
        }
    }
    else
    {
        relive_new FallingItem(static_cast<relive::Path_FallingItem*>(pTlv), tlvId);
    }
}

void Factory::Factory_PullRingRope(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::AE_Rope);
        ResourceManagerWrapper::PendAnimation(AnimId::PullRingRope_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::PullRingRope_UseBegin);
        ResourceManagerWrapper::PendAnimation(AnimId::PullRingRope_UseEnd);
    }
    else
    {
        relive_new PullRingRope(static_cast<relive::Path_PullRingRope*>(pTlv), tlvId);
    }
}

void Factory::Factory_TimedMine(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode)
{
    auto mine_tlv = static_cast<relive::Path_TimedMine*>(pTlv);

    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::TimedMine_Activated);
        ResourceManagerWrapper::PendAnimation(AnimId::TimedMine_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::Bomb_Flash);
        ResourceManagerWrapper::PendAnimation(AnimId::Bomb_RedGreenTick);
        ResourceManagerWrapper::PendAnimation(AnimId::Explosion_Rocks);
        ResourceManagerWrapper::PendAnimation(AnimId::GroundExplosion);
    }
    else
    {
        relive_new TimedMine(mine_tlv, tlvId);
    }
}

static void LoadWalkingSligResources()
{
    ResourceManagerWrapper::PendAnims(Slig::sSligAnimIdTable);
    ResourceManagerWrapper::PendAnimation(AnimId::ShootingZFire_Particle);
    ResourceManagerWrapper::PendAnimation(AnimId::ShootingFire_Particle);
    ResourceManagerWrapper::PendAnimation(AnimId::Bullet_Shell);
    ResourceManagerWrapper::PendAnims(kSligGibs);
    ResourceManagerWrapper::PendAnimation(AnimId::ObjectShadow);
}

void Factory::Factory_Slig(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    auto pSligTlv = static_cast<relive::Path_Slig*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        LoadWalkingSligResources();
    }
    else
    {
        relive_new Slig(pSligTlv, tlvId);
    }
}

static void LoadSlogResources()
{
    ResourceManagerWrapper::PendAnims(Slog::sSlogAnimIdTable);
}

void Factory::Factory_Slog(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        LoadSlogResources();
    }
    else
    {
        relive_new Slog(static_cast<relive::Path_Slog*>(pTlv), tlvId);
    }
}

void Factory::Factory_Lever(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Lever_Pull_Release_Left);
        ResourceManagerWrapper::PendAnimation(AnimId::Lever_Pull_Release_Right);
        ResourceManagerWrapper::PendAnimation(AnimId::Lever_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::Lever_Pull_Left);
        ResourceManagerWrapper::PendAnimation(AnimId::Lever_Pull_Right);
    }
    else
    {
        relive_new Lever(static_cast<relive::Path_Lever*>(pTlv), tlvId);
    }
}

void Factory::Factory_SecurityOrb(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    relive::Path_SecurityOrb* pSecurityOrbTlv = static_cast<relive::Path_SecurityOrb*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Security_Orb);
        ResourceManagerWrapper::PendAnimation(AnimId::Zap_Line_Blue);
        ResourceManagerWrapper::PendAnimation(AnimId::Zap_Line_Red);
        ResourceManagerWrapper::PendAnimation(AnimId::AE_ZapSpark);
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::Metal_Gib);
        ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion);
    }
    else
    {
        relive_new SecurityOrb(pSecurityOrbTlv, tlvId);
    }
}

void Factory::Factory_AbeStart(relive::Path_TLV* pTlv, Path*, const Guid& /*tlvId*/, LoadMode loadmode)
{
    if (loadmode != LoadMode::LoadResourceFromList_1 && loadmode != LoadMode::LoadResource_2 && !gAttract)
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
}

void Factory::Factory_Mine(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode)
{
    auto mine_tlv = static_cast<relive::Path_Mine*>(pTlv);

    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::Mine);
        ResourceManagerWrapper::PendAnimation(AnimId::Mine_Flash);
        ResourceManagerWrapper::PendAnimation(AnimId::Explosion_Rocks);
        ResourceManagerWrapper::PendAnimation(AnimId::GroundExplosion);
    }
    else
    {
        relive_new Mine(mine_tlv, tlvId);
    }
}

void Factory::Factory_UXB(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadMode)
{
    auto uxb_tlv = static_cast<relive::Path_UXB*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::UXB_Active);
        ResourceManagerWrapper::PendAnimation(AnimId::UXB_Toggle);
        ResourceManagerWrapper::PendAnimation(AnimId::UXB_Disabled);
        ResourceManagerWrapper::PendAnimation(AnimId::Bomb_Flash);
        ResourceManagerWrapper::PendAnimation(AnimId::Bomb_RedGreenTick);
        ResourceManagerWrapper::PendAnimation(AnimId::Explosion_Rocks);
        ResourceManagerWrapper::PendAnimation(AnimId::GroundExplosion);
    }
    else
    {
        relive_new UXB(uxb_tlv, tlvId);
    }
}

void Factory::Factory_Paramite(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Paramite::sParamiteMotionAnimIds);
        ResourceManagerWrapper::PendAnimation(AnimId::ParamiteWeb);
    }
    else
    {
        relive_new Paramite(static_cast<relive::Path_Paramite*>(pTlv), tlvId);
    }
}

void Factory::Factory_MovieHandStone(relive::Path_TLV*, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        // Empty
    }
    else
    {
        Path::TLV_Reset(tlvId, -1, 0, 0);
    }
}

void Factory::Factory_BirdPortal(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    auto pBirdPortalTlv = static_cast<relive::Path_BirdPortal*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::BirdPortal_TerminatorShrink);
        ResourceManagerWrapper::PendAnimation(AnimId::BirdPortal_TerminatorIdle);
        ResourceManagerWrapper::PendAnimation(AnimId::BirdPortal_TerminatorGrow);
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
    else if (SwitchStates_Get(pBirdPortalTlv->mCreatePortalSwitchId))
    {
        relive_new BirdPortal(pBirdPortalTlv, tlvId);
    }
    else
    {
        Path::TLV_Reset(tlvId, -1, 0, 0);
    }
}

void Factory::Factory_TrapDoor(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eMudomoVault:
            case EReliveLevelIds::eMudancheeVault:
            case EReliveLevelIds::eMudancheeVault_Ender:
            case EReliveLevelIds::eMudomoVault_Ender:
                ResourceManagerWrapper::PendAnimation(AnimId::Trap_Door_Tribal_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::Trap_Door_Tribal_Closing);
                ResourceManagerWrapper::PendAnimation(AnimId::Trap_Door_Tribal_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::Trap_Door_Tribal_Opening);
                break;

            default:
                ResourceManagerWrapper::PendAnimation(AnimId::Trap_Door_Open);
                ResourceManagerWrapper::PendAnimation(AnimId::Trap_Door_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::Trap_Door_Closing);
                ResourceManagerWrapper::PendAnimation(AnimId::Trap_Door_Opening);
                break;
        }
    }
    else
    {
        relive_new TrapDoor(static_cast<relive::Path_TrapDoor*>(pTlv), tlvId);
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
        pTlvIter = Path::Next_TLV(pTlvIter);
    }
    return nullptr;
}

void Factory::Factory_SligBoundLeft(relive::Path_TLV* pTlv, Path*, const Guid& /*tlvId*/, LoadMode loadMode)
{
    auto pBound = static_cast<relive::Path_SligBound*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        LoadWalkingSligResources();
    }
    else
    {
        pBound->mTlvFlags.Clear(relive::TlvFlags::eBit1_Created);
        pBound->mTlvFlags.Clear(relive::TlvFlags::eBit2_Destroyed);

        for (s16 camX_idx = -2; camX_idx < 3; camX_idx++)
        {
            relive::Path_TLV* pTlvIter = gPathInfo->Get_First_TLV_For_Offsetted_Camera(camX_idx, 0);
            pTlvIter = FindMatchingSligTLV(pTlvIter, pBound);
            if (pTlvIter)
            {
                pTlvIter->mTlvFlags.Set(relive::TlvFlags::eBit1_Created);
                pTlvIter->mTlvFlags.Set(relive::TlvFlags::eBit2_Destroyed);

                relive_new Slig(static_cast<relive::Path_Slig*>(pTlvIter), pTlvIter->mId); // id of the slig to spawn at the bound, not the bound itself

                return;
            }
        }
    }
}

void Factory::Factory_FootSwitch(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eMudomoVault:
            case EReliveLevelIds::eMudancheeVault:
            case EReliveLevelIds::eMudancheeVault_Ender:
            case EReliveLevelIds::eMudomoVault_Ender:
                ResourceManagerWrapper::PendAnimation(AnimId::Foot_Switch_Vault_Idle);
                ResourceManagerWrapper::PendAnimation(AnimId::Foot_Switch_Vault_Pressed);
                break;
            case EReliveLevelIds::eBonewerkz:
                ResourceManagerWrapper::PendAnimation(AnimId::Foot_Switch_Bonewerkz_Idle);
                ResourceManagerWrapper::PendAnimation(AnimId::Foot_Switch_Bonewerkz_Pressed);
                break;
            default:
                ResourceManagerWrapper::PendAnimation(AnimId::Foot_Switch_Industrial_Idle);
                ResourceManagerWrapper::PendAnimation(AnimId::Foot_Switch_Industrial_Pressed);
                break;
        }
    }
    else
    {
        relive_new FootSwitch(static_cast<relive::Path_FootSwitch*>(pTlv), tlvId);
    }
}

void Factory::Factory_SecurityClaw(relive::Path_TLV* pTlv, Path* pPath, const Guid& tlvId, LoadMode loadMode)
{
    // TODO: Most of the code for the chant suppressor with arms is still in the game
    // check if it can be re-added at some point.
    Factory_SecurityOrb(pTlv, pPath, tlvId, loadMode);
}

void Factory::Factory_MotionDetector(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new MotionDetector(static_cast<relive::Path_MotionDetector*>(pTlv), tlvId, nullptr);
    }
    else
    {
        ResourceManagerWrapper::PendAnimation(AnimId::MotionDetector_Flare);
        ResourceManagerWrapper::PendAnimation(AnimId::MotionDetector_Laser);
    }
}

void Factory::Factory_SligSpawner(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    auto pSligTlv = static_cast<relive::Path_Slig*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        LoadWalkingSligResources();
    }
    else
    {
        relive_new SligSpawner(pSligTlv, tlvId);
    }
}

void Factory::Factory_ElectricWall(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Electric_Wall);
    }
    else
    {
        relive_new ElectricWall(static_cast<relive::Path_ElectricWall*>(pTlv), tlvId);
    }
}

void Factory::Factory_LiftMover(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode != LoadMode::LoadResourceFromList_1 && loadmode != LoadMode::LoadResource_2)
    {
        relive_new LiftMover(static_cast<relive::Path_LiftMover*>(pTlv), tlvId);
    }
}

void Factory::Factory_MeatSack(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
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

void Factory::Factory_Scrab(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Scrab::sScrabMotionAnimIds);
    }
    else
    {
        relive_new Scrab(static_cast<relive::Path_Scrab*>(pTlv), tlvId, relive::Path_ScrabSpawner::SpawnDirection::eNone);
    }
}

void Factory::Factory_SligBoundRight(relive::Path_TLV* pTlv, Path* pPath, const Guid& tlvId, LoadMode loadMode)
{
    Factory_SligBoundLeft(pTlv, pPath, tlvId, loadMode);
}

void Factory::Factory_InvisibleSwitch(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new InvisibleSwitch(static_cast<relive::Path_InvisibleSwitch*>(pTlv), tlvId);
    }
}

void Factory::Factory_Mudokon(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    auto pMudTlv = static_cast<relive::Path_Mudokon*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Mudokon::kMudMotionAnimIds);
        ResourceManagerWrapper::PendAnimation(AnimId::ObjectShadow);
    }
    else
    {
        relive_new Mudokon(pMudTlv, tlvId);
    }
}

void Factory::Factory_DoorFlame(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
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

void Factory::Factory_MovingBomb(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    auto pMovingBombTlv = static_cast<relive::Path_MovingBomb*>(pTlv);
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::MovingBomb);
        ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion);
        ResourceManagerWrapper::PendAnimation(AnimId::Metal_Gib);
        ResourceManagerWrapper::PendAnims(kAbeGibs);
    }
    else
    {
        relive_new MovingBomb(pMovingBombTlv, tlvId);
    }
}

void Factory::Factory_TimerTrigger(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::ConstructObject_0)
    {
        relive_new TimerTrigger(static_cast<relive::Path_TimerTrigger*>(pTlv), tlvId);
    }
}

void Factory::Factory_SecurityDoor(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
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

void Factory::Factory_BoomMachine(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    auto pTlvBooMachine = static_cast<relive::Path_BoomMachine*>(pTlv);
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
    }
    else
    {
        relive_new BoomMachine(pTlvBooMachine, tlvId);
    }
}

void Factory::Factory_BackgroundAnimation(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode != LoadMode::LoadResourceFromList_1 && loadmode != LoadMode::LoadResource_2)
    {
        relive_new BackgroundAnimation(static_cast<relive::Path_BackgroundAnimation*>(pTlv), tlvId);
    }
}

void Factory::Factory_LCDScreen(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        // Map::LoadResource("LCDFONT.FNT", ResourceManager::ResourceType::Resource_Font, 2, loadmode); // TODO: Add to resource ID enum
        return;
    }

    relive_new LCDScreen(static_cast<relive::Path_LCDScreen*>(pTlv), tlvId);
}

void Factory::Factory_HandStone(relive::Path_TLV*, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::SpotLight);
    }
    else
    {
        Path::TLV_Reset(tlvId, -1, 0, 0);
    }
}

void Factory::Factory_CreditsController(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode != LoadMode::LoadResourceFromList_1 && loadmode != LoadMode::LoadResource_2 && !gCreditsControllerExists)
    {
        relive_new CreditsController(pTlv, tlvId);
    }
}

void Factory::Factory_LCDStatusBoard(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        // Map::LoadResource("LCDFONT.FNT", ResourceManager::ResourceType::Resource_Font, AEResourceID::kLcdfontResID, loadmode);
        return;
    }

    relive_new LCDStatusBoard(static_cast<relive::Path_LCDStatusBoard*>(pTlv), tlvId);
}

void Factory::Factory_WheelSyncer(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode != LoadMode::LoadResourceFromList_1 && loadmode != LoadMode::LoadResource_2)
    {
        relive_new WheelSyncer(static_cast<relive::Path_WheelSyncer*>(pTlv), tlvId);
    }
}

void Factory::Factory_MusicTrigger(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode != LoadMode::LoadResourceFromList_1 && loadmode != LoadMode::LoadResource_2)
    {
        relive_new MusicTrigger(static_cast<relive::Path_MusicTrigger*>(pTlv), tlvId);
    }
}

void Factory::Factory_SlogSpawner(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        LoadSlogResources();
    }
    else
    {
        relive_new SlogSpawner(static_cast<relive::Path_SlogSpawner*>(pTlv), tlvId);
    }
}

void Factory::Factory_GasCountdown(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        // gMap.LoadResource("LCDFONT.FNT", ResourceManager::Resource_Font, AEResourceID::kLcdfontResID, loadMode);
        // gMap.LoadResource("ABEGAS.BAN", ResourceManager::Resource_Animation, AEResourceID::kAbegasResID, loadMode);
    }
    else
    {
        relive_new GasCountDown(static_cast<relive::Path_GasCountDown*>(pTlv), tlvId);
    }
}

void Factory::Factory_GasEmitter(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new GasEmitter(static_cast<relive::Path_GasEmitter*>(pTlv), tlvId);
    }
}

void Factory::Factory_ZzzSpawner(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        relive_new ZzzSpawner(static_cast<relive::Path_ZzzSpawner*>(pTlv), tlvId);
    }
}

void Factory::Factory_Glukkon(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eFeeCoDepot:
            case EReliveLevelIds::eFeeCoDepot_Ender:
                for (s32 i = 0; i < 25; i++)
                {
                    const auto& anim = Glukkon::sGlukkonsAnimIdTable[1][i];
                    ResourceManagerWrapper::PendAnimation(anim);
                }
                ResourceManagerWrapper::PendAnimation(AnimId::Aslik_Head_Gib);
                ResourceManagerWrapper::PendAnimation(AnimId::Aslik_Arm_Gib);
                ResourceManagerWrapper::PendAnimation(AnimId::Aslik_Body_Gib);
                break;

            case EReliveLevelIds::eBarracks:
            case EReliveLevelIds::eBarracks_Ender:
                for (s32 i = 0; i < 25; i++)
                {
                    const auto& anim = Glukkon::sGlukkonsAnimIdTable[2][i];
                    ResourceManagerWrapper::PendAnimation(anim);
                }
                ResourceManagerWrapper::PendAnimation(AnimId::Dripik_Head_Gib);
                ResourceManagerWrapper::PendAnimation(AnimId::Dripik_Arm_Gib);
                ResourceManagerWrapper::PendAnimation(AnimId::Dripik_Body_Gib);
                break;

            case EReliveLevelIds::eBonewerkz:
            case EReliveLevelIds::eBonewerkz_Ender:
                for (s32 i = 0; i < 25; i++)
                {
                    const auto& anim = Glukkon::sGlukkonsAnimIdTable[3][i];
                    ResourceManagerWrapper::PendAnimation(anim);
                }
                ResourceManagerWrapper::PendAnimation(AnimId::Phleg_Head_Gib);
                ResourceManagerWrapper::PendAnimation(AnimId::Phleg_Arm_Gib);
                ResourceManagerWrapper::PendAnimation(AnimId::Phleg_Body_Gib);
                break;

            default:
                for (s32 i = 0; i < 25; i++)
                {
                    const auto& anim = Glukkon::sGlukkonsAnimIdTable[0][i];
                    ResourceManagerWrapper::PendAnimation(anim);
                }
                ResourceManagerWrapper::PendAnimation(AnimId::Glukkon_Head_Gib);
                ResourceManagerWrapper::PendAnimation(AnimId::Glukkon_Arm_Gib);
                ResourceManagerWrapper::PendAnimation(AnimId::Glukkon_Body_Gib);
                break;
        }
    }
    else
    {
        relive_new Glukkon(static_cast<relive::Path_Glukkon*>(pTlv), tlvId);
    }
}

void Factory::Factory_Water(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::WaterDrop);
        ResourceManagerWrapper::PendAnimation(AnimId::WaterSplash);
    }
    else
    {
        relive_new Water(static_cast<relive::Path_Water*>(pTlv), tlvId);
    }
}

void Factory::Factory_WorkWheel(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Work_Wheel_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::Work_Wheel_Turning);
    }
    else
    {
        relive_new WorkWheel(static_cast<relive::Path_WorkWheel*>(pTlv), tlvId);
    }
}

static void Create_LaughingGas(Layer layer, relive::Path_TLV* pTlv, const Guid& tlvId)
{
    if (!gLaughingGasInstanceCount)
    {
        relive_new LaughingGas(layer, static_cast<relive::Path_LaughingGas*>(pTlv), tlvId);
    }
}

void Factory::Factory_LaughingGas(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        Create_LaughingGas(Layer::eLayer_Above_FG1_39, pTlv, tlvId);
    }
}

static void LoadFlyingSligResources()
{
    ResourceManagerWrapper::PendAnims(FlyingSlig::sFlyingSligAnimIdTable);
    ResourceManagerWrapper::PendAnims(kSligGibs);
    ResourceManagerWrapper::PendAnimation(AnimId::Grenade);
    ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion_Small);
    ResourceManagerWrapper::PendAnimation(AnimId::Metal_Gib);
    ResourceManagerWrapper::PendAnims(kAbeGibs);
    ResourceManagerWrapper::PendAnimation(AnimId::ShootingFire_Particle);
    ResourceManagerWrapper::PendAnimation(AnimId::Vaporize_Particle);
    ResourceManagerWrapper::PendAnims(kSlogGibs);
}

void Factory::Factory_FlyingSlig(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        LoadFlyingSligResources();
    }
    else
    {
        relive_new FlyingSlig(static_cast<relive::Path_FlyingSlig*>(pTlv), tlvId);
    }
}

void Factory::Factory_Fleech(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Fleech::sFleechAnimFromMotion);
        ResourceManagerWrapper::PendAnimation(AnimId::Fleech_Head_Gib);
        ResourceManagerWrapper::PendAnimation(AnimId::Fleech_Body_Gib);
    }
    else if (gMap.mCurrentLevel != EReliveLevelIds::eMudancheeVault_Ender || gMap.mCurrentPath != 9 || gMap.mCurrentCamera != 4)
    {
        relive_new Fleech(static_cast<relive::Path_Fleech*>(pTlv), tlvId);
    }
}

void Factory::Factory_Slurg(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Slurg_Move);
        ResourceManagerWrapper::PendAnimation(AnimId::Slurg_Burst);
        ResourceManagerWrapper::PendAnimation(AnimId::Slurg_Turn_Around);
    }
    else
    {
        relive_new Slurg(static_cast<relive::Path_Slurg*>(pTlv), tlvId);
    }
}

void Factory::Factory_SlamDoor(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        switch (gMap.mCurrentLevel)
        {
            case EReliveLevelIds::eNecrum:
            case EReliveLevelIds::eMudomoVault:
            case EReliveLevelIds::eMudancheeVault:
            case EReliveLevelIds::eMudancheeVault_Ender:
            case EReliveLevelIds::eMudomoVault_Ender:
                ResourceManagerWrapper::PendAnimation(AnimId::Slam_Door_Vault_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::Slam_Door_Vault_Closing);
                ResourceManagerWrapper::PendAnimation(AnimId::Slam_Door_Vault_Opening);
                break;
            default:
                ResourceManagerWrapper::PendAnimation(AnimId::Slam_Door_Industrial_Closed);
                ResourceManagerWrapper::PendAnimation(AnimId::Slam_Door_Industrial_Closing);
                ResourceManagerWrapper::PendAnimation(AnimId::Slam_Door_Industrial_Opening);
                break;
        }
    }
    else
    {
        relive_new SlamDoor(static_cast<relive::Path_SlamDoor*>(pTlv), tlvId);
    }
}

void Factory::Factory_LevelLoader(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode != LoadMode::LoadResourceFromList_1 && loadmode != LoadMode::LoadResource_2)
    {
        relive_new LevelLoader(static_cast<relive::Path_LevelLoader*>(pTlv), tlvId);
    }
}

void Factory::Factory_DemoSpawnPoint(relive::Path_TLV*, Path*, const Guid& /*tlvId*/, LoadMode loadMode)
{
    if (loadMode != LoadMode::LoadResourceFromList_1 && loadMode != LoadMode::LoadResource_2)
    {
        if (gAttract)
        {
            if (!gActiveDemoPlayback)
            {
                relive_new DemoPlayback();
            }
        }
    }
}

void Factory::Factory_Teleporter(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode != LoadMode::LoadResourceFromList_1 && loadmode != LoadMode::LoadResource_2)
    {
        relive_new Teleporter(static_cast<relive::Path_Teleporter*>(pTlv), tlvId);
    }
}

void Factory::Factory_SlurgSpawner(relive::Path_TLV* /*pTlv*/, Path*, const Guid& /*tlvId*/, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Slurg_Move);
        ResourceManagerWrapper::PendAnimation(AnimId::Slurg_Burst);
        ResourceManagerWrapper::PendAnimation(AnimId::Slurg_Turn_Around);
    }
    else
    {
        /*
        // TODO/HACK disabled because it crashes the game when a quick load is done
        // after you save when a slurg is spawned as it has no TLV.
        // Its only used to spawn 1 slurg in 1 screen of the game. Fix in abi_break
        // branch by converting to a normal slurg.
            relive_new SlurgSpawner(static_cast<relive::Path_SlurgSpawner*>(pTlv), tlvId);
            */
    }
}

void Factory::Factory_Drill(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Drill_Horizontal_Off);
        ResourceManagerWrapper::PendAnimation(AnimId::Drill_Horizontal_On);
        ResourceManagerWrapper::PendAnimation(AnimId::Drill_Vertical_Off);
        ResourceManagerWrapper::PendAnimation(AnimId::Drill_Vertical_On);
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
    }
    else
    {
        relive_new Drill(static_cast<relive::Path_Drill*>(pTlv), tlvId);
    }
}

void Factory::Factory_ColourfulMeter(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        // gMap.LoadResource("LCDFONT.FNT", ResourceManager::Resource_Font, AEResourceID::kLcdfontResID, loadMode);
    }
    else
    {
        relive_new ColourfulMeter(static_cast<relive::Path_ColourfulMeter*>(pTlv), tlvId);
    }
}

void Factory::Factory_FlyingSligSpawner(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        LoadFlyingSligResources();
    }
    else
    {
        relive_new FlyingSligSpawner(static_cast<relive::Path_FlyingSligSpawner*>(pTlv), tlvId);
    }
}

void Factory::Factory_MineCar(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Mine_Car_Closed);
        ResourceManagerWrapper::PendAnimation(AnimId::Mine_Car_Open);
        ResourceManagerWrapper::PendAnimation(AnimId::Mine_Car_Shake_A);
        ResourceManagerWrapper::PendAnimation(AnimId::Mine_Car_Shake_B);
        ResourceManagerWrapper::PendAnimation(AnimId::Mine_Car_Tread_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::Mine_Car_Tread_Move_A);
        ResourceManagerWrapper::PendAnimation(AnimId::Mine_Car_Tread_Move_B);
        ResourceManagerWrapper::PendAnimation(AnimId::Metal_Gib);
        ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion);
        ResourceManagerWrapper::PendAnims(kAbeGibs);
    }
    else
    {
        relive_new MineCar(static_cast<relive::Path_MineCar*>(pTlv), tlvId, 0, 0, 0);
    }
}

void Factory::Factory_BoneBag(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::BoneBag_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::BoneBag_HardHit);
        ResourceManagerWrapper::PendAnimation(AnimId::BoneBag_SoftHit);
        ResourceManagerWrapper::PendAnimation(AnimId::Bone);
    }
    else
    {
        relive_new BoneBag(static_cast<relive::Path_BoneBag*>(pTlv), tlvId);
    }
}

void Factory::Factory_ExplosionSet(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        if (gMap.mCurrentLevel == EReliveLevelIds::eBonewerkz)
        {
            ResourceManagerWrapper::PendAnimation(AnimId::FallingCrate_Falling);
            ResourceManagerWrapper::PendAnimation(AnimId::FallingCrate_Waiting);
        }
        else
        {
            ResourceManagerWrapper::PendAnimation(AnimId::AE_FallingRock_Falling);
            ResourceManagerWrapper::PendAnimation(AnimId::AE_FallingRock_Waiting);
        }
        ResourceManagerWrapper::PendAnimation(AnimId::HoistRock1);
        ResourceManagerWrapper::PendAnimation(AnimId::HoistRock2);
        ResourceManagerWrapper::PendAnimation(AnimId::HoistRock3);
        ResourceManagerWrapper::PendAnimation(AnimId::Explosion_Sticks);
        ResourceManagerWrapper::PendAnimation(AnimId::ObjectShadow);
        ResourceManagerWrapper::PendAnimation(AnimId::Explosion_Rocks);
        ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion);
    }
    else
    {
        if (!gExplosionSet)
        {
            // pExplosionSet_5BBF68 is assigned in the ctor (OWI programming)
            relive_new ExplosionSet();
        }
        gExplosionSet->Init(static_cast<relive::Path_ExplosionSet*>(pTlv));
        Path::TLV_Reset(tlvId, -1, 0, 0);
    }
}

void Factory::Factory_MultiSwitchController(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode != LoadMode::LoadResourceFromList_1 && loadmode != LoadMode::LoadResource_2)
    {
        relive_new MultiSwitchController(static_cast<relive::Path_MultiSwitchController*>(pTlv), tlvId);
    }
}

void Factory::Factory_StatusLight(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Status_Light_Green);
        ResourceManagerWrapper::PendAnimation(AnimId::Status_Light_Red);
    }
    else
    {
        relive_new StatusLight(static_cast<relive::Path_StatusLight*>(pTlv), tlvId);
    }
}

void Factory::Factory_SlapLock(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::SlapLock_Initiate);
        ResourceManagerWrapper::PendAnimation(AnimId::SlapLock_Punched);
        ResourceManagerWrapper::PendAnimation(AnimId::SlapLock_Shaking);
    }
    else
    {
        relive_new SlapLock(static_cast<relive::Path_SlapLock*>(pTlv), tlvId);
    }
}

void Factory::Factory_ParamiteWebLine(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::ParamiteWeb);
    }
    else
    {
        relive_new ParamiteWebLine(static_cast<relive::Path_ParamiteWebLine*>(pTlv), tlvId);
    }
}

void Factory::Factory_Alarm(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::ConstructObject_0)
    {
        relive_new Alarm(static_cast<relive::Path_Alarm*>(pTlv), tlvId);
    }
}

void Factory::Factory_BrewMachine(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode)
{
    if (loadmode == LoadMode::LoadResourceFromList_1 || loadmode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::BrewMachine_Button);
        ResourceManagerWrapper::PendAnimation(AnimId::Fart);
        ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion);
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        // gMap.LoadResource("LCDFONT.FNT", ResourceManager::Resource_Font, AEResourceID::kLcdfontResID, loadmode);
    }
    else
    {
        relive_new BrewMachine(static_cast<relive::Path_BrewMachine*>(pTlv), tlvId);
    }
}

void Factory::Factory_ScrabSpawner(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(Scrab::sScrabMotionAnimIds);
    }
    else
    {
        relive_new ScrabSpawner(static_cast<relive::Path_ScrabSpawner*>(pTlv), tlvId);
    }
}

void Factory::Factory_CrawlingSlig(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnims(CrawlingSlig::sCrawlingSligAnimIdTable);
        ResourceManagerWrapper::PendAnims(kSligGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::Grenade);
        ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion_Small);
        ResourceManagerWrapper::PendAnimation(AnimId::Metal_Gib);
        ResourceManagerWrapper::PendAnims(kAbeGibs);
        ResourceManagerWrapper::PendAnimation(AnimId::ShootingFire_Particle);
        ResourceManagerWrapper::PendAnimation(AnimId::Vaporize_Particle);
        ResourceManagerWrapper::PendAnims(kSlogGibs);
    }
    else
    {
        relive_new CrawlingSlig(static_cast<relive::Path_CrawlingSlig*>(pTlv), tlvId);
    }
}

void Factory::Factory_SligGetPants(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        LoadWalkingSligResources();
        ResourceManagerWrapper::PendAnimation(AnimId::CrawlingSligLocker_Closed);
        ResourceManagerWrapper::PendAnimation(AnimId::CrawlingSligLocker_Open);
    }
    else
    {
        relive_new SligGetPantsAndWings(pTlv, tlvId);
    }
}

void Factory::Factory_SligGetWings(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        LoadFlyingSligResources();
        ResourceManagerWrapper::PendAnimation(AnimId::CrawlingSligLocker_Closed);
        ResourceManagerWrapper::PendAnimation(AnimId::CrawlingSligLocker_Open);
    }
    else
    {
        relive_new SligGetPantsAndWings(pTlv, tlvId);
    }
}

void Factory::Factory_Greeter(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::MotionDetector_Flare);
        ResourceManagerWrapper::PendAnimation(AnimId::MotionDetector_Laser);
        ResourceManagerWrapper::PendAnimation(AnimId::Greeter_Moving);
        ResourceManagerWrapper::PendAnimation(AnimId::Greeter_Turn);
        ResourceManagerWrapper::PendAnimation(AnimId::Greeter_Hit);
        ResourceManagerWrapper::PendAnimation(AnimId::Greeter_Speak);
        ResourceManagerWrapper::PendAnimation(AnimId::Greeter_Chase);
        ResourceManagerWrapper::PendAnimation(AnimId::Greeter_Falling);
        ResourceManagerWrapper::PendAnimation(AnimId::Zap_Line_Blue);
        ResourceManagerWrapper::PendAnimation(AnimId::Zap_Line_Red);
        ResourceManagerWrapper::PendAnimation(AnimId::Metal_Gib);
        ResourceManagerWrapper::PendAnimation(AnimId::AirExplosion);
        ResourceManagerWrapper::PendAnims(kAbeGibs);
    }
    else
    {
        relive_new Greeter(static_cast<relive::Path_Greeter*>(pTlv), tlvId);
    }
}

void Factory::Factory_CrawlingSligButton(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::CrawlingSligButton);
        ResourceManagerWrapper::PendAnimation(AnimId::CrawlingSligButtonUse);
    }
    else
    {
        relive_new CrawlingSligButton(static_cast<relive::Path_CrawlingSligButton*>(pTlv), tlvId);
    }
}

void Factory::Factory_GlukkonSwitch(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Security_Door_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::Security_Door_Speak);
    }
    else
    {
        relive_new GlukkonSwitch(static_cast<relive::Path_GlukkonSwitch*>(pTlv), tlvId);
    }
}

void Factory::Factory_DoorBlocker(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Door_Lock_Idle);
        ResourceManagerWrapper::PendAnimation(AnimId::Door_Lock_Open);
    }
    else
    {
        relive_new DoorBlocker(static_cast<relive::Path_DoorBlocker*>(pTlv), tlvId);
    }
}

void Factory::Factory_TorturedMudokon(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (!pTlv->mTlvSpecificMeaning)
    {
        if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
        {
            ResourceManagerWrapper::PendAnimation(AnimId::Tortured_Mudokon);
            ResourceManagerWrapper::PendAnimation(AnimId::Tortured_Mudokon_Released);
            ResourceManagerWrapper::PendAnimation(AnimId::Tortured_Mudokon_Zap);
            ResourceManagerWrapper::PendAnimation(AnimId::Tortured_Mudokon_Tears);
            ResourceManagerWrapper::PendAnimation(AnimId::Electric_Wall);
        }
        else
        {
            relive_new TorturedMudokon(static_cast<relive::Path_TorturedMudokon*>(pTlv), tlvId);
        }
    }
}

void Factory::Factory_TrainDoor(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode)
{
    if (loadMode == LoadMode::LoadResourceFromList_1 || loadMode == LoadMode::LoadResource_2)
    {
        ResourceManagerWrapper::PendAnimation(AnimId::Door_Train_Closed);
        ResourceManagerWrapper::PendAnimation(AnimId::Door_Train_Closing);
    }
    else
    {
        relive_new TrainDoor(static_cast<relive::Path_TrainDoor*>(pTlv), tlvId);
    }
}

Factory::Factory()
{
    mMap[ReliveTypes::eMainMenuController] = &Factory::Factory_MainMenuController;
    mMap[ReliveTypes::eHoist] = &Factory::Factory_Hoist;
    mMap[ReliveTypes::eEdge] = &Factory::Factory_Edge;
    mMap[ReliveTypes::eDoor] = &Factory::Factory_Door;
    mMap[ReliveTypes::eShadowZone] = &Factory::Factory_ShadowZone;
    mMap[ReliveTypes::eLiftPoint] = &Factory::Factory_LiftPoint;
    mMap[ReliveTypes::eWellExpress] = &Factory::Factory_Well;
    mMap[ReliveTypes::eWellLocal] = &Factory::Factory_Well;
    mMap[ReliveTypes::eDove] = &Factory::Factory_Dove;
    mMap[ReliveTypes::eRockSack] = &Factory::Factory_RockSack;
    mMap[ReliveTypes::eFallingItem] = &Factory::Factory_FallingItem;
    mMap[ReliveTypes::ePullRingRope] = &Factory::Factory_PullRingRope;
    mMap[ReliveTypes::eTimedMine] = &Factory::Factory_TimedMine;
    mMap[ReliveTypes::eSlig] = &Factory::Factory_Slig;
    mMap[ReliveTypes::eSlog] = &Factory::Factory_Slog;
    mMap[ReliveTypes::eLever] = &Factory::Factory_Lever;
    mMap[ReliveTypes::eSecurityOrb] = &Factory::Factory_SecurityOrb;
    mMap[ReliveTypes::eAbeStart] = &Factory::Factory_AbeStart;
    mMap[ReliveTypes::eMine] = &Factory::Factory_Mine;
    mMap[ReliveTypes::eUXB] = &Factory::Factory_UXB;
    mMap[ReliveTypes::eParamite] = &Factory::Factory_Paramite;
    mMap[ReliveTypes::eMovieHandStone] = &Factory::Factory_MovieHandStone;
    mMap[ReliveTypes::eBirdPortal] = &Factory::Factory_BirdPortal;
    mMap[ReliveTypes::eTrapDoor] = &Factory::Factory_TrapDoor;
    mMap[ReliveTypes::eSligBoundLeft] = &Factory::Factory_SligBoundLeft;
    mMap[ReliveTypes::eFootSwitch] = &Factory::Factory_FootSwitch;
    mMap[ReliveTypes::eSecurityClaw] = &Factory::Factory_SecurityClaw;
    mMap[ReliveTypes::eMotionDetector] = &Factory::Factory_MotionDetector;
    mMap[ReliveTypes::eSligSpawner] = &Factory::Factory_SligSpawner;
    mMap[ReliveTypes::eElectricWall] = &Factory::Factory_ElectricWall;
    mMap[ReliveTypes::eLiftMover] = &Factory::Factory_LiftMover;
    mMap[ReliveTypes::eMeatSack] = &Factory::Factory_MeatSack;
    mMap[ReliveTypes::eScrab] = &Factory::Factory_Scrab;
    mMap[ReliveTypes::eSligBoundRight] = &Factory::Factory_SligBoundRight;
    mMap[ReliveTypes::eInvisibleSwitch] = &Factory::Factory_InvisibleSwitch;
    mMap[ReliveTypes::eMudokon] = &Factory::Factory_Mudokon;
    mMap[ReliveTypes::eDoorFlame] = &Factory::Factory_DoorFlame;
    mMap[ReliveTypes::eMovingBomb] = &Factory::Factory_MovingBomb;
    mMap[ReliveTypes::eTimerTrigger] = &Factory::Factory_TimerTrigger;
    mMap[ReliveTypes::eSecurityDoor] = &Factory::Factory_SecurityDoor;
    mMap[ReliveTypes::eBoomMachine] = &Factory::Factory_BoomMachine;
    mMap[ReliveTypes::eBackgroundAnimation] = &Factory::Factory_BackgroundAnimation;
    mMap[ReliveTypes::eLCDScreen] = &Factory::Factory_LCDScreen;
    mMap[ReliveTypes::eHandStone] = &Factory::Factory_HandStone;
    mMap[ReliveTypes::eCreditsController] = &Factory::Factory_CreditsController;
    mMap[ReliveTypes::eLCDStatusBoard] = &Factory::Factory_LCDStatusBoard;
    mMap[ReliveTypes::eWheelSyncer] = &Factory::Factory_WheelSyncer;
    mMap[ReliveTypes::eMusicTrigger] = &Factory::Factory_MusicTrigger;
    mMap[ReliveTypes::eSlogSpawner] = &Factory::Factory_SlogSpawner;
    mMap[ReliveTypes::eGasCountdown] = &Factory::Factory_GasCountdown;
    mMap[ReliveTypes::eGasEmitter] = &Factory::Factory_GasEmitter;
    mMap[ReliveTypes::eZzzSpawner] = &Factory::Factory_ZzzSpawner;
    mMap[ReliveTypes::eGlukkon] = &Factory::Factory_Glukkon;
    mMap[ReliveTypes::eWater] = &Factory::Factory_Water;
    mMap[ReliveTypes::eWorkWheel] = &Factory::Factory_WorkWheel;
    mMap[ReliveTypes::eLaughingGas] = &Factory::Factory_LaughingGas;
    mMap[ReliveTypes::eFlyingSlig] = &Factory::Factory_FlyingSlig;
    mMap[ReliveTypes::eFleech] = &Factory::Factory_Fleech;
    mMap[ReliveTypes::eSlurg] = &Factory::Factory_Slurg;
    mMap[ReliveTypes::eSlamDoor] = &Factory::Factory_SlamDoor;
    mMap[ReliveTypes::eLevelLoader] = &Factory::Factory_LevelLoader;
    mMap[ReliveTypes::eDemoSpawnPoint] = &Factory::Factory_DemoSpawnPoint;
    mMap[ReliveTypes::eTeleporter] = &Factory::Factory_Teleporter;
    mMap[ReliveTypes::eSlurgSpawner] = &Factory::Factory_SlurgSpawner;
    mMap[ReliveTypes::eDrill] = &Factory::Factory_Drill;
    mMap[ReliveTypes::eColourfulMeter] = &Factory::Factory_ColourfulMeter;
    mMap[ReliveTypes::eFlyingSligSpawner] = &Factory::Factory_FlyingSligSpawner;
    mMap[ReliveTypes::eMineCar] = &Factory::Factory_MineCar;
    mMap[ReliveTypes::eBoneBag] = &Factory::Factory_BoneBag;
    mMap[ReliveTypes::eExplosionSet] = &Factory::Factory_ExplosionSet;
    mMap[ReliveTypes::eMultiSwitchController] = &Factory::Factory_MultiSwitchController;
    mMap[ReliveTypes::eStatusLight] = &Factory::Factory_StatusLight;
    mMap[ReliveTypes::eSlapLock] = &Factory::Factory_SlapLock;
    mMap[ReliveTypes::eParamiteWebLine] = &Factory::Factory_ParamiteWebLine;
    mMap[ReliveTypes::eAlarm] = &Factory::Factory_Alarm;
    mMap[ReliveTypes::eBrewMachine] = &Factory::Factory_BrewMachine;
    mMap[ReliveTypes::eScrabSpawner] = &Factory::Factory_ScrabSpawner;
    mMap[ReliveTypes::eCrawlingSlig] = &Factory::Factory_CrawlingSlig;
    mMap[ReliveTypes::eSligGetPants] = &Factory::Factory_SligGetPants;
    mMap[ReliveTypes::eSligGetWings] = &Factory::Factory_SligGetWings;
    mMap[ReliveTypes::eGreeter] = &Factory::Factory_Greeter;
    mMap[ReliveTypes::eCrawlingSligButton] = &Factory::Factory_CrawlingSligButton;
    mMap[ReliveTypes::eGlukkonSwitch] = &Factory::Factory_GlukkonSwitch;
    mMap[ReliveTypes::eDoorBlocker] = &Factory::Factory_DoorBlocker;
    mMap[ReliveTypes::eTorturedMud] = &Factory::Factory_TorturedMudokon;
    mMap[ReliveTypes::eTrainDoor] = &Factory::Factory_TrainDoor;
}
    
void Factory::Factory::ConstructTLVObject(relive::Path_TLV* pTlv, Path* pPath, const Guid& tlvInfo, LoadMode loadMode)
{
    auto it = mMap.find(pTlv->mTlvType);
    if (it != std::end(mMap))
    {
        TFactoryFunction fn = it->second;
        (this->*fn)(pTlv, pPath, tlvInfo, loadMode);
    }
}

