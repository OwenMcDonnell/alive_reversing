#pragma once
#include "../relive_lib/StringHash.hpp"

namespace relive
{
    class Path_TLV;
}

class Guid;
class Path;

enum class LoadMode : s16
{
    ConstructObject_0 = 0,
    LoadResourceFromList_1 = 1,
    LoadResource_2 = 2
};

class Factory final
{
public:
    Factory();

    void ConstructTLVObject(relive::Path_TLV* pTlv, Path* pPath, const Guid& tlvInfo, LoadMode loadMode);

private:
    void Factory_MainMenuController(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode);
    void Factory_Hoist(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode);
    void Factory_Edge(relive::Path_TLV* /*pTlv*/, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode);
    void Factory_Door(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_ShadowZone(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode);
    void Factory_LiftPoint(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_Well(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode);
    void Factory_Dove(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_RockSack(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_FallingItem(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_PullRingRope(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_TimedMine(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode);
    void Factory_Slig(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_Slog(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_Lever(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_SecurityOrb(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_AbeStart(relive::Path_TLV* pTlv, Path*, const Guid& /*tlvId*/, LoadMode loadmode);
    void Factory_Mine(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadmode);
    void Factory_UXB(relive::Path_TLV* pTlv, Path* /*pPath*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Paramite(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_MovieHandStone(relive::Path_TLV*, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_BirdPortal(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_TrapDoor(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_SligBoundLeft(relive::Path_TLV* pTlv, Path*, const Guid& /*tlvId*/, LoadMode loadMode);
    void Factory_FootSwitch(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_SecurityClaw(relive::Path_TLV* pTlv, Path* pPath, const Guid& tlvId, LoadMode loadMode);
    void Factory_MotionDetector(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_SligSpawner(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_ElectricWall(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_LiftMover(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_MeatSack(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_Scrab(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_SligBoundRight(relive::Path_TLV* pTlv, Path* pPath, const Guid& tlvId, LoadMode loadMode);
    void Factory_InvisibleSwitch(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_Mudokon(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_DoorFlame(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_MovingBomb(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_TimerTrigger(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_SecurityDoor(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_BoomMachine(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_BackgroundAnimation(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_LCDScreen(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_HandStone(relive::Path_TLV*, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_CreditsController(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_LCDStatusBoard(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_WheelSyncer(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_MusicTrigger(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_SlogSpawner(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_GasCountdown(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_GasEmitter(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_ZzzSpawner(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_Glukkon(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_Water(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_WorkWheel(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_LaughingGas(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_FlyingSlig(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_Fleech(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_Slurg(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_SlamDoor(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_LevelLoader(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_DemoSpawnPoint(relive::Path_TLV*, Path*, const Guid&, LoadMode loadMode);
    void Factory_Teleporter(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_SlurgSpawner(relive::Path_TLV*, Path*, const Guid&, LoadMode loadMode);
    void Factory_Drill(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_ColourfulMeter(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_FlyingSligSpawner(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_MineCar(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_BoneBag(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_ExplosionSet(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_MultiSwitchController(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_StatusLight(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_SlapLock(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_ParamiteWebLine(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_Alarm(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_BrewMachine(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadmode);
    void Factory_ScrabSpawner(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_CrawlingSlig(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_SligGetPants(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_SligGetWings(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_Greeter(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_CrawlingSligButton(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_GlukkonSwitch(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_DoorBlocker(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_TorturedMudokon(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);
    void Factory_TrainDoor(relive::Path_TLV* pTlv, Path*, const Guid& tlvId, LoadMode loadMode);

    using TFactoryFunction = decltype(&Factory::Factory_Hoist);

    std::map<StringHash, TFactoryFunction> mMap;
};
