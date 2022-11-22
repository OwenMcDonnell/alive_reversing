#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "Map.hpp"
#include "BaseAliveGameObject.hpp"
#include "Path.hpp"

class PathLine;

namespace AO {

class RollingBallShaker;

class RollingBall final : public BaseAliveGameObject
{
public:
    RollingBall(relive::Path_RollingBall* pTlv, const Guid& tlvId);
    ~RollingBall();

    void LoadAnimations();

    virtual void VUpdate() override;

    void Accelerate();
    void CrushThingsInTheWay();

    Guid field_10C_tlvInfo;
    u16 mReleaseSwitchId = 0;
    enum class States : s16
    {
        eInactive,
        eStartRolling,
        eRolling,
        eFallingAndHittingWall,
        eCrushedBees
    };
    States mState = States::eInactive;
    Guid mRollingBallShakerId;
    FP mMaxSpeed = {};
    FP mAcceleration = {};

private:
    void KillRollingBallShaker();
};


} // namespace AO
