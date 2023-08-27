#pragma once

#include "Types.hpp"
#include "StringHashCollection.hpp"

class ReliveTypes final : public StringHashCollection
{
public:
    // internal types
    static inline constexpr StringHash eNone{"none"};
    static inline constexpr StringHash eScreenManager{"screen_manager"};
    static inline constexpr StringHash eBullet{"bullet"};
    static inline constexpr StringHash eDDCheat{"dd_cheat"};
    static inline constexpr StringHash eBells{"bells"};
    static inline constexpr StringHash eZapSpark{"zap_spark"};
    static inline constexpr StringHash eParticleBurst{"particle_burst"};
    static inline constexpr StringHash eGameSpeak{"game_speak"};
    static inline constexpr StringHash ePalOverwriter{"pal_overwriter"};
    static inline constexpr StringHash eGroundExplosion{"ground_explosion"};
    static inline constexpr StringHash eRockSpawner{"rock_spawner"};
    static inline constexpr StringHash eThrowableTotalIndicator{"throwable_total_indicator"};
    static inline constexpr StringHash eGameEnderController{"game_ender_controller"};
    static inline constexpr StringHash eDeathBird{"death_bird"};
    static inline constexpr StringHash eLoadingFile{"loading_file"};
    static inline constexpr StringHash eGrenade{"grenade"};
    static inline constexpr StringHash eAbe{"abe"};
    static inline constexpr StringHash MainMenuFade{"main_menu_fade"};
    static inline constexpr StringHash eClawOrBirdPortalTerminator{"claw_or_bird_portal_terminator"};
    static inline constexpr StringHash eRingOrLiftMud{"ring_or_lift_mud"};
    static inline constexpr StringHash eMeat{"meat"};
    static inline constexpr StringHash eRollingBallStopperShaker{"rolling_ball_stopper_shaker"};
    static inline constexpr StringHash ePauseMenu{"pause_menu"};
    static inline constexpr StringHash eDemoPlayback{"demo_playback"};
    static inline constexpr StringHash eBirdPortalTerminator{"bird_portal_terminator"};
    static inline constexpr StringHash eFG1{"fg1"};
    static inline constexpr StringHash eAbilityRing{"ability_ring"};
    static inline constexpr StringHash eRock{"rock"};
    static inline constexpr StringHash eRope{"rope"};
    static inline constexpr StringHash eAirExplosion{"air_explosion"};
    static inline constexpr StringHash eRedLaser{"red_laser"};
    static inline constexpr StringHash eScreenClipper{"screen_clipper"};
    static inline constexpr StringHash eEffectBase{"effect_base"};
    static inline constexpr StringHash eFade{"fade"};
    static inline constexpr StringHash eFlash{"flash"};
    static inline constexpr StringHash ScreenShake{"screen_shake_ao"}; // TODO: rename to eScreenShake
    static inline constexpr StringHash eScreenWave{"screen_wave"};
    static inline constexpr StringHash eUnknown{"unknown"}; // TODO: remove?
    static inline constexpr StringHash eShrykull{"shrykull"};
    static inline constexpr StringHash eSnoozParticle{"snoozparticle"};
    static inline constexpr StringHash SlingMud{"sling_mud"};
    static inline constexpr StringHash eParticle{"particle"};
    static inline constexpr StringHash eZapLine{"zap_line"};
    static inline constexpr StringHash eBeeSwarm{"bee_swarm"};
    static inline constexpr StringHash eMovie{"movie"};
    static inline constexpr StringHash eCameraSwapper{"camera_swapper"};
    static inline constexpr StringHash eElectrocute{"electrocute"};
    static inline constexpr StringHash eTimedMine_or_MovingBomb{"timed_mine_or_moving_bomb"};
    static inline constexpr StringHash eBone{"bone"};
    static inline constexpr StringHash eSligButton{"slig_button"};
    static inline constexpr StringHash eMetal{"metal"};
    static inline constexpr StringHash eMinesAlarm{"mines_alarm"};
    static inline constexpr StringHash eDoorLock{"door_lock"};
    static inline constexpr StringHash eEvilFart{"evil_fart"};
    static inline constexpr StringHash ePossessionFlicker{"possession_flicker"};
    static inline constexpr StringHash eSlapLock_OrbWhirlWind{"slap_lock_orb_whirl_wind"};
    static inline constexpr StringHash eHelpPhone{"help_phone"};
    static inline constexpr StringHash eEyeOrbPart{"eye_orb_part"};
    static inline constexpr StringHash eInvisibleEffect{"invisible_effect"};
    static inline constexpr StringHash ePulley{"pulley"};
    static inline constexpr StringHash eResourceManager{"resource_manager"};
    static inline constexpr StringHash eSligGetPantsOrWings{"slig_get_pants_or_wings"};
    static inline constexpr StringHash eText{"text"};
    static inline constexpr StringHash eGreeterBody{"greeter_body"};
    static inline constexpr StringHash eMusicController{"music_controller"};
    static inline constexpr StringHash eMainMenuTransistion{"main_menu_transition"}; // TODO: fix typo later
    static inline constexpr StringHash eScreenShake{"screen_shake_ae"};
    static inline constexpr StringHash eSnoozeParticle{"snooze_particle"}; // TODO: fix typo later and merge eSnoozeParticle/eSnoozParticle
    static inline constexpr StringHash eWebLine{"web_line"};
    static inline constexpr StringHash eDeathDrop{"death_drop"};
    static inline constexpr StringHash eInvisibleZone{"invisible_zone"};
    static inline constexpr StringHash eContinuePoint{"continue_point"};
    static inline constexpr StringHash eBirdPortalExit{"bird_portal_exit"};
    static inline constexpr StringHash eSoftLanding{"soft_landing"};
    static inline constexpr StringHash eSligPersist{"slig_persist"};
    static inline constexpr StringHash eElumStart{"elum_start"};
    static inline constexpr StringHash eStartController{"start_controller"};
    static inline constexpr StringHash eScrabNoFall{"scrab_no_fall"};
    static inline constexpr StringHash eScrabLeftBound{"scrab_left_bound"};
    static inline constexpr StringHash eScrabRightBound{"scrab_right_bound"};
    static inline constexpr StringHash eHoneyDripTarget{"honey_drip_target"};
    static inline constexpr StringHash eZSligCover{"z_slig_cover"};
    static inline constexpr StringHash eResetPath{"reset_path"};
    static inline constexpr StringHash ePathTransition{"path_transition"};
    static inline constexpr StringHash eEnemyStopper{"enemy_stopper"};
    static inline constexpr StringHash eMovingBombStopper{"moving_bomb_stopper"};
    static inline constexpr StringHash eElumPathTrans{"elum_path_trans"};
    static inline constexpr StringHash eMudokonPathTrans{"mudokon_path_trans"};
    static inline constexpr StringHash eThrowableArray{"throwable_array"};
    static inline constexpr StringHash eWell{"well"};
    
    // objects with factory funcs
    static inline constexpr StringHash eHoist{"hoist"};
    static inline constexpr StringHash eEdge{"edge"};
    static inline constexpr StringHash eDoor{"door"};
    static inline constexpr StringHash eShadowZone{"shadow_zone"};
    static inline constexpr StringHash eLiftPoint{"lift_point"};
    static inline constexpr StringHash eWellExpress{"well_express"};
    static inline constexpr StringHash eWellLocal{"well_local"};
    static inline constexpr StringHash eDove{"dove"};
    static inline constexpr StringHash eRockSack{"rock_sack"};
    static inline constexpr StringHash eZBall{"z_ball"};
    static inline constexpr StringHash eFallingItem{"falling_item"};
    static inline constexpr StringHash ePullRingRope{"pull_ring_rope"};
    static inline constexpr StringHash eBackgroundAnimation{"background_animation"};
    static inline constexpr StringHash eHoney{"honey"};
    static inline constexpr StringHash eTimedMine{"timed_mine"};
    static inline constexpr StringHash eSlig{"slig"};
    static inline constexpr StringHash eSlog{"slog"};
    static inline constexpr StringHash eLever{"lever"};
    static inline constexpr StringHash eBellHammer{"bell_hammer"};
    static inline constexpr StringHash eSecurityOrb{"security_orb"};
    static inline constexpr StringHash eLiftMudokon{"lift_mudokon"};
    static inline constexpr StringHash eBeeSwarmHole{"bee_swarm_hole"};
    static inline constexpr StringHash eHoneySack{"honey_sack"};
    static inline constexpr StringHash eAbeStart{"abe_start"};
    static inline constexpr StringHash eElumWall{"elum_wall"};
    static inline constexpr StringHash eSlingMud{"sling_mud"};
    static inline constexpr StringHash eBeeNest{"bee_nest"};
    static inline constexpr StringHash eMine{"mine"};
    static inline constexpr StringHash eUXB{"uxb"};
    static inline constexpr StringHash eParamite{"paramite"};
    static inline constexpr StringHash eBat{"bat"};
    static inline constexpr StringHash eRingMudokon{"ring_mudokon"};
    static inline constexpr StringHash eBirdPortal{"bird_portal"};
    static inline constexpr StringHash eBellSongStone{"bell_song_stone"};
    static inline constexpr StringHash eTrapDoor{"trap_door"};
    static inline constexpr StringHash eRollingBall{"rolling_ball"};
    static inline constexpr StringHash eSligBoundLeft{"slig_bound_left"};
    static inline constexpr StringHash eRollingBallStopper{"rolling_ball_stopper"};
    static inline constexpr StringHash eFootSwitch{"foot_switch"};
    static inline constexpr StringHash eSecurityClaw{"security_claw"};
    static inline constexpr StringHash eMotionDetector{"motion_detector"};
    static inline constexpr StringHash eSligSpawner{"slig_spawner"};
    static inline constexpr StringHash eElectricWall{"electric_wall"};
    static inline constexpr StringHash eLiftMover{"lift_mover"};
    static inline constexpr StringHash eChimeLock{"chime_lock"};
    static inline constexpr StringHash eElum{"elum"};
    static inline constexpr StringHash eMeatSack{"meat_sack"};
    static inline constexpr StringHash eScrab{"scrab"};
    static inline constexpr StringHash eFlintLockFire{"flint_lock_fire"};
    static inline constexpr StringHash eSligBoundRight{"slig_bound_right"};
    static inline constexpr StringHash eInvisibleSwitch{"invisible_switch"};
    static inline constexpr StringHash eMudokon{"mudokon"};
    static inline constexpr StringHash eDoorFlame{"door_flame"};
    static inline constexpr StringHash eMovingBomb{"moving_bomb"};
    static inline constexpr StringHash eMeatSaw{"meat_saw"};
    static inline constexpr StringHash eMainMenuController{"main_menu_controller"};
    static inline constexpr StringHash eHintFly{"hint_fly"};
    static inline constexpr StringHash eTimerTrigger{"timer_trigger"};
    static inline constexpr StringHash eSecurityDoor{"security_door"};
    static inline constexpr StringHash eBoomMachine{"boom_machine"};
    static inline constexpr StringHash eLCDScreen{"lcd_screen"};
    static inline constexpr StringHash eHandStone{"hand_stone"};
    static inline constexpr StringHash eCreditsController{"credits_controller"};
    static inline constexpr StringHash eLCDStatusBoard{"lcd_status_board"};
    // static inline constexpr StringHash eSwitchStateBooleanLogic{"switch_state_boolean_logic"}; // unused object not implemented yet
    static inline constexpr StringHash eMusicTrigger{"music_trigger"};
    static inline constexpr StringHash eLightEffect{"light_effect"};
    static inline constexpr StringHash eSlogSpawner{"slog_spawner"};
    static inline constexpr StringHash eGasCountdown{"gas_countdown"};
    static inline constexpr StringHash eRingCancel{"ring_cancel"};
    static inline constexpr StringHash eGasEmitter{"gas_emitter"};
    static inline constexpr StringHash eZzzSpawner{"zzz_spawner"};
    static inline constexpr StringHash eBackgroundGlukkon{"background_glukkon"};
    static inline constexpr StringHash eKillUnsavedMuds{"kill_unsaved_muds"};
    static inline constexpr StringHash eMovieHandStone{"movie_hand_stone"};
    static inline constexpr StringHash eWheelSyncer{"wheel_syncer"};
    static inline constexpr StringHash eGlukkon{"glukkon"};
    static inline constexpr StringHash eWater{"water"};
    static inline constexpr StringHash eWorkWheel{"work_wheel"};
    static inline constexpr StringHash eLaughingGas{"laughing_gas"};
    static inline constexpr StringHash eFlyingSlig{"flying_slig"};
    static inline constexpr StringHash eFleech{"fleech"};
    static inline constexpr StringHash eSlurg{"slurg"};
    static inline constexpr StringHash eSlamDoor{"slam_door"};
    static inline constexpr StringHash eLevelLoader{"level_loader"};
    static inline constexpr StringHash eDemoSpawnPoint{"demo_spawn_point"};
    static inline constexpr StringHash eTeleporter{"teleporter"};
    static inline constexpr StringHash eSlurgSpawner{"slurg_spawner"};
    static inline constexpr StringHash eDrill{"drill"};
    static inline constexpr StringHash eColourfulMeter{"colourful_meter"};
    static inline constexpr StringHash eFlyingSligSpawner{"flying_slig_spawner"};
    static inline constexpr StringHash eMineCar{"mine_car"};
    static inline constexpr StringHash eBoneBag{"bone_bag"};
    static inline constexpr StringHash eExplosionSet{"explosion_set"};
    static inline constexpr StringHash eMultiSwitchController{"multi_switch_controller"};
    static inline constexpr StringHash eStatusLight{"status_light"};
    static inline constexpr StringHash eSlapLock{"slap_lock"};
    static inline constexpr StringHash eParamiteWebLine{"paramite_web_line"};
    static inline constexpr StringHash eAlarm{"alarm"};
    static inline constexpr StringHash eBrewMachine{"brew_machine"};
    static inline constexpr StringHash eScrabSpawner{"scrab_spawner"};
    static inline constexpr StringHash eCrawlingSlig{"crawling_slig"};
    static inline constexpr StringHash eSligGetPants{"slig_get_pants"};
    static inline constexpr StringHash eSligGetWings{"slig_get_wings"};
    static inline constexpr StringHash eGreeter{"greeter"};
    static inline constexpr StringHash eCrawlingSligButton{"crawling_slig_button"};
    static inline constexpr StringHash eGlukkonSwitch{"glukkon_switch"};
    static inline constexpr StringHash eDoorBlocker{"door_blocker"};
    static inline constexpr StringHash eTrainDoor{"train_door"};
    static inline constexpr StringHash eDemoPlaybackStone{"demo_playback_stone"};
    static inline constexpr StringHash eTorturedMud{"tortured_mud"};

    ReliveTypes()
    {
        Add(eNone);
        Add(eHoist);
        Add(eEdge);
        Add(eShadowZone);
        Add(eLiftPoint);
        Add(eWell);
        Add(eWellExpress);
        Add(eWellLocal);
        Add(eDove);
        Add(eRockSack);
        Add(eZBall);
        Add(eFallingItem);
        Add(ePullRingRope);
        Add(eBackgroundAnimation);
        Add(eHoney);
        Add(eTimedMine);
        Add(eSlig);
        Add(eSlog);
        Add(eLever);
        Add(eBellHammer);
        Add(eSecurityOrb);
        Add(eLiftMudokon);
        Add(eBeeSwarmHole);
        Add(eHoneySack);
        Add(eAbeStart);
        Add(eElumWall);
        Add(eSlingMud);
        Add(eBeeNest);
        Add(eMine);
        Add(eUXB);
        Add(eParamite);
        Add(eBat);
        Add(eRingMudokon);
        Add(eBirdPortal);
        Add(eBellSongStone);
        Add(eTrapDoor);
        Add(eRollingBall);
        Add(eSligBoundLeft);
        Add(eRollingBallStopper);
        Add(eFootSwitch);
        Add(eSecurityClaw);
        Add(eMotionDetector);
        Add(eSligSpawner);
        Add(eElectricWall);
        Add(eLiftMover);
        Add(eChimeLock);
        Add(eElum);
        Add(eMeatSack);
        Add(eScrab);
        Add(eFlintLockFire);
        Add(eSligBoundRight);
        Add(eInvisibleSwitch);
        Add(eMudokon);
        Add(eDoorFlame);
        Add(eMovingBomb);
        Add(eMeatSaw);
        Add(eMainMenuController);
        Add(eHintFly);
        Add(eTimerTrigger);
        Add(eSecurityDoor);
        Add(eBoomMachine);
        Add(eLCDScreen);
        Add(eHandStone);
        Add(eCreditsController);
        Add(eLCDStatusBoard);
        // Add(eSwitchStateBooleanLogic); // unused object not implemented yet
        Add(eMusicTrigger);
        Add(eLightEffect);
        Add(eSlogSpawner);
        Add(eGasCountdown);
        Add(eRingCancel);
        Add(eGasEmitter);
        Add(eZzzSpawner);
        Add(eBackgroundGlukkon);
        Add(eKillUnsavedMuds);
        Add(eMovieHandStone);
        Add(eWheelSyncer);
        Add(eGlukkon);
        Add(eWater);
        Add(eWorkWheel);
        Add(eLaughingGas);
        Add(eFlyingSlig);
        Add(eFleech);
        Add(eSlurg);
        Add(eSlamDoor);
        Add(eLevelLoader);
        Add(eDemoSpawnPoint);
        Add(eTeleporter);
        Add(eSlurgSpawner);
        Add(eDrill);
        Add(eColourfulMeter);
        Add(eFlyingSligSpawner);
        Add(eMineCar);
        Add(eBoneBag);
        Add(eExplosionSet);
        Add(eMultiSwitchController);
        Add(eStatusLight);
        Add(eSlapLock);
        Add(eParamiteWebLine);
        Add(eAlarm);
        Add(eBrewMachine);
        Add(eScrabSpawner);
        Add(eCrawlingSlig);
        Add(eSligGetPants);
        Add(eGreeter);
        Add(eCrawlingSligButton);
        Add(eGlukkonSwitch);
        Add(eDoorBlocker);
        Add(eTrainDoor);
        Add(eDeathDrop);
        Add(eInvisibleZone);
        Add(eContinuePoint);
        Add(eBirdPortalExit);
        Add(eSoftLanding);
        Add(eSligPersist);
        Add(eElumStart);
        Add(eStartController);
        Add(eScrabNoFall);
        Add(eScrabLeftBound);
        Add(eScrabRightBound);
        Add(eHoneyDripTarget);
        Add(eZSligCover);
        Add(eResetPath);
        Add(ePathTransition);
        Add(eEnemyStopper);
        Add(eMovingBombStopper);
        Add(eElumPathTrans);
        Add(eMudokonPathTrans);
        Add(eSligGetWings);
        Add(eThrowableArray);
        Add(eDemoPlaybackStone);
        Add(eTorturedMud);
    }
};

/* enum class ReliveTypes : s16
{
    eNone = 7000,
    eCrawlingSligButton,
    eWheelSyncer,
    eDemoSpawnPoint,
    eMultiSwitchController,
    eStatusLight,
    eSlapLock,
    eParamiteWebLine,
    eGlukkonSwitch,
    eDoorBlocker,
    eTrainDoor,
    eLevelLoader,
    eSligGetWings,
    eSligGetPants,
    eTeleporter,
    eWater,
    eWorkWheel,
    eLCDScreen,
    eInvisibleSwitch,
    eDoorFlame,
    eMovingBomb,
    eMainMenuController,
    eHintFly,
    eSecurityDoor,
    eCreditsController,
    eLCDStatusBoard,
    eSwitchStateBooleanLogic,
    eLightEffect,
    eSlogSpawner,
    eGasEmitter,
    eRingCancel,
    eElumWall,
    eAbeStart,
    eBeeSwarmHole,
    eFallingItem,
    eShadowZone,
    eStartController,
    eBirdPortalExit,
    eHoneyDripTarget,
    ePathTransition,
    eZSligCover,
    eResetPath,
    eElumPathTrans,
    eScrabLeftBound,
    eScrabRightBound,
    eScrabNoFall,
    eMovingBombStopper,
    eElumStart,
    eEdge,
    eSoftLanding,
    eMovieHandStone,
    eBellSongStone,
    eDemoPlaybackStone,
    eHandStone,
    eHoist,
    eContinuePoint,
    eWellLocal,
    eWellExpress,
    eMudokonPathTrans,
    eRingMudokon,
    eLiftMudokon,
    eInvisibleZone,
    eEnemyStopper,
    eSligBoundLeft,
    eSligBoundRight,
    eSligPersist,
    eZzzSpawner,
    eKillUnsavedMuds,
    eDeathDrop,
    eAlarm,
    eScreenManager,
    eBackgroundAnimation,
    eBat,
    eLiftMover,
    eTimedMine, // AO only
    eBullet,
    eDDCheat,
    eBells,
    eChimeLock,
    eGasCountDown,
    eParticleBurst,
    eDoor,
    eGameSpeak,
    eElectricWall,
    eElum,
    eBellHammer,
    ePalOverwriter,
    eGroundExplosion,
    eSecurityClaw,
    eRockSpawner,
    eFlintLockFire,
    eThrowableTotalIndicator,
    eFootSwitch,
    eGameEnderController,
    eDeathBird,
    eLoadingFile,
    eGrenade,
    eBoomMachine,
    eBackgroundGlukkon,
    eAbe,
    MainMenuFade, // TODO: rename to eMainMenuFade
    eHoneySack,
    eHoney,
    eClawOrBirdPortalTerminator,
    eMudokon,
    eLiftPoint,
    eMeat,
    eMeatSack,
    eMeatSaw,
    eMine,
    eRollingBallStopperShaker,
    eMotionDetector,
    eRollingBallStopper,
    ePauseMenu,
    eParamite,
    eDemoPlayback,
    eBirdPortal,
    eBirdPortalTerminator,
    eFG1,
    eAbilityRing,
    eRock,
    eRockSack,
    eRollingBall,
    eRope,
    eAirExplosion,
    eRedLaser,
    eScrab,
    eScreenClipper,
    eEffectBase,
    eFade,
    eFlash,
    ScreenShake, // TODO: rename to eScreenShake
    eScreenWave,
    eUnknown, // todo: remove ?
    eShrykull,
    eSnoozParticle, // TODO: remove this typo version of eSnoozeParticle
    eSlig,
    eSlog,
    SlingMud, // TODO: rename to eSlingMud
    eSligSpawner,
    eZBall,
    eParticle,
    eZapLine,
    eBeeSwarm, // not the same as beeswarmhole?
    eBeeNest,
    eLever,
    eTrapDoor,
    eUXB,
    eMovie,
    eCameraSwapper,
    eElectrocute,
    eTimedMine_or_MovingBomb, // AE only
    eBone,
    eBoneBag,
    eBrewMachine,
    eSligButton,
    eExplosionSet,
    eZapSpark,
    eMetal,
    eMinesAlarm,
    eCrawlingSlig,
    eDrill,
    eLaughingGas,
    eDoorLock,
    eDove,
    eEvilFart,
    eFleech,
    ePossessionFlicker,
    eFlyingSlig,
    eFlyingSligSpawner,
    eColourfulMeter,
    eSlapLock_OrbWhirlWind,
    eGreeter,
    eGlukkon,
    eHelpPhone,
    eEyeOrbPart,
    eInvisibleEffect,
    ePulley,
    eResourceManager,
    eSligGetPantsOrWings,
    eRingOrLiftMud,
    eSecurityOrb,
    eText,
    eMineCar,
    eGreeterBody,
    eMusicController,
    eMusicTrigger,
    ePullRingRope,
    eScrabSpawner,
    eMainMenuTransistion, // TODO: fix typo
    eScreenShake,
    eSlamDoor,
    eSnoozeParticle,
    eSlurgSpawner,
    eSlurg,
    eTimerTrigger,
    eTorturedMud,
    eWebLine,
    eWell,
    eThrowableArray
};*/

enum class AETypes : s16
{
    eNone_0 = 0,
    eAlarm_1 = 1,
    eSligSpawner_2 = 2,
    eScreenManager_6 = 6,
    eBackgroundAnimation_7 = 7,
    eLiftMover_9 = 9,
    eTimedMine_or_MovingBomb_10 = 10,
    eBone_11 = 11,
    eBoneBag_12 = 12,
    eBrewMachine_13 = 13,
    eBullet_15 = 15,
    eSligButton_16 = 16,
    eExplosionSet_18 = 18,
    eDDCheat_19 = 19,
    eZapSpark_22 = 22,
    eGasClock_23 = 23,
    eMetal_24 = 24,
    eMinesAlarm_25 = 25,
    eCrawlingSlig_26 = 26,
    eParticleBurst_29 = 29,
    eDrill_30 = 30,
    eLaughingGas_31 = 31,
    eDoor_33 = 33,
    eDoorLock_34 = 34,
    eDove_35 = 35,
    eGameSpeak_38 = 38,
    eElectricWall_39 = 39,
    ePalOverwriter_44 = 44,
    eEvilFart_45 = 45,
    eBaseBomb_46 = 46,
    eSecurityClaw_47 = 47,
    eRockSpawner_48 = 48,
    eFleech_50 = 50,
    ePossessionFlicker_51 = 51,
    eThrowableTotalIndicator_53 = 53,
    eFlyingSlig_54 = 54,
    eFlyingSligSpawner_55 = 55,
    eFootSwitch_56 = 56,
    eGameEnderController_57 = 57,
    eColourfulMeter_59 = 59,
    eSlapLock_OrbWhirlWind_60 = 60,
    eSlapLock_61 = 61,
    eDeathBird_62 = 62,
    eGreeter_64 = 64,
    eGrenade_65 = 65,
    eGrenadeMachine_66 = 66,
    eGlukkon_67 = 67,
    eHelpPhone_68 = 68,
    eAbe_69 = 69,
    eEyeOrbPart_74 = 74,
    eInvisibleEffect_75 = 75,
    ePulley_76 = 76,
    eLiftPoint_78 = 78,
    eResourceManager_70 = 79,
    eSligGetPantsOrWings_80 = 80,
    eRingOrLiftMud_81 = 81,
    eSecurityOrb_83 = 83,
    eMeat_84 = 84,
    eMeatSack_85 = 85,
    eMeatSaw_86 = 86, // from AO
    eText_87 = 87,
    eMine_88 = 88,
    eMineCar_89 = 89,
    eGreeterBody_91 = 91,
    eMusicController_93 = 93,
    eMusicTrigger_94 = 94,
    ePauseMenu_95 = 95,
    eParamite_96 = 96,
    eDemoPlayback_98 = 98,
    eBirdPortal_99 = 99,
    eBirdPortalTerminator_100 = 100,
    eFG1_101 = 101,
    eThrowableArray_102 = 102,
    ePullRope_103 = 103,
    eAbilityRing_104 = 104,
    eRock_105 = 105,
    eRockSack_106 = 106,
    eRope_108 = 108,
    eExplosion_109 = 109,
    eMudokon_110 = 110,
    eRedLaser_111 = 111,
    eScrab_112 = 112,
    eScrabSpawner_113 = 113,
    eScreenClipper_114 = 114,
    eEffectBase_115 = 115,
    eMainMenuTransistion_116 = 116,
    eFlash_117 = 117,
    eScreenShake_118 = 118,
    eShrykull_121 = 121,
    eSlamDoor_122 = 122,
    eSnoozeParticle_124 = 124,
    eSlig_125 = 125,
    eSlog_126 = 126,
    eSlurgSpawner_128 = 128,
    eSlurg_129 = 129,
    eParticle_134 = 134,
    eZapLine_135 = 135,
    eTimerTrigger_136 = 136,
    eLever_139 = 139,
    eTorturedMud_141 = 141,
    eTrapDoor_142 = 142,
    eUXB_143 = 143,
    eMovie_145 = 145,
    eWebLine_146 = 146,
    eWell_147 = 147,
    eWorkWheel_148 = 148,
    eCameraSwapper_149 = 149,
    eElectrocute_150 = 150,
};


namespace AO {

enum class AOTypes : s16
{
    eNone_0 = 0,
    eAlarm_1 = 1,

    eScreenManager_4 = 4,
    eBackgroundAnimation_5 = 5,
    eBat_6 = 6,
    eLiftMover_7 = 7,
    eTimedMine_8 = 8,

    eBullet_10 = 10,
    eDDCheat_12 = 12,
    eBells_13 = 13,
    eChimeLock_14 = 14,
    eZapSpark_15 = 15,
    eGasClock_16 = 16,

    eParticleBurst_19 = 19,

    eDoor_21 = 21,
    eDove_22 = 22,

    eGameSpeak_24 = 24,
    eElectricWall_25 = 25,
    eElum_26 = 26,
    eBellHammer_27 = 27,

    ePalOverwriter_29 = 29,
    eBaseBomb_30 = 30,
    eSecurityClaw_31 = 31,
    eRockSpawner_32 = 32,

    eFlintLockFire_34 = 34,
    eThrowableTotalIndicator_35 = 35,
    eFootSwitch36 = 36,
    eGameEnderController_37 = 37,
    eDeathBird_38 = 38,
    eLoadingFile_39 = 39,
    eGrenade_40 = 40,
    eGrenadeMachine_41 = 41,
    eBackgroundGlukkon_42 = 42,
    eAbe_43 = 43,
    MainMenuFade_44 = 44,
    eHoneySack_45 = 45,

    eHoney_47 = 47,
    eClawOrBirdPortalTerminator_48 = 48,

    eRingOrLiftMud_52 = 52,
    eLiftPoint_51 = 51,
    SecurityOrb_53 = 53,
    eMeat_54 = 54,
    eMeatStack_55 = 55,
    eMeatSaw_56 = 56,
    eMine_57 = 57,
    eRollingBallStopperShaker_58 = 58,
    eMotionDetector_59 = 59,
    eRollingBallStopper_60 = 60,
    ePauseMenu_61 = 61,
    eParamite_62 = 62,
    eDemoPlayback = 64,
    eBirdPortal_65 = 65,
    eBirdPortalTerminator_66 = 66,
    eFG1_67 = 67,
    ePullRingRope_68 = 68,
    eAbilityRing_69 = 69,
    eRock_70 = 70,
    eRockSack_71 = 71,
    eRollingBall_72 = 72,
    eRope_73 = 73,
    eExplosion_74 = 74,
    eMudokon_75 = 75,
    eRedLaser_76 = 76,
    eScrab_77 = 77,
    eScreenClipper_78 = 78,
    eEffectBase_79 = 79,
    eDeathFadeOut_80 = 80, // TODO: Actually eMainMenuTransistion in AE, shared?
    eFlash_81 = 81,
    ScreenShake_82 = 82,
    eScreenWave_83 = 83,
    eUnknown_84 = 84,
    eShrykull_85 = 85,

    eSnoozParticle_87 = 87,
    eSlig_88 = 88,
    eSlog_89 = 89,
    SlingMud_90 = 90,
    eSligSpawner_91 = 91,
    eZBall_92 = 92,
    eParticle_93 = 93,
    eZapLine_94 = 94,
    eBeeSwarm_95 = 95,
    eBeeNest_96 = 96,
    eLever_97 = 97,
    eTrapDoor_98 = 98,
    eUXB_99 = 99,
    eMovie_100 = 100,
    eWell_101 = 101,
    eCameraSwapper_102 = 102,
    eElectrocute_103 = 103,
};
}