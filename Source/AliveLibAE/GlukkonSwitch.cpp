#include "stdafx.h"
#include "GlukkonSwitch.hpp"
#include "Function.hpp"
#include "Game.hpp"
#include "stdlib.hpp"
#include "Abe.hpp"
#include "Events.hpp"
#include "Sound/Midi.hpp"
#include "Glukkon.hpp"
#include "Sfx.hpp"
#include "SwitchStates.hpp"
#include "GameSpeak.hpp"

GlukkonSwitch::GlukkonSwitch(Path_GlukkonSwitch* pTlv, s32 tlvInfo)
    : BaseAnimatedWithPhysicsGameObject(0)
{
    field_100_last_event_idx = -1;
    field_114 = 0;
    field_116 = -1;

    SetType(ReliveTypes::eHelpPhone);

    const AnimRecord& rec = AnimRec(AnimId::Security_Door_Idle);
    u8** ppRes = Add_Resource(ResourceManager::Resource_Animation, rec.mResourceId);
    Animation_Init(rec.mFrameTableOffset, rec.mMaxW, rec.mMaxH, ppRes, 1, 1);

    mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
    field_F4_tlvInfo = tlvInfo;
    mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_BeforeWell_22;

    if (pTlv->field_10_scale == Path_GlukkonSwitch::Scale::eFull_1)
    {
        mBaseAnimatedWithPhysicsGameObject_SpriteScale = FP_FromInteger(1);
        mBaseAnimatedWithPhysicsGameObject_Scale = Scale::Fg;
    }
    else if (pTlv->field_10_scale == Path_GlukkonSwitch::Scale::eHalf_0)
    {
        mBaseAnimatedWithPhysicsGameObject_SpriteScale = FP_FromDouble(0.5);
        mBaseAnimatedWithPhysicsGameObject_Scale = Scale::Bg;
    }

    field_FA_ok_switch_id = pTlv->field_12_ok_switch_id;
    field_FC_fail_switch_id = pTlv->field_14_fail_switch_id;
    field_118_top_left = pTlv->field_8_top_left;
    field_11C_bottom_right = pTlv->field_C_bottom_right;

    mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(pTlv->field_16_xpos);
    mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(pTlv->field_18_ypos);

    PSX_Point pos = {};
    gMap.Get_Abe_Spawn_Pos(&pos);
    if (mBaseAnimatedWithPhysicsGameObject_XPos > FP_FromInteger(0))
    {
        mBaseAnimatedWithPhysicsGameObject_XPos -= FP_FromInteger(pos.field_0_x);
    }
    else
    {
        mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger((pTlv->field_8_top_left.field_0_x + pTlv->field_C_bottom_right.field_0_x) / 2);
    }

    if (mBaseAnimatedWithPhysicsGameObject_YPos > FP_FromInteger(0))
    {
        mBaseAnimatedWithPhysicsGameObject_YPos -= FP_FromInteger(pos.field_2_y);
    }
    else
    {
        mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger((pTlv->field_8_top_left.field_2_y + pTlv->field_C_bottom_right.field_2_y) / 2);
    }

    if (pTlv->field_1_tlv_state)
    {
        field_F8_state = pTlv->field_1_tlv_state - 1;
    }
    else
    {
        field_F8_state = 0;
    }

    if (field_F8_state != 1)
    {
        field_120_timer = sGnFrame + 10;
    }
}

GlukkonSwitch::~GlukkonSwitch()
{
    Path::TLV_Reset(field_F4_tlvInfo, -1, 0, 0);
}

void GlukkonSwitch::VScreenChanged()
{
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
}

s16 GlukkonSwitch::PlayerNearMe()
{
    const s16 playerXPos = FP_GetExponent(sControlledCharacter_5C1B8C->mBaseAnimatedWithPhysicsGameObject_XPos);
    const s16 playerYPos = FP_GetExponent(sControlledCharacter_5C1B8C->mBaseAnimatedWithPhysicsGameObject_YPos);

    if ((playerXPos >= field_118_top_left.field_0_x && playerXPos <= field_11C_bottom_right.field_0_x) && (playerYPos >= field_118_top_left.field_2_y && playerYPos <= field_11C_bottom_right.field_2_y))
    {
        return 1;
    }

    return 0;
}

void GlukkonSwitch::VUpdate()
{
    if (Event_Get(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }

    const s32 lastEventIdx = pEventSystem_5BC11C->field_28_last_event_index;
    GameSpeakEvents lastEventIdx2 = GameSpeakEvents::eNone_m1;
    if (field_100_last_event_idx == lastEventIdx)
    {
        if (pEventSystem_5BC11C->field_20_last_event == GameSpeakEvents::eNone_m1)
        {
            lastEventIdx2 = GameSpeakEvents::eNone_m1;
        }
        else
        {
            lastEventIdx2 = GameSpeakEvents::eSameAsLast_m2;
        }
    }
    else
    {
        field_100_last_event_idx = lastEventIdx;
        lastEventIdx2 = pEventSystem_5BC11C->field_20_last_event;
    }

    switch (field_F8_state)
    {
        case 0:
            if (static_cast<s32>(sGnFrame) <= field_120_timer)
            {
                return;
            }

            if (PlayerNearMe())
            {
                mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Set(AnimFlags::eBit3_Render);
                field_F8_state = 2;
            }
            else
            {
                mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
            }
            return;

        case 1:
            if (static_cast<s32>(sGnFrame) == field_120_timer)
            {
                SND_SEQ_Play(SeqId::SaveTriggerMusic_31, 1, 127, 127);
            }
            else if (static_cast<s32>(sGnFrame) > field_120_timer && !PlayerNearMe())
            {
                field_F8_state = 0;
            }
            return;

        case 2:
        {
            Glukkon::PlaySound_GameSpeak(GlukkonSpeak::Hey_0, 127, -200, 0);
            const AnimRecord& animRec = AnimRec(AnimId::Security_Door_Speak);
            mBaseAnimatedWithPhysicsGameObject_Anim.Set_Animation_Data(animRec.mFrameTableOffset, nullptr);
            field_F8_state = 3;
            field_120_timer = sGnFrame + 150;
            return;
        }
        case 3:
            if (!PlayerNearMe())
            {
                field_F8_state = 0;
                field_120_timer = sGnFrame - 1;
                return;
            }

            if (lastEventIdx2 == GameSpeakEvents::eNone_m1 || lastEventIdx2 == GameSpeakEvents::eSameAsLast_m2)
            {
                if (static_cast<s32>(sGnFrame) > field_120_timer)
                {
                    field_F8_state = 0;
                }
            }
            else
            {
                if (lastEventIdx2 == GameSpeakEvents::Glukkon_Hey_36)
                {
                    field_F8_state = 4;
                    field_120_timer = sGnFrame + 30;
                }
                else
                {
                    if (lastEventIdx2 < GameSpeakEvents::Glukkon_Hey_36)
                    {
                        field_F8_state = 8;
                        field_120_timer = sGnFrame + 30;
                    }

                    if (static_cast<s32>(sGnFrame) > field_120_timer)
                    {
                        field_F8_state = 0;
                    }
                }
            }
            return;

        case 4:
        {
            if (static_cast<s32>(sGnFrame) <= field_120_timer)
            {
                return;
            }
            Glukkon::PlaySound_GameSpeak(GlukkonSpeak::What_11, 127, -200, 0);
            const AnimRecord& animRec = AnimRec(AnimId::Security_Door_Speak);
            mBaseAnimatedWithPhysicsGameObject_Anim.Set_Animation_Data(animRec.mFrameTableOffset, nullptr);
            field_F8_state = 5;
            field_120_timer = sGnFrame + 60;
            return;
        }
        case 5:
            if (PlayerNearMe())
            {
                if (lastEventIdx2 == GameSpeakEvents::eNone_m1 || lastEventIdx2 == GameSpeakEvents::eSameAsLast_m2)
                {
                    if (static_cast<s32>(sGnFrame) > field_120_timer)
                    {
                        field_F8_state = 7;
                        field_120_timer = sGnFrame + 15;
                    }
                }
                else if (lastEventIdx2 == GameSpeakEvents::Glukkon_DoIt_37)
                {
                    field_F8_state = 6;
                    field_120_timer = sGnFrame + 30;
                }
                else if (lastEventIdx2 < GameSpeakEvents::Glukkon_Hey_36)
                {
                    field_F8_state = 8;
                    field_120_timer = sGnFrame + 30;
                }
                else
                {
                    field_F8_state = 7;
                    field_120_timer = sGnFrame + 15;
                }
            }
            else
            {
                field_F8_state = 0;
                field_120_timer = sGnFrame - 1;
            }
            return;

        case 6:
        {
            if (static_cast<s32>(sGnFrame) != field_120_timer)
            {
                return;
            }
            SFX_Play_Pitch(SoundEffect::GlukkonSwitchBleh_88, 127, -700); //Bleh!
            Glukkon::PlaySound_GameSpeak(GlukkonSpeak::Laugh_7, 127, -200, 0);
            const AnimRecord& animRec = AnimRec(AnimId::Security_Door_Speak);
            mBaseAnimatedWithPhysicsGameObject_Anim.Set_Animation_Data(animRec.mFrameTableOffset, nullptr);
            SwitchStates_Do_Operation(field_FA_ok_switch_id, SwitchOp::eToggle_2);
            field_F8_state = 1;
            field_120_timer = sGnFrame + 15;
            return;
        }
        case 7:
        {
            if (static_cast<s32>(sGnFrame) != field_120_timer)
            {
                return;
            }
            Glukkon::PlaySound_GameSpeak(GlukkonSpeak::Heh_5, 127, -200, 0);
            const AnimRecord& animRec = AnimRec(AnimId::Security_Door_Speak);
            mBaseAnimatedWithPhysicsGameObject_Anim.Set_Animation_Data(animRec.mFrameTableOffset, nullptr);
            field_F8_state = 0;
            field_120_timer = sGnFrame + 90;
            return;
        }
        case 8:
        {
            if (static_cast<s32>(sGnFrame) != field_120_timer)
            {
                return;
            }
            Glukkon::PlaySound_GameSpeak(GlukkonSpeak::Heh_5, 127, -200, 0);
            const AnimRecord& animRec = AnimRec(AnimId::Security_Door_Speak);
            mBaseAnimatedWithPhysicsGameObject_Anim.Set_Animation_Data(animRec.mFrameTableOffset, nullptr);
            SwitchStates_Do_Operation(field_FC_fail_switch_id, SwitchOp::eSetTrue_0);
            field_F8_state = 0;
            field_120_timer = sGnFrame + 90;
            return;
        }
        default:
            return;
    }
}
