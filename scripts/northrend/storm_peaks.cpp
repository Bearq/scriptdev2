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
SDName: Storm_Peaks
SD%Complete: 100
SDComment: Vendor Support (31247). Quest support: 12970, 12684, 12983
SDCategory: Storm Peaks
EndScriptData */

/* ContentData
npc_loklira_the_crone
npc_roxi_ramrocket
npc_frostborn_scout
npc_harnessed_icemaw
EndContentData */

#include "precompiled.h"

/*######
## npc_frostborn_scout
######*/

enum Scout
{
    QUEST_MISSING_SCOUT          = 12864,

    GOSSIP_TEXTID_SCOUT_1        = 13611,
    GOSSIP_TEXTID_SCOUT_2        = 13612,
    GOSSIP_TEXTID_SCOUT_3        = 13613,
    GOSSIP_TEXTID_SCOUT_4        = 13614

};

#define GOSSIP_ITEM_SCOUT_1     "Are you okay? I've come to take you back to Frosthold if you can stand."
#define GOSSIP_ITEM_SCOUT_2     "I'm sorry that I didn't get here sooner. What happened?"
#define GOSSIP_ITEM_SCOUT_3     "I'll go get some help. Hang in there."

bool GossipHello_npc_frostborn_scout(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_MISSING_SCOUT) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SCOUT_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SCOUT_1, pCreature->GetObjectGuid());
        return true;
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_frostborn_scout(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SCOUT_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SCOUT_2, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SCOUT_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SCOUT_3, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SCOUT_4, pCreature->GetObjectGuid());
            pPlayer->AreaExploredOrEventHappens(QUEST_MISSING_SCOUT);
            break;
    }
    return true;
}

/*######
## npc_loklira_the_crone
######*/

#define GOSSIP_ITEM_TELL_ME         "Tell me about this proposal."
#define GOSSIP_ITEM_WHAT_HAPPENED   "What happened then?"
#define GOSSIP_ITEM_YOU_WANT_ME     "You want me to take part in the Hyldsmeet to end the war?"
#define GOSSIP_ITEM_VERY_WELL       "Very well. I'll take part in this competition."

enum
{
    GOSSIP_TEXTID_LOKLIRA1    = 13777,
    GOSSIP_TEXTID_LOKLIRA2    = 13778,
    GOSSIP_TEXTID_LOKLIRA3    = 13779,
    GOSSIP_TEXTID_LOKLIRA4    = 13780,

    QUEST_THE_HYLDSMEET       = 12970,

    CREDIT_LOKLIRA            = 30467
};

bool GossipHello_npc_loklira_the_crone(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(QUEST_THE_HYLDSMEET) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TELL_ME, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOKLIRA1, pCreature->GetObjectGuid());
        return true;
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_loklira_the_crone(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_WHAT_HAPPENED, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOKLIRA2, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_YOU_WANT_ME, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOKLIRA3, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_VERY_WELL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOKLIRA4, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->TalkedToCreature(CREDIT_LOKLIRA, pCreature->GetObjectGuid());
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
    }
    return true;
}

/*######
## npc_thorim
######*/

#define GOSSIP_ITEM_THORIM1         "Can you tell me what became of Sif?"
#define GOSSIP_ITEM_THORIM2         "He did more than that, Thorim. He controls Ulduar now."
#define GOSSIP_ITEM_THORIM3         "It needn't end this way."

enum
{
    QUEST_SIBLING_RIVALRY           = 13064,

    SPELL_THORIM_STORY_KILL_CREDIT  = 56940,

    GOSSIP_TEXTID_THORIM1           = 13799,
    GOSSIP_TEXTID_THORIM2           = 13801,
    GOSSIP_TEXTID_THORIM3           = 13802,
    GOSSIP_TEXTID_THORIM4           = 13803
};

bool GossipHello_npc_thorim(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(QUEST_SIBLING_RIVALRY) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_THORIM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM1, pCreature->GetObjectGuid());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_npc_thorim(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_THORIM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM2, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_THORIM3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM3, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM4, pCreature->GetObjectGuid());
            pCreature->CastSpell(pPlayer, SPELL_THORIM_STORY_KILL_CREDIT, true);
            break;
    }

    return true;
}

/*######
## npc_roxi_ramrocket
######*/

#define GOSSIP_TEXT_RAMROCKET1  "How do you fly in this cold climate?"
#define GOSSIP_TEXT_RAMROCKET2  "I hear you sell motorcycle parts."

enum
{
    SPELL_MECHANO_HOG           = 60866,
    SPELL_MEKGINEER_CHOPPER     = 60867
};

bool GossipHello_npc_roxi_ramrocket(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isTrainer())
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_RAMROCKET1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

    if (pCreature->isVendor())
    {
        if (pPlayer->HasSpell(SPELL_MECHANO_HOG) || pPlayer->HasSpell(SPELL_MEKGINEER_CHOPPER))
        {
            if (pPlayer->HasSkill(SKILL_ENGINEERING) && pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 450)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_RAMROCKET2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
        }
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_roxi_ramrocket(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_TRAIN:
            pPlayer->SEND_TRAINERLIST(pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_TRADE:
            pPlayer->SEND_VENDORLIST(pCreature->GetObjectGuid());
            break;
    }

    return true;
}

/*#####
## go_heart_of_the_storm
#####*/

enum
{
    QUEST_HEART_OF_THE_STORM    = 12998,
    SPELL_STORMS_FURY           = 56485,
    NPC_OVERSEER_NARVIR         = 30299,
    DESPAWN_TIMER               = 30000,
    SAY_NARVIR1                 = -1532116,
    SAY_NARVIR2                 = -1532117
};

bool GOUse_go_heart_of_the_storm(Player* pPlayer, GameObject* pGo)
{
    Creature* pNarvir = GetClosestCreatureWithEntry(pPlayer, NPC_OVERSEER_NARVIR, 25.0f);
    if (pNarvir)
        return true;

    if (pPlayer->GetQuestStatus(QUEST_HEART_OF_THE_STORM) == QUEST_STATUS_INCOMPLETE)
    {
        if (Creature* pNarvir = pPlayer->SummonCreature(NPC_OVERSEER_NARVIR, 7315.48f, -711.069f, 791.611f, 4.65591f, TEMPSUMMON_TIMED_DESPAWN, DESPAWN_TIMER) )
		
        {
            pNarvir->CastSpell(pPlayer, SPELL_STORMS_FURY, false);
			pGo->DestroyForPlayer(pPlayer, false);
            pPlayer->KilledMonsterCredit(NPC_OVERSEER_NARVIR, pNarvir->GetObjectGuid());
        }
    }
    return true;
};

struct MANGOS_DLL_DECL npc_overseer_narvir : public ScriptedAI
{
    npc_overseer_narvir(Creature*pCreature) : ScriptedAI(pCreature) { Reset();}

    bool MovementStarted;
    uint32 uiTimer;
    uint32 uiPhase;


    void Reset () 
    {
    uiTimer = 1000;
    uiPhase = 0;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (uiTimer<= uiDiff)
        {

            switch(uiPhase)
            {
            case 0: m_creature->GetMotionMaster()->MovePoint(1, 7314.01f, -727.78f, 791.611f);
                  uiTimer = 3000;
                  uiPhase++;
                  break;
            case 1: DoScriptText(SAY_NARVIR1, m_creature);
                uiTimer = 6000;
                uiPhase++;
                break;
            case 2: DoScriptText(SAY_NARVIR2, m_creature);
                uiTimer = 4000;
                uiPhase++;
                break;
            case 3: m_creature->ForcedDespawn(1000);
                uiTimer = 0;
                uiPhase++;
                break;
            }
        }
        else uiTimer -= uiDiff;
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type != POINT_MOTION_TYPE || !MovementStarted) 
            return;
    }
};

CreatureAI* GetAI_npc_overseer_narvir(Creature* pCreature)
{
    return new npc_overseer_narvir (pCreature);
}

/********
** npc_harnessed_icemaw
*********/
struct MANGOS_DLL_DECL npc_harnessed_icemawAI : public ScriptedAI
{
    npc_harnessed_icemawAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    bool m_bIsHerKind;

    uint32 m_uiEventTimer;
    uint32 m_uiPhase;

    void Reset () 
    {
        m_uiEventTimer = 4000;
        m_uiPhase = 0;

        m_bIsHerKind = true;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiEventTimer < uiDiff)
        {
            switch(m_uiPhase)
            {
                case 0: 
                    m_creature->GetMotionMaster()->MovePoint(0, 7329.4262f, -2095.0290f, 772.7434f);
                    m_uiPhase = 1;
                    m_uiEventTimer = 5000;
                    break;
                case 1:
                    m_creature->GetMotionMaster()->MovePoint(0, 7286.2041f, -2112.6110f, 775.8190f);
                    m_uiPhase = 2;
                    m_uiEventTimer = 8000;
                    break;
                case 2:
                    m_creature->GetMotionMaster()->MovePoint(0, 7239.8691f, -2120.1247f, 777.5736f);
                    m_uiPhase = 3;
                    m_uiEventTimer = 8000;
                    break;
                case 3:
                    m_creature->GetMotionMaster()->MovePoint(0, 7195.2670f, -2108.7006f, 766.2100f);
                    m_uiPhase = 4;
                    m_uiEventTimer = 15000;
                    break;
                case 4:
                    m_creature->GetMotionMaster()->MovePoint(0, 7137.6996f, -2140.6071f, 761.1889f);
                    m_uiPhase = 5;
                    m_uiEventTimer = 40000;
                    break;
                case 5:
                    m_creature->GetMotionMaster()->MovePoint(0, 7062.8837f, -1914.8781f, 782.7465f);
                    m_uiPhase = 6;
                    m_uiEventTimer = 5000;
                    break;
                case 6:
                    m_creature->GetMotionMaster()->MovePoint(0, 7088.5083f, -1889.2677f, 787.8016f);
                    m_uiPhase = 7;
                    m_uiEventTimer = 5000;
                    break;
                case 7:
                    m_creature->GetMotionMaster()->MovePoint(0, 7030.2773f, -1880.2751f, 800.9303f);
                    m_uiPhase = 8;
                    m_uiEventTimer = 10000;
                    break;
                case 8:
                    m_creature->GetMotionMaster()->MovePoint(0, 7007.7768f, -1713.0822f, 0819.7851f);
                    m_uiPhase = 9;
                    m_uiEventTimer = 25000;
                    break;
                case 9:
                    m_creature->GetMotionMaster()->MovePoint(0, 6947.6542f, -1724.4016f, 820.6044f);
                    m_uiPhase = 10;
                    m_uiEventTimer = 10000;
                    break;
                case 10:
                    m_creature->GetMotionMaster()->MovePoint(0, 6883.1499f, -1686.7318f, 820.3461f);
                    m_uiPhase = 11;
                    m_uiEventTimer = 10000;
                    break;
                case 11:
                    m_creature->GetMotionMaster()->MovePoint(0, 6822.9223f, -1703.5740f, 820.5421f);
                    m_bIsHerKind = false;
                    break;
                default:
                    break;
            }
        }else m_uiEventTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_harnessed_icemaw(Creature* pCreature)
{
    return new npc_harnessed_icemawAI(pCreature);
}

void AddSC_storm_peaks()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "npc_frostborn_scout";
    newscript->pGossipHello = &GossipHello_npc_frostborn_scout;
    newscript->pGossipSelect = &GossipSelect_npc_frostborn_scout;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_loklira_the_crone";
    newscript->pGossipHello = &GossipHello_npc_loklira_the_crone;
    newscript->pGossipSelect = &GossipSelect_npc_loklira_the_crone;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_thorim";
    newscript->pGossipHello = &GossipHello_npc_thorim;
    newscript->pGossipSelect = &GossipSelect_npc_thorim;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_roxi_ramrocket";
    newscript->pGossipHello = &GossipHello_npc_roxi_ramrocket;
    newscript->pGossipSelect = &GossipSelect_npc_roxi_ramrocket;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_heart_of_the_storm";
    newscript->pGOUse = &GOUse_go_heart_of_the_storm;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_harnessed_icemaw";
    newscript->GetAI = &GetAI_npc_harnessed_icemaw;
    newscript->RegisterSelf();
}
