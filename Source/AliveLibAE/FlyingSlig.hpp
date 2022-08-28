#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "BaseAliveGameObject.hpp"
#include "Path.hpp"
#include "FlyingSligSpawner.hpp"
#include "Sfx.hpp"

enum class LevelIds : s16;

class FlyingSlig;

using TFlyingSligBrainFn = void (FlyingSlig::*)(void);

#define FLYING_SLIG_MOTIONS_ENUM(ENTRY)         \
    ENTRY(M_Idle_0_4385E0)                      \
    ENTRY(M_HorizontalMovement_1_4386A0)        \
    ENTRY(M_IdleToTurn_2_4388B0)                \
    ENTRY(M_DownMovement_3_438AA0)              \
    ENTRY(M_DownMovementToTurn_4_438CC0)        \
    ENTRY(M_UpMovement_5_438DD0)                \
    ENTRY(M_UpMovementToTurn_6_439030)          \
    ENTRY(M_LeverPull_7_439150)                 \
    ENTRY(M_GameSpeak_8_4391D0)                 \
    ENTRY(M_Possession_9_434290)                \
    ENTRY(M_EndHorizontalMovement_10_4387D0)    \
    ENTRY(M_BeginUpMovement_11_438E40)          \
    ENTRY(M_HorizontalToDownMovement_12_438B10) \
    ENTRY(M_UpToHorizontalMovement_13_438F60)   \
    ENTRY(M_DownToHorizontalMovement_14_438BF0) \
    ENTRY(M_QuickTurn_15_4387F0)                \
    ENTRY(M_IdleToHorizontalMovement_16_438730) \
    ENTRY(M_BeginDownMovement_17_438B80)        \
    ENTRY(M_EndDownMovement_18_438C90)          \
    ENTRY(M_DownKnockback_19_4390D0)            \
    ENTRY(M_UpKnockback_20_439110)              \
    ENTRY(M_EndUpMovement_21_438EB0)            \
    ENTRY(M_InstantUpXTurn_22_438EE0)           \
    ENTRY(M_InstantDownXTurn_23_438F20)         \
    ENTRY(M_HorizontalToUpMovement_24_438D60)   \
    ENTRY(M_TurnToHorizontalMovement_25_4389E0)

#define MAKE_ENUM(VAR) VAR,
enum eFlyingSligMotions : s32
{
    FLYING_SLIG_MOTIONS_ENUM(MAKE_ENUM)
};

enum class SligSpeak : s8;

struct FlyingSlig_State final
{
    AETypes field_0_type;
    s16 field_2;
    FP field_4_xpos;
    FP field_8_ypos;
    FP field_C_velx;
    FP field_10_vely;
    s16 field_14_path_number;
    LevelIds field_16_lvl_number;
    FP field_18_sprite_scale;
    s16 field_1C_oldr;
    s16 field_1E_oldg;
    s16 field_20_oldb;
    s16 field_22_bAnimFlipX;
    s16 field_24_current_state;
    s16 field_26_current_frame;
    s16 field_28_frame_change_counter;
    u8 field_2A_bAnimRender;
    u8 field_2B_bDrawable;
    FP field_2C_current_health;
    s16 field_30_current_state;
    s16 field_32_delayed_state;
    s16 field_34_lastLineYPos;
    s16 field_36_line_idx;
    u8 field_38_launch_switch_id;
    u8 field_39_padding;
    enum Flags_3A
    {
        eBit1_bPossessed = 0x1,
        eBit2_Throw = 0x2,
        eBit3_bAlertedAndNotFacingAbe = 0x4,
        eBit4_DoAction = 0x8,
        eBit5_Chanting = 0x10,
        eBit6_Speaking_flag2 = 0x20,
        eBit7_Speaking_flag1 = 0x40,
        eBit8_bLastLine = 0x80,
        eBit9 = 0x100,
        eBit10 = 0x200,
        eBit11_padding = 0x400,
    };
    BitField16<Flags_3A> field_3A;
    s32 field_3C_tlvInfo;
    s32 field_40_timer;
    s32 field_44_grenade_delay;
    s32 field_48_collision_reaction_timer;
    FP field_4C_xSpeed;
    FP field_50_ySpeed;
    SligSpeak field_54_next_speak;
    s8 field_55_padding;
    s16 field_56_voice_pitch_min;
    s32 field_58_obj_id;
    FP field_5C;
    FP field_60;
    FP field_64;
    FP field_68_line_length;
    FP field_6C;
    FP field_70_lever_pull_range_xpos;
    FP field_74_lever_pull_range_ypos;
    s32 field_78_unused;
    s32 field_7C_unused;
    s32 field_80_unused;
    s32 field_84_unused;
    FP field_88_nextXPos;
    FP field_8C_nextYPos;
    s32 field_90_fns1_idx;
    s16 field_94_padding;
    s16 field_96_padding;
    s16 field_98_unused;
    LevelIds field_9A_abe_level;
    s16 field_9C_abe_path;
    s16 field_9E_abe_camera;
    s16 field_A0_bobbing_values_table_index;
    s16 field_A2_padding;
    s32 field_A4_bobbing_values_index;
    FP field_A8_bobbing_value;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(FlyingSlig_State, 0xAC);

class FlyingSlig final : public BaseAliveGameObject
{
public:
    FlyingSlig(relive::Path_FlyingSlig* pTlv, const TLVUniqueId& tlvId);
    ~FlyingSlig();

    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;
    virtual void VScreenChanged() override;
    virtual s16 VTakeDamage(BaseGameObject* pFrom) override;
    virtual void VPossessed() override;
    virtual void VSetMotion(s16 state) override;
    virtual s32 VGetSaveState(u8* pSaveBuffer) override;

    static s32 CreateFromSaveState(const u8* pBuffer);

private:
    s16 IsPossessed();
    void sub_4348A0();
    void Movement();

public:
    void Brain_0_Inactive();
    void Brain_1_Death();
    void Brain_2_Moving();
    void Brain_3_GetAlerted();
    void Brain_4_ChasingEnemy();
    void Brain_5_Idle();
    void Brain_6_GameSpeakToMoving();
    void Brain_7_PanicMoving();
    void Brain_8_PanicIdle();
    void Brain_9_SpottedEnemy();
    void Brain_10_LaunchingGrenade();
    void Brain_11_AbeDead();
    void Brain_12_Possessed();
    void Brain_13_Possession();
    void Brain_14_DePossession();
    void Brain_15_FlyingSligSpawn();
    void Brain_17_FromCrawlingSlig();

public:
    void M_Idle_0_4385E0();
    void M_HorizontalMovement_1_4386A0();
    void M_IdleToTurn_2_4388B0();
    void M_DownMovement_3_438AA0();
    void M_DownMovementToTurn_4_438CC0();
    void M_UpMovement_5_438DD0();
    void M_UpMovementToTurn_6_439030();
    void M_LeverPull_7_439150();
    void M_GameSpeak_8_4391D0();
    void M_Possession_9_434290();
    void M_EndHorizontalMovement_10_4387D0();
    void M_BeginUpMovement_11_438E40();
    void M_HorizontalToDownMovement_12_438B10();
    void M_UpToHorizontalMovement_13_438F60();
    void M_DownToHorizontalMovement_14_438BF0();
    void M_QuickTurn_15_4387F0();
    void M_IdleToHorizontalMovement_16_438730();
    void M_BeginDownMovement_17_438B80();
    void M_EndDownMovement_18_438C90();
    void M_DownKnockback_19_4390D0();
    void M_UpKnockback_20_439110();
    void M_EndUpMovement_21_438EB0();
    void M_InstantUpXTurn_22_438EE0();
    void M_InstantDownXTurn_23_438F20();
    void M_HorizontalToUpMovement_24_438D60();
    void M_TurnToHorizontalMovement_25_4389E0();

    s16 IsFacingMovementDirection_43A510();

public:
    void ToPlayerControlled_4360C0();
    void ToMoving_435720();
    void ToPanicIdle_435B50();
    void ToChase_435E10();
    s16 CanChase_436850(BaseAliveGameObject* pObj);
    void Say_436A50(SligSpeak speak, s16 pitch);
    s16 sub_4374A0(s16 a2);
    static s16 IsAbeEnteringDoor_43B030(BaseAliveGameObject* pThis);
    static bool IsWallBetween_43A550(BaseAliveGameObject* pThis, BaseAliveGameObject* pObj);
    void ThrowGrenade_43A1E0();
    void BlowUp_436510();
    s16 sub_436730();
    s16 CanHearAbe_4369C0();
    void ToSpottedEnemy_435E70();
    void ToAbeDead_436010();
    void ToAlerted_4357E0();
    void ToPanicMoving_435A50();
    s16 IsTurning_436AE0();
    u8** ResBlockForMotion_4350F0(s32 motion);
    void ToChantShake_436270();
    void ToPossesed_436130();
    void vUpdateAnimRes_4350A0();
    void PatrolDelay_435860();
    s16 CanThrowGrenade_43A490();
    void ToLaunchingGrenade_435F50();
    void HandlePlayerControls_439340();
    s16 sub_437C70(PathLine* pLine);
    ReliveTypes FindLeftOrRightBound_43B0A0(FP xOrY, FP wOrH);
    s16 sub_436C60(PSX_RECT* pRect, s16 op1);
    bool sub_436B20();
    void sub_4373B0();
    void vSetMotion_43B1B0(s16 newMotion);
    s16 CollisionUp_43A640(FP velY);
    s16 CollisionDown_43A9E0(FP velY);
    s16 CollisionLeftRight_43AC80(FP velX);
    void PullLever_436450();
    s16 TryPullLever_439DB0();
    void sub_437AC0(FP a2, FP_Point* pPoint);

    void SetBrain(TFlyingSligBrainFn fn);
    bool BrainIs(TFlyingSligBrainFn fn);

private:
    relive::Path_FlyingSlig field_118_data = {};
    TLVUniqueId field_148_tlvInfo = 0;
    s32 field_14C_timer = 0;
    s32 field_150_grenade_delay = 0;
    s32 field_154_collision_reaction_timer = 0;
    s32 field_158_obj_id = 0;
    s16 field_15C_voice_pitch_min = 0;
    s16 field_15E_useless = 0;
    s16 field_160_voice_pitch_min = 0;
    s32 field_164_unused = 0;
    s16 field_178_unused = 0;
    s16 field_17A_unused = 0;
    u8 field_17C_launch_switch_id = 0;
    SligSpeak field_17D_next_speak = SligSpeak::eHi_0;

    enum Flags_17E
    {
        eBit1_Speaking_flag1 = 0x1,
        eBit2_bLastLine = 0x2,
        eBit3 = 0x4,
        eBit4 = 0x8,
        eBit5_Throw = 0x10,
        eBit6_bAlertedAndNotFacingAbe = 0x20,
        eBit7_DoAction = 0x40,
        eBit8_Unused = 0x80,
        eBit9_Chanting = 0x100,
        eBit10_Speaking_flag2 = 0x200,
        eBit11_bNoPrevLine = 0x400,
        eBit12_bNoNextLine = 0x800,
        eBit13_Persistant = 0x1000,
    };
    BitField16<Flags_17E> field_17E_flags = {};
    ReliveTypes field_180_bound2 = ReliveTypes::eNone;
    ReliveTypes field_182_bound1 = ReliveTypes::eNone;
    FP field_184_xSpeed = {};
    FP field_188_ySpeed = {};
    FP field_18C = {};
    FP field_190 = {};
    FP field_194 = {};
    FP field_198_line_length = {};
    FP_Rect field_1A4_rect = {};
    FP field_1BC = {};
    FP field_1C0 = {};
    FP field_1C4 = {};
    FP field_1C8_lever_pull_range_xpos = {};
    FP field_1CC_lever_pull_range_ypos = {};
    s32 field_1D8_unused = 0;
    s32 field_1DC_unused = 0;
    s32 field_1E0_unused = 0;
    s32 field_1E4_unused = 0;
    s16 field_1E8_unused = 0;
    PathLine* field_1EC_pNextLine = nullptr;
    PathLine* field_1F0_pPrevLine = nullptr;
    s16 field_1F4_pPalAlloc[64] = {};
    PSX_RECT field_274_pal_rect = {};
    s16 field_27C_r = 0;
    s16 field_27E_g = 0;
    s16 field_280_b = 0;
    FP field_284_bobbing_value = {};
    const FP* field_288_unused = nullptr;
    s16 field_28C_bobbing_values_table_index = 0;
    s32 field_290_bobbing_values_index = 0;

public:
    FP field_294_nextXPos = {};
    FP field_298_nextYPos = {};
    TFlyingSligBrainFn field_29C_brain_state = nullptr;
    EReliveLevelIds field_2A0_abe_level = EReliveLevelIds::eNone;
    s16 field_2A2_abe_path = 0;
    s16 field_2A4_abe_camera = 0;
    FP field_2A8_max_x_speed = {};
    FP field_2AC_up_vel = {};
    FP field_2B0_down_vel = {};
    FP field_2B4_max_slow_down = {};
    FP field_2B8_max_speed_up = {};
};
ALIVE_ASSERT_SIZEOF(FlyingSlig, 0x2BC);
