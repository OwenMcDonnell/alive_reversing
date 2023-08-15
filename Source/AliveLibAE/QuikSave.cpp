#include "stdafx.h"
#include "QuikSave.hpp"
#include "../relive_lib/Function.hpp"
#include "ResourceManager.hpp"
#include "PathData.hpp"
#include "Map.hpp"
#include "Abe.hpp"
#include "Glukkon.hpp"
#include "UXB.hpp"
#include "ThrowableArray.hpp"
#include "LCDStatusBoard.hpp"
#include "DDCheat.hpp"
#include "../relive_lib/Events.hpp"
#include "WorkWheel.hpp"
#include "Drill.hpp"
#include "Io.hpp"
#include "LiftPoint.hpp"
#include "LiftMover.hpp"
#include "TrapDoor.hpp"
#include "TimerTrigger.hpp"
#include "SlamDoor.hpp"
#include "FlyingSlig.hpp"
#include "SlapLock.hpp"
#include "SlapLockWhirlWind.hpp"
#include "AbilityRing.hpp"
#include "Slurg.hpp"
#include "GasCountDown.hpp"
#include "Rock.hpp"
#include "Meat.hpp"
#include "Bone.hpp"
#include "MineCar.hpp"
#include "Slig.hpp"
#include "SligSpawner.hpp"
#include "ScrabSpawner.hpp"
#include "GameEnderController.hpp"
#include "Paramite.hpp"
#include "BirdPortal.hpp"
#include "ColourfulMeter.hpp"
#include "MinesAlarm.hpp"
#include "EvilFart.hpp"
#include "CrawlingSlig.hpp"
#include "Fleech.hpp"
#include "Greeter.hpp"
#include "Slog.hpp"
#include "Grenade.hpp"
#include "Mudokon.hpp"
#include "../relive_lib/FatalError.hpp"
#include "../relive_lib/BinaryPath.hpp"
#include "FlyingSligSpawner.hpp"
#include "Scrab.hpp"
#include "Game.hpp"

#include "nlohmann/json.hpp" // TODO: temp
#include "../relive_lib/data_conversion/AESaveSerialization.hpp"

Quicksave QuikSave::gActiveQuicksaveData;
SaveFileRec QuikSave::gSaveFileRecords[128];
s32 QuikSave::gSavedGameToLoadIdx;
s32 QuikSave::gTotalSaveFilesCount;

static void ConvertObjectSaveStateDataToJson(nlohmann::json& j, const StringHash& reliveType, const SerializedObjectData& pData)
{
    switch (reliveType.Value())
    {
        case ::ReliveTypes::eSligSpawner.Value():
            j.push_back(*pData.ReadTmpPtr<::SligSpawnerSaveState>());
            break;
        case ::ReliveTypes::eLiftMover.Value():
            j.push_back(*pData.ReadTmpPtr<::LiftMoverSaveState>());
            break;

        case ::ReliveTypes::eBone.Value():
            j.push_back(*pData.ReadTmpPtr<::BoneSaveState>());
            break;

        case ::ReliveTypes::eMinesAlarm.Value():
            j.push_back(*pData.ReadTmpPtr<::MinesAlarmSaveState>());
            break;

        case ::ReliveTypes::eCrawlingSlig.Value():
            j.push_back(*pData.ReadTmpPtr<::CrawlingSligSaveState>());
            break;

        case ::ReliveTypes::eDrill.Value():
            j.push_back(*pData.ReadTmpPtr<::DrillSaveState>());
            break;

        case ::ReliveTypes::eEvilFart.Value():
            j.push_back(*pData.ReadTmpPtr<::EvilFartSaveState>());
            break;

        case ::ReliveTypes::eFleech.Value():
            j.push_back(*pData.ReadTmpPtr<::FleechSaveState>());
            break;

        case ::ReliveTypes::eFlyingSlig.Value():
            j.push_back(*pData.ReadTmpPtr<::FlyingSligSaveState>());
            break;

        case ::ReliveTypes::eFlyingSligSpawner.Value():
            j.push_back(*pData.ReadTmpPtr<::FlyingSligSpawnerSaveState>());
            break;

        case ::ReliveTypes::eGameEnderController.Value():
            j.push_back(*pData.ReadTmpPtr<::GameEnderControllerSaveState>());
            break;

        case ::ReliveTypes::eSlapLock_OrbWhirlWind.Value():
            j.push_back(*pData.ReadTmpPtr<::SlapLockWhirlWindSaveState>());
            break;

        case ::ReliveTypes::eSlapLock.Value():
            j.push_back(*pData.ReadTmpPtr<::SlapLockSaveState>());
            break;

        case ::ReliveTypes::eGreeter.Value():
            j.push_back(*pData.ReadTmpPtr<::GreeterSaveState>());
            break;

        case ::ReliveTypes::eGrenade.Value():
            j.push_back(*pData.ReadTmpPtr<::GrenadeSaveState>());
            break;

        case ::ReliveTypes::eGlukkon.Value():
            j.push_back(*pData.ReadTmpPtr<::GlukkonSaveState>());
            break;

        case ::ReliveTypes::eAbe.Value():
            j.push_back(*pData.ReadTmpPtr<::AbeSaveState>());
            break;

        case ::ReliveTypes::eLiftPoint.Value():
            j.push_back(*pData.ReadTmpPtr<::LiftPointSaveState>());
            break;

        case ::ReliveTypes::eMudokon.Value():
        case ::ReliveTypes::eRingOrLiftMud.Value():
            j.push_back(*pData.ReadTmpPtr<::MudokonSaveState>());
            break;

        case ::ReliveTypes::eMeat.Value():
            j.push_back(*pData.ReadTmpPtr<::MeatSaveState>());
            break;

        case ::ReliveTypes::eMineCar.Value():
            j.push_back(*pData.ReadTmpPtr<::MineCarSaveState>());
            break;

        case ::ReliveTypes::eParamite.Value():
            j.push_back(*pData.ReadTmpPtr<::ParamiteSaveState>());
            break;

        case ::ReliveTypes::eBirdPortal.Value():
            j.push_back(*pData.ReadTmpPtr<::BirdPortalSaveState>());
            break;

        case ::ReliveTypes::eThrowableArray.Value():
            j.push_back(*pData.ReadTmpPtr<::ThrowableArraySaveState>());
            break;

        case ::ReliveTypes::eAbilityRing.Value():
            j.push_back(*pData.ReadTmpPtr<::AbilityRingSaveState>());
            break;

        case ::ReliveTypes::eRock.Value():
            j.push_back(*pData.ReadTmpPtr<::RockSaveState>());
            break;

        case ::ReliveTypes::eScrab.Value():
            j.push_back(*pData.ReadTmpPtr<::ScrabSaveState>());
            break;

        case ::ReliveTypes::eScrabSpawner.Value():
            j.push_back(*pData.ReadTmpPtr<::ScrabSpawnerSaveState>());
            break;

        case ::ReliveTypes::eSlamDoor.Value():
            j.push_back(*pData.ReadTmpPtr<::SlamDoorSaveState>());
            break;

        case ::ReliveTypes::eSlig.Value():
            j.push_back(*pData.ReadTmpPtr<::SligSaveState>());
            break;

        case ::ReliveTypes::eSlog.Value():
            j.push_back(*pData.ReadTmpPtr<::SlogSaveState>());
            break;

        case ::ReliveTypes::eSlurg.Value():
            j.push_back(*pData.ReadTmpPtr<::SlurgSaveState>());
            break;

        case ::ReliveTypes::eTimerTrigger.Value():
            j.push_back(*pData.ReadTmpPtr<::TimerTriggerSaveState>());
            break;

        case ::ReliveTypes::eTrapDoor.Value():
            j.push_back(*pData.ReadTmpPtr<::TrapDoorSaveState>());
            break;

        case ::ReliveTypes::eUXB.Value():
            j.push_back(*pData.ReadTmpPtr<::UXBSaveState>());
            break;

        case ::ReliveTypes::eWorkWheel.Value():
            j.push_back(*pData.ReadTmpPtr<::WorkWheelSaveState>());
            break;

        default:
            ALIVE_FATAL("No create json save state for type %s", reliveType.String());
    }
}


static void RestoreObjectState(const StringHash& reliveType, SerializedObjectData& pData)
{
    switch (reliveType.Value())
    {
        case ::ReliveTypes::eSligSpawner.Value():
            return SligSpawner::CreateFromSaveState(pData);
            
        case ::ReliveTypes::eLiftMover.Value():
            return LiftMover::CreateFromSaveState(pData);

        case ::ReliveTypes::eBone.Value():
            return Bone::CreateFromSaveState(pData);

        case ::ReliveTypes::eMinesAlarm.Value():
            return MinesAlarm::CreateFromSaveState(pData);

        case ::ReliveTypes::eCrawlingSlig.Value():
            return CrawlingSlig::CreateFromSaveState(pData);

        case ::ReliveTypes::eDrill.Value():
            return Drill::CreateFromSaveState(pData);

        case ::ReliveTypes::eEvilFart.Value():
            return EvilFart::CreateFromSaveState(pData);

        case ::ReliveTypes::eFleech.Value():
            return Fleech::CreateFromSaveState(pData);

        case ::ReliveTypes::eFlyingSlig.Value():
            return FlyingSlig::CreateFromSaveState(pData);

        case ::ReliveTypes::eFlyingSligSpawner.Value():
            return FlyingSligSpawner::CreateFromSaveState(pData);

        case ::ReliveTypes::eGameEnderController.Value():
            return GameEnderController::CreateFromSaveState(pData);

        case ::ReliveTypes::eSlapLock_OrbWhirlWind.Value():
            return SlapLockWhirlWind::CreateFromSaveState(pData);

        case ::ReliveTypes::eSlapLock.Value():
            return SlapLock::CreateFromSaveState(pData);

        case ::ReliveTypes::eGreeter.Value():
            return Greeter::CreateFromSaveState(pData);

        case ::ReliveTypes::eGrenade.Value():
            return Grenade::CreateFromSaveState(pData);

        case ::ReliveTypes::eGlukkon.Value():
            return Glukkon::CreateFromSaveState(pData);

        case ::ReliveTypes::eAbe.Value():
            return Abe::CreateFromSaveState(pData);

        case ::ReliveTypes::eLiftPoint.Value():
            return LiftPoint::CreateFromSaveState(pData);

        case ::ReliveTypes::eMudokon.Value():
        case ::ReliveTypes::eRingOrLiftMud.Value():
            return Mudokon::CreateFromSaveState(pData);

        case ::ReliveTypes::eMeat.Value():
            return Meat::CreateFromSaveState(pData);

        case ::ReliveTypes::eMineCar.Value():
            return MineCar::CreateFromSaveState(pData);

        case ::ReliveTypes::eParamite.Value():
            return Paramite::CreateFromSaveState(pData);

        case ::ReliveTypes::eBirdPortal.Value():
            return BirdPortal::CreateFromSaveState(pData);

        case ::ReliveTypes::eThrowableArray.Value():
            return ThrowableArray::CreateFromSaveState(pData);

        case ::ReliveTypes::eAbilityRing.Value():
            return AbilityRing::CreateFromSaveState(pData);

        case ::ReliveTypes::eRock.Value():
            return Rock::CreateFromSaveState(pData);

        case ::ReliveTypes::eScrab.Value():
            return Scrab::CreateFromSaveState(pData);

        case ::ReliveTypes::eScrabSpawner.Value():
            return ScrabSpawner::CreateFromSaveState(pData);

        case ::ReliveTypes::eSlamDoor.Value():
            return SlamDoor::CreateFromSaveState(pData);

        case ::ReliveTypes::eSlig.Value():
            return Slig::CreateFromSaveState(pData);

        case ::ReliveTypes::eSlog.Value():
            return Slog::CreateFromSaveState(pData);

        case ::ReliveTypes::eSlurg.Value():
            return Slurg::CreateFromSaveState(pData);

        case ::ReliveTypes::eTimerTrigger.Value():
            return TimerTrigger::CreateFromSaveState(pData);

        case ::ReliveTypes::eTrapDoor.Value():
            return TrapDoor::CreateFromSaveState(pData);

        case ::ReliveTypes::eUXB.Value():
            return UXB::CreateFromSaveState(pData);

        case ::ReliveTypes::eWorkWheel.Value():
            return WorkWheel::CreateFromSaveState(pData);
            
        default:
            ALIVE_FATAL("No create save state for type %s", reliveType.String());
    }
}

void ConvertObjectsStatesToJson(nlohmann::json& j, const SerializedObjectData& pData)
{
    pData.ReadRewind();
    while (pData.CanRead())
    {
        const SaveStateBase* pSaveStateBase = pData.PeekTmpPtr<SaveStateBase>();
        LOG_INFO("Converting type %d with size %d", pSaveStateBase->mType, pSaveStateBase->mSize);
        ConvertObjectSaveStateDataToJson(j, pSaveStateBase->mType, pData);
    }
}

void QuikSave::RestoreBlyData(Quicksave& pSaveData)
{
    pSaveData.mObjectsStateData.ReadRewind();
    while (pSaveData.mObjectsStateData.CanRead())
    {
        const SaveStateBase* pSaveStateBase = pSaveData.mObjectsStateData.PeekTmpPtr<SaveStateBase>();
        LOG_INFO("Restore type %d with size %d", pSaveStateBase->mType, pSaveStateBase->mSize);
        RestoreObjectState(pSaveStateBase->mType, pSaveData.mObjectsStateData);
    }

    pSaveData.mObjectBlyData.ReadRewind();

    const u32 flagsTotal = pSaveData.mObjectBlyData.ReadU32();
    u32 readFlagsCount = 0;
    for (auto& binaryPath : gMap.GetLoadedPaths())
    {
        for (auto& cam : binaryPath->GetCameras())
        {
            auto pTlv = reinterpret_cast<relive::Path_TLV*>(cam->mBuffer.data());
            while (pTlv)
            {
                if (pTlv->mAttribute == relive::QuiksaveAttribute::eClearTlvFlags_1 || pTlv->mAttribute == relive::QuiksaveAttribute::eKeepTlvFlags_2) // Type 0 ignored - actually it should never be written here anyway
                {
                    pTlv->mTlvFlags.Raw().all = pSaveData.mObjectBlyData.ReadU8();
                    pTlv->mTlvSpecificMeaning = pSaveData.mObjectBlyData.ReadU8();
                    readFlagsCount++;
                    if (readFlagsCount > flagsTotal)
                    {
                        ALIVE_FATAL("Data contains %d sets of flags but read more than that", flagsTotal);
                    }
                }
                pTlv = Path::Next_TLV(pTlv);
            }
        }
    }

    ResourceManagerWrapper::LoadingLoop(false);
}

void Quicksave_LoadFromMemory_4C95A0()
{
    DestroyObjects();
    EventsReset();
    gSkipGameObjectUpdates = true;
    QuikSave::RestoreWorldInfo(QuikSave::gActiveQuicksaveData.mWorldInfo);
    gSwitchStates = QuikSave::gActiveQuicksaveData.mSwitchStates;
    gMap.mRestoreMapObjectStates = true;
    gMap.SetActiveCam(
        QuikSave::gActiveQuicksaveData.mWorldInfo.mLevel,
        QuikSave::gActiveQuicksaveData.mWorldInfo.mPath,
        QuikSave::gActiveQuicksaveData.mWorldInfo.mCam,
        CameraSwapEffects::eInstantChange_0,
        0,
        1);
    gMap.mForceLoad = 1;
}

void QuikSave::LoadActive()
{
    ResourceManagerWrapper::ShowLoadingIcon();
    Quicksave_LoadFromMemory_4C95A0();
}

static void WriteFlags(SerializedObjectData& pSaveBuffer, const relive::Path_TLV* pTlv, const BitField8<relive::TlvFlags>& flags)
{
    pSaveBuffer.WriteU8(flags.Raw().all);
    pSaveBuffer.WriteU8(pTlv->mTlvSpecificMeaning);
}

static u32 Quicksave_SaveBlyData_CountOrSave(SerializedObjectData* pSaveBuffer)
{
    u32 flagsTotal = 0;

    for (auto& binaryPath : gMap.GetLoadedPaths())
    {
        for (auto& cam : binaryPath->GetCameras())
        {
            auto pTlv = reinterpret_cast<relive::Path_TLV*>(cam->mBuffer.data());
            while (pTlv)
            {
                if (pTlv->mAttribute == relive::QuiksaveAttribute::eClearTlvFlags_1)
                {
                    if (pSaveBuffer)
                    {
                        BitField8<relive::TlvFlags> flags = pTlv->mTlvFlags;
                        if (flags.Get(relive::TlvFlags::eBit1_Created))
                        {
                            flags.Clear(relive::TlvFlags::eBit1_Created);
                            flags.Clear(relive::TlvFlags::eBit2_Destroyed);
                        }

                        WriteFlags(*pSaveBuffer, pTlv, flags);
                    }
                    flagsTotal++;
                }
                else if (pTlv->mAttribute == relive::QuiksaveAttribute::eKeepTlvFlags_2)
                {
                    if (pSaveBuffer)
                    {
                        WriteFlags(*pSaveBuffer, pTlv, pTlv->mTlvFlags);
                    }
                    flagsTotal++;
                }
                else
                {
                    // Type 0 ignored
                }
                pTlv = Path::Next_TLV(pTlv);
            }
        }
    }
    return flagsTotal;
}


void Quicksave_SaveBlyData_4C9660(SerializedObjectData& pSaveBuffer)
{
    pSaveBuffer.WriteRewind();

    const u32 flagsCount = Quicksave_SaveBlyData_CountOrSave(nullptr);
    pSaveBuffer.WriteU32(flagsCount);

    Quicksave_SaveBlyData_CountOrSave(&pSaveBuffer);
}

void QuikSave::SaveToMemory_4C91A0(Quicksave& pSave)
{
    if (sActiveHero->mHealth > FP_FromInteger(0))
    {
        QuikSave::SaveWorldInfo(&pSave.mWorldInfo);
        pSave.mSwitchStates = gSwitchStates;

        pSave.mObjectsStateData.WriteRewind();
        for (s32 idx = 0; idx < gBaseGameObjects->Size(); idx++)
        {
            BaseGameObject* pObj = gBaseGameObjects->ItemAt(idx);
            if (!pObj)
            {
                break;
            }

            if (!pObj->GetDead())
            {
                pObj->VGetSaveState(pSave.mObjectsStateData);
            }
        }

        Quicksave_SaveBlyData_4C9660(pSave.mObjectBlyData);
    }
}

void QuikSave::DoQuicksave()
{
    ResourceManagerWrapper::ShowLoadingIcon();
    QuikSave::SaveToMemory_4C91A0(gActiveQuicksaveData);
}

void QuikSave::RestoreWorldInfo(const Quicksave_WorldInfo& rInfo)
{
    // Read all fields bar the last
    for (s32 i = 0; i < ALIVE_COUNTOF(rInfo.field_18_saved_killed_muds_per_zulag); i++)
    {
        sSavedKilledMudsPerZulag_5C1B50.mData[i] = rInfo.field_18_saved_killed_muds_per_zulag[i];
    }

    // Last is read from another field
    sSavedKilledMudsPerZulag_5C1B50.mData[ALIVE_COUNTOF(sSavedKilledMudsPerZulag_5C1B50.mData) - 1] = rInfo.field_17_last_saved_killed_muds_per_path;

    sActiveHero->SetRestoredFromQuickSave(true);
    gZulagNumber = rInfo.field_2C_current_zulag_number;
    gKilledMudokons = rInfo.mKilledMudokons;
    gRescuedMudokons = rInfo.mRescuedMudokons;
    gMudokonsInArea = rInfo.field_16_muds_in_area; // TODO: Check types
    gTotalMeterBars = rInfo.mTotalMeterBars;
    gbDrawMeterCountDown = rInfo.field_30_bDrawMeterCountDown;
    gGasTimer = rInfo.mGasTimer;
    gAbeInvincible = rInfo.mAbeInvincible;
    gVisitedBonewerkz = rInfo.mVisitedBonewerkz;
    gVisitedBarracks = rInfo.mVisitedBarracks;
    gVisitedFeecoEnder = rInfo.mVisitedFeecoEnder;
    sGnFrame = rInfo.mGnFrame;
}

void QuikSave::SaveWorldInfo(Quicksave_WorldInfo* pInfo)
{
    const PSX_RECT rect = sControlledCharacter->VGetBoundingRect();

    pInfo->mGnFrame = sGnFrame;
    pInfo->mLevel = gMap.mCurrentLevel;
    pInfo->mPath = gMap.mCurrentPath;
    pInfo->mCam = gMap.mCurrentCamera;

    for (s32 i = 0; i < ALIVE_COUNTOF(pInfo->field_18_saved_killed_muds_per_zulag); i++)
    {
        pInfo->field_18_saved_killed_muds_per_zulag[i] = sSavedKilledMudsPerZulag_5C1B50.mData[i];
    }

    pInfo->field_17_last_saved_killed_muds_per_path = sSavedKilledMudsPerZulag_5C1B50.mData[ALIVE_COUNTOF(sSavedKilledMudsPerZulag_5C1B50.mData) - 1];

    pInfo->field_2C_current_zulag_number = gZulagNumber;
    pInfo->mRescuedMudokons = gRescuedMudokons;
    pInfo->mKilledMudokons = gKilledMudokons;
    pInfo->field_16_muds_in_area = static_cast<s8>(gMudokonsInArea); // TODO: Check types
    pInfo->mTotalMeterBars = gTotalMeterBars;
    pInfo->field_30_bDrawMeterCountDown = gbDrawMeterCountDown;
    pInfo->mAbeInvincible = gAbeInvincible;
    pInfo->mVisitedBonewerkz = gVisitedBonewerkz;
    pInfo->mVisitedBarracks = gVisitedBarracks;
    pInfo->mVisitedFeecoEnder = gVisitedFeecoEnder;
    pInfo->mGasTimer = gGasTimer;
    pInfo->mControlledCharX = FP_GetExponent(sControlledCharacter->mXPos);
    pInfo->mControlledCharY = rect.h;
    pInfo->mControlledCharScale = sControlledCharacter->GetSpriteScale() == FP_FromDouble(1.0);
}

static s32 Sort_comparitor_4D42C0(const void* pSaveRecLeft, const void* pSaveRecRight)
{
    const s32 leftTime = reinterpret_cast<const SaveFileRec*>(pSaveRecLeft)->mLastWriteTimeStamp;
    const s32 rightTime = reinterpret_cast<const SaveFileRec*>(pSaveRecRight)->mLastWriteTimeStamp;

    if (leftTime <= rightTime)
    {
        return leftTime < rightTime;
    }
    else
    {
        return -1;
    }
}

void QuikSave::FindSaves()
{
    gTotalSaveFilesCount = 0;

    IO_EnumerateDirectory("*.json", [](const char_type* fileName, u32 lastWriteTime)
                          {
                              if (gTotalSaveFilesCount < 128)
                              {
                                  size_t fileNameLen = strlen(fileName) - 5; // remove .json
                                  if (fileNameLen > 0)
                                  {
                                      // Limit length to prevent buffer overflow
                                      if (fileNameLen > 20)
                                      {
                                          fileNameLen = 20;
                                      }

                                      SaveFileRec* pRec = &gSaveFileRecords[gTotalSaveFilesCount];
                                      memcpy(pRec->mFileName, fileName, fileNameLen);
                                      pRec->mFileName[fileNameLen] = 0;

                                      pRec->mLastWriteTimeStamp = lastWriteTime;
                                      gTotalSaveFilesCount++;
                                  }
                              }
                          });

    // Sort all we've found by time stamp, users probably want to load their last save first
    qsort(gSaveFileRecords, gTotalSaveFilesCount, sizeof(SaveFileRec), Sort_comparitor_4D42C0);

    // Underflow
    if (gSavedGameToLoadIdx < 0)
    {
        gSavedGameToLoadIdx = 0;
    }

    // Overflow
    if (gSavedGameToLoadIdx >= gTotalSaveFilesCount)
    {
        gSavedGameToLoadIdx = gTotalSaveFilesCount - 1;
    }
}
