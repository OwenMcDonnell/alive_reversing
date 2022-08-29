#include "stdafx.h"
#include "LaughingGas.hpp"
#include "Function.hpp"
#include "SwitchStates.hpp"
#include "Game.hpp"
#include "../relive_lib/ScreenManager.hpp"
#include "stdlib.hpp"
#include "../relive_lib/PsxDisplay.hpp"
#include "PsxRender.hpp"
#include "../relive_lib/Events.hpp"
#include <math.h>

ALIVE_VAR(1, 0x5BC214, s32, gGasInstanceCount_5BC214, 0);
ALIVE_VAR(1, 0x5C1BA4, s16, gLaughingGasOn_5C1BA4, FALSE);

// On linux not using this random algorithm produces much bigger numbers
// which causes flickering in the gas rendering. Apparently this is the MSVC algorithm.
static s32 random_seed = 0;
static s32 gas_rand()
{
    random_seed = (random_seed * 214013 + 2531011) & 0xFFFFFFFF;
    return (random_seed >> 16) & 0x7FFF;
}

LaughingGas::LaughingGas(Layer layer, s32 /*notUsed*/, relive::Path_LaughingGas* pTlv, const Guid& tlvId)
    : BaseGameObject(TRUE, 0)
{
    gGasInstanceCount_5BC214++;

    SetType(ReliveTypes::eLaughingGas);
    Path_LaughingGas_Data* pData = &field_48_tlv_data;
    pData->field_0_bLaughing_gas = pTlv->mLaughingGas == relive::reliveChoice::eYes ? Choice_short::eYes_1 : Choice_short::eNo_0;
    pData->field_2_laughing_gas_switch_id = pTlv->mLaughingGasSwitchId;

    pData->field_4_red_percent = pTlv->mRedPercent;
    pData->field_6_blue_percent = pTlv->mBluePercent;
    pData->field_8_green_percent = pTlv->mBluePercent;


    if (field_48_tlv_data.field_0_bLaughing_gas == Choice_short::eYes_1)
    {
        field_36_bLaughing_gas = Choice_short::eYes_1;
    }
    else
    {
        field_36_bLaughing_gas = Choice_short::eNo_0;
    }

    if (SwitchStates_Get(field_48_tlv_data.field_2_laughing_gas_switch_id))
    {
        field_34_bEnabled = 1;
        field_54_amount_on = FP_FromInteger(1);
    }
    else
    {
        field_34_bEnabled = 0;
        field_54_amount_on = FP_FromInteger(0);
    }

    field_24_tlvInfo = tlvId;
    field_58_layer = layer;

    gObjListDrawables->Push_Back(this);
    mBaseGameObjectFlags.Set(BaseGameObject::eDrawable_Bit4);

    field_28_y = FP_GetExponent(FP_FromInteger(pTlv->mTopLeftY) - pScreenManager->CamYPos());
    field_2A_x = FP_GetExponent(PsxToPCX(FP_FromInteger(pTlv->mTopLeftX) - pScreenManager->CamXPos()));

    field_2C_h = FP_GetExponent(FP_FromInteger(pTlv->mBottomRightY) - pScreenManager->CamYPos());
    field_2E_w = FP_GetExponent(PsxToPCX(FP_FromInteger(pTlv->mBottomRightX) - pScreenManager->CamXPos()));

    field_31F8_w_count = (field_2E_w - field_2A_x) / 4;
    field_31FC_h_count = (field_2C_h - field_28_y + 2) / 2;

    field_19C_pMem = relive_new u16[field_31FC_h_count * field_31F8_w_count];

    Init();
    VUpdate();
}

LaughingGas::~LaughingGas()
{
    Path::TLV_Reset(field_24_tlvInfo, -1, 0, 0);
    gObjListDrawables->Remove_Item(this);
    gLaughingGasOn_5C1BA4 = FALSE;
    gGasInstanceCount_5BC214--;
    relive_delete[] field_19C_pMem;
}

void LaughingGas::VScreenChanged()
{
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
}

const f32 dword_551C58[7] = {1.0, 5.0, 10.0, 10.0, 5.0, 1.0, 0.0};

void LaughingGas::Init()
{
    for (s32 i = 0; i < field_31F8_w_count; i++)
    {
        const f32 v4 = (f32) i / (f32) field_31F8_w_count;
        f32 val1 = 1.0f;
        for (s32 j = 0; j < 7; j++)
        {
            field_1A0_x_data[i].array_4[j] = val1 * dword_551C58[j];
            val1 *= v4;
        }

        f32* pElem_ptr = &field_1A0_x_data[i].array_4[5];
        const f32 v1 = 1.0f - v4;
        f32 val2 = 1.0f;
        for (s32 j = 0; j < 6; j++)
        {
            const f32 calc2 = val2 * *pElem_ptr;
            *pElem_ptr = calc2;
            --pElem_ptr;
            val2 *= v1;
        }
    }

    for (s32 i = 0; i < field_31FC_h_count; i++)
    {
        const f32 v4 = (f32) i / (f32) field_31FC_h_count;
        f32 val1 = 1.0f;
        for (s32 j = 0; j < 7; j++)
        {
            field_24D0_y_data[i].array_4[j] = val1 * dword_551C58[j];
            val1 *= v4;
        }

        f32* pElem_ptr = &field_24D0_y_data[i].array_4[5];
        const f32 v1 = 1.0f - v4;
        f32 val2 = 1.0f;
        for (s32 j = 0; j < 6; j++)
        {
            const f32 calc2 = val2 * *pElem_ptr;
            *pElem_ptr = calc2;
            --pElem_ptr;
            val2 *= v1;
        }
    }

    for (s32 i = 0; i < 6; i++)
    {
        for (s32 j = 0; j < 6; j++)
        {
            field_10C_gas_x[i][j] = static_cast<f32>(gas_rand()) * 6.28f * (1.0f / 32767.0f);
        }
    }

    field_5C_prim.mPrimHeader.rgb_code.code_or_pad = PrimTypeCodes::eLaughingGas;
    field_5C_prim.x = field_2A_x;
    field_5C_prim.y = field_28_y;
    field_5C_prim.w = field_2E_w;
    field_5C_prim.h = field_2C_h;
    field_5C_prim.pData = field_19C_pMem;
}

void LaughingGas::VRender(PrimHeader** ppOt)
{
    if (field_54_amount_on > FP_FromDouble(0.1) || field_36_bLaughing_gas == Choice_short::eNo_0)
    {
        if (field_19C_pMem)
        {
            if (sbDisplayRenderFrame)
            {
                DoRender();
            }
            OrderingTable_Add(OtLayer(ppOt, field_58_layer), &field_5C_prim.mPrimHeader);
        }
        pScreenManager->InvalidateRectCurrentIdx(0, 0, gPsxDisplay.mWidth, gPsxDisplay.mHeight);
    }
}

void LaughingGas::DoRender()
{
    f32 local_array[6];

    u16* memPtr = field_19C_pMem;
    s32 rgb_base = (1 << sRedShift_C215C4) + (1 << sGreenShift_C1D180);

    if (field_36_bLaughing_gas == Choice_short::eNo_0)
    {
        rgb_base = (1 << sBlueShift_C19140) + (1 << sRedShift_C215C4) + (1 << sGreenShift_C1D180);
    }

    for (s32 yCount = 0; yCount < field_31FC_h_count; ++yCount)
    {
        for (s32 p = 0; p < 6; p++)
        {
            local_array[p] = Calc_Y(&field_7C_gas_y[p][0], yCount);
        }

        for (s32 xCount = 0; xCount < field_31F8_w_count; ++memPtr)
        {
            f32 yValue = Calc_X(local_array, xCount);
            if (yValue > 0.0f)
            {
                if (yValue >= 3.0f)
                {
                    if (yValue > 31.0f)
                    {
                        yValue = 31.0f;
                    }
                }
                else
                {
                    yValue = 3.0f;
                }
            }
            else
            {
                yValue = 0.0f;
            }

            *memPtr = static_cast<u16>(rgb_base * (static_cast<u8>(yValue) & 30));
            ++xCount;
        }
    }
}

s16 LaughingGas::CounterOver()
{
    return field_54_amount_on >= FP_FromDouble(0.3);
}

void LaughingGas::VUpdate()
{
    if (EventGet(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }

    if (SwitchStates_Get(field_48_tlv_data.field_2_laughing_gas_switch_id))
    {
        field_34_bEnabled = 1;
    }
    else
    {
        field_34_bEnabled = 0;
    }

    if (field_36_bLaughing_gas == Choice_short::eYes_1)
    {
        if (field_34_bEnabled)
        {
            if (field_54_amount_on < FP_FromInteger(1))
            {
                field_54_amount_on += FP_FromDouble(0.01);
            }
        }
        else
        {
            if (field_54_amount_on > FP_FromInteger(0))
            {
                field_54_amount_on -= FP_FromDouble(0.01);
            }
        }
    }

    if (field_36_bLaughing_gas == Choice_short::eYes_1)
    {
        gLaughingGasOn_5C1BA4 = 1;
        if (CounterOver())
        {
            sub_4328A0();
            return;
        }
    }

    gLaughingGasOn_5C1BA4 = 0;
    sub_4328A0();
}

f32 LaughingGas::Calc_X(f32* a2, s32 xIndex)
{
    f32 result = 0.0;
    f32* v4 = a2 + 1;

    for (s32 i = 0; i < 4; i++)
    {
        const f32 v5 = field_1A0_x_data[xIndex].array_4[i + 1];
        result += v5 * *v4;
        v4++;
    }

    return result;
}

f32 LaughingGas::Calc_Y(f32* a2, s32 yIndex)
{
    f32 result = 0.0;
    f32* v4 = a2 + 1;

    for (s32 i = 0; i < 4; i++)
    {
        const f32 v5 = field_24D0_y_data[yIndex].array_4[i + 1];
        result += v5 * *v4;
        v4++;
    }

    return result;
}

void LaughingGas::sub_4328A0()
{
    for (s32 i = 0; i < 4; i++)
    {
        for (s32 j = 0; j < 4; j++)
        {
            const s32 rnd = gas_rand() - 8191;
            field_7C_gas_y[1 + i][1 + j] = (sin(field_10C_gas_x[1 + i][1 + j]) * 50.0f + 30.0f) * static_cast<f32>(FP_GetDouble(field_54_amount_on));
            field_10C_gas_x[1 + i][1 + j] += (f32)(rnd) *0.03f * (1.0f / 16383.0f);
        }
    }
}
