#include "stdafx_ao.h"
#include "Function.hpp"
#include "ZapLine.hpp"
#include "stdlib.hpp"
#include "ResourceManager.hpp"
#include "Map.hpp"
#include "PsxDisplay.hpp"
#include "ScreenManager.hpp"
#include "Game.hpp"
#include "Math.hpp"

void ZapLine_ForceLink()
{ }

namespace AO {

ZapLine::~ZapLine()
{
    ResourceManager::FreeResource_455550(field_E8_ppRes);
    relive_delete[] field_128_sprite_positions;
    relive_delete[] field_12C_zap_points;
    relive_delete[] field_130_sprite_segment_positions;
}

ZapLine::ZapLine(FP x1, FP y1, FP x2, FP y2, s32 aliveTime, ZapLineType type, Layer layer)
{
    mBaseGameObjectTypeId = ReliveTypes::eZapLine;
    field_11A_type = type;

    AnimId animId = AnimId::None;
    if (field_11A_type == ZapLineType::eThin_1)
    {
        field_120_number_of_pieces_per_segment = 20;
        field_11E_number_of_segments = 12;
        animId = AnimId::Zap_Line_Blue;
        field_11C_tPageAbr = TPageAbr::eBlend_3;
    }
    else if (field_11A_type == ZapLineType::eThick_0)
    {
        field_120_number_of_pieces_per_segment = 10;
        field_11E_number_of_segments = 28;
        animId = AnimId::Zap_Line_Red;
        field_11C_tPageAbr = TPageAbr::eBlend_1;
    }

    const AnimRecord& rec = AO::AnimRec(animId);
    u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, rec.mResourceId, 1, 0);
    Animation_Init_417FD0(rec.mFrameTableOffset, rec.mMaxW, rec.mMaxH, ppRes, 1);

    mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Clear(AnimFlags::eBit15_bSemiTrans);
    mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = layer;
    field_122_number_of_sprites = field_11E_number_of_segments * field_120_number_of_pieces_per_segment;

    field_E8_ppRes = ResourceManager::Allocate_New_Locked_Resource(ResourceManager::Resource_Spline, 0, sizeof(ZapLineSprites) * field_122_number_of_sprites);
    field_124_pSprts = reinterpret_cast<ZapLineSprites*>(*field_E8_ppRes);

    field_128_sprite_positions = relive_new PSX_Point[field_122_number_of_sprites];
    field_12C_zap_points = relive_new ZapPoint[field_120_number_of_pieces_per_segment];
    field_130_sprite_segment_positions = relive_new FP_Point[field_11E_number_of_segments];

    field_118_max_alive_time = static_cast<s16>(aliveTime);

    mBaseAnimatedWithPhysicsGameObject_XPos = x1;
    mBaseAnimatedWithPhysicsGameObject_YPos = y1;

    field_E4_state = ZapLineState::eInit_0;
    field_116_alive_timer = 0;

    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit13_Is8Bit))
    {
        field_114_tPageMode = TPageMode::e8Bit_1;
    }
    else if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit14_Is16Bit))
    {
        field_114_tPageMode = TPageMode::e16Bit_2;
    }
    else
    {
        field_114_tPageMode = TPageMode::e4Bit_0;
    }

    u8 u0 = mBaseAnimatedWithPhysicsGameObject_Anim.mVramRect.x & 0x3F;
    if (field_114_tPageMode == TPageMode::e8Bit_1)
    {
        u0 = 2 * u0;
    }
    else if (field_114_tPageMode == TPageMode::e4Bit_0)
    {
        u0 = 4 * u0;
    }

    auto pFrameHeader = reinterpret_cast<FrameHeader*>(&(*mBaseAnimatedWithPhysicsGameObject_Anim.field_20_ppBlock)[mBaseAnimatedWithPhysicsGameObject_Anim.Get_FrameHeader(-1)->field_0_frame_header_offset]);

    const u8 frameW = pFrameHeader->field_4_width;
    const u8 frameH = pFrameHeader->field_5_height;

    for (s32 i = 0; i < 2; i++)
    {
        for (s32 j = 0; j < field_11E_number_of_segments; j++)
        {
            for (s32 k = 0; k < field_120_number_of_pieces_per_segment; k++)
            {
                Prim_Sprt* pSprt = &field_124_pSprts[(j * field_120_number_of_pieces_per_segment) + k].field_0_sprts[i];
                Sprt_Init(pSprt);

                Poly_Set_SemiTrans(&pSprt->mBase.header, 1);
                Poly_Set_Blending(&pSprt->mBase.header, 1);
                SetClut(pSprt, static_cast<s16>(PSX_getClut(
                                   mBaseAnimatedWithPhysicsGameObject_Anim.mPalVramXY.x,
                                   mBaseAnimatedWithPhysicsGameObject_Anim.mPalVramXY.y)));

                SetUV0(pSprt, u0, mBaseAnimatedWithPhysicsGameObject_Anim.mVramRect.y & 0xFF);
                pSprt->field_14_w = frameW - 1;
                pSprt->field_16_h = frameH - 1;
            }
        }
    }

    CalculateSourceAndDestinationPositions(x1, y1, x2, y2);
}

void ZapLine::CalculateSourceAndDestinationPositions(FP xPosSource, FP yPosSource, FP xPosDest, FP yPosDest)
{
    field_10C_x_position_source = FP_GetExponent(xPosSource - (pScreenManager->mCamPos->x - FP_FromInteger(pScreenManager->mCamXOff)));
    field_10E_y_position_source = FP_GetExponent(yPosSource - (pScreenManager->mCamPos->y - FP_FromInteger(pScreenManager->mCamYOff)));
    field_110_x_position_destination = FP_GetExponent(xPosDest - (pScreenManager->mCamPos->x - FP_FromInteger(pScreenManager->mCamXOff)));
    field_112_y_position_destination = FP_GetExponent(yPosDest - (pScreenManager->mCamPos->y - FP_FromInteger(pScreenManager->mCamYOff)));

    field_10C_x_position_source = PsxToPCX(field_10C_x_position_source, 11);
    field_110_x_position_destination = PsxToPCX(field_110_x_position_destination, 11);

    s16 xOff = 0;
    s16 yOff = 0;
    mBaseAnimatedWithPhysicsGameObject_Anim.Get_Frame_Offset(&xOff, &yOff);

    field_10C_x_position_source = FP_GetExponent(FP_FromInteger(xOff) + FP_FromInteger(field_10C_x_position_source));
    field_10E_y_position_source = FP_GetExponent(FP_FromInteger(yOff) + FP_FromInteger(field_10E_y_position_source));
    field_110_x_position_destination = FP_GetExponent(FP_FromInteger(xOff) + FP_FromInteger(field_110_x_position_destination));
    field_112_y_position_destination = FP_GetExponent(FP_FromInteger(yOff) + FP_FromInteger(field_112_y_position_destination));
}

void ZapLine::VScreenChanged()
{
    if (gMap.mOverlayId != gMap.GetOverlayId())
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
}

void ZapLine::VRender(PrimHeader** ppOt)
{
    if (gMap.Is_Point_In_Current_Camera(
            mBaseAnimatedWithPhysicsGameObject_LvlNumber,
            mBaseAnimatedWithPhysicsGameObject_PathNumber,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            0)
        && field_E4_state > ZapLineState::eInitSpriteVertices_2)
    {
        const auto bufferIdx = gPsxDisplay_504C78.field_A_buffer_index;

        for (s32 i = 0; i < field_11E_number_of_segments; i++)
        {
            for (s32 j = 0; j < field_120_number_of_pieces_per_segment; j++)
            {
                Prim_Sprt* pSprt = &field_124_pSprts->field_0_sprts[j + (i * field_120_number_of_pieces_per_segment)];
                OrderingTable_Add(OtLayer(ppOt, mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer), &pSprt[bufferIdx].mBase.header);
            }
        }

        const s32 calcTPage = PSX_getTPage(
            field_114_tPageMode,
            field_11C_tPageAbr,
            mBaseAnimatedWithPhysicsGameObject_Anim.mVramRect.x,
            mBaseAnimatedWithPhysicsGameObject_Anim.mVramRect.y & ~63); // TODO: Required ?

        Prim_SetTPage* pTPage = &field_EC_tPage_p8[bufferIdx];
        Init_SetTPage(pTPage, 0, 0, calcTPage);
        OrderingTable_Add(OtLayer(ppOt, mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer), &pTPage->mBase);

        PSX_RECT* pRect = &field_134_rects[bufferIdx];
        pRect->x = 32767;
        pRect->w = -32767;
        pRect->y = 32767;
        pRect->h = -32767;

        for (s32 i = 0; i < field_11E_number_of_segments; i++)
        {
            const PSX_Point* pPoint = &field_128_sprite_positions[i * field_120_number_of_pieces_per_segment];
            for (s32 j = 0; j < field_120_number_of_pieces_per_segment; j++)
            {
                if (pPoint->x < pRect->x)
                {
                    pRect->x = pPoint->x;
                }

                if (pPoint->x > pRect->w)
                {
                    pRect->w = pPoint->x;
                }

                if (pPoint->y < pRect->y)
                {
                    pRect->y = pPoint->y;
                }

                if (pPoint->y > pRect->h)
                {
                    pRect->h = pPoint->y;
                }
            }
        }

        pRect->x -= 25;
        pRect->w += 25;
        pRect->y -= 25;
        pRect->h += 25;
        const PSX_RECT* pRectToUse = &field_134_rects[gPsxDisplay_504C78.field_A_buffer_index];
        pScreenManager->InvalidateRect(
            pRectToUse->x,
            pRectToUse->y,
            pRectToUse->w,
            pRectToUse->h,
            pScreenManager->mIdx);
    }
}

void ZapLine::VUpdate()
{
    field_116_alive_timer++;

    switch (field_E4_state)
    {
        case ZapLineState::eInit_0:
            CalculateZapPoints_479380();

            if (field_11A_type == ZapLineType::eThin_1)
            {
                CalculateThinSpriteSegmentPositions();
            }
            else if (field_11A_type == ZapLineType::eThick_0)
            {
                CalculateThickSpriteSegmentPositions();
            }
            field_E4_state = ZapLineState::eInitSpritePositions_1;
            break;

        case ZapLineState::eInitSpritePositions_1:
            CalculateSpritePositionsOuter();
            field_E4_state = ZapLineState::eInitSpriteVertices_2;
            break;

        case ZapLineState::eInitSpriteVertices_2:
        case ZapLineState::eUpdateSpriteVertices_4:
            UpdateSpriteVertexPositions();

            if (field_116_alive_timer >= field_118_max_alive_time && field_11A_type != ZapLineType::eThin_1)
            {
                mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                return;
            }

            if (field_11A_type == ZapLineType::eThin_1)
            {
                CalculateThinSpriteSegmentPositions();
            }
            else if (field_11A_type == ZapLineType::eThick_0)
            {
                CalculateThickSpriteSegmentPositions();
            }
            field_E4_state = ZapLineState::eUpdateSpritePositions_3;
            break;

        case ZapLineState::eUpdateSpritePositions_3:
            CalculateSpritePositionsOuter();
            field_E4_state = ZapLineState::eUpdateSpriteVertices_4;
            break;
    }
}

void ZapLine::CalculateSpritePositionsOuter()
{
    for (s16 i = 0; i < field_11E_number_of_segments; i++)
    {
        if (i == 0)
        {
            // First item.
            CalculateSpritePositionsInner(0, 0, 1, 0);
        }
        else
        {
            const s16 lastIdx = field_11E_number_of_segments - 1;
            if (i == lastIdx)
            {
                // Last item.
                CalculateSpritePositionsInner(field_11E_number_of_segments - 2, lastIdx, lastIdx, field_11E_number_of_segments - 1);
            }
            else
            {
                // Other items.
                CalculateSpritePositionsInner(i - 1, i, i + 1, i);
            }
        }
    }
}

void ZapLine::CalculateZapPoints_479380()
{
    FP acc = FP_FromInteger(0);
    const FP delta = FP_FromInteger(1) / FP_FromInteger(field_120_number_of_pieces_per_segment);
    for (s32 i = 0; i < field_120_number_of_pieces_per_segment; i++)
    {
        const FP accSqrd = (acc * acc);
        field_12C_zap_points[i].field_0 = accSqrd - FP_FromRaw(2 * acc.fpValue) + FP_FromInteger(1);
        field_12C_zap_points[i].field_4 = -FP_FromRaw(2 * accSqrd.fpValue) + FP_FromRaw(2 * acc.fpValue) + FP_FromInteger(1);
        field_12C_zap_points[i].field_8 = accSqrd;
        acc += delta;
    }
}

void ZapLine::CalculateThinSpriteSegmentPositions()
{
    field_130_sprite_segment_positions[0].x = FP_FromInteger(field_10C_x_position_source);
    field_130_sprite_segment_positions[0].y = FP_FromInteger(field_10E_y_position_source);
    field_130_sprite_segment_positions[field_11E_number_of_segments - 1].x = FP_FromInteger(field_110_x_position_destination);
    field_130_sprite_segment_positions[field_11E_number_of_segments - 1].y = FP_FromInteger(field_112_y_position_destination);

    const FP x2Diff = FP_FromInteger(field_110_x_position_destination - field_10C_x_position_source) / FP_FromInteger(field_11E_number_of_segments);
    const FP y2Diff = FP_FromInteger(field_112_y_position_destination - field_10E_y_position_source) / FP_FromInteger(field_11E_number_of_segments);

    const FP y2DiffDiv = -y2Diff * FP_FromDouble(0.1);
    const FP x2DiffDiv = x2Diff * FP_FromDouble(0.1);

    for (s32 i = 1; i < field_11E_number_of_segments - 1; i++)
    {
        const FP rnd = FP_FromInteger(Math_NextRandom() % 32 - 16);
        field_130_sprite_segment_positions[i].x = (y2DiffDiv * rnd) + FP_FromInteger(field_10C_x_position_source) + (FP_FromInteger(i) * x2Diff);
        field_130_sprite_segment_positions[i].y = (x2DiffDiv * rnd) + FP_FromInteger(field_10E_y_position_source) + (FP_FromInteger(i) * y2Diff);
    }
}

void ZapLine::CalculateThickSpriteSegmentPositions()
{
    s32 v1 = 0;
    if (field_116_alive_timer >= 8)
    {
        const s32 v4 = field_118_max_alive_time - field_116_alive_timer;
        if (v4 >= 8)
        {
            v1 = 4;
        }
        else
        {
            v1 = (v4 / 4) + 3;
        }
    }
    else
    {
        v1 = (field_116_alive_timer / 4) + 3;
    }

    s32 v5 = 1 << v1;
    s32 v6 = 1 << (v1 - 1);

    field_130_sprite_segment_positions[0].x = FP_FromInteger(field_10C_x_position_source);
    field_130_sprite_segment_positions[0].y = FP_FromInteger(field_10E_y_position_source);

    field_130_sprite_segment_positions[field_11E_number_of_segments - 1].x = FP_FromInteger(field_110_x_position_destination);
    field_130_sprite_segment_positions[field_11E_number_of_segments - 1].y = FP_FromInteger(field_112_y_position_destination);

    s32 angExtra = 0;
    if ((sGnFrame / 8) & 1)
    {
        angExtra = 0;
    }
    else
    {
        angExtra = 128;
    }

    const FP xDiff = FP_FromInteger(field_110_x_position_destination - field_10C_x_position_source) / FP_FromInteger(field_11E_number_of_segments);
    const FP xDiffDiv = (xDiff * FP_FromDouble(1.5));

    const FP yDiff = FP_FromInteger(field_112_y_position_destination - field_10E_y_position_source) / FP_FromInteger(field_11E_number_of_segments);
    const FP yDiffDiv = (-yDiff * FP_FromDouble(1.5));

    for (s32 i = 1; i < field_11E_number_of_segments - 1; i++)
    {
        const u8 ang = static_cast<u8>(angExtra + 18 * i);

        field_130_sprite_segment_positions[i].x = FP_FromInteger(Math_NextRandom() % v5) + (Math_Cosine_4510A0(ang) * yDiffDiv) + FP_FromInteger(field_10C_x_position_source) + (FP_FromInteger(i) * xDiff) - FP_FromInteger(v6);

        field_130_sprite_segment_positions[i].y = FP_FromInteger(Math_NextRandom() % v5) + (Math_Cosine_4510A0(ang) * xDiffDiv) + FP_FromInteger(field_10E_y_position_source) + (FP_FromInteger(i) * yDiff) - FP_FromInteger(v6);
    }

    field_134_rects[0].x = 0;
    field_134_rects[0].y = 0;
    field_134_rects[0].w = gPsxDisplay_504C78.field_0_width;
    field_134_rects[0].h = gPsxDisplay_504C78.field_2_height;

    field_134_rects[1].x = 0;
    field_134_rects[1].y = 0;
    field_134_rects[1].w = gPsxDisplay_504C78.field_0_width;
    ;
    field_134_rects[1].h = gPsxDisplay_504C78.field_2_height;
}

void ZapLine::UpdateSpriteVertexPositions()
{
    for (s32 i = 0; i < field_11E_number_of_segments; i++)
    {
        for (s32 j = 0; j < field_120_number_of_pieces_per_segment; j++)
        {
            const auto pPoint = &field_128_sprite_positions[j + (i * field_120_number_of_pieces_per_segment)];
            Prim_Sprt* pSprt = &field_124_pSprts->field_0_sprts[j + (i * field_120_number_of_pieces_per_segment)];
            SetXY0(&pSprt[0], pPoint->x, pPoint->y);
            SetXY0(&pSprt[1], pPoint->x, pPoint->y);
        }
    }
}

void ZapLine::CalculateSpritePositionsInner(s32 idx1, s32 idx2, s32 idx3, s16 idx4)
{
    const FP x1 = field_130_sprite_segment_positions[idx1].x;
    const FP y1 = field_130_sprite_segment_positions[idx1].y;

    const FP x2 = field_130_sprite_segment_positions[idx2].x;
    const FP y2 = field_130_sprite_segment_positions[idx2].y;

    const FP x3 = field_130_sprite_segment_positions[idx3].x;
    const FP y3 = field_130_sprite_segment_positions[idx3].y;

    for (s32 i = 0; i < field_120_number_of_pieces_per_segment; i++)
    {
        auto pItem = &field_128_sprite_positions[i + (idx4 * field_120_number_of_pieces_per_segment)];

        pItem->x = FP_GetExponent(
            FP_FromRaw((
                           (field_12C_zap_points[i].field_8 * x3) + (field_12C_zap_points[i].field_4 * x2) + (field_12C_zap_points[i].field_0 * x1))
                           .fpValue
                       >> 1));

        pItem->y = FP_GetExponent(
            FP_FromRaw((
                           (field_12C_zap_points[i].field_8 * y3) + (field_12C_zap_points[i].field_4 * y2) + (field_12C_zap_points[i].field_0 * y1))
                           .fpValue
                       >> 1));
    }
}

} // namespace AO
