#include "stdafx_ao.h"
#include "ResourceManager.hpp"
#include "Function.hpp"
#include "Particle.hpp"
#include "stdlib.hpp"
#include "PsxDisplay.hpp"
#include "Psx.hpp"
#include "PsxRender.hpp"
#include "ScreenManager.hpp"
#include "Game.hpp"
#include "LvlArchive.hpp"

START_NS_AO

ALIVE_VAR(1, 0x5009E0, DynamicArrayT<ResourceManager::ResourceManager_FileRecord>*, ObjList_5009E0, nullptr);

ALIVE_VAR(1, 0x9F0E48, DWORD, sManagedMemoryUsedSize_9F0E48, 0);

ALIVE_VAR(1, 0x5076A0, short, bHideLoadingIcon_5076A0, 0);
ALIVE_VAR(1, 0x5076A4, int, loading_ticks_5076A4, 0);
ALIVE_VAR(1, 0x9F0E38, short, sResources_Pending_Loading_9F0E38, 0);

ALIVE_VAR(1, 0x50EE2C, ResourceManager::ResourceHeapItem*, sFirstLinkedListItem_50EE2C, nullptr);
ALIVE_VAR(1, 0x50EE28, ResourceManager::ResourceHeapItem*, sSecondLinkedListItem_50EE28, nullptr);

const DWORD kResHeapSize = 5120000;
ALIVE_ARY(1, 0x50EE38, BYTE, kResHeapSize, sResourceHeap_50EE38, {}); // Huge 5.4 MB static resource buffer

const DWORD kLinkedListArraySize = 375;
ALIVE_ARY(1, 0x50E270, ResourceManager::ResourceHeapItem, kLinkedListArraySize, sResourceLinkedList_50E270, {});

ALIVE_VAR(1, 0x50EE30, BYTE*, spResourceHeapStart_50EE30, nullptr);
ALIVE_VAR(1, 0x9F0E3C, BYTE*, spResourceHeapEnd_9F0E3C, nullptr);

// TODO :Move to psx file
EXPORT CdlLOC* CC PSX_Pos_To_CdLoc_49B340(int /*pos*/, CdlLOC* /*pLoc*/)
{
    NOT_IMPLEMENTED();
    return nullptr;
}

EXPORT int CC PSX_CD_File_Seek_49B670(char /*mode*/, CdlLOC* /*pLoc*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT int CC PSX_CD_File_Read_49B8B0(int /*numSectors*/, void* /*pBuffer*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT int CC PSX_CD_FileIOWait_49B900(int)
{
    NOT_IMPLEMENTED();
    return 0;
}

EXPORT void CC Odd_Sleep_48DD90(DWORD /*dwMilliseconds*/)
{
    NOT_IMPLEMENTED();
}

ALIVE_VAR(1, 0x507714, int, gFilesPending_507714, 0);
ALIVE_VAR(1, 0x50768C, short, bLoadingAFile_50768C, 0);

using TLoadCallBack = void(CC*)(void*);

// TODO: Rename to "LoadingFile"
class ResourceManager_FileRecord_Unknown : public BaseGameObject
{
public:
    EXPORT ResourceManager_FileRecord_Unknown* ctor_41E8A0(int pos, int size, TLoadCallBack pFn, void* fnArg, Camera* pArray)
    {
        ctor_487E10(1);
        
        SetVTable(this, 0x4BB088);

        gFilesPending_507714++;

        field_6_flags.Set(Options::eSurviveDeathReset_Bit9);
        field_6_flags.Set(Options::eUpdateDuringCamSwap_Bit10);

        field_14_fn = pFn;
        field_18_fn_arg = fnArg;
        field_10_size = size;

        field_4_typeId = Types::eLoadingFile_39;
        field_1C_pCamera = pArray;
        
        PSX_Pos_To_CdLoc_49B340(pos, &field_2A_cdLoc);

        field_28_state = 0;
        return this;
    }

    EXPORT BaseGameObject* dtor_41E870()
    {
        SetVTable(this, 0x4BB088);

        gFilesPending_507714--;

        if (field_28_state != 0)
        {
            if (field_28_state != 7)
            {
                bLoadingAFile_50768C = 0;
            }
        }
        return dtor_487DF0();
    }

    EXPORT void DestroyOnState0_41EA50()
    {
        if (field_28_state == 0)
        {
            field_6_flags.Set(BaseGameObject::eDead_Bit3);
        }
    }

    virtual void VUpdate() override
    {
        VUpdate_41E900();
    }

    EXPORT void VUpdate_41E900()
    {
        switch (field_28_state)
        {
        case 0:
            if (!bLoadingAFile_50768C)
            {
                field_20_ppRes = ResourceManager::Allocate_New_Block_454FE0(field_10_size << 11, ResourceManager::eFirstMatching);
                if (field_20_ppRes)
                {
                    ResourceManager::Header* pHeader = ResourceManager::Get_Header_455620(field_20_ppRes);
                    field_24_readBuffer = pHeader;
                    pHeader->field_8_type = ResourceManager::Resource_Pend;
                    ResourceManager::Increment_Pending_Count_4557A0();
                    bLoadingAFile_50768C = 1;
                    field_28_state = 1;
                }
                else
                {
                    ResourceManager::Reclaim_Memory_455660(200000u);
                }
            }
            break;

        case 1:
            if (PSX_CD_File_Seek_49B670(2, &field_2A_cdLoc))
            {
                field_28_state = 2;
            }
            break;

        case 2:
            if (PSX_CD_File_Read_49B8B0(field_10_size, field_24_readBuffer))
            {
                field_28_state = 3;
                const int ioRet = PSX_CD_FileIOWait_49B900(1);
                if (ioRet <= 0)
                {
                    field_28_state = ioRet != -1 ? 4 : 1;
                }
                break;
            }
            break;

        case 3:
        {
            const int ioRet = PSX_CD_FileIOWait_49B900(1);
            if (ioRet <= 0)
            {
                field_28_state = ioRet != -1 ? 4 : 1;
            }
            break;
        }

        case 4:
            ResourceManager::Move_Resources_To_DArray_455430(
                field_20_ppRes,
                &field_1C_pCamera->field_0_array);
            field_28_state = 5;
            break;

        case 5:
            if (field_14_fn)
            {
                field_14_fn(field_18_fn_arg);
            }
            field_28_state = 6;
            bLoadingAFile_50768C = 0;
            break;

        case 6:
            ResourceManager::Decrement_Pending_Count_4557B0();
            field_6_flags.Set(BaseGameObject::eDead_Bit3);
            field_28_state = 7;
            break;

        default:
            return;
        }
    }

    virtual void VScreenChanged() override
    {
        // Stay alive
    }


    virtual BaseGameObject* VDestructor(signed int flags) override
    {
        return Vdtor_41EBB0(flags);
    }

    EXPORT ResourceManager_FileRecord_Unknown* Vdtor_41EBB0(signed int flags)
    {
        dtor_41E870();
        if (flags & 1)
        {
            ao_delete_free_447540(this);
        }
        return this;
    }

    int field_10_size;
    TLoadCallBack field_14_fn;
    void* field_18_fn_arg;
    Camera* field_1C_pCamera;
    BYTE** field_20_ppRes;
    void* field_24_readBuffer;
    __int16 field_28_state;
    CdlLOC field_2A_cdLoc;
    __int16 field_2E_pad;
};
ALIVE_ASSERT_SIZEOF(ResourceManager_FileRecord_Unknown, 0x30);

void CC Game_ShowLoadingIcon_445EB0()
{
    BYTE** ppLoadingAnimRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, 8010, 1, 0);
    if (ppLoadingAnimRes)
    {
        auto pParticle = ao_new<Particle>();
        if (pParticle)
        {
            pParticle->ctor_478880(FP_FromInteger(0), FP_FromInteger(0), 652, 50, 38, ppLoadingAnimRes);
        }

        pParticle->field_10_anim.field_4_flags.Clear(AnimFlags::eBit15_bSemiTrans);
        pParticle->field_10_anim.field_4_flags.Set(AnimFlags::eBit16_bBlending);

        pParticle->field_10_anim.field_C_layer = 0;

        int* local_ot[42] = {};
        PSX_DRAWENV drawEnv = {};

        PSX_SetDefDrawEnv_495EF0(&drawEnv, 0, 0, 640, 240);
        PSX_PutDrawEnv_495DD0(&drawEnv);
        PSX_DrawSync_496750(0);
        PSX_ClearOTag_496760(local_ot, 42);

        pParticle->field_10_anim.vRender(320, 220, local_ot, 0, 0);

        PSX_DrawOTag_4969F0(local_ot);
        PSX_DrawSync_496750(0);

        PSX_ClearOTag_496760(local_ot, 42);

        pParticle->field_10_anim.vRender(320, gPsxDisplay_504C78.field_2_height + 220, local_ot, 0, 0);

        PSX_DrawOTag_4969F0(local_ot);
        PSX_DrawSync_496750(0);

        PSX_DISPENV dispEnv = {};
        PSX_SetDefDispEnv_4959D0(&dispEnv, 0, 0, 640, 240);
        PSX_PutDispEnv_495CE0(&dispEnv);
        pParticle->field_6_flags.Set(BaseGameObject::eDead_Bit3);
        bHideLoadingIcon_5076A0 = TRUE;
    }
}


void CC ResourceManager::On_Loaded_446C10(ResourceManager_FileRecord* pLoaded)
{
    for (int i=0; i< pLoaded->field_10_file_sections_dArray.Size(); i++)
    {
        ResourceManager_FilePartRecord* pFilePart = pLoaded->field_10_file_sections_dArray.ItemAt(i);
        if (!pFilePart)
        {
            break;
        }

        BYTE** ppRes = ResourceManager::GetLoadedResource_4554F0(
            pFilePart->field_0_ResId,
            pFilePart->field_4_bAddUsecount,
            1,
            0);

        if (ppRes)
        {
            pFilePart->field_8_pCamera->field_0_array.Push_Back(ppRes);
        }

        ao_delete_free_447540(pFilePart);
    }

    // pLoaded is done with now, remove it
    ObjList_5009E0->Remove_Item(pLoaded);

    if (pLoaded)
    {
        // And destruct/free it
        pLoaded->dtor_447510();
        ao_delete_free_447540(pLoaded);
    }
}

void CC ResourceManager::LoadResource_446C90(const char* /*pFileName*/, int /*type*/, int /*resourceId*/, __int16 /*loadMode*/, __int16 /*bDontLoad*/)
{
    NOT_IMPLEMENTED();
}

void CC ResourceManager::LoadResourcesFromList_446E80(const char* /*pFileName*/, ResourcesToLoadList* /*list*/, __int16 /*loadMode*/, __int16)
{
    NOT_IMPLEMENTED();
}

void CC ResourceManager::WaitForPendingResources_41EA60(BaseGameObject* pObj)
{
    for (int i = 0; i < gBaseGameObject_list_9F2DF0->Size(); i++)
    {
        BaseGameObject* pObjIter = gBaseGameObject_list_9F2DF0->ItemAt(i);
        if (!pObjIter)
        {
            break;
        }

        if (pObjIter->field_4_typeId == Types::eLoadingFile_39)
        {
            auto pLoadingFile = static_cast<ResourceManager_FileRecord_Unknown*>(pObjIter);
            if (!pObj || pObj == pLoadingFile->field_18_fn_arg)
            {
                while (pLoadingFile->field_28_state != 0)
                {
                    if (pLoadingFile->field_6_flags.Get(BaseGameObject::eDead_Bit3))
                    {
                        break;
                    }
                    pLoadingFile->VUpdate();
                }
                pLoadingFile->field_6_flags.Set(BaseGameObject::eDead_Bit3);
            }
        }
    }
}

EXPORT void CC ResourceManager::LoadingLoop_41EAD0(__int16 bShowLoadingIcon)
{
    while (gFilesPending_507714 > 0)
    {
        SYS_EventsPump_44FF90();

        for (int i=0; i<gBaseGameObject_list_9F2DF0->Size(); i++)
        {
            BaseGameObject* pObjIter = gBaseGameObject_list_9F2DF0->ItemAt(i);
            if (!pObjIter)
            {
                break;
            }

            if (pObjIter->field_4_typeId == Types::eLoadingFile_39)
            {
                if (!pObjIter->field_6_flags.Get(BaseGameObject::eDead_Bit3))
                {
                    pObjIter->VUpdate();

                }
                
                if (pObjIter->field_6_flags.Get(BaseGameObject::eDead_Bit3))
                {
                    i = gBaseGameObject_list_9F2DF0->RemoveAt(i);
                    pObjIter->VDestructor(1);
                }
            }
        }

        Odd_Sleep_48DD90(16u);
        PSX_VSync_496620(0);
        
        loading_ticks_5076A4++;

        if (bShowLoadingIcon)
        {
            if (!bHideLoadingIcon_5076A0 && loading_ticks_5076A4 > 180)
            {
                Game_ShowLoadingIcon_445EB0();
            }
        }
    }
}

void CC ResourceManager::Free_Resources_For_Camera_447170(Camera* pCamera)
{
    for (int i = 0; i < ObjList_5009E0->Size(); i++)
    {
        ResourceManager_FileRecord* pObjIter = ObjList_5009E0->ItemAt(i);
        if (!pObjIter)
        {
            break;
        }

        if (pObjIter->field_1C_pGameObjFileRec->field_28_state == 0)
        {
            // Remove/free file parts that belong to the cameraa
            auto pFileSecsArray = &pObjIter->field_10_file_sections_dArray;
            for (int j = 0; j < pFileSecsArray->Size(); j++)
            {
                ResourceManager_FilePartRecord* pFilePartRecord = pFileSecsArray->ItemAt(j);
                if (!pFilePartRecord)
                {
                    break;
                }

                if (pFilePartRecord->field_8_pCamera == pCamera)
                {
                    j = pFileSecsArray->RemoveAt(j);
                }

                ao_delete_free_447540(pFilePartRecord);
            }

            // Free the containing record if its section array is now empty
            if (pObjIter->field_10_file_sections_dArray.Empty())
            {
                if (pObjIter->field_1C_pGameObjFileRec)
                {
                    pObjIter->field_1C_pGameObjFileRec->DestroyOnState0_41EA50();
                }

                i = ObjList_5009E0->RemoveAt(i);
                pObjIter->dtor_447510();
                ao_delete_free_447540(pObjIter);
            }
        }
    }
}

void CC ResourceManager::Init_454DA0()
{
    for (int i = 1; i < kLinkedListArraySize - 1; i++)
    {
        sResourceLinkedList_50E270[i].field_0_ptr = nullptr;
        sResourceLinkedList_50E270[i].field_4_pNext = &sResourceLinkedList_50E270[i + 1];
    }

    sResourceLinkedList_50E270[kLinkedListArraySize - 1].field_4_pNext = nullptr;

    sResourceLinkedList_50E270[0].field_0_ptr =  &sResourceHeap_50EE38[sizeof(Header)];
    sResourceLinkedList_50E270[0].field_4_pNext = nullptr;
    
    Header* pHeader = Get_Header_455620(&sResourceLinkedList_50E270[0].field_0_ptr);
    pHeader->field_0_size = kResHeapSize;
    pHeader->field_8_type = Resource_Free;

    sFirstLinkedListItem_50EE2C = &sResourceLinkedList_50E270[0];
    sSecondLinkedListItem_50EE28 = &sResourceLinkedList_50E270[1];

    spResourceHeapStart_50EE30 = &sResourceHeap_50EE38[0];
    spResourceHeapEnd_9F0E3C =  &sResourceHeap_50EE38[kResHeapSize - 1];
}

EXPORT ResourceManager::ResourceManager_FileRecord* CC ResourceManager::LoadResourceFile_4551E0(const char* /*pFileName*/, TLoaderFn /*fnOnLoad*/, Camera* /*pCamera1*/, Camera* /*pCamera2*/)
{
    NOT_IMPLEMENTED();
    return nullptr;
}

BYTE** ResourceManager::Alloc_New_Resource_Impl(DWORD type, DWORD id, DWORD size, bool locked, BlockAllocMethod allocType)
{
    BYTE** ppNewRes = Allocate_New_Block_454FE0(size + sizeof(Header), allocType);
    if (!ppNewRes)
    {
        // Failed, try to reclaim some memory and try again.
        Reclaim_Memory_455660(0);
        ppNewRes = Allocate_New_Block_454FE0(size + sizeof(Header), allocType);
    }

    if (ppNewRes)
    {
        Header* pHeader = Get_Header_455620(ppNewRes);
        pHeader->field_8_type = type;
        pHeader->field_C_id = id;
        pHeader->field_4_ref_count = 1;
        pHeader->field_6_flags = locked ? ResourceHeaderFlags::eLocked : 0;
    }
    return ppNewRes;
}

BYTE** CC ResourceManager::Alloc_New_Resource_454F20(DWORD type, DWORD id, DWORD size)
{
  return Alloc_New_Resource_Impl(type, id, size, false, BlockAllocMethod::eFirstMatching);
}

BYTE** CC ResourceManager::Allocate_New_Locked_Resource_454F80(DWORD type, DWORD id, DWORD size)
{
    return Alloc_New_Resource_Impl(type, id, size, true, BlockAllocMethod::eLastMatching);
}

EXPORT BYTE** CC ResourceManager::Allocate_New_Block_454FE0(DWORD /*sizeBytes*/, BlockAllocMethod /*allocMethod*/)
{
    NOT_IMPLEMENTED();
    return nullptr;
}

EXPORT __int16 CC ResourceManager::LoadResourceFile_455270(const char* filename, Camera* pCam, BlockAllocMethod allocMethod)
{
    // Note: None gPcOpenEnabled_508BF0 block not impl as never used

    ResourceManager::LoadingLoop_41EAD0(0);

    LvlFileRecord* pFileRec = sLvlArchive_4FFD60.Find_File_Record_41BED0(filename);
    if (!pFileRec)
    {
        return 0;
    }
    
    const int size = pFileRec->field_10_num_sectors << 11;
    BYTE** ppRes = ResourceManager::Allocate_New_Block_454FE0(size, allocMethod);
    if (!ppRes)
    {
        ResourceManager::Reclaim_Memory_455660(0);
        ppRes = ResourceManager::Allocate_New_Block_454FE0(size, allocMethod);
        if (!ppRes)
        {
            return 0;
        }
    }

    // NOTE: Not sure why this is done twice, perhaps the above memory compact can invalidate the ptr?
    pFileRec = sLvlArchive_4FFD60.Find_File_Record_41BED0(filename);
    if (!pFileRec)
    {
        return 0;
    }

    if (!sLvlArchive_4FFD60.Read_File_41BE40(pFileRec, Get_Header_455620(ppRes)))
    {
        FreeResource_455550(ppRes);
        return 0;
    }

    ResourceManager::Move_Resources_To_DArray_455430(ppRes, &pCam->field_0_array);
    return 1;
}

EXPORT __int16 CC ResourceManager::Move_Resources_To_DArray_455430(BYTE** /*ppRes*/, DynamicArrayT<BYTE*>* /*pArray*/)
{
    NOT_IMPLEMENTED();
    return 0;
}

BYTE** CC ResourceManager::GetLoadedResource_4554F0(DWORD type, DWORD resourceId, __int16 addUseCount, __int16 bLock)
{
    // Iterate all list items
    ResourceHeapItem* pListIter = sFirstLinkedListItem_50EE2C;
    while (pListIter)
    {
        // Find something that matches the type and resource ID
        Header* pResHeader = Get_Header_455620(&pListIter->field_0_ptr);
        if (pResHeader->field_8_type == type && pResHeader->field_C_id == resourceId)
        {
            if (addUseCount)
            {
                pResHeader->field_4_ref_count++;
            }

            if (bLock)
            {
                pResHeader->field_6_flags |= ResourceHeaderFlags::eLocked;
            }

            return &pListIter->field_0_ptr;
        }

        pListIter = pListIter->field_4_pNext;
    }
    return nullptr;
}

__int16 CC ResourceManager::FreeResource_455550(BYTE** /*ppRes*/)
{
    NOT_IMPLEMENTED();
    return 0;
}


__int16 CC ResourceManager::FreeResource_Impl_4555B0(BYTE* handle)
{
    if (handle)
    {
        Header* pHeader = Get_Header_455620(&handle);
        if (pHeader->field_4_ref_count)
        {
            // Decrement ref count, if its not zero then we can't free it yet
            pHeader->field_4_ref_count--;
            if (pHeader->field_4_ref_count > 0)
            {
                return 0;
            }
            pHeader->field_8_type = Resource_Free;
            pHeader->field_6_flags = 0;
            sManagedMemoryUsedSize_9F0E48 -= pHeader->field_0_size;
        }
    }
    return 1;
}

ResourceManager::Header* CC ResourceManager::Get_Header_455620(BYTE** ppRes)
{
    return reinterpret_cast<Header*>((*ppRes - sizeof(Header)));
}

void CC ResourceManager::Reclaim_Memory_455660(DWORD /*sizeToReclaim*/)
{
    NOT_IMPLEMENTED();
}

void CC ResourceManager::Increment_Pending_Count_4557A0()
{
    sResources_Pending_Loading_9F0E38++;
}

void CC ResourceManager::Decrement_Pending_Count_4557B0()
{
    sResources_Pending_Loading_9F0E38--;
}

void CC ResourceManager::Set_Header_Flags_4557D0(BYTE** ppRes, __int16 flags)
{
    Get_Header_455620(ppRes)->field_6_flags |= flags;
}

int CC ResourceManager::Is_Resources_Pending_4557C0()
{
    return sResources_Pending_Loading_9F0E38 > 0 ? 1 : 0;
}

void CC ResourceManager::Free_Resource_Of_Type_455810(DWORD type)
{
    ResourceHeapItem* pListItem = sFirstLinkedListItem_50EE2C;
    while (pListItem)
    {
        // Free it if the type matches and its not flagged as never free
        Header* pHeader = Get_Header_455620(&pListItem->field_0_ptr);
        if (pHeader->field_8_type == type && !(pHeader->field_6_flags & ResourceHeaderFlags::eNeverFree))
        {
            pHeader->field_8_type = Resource_Free;
            pHeader->field_6_flags = 0;
            pHeader->field_4_ref_count = 0;

            sManagedMemoryUsedSize_9F0E48 -= pHeader->field_0_size;
        }
        pListItem = pListItem->field_4_pNext;
    }
}

END_NS_AO



