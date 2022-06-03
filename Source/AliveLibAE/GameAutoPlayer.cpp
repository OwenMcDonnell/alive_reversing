#include "GameAutoPlayer.hpp"
#include "Input.hpp"
#include "Sys_common.hpp"
#include "BaseGameObject.hpp"
#include "BaseAliveGameObject.hpp"

void Recorder::SaveObjectStates()
{
    mFile.Write(RecordTypes::FrameCounter);
    mFile.Write(sGnFrame_5C1B84);

    const u32 objCount = gBaseGameObjects->Size();
    mFile.Write(RecordTypes::ObjectCounter);
    mFile.Write(objCount);

    for (u32 i = 0; i < objCount; i++)
    {
        mFile.Write(RecordTypes::ObjectStates);
        BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
        const s16 objType = static_cast<s16>(pObj->Type());
        ::fwrite(&objType, sizeof(s16), 1, mFile.GetFile());

        if (pObj->mBaseGameObjectFlags.Get(BaseGameObject::eIsBaseAliveGameObject_Bit6))
        {
            mFile.Write(RecordTypes::AliveObjectStates);

            auto pAliveObj = static_cast<BaseAliveGameObject*>(pObj);

            mFile.Write(pAliveObj->mBaseAnimatedWithPhysicsGameObject_XPos.fpValue);
            mFile.Write(pAliveObj->mBaseAnimatedWithPhysicsGameObject_YPos.fpValue);

            mFile.Write(pAliveObj->BaseAliveGameObjectLastLineYPos.fpValue);

            mFile.Write(pAliveObj->mCurrentMotion);
            mFile.Write(pAliveObj->mNextMotion);
            mFile.Write(pAliveObj->mPreviousMotion);

            mFile.Write(pAliveObj->mHealth.fpValue);
        }
    }
}

bool Player::ValidateObjectStates()
{
    ValidateNextTypeIs(RecordTypes::FrameCounter);

    const u32 gnFrame = mFile.ReadU32();
    if (gnFrame != sGnFrame_5C1B84)
    {
        return false;
    }

    ValidateNextTypeIs(RecordTypes::ObjectCounter);
    const u32 objCount = mFile.ReadU32();

    if (static_cast<u32>(gBaseGameObjects->Size()) != objCount)
    {
        LOG_ERROR("Got " << gBaseGameObjects->Size() << " objects but expected " << objCount);
        return false;
    }

    for (u32 i = 0; i < objCount; i++)
    {
        ValidateNextTypeIs(RecordTypes::ObjectStates);

        s16 objType = 0;
        mFile.Read(objType);

        BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
        if (static_cast<s16>(pObj->Type()) != objType)
        {
            LOG_ERROR("Got " << static_cast<s16>(pObj->Type()) << " type but expected " << objType);
            return false;
        }

        if (pObj->mBaseGameObjectFlags.Get(BaseGameObject::eIsBaseAliveGameObject_Bit6))
        {
            ValidateNextTypeIs(RecordTypes::AliveObjectStates);

            auto pAliveObj = static_cast<BaseAliveGameObject*>(pObj);
            bool validateFailed = false;
            validateFailed |= ValidField(mFile, pAliveObj->mBaseAnimatedWithPhysicsGameObject_XPos, "xpos");
            validateFailed |= ValidField(mFile, pAliveObj->mBaseAnimatedWithPhysicsGameObject_YPos, "ypos");
            validateFailed |= ValidField(mFile, pAliveObj->BaseAliveGameObjectLastLineYPos, "last line ypos");
            validateFailed |= ValidField(mFile, pAliveObj->mCurrentMotion, "current motion");
            validateFailed |= ValidField(mFile, pAliveObj->mNextMotion, "next motion");
            validateFailed |= ValidField(mFile, pAliveObj->mPreviousMotion, "previous motion");
            validateFailed |= ValidField(mFile, pAliveObj->mHealth, "health motion");
            if (validateFailed)
            {
                return false;
            }
        }
    }
    return true;
}

u32 GameAutoPlayer::ReadInput(u32 padIdx)
{
    return Input_Read_Pad_4FA9C0(padIdx);
}
