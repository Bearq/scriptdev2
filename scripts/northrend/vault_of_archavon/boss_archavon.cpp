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
SDName: Boss_Archavon_The_Stone_Watcher
SD%Author: Fixed by Bear
SD%Complete: 100%
SDComment:
SDCategory: Vault of Archavon
EndScriptData */

#include "precompiled.h"
#include "vault_of_archavon.h"

enum
{
    SPELL_ROCK_SHARDS_LEFT_N                = 58695,
    SPELL_ROCK_SHARDS_LEFT_H                = 60883,
    SPELL_ROCK_SHARDS_RIGHT_N               = 58696,
    SPELL_ROCK_SHARDS_RIGHT_H               = 60884,
    SPELL_CRUSHING_LEAP_N                   = 58960,
    SPELL_CRUSHING_LEAP_H                   = 60894,
    SPELL_STOMP_N                           = 58663,
    SPELL_STOMP_H                           = 60880,
    SPELL_IMPALE_DMG_N                      = 58666,
    SPELL_IMPALE_DMG_H                      = 60882,
    SPELL_IMPALE_STUN                       = 50839,
    SPELL_BERSERK                           = 47008,

};

struct MANGOS_DLL_DECL boss_archavonAI : public ScriptedAI
{
    boss_archavonAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiEvadeCheckCooldown;
    uint32 m_uiBerserkTimer;
    uint32 m_uiRockShardsTimer;
    bool m_bRockShardsInProgress;
    uint32 m_uiRockShardsProgressTimer;
    uint32 m_uiRockShardTimer;
    bool m_bRLRockShard;
    ObjectGuid m_pRockShardsTargetGuid;
    uint32 m_uiCrushingLeapTimer;
    uint32 m_uiCloudTimer;
    uint32 m_uiStompTimer;
    uint32 m_uiImpaleAfterStompTimer;
    bool m_bImpaleInProgress;

    void Reset()
    {
        m_uiEvadeCheckCooldown = 2000;
        m_uiBerserkTimer = 300000;
        m_uiRockShardsTimer = 15000;
        m_bRockShardsInProgress = false;
        m_uiRockShardsProgressTimer = 3000;
        m_uiRockShardTimer = 0;
        m_bRLRockShard = true;
        m_pRockShardsTargetGuid.Clear();
        m_uiCrushingLeapTimer = 30000;
        m_uiStompTimer = 45000;
        m_uiImpaleAfterStompTimer = 1000;
        m_bImpaleInProgress = false;

        if(m_pInstance)
            m_pInstance->SetData(TYPE_ARCHAVON, NOT_STARTED);
    }

    void Aggro(Unit *pWho)
    {
        if(m_pInstance)
            m_pInstance->SetData(TYPE_ARCHAVON, IN_PROGRESS);
    }

    void JustDied(Unit* pKiller)
    {
        if(m_pInstance)
            m_pInstance->SetData(TYPE_ARCHAVON, DONE);
    }

   Unit* SelectTargetWithinDist()
   {
        ThreatList const& m_threatlist = m_creature->getThreatManager().getThreatList();

        if (m_threatlist.empty())
            return NULL;

        GUIDList distPositive;
        for (ThreatList::const_iterator itr = m_threatlist.begin(); itr!= m_threatlist.end(); ++itr)
        {
            if (Unit* pTemp = m_creature->GetMap()->GetUnit((*itr)->getUnitGuid()))
            {
                //player within 80 yards
                if ((pTemp->GetTypeId() == TYPEID_PLAYER && !m_creature->IsWithinDist(pTemp, 10.0f) && m_creature->IsWithinDist(pTemp, 80.0f)))
                    distPositive.push_back(pTemp->GetObjectGuid());
            }
        }

        if (!distPositive.empty())
        {
            GUIDList::iterator m_uiPlayerGUID = distPositive.begin();
            advance(m_uiPlayerGUID, (rand()%distPositive.size()));

            if (Player* pTemp = m_creature->GetMap()->GetPlayer(*m_uiPlayerGUID))
                return pTemp;
        }
        return NULL;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiEvadeCheckCooldown < uiDiff)
        {
            if (m_creature->GetDistance2d(140.34f, -102.34f) > 80.0f)
            {
                EnterEvadeMode();
                return;
            }
            m_uiEvadeCheckCooldown = 2000;
        }
        else
            m_uiEvadeCheckCooldown -= uiDiff;

        if(m_uiCrushingLeapTimer < uiDiff)
        {
            if (Unit* pTarget = SelectTargetWithinDist())
            {
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_CRUSHING_LEAP_N : SPELL_CRUSHING_LEAP_H);
                m_uiCrushingLeapTimer = 30000;
            }
        }else m_uiCrushingLeapTimer -= uiDiff;
            
        if (m_bImpaleInProgress)
        {
            if (m_uiImpaleAfterStompTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->getVictim())
                {
                    DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_IMPALE_DMG_N : SPELL_IMPALE_DMG_H);
                    pTarget->CastSpell(pTarget, SPELL_IMPALE_STUN, true);
                }
                m_bImpaleInProgress = false;
            }
            else
            {
                m_uiImpaleAfterStompTimer -= uiDiff;
                return;
            }
        }

        if (m_bRockShardsInProgress)
        {
            if (m_uiRockShardsProgressTimer < uiDiff)
            {
                m_bRockShardsInProgress = false;
                if (!m_pRockShardsTargetGuid.IsEmpty())
                    if (Unit* m_pRockShardsTarget = m_creature->GetMap()->GetUnit(m_pRockShardsTargetGuid))
                        m_creature->getThreatManager().addThreat(m_pRockShardsTarget, -100000000.0f);
                return;
            }
            else
                m_uiRockShardsProgressTimer -= uiDiff;

            if (m_uiRockShardTimer < uiDiff)
            {
                if (Unit* m_pRockShardsTarget = m_creature->GetMap()->GetUnit(m_pRockShardsTargetGuid))
                    if (m_pRockShardsTarget->isAlive())
                    {
                        DoCast(m_pRockShardsTarget, m_bIsRegularMode ? (m_bRLRockShard ? SPELL_ROCK_SHARDS_LEFT_N : SPELL_ROCK_SHARDS_RIGHT_N) : (m_bRLRockShard ? SPELL_ROCK_SHARDS_LEFT_H : SPELL_ROCK_SHARDS_RIGHT_H));
                        m_bRLRockShard = !m_bRLRockShard;
                    }
                    m_uiRockShardTimer = 100;
            }
            else
                m_uiRockShardsTimer -= uiDiff;

            return;
        }

        if (m_uiRockShardsTimer < uiDiff)
        {
            m_bRockShardsInProgress = true;
            m_uiRockShardsProgressTimer = 3000;
            m_bRLRockShard = true;
            if (Unit* m_pRockShardsTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                m_pRockShardsTargetGuid = m_pRockShardsTarget->GetObjectGuid();
                m_creature->getThreatManager().addThreat(m_pRockShardsTarget, 100000000.0f);
            }
            m_uiRockShardsTimer = 15000+rand()%15000;
            return;
        }
        else
            m_uiRockShardsTimer -= uiDiff;

        if (m_uiStompTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_STOMP_N : SPELL_STOMP_H);
            m_uiImpaleAfterStompTimer = 1000;
            m_bImpaleInProgress = true;
            m_uiStompTimer = 45000+rand()%15000;
        }
        else
            m_uiStompTimer -= uiDiff;

        if (m_uiBerserkTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BERSERK);
            m_uiBerserkTimer = 60000;
        }
        else
            m_uiBerserkTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_archavon(Creature *pCreature)
{
    return new boss_archavonAI (pCreature);
};

void AddSC_boss_archavon()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_archavon";
    newscript->GetAI = &GetAI_boss_archavon;
    newscript->RegisterSelf();
};
