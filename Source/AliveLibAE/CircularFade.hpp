#pragma once

#include "../relive_lib/GameObjects/BaseAnimatedWithPhysicsGameObject.hpp"

class CircularFade final : public ::BaseAnimatedWithPhysicsGameObject
{
public:
    CircularFade(FP xpos, FP ypos, FP scale, s16 direction, s8 destroyOnDone);
    ~CircularFade();

    virtual void VScreenChanged() override;
    virtual void VUpdate() override;
    virtual void VRender(BasePrimitive** ppOt) override;

    // New virtuals
    virtual void VFadeIn(s16 direction, s8 destroyOnDone);
    virtual s32 VDone();

private:
    bool mFadeIn = false;
    bool mDone = false;
    bool mDestroyOnDone = false;
    Poly_G4 mTile1[2] = {};
    Poly_G4 mTile2[2] = {};
    Poly_G4 mTile3[2] = {};
    Poly_G4 mTile4[2] = {};
    s16 mFadeColour = 0;
    s16 mSpeed = 0;
};

CircularFade* Make_Circular_Fade(FP xpos, FP ypos, FP scale, s16 direction, s8 destroyOnDone, bool surviveDeathReset);
