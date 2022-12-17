cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

option(BEHAVIOUR_CHANGE_SUB_DATA_FOLDERS "Allow the game to load ddv and lvl files from their own folders. (movies, levels)" ON)
option(FORCE_DDCHEAT "Force ddcheat mode to be enabled" ON)
option(LCD_PS1_SPEED "Corrects LCD Screens to move as fast as the original PS1 version of the game." OFF)
option(USE_SDL2_SOUND "Use SDL2 for audio." ON)
option(USE_SDL2_IO "Use SDL2 for all File/Stream IO." ON)
option(AUTO_SWITCH_CONTROLLER "Automatically switches between keyboard/gamepad depending on what is connected." ON)
option(MISC_PC_MENU_FIXES "Small bug fixes and improvements for AO Load Menu, AO Keyboard Config Menu, and AE Controller Menu." ON)
option(ORIGINAL_PS1_BEHAVIOR "Fixes bugs in the PSX Emu layer / Gameplay to match PS1 version of the game." ON)
option(ORIGINAL_GAME_FIXES "Fixes ALL known gameplay bugs" ON)
option(ORIGINAL_GAME_FIX_AUTO_TURN "Fixes the auto-turn bug commonly used in speedruns" OFF)
option(ORIGINAL_GAME_FIX_DEATH_DELAY_AO "Fixes the death delay glitch commonly used in speedruns" OFF)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Source/relive_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Source/relive_lib/relive_config.h)
