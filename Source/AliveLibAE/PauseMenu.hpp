#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/Animation.hpp"
#include "Function.hpp"
#include "Font.hpp"
#include "../relive_lib/BaseAnimatedWithPhysicsGameObject.hpp"


class PauseMenu;
struct PauseMenuPage;

enum PauseMenuAlign
{
    Left = 0,
    Centre = 1,
    Right = 2,
};

struct PauseMenuPageEntry final
{
    s16 field_0_unknown2;
    s16 field_2_x;
    s16 y;
    s16 field_6_unknown;
    const char_type* field_8_text;
    u8 field_C_r;
    u8 field_D_g;
    u8 field_E_b;
    u8 field_F_alignment;
};
ALIVE_ASSERT_SIZEOF(PauseMenuPageEntry, 0x10);

class PauseMenu final : public ::BaseAnimatedWithPhysicsGameObject
{
public:
    struct PauseMenuPage;

    PauseMenu();
    ~PauseMenu();

    void LoadAnimations();

    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;
    virtual void VScreenChanged() override;

    void Init();

    void Page_Main_Update();
    void Page_Base_Render(PrimHeader** ot, PauseMenuPage* mp);

    void Page_ControlsActions_Update();
    void Page_ReallyQuit_Update();

    void Page_Save_Update();
    void Page_Save_Render(PrimHeader** ot, PauseMenuPage* pPage);

    void Page_Status_Update();
    void Page_Status_Render(PrimHeader** ot, PauseMenuPage* pPage);

    void Page_Load_Update();
    void Page_Load_Render(PrimHeader** ot, PauseMenuPage* mp);

    using t_PmPage_Update = decltype(&PauseMenu::Page_Main_Update);
    using t_PmPage_Render = decltype(&PauseMenu::Page_Base_Render);

    struct PauseMenuPage final
    {
        t_PmPage_Update field_0_fn_update;
        t_PmPage_Render field_4_fn_render;
        PauseMenuPageEntry* field_8_menu_items;
        s16 field_C_selected_index;
        s8 field_E_background_r;
        s8 field_F_background_g;
        s8 field_10_background_b;
        s8 field_11_padding;
        s8 field_12_padding;
        s8 field_13_padding;
    };
    ALIVE_ASSERT_SIZEOF(PauseMenu::PauseMenuPage, 0x14);

private:
    void RestartPath();

public:
    FontContext mFontContext;
    PalResource mPal;
    AliveFont field_F4_font = {};
    s16 word12C_flags = 0;
    s16 field_12E_selected_glow = 0;
    s16 field_130_selected_glow_counter = 0;

    enum MainPages : s16
    {
        ePage_Continue_0 = 0,
        ePage_QuickSave_1 = 1,
        ePage_Controls_2 = 2,
        ePage_Status_3 = 3,
        ePage_Save_4 = 4,
        ePage_Load_5 = 5,
        ePage_RestartPath_6 = 6,
        ePage_Quit_7 = 7,
    };

    /*MainPages*/ s16 field_134_index_main = 0;
    s16 field_138_control_action_page_index = 0;

    enum class SaveState : s16
    {
        ReadingInput_0 = 0,
        DoSave_4 = 4,
        SaveConfirmOverwrite_8 = 8,
    };
    SaveState field_13C_save_state = SaveState::ReadingInput_0;

    s16 field_142_poly_offset = 0;
    PauseMenu::PauseMenuPage field_144_active_menu = {};
    Animation field_158_animation = {};
    Prim_SetTPage field_1F0_primitives[2] = {};
    Poly_G4 field_210_polygons[2] = {};
};

extern PauseMenu* gPauseMenu;
extern bool gQuicksave_SaveNextFrame;
extern bool gQuicksave_LoadNextFrame;
extern u8 pauseMenuFontPal[32];
