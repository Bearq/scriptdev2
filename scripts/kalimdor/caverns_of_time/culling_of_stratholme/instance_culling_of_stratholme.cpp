/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


/* ScriptData
SDName: instance_culling_of_stratholme
SD%Complete: ?%
SDComment: by MaxXx2021
SDCategory: Culling of Stratholme
EndScriptData */

#include "precompiled.h"
#include "culling_of_stratholme.h"

struct MANGOS_DLL_DECL instance_culling_of_stratholme : public ScriptedInstance
{
    instance_culling_of_stratholme(Map* pMap) : ScriptedInstance(pMap) {Initialize();};

    uint8 m_uiCratesCount;
    uint32 m_auiEncounter[7];
    uint32 m_uiHeroicTimer;
    uint32 m_uiLastTimer;

    uint64 m_uiChromi01GUID;
    uint64 m_uiChromi02GUID;
    uint64 m_uiMikeGUID;
    uint64 m_uiMalCoricsGUID;
    uint64 m_uiGrianStoneGUID;
    uint64 m_uiJamesGUID;
    uint64 m_uiFrasCiabiGUID;
    uint64 m_uiForrestenGUID;
    uint64 m_uiRogerGUID;
    uint64 m_uiMoriganGUID;
    uint64 m_uiPerelliGUID;
    uint64 m_uiJenaGUID;
    uint64 m_uiMarthaGUID;
    uint64 m_uiMalcolmGUID;
    uint64 m_uiDogGUID;
    uint64 m_uiBartlebyGUID;
    uint64 m_uiArthasGUID;
    uint64 m_uiUtherGUID;
    uint64 m_uiJainaGUID;
    uint64 m_uiSalrammGUID;
    uint64 m_uiMalganisGUID;
    uint64 m_uiCorruptorGUID;

    uint64 m_uiShkafGateGUID;
    uint64 m_uiMalGate1GUID;
    uint64 m_uiMalGate2GUID;
    uint64 m_uiMalChestGUID;
    uint64 m_uiExitGUID;

    void Initialize()
    {
       m_uiHeroicTimer = 1500000;
       m_uiLastTimer = 1500000;
       m_auiEncounter[0] = NOT_STARTED;
       m_auiEncounter[1] = NOT_STARTED;
       m_auiEncounter[2] = 0;
       m_auiEncounter[3] = NOT_STARTED;
       m_auiEncounter[4] = 0;
       m_auiEncounter[5] = NOT_STARTED;
       m_auiEncounter[6] = NOT_STARTED;

       DoUpdateWorldState(WORLD_STATE_COS_CRATE_COUNT, 0);
       DoUpdateWorldState(WORLD_STATE_COS_CRATE_ON, 0);
       DoUpdateWorldState(WORLD_STATE_COS_WAVE_COUNT, 0);
       DoUpdateWorldState(WORLD_STATE_COS_TIME_COUNT, 0);
       DoUpdateWorldState(WORLD_STATE_COS_TIME_ON, 0);

       m_uiCratesCount = 0;
       m_uiMikeGUID = 0;
       m_uiChromi01GUID = 0;
       m_uiChromi02GUID = 0;
       m_uiMalCoricsGUID = 0;
       m_uiGrianStoneGUID = 0;
       m_uiJamesGUID = 0;
       m_uiFrasCiabiGUID = 0;
       m_uiForrestenGUID = 0;
       m_uiRogerGUID = 0;
       m_uiMoriganGUID = 0;
       m_uiPerelliGUID = 0;
       m_uiJenaGUID = 0;
       m_uiMarthaGUID = 0;
       m_uiMalcolmGUID = 0;
       m_uiDogGUID = 0;
       m_uiBartlebyGUID = 0;
       m_uiArthasGUID = 0;
       m_uiUtherGUID = 0;
       m_uiJainaGUID = 0;
       m_uiShkafGateGUID = 0;
       m_uiSalrammGUID = 0;
       m_uiCorruptorGUID = 0;
       m_uiMalganisGUID = 0;
       m_uiMalGate1GUID = 0;
       m_uiMalGate2GUID = 0;
       m_uiMalChestGUID = 0;
       m_uiExitGUID = 0;
    }

    void OnCreatureCreate(Creature* pCreature)
    {
        m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();

        switch(pCreature->GetEntry())
        {
            case NPC_CHROMI01: 
                         pCreature->SetActiveObjectState(true);
                         break;
            case NPC_CHROMI02:
                         pCreature->SetActiveObjectState(true);
                         if (m_auiEncounter[0] == DONE)
                            pCreature->SetVisibility(VISIBILITY_ON);
                         else
                            pCreature->SetVisibility(VISIBILITY_OFF);
                         break;
            case NPC_MAL_CORICS: 
                         pCreature->SetActiveObjectState(true);
                         break;
            case NPC_GRIAN_STONE: 
                         pCreature->SetActiveObjectState(true);
                         pCreature->SetStandState(UNIT_STAND_STATE_SIT_MEDIUM_CHAIR);
                         break;
            case NPC_JAMES: 
                         pCreature->SetActiveObjectState(true);
                         pCreature->SetStandState(UNIT_STAND_STATE_SIT_MEDIUM_CHAIR);
                         break;
            case NPC_FRAS_FRASIABI:
                         pCreature->SetActiveObjectState(true);
                         pCreature->SetStandState(UNIT_STAND_STATE_SIT_MEDIUM_CHAIR); 
                         break;
            case NPC_FORRESTER: 
                         pCreature->SetActiveObjectState(true);
                         pCreature->SetStandState(UNIT_STAND_STATE_SIT_MEDIUM_CHAIR);
                         break;
            case NPC_PERELLI:
                         pCreature->SetActiveObjectState(true);
                         break;
            case NPC_MARTHA:
                         pCreature->CastSpell(pCreature, 58925, false);
                         pCreature->SetActiveObjectState(true);
                         break;
            case NPC_DOG:
                         pCreature->SetActiveObjectState(true);
                         break;
            case NPC_JAINA:
                         pCreature->SetActiveObjectState(true);
                         break;
            case NPC_INFINITE_CORRUPTOR: 
                         pCreature->SetPhaseMask(0, true);
                         break;
        }
    }

    void OnObjectCreate(GameObject* pGo)
    {
        m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
    }

    void ChromiWhispers()
    {

       Map::PlayerList const &PlayerList = instance->GetPlayers();

       if (PlayerList.isEmpty())
           return;

       if (Creature* pChromi = instance->GetCreature(m_uiChromi01GUID))
       {
           for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
           {
                pChromi->MonsterWhisper("Good work with crates! Come to me in front of Stratholme for your next assignment!", i->getSource(), false);
                i->getSource()->KilledMonsterCredit(30996, pChromi->GetObjectGuid());
                i->getSource()->DestroyItemCount(ITEM_ARCANE_DISRUPTOR, 1, true);
            }
            pChromi->SetVisibility(VISIBILITY_OFF);
        }
        if (Creature* pChromi2 = instance->GetCreature(m_uiChromi02GUID))
            pChromi2->SetVisibility(VISIBILITY_ON);
    }

    void SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
            case TYPE_QUEST:
                m_auiEncounter[0] = uiData;
                break; 
            case TYPE_CRATES_COUNT:
                m_uiCratesCount = m_uiCratesCount + uiData;
                if(m_uiCratesCount == 5)
                {
                   m_auiEncounter[0] = DONE;
                   ChromiWhispers();
                }
                DoUpdateWorldState(WORLD_STATE_COS_CRATE_COUNT, m_uiCratesCount);
                break;
            case TYPE_INTRO:
                m_auiEncounter[1] = uiData;
                break;
            case TYPE_PHASE:
                m_auiEncounter[2] = uiData;
                break;
            case TYPE_ENCOUNTER:
                m_auiEncounter[3] = uiData;
                break;
            case TYPE_WING:
                m_auiEncounter[4] = uiData;
                break;
            case TYPE_BONUS:
                m_auiEncounter[5] = uiData;
                if(uiData == IN_PROGRESS)
                {
                  if(Creature* Corruptor = instance->GetCreature(m_uiCorruptorGUID))
                     Corruptor->SetPhaseMask(1, true);
                  DoUpdateWorldState(WORLD_STATE_COS_TIME_ON, 1);
                  DoUpdateWorldState(WORLD_STATE_COS_TIME_COUNT, 25);  
                } 
                break;
            case TYPE_MALGANIS:
                m_auiEncounter[6] = uiData;
                if (uiData == DONE)
                {
                    DoRespawnGameObject(m_uiMalChestGUID, 30*MINUTE);
                    if (GameObject* pGo = instance->GetGameObject(m_uiMalChestGUID))
                        pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                    if (Creature* pChromi2 = instance->GetCreature(m_uiChromi02GUID))
                        pChromi2->SetVisibility(VISIBILITY_OFF);
                    if (GameObject* pGo = instance->GetGameObject(m_uiExitGUID))
                        pGo->SetGoState(GO_STATE_ACTIVE);
                }
                break;
        }
    }

    void SetData64(uint32 uiData, uint64 uiGuid)
    {
        switch(uiData)
        {
            case NPC_SALRAMM:
                m_uiSalrammGUID = uiGuid;
                break; 
            case NPC_MALGANIS:
                m_uiMalganisGUID = uiGuid;
                break; 
        }
    }

    uint32 GetData(uint32 uiType)
    {
        switch(uiType)
        {
            case TYPE_QUEST:
                return m_auiEncounter[0];
            case TYPE_INTRO:
                return m_auiEncounter[1];
            case TYPE_PHASE:
                return m_auiEncounter[2];
            case TYPE_ENCOUNTER:
                return m_auiEncounter[3];
            case TYPE_WING:
                return m_auiEncounter[4];
            case TYPE_BONUS:
                return m_auiEncounter[5];
            case TYPE_MALGANIS:
                return m_auiEncounter[6];
        }
        return 0;
    }

    void Update(uint32 uiDiff)
    {
       if(m_auiEncounter[5] == IN_PROGRESS)
       {
         if(m_uiHeroicTimer < uiDiff)
         {
             m_auiEncounter[5] = FAIL;
             DoUpdateWorldState(WORLD_STATE_COS_TIME_ON, 0);
             if(Creature* Corruptor = instance->GetCreature(m_uiCorruptorGUID))
               Corruptor->SetPhaseMask(0, true);

         }else m_uiHeroicTimer -= uiDiff;

         if(m_uiHeroicTimer < m_uiLastTimer - 60000)
         {
            m_uiLastTimer = m_uiHeroicTimer;
            uint32 tMinutes = m_uiHeroicTimer / 60000;
            DoUpdateWorldState(WORLD_STATE_COS_TIME_COUNT, tMinutes);
         }
       }
 
       return;
    }
};

InstanceData* GetInstanceData_instance_culling_of_stratholme(Map* pMap)
{
    return new instance_culling_of_stratholme(pMap);
}

void AddSC_instance_culling_of_stratholme()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_culling_of_stratholme";
    newscript->GetInstanceData = &GetInstanceData_instance_culling_of_stratholme;
    newscript->RegisterSelf();
}
