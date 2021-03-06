/* Copyright (C) 2006 - 2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: boss_kologarn
SD%Complete: 90%
SDComment: right arm leaves Kologarn vehicle when a player enters arms vehicle :/
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"
#include "Vehicle.h"

enum
{
    SAY_AGGRO                           = -1603126,
    SAY_SHOCKWAVE                       = -1603127,
    SAY_GRAB                            = -1603128,
    SAY_ARM_LOST_LEFT                   = -1603129,
    SAY_ARM_LOST_RIGHT                  = -1603130,
    SAY_SLAY_1                          = -1603131,
    SAY_SLAY_2                          = -1603132,
    SAY_BERSERK                         = -1603133,
    SAY_DEATH                           = -1603134,

    EMOTE_ARM_RIGHT                     = -1603135,
    EMOTE_ARM_LEFT                      = -1603136,
    EMOTE_STONE_GRIP                    = -1603137,


    //kologarn
    SPELL_OVERHEAD_SMASH		= 63356,
    SPELL_OVERHEAD_SMASH_H		= 64003,
    SPELL_ONE_ARMED_SMASH		= 63573,
    SPELL_ONE_ARMED_SMASH_H		= 64006,
    SPELL_STONE_SHOUT			= 63716,
    SPELL_STONE_SHOUT_H			= 64005,
    SPELL_PETRIFYING_BREATH		= 62030,
    SPELL_PETRIFYING_BREATH_H	= 63980,
    // Focused Eyebeam
    SPELL_FOCUSED_EYEBEAM       = 63342,
    NPC_FOCUSED_EYEBEAM_RIGHT   = 33802,
    NPC_FOCUSED_EYEBEAM_LEFT    = 33632,
    SPELL_EYEBEAM_PERIODIC      = 63347,
    SPELL_EYEBEAM_PERIODIC_H    = 63977,
    SPELL_EYEBEAM_PERIODIC_VIS  = 63369,
    SPELL_EYEBEAM_SUMMON_LEFT   = 63343,
    SPELL_EYEBEAM_SUMMON_RIGHT  = 63701,
    SPELL_EYEBEAM_VISUAL_LEFT   = 63352,
    SPELL_EYEBEAM_VISUAL_LEFT_2 = 63702,
    SPELL_EYEBEAM_VISUAL_RIGHT  = 63676,

    SPELL_ENRAGE                = 26662,
    //left arm
    SPELL_ARM_SWEEP             = 63766,
    SPELL_ARM_SWEEP_H           = 63983,
    SPELL_SHOCKWAVE				= 63783,
    SPELL_SHOCKWAVE_H			= 63982,
    //right arm
    SPELL_STONE_GRIP_GRAB       = 62166,
    SPELL_STONE_GRIP_GRAB_H     = 63981,
    SPELL_STONE_GRIP			= 64290,
    SPELL_STONE_GRIP_H			= 64292,
    SPELL_STONE_GRIP_VEH        = 62056,
    SPELL_STONE_GRIP_VEH_H      = 63985,
    SPELL_STONE_GRIP_KILL_AURA  = 64708,
    //both
    SPELL_ARM_VISUAL			= 64753,
    //rubble
    SPELL_RUMBLE				= 63818,    // on 10 man
    SPELL_STONE_NOVA			= 63978,    // on 25 man
    //NPC ids
    MOB_RUBBLE					= 33768,

    ACHIEV_RUBBLE_AND_ROLL      = 2959,
    ACHIEV_RUBBLE_AND_ROLL_H    = 2960,
    ACHIEV_WITH_OPEN_ARMS       = 2951,
    ACHIEV_WITH_OPEN_ARMS_H     = 2952,
    ACHIEV_DISARMED             = 2953,
    ACHIEV_DISARMED_H           = 2954,
    ACHIEV_IF_LOOKS_COULD_KILL  = 2955,
    ACHIEV_IF_LOOKS_COULD_KILL_H= 2956,
};

float LeftArm[3] = {1784.742f, -39.962f, 448.805f};
float RightArm[3] = {1785.615f, -5.516f, 448.810f};
const float KoloFront[3] = {1771.683f, -24.230f, 448.806f};

// Rubble
struct MANGOS_DLL_DECL mob_ulduar_rubbleAI : public ScriptedAI
{
    mob_ulduar_rubbleAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiStone_Nova_Timer;

    void Reset()
    {
        m_uiStone_Nova_Timer = urand(8000, 12000);
        m_creature->SetRespawnDelay(DAY);
    }

    void UpdateAI(const uint32 diff)
    {
        if (m_pInstance && m_pInstance->GetData(TYPE_KOLOGARN) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiStone_Nova_Timer < diff)
        {
            DoCast(m_creature, m_bIsRegularMode ? SPELL_RUMBLE : SPELL_STONE_NOVA);
            m_uiStone_Nova_Timer = urand(7000, 9000);
        }else m_uiStone_Nova_Timer -= diff;

        DoMeleeAttackIfReady();
    }
 };
 
CreatureAI* GetAI_mob_ulduar_rubble(Creature* pCreature)
{
    return new mob_ulduar_rubbleAI(pCreature);
}

// Left Arm
struct MANGOS_DLL_DECL boss_left_armAI : public ScriptedAI
{
    boss_left_armAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        SetCombatMovement(false);
        pCreature->SetRespawnDelay(7*DAY);
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    void Reset()
    {
        DoCast(m_creature, SPELL_ARM_VISUAL);
    }

    void JustDied(Unit* pKiller)
    {
        if (!m_pInstance || pKiller == m_creature)
            return;

        if (Creature* pTemp = m_pInstance->GetSingleCreatureFromStorage(NPC_KOLOGARN))
        {
            DoScriptText(SAY_ARM_LOST_LEFT, pTemp);
            if (pTemp->isAlive())
                pTemp->DealDamage(pTemp, m_creature->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        }
    }

    void UpdateAI(const uint32 diff){}
};

CreatureAI* GetAI_boss_left_arm(Creature* pCreature)
{
    return new boss_left_armAI(pCreature);
}

// Right Arm
struct MANGOS_DLL_DECL boss_right_armAI : public ScriptedAI
{
    boss_right_armAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        SetCombatMovement(false);
        pCreature->SetRespawnDelay(7*DAY);
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiStone_Grip_Timer;
    uint32 m_uiFreeDamage;
    uint32 m_uiMaxDamage;
    ObjectGuid m_uiGripTargetGUID[3];
    uint8 m_uiMaxTargets;

    void Reset()
    {
        m_uiStone_Grip_Timer    = 20000;
        m_uiMaxTargets          = m_bIsRegularMode ? 1 : 3;
        m_uiFreeDamage          = 0;
        m_uiMaxDamage           = m_bIsRegularMode ? 100000 : 480000;

        for(int i = 0; i < m_uiMaxTargets; i++)
            m_uiGripTargetGUID[i].Clear();

        DoCast(m_creature, SPELL_ARM_VISUAL);
    }

    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        m_uiFreeDamage += uiDamage;
    }

    void JustDied(Unit* pKiller)
    {
        if (!m_pInstance || pKiller == m_creature)
            return;

        if (Creature* pTemp = m_pInstance->GetSingleCreatureFromStorage(NPC_KOLOGARN))
        {
            DoScriptText(SAY_ARM_LOST_RIGHT, pTemp);
            if (pTemp->isAlive())
                pTemp->DealDamage(pTemp, m_creature->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        }

        for(int i = 0; i < m_uiMaxTargets; i++)
        {
            if (Unit* pVictim = m_pInstance->instance->GetUnit(m_uiGripTargetGUID[i]))
            {
                pVictim->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_STONE_GRIP : SPELL_STONE_GRIP_H);
                pVictim->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_STONE_GRIP_VEH : SPELL_STONE_GRIP_VEH_H);
                pVictim->ExitVehicle();
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_pInstance)
            return;

        if (m_uiFreeDamage > m_uiMaxDamage)
        {
            m_uiFreeDamage = 0;
            for(int i = 0; i < m_uiMaxTargets; i++)
            {
                if (Unit* pVictim = m_pInstance->instance->GetUnit(m_uiGripTargetGUID[i]))
                {
                    pVictim->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_STONE_GRIP : SPELL_STONE_GRIP_H);
                    pVictim->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_STONE_GRIP_VEH : SPELL_STONE_GRIP_VEH_H);
                    pVictim->ExitVehicle();
                }
            }
        }

        if (m_uiStone_Grip_Timer < diff)
        {
            // Need to test!
            //if (!m_creature->SetVehicleId(380))
              if (!m_creature->IsVehicle())
                return;

            if (Creature* pTemp = m_pInstance->GetSingleCreatureFromStorage(NPC_KOLOGARN))
                DoScriptText(SAY_GRAB, pTemp);

            DoScriptText(EMOTE_STONE_GRIP, m_creature);

			// this needs vehicles!
            for(int i = 0; i < m_uiMaxTargets; i++)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, m_bIsRegularMode ? 2 : 4))
                {
                    DoCast(pTarget, m_bIsRegularMode ? SPELL_STONE_GRIP_GRAB : SPELL_STONE_GRIP_GRAB_H, true);
                    m_uiGripTargetGUID[i] = pTarget->GetObjectGuid();
                    //pTarget->EnterVehicle(m_creature->GetVehicleKit());
                }
            }
            m_uiFreeDamage = 0;
            m_uiStone_Grip_Timer = 30000;
        }else m_uiStone_Grip_Timer -= diff;
    }
};

CreatureAI* GetAI_boss_right_arm(Creature* pCreature)
{
    return new boss_right_armAI(pCreature);
}

// Kologarn
struct MANGOS_DLL_DECL boss_kologarnAI : public ScriptedAI
{
    boss_kologarnAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        SetCombatMovement(false);
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bIsEmerged;
    uint32 m_uiEmergedTimer;
    uint32 m_uiSpell_Timer;
    uint32 m_uiShockwave_Timer;
    uint32 m_uiCheck_Timer;
    uint32 m_uiEyebeam_Timer;
    uint32 m_uiRespawnRightTimer;
    uint32 m_uiRespawnLeftTimer;
    uint32 m_uiEnrageTimer;
    uint32 m_uiRubbleCounter;
    bool m_bIsRightDead;
    bool m_bIsLeftDead;

    void Reset()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);

        m_uiSpell_Timer     = 10000;
        m_uiShockwave_Timer = 30000;
        m_uiCheck_Timer     = 10000;
        m_uiEnrageTimer     = 600000;
        m_uiEyebeam_Timer   = 10000 + urand(1000, 5000);
        m_bIsRightDead      = false;
        m_bIsLeftDead       = false;
        m_bIsEmerged        = false;

        m_creature->HandleEmote(EMOTE_STATE_SUBMERGED);

        // reset arms (due to some evade problems)
        if (VehicleKit *pVehKit = m_creature->GetVehicleKit())
        {
            if (Unit *pTmp = pVehKit->GetPassenger(0))
            {
                pTmp->SetVisibility(VISIBILITY_OFF);
                pTmp->DealDamage(pTmp, pTmp->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
            }
            if (Unit *pTmp = pVehKit->GetPassenger(1))
            {
                pTmp->SetVisibility(VISIBILITY_OFF);
                pTmp->DealDamage(pTmp, pTmp->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
            }
            pVehKit->InstallAllAccessories(m_creature->GetEntry());
        }

        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_ACHI_OPEN_ARMS, DONE);
            m_pInstance->SetData(TYPE_ACHI_IF_LOOKS, DONE);
            m_pInstance->SetData(TYPE_ACHI_RUBBLE_ROLL, FAIL);
        }
        m_uiRubbleCounter = 0;
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!m_bIsEmerged)
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER && !((Player*)pWho)->isGameMaster())
            {
                if (m_creature->IsWithinDist(pWho, 20.0f, false))
                {
                    if (m_pInstance)
                    {
                        Aggro(pWho);
                        m_creature->HandleEmote(EMOTE_ONESHOT_EMERGE);

                        DoScriptText(SAY_AGGRO, m_creature);
                        m_uiEmergedTimer = 3000;
                        m_bIsEmerged = true;
                    }
                }
            }
        }
        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_KOLOGARN, DONE);
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_KOLOGARN, IN_PROGRESS);

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_SLAY_1 : SAY_SLAY_2, m_creature);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_KOLOGARN, FAIL);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (m_bIsEmerged)
            {
                if (m_uiEmergedTimer <= uiDiff)
                    m_creature->HandleEmote(EMOTE_STATE_NONE);
                else
                    m_uiEmergedTimer -= uiDiff;
            }
            return;
        }

        if (m_uiSpell_Timer < uiDiff)
        {
            if (!m_bIsRightDead && !m_bIsLeftDead)
            {
                DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_OVERHEAD_SMASH : SPELL_OVERHEAD_SMASH_H);
                m_uiSpell_Timer = 20000;
            }
            else if (m_bIsRightDead && m_bIsLeftDead)
            {
                DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_STONE_SHOUT : SPELL_STONE_SHOUT_H);
                m_uiSpell_Timer = 2000;
            }
            else
            {
                DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_ONE_ARMED_SMASH : SPELL_ONE_ARMED_SMASH_H);
                m_uiSpell_Timer = 20000;
            }
        }else m_uiSpell_Timer -= uiDiff;

        if (m_uiShockwave_Timer < uiDiff)
        {
            if (VehicleKit *pVehKit = m_creature->GetVehicleKit())
            {
                if (Unit *pLeft = pVehKit->GetPassenger(0))
                {
                    DoScriptText(SAY_SHOCKWAVE, m_creature);
                    DoCast(pLeft, m_bIsRegularMode ? SPELL_ARM_SWEEP : SPELL_ARM_SWEEP_H);
                    m_uiShockwave_Timer = 17000;
                }
            }
        }else m_uiShockwave_Timer -= uiDiff;

        if (m_uiEyebeam_Timer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, m_bIsRegularMode ? 4 : 10))
            {
                //DoCast(m_creature->getVictim(), SPELL_FOCUSED_EYEBEAM, true);
                if (Creature *pLeft = m_creature->SummonCreature(NPC_FOCUSED_EYEBEAM_LEFT, pTarget->GetPositionX(), pTarget->GetPositionY()-4.0f, pTarget->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10000))
                {
                    pLeft->SetInCombatWithZone();
                    pLeft->SetDisplayId(11686);
                    pLeft->SetSpeedRate(MOVE_RUN, 1.0);
                    pLeft->CastSpell(pLeft, m_bIsRegularMode ? SPELL_EYEBEAM_PERIODIC : SPELL_EYEBEAM_PERIODIC_H, true);
                    pLeft->CastSpell(pLeft, SPELL_EYEBEAM_VISUAL_LEFT_2, true);
                    pLeft->AI()->AttackStart(pTarget);
                }
                if (Creature *pRight = m_creature->SummonCreature(NPC_FOCUSED_EYEBEAM_RIGHT, pTarget->GetPositionX(), pTarget->GetPositionY()+4.0f, pTarget->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10000))
                {
                    pRight->SetInCombatWithZone();
                    pRight->SetDisplayId(11686);
                    pRight->SetSpeedRate(MOVE_RUN, 1.0);
                    pRight->CastSpell(pRight, SPELL_EYEBEAM_PERIODIC_VIS, true);
                    pRight->CastSpell(pRight, SPELL_EYEBEAM_VISUAL_RIGHT, true);
                    pRight->AI()->AttackStart(pTarget);
                }
                m_uiEyebeam_Timer = 10000 + urand(1000, 5000);
            }
        }else m_uiEyebeam_Timer -= uiDiff;

		// respawn arms
        // needs new implementation!
        /*if (m_uiRespawnLeftTimer < uiDiff && m_bIsLeftDead)
        {
            if (VehicleKit *pVehKit = m_creature->GetVehicleKit())
            {
                m_bIsLeftDead   = false;
                DoScriptText(EMOTE_ARM_LEFT, m_creature);
            }
        }else m_uiRespawnLeftTimer -= uiDiff;

        if (m_uiRespawnRightTimer < uiDiff && m_bIsRightDead)
        {
            if (VehicleKit *pVehKit = m_creature->GetVehicleKit())
            {
                m_bIsRightDead  = false;
                DoScriptText(EMOTE_ARM_RIGHT, m_creature);
            }
        }else m_uiRespawnRightTimer -= uiDiff;*/

		// check if arms are dead and if there is no player in melee range
        if (m_uiCheck_Timer < uiDiff)
        {
            if (VehicleKit *pVehKit = m_creature->GetVehicleKit())
            {
                Unit *pLeft = pVehKit->GetPassenger(0);
                Unit *pRight = pVehKit->GetPassenger(1);

                if (!pLeft && !m_bIsLeftDead)
                {
                    for(uint8 i = 0; i < 5; i ++)
                    {
                        if(Creature* pRubble = m_creature->SummonCreature(MOB_RUBBLE, LeftArm[0] - urand(0, 5), LeftArm[1] + urand(0, 10), LeftArm[2], 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000))
                        {
                            pRubble->GetMotionMaster()->MovePoint(0, KoloFront[0], KoloFront[1], KoloFront[2]);

                            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                            {
                                pRubble->AddThreat(pTarget,0.0f);
                                pRubble->AI()->AttackStart(pTarget);
                                pRubble->SetInCombatWithZone();
                            }
                        }
                    }

                    if (m_pInstance)
                        m_pInstance->SetData(TYPE_ACHI_OPEN_ARMS, FAIL);

                    m_bIsLeftDead = true;
                    m_uiRespawnLeftTimer = 47000;
                }

                if (!pRight && !m_bIsRightDead)
                {
                    for(uint8 i = 0; i < 5; i ++)
                    {
                        if(Creature* pRubble = m_creature->SummonCreature(MOB_RUBBLE, RightArm[0] - urand(0, 5), RightArm[1] + urand(0, 10), RightArm[2], 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000))
                        {
                            pRubble->GetMotionMaster()->MovePoint(0, KoloFront[0], KoloFront[1], KoloFront[2]);

                            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                            {
                                pRubble->AddThreat(pTarget,0.0f);
                                pRubble->AI()->AttackStart(pTarget);
                                pRubble->SetInCombatWithZone();
                            }

                            m_uiRubbleCounter++;
                            if (m_uiRubbleCounter >= 25)
                            {
                                if (m_pInstance)
                                    m_pInstance->SetData(TYPE_ACHI_RUBBLE_ROLL, DONE);
                            }
                        }
                    }

                    if (m_pInstance)
                        m_pInstance->SetData(TYPE_ACHI_OPEN_ARMS, FAIL);

                    m_bIsRightDead = true;
                    m_uiRespawnRightTimer = 47000;
                }
            }

            //Petrifying breath
            if (m_creature->GetCombatDistance(m_creature->getVictim()) >= ATTACK_DISTANCE)
                DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_PETRIFYING_BREATH : SPELL_PETRIFYING_BREATH_H);

            m_uiCheck_Timer = 500;
        }else m_uiCheck_Timer -= uiDiff;

        if (m_uiEnrageTimer < uiDiff)
        {
            DoScriptText(SAY_BERSERK, m_creature);
            DoCast(m_creature, SPELL_ENRAGE);
            m_uiEnrageTimer = 30000;
        }else m_uiEnrageTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_kologarn(Creature* pCreature)
{
    return new boss_kologarnAI(pCreature);
}

// Focused Eyebeam trigger mobs - just make them not attack in melee and handle achievement event
struct MANGOS_DLL_DECL mob_eyebeam_triggerAI : public ScriptedAI
{
    mob_eyebeam_triggerAI(Creature* pCreature) : ScriptedAI(pCreature){}
    void Reset(){}
    void UpdateAI(const uint32 uiDiff){}
    void SpellHitTarget(Unit *pVictim, SpellEntry const *spellInfo)
    {
        if (spellInfo->Id == SPELL_EYEBEAM_PERIODIC || spellInfo->Id == SPELL_EYEBEAM_PERIODIC_H)
        {
            if (InstanceData *pInstance = m_creature->GetInstanceData())
                pInstance->SetData(TYPE_ACHI_IF_LOOKS, FAIL);
        }
    }
};
CreatureAI* GetAI_mob_eyebeam_trigger(Creature* pCreature)
{
    return new mob_eyebeam_triggerAI(pCreature);
}

// kologarn kill pit bunny - kills players that fall down into the pit. also handling bridge respawn after server restarts
struct MANGOS_DLL_DECL mob_kologarn_pit_kill_bunnyAI : public ScriptedAI
{
    mob_kologarn_pit_kill_bunnyAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_fPositionZ = m_creature->GetPositionZ();
        m_bBridgeLocked = false;
    }
    ScriptedInstance *m_pInstance;
    float m_fPositionZ;
    bool m_bBridgeLocked;
    void Reset(){}
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_bBridgeLocked)
        {
            if (m_pInstance)
            {
                Creature *pKolo = m_pInstance->GetSingleCreatureFromStorage(NPC_KOLOGARN);
                if (!pKolo || pKolo && !pKolo->isAlive())
                {
                    if (GameObject *pGo = m_pInstance->GetSingleGameObjectFromStorage(GO_KOLOGARN_BRIDGE))
                    {
                        pGo->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                        pGo->SetGoState(GO_STATE_READY);
                    }
                    if (Creature *pBridge = m_pInstance->GetSingleCreatureFromStorage(NPC_KOLOGARN_BRIDGE_DUMMY))
                        pBridge->SetVisibility(VISIBILITY_ON);
                    m_bBridgeLocked = true;
                }
            }
        }
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (pWho->GetTypeId() == TYPEID_PLAYER && !pWho->GetVehicle())
            if (m_creature->IsWithinLOSInMap(pWho) && pWho->GetPositionZ() - m_fPositionZ <= 15.0f)
                pWho->DealDamage(pWho, pWho->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
    }
};
CreatureAI* GetAI_mob_kologarn_pit_kill_bunny(Creature* pCreature)
{
    return new mob_kologarn_pit_kill_bunnyAI(pCreature);
}

void AddSC_boss_kologarn()
{
    Script* NewScript;

    NewScript = new Script;
    NewScript->Name = "boss_kologarn";
    NewScript->GetAI = GetAI_boss_kologarn;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_ulduar_rubble";
    NewScript->GetAI = &GetAI_mob_ulduar_rubble;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "boss_left_arm";
    NewScript->GetAI = &GetAI_boss_left_arm;
    NewScript->RegisterSelf();
 
    NewScript = new Script;
    NewScript->Name = "boss_right_arm";
    NewScript->GetAI = &GetAI_boss_right_arm;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_eyebeam_trigger";
    NewScript->GetAI = &GetAI_mob_eyebeam_trigger;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_kologarn_pit_kill_bunny";
    NewScript->GetAI = &GetAI_mob_kologarn_pit_kill_bunny;
    NewScript->RegisterSelf();
}
