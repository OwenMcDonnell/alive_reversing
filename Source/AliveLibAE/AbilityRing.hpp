#pragma once

#include "../relive_lib/Function.hpp"
#include "../relive_lib/GameObjects/BaseGameObject.hpp"
#include "../relive_lib/Primitives.hpp"
#include "../relive_lib/Layer.hpp"
#include "../relive_lib/MapWrapper.hpp"
#include "../relive_lib/SaveStateBase.hpp"

enum class RingTypes : s16
{
    // Red rings
    eExplosive_Pulse_0 = 0,
    eExplosive_Emit_1 = 1,        // Actually blows stuff up
    eExplosive_Emit_Effect_2 = 2, // Graphical effect only
    eExplosive_Give_3 = 3,

    // Blue rings
    eShrykull_Pulse_Small_4 = 4,
    eShrykull_Pulse_Large_5 = 5,
    eShrykull_Pulse_Orange_6 = 6, // Never used?

    // Green rings
    eInvisible_Pulse_Small_7 = 7,
    eInvisible_Pulse_Large_8 = 8,
    eInvisible_Pulse_Emit_9 = 9,
    eInvisible_Pulse_Give_10 = 10,

    // Yellow rings
    eHealing_Emit_Effect_11 = 11, // Graphical effect only
    eHealing_Emit_12 = 12,        // Actually heal muds
    eHealing_Give_13 = 13,
    eHealing_Pulse_14 = 14,
};


struct AbilityRingSaveState final : public SaveStateBase
{
    AbilityRingSaveState()
        : SaveStateBase(ReliveTypes::eAbilityRing, sizeof(*this))
    { }
    FP mRingXPos;
    FP mRingYPos;
    RingTypes mRingType;
    FP mRingScale;
    Guid mRingTlvInfo;
    FP mRingRight;
    s32 mRingCount;
    s16 mRingRed;
    s16 mRingGreen;
    s16 mRingBlue;
};

struct AbilityRing_PolyBuffer;
enum class LevelIds : s16;

class AbilityRing final : public BaseGameObject
{
public:
    AbilityRing(FP xpos, FP ypos, RingTypes ringType, FP scale);
    ~AbilityRing();

    virtual void VUpdate() override;
    virtual void VRender(OrderingTable& ot) override;
    virtual void VScreenChanged() override;
    virtual void VGetSaveState(SerializedObjectData& pSaveBuffer) override;

    static AbilityRing* Factory(FP xpos, FP ypos, RingTypes type, FP scale);
    virtual void VSetTarget(BaseGameObject* pTarget);
    static void CreateFromSaveState(SerializedObjectData& pBuffer);

private:
    void CollideWithObjects(s16 bDealDamage);

    Layer mRingLayer = Layer::eLayer_0;
    Poly_G4 mRingPolyBuffer[64] = {};
    PSX_RECT mRingCollideRects[64] = {};
    FP mRingXPos = {};
    FP mRingYPos = {};
    FP mRingLeft = {};
    FP mRingRight = {};
    FP mRingSpeed = {};
    FP mRingScaleX = {};
    FP mRingScaleY = {};
    FP mRingThickness = {};
    s16 mRingFadeoutDistance = 0;
    s16 mRingScreenX = 0;
    s16 mRingScreenY = 0;
    s16 mRingScreenXPos = 0;
    s16 mRingScreenYPos = 0;
    s16 mRingRed = 0;
    s16 mRingGreen = 0;
    s16 mRingBlue = 0;
    s16 mRingSemiTrans = 1;
    EReliveLevelIds mRingLevel = EReliveLevelIds::eNone;
    s16 mRingPath = 0;
    RingTypes mRingType = RingTypes::eExplosive_Pulse_0;
    Guid mRingTargetObjId = Guid{};
    s32 mRingCount = 64;
    s16 mRefreshTargetObjId = 0;
};
