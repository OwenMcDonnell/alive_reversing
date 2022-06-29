#include "stdafx.h"
#include "WheelSyncer.hpp"
#include "Function.hpp"
#include "SwitchStates.hpp"
#include "Events.hpp"
#include "Map.hpp"
#include "stdlib.hpp"

WheelSyncer::WheelSyncer(Path_WheelSyncer* pTlv, u32 tlvInfo)
    : BaseGameObject(TRUE, 0)
{
    field_30_tlvInfo = tlvInfo;
    field_20_input_switch_id1 = pTlv->field_10_input_switch_id1;
    field_22_input_switch_id2 = pTlv->field_12_input_switch_id2;
    field_24_trigger_id = pTlv->field_14_output_switch_id;
    field_2E_output_requirement = pTlv->field_16_output_requirement;
    field_26_input_switch_id3 = pTlv->field_18_input_switch_id3;
    field_28_input_switch_id4 = pTlv->field_1A_input_switch_id4;
    field_2A_input_switch_id5 = pTlv->field_1C_input_switch_id5;
    field_2C_input_switch_id6 = pTlv->field_1E_input_switch_id6;
}

void WheelSyncer::VUpdate()
{
    const s32 state1 = SwitchStates_Get(field_20_input_switch_id1);
    const s32 state2 = SwitchStates_Get(field_22_input_switch_id2);
    const s32 state3 = SwitchStates_Get(field_26_input_switch_id3);
    const s32 state4 = SwitchStates_Get(field_28_input_switch_id4);
    const s32 state5 = SwitchStates_Get(field_2A_input_switch_id5);
    const s32 state6 = SwitchStates_Get(field_2C_input_switch_id6);

    s32 switchValue = 0;

    switch (field_2E_output_requirement)
    {
        case WheelSyncerOutputRequirement::eAllOn_0:
            if (!state1 || !state2 || !state3 || !state4 || !state5 || !state6)
            {
                switchValue = 0;
            }
            else
            {
                switchValue = 1;
            }
            break;

        case WheelSyncerOutputRequirement::e1OnAnd2Off_1:
            if (!state1 || state2)
            {
                switchValue = 0;
            }
            else
            {
                switchValue = 1;
            }
            break;

        case WheelSyncerOutputRequirement::e1Or2On_2:
            if (state1 || state2)
            {
                switchValue = 1;
            }
            else
            {
                switchValue = 0;
            }
            break;

        case WheelSyncerOutputRequirement::e1OnOr2Off_3:
            if (state1 || !state2)
            {
                switchValue = 1;
            }
            else
            {
                switchValue = 0;
            }
            break;

        default:
            switchValue = state5;
            break;
    }

    SwitchStates_Set(field_24_trigger_id, static_cast<s8>(switchValue));

    if (EventGet(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
}

WheelSyncer::~WheelSyncer()
{
    Path::TLV_Reset(field_30_tlvInfo, -1, 0, 0);
}

void WheelSyncer::VScreenChanged()
{
    if (gMap.mOverlayId != gMap.GetOverlayId())
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
}
