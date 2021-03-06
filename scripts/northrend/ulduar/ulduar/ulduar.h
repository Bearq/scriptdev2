/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software licensed under GPL version 2
* Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_ULDUAR_H
#define DEF_ULDUAR_H

enum
{
    MAX_ENCOUNTER               = 14,
    HARD_MODE_ENCOUNTER         = 9,
    KEEPER_ENCOUNTER            = 4,
    FREYA_ELDERS_ENCOUNTER      = 3,
    TELEPORTER_ENCOUNTER        = 3,

    // boss types
    TYPE_LEVIATHAN              = 0,
    TYPE_IGNIS                  = 1,
    TYPE_RAZORSCALE             = 2,
    TYPE_XT002                  = 3,
    TYPE_ASSEMBLY               = 4,
    TYPE_KOLOGARN               = 5,
    TYPE_AURIAYA                = 6,
    TYPE_MIMIRON                = 7,
    TYPE_HODIR                  = 8,
    TYPE_THORIM                 = 9,
    TYPE_FREYA                  = 10,
    TYPE_VEZAX                  = 11,
    TYPE_YOGGSARON              = 12,
    TYPE_ALGALON                = 13,

    // Freya 1, 2 elders
    TYPE_FREYA_1                = 35,
    TYPE_FREYA_2                = 36,

    // hard mode bosses
    TYPE_LEVIATHAN_HARD         = 37,
    TYPE_XT002_HARD             = 38,
    TYPE_ASSEMBLY_HARD          = 39,
    TYPE_MIMIRON_HARD           = 40,
    TYPE_HODIR_HARD             = 41,
    TYPE_THORIM_HARD            = 42,
    TYPE_FREYA_HARD             = 43, // this means 3 elders up
    TYPE_VEZAX_HARD             = 44,
    TYPE_YOGGSARON_HARD         = 45,

    // keepers help at Yogg
    TYPE_KEEPER_HODIR           = 46,
    TYPE_KEEPER_FREYA           = 47,
    TYPE_KEEPER_THORIM          = 48,
    TYPE_KEEPER_MIMIRON         = 49,

    // teleporters
    TYPE_LEVIATHAN_TP           = 50,
    TYPE_XT002_TP               = 51,
    TYPE_MIMIRON_TP             = 52,

    //other-> these won't be saved to db
    TYPE_RUNE_GIANT             = 14,
    TYPE_RUNIC_COLOSSUS         = 15,
    TYPE_LEVIATHAN_MK           = 16,
    TYPE_VX001                  = 17,
    TYPE_AERIAL_UNIT            = 18,
    TYPE_YOGG_BRAIN             = 22,
    TYPE_MIMIRON_PHASE          = 23,
    TYPE_YOGG_PHASE             = 24,
    TYPE_VISION_PHASE           = 25,

    // achievement types
    TYPE_ACHI_QUICK_SHAVE       = 53,
    TYPE_ACHI_SHATTERED         = 54,
    TYPE_ACHI_NERF_ENGI         = 55,
    TYPE_ACHI_NERF_GRAVITY      = 56,
    TYPE_ACHI_CHOOSE_MOLG       = 57,
    TYPE_ACHI_CHOOSE_BRUN       = 58,
    TYPE_ACHI_CHOOSE_STEEL      = 59,
    TYPE_ACHI_CANT_DO_THAT      = 60,
    TYPE_ACHI_OPEN_ARMS         = 61,
    TYPE_ACHI_IF_LOOKS          = 62,
    TYPE_ACHI_RUBBLE_ROLL       = 63,
    TYPE_ACHI_CAT_LADY          = 64,
    TYPE_ACHI_NINE_LIVES        = 65,

    // achievement criterias
    ACHIEV_CRIT_QUICK_SHAVE_10  = 10062,
    ACHIEV_CRIT_QUICK_SHAVE_25  = 10063,
    ACHIEV_CRIT_IRON_DWARF_10   = 10066,
    ACHIEV_CRIT_IRON_DWARF_25   = 10067,
    ACHIEV_CRIT_SHATTERED_10    = 10068,
    ACHIEV_CRIT_SHATTERED_25    = 10069,
    ACHIEV_CRIT_NERF_ENGI_10    = 10074,
    ACHIEV_CRIT_NERF_ENGI_25    = 10075,
    ACHIEV_CRIT_NERF_GRAVITY_10 = 10077,
    ACHIEV_CRIT_NERF_GRAVITY_25 = 10079,
    ACHIEV_CRIT_HEARTBREAKER_10 = 10221,
    ACHIEV_CRIT_HEARTBREAKER_25 = 10220,
    ACHIEV_CRIT_CHOOSE_MOLG_10  = 10082,
    ACHIEV_CRIT_CHOOSE_MOLG_25  = 10085,
    ACHIEV_CRIT_CHOOSE_BRUN_10  = 10083,
    ACHIEV_CRIT_CHOOSE_BRUN_25  = 10086,
    ACHIEV_CRIT_CHOOSE_STEEL_10 = 10084,
    ACHIEV_CRIT_CHOOSE_STEEL_25 = 10087,
    ACHIEV_CRIT_UR_SIDE_MOLG_10 = 10088,
    ACHIEV_CRIT_UR_SIDE_MOLG_25 = 10089,
    ACHIEV_CRIT_UR_SIDE_BRUN_10 = 10418,
    ACHIEV_CRIT_UR_SIDE_BRUN_25 = 10420,
    ACHIEV_CRIT_UR_SIDE_STEEL_10= 10419,
    ACHIEV_CRIT_UR_SIDE_STEEL_25= 10421,
    ACHIEV_CRIT_CANTDOTHAT_M_10 = 10090,
    ACHIEV_CRIT_CANTDOTHAT_M_25 = 10091,
    ACHIEV_CRIT_CANTDOTHAT_B_10 = 10422,
    ACHIEV_CRIT_CANTDOTHAT_B_25 = 10424,
    ACHIEV_CRIT_CANTDOTHAT_S_10 = 10423,
    ACHIEV_CRIT_CANTDOTHAT_S_25 = 10425,
    ACHIEV_CRIT_OPEN_ARMS_10    = 10285,
    ACHIEV_CRIT_OPEN_ARMS_25    = 10095,
    ACHIEV_CRIT_IF_LOOKS_10     = 10286,
    ACHIEV_CRIT_IF_LOOKS_25     = 10099,
    ACHIEV_CRIT_RUBBLE_ROLL_10  = 10290,
    ACHIEV_CRIT_RUBBLE_ROLL_25  = 10133,
    ACHIEV_CRIT_CAT_LADY_10     = 10400,
    ACHIEV_CRIT_CAT_LADY_25     = 10184,
    ACHIEV_CRIT_NINE_LIVES_10   = 10399,
    ACHIEV_CRIT_NINE_LIVES_25   = 10243,

    // siege
    NPC_LEVIATHAN               = 33113,
    NPC_IGNIS                   = 33118,
    NPC_IRON_CONSTRUCT          = 33121,
    NPC_RAZORSCALE              = 33186,
    NPC_COMMANDER               = 33210,
    NPC_XT002                   = 33293,
    // antechamber
    NPC_STEELBREAKER            = 32867,
    NPC_MOLGEIM                 = 32927,
    NPC_BRUNDIR                 = 32857,
    NPC_KOLOGARN                = 32930,
    NPC_RIGHT_ARM               = 32934,
    NPC_LEFT_ARM                = 32933,
    NPC_KOLOGARN_BRIDGE_DUMMY   = 34297,
    NPC_AURIAYA                 = 33515,
    NPC_SANCTUM_SENTRY          = 34014,
    NPC_FERAL_DEFENDER          = 34035,
    // keepers
    NPC_MIMIRON                 = 33350,
    NPC_LEVIATHAN_MK            = 33432,
    NPC_VX001                   = 33651,
    NPC_AERIAL_UNIT             = 33670,
    NPC_HODIR                   = 32845,
    NPC_THORIM                  = 32865,
    NPC_RUNIC_COLOSSUS          = 32872,
    NPC_RUNE_GIANT              = 32873,
    NPC_JORMUNGAR_BEHEMOTH      = 32882,
    NPC_FREYA                   = 32906,
    NPC_BRIGHTLEAF              = 32915,
    NPC_IRONBRACH               = 32913,
    NPC_STONEBARK               = 32914,
    // madness
    NPC_VEZAX                   = 33271,
    NPC_ANIMUS                  = 33524,
    NPC_YOGGSARON               = 33288,
    NPC_ALGALON                 = 32871,
    NPC_SARA                    = 33134,
    NPC_YOGG_BRAIN              = 33890, 
    // keepers images used to start the encounter
    THORIM_IMAGE                = 33413,
    MIMIRON_IMAGE               = 33412,
    HODIR_IMAGE                 = 33411,
    FREYA_IMAGE                 = 33410,
    // Keepers used at yogg saron encounter
    KEEPER_FREYA                = 33241,
    KEEPER_HODIR                = 33213,
    KEEPER_MIMIRON              = 33244,
    KEEPER_THORIM               = 33242, 

    // loot chests
    // Kologarn
    GO_CACHE_OF_LIVING_STONE_N  = 195046,
    GO_CACHE_OF_LIVING_STONE_H	= 195047,
    // Hodir
    GO_CACHE_OF_WINTER_N        = 194307,
    GO_CACHE_OF_WINTER_H        = 194308,
    GO_CACHE_OF_RARE_WINTER_N   = 194200,
    GO_CACHE_OF_RARE_WINTER_H   = 194201,
    // Thorim
    GO_CACHE_OF_STORMS_N        = 194312,
    GO_CACHE_OF_RARE_STORMS_N   = 194313,
    GO_CACHE_OF_STORMS_H        = 194314,
    GO_CACHE_OF_RARE_STORMS_H   = 194315,
    // Alagon
    GO_GIFT_OF_OBSERVER_H       = 194821,
    GO_GIFT_OF_OBSERVER_N       = 194822,
    GO_GIFT_OF_OBSERVER_HH      = 194823,   // unk
    // Freya -> each chest is for a mode
    // 10 man
    GO_FREYA_GIFT_N             = 194324,//10 normal
    GO_FREYA_GIFT_HARD_N        = 194327,//10 3 elders
    // 25 man
    GO_FREYA_GIFT_H             = 194328,//25 normal
    GO_FREYA_GIFT_HARD_H        = 194331,//25 3 elders
    // Mimiron
    GO_CACHE_OF_INOV_N          = 194789,
    GO_CACHE_OF_INOV_H          = 194956,
    GO_CACHE_OF_INOV_HARD_N     = 194957,
    GO_CACHE_OF_INOV_HARD_H     = 194958,

    // doors
    // the siege
    GO_SHIELD_WALL              = 194416,
    GO_LEVIATHAN_GATE           = 194630,
    GO_XT002_GATE               = 194631,
    GO_BROKEN_HARPOON           = 194565,
    // archivum
    GO_KOLOGARN_BRIDGE          = 194232,
    GO_SHATTERED_DOOR           = 194553,
    GO_IRON_ENTRANCE_DOOR       = 194554,
    GO_ARCHIVUM_DOOR            = 194556,
    GO_ARCHIVUM_CONSOLE         = 194555,
    // planetarium: algalon
    GO_CELESTIAL_ACCES          = 194628,
    GO_CELESTIAL_ACCES_H        = 194752,
    GO_CELESTIAL_DOOR           = 194767,
    GO_UNIVERSE_FLOOR_ARCHIVUM  = 194715,
    GO_UNIVERSE_FLOOR_CELESTIAL = 194716,
    GO_AZEROTH_GLOBE            = 194148,
    // the keepers
    // hodir
    GO_HODIR_EXIT               = 194634,
    GO_HODIR_ICE_WALL           = 194441,
    GO_HODIR_ENTER              = 194442,
    // mimiron
    GO_MIMIRON_TRAM             = 194675,
    GO_MIMIRON_BUTTON           = 194739,
    GO_MIMIRON_DOOR_1           = 194774,
    GO_MIMIRON_DOOR_2           = 194775,
    GO_MIMIRON_DOOR_3           = 194776,
    GO_MIMIRON_TEL1             = 194741,
    GO_MIMIRON_TEL2             = 194742,
    GO_MIMIRON_TEL3             = 194743,
    GO_MIMIRON_TEL4             = 194744,
    GO_MIMIRON_TEL5             = 194740,
    GO_MIMIRON_TEL6             = 194746,
    GO_MIMIRON_TEL7             = 194747,
    GO_MIMIRON_TEL8             = 194748,
    GO_MIMIRON_TEL9             = 194745,
    GO_MIMIRON_ELEVATOR         = 194749,
    // Thorim
    GO_DARK_IRON_PORTCULIS      = 194560,
    GO_RUNED_STONE_DOOR         = 194557,
    GO_THORIM_STONE_DOOR        = 194558,
    GO_LIGHTNING_DOOR           = 194905,
    GO_LIGHTNING_FIELD          = 194559,
    GO_DOOR_LEVER               = 194264,
    //Yogg
    GO_ANCIENT_GATE             = 194255,
    GO_VEZAX_GATE               = 194750,
    GO_YOGG_GATE                = 194773,
    GO_BRAIN_DOOR1              = 194635,
    GO_BRAIN_DOOR2              = 194636,
    GO_BRAIN_DOOR3              = 194637,

    ACHIEV_IRON_COUNCIL         = 2888,
    ACHIEV_IRON_COUNCIL_H       = 2889,

    ACHIEV_KEEPERS              = 2890,
    ACHIEV_KEEPERS_H            = 2891,

    ACHIEV_CELESTIAL_DEFENDER   = 3259,     // realm first algalon
    SPELL_ALGALON_ACHIEV_TRIGG  = 65184,
    ACHIEV_DEATHS_DEMISE        = 3117,     // realm first yogg

    // World state used for algalon timer
    WORLD_STATE_TIMER           = 4132,
    WORLD_STATE_TIMER_COUNT     = 4131,
};

class MANGOS_DLL_DECL instance_ulduar : public ScriptedInstance
{
    public:
        instance_ulduar(Map* pMap);
        ~instance_ulduar() {}

        void Initialize();
        bool IsEncounterInProgress() const;

        void OnCreatureCreate(Creature* pCreature);
        void OnObjectCreate(GameObject* pGo);

        void SetData(uint32 uiType, uint32 uiData);
        uint32 GetData(uint32 uiType);

        const char* Save();
        void Load(const char* chrIn);

        // Dummy, leave till correct solution for hardmode found
        bool CheckConditionCriteriaMeet(Player const* pSource, uint32 uiMapId, uint32 uiInstanceConditionId);
        bool CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 = 0);

        void OpenDoor(uint32 m_uiDoorEntry);
        void CloseDoor(uint32 m_uiDoorEntry);
        void DoOpenMadnessDoorIfCan();
        void OpenXtDoor();
        void CheckIronCouncil();
        void CheckKeepers();
        Player* GetPlayerInMap();
        void SpawnFriendlyKeeper(uint32 uiWho);

        GUIDList m_lIronConstructsGUIDs;

        // achievements
        void IronDwarfPushBack(uint64 uiGuid);

    protected:
        
	// initialize the encouter variables
    std::string m_strInstData;
    uint32 m_auiEncounter[MAX_ENCOUNTER];
    uint32 m_auiHardBoss[HARD_MODE_ENCOUNTER];
    uint32 m_auiUlduarKeepers[KEEPER_ENCOUNTER];
    uint32 m_auiFreyaElders[FREYA_ELDERS_ENCOUNTER];
    uint32 m_auiUlduarTeleporters[3];
    uint32 m_auiMiniBoss[6];

    // achievements
    bool m_bQuickShave;
    bool m_bShattered;
    bool m_bNerfEngi;
    bool m_bNerfGravity;
    bool m_bChooseMolg;
    bool m_bChooseBrun;
    bool m_bChooseSteel;
    bool m_bCantDoThat;
    bool m_bOpenArms;
    bool m_bIfLooks;
    bool m_bRubbleRoll;
    bool m_bCatLady;
    bool m_bNineLives;

    uint32 m_uiMimironPhase;
    uint32 m_uiYoggPhase;
    uint32 m_uiVisionPhase;

    GUIDList m_lIronDwarvesAchievList;
};

#endif
