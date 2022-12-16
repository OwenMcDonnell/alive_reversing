#pragma once

#include "../relive_lib/BaseGameObject.hpp"
#include "../relive_lib/FixedPoint.hpp"

namespace relive
{
    struct Path_LiftMover;
}

class LiftPoint;

enum class LiftMoverStates : s16
{
    eInactive_0 = 0,
    eStartMovingDown_1 = 1,
    eMovingDown_2 = 2,
    eStartMovingUp_3 = 3,
    eMovingUp_4 = 4,
    eMovingDone_5 = 5,
};

struct LiftMoverSaveState final
{
    ReliveTypes mType;
    Guid mTlvId;
    LiftMoverStates mState;
};

class LiftMover final : public BaseGameObject
{
public:
    LiftMover(relive::Path_LiftMover* pTlv, const Guid& tlvId);
    ~LiftMover();

    static s32 CreateFromSaveState(const u8* pData);
    
    virtual void VUpdate() override;
    virtual s32 VGetSaveState(u8* pSaveBuffer) override;

private:
    LiftPoint* GetLiftPoint();

private:
    s16 mLiftMoverSwitchId = 0;
    s16 mTargetLiftPointId = 0;
    Guid mTlvId;
    Guid mTargetLiftId;
    FP mLiftSpeed = {};
    LiftMoverStates mState = LiftMoverStates::eInactive_0;
    bool mMoving = false;
};
