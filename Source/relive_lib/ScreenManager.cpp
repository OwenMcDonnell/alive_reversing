#include "stdafx.h"
#include "ScreenManager.hpp"
#include "../AliveLibCommon/Function.hpp"
#include "VRam.hpp"
#include "../AliveLibAE/Renderer/IRenderer.hpp"
#include "../AliveLibCommon/CamDecompressor.hpp"
#include "../relive_lib/GameType.hpp"
#include "ResourceManagerWrapper.hpp"

ALIVE_VAR(1, 0x5BB5F4, ScreenManager*, pScreenManager, nullptr);
ALIVE_ARY(1, 0x5b86c8, SprtTPage, 300, sSpriteTPageBuffer, {});

void ScreenManager::sub_40EE10()
{
    for (s32 i = 0; i < 20; i++)
    {
        mDirtyBits[mYIdx].mData[i] |= mDirtyBits[mXIdx].mData[i];
    }
}

void ScreenManager::MoveImage()
{
    PSX_RECT rect = {};
    rect.x = mUPos;
    rect.y = mVPos;
    rect.h = 240;
    rect.w = 640;
    PSX_MoveImage(&rect, 0, 0);
}

void ScreenManager::InvalidateRect(s32 x, s32 y, s32 width, s32 height, s32 idx)
{
    x = std::max(x, 0);
    y = std::max(y, 0);

    width = std::min(width, 639);
    height = std::min(height, 239);

    for (s32 tileX = x / 32; tileX <= width / 32; tileX++)
    {
        for (s32 tileY = y / 16; tileY <= height / 16; tileY++)
        {
            mDirtyBits[idx].SetTile(tileX, tileY, true);
        }
    }
}

void ScreenManager::InvalidateRect_Layer3(s32 x, s32 y, s32 width, s32 height)
{
    InvalidateRect(x, y, width, height, Unknown_3);
}

void ScreenManager::InvalidateRect_IdxPlus4(s32 x, s32 y, s32 width, s32 height, s32 idx)
{
    InvalidateRect(x, y, width, height, idx + FG1_Half_Well_4);
}

void ScreenManager::InvalidateRectCurrentIdx(s32 x, s32 y, s32 width, s32 height)
{
    InvalidateRect(x, y, width, height, mIdx);
}

void ScreenManager::UnsetDirtyBits(s32 idx)
{
    memset(&mDirtyBits[idx], 0, sizeof(mDirtyBits[idx]));
}

void ScreenManager::UnsetDirtyBits_FG1()
{
    UnsetDirtyBits(FG1_Half_Well_4);
    UnsetDirtyBits(FG1_Half_5);
    UnsetDirtyBits(FG1_Well_6);
    UnsetDirtyBits(FG1_7);
}

s16 ScreenManager::IsDirty(s32 idx, s32 x, s32 y)
{
    return mDirtyBits[idx].GetTile(x / 32, y / 16);
}

const s32 kStripSize = 16;
const s32 kNumStrips = 640 / kStripSize;

void ScreenManager::DecompressCameraToVRam(CamResource& camRes)
{
    mCamRes = camRes;

    /*
    u16* pIter = *ppBits;
    for (s32 i = 0; i < kNumStrips; i++)
    {
        const u16 stripSize = *pIter;
        pIter++;

        const PSX_RECT rect = {static_cast<s16>(i * kStripSize), 256 + 16, kStripSize, 240};
        IRenderer::GetRenderer()->Upload(IRenderer::BitDepth::e8Bit, rect, reinterpret_cast<const u8*>(pIter));
        pIter += (stripSize / sizeof(u16));
    }
    */

    UnsetDirtyBits(0);
    UnsetDirtyBits(1);
    UnsetDirtyBits(2);
    UnsetDirtyBits(3);
}

ScreenManager::ScreenManager(CamResource& camRes, FP_Point* pCameraOffset)
    : BaseGameObject(TRUE, 0)
{
    mCamPos = pCameraOffset;

    mBaseGameObjectFlags.Set(BaseGameObject::eSurviveDeathReset_Bit9);
    mBaseGameObjectFlags.Set(BaseGameObject::eUpdateDuringCamSwap_Bit10);

    Init(camRes);
}

void ScreenManager::Init(CamResource& camRes)
{
    EnableRendering();

    SetType(ReliveTypes::eScreenManager);

    // TODO: Refactor out
    if (GetGameType() == GameType::eAo)
    {
        mCamXOff = 184;
        mCamYOff = 120;
    }

    mUPos = 0;
    mVPos = 272;
    mCamWidth = 640;
    mCamHeight = 240;

    Vram_alloc(0, 272, 640 - 1, 512 - 1);
    DecompressCameraToVRam(camRes);

    /*
    mScreenSprites = &sSpriteTPageBuffer[0];

    s16 xpos = 0;
    s16 ypos = 0;
    for (s32 i = 0; i < 300; i++)
    {
        SprtTPage* pItem = &mScreenSprites[i];
        Sprt_Init(&pItem->mSprt);
        SetRGB0(&pItem->mSprt, 128, 128, 128);
        SetXY0(&pItem->mSprt, xpos, ypos);

        pItem->mSprt.field_14_w = 32;
        pItem->mSprt.field_16_h = 16;

        s32 u0 = mUPos + 32 * (i % 20);
        s32 v0 = mVPos + 16 * (i / 20);
        s32 tpage = ScreenManager::GetTPage(TPageMode::e16Bit_2, TPageAbr::eBlend_0, &u0, &v0);

        tpage |= 0x8000;

        Init_SetTPage(&pItem->mTPage, 0, 0, tpage);

        SetUV0(&pItem->mSprt, static_cast<u8>(u0), static_cast<u8>(v0));

        xpos += 32;
        if (xpos == 640)
        {
            xpos = 0;
            ypos += 16;
        }
    }

    for (s32 i = 0; i < 8; i++)
    {
        UnsetDirtyBits(i);
    }
    */

    mIdx = Unknown_2;
    mYIdx = Unknown_1;
    mXIdx = Unknown_0;
}

void ScreenManager::VUpdate()
{
    // Empty
}

s32 ScreenManager::GetTPage(TPageMode tp, TPageAbr abr, s32* xpos, s32* ypos)
{
    const s16 clampedYPos = *ypos & 0xFF00;
    const s16 clampedXPos = *xpos & 0xFFC0;
    *xpos -= clampedXPos;
    *ypos -= clampedYPos;
    return PSX_getTPage(tp, abr, clampedXPos, clampedYPos);
}

ALIVE_VAR(1, 0x5BB5DC, SprtTPage*, pCurrent_SprtTPage_5BB5DC, nullptr);
ALIVE_VAR(1, 0x5bb5f0, s32, sCurrentYPos_5BB5F0, 0);
ALIVE_VAR(1, 0x5bb5d8, Layer, sIdx_5BB5D8, Layer::eLayer_0);

void ScreenManager::Render_Helper_40E9F0(s32 xpos, s32 ypos, Layer idx, s32 sprite_idx, PrimHeader** ppOt)
{
    if (IsDirty(mIdx, xpos, ypos) || IsDirty(mYIdx, xpos, ypos) || IsDirty(Unknown_3, xpos, ypos))
    {
        SprtTPage* pSprite = &mScreenSprites[sprite_idx];
        if (Y0(&pSprite->mSprt) != sCurrentYPos_5BB5F0 || sIdx_5BB5D8 != idx)
        {
            if (pCurrent_SprtTPage_5BB5DC)
            {
                OrderingTable_Add(OtLayer(ppOt, sIdx_5BB5D8), &pCurrent_SprtTPage_5BB5DC->mSprt.mBase.header);
                OrderingTable_Add(OtLayer(ppOt, sIdx_5BB5D8), &pCurrent_SprtTPage_5BB5DC->mTPage.mBase);
            }
            pSprite->mSprt.field_14_w = 32;
            pCurrent_SprtTPage_5BB5DC = pSprite;
            sIdx_5BB5D8 = idx;
            sCurrentYPos_5BB5F0 = Y0(&pSprite->mSprt);
        }
        else
        {
            pCurrent_SprtTPage_5BB5DC->mSprt.field_14_w += 32;
        }
    }
    else if (pCurrent_SprtTPage_5BB5DC)
    {
        OrderingTable_Add(OtLayer(ppOt, sIdx_5BB5D8), &pCurrent_SprtTPage_5BB5DC->mSprt.mBase.header);
        OrderingTable_Add(OtLayer(ppOt, sIdx_5BB5D8), &pCurrent_SprtTPage_5BB5DC->mTPage.mBase);
        pCurrent_SprtTPage_5BB5DC = nullptr;
        sCurrentYPos_5BB5F0 = -1;
    }
}

void ScreenManager::sub_40EE50()
{
    // NOTE: The algorithm calling Add_Dirty_Area_4ED970 has not been implemented
    // as its not actually used.

    mXIdx = mYIdx;
    mYIdx = mIdx;
    mIdx = (mIdx + 1) % 3;
    UnsetDirtyBits(mIdx);
}


void ScreenManager::VRender(PrimHeader** ppOt)
{
    if (mRenderingDisabled)
    {
        return;
    }

#if RENDERER_OPENGL
    // TODO: A custom sprite prim with magic numbers
    // to trigger proper order rendering of our cam.
    static Prim_Sprt MagicBackgroundPrim;
    Sprt_Init(&MagicBackgroundPrim);
    SetRGB0(&MagicBackgroundPrim, 255, 254, 253);
    OrderingTable_Add(OtLayer(ppOt, Layer::eLayer_1), &MagicBackgroundPrim.mBase.header);
#endif

    if (mCamRes.mData.mPixels)
    {
        PolyFT4_Init(&mPoly);

        SetXY0(&mPoly, 0, 0);
        SetXY1(&mPoly, 640, 0);
        SetXY2(&mPoly, 0, 240);
        SetXY3(&mPoly, 640, 240);
        SetRGB0(&mPoly, 127, 127, 127);
        OrderingTable_Add(OtLayer(ppOt, Layer::eLayer_1), &mPoly.mBase.header);
        mPoly.mCam = &mCamRes;
    }

    //PSX_DrawSync_4F6280(0);
    //pCurrent_SprtTPage_5BB5DC = nullptr;
    //sCurrentYPos_5BB5F0 = -1;

    /*
    for (s32 i = 0; i < 300; i++)
    {
        SprtTPage* pSpriteTPage = &mScreenSprites[i];
        const s32 spriteX = pSpriteTPage->mSprt.mBase.vert.x;
        const s32 spriteY = pSpriteTPage->mSprt.mBase.vert.y;

        if (IsDirty(FG1_7, spriteX, spriteY))
        {
            Render_Helper_40E9F0(spriteX, spriteY, Layer::eLayer_FG1_37, i, ppOt);
        }
        else if (IsDirty(FG1_Well_6, spriteX, spriteY))
        {
            Render_Helper_40E9F0(spriteX, spriteY, Layer::eLayer_Well_23, i, ppOt);
        }
        else if (IsDirty(FG1_Half_5, spriteX, spriteY))
        {
            Render_Helper_40E9F0(spriteX, spriteY, Layer::eLayer_FG1_Half_18, i, ppOt);
        }
        else if (IsDirty(FG1_Half_Well_4, spriteX, spriteY))
        {
            Render_Helper_40E9F0(spriteX, spriteY, Layer::eLayer_Well_Half_4, i, ppOt);
        }
        else if (IsDirty(mYIdx, spriteX, spriteY) || IsDirty(Unknown_3, spriteX, spriteY))
        {
            if (spriteY != sCurrentYPos_5BB5F0 || sIdx_5BB5D8 != Layer::eLayer_1)
            {
                AddCurrentSPRT_TPage(ppOt);
                pSpriteTPage->mSprt.field_14_w = 32;
                pCurrent_SprtTPage_5BB5DC = pSpriteTPage;
                sIdx_5BB5D8 = Layer::eLayer_1;
                sCurrentYPos_5BB5F0 = spriteY;
            }
            else
            {
                pCurrent_SprtTPage_5BB5DC->mSprt.field_14_w += 32;
            }
        }
        else
        {
            if (pCurrent_SprtTPage_5BB5DC)
            {
                AddCurrentSPRT_TPage(ppOt);
                pCurrent_SprtTPage_5BB5DC = nullptr;
                sCurrentYPos_5BB5F0 = -1;
            }
        }
    }

    AddCurrentSPRT_TPage(ppOt);

    sub_40EE50();

    for (s32 i = 0; i < 20; i++)
    {
        mDirtyBits[mYIdx].mData[i] |= mDirtyBits[Unknown_3].mData[i];
    }
    */

    UnsetDirtyBits(Unknown_3);
}

void ScreenManager::VScreenChanged()
{
    // Empty
}

void ScreenManager::AddCurrentSPRT_TPage(PrimHeader** ppOt)
{
    if (pCurrent_SprtTPage_5BB5DC)
    {
        OrderingTable_Add(OtLayer(ppOt, sIdx_5BB5D8), &pCurrent_SprtTPage_5BB5DC->mSprt.mBase.header);
        OrderingTable_Add(OtLayer(ppOt, sIdx_5BB5D8), &pCurrent_SprtTPage_5BB5DC->mTPage.mBase);
    }
}
