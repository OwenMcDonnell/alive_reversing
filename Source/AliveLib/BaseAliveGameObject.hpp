#pragma once

#include "FunctionFwd.hpp"
#include "DynamicArray.hpp"
#include "Animation.hpp"
#include "BaseAnimatedWithPhysicsGameObject.hpp"

struct TintEntry
{
    __int8 field_0_level;
    unsigned __int8 field_1_r;
    unsigned __int8 field_2_g;
    unsigned __int8 field_3_b;
};
ALIVE_ASSERT_SIZEOF(TintEntry, 0x4);

struct Path_TLV;
struct PathLine;

enum Flags_114
{
    e114_Bit1 = 0x1,
    e114_Bit2 = 0x2,
    e114_Bit3 = 0x4,
    e114_Bit4_bPossesed = 0x8,
    e114_Bit5 = 0x10,
    e114_Bit6_SetOffExplosives = 0x20,
    e114_Bit7 = 0x40,
    e114_Bit8 = 0x80,
    e114_Bit9 = 0x100,
    e114_Bit10 = 0x200,
    e114_Bit11 = 0x400,
};

#pragma pack(push)
#pragma pack(2)
class BaseAliveGameObject : public BaseAnimatedWithPhysicsGameObject
{
public:
    EXPORT BaseAliveGameObject* ctor_408240(short resourceArraySize);
    EXPORT void dtor_4080B0();

    BaseGameObject* vdtor_408210(signed int flags);

    virtual void VRender(int** pOrderingTable) override;
    virtual BaseGameObject* VDestructor(signed int flags) override;

    virtual int VUnPosses_408F90();
    virtual unsigned __int16 Vnull_408F70(short a1);
    virtual void VUpdateState_4081C0(__int16 state);
    virtual  int Vsub_408320(__int16 a2, __int16 a3, int a4);
    virtual __int16 VTakeDamage_408730(BaseAliveGameObject* pFrom);
    virtual signed __int16 VOn_TLV_Collision_4087F0(Path_TLV* pTlv);
    virtual char Vsub_408A40(__int16 a2);
    virtual BaseGameObject* Vsub_408FD0(__int16 a2);
    virtual int Vnull_4081F0();
  
protected:
    EXPORT int vnull_408F90();
    EXPORT unsigned __int16 vnull_408F70(short a1);
    EXPORT void vUpdateState_4081C0(__int16 state);
    EXPORT int vsub_408320(__int16 a2, __int16 a3, int a4);
    EXPORT __int16 vTakeDamage_408730(BaseAliveGameObject* pFrom);
    EXPORT signed __int16 vOn_TLV_Collision_4087F0(Path_TLV* pTlv);
    EXPORT char vsub_408A40(__int16 a2);
    EXPORT BaseGameObject* vsub_408FD0(__int16 a2);
    EXPORT int vnull_4081F0();
    EXPORT void SetTint_425600(const TintEntry* pTintArray, LevelIds level_id);
    EXPORT signed __int16 SetBaseAnimPaletteTint_425690(TintEntry *pTintArray, LevelIds level_id, int resourceID);
    EXPORT void sub_408C40();
    EXPORT __int16 MapFollowMe_408D10(__int16 snapToGrid);
    EXPORT int Raycast_408750(FP offY, FP offX);
    EXPORT __int16 InAirCollision_408810(PathLine **ppPathLine, FP* hitX, FP* hitY, FP velY);
    EXPORT BaseAliveGameObject* FindObjectOfType_425180(Types typeToFind, FP xpos, FP ypos);
public:
    EXPORT __int16 OnTrapDoorIntersection_408BA0(BaseAliveGameObject* pOther);
public:
    FP field_E4;
    FP field_E8;
    FP field_EC;
    FP field_F0_prev_base;
    __int16 field_F4;
    __int16 field_F6_anim_frame;
    FP field_F8;
    Path_TLV* field_FC_pPathTLV;
    PathLine* field_100_pCollisionLine;
    __int16 field_104;
    __int16 field_106_current_state;
    __int16 field_108_delayed_state;
    __int16 field_10A;
    FP field_10C_health;
    int field_110_id;
    BitField16<Flags_114> field_114_flags;
};
#pragma pack(pop)
ALIVE_ASSERT_SIZEOF(BaseAliveGameObject, 0x116);

ALIVE_VAR_EXTERN(DynamicArrayT<BaseAliveGameObject>*, gBaseAliveGameObjects_5C1B7C);
