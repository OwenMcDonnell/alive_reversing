#include "stdafx.h"
#include "Text.hpp"
#include "../relive_lib/Function.hpp"
#include "stdlib.hpp"
#include "../relive_lib/PsxDisplay.hpp"
#include "Input.hpp"
#include "../relive_lib/Sound/Midi.hpp"
#include "../relive_lib/Sound/Sound.hpp"
#include "../relive_lib/Sys.hpp"
#include "GameAutoPlayer.hpp"
#include "../relive_lib/ResourceManagerWrapper.hpp"
#include "../relive_lib/GameObjects/BaseAnimatedWithPhysicsGameObject.hpp"

void Text::VUpdate()
{
    // Empty
}

void Text::VScreenChanged()
{
    // Empty
}

Text::Text(const char_type* pMessage, s32 renderCount, s32 bShadow)
    : BaseGameObject(true, 0)
{
    SetSurviveDeathReset(true);
    SetDrawable(true);

    SetType(ReliveTypes::eText);

    gObjListDrawables->Push_Back(this);

    mFontContext.LoadFontType(FontType::PauseMenu);
    mPal = ResourceManagerWrapper::LoadPal(PalId::MainMenuFont_PauseMenu);
    field_20_font.Load(static_cast<s32>((bShadow + 1) * strlen(pMessage)), mPal, &mFontContext);

    field_5C_xpos = static_cast<s16>(field_20_font.MeasureTextWidth(pMessage));
    field_5E_ypos = 0;

    field_58_k0_unused = 0; // never used?
    field_5A_k4_unused = 4; // never used?

    memcpy(field_68_txt_buffer, pMessage, strlen(pMessage) + 1);

    field_60_bShadow = static_cast<s16>(bShadow);
    field_64_render_count = renderCount;
}


Text::~Text()
{
    gObjListDrawables->Remove_Item(this);
    SetDrawable(false);
}

void Text::SetYPos(s32 /*not_used*/, s16 ypos)
{
    field_5E_ypos = ypos;
}

void Text::VRender(BasePrimitive** ppOt)
{
    const s16 ypos = field_5E_ypos + 100;
    const s32 xpos = (368 / 2) - (field_5C_xpos / 2);

    s32 drawRet1 = field_20_font.DrawString(
        ppOt,
        field_68_txt_buffer,
        xpos,
        ypos,
        relive::TBlendModes::eBlend_0,
        1,
        0,
        Layer::eLayer_Text_42,
        210,
        150,
        80,
        0,
        FP_FromDouble(1.0),
        640,
        0);

    // Draw again with offsets on x/y to create a shadow effect
    if (field_60_bShadow)
    {
        s32 drawRet2 = field_20_font.DrawString(
            ppOt,
            field_68_txt_buffer,
            xpos + 2,
            ypos + 2,
            relive::TBlendModes::eBlend_0,
            1,
            0,
            Layer::eLayer_Text_42,
            0,
            0,
            0,
            drawRet1,
            FP_FromDouble(1.0),
            640,
            0);

        field_20_font.DrawString(
            ppOt,
            field_68_txt_buffer,
            xpos - 1,
            ypos - 1,
            relive::TBlendModes::eBlend_0,
            1,
            0,
            Layer::eLayer_Text_42,
            0,
            0,
            0,
            drawRet2,
            FP_FromDouble(1.0),
            640,
            0);
    }

    if (field_64_render_count > 0)
    {
        field_64_render_count--;
        if (field_64_render_count <= 0)
        {
            SetDead(true);
        }
    }
}

// ResourceManager::vLoadFile_StateMachine_464A70 will call with type 0 (Displays Oddworld Abe's Exoddus.. but why?).
// Movie::vUpdate_4E0030 will call with type 1 which does nothing (trying to display movie skip message when it can't be found?).
// MainMenuController::LoadDemo_Update_4D1040 will call with type 2 (trying to display demo skip message when it can't be found?).
// MainMenuController::ChangeScreenAndIntroLogic_4CF640 will call with type 3 (Shown on boot, says Abe's Exoddus).

// TODO: When above functions are reversed clean up this function to remove strange dead cases..
s8 Display_Full_Screen_Message_Blocking(s32 /*not_used*/, MessageType messageType)
{
    if (messageType == MessageType::eSkipMovie_1)
    {
        return 0;
    }

    auto pTextObj = relive_new Text(messageType == MessageType::eShortTitle_3 ? "    Abe's Exoddus    " : "       Oddworld Abe's Exoddus        ", 1, 0);

    Text* pTextObj2 = nullptr;
    switch (messageType)
    {
        case MessageType::eLongTitle_0:
            // Never read ?
            //dword_55C128 = -1;
            break;

        case MessageType::eShortTitle_3:
            // Do nothing
            break;

        // Dead due to early return ??
        case MessageType::eSkipMovie_1:
            pTextObj2 = relive_new Text("or esc to skip the movie", 1, 0);
            if (pTextObj2)
            {
                pTextObj2->SetYPos(0, 30);
            }
            break;

        case MessageType::eSkipDemo_2:
            pTextObj2 = relive_new Text("or esc to skip the demo", 1, 0);
            if (pTextObj2)
            {
                pTextObj2->SetYPos(0, 30);
            }
            break;
    }

   // const PSX_RECT rect = {0, 0, 640, 240};
    //PSX_ClearImage_4F5BD0(&rect, 0, 0, 0);
    SYS_EventsPump();
    pTextObj->VRender(gPsxDisplay.mDrawEnvs[gPsxDisplay.mBufferIndex].mOrderingTable.mOrderingTable);

    if (pTextObj2)
    {
        pTextObj2->VRender(gPsxDisplay.mDrawEnvs[gPsxDisplay.mBufferIndex].mOrderingTable.mOrderingTable);
    }

    //Add_Dirty_Area_4ED970(0, 0, 640, 240);
    gDisplayRenderFrame = false;
    gPsxDisplay.RenderOrderingTable();

    if (SND_Seq_Table_Valid())
    {
        SND_StopAll();
    }

    u32 displayForMsecs = GetGameAutoPlayer().SysGetTicks() + 1000;

    if (messageType == MessageType::eShortTitle_3)
    {
        displayForMsecs += 4000;
    }

    if (GetGameAutoPlayer().IsRecording() || GetGameAutoPlayer().IsPlaying())
    {
        displayForMsecs = 200; // Get rid of these quickly for recordings
    }

    s8 bQuitViaEnterOrTimeOut = 1;
    if (GetGameAutoPlayer().SysGetTicks() < displayForMsecs)
    {
        bool waitReturn = true;
        while (!Input_IsVKPressed_4EDD40(VK_RETURN))
        {
            // User quit
            if (messageType != MessageType::eLongTitle_0 && Input_IsVKPressed_4EDD40(VK_ESCAPE))
            {
                bQuitViaEnterOrTimeOut = 0; // Nope, quitting via escape key

                // TODO: Never read?
                //dword_55C128 = sLevelId_dword_5CA408;

                // Wait for escape to come back up
                while (Input_IsVKPressed_4EDD40(VK_ESCAPE))
                {
                    SYS_EventsPump();
                }
                waitReturn = false;
                break;
            }

            SYS_EventsPump();

            if (GetGameAutoPlayer().SysGetTicks() >= displayForMsecs)
            {
                waitReturn = false;
                break;
            }
        }

        if (waitReturn)
        {
            // Wait for return to come back up, as we can only be here if it was pressed, didn't time out or escape wasn't pressed
            if (!GetGameAutoPlayer().IsRecording() && !GetGameAutoPlayer().IsPlaying())
            {
                while (Input_IsVKPressed_4EDD40(VK_RETURN))
                {
                    SYS_EventsPump();
                }
            }
        }
    }

    if (SND_Seq_Table_Valid())
    {
        GetSoundAPI().mSND_Restart();
    }

    SYS_EventsPump();

    gDisplayRenderFrame = false;
    gPsxDisplay.RenderOrderingTable();

    if (pTextObj)
    {
        gBaseGameObjects->Remove_Item(pTextObj);
        delete pTextObj;
    }

    if (pTextObj2)
    {
        gBaseGameObjects->Remove_Item(pTextObj2);
        delete pTextObj2;
    }

    return bQuitViaEnterOrTimeOut;
}
