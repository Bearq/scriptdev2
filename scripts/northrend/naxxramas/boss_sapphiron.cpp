/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Sapphiron
SD%Complete: 80
SDComment: Some spells need core implementation
SDCategory: Naxxramas

przemratajczak:
ToDo:
* hack - with dmg from frostbreath
* 
* maybe somehow simplify intro?
EndScriptData */

/* Additional comments:
 * Bugged spells:   28560 (needs maxTarget = 1, Summon of 16474 implementation, TODO, 30s duration)
 *                  28526 (needs ScriptEffect to cast 28522 onto random target)
 *
 * Blizzard might need handling for their movement
 * SetHover hackz must be replaced by proper opcodes 04D3(Liftoff) 04D4(Landing)
 * Achievement-criteria check needs implementation
 *
 * Frost-Breath ability: the dummy spell 30101 is self cast, so it won't take the needed delay of ~7s until it reaches its target
 *                       As Sapphiron is displayed visually in hight (hovering), and the spell is cast with target=self-location
 *                       which is still on the ground, the client shows a nice slow falling of the visual animation
 *                       Insisting on using the Dummy-Effect to cast the breath-dmg spells, would require, to relocate Sapphi internally,
 *                       and to hack the targeting to be "on the ground" - Hence the prefered way as it is now!
 */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    EMOTE_BREATH                = -1533082,
    EMOTE_ENRAGE                = -1533083,
    EMOTE_FLY                   = -1999768,
    EMOTE_GROUND                = -1999767,

    SPELL_ICEBOLT               = 28522,
    //SPELL_ICEBOLT             = 28526,    // eff 77 implicit 1/0 but with casttime (not used)
    SPELL_FROSTBREATH           = 28524,
    SPELL_FROSTBREATH_VISUAL    = 30101,
    SPELL_SAPPHIRONS_WING_BUFFET= 29328,

    SPELL_FROST_AURA            = 28531,
    H_SPELL_FROST_AURA          = 55799,

    SPELL_LIFE_DRAIN            = 28542,
    H_SPELL_LIFE_DRAIN          = 55665,

    SPELL_TAIL_SWEEP            = 55697,
    H_SPELL_TAIL_SWEEP          = 55696,

    SPELL_CLEAVE                = 19983,
    SPELL_BESERK                = 26662,

    //SPELL_SUMMON_BLIZZARD     = 28560,    // script effect 100yd (not used)
    SPELL_ACTIVATE_BLIZZARD     = 29969,    // dummy
    SPELL_DEACTIVATE_BLIZZARD   = 29970,
    SPELL_CHILL                 = 28547,    // cast by Blizzard NPC
    SPELL_CHILL_H               = 55699,    // cast by Blizzard NPC (h)
    SPELL_SAPPHIRON_DIES        = 29357,    // dummy
    SPELL_SAPPHIRON_ACHI_CHECK  = 60539,    // script effect

    SPELL_HOVER                 = 57764,

    POINT_HOME                  = 0,
    NPC_WING_BUFFET             = 17025,
    GO_ICEBLOCK                 = 181247,   // should be summoned by some spell
    NPC_YOU_KNOW_WHO            = 16474,

    PHASE_FIGHT_ON_GROUND       = 0,
    PHASE_RETURN_TO_THE_CENTER  = 1,
    PHASE_ICEBOLTS              = 2,
    PHASE_LANDING               = 3
};

struct MANGOS_DLL_DECL boss_sapphironAI : public ScriptedAI
{
    boss_sapphironAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_naxxramas* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bCastingFrostBreath; // hack part
    bool m_bHundredClub;        // achievement check
    float fHomeX, fHomeY, fHomeZ;
    std::map<ObjectGuid /*owner*/, ObjectGuid /*GO*/> m_mIceblocks;

    int8 m_iIceboltCount;
    uint32 m_uiIceboltTimer;
    uint32 m_uiLifeDrainTimer;
    uint32 m_uiBlizzardTimer;
    uint32 m_uiTailSweepTimer;
    uint32 m_uiCleaveTimer;
    uint32 m_uiFlyTimer;
    uint32 m_uiBeserkTimer;
    uint32 m_uiPhase;
    uint32 m_uiLandTimer;
    uint32 m_uiRespawnTime;
    uint32 m_uiHundredClubCheckTimer;
    ObjectGuid m_uiWingBuffetGuid;

    void Reset()
    {
        m_uiLifeDrainTimer  = 24000;
        m_uiBlizzardTimer   = 10000;
        m_uiTailSweepTimer  = 10000;
        m_uiCleaveTimer     = 10000;
        m_uiFlyTimer        = 45000;
        m_uiIceboltTimer    = 4000;
        m_uiLandTimer       = 2000;
        m_uiRespawnTime     = 22000;
        m_uiBeserkTimer     = 15*MINUTE*IN_MILLISECONDS;
        m_uiPhase           = PHASE_FIGHT_ON_GROUND;
        m_iIceboltCount     = 0;
        m_uiWingBuffetGuid  = 0;
        m_bCastingFrostBreath = false;
        m_bHundredClub      = true;
        m_mIceblocks.clear();
        m_uiHundredClubCheckTimer = 5000;
        m_creature->GetRespawnCoord(fHomeX, fHomeY, fHomeZ);
    }

    Unit* SelectTargetForIcebolt()
    {
         // get `iceblockers`
         std::list<Unit*> lPotentialTargets;
         ThreatList const& tList = m_creature->getThreatManager().getThreatList();
         for (ThreatList::const_iterator i = tList.begin();i != tList.end(); ++i)
         {
             Unit* pUnit = m_creature->GetMap()->GetUnit((*i)->getUnitGuid());
             if (pUnit && pUnit->GetTypeId() == TYPEID_PLAYER &&
                 pUnit->isAlive() && !pUnit->HasAura(SPELL_ICEBOLT))
                 lPotentialTargets.push_back(pUnit);
         }

         if (lPotentialTargets.empty())
             return NULL;

         std::list<Unit*>::iterator i = lPotentialTargets.begin();
         advance(i, (rand()%lPotentialTargets.size()));
         return (*i);
    }     

    //!!! Frost Breath HACK!!!
    // Since GOs are not valid obstacle for LoS we need this
    bool IsBehindIceBlock(Unit* pVictim)
    {
        // get `iceblockers`
         std::list<Unit*> lBlockList;
         ThreatList const& tList = m_creature->getThreatManager().getThreatList();
         for (ThreatList::const_iterator i = tList.begin();i != tList.end(); ++i)
         {
             Unit* pUnit = m_creature->GetMap()->GetUnit((*i)->getUnitGuid());
             if (pUnit && pUnit->HasAura(SPELL_ICEBOLT))
                 lBlockList.push_back(pUnit);
         }

         if (lBlockList.empty())
             return false;

         float fVictimX, fVictimY, fVictimZ;
         float fSapphironX, fSapphironY, fSapphironZ;
         m_creature->GetPosition(fSapphironX, fSapphironY, fSapphironZ);
         pVictim->GetPosition(fVictimX, fVictimY, fVictimZ);
         for (std::list<Unit*>::iterator itr = lBlockList.begin(); itr != lBlockList.end(); ++itr)
         {
             float fDistToVictim = m_creature->GetDistance(pVictim);
             float fDistToBlocker = m_creature->GetDistance(*itr);

             // if victim stands between blocker and sapphiron or too far from blocker
             if (fDistToVictim < fDistToBlocker || fDistToBlocker + 5.0f < fDistToVictim)
                 continue;

             float fBlockX, fBlockY, fBlockZ;
             float a = 0.0f;
             float b = 0.0f;
             (*itr)->GetPosition(fBlockX, fBlockY, fBlockZ);
             // y = ax + b
             // now we are looking for line eqation connecting potencial victim and sapphiron
             a = (fSapphironX - fVictimX)/(fSapphironY - fVictimY);
             b = fSapphironX - a * fSapphironY;
             // if we now have all neccessary parameters lets check if blocking unit stands approximetly on line
             if ((fBlockX - a * fBlockY - b) < 3.0f && (fBlockX - a * fBlockY - b) > -3.0f)
                 return true;
         }
         return false;
    }

    //!!! Frost Breath HACK!!!
    void DamageDeal(Unit* pDoneTo, uint32& uiDamage)
    {
        if (!pDoneTo && !pDoneTo->isAlive())
            return;

        if (IsBehindIceBlock(pDoneTo) && m_bCastingFrostBreath)
            uiDamage = 0;
    }

    void SpellHitTarget(Unit *pVictim, const SpellEntry *spellInfo)
    {
        if (!pVictim || !spellInfo)
            return;

        if (spellInfo->Id == SPELL_FROSTBREATH)
        {
            if (SpellAuraHolderPtr holder = pVictim->GetSpellAuraHolder(SPELL_ICEBOLT))
            {
                holder->SetAuraDuration(500);
                holder->SendAuraUpdate(false);
            }

            std::map<ObjectGuid, ObjectGuid>::iterator itr = m_mIceblocks.find(pVictim->GetObjectGuid());
            if (itr != m_mIceblocks.end())
            {
                // find my Iceblock
                if (GameObject *pGO = m_creature->GetMap()->GetGameObject(itr->second))
                {
                    pGO->Delete();
                    m_mIceblocks.erase(itr);
                }
            }
        }
        else if (spellInfo->Id == SPELL_ICEBOLT)
        {
            if (pVictim->HasAura(SPELL_ICEBOLT) && !pVictim->GetGameObject(spellInfo->Id))
            {
                if (GameObject *pGO = pVictim->SummonGameobject(GO_ICEBLOCK, pVictim->GetPositionX(), pVictim->GetPositionY(), pVictim->GetPositionZ(), 0.0f, 30))
                {
                    pGO->SetSpellId(spellInfo->Id);
                    pVictim->AddGameObject(pGO);
                    m_mIceblocks.insert(std::make_pair(pVictim->GetObjectGuid(), pGO->GetObjectGuid()));
                }
            }
        }
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SAPPHIRON, IN_PROGRESS);

        m_creature->SetInCombatWithZone();
        DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_FROST_AURA : H_SPELL_FROST_AURA);
    }

    void JustDied(Unit* pKiller)
    {
        DoCastSpellIfCan(m_creature, SPELL_DEACTIVATE_BLIZZARD, CAST_TRIGGERED);

        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_SAPPHIRON, DONE);
            if (m_bHundredClub)
                m_pInstance->SetData(m_bIsRegularMode ? ACHIEV_CRIT_HUNDRED_CLUB_N : ACHIEV_CRIT_HUNDRED_CLUB_H, DONE);
        }
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SAPPHIRON, FAIL);

        DoCastSpellIfCan(m_creature, SPELL_DEACTIVATE_BLIZZARD, CAST_TRIGGERED);
        Creature* pWingBuffet = m_creature->GetMap()->GetCreature(m_uiWingBuffetGuid);
        if (pWingBuffet && pWingBuffet->isAlive())
            pWingBuffet->ForcedDespawn();

        // after server crash
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, (UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE));
        m_creature->SetVisibility(VISIBILITY_ON);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_YOU_KNOW_WHO)
        {
            if (Unit* pEnemy = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                pSummoned->AI()->AttackStart(pEnemy);
        }
    }

    void MovementInform(uint32 uiMotionType, uint32 uiPointId)
    {
        if (uiMotionType != POINT_MOTION_TYPE)
            return;

        if (uiPointId == POINT_HOME)
        {
            m_creature->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
            DoCast(m_creature, SPELL_HOVER, true);
            m_uiIceboltTimer = 4000;
            m_iIceboltCount = 0;
            DoScriptText(EMOTE_FLY, m_creature);
            if (Creature* pWingBuffet = m_creature->SummonCreature(NPC_WING_BUFFET, fHomeX, fHomeY, fHomeZ, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0))
                m_uiWingBuffetGuid = pWingBuffet->GetObjectGuid();            
            m_uiPhase = PHASE_ICEBOLTS;
        }
    }

    // achievement check
    bool DoHundredClubCheck()
    {
        if (!m_pInstance)
            return false;

        Map::PlayerList const& lPlayers = m_pInstance->instance->GetPlayers();
        for(Map::PlayerList::const_iterator itr = lPlayers.begin(); itr != lPlayers.end(); ++itr)
        {
            if (Player* pPlayer = itr->getSource())
            {
                if (pPlayer->GetResistance(SPELL_SCHOOL_FROST) > 100)
                    return false;
            }
        }

        return true;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // respawntime is calculated duration of GO_sapphirons birth special animation
        // if sapphiron assemble is in progres TYPE_SAPPHIRON = SPECIAL
        if (m_pInstance && m_pInstance->GetData(TYPE_SAPPHIRON) == SPECIAL && m_creature->GetVisibility() == VISIBILITY_OFF)
        {
            GameObject* pSapphironBirth = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_SAPPHIRON_BIRTH));
            if (pSapphironBirth && pSapphironBirth->GetRespawnTime() == 0)
            {
                pSapphironBirth->SetRespawnTime(604800);
                pSapphironBirth->Delete();
            }
            if (m_uiRespawnTime < uiDiff)
            {
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, (UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE));
                m_creature->SetVisibility(VISIBILITY_ON);
            }
            else
                m_uiRespawnTime -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bHundredClub)
        {
            if (m_uiHundredClubCheckTimer <= uiDiff)
            {
                m_bHundredClub = DoHundredClubCheck();
                m_uiHundredClubCheckTimer = 5000;
            }else m_uiHundredClubCheckTimer -= uiDiff;
        }

        if (m_uiBeserkTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BESERK);
            m_uiBeserkTimer = 300000;
            DoScriptText(EMOTE_ENRAGE, m_creature);
        }
        else
            m_uiBeserkTimer -= uiDiff;

        switch(m_uiPhase)
        {
            case PHASE_FIGHT_ON_GROUND:

                if (m_creature->GetHealthPercent() > 10.0f)
                {
                    if (m_uiFlyTimer < uiDiff)
                    {
                        m_creature->InterruptNonMeleeSpells(false);
                        SetCombatMovement(false);
                        m_creature->GetMotionMaster()->MovePoint(POINT_HOME, fHomeX, fHomeY, fHomeZ);
                        m_uiPhase = PHASE_RETURN_TO_THE_CENTER;
                        return;
                    }
                    else
                        m_uiFlyTimer -= uiDiff;
                }

                if (m_uiLifeDrainTimer < uiDiff)
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                        DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_LIFE_DRAIN : H_SPELL_LIFE_DRAIN);
                    m_uiLifeDrainTimer = 24000;
                }
                else
                    m_uiLifeDrainTimer -= uiDiff;

                if (m_uiBlizzardTimer < uiDiff)
                {
                    DoCastSpellIfCan(m_creature, SPELL_ACTIVATE_BLIZZARD);
                    m_uiBlizzardTimer = 20000;
                }
                else
                    m_uiBlizzardTimer -= uiDiff;

                if (m_uiCleaveTimer < uiDiff)
                {
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE);
                    m_uiCleaveTimer = urand(7000, 10000);
                }
                else
                    m_uiCleaveTimer -= uiDiff;

                if (m_uiTailSweepTimer < uiDiff)
                {
                    DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_TAIL_SWEEP : H_SPELL_TAIL_SWEEP);
                    m_uiTailSweepTimer = urand(10000, 15000);
                }
                else
                    m_uiTailSweepTimer -= uiDiff;

                DoMeleeAttackIfReady();
                EnterEvadeIfOutOfCombatArea(uiDiff);
                break;

            // walking back to the center, he is supposed to do nothing at this time
            case PHASE_RETURN_TO_THE_CENTER:
                return;

            // casting ice bolts (2:3 n/h) than visual effect (ball) of Frost Breath and waiting untill ball reach ground
            case PHASE_ICEBOLTS:
                if (m_uiIceboltTimer < uiDiff)
                {
                    if (Unit* pTarget = SelectTargetForIcebolt())
                        DoCastSpellIfCan(pTarget, SPELL_ICEBOLT);

                    ++m_iIceboltCount;

                    if (m_iIceboltCount >= (m_bIsRegularMode ? 2 : 3))
                    {
                        DoScriptText(EMOTE_BREATH, m_creature);
                        Creature* pWingBuffet = m_creature->GetMap()->GetCreature(m_uiWingBuffetGuid);
                        if (pWingBuffet && pWingBuffet->isAlive())
                            DoCastSpellIfCan(pWingBuffet, SPELL_FROSTBREATH_VISUAL, CAST_TRIGGERED);
                        m_uiPhase = PHASE_LANDING;
                        m_uiLandTimer = 7000;
                    }
                    m_uiIceboltTimer = 4000;
                }
                else
                    m_uiIceboltTimer -= uiDiff;
                break;

            // when ball of Frostbreath reaches ground dmg and visual effect of AoE Frostbreath is triggered
            // Sapphiron descends to the ground to rejoin melee fight
            case PHASE_LANDING:

                if (m_uiLandTimer < uiDiff)
                {
                    m_uiPhase = PHASE_FIGHT_ON_GROUND;
                    // !!HACK!! bool variable needed to determine when DealDmg should be = 0.
                    // dunno how to check which dmg was done by which spell to disable only
                    // dmg form FrostBreath :/
                    m_bCastingFrostBreath = true;
                    DoCastSpellIfCan(m_creature, SPELL_FROSTBREATH, CAST_TRIGGERED);
                    Creature* pWingBuffet = m_creature->GetMap()->GetCreature(m_uiWingBuffetGuid);
                    if (pWingBuffet && pWingBuffet->isAlive())
                        pWingBuffet->ForcedDespawn();

                    m_creature->HandleEmoteCommand(EMOTE_ONESHOT_LAND);
                    m_creature->RemoveAurasDueToSpell(SPELL_HOVER);
                    m_uiBlizzardTimer = 5000;
                    m_uiFlyTimer = 45000;
                    DoScriptText(EMOTE_GROUND, m_creature);
                    SetCombatMovement(true);
                    m_creature->GetMotionMaster()->MovementExpired(true);
                    if (m_creature->getVictim())
                        m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    m_bCastingFrostBreath = false;
                }
                else
                    m_uiLandTimer -= uiDiff;
                break;
        }
    }
};

CreatureAI* GetAI_boss_sapphiron(Creature* pCreature)
{
    return new boss_sapphironAI(pCreature);
}

struct MANGOS_DLL_DECL mob_sapphiron_blizzardAI : public ScriptedAI
{
    mob_sapphiron_blizzardAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        Reset();
    }

    instance_naxxramas *m_pInstance;
    bool m_bIsRegularMode;
    bool m_bIsActive;
    uint32 m_uiChillTimer;

    void Reset()
    {
        m_bIsActive    = false;
        m_uiChillTimer = 0;
    }

    void AttackStart(Unit *pWho){}

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bIsActive)
        {
            if (m_uiChillTimer <= uiDiff)
            {
                //DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_CHILL : SPELL_CHILL_H, CAST_TRIGGERED);
                float x, y, z;
                x = m_creature->GetPositionX() + frand(-15.0f, 15.0f);
                y = m_creature->GetPositionY() + frand(-15.0f, 15.0f);
                z = m_creature->GetPositionZ();

                m_creature->CastSpell(x, y, z, m_bIsRegularMode ? SPELL_CHILL : SPELL_CHILL_H, true);
                m_uiChillTimer = 500;
            }else m_uiChillTimer -= uiDiff;
        }
    }
};

bool EffectDummyNPC_spell_sapphiron_encounter_blizzard(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Creature* pCreatureTarget)
{
    if (uiSpellId == SPELL_ACTIVATE_BLIZZARD)
    {
        if (uiEffIndex == EFFECT_INDEX_0)
        {
            if (mob_sapphiron_blizzardAI *pBlizzard = dynamic_cast<mob_sapphiron_blizzardAI*> (pCreatureTarget->AI()))
            {
                pBlizzard->m_bIsActive = true;
                return true;
            }
        }
    }
    else if (uiSpellId == SPELL_DEACTIVATE_BLIZZARD)
    {
        if (uiEffIndex == EFFECT_INDEX_0)
        {
            if (mob_sapphiron_blizzardAI *pBlizzard = dynamic_cast<mob_sapphiron_blizzardAI*> (pCreatureTarget->AI()))
            {
                pBlizzard->m_bIsActive = false;
                return true;
            }
        }
    }
    return false;
}

CreatureAI* GetAI_mob_sapphiron_blizzard(Creature* pCreature)
{
    return new mob_sapphiron_blizzardAI(pCreature);
}

void AddSC_boss_sapphiron()
{
    Script* newscript;
    newscript = new Script;
    newscript->Name = "boss_sapphiron";
    newscript->GetAI = &GetAI_boss_sapphiron;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_sapphiron_blizzard";
    newscript->GetAI = &GetAI_mob_sapphiron_blizzard;
    newscript->pEffectDummyNPC = &EffectDummyNPC_spell_sapphiron_encounter_blizzard;
    newscript->RegisterSelf();
}
