#pragma once
#include "../relive_lib/StringHash.hpp"

namespace relive
{
    class Path_TLV;
}

class Guid;

namespace AO {

class Map;

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

    void ConstructTLVObject(relive::Path_TLV* pTlv, Map* pMap, const Guid& tlvInfo, LoadMode loadMode);
private:
    void Factory_Hoist(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Edge(relive::Path_TLV* /*pTlv*/, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Door(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_ShadowZone(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_LiftPoint(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Well(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Dove(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_RockSack(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_ZBall(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_FallingItem(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_PullRingRope(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_BackgroundAnimation(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Honey(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_TimedMine(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Slig(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Slog(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Lever(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_BellHammer(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_SecurityOrb(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_LiftMudokon(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_BeeSwarmHole(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_HoneySack(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_AbeStart(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& /*tlvId*/, LoadMode loadMode);
    void Factory_ElumWall(relive::Path_TLV* /*pTlv*/, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_SlingMud(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_BeeNest(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Mine(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Uxb(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Paramite(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Bat(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_RingMudokon(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_BirdPortal(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_BellSongStone(relive::Path_TLV* /*pTlv*/, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_TrapDoor(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_RollingBall(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_SligBoundLeft(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_RollingBallStopper(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_FootSwitch(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_SecurityClaw(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_MotionDetector(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_SligSpawner(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_ElectricWall(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_LiftMover(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_ChimeLock(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Elum(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_MeatSack(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_Scrab(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_FlintLockFire(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_SligBoundRight(relive::Path_TLV* pTlv, Map* pMap, const Guid& tlvId, LoadMode loadMode);
    void Factory_InvisibleSwitch(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_WorkerMudokon(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_DoorFlame(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_MovingBomb(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_MeatSaw(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_MainMenuController(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_HintFly(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_TimerTrigger(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_SecurityDoor(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_BoomMachine(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_LCDScreen(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_HandStone(relive::Path_TLV* /*pTlv*/, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_CreditsController(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_LCDStatusBoard(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_SwitchStateBooleanLogic(relive::Path_TLV* /*pTlv*/, Map* /*pMap*/, const Guid& /*tlvId*/, LoadMode loadMode);
    void Factory_MusicTrigger(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_LightEffect(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_SlogSpawner(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_GasCountdown(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_RingCancel(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_GasEmitter(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_ZzzSpawner(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_BackgroundGlukkon(relive::Path_TLV* pTlv, Map* /*pMap*/, const Guid& tlvId, LoadMode loadMode);
    void Factory_KillUnsavedMuds(relive::Path_TLV* /*pTlv*/, Map* pMap, const Guid& tlvId, LoadMode loadMode);

    using TFactoryFunction = decltype(&Factory::Factory_Hoist);

    std::map<StringHash, TFactoryFunction> mMap;
};

} // namespace AO
