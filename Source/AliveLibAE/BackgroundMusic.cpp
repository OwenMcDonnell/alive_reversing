#include "stdafx.h"
#include "BackgroundMusic.hpp"
#include "Sound/Midi.hpp"
#include "Function.hpp"
#include "Map.hpp"
#include "stdlib.hpp"
#include "PathData.hpp"

ALIVE_VAR(1, 0x560f78, s16, sBackgroundMusic_seq_id_560F78, -1);


BackgroundMusic::BackgroundMusic(s32 musicId)
    : BaseGameObject(TRUE, 0)
{
    field_20_music_id = static_cast<s16>(musicId);
    sBackgroundMusic_seq_id_560F78 = -1;
}

void BackgroundMusic::VUpdate()
{
    if (field_20_music_id >= 0)
    {
        if (gMap.mCurrentLevel != EReliveLevelIds::eNone || gMap.mCurrentPath != 1 || gMap.mCurrentCamera != 10)
        {
            SND_SEQ_PlaySeq(field_20_music_id, 0, 0);
        }
        sBackgroundMusic_seq_id_560F78 = field_20_music_id;
    }
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
}

// In order of functions in the orignal game these are not part of this object
void BackgroundMusic::Stop()
{
    if (sBackgroundMusic_seq_id_560F78 >= 0)
    {
        SND_SEQ_Stop(sBackgroundMusic_seq_id_560F78);
    }
}

void BackgroundMusic::Play()
{
    if (sBackgroundMusic_seq_id_560F78 >= 0)
    {
        SND_SEQ_PlaySeq(sBackgroundMusic_seq_id_560F78, 0, 0);
    }
}
