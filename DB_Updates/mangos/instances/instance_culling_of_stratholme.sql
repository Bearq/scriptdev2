UPDATE instance_template SET ScriptName='instance_culling_of_stratholme' WHERE map=595;
UPDATE creature_template SET ScriptName='npc_mike' WHERE entry=30571;
UPDATE creature_template SET ScriptName='npc_chromi_start' WHERE entry=26527;
UPDATE creature_template SET ScriptName='npc_roger' WHERE entry=27903;
UPDATE creature_template SET ScriptName='npc_morigan' WHERE entry=27877;
UPDATE creature_template SET ScriptName='npc_stratholme_crates' WHERE entry=30996;
UPDATE creature_template SET ScriptName='npc_jena' WHERE entry=27885;
UPDATE creature_template SET ScriptName='npc_malcolm' WHERE entry=27891;
UPDATE creature_template SET ScriptName='npc_bartleby_cs' WHERE entry=27907;
UPDATE creature_template SET ScriptName='npc_chromi_middle' WHERE entry=27915;
UPDATE creature_template SET ScriptName='npc_uther' WHERE entry=26528;
UPDATE creature_template SET ScriptName='npc_arthas' WHERE entry=26499;
UPDATE creature_template SET ScriptName='npc_arthas_priest' WHERE entry=27747;
UPDATE creature_template SET ScriptName='npc_arthas_marine' WHERE entry=27745;
UPDATE creature_template SET ScriptName='npc_dark_conversion' WHERE entry IN (31127, 31126, 28167, 28169);
UPDATE creature_template SET ScriptName='npc_cs_gnoul' WHERE entry=28249;
UPDATE creature_template SET ScriptName='npc_cs_necromancer' WHERE entry=28200;
UPDATE creature_template SET ScriptName='npc_cs_field' WHERE entry=27734;
UPDATE creature_template SET ScriptName='npc_cs_acolyte' WHERE entry=27731;
UPDATE creature_template SET ScriptName='npc_cs_butcher' WHERE entry=27736;
UPDATE creature_template SET ScriptName='boss_meathook' WHERE entry=26529;
UPDATE creature_template SET ScriptName='boss_salramm' WHERE entry=26530;
UPDATE creature_template SET ScriptName='npc_salramm_gnoul' WHERE entry=27733;
UPDATE creature_template SET ScriptName='boss_lord_epoch' WHERE entry=26532;
UPDATE creature_template SET ScriptName='boss_malganis' WHERE entry=26533;
UPDATE creature_template SET ScriptName='npc_time_riftCS' WHERE entry=28409;
UPDATE creature_template SET ScriptName='boss_infinite_corruptor' WHERE entry=32273;

DELETE FROM creature WHERE id in (27915, 26499, 26497, 26528, 27891, 27892, 32273, 28439);
INSERT INTO creature (id, map, spawnMask, phaseMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, DeathState, MovementType) VALUES
(27915, 595, 3, 1, 0, 0, 1812.49, 1284.81, 142.248, 4.03364, 300, 0, 0, 17010, 0, 0, 0),
(26499, 595, 3, 1, 0, 1613, 1920.87, 1287.12, 142.935, 6.25562, 43200, 0, 0, 44100, 7988, 0, 0),
(26497, 595, 3, 1, 0, 1221, 1896.39, 1292.91, 143.711, 0.016332, 25, 5, 0, 100800, 88140, 0, 0),
(26528, 595, 3, 1, 0, 1819, 1761.42, 1285.75, 139.945, 4.93874, 25, 5, 0, 126000, 59910, 0, 0),
(27891, 595, 3, 1, 0, 0, 1603.38, 805.988, 123.272, 1.90688, 25, 5, 0, 8982, 0, 0, 0),
(27892, 595, 3, 1, 0, 0, 1602.3, 809.385, 123.454, 5.02884, 25, 5, 0, 8982, 0, 0, 0),
(32273, 595, 2, 1, 0, 1839, 2330.93, 1275.59, 132.848, 3.60489, 86400, 5, 0, 417911, 0, 0, 0),
(28439, 595, 2, 1, 0, 0, 2336.56, 1277.9, 132.885, 3.47923, 25, 5, 0, 1, 0, 0, 0);

--  Dark Runed Chest (190663/193597)
UPDATE gameobject_template SET flags=0 WHERE entry IN (190663,193597);

DELETE FROM gameobject WHERE id IN (190663,193597);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(67603, 190663, 595, 1, 1, 2288.35, 1498.73, 128.414, -0.994837, 0, 0, 0, 1, -604800, 255, 1),
(82708, 193597, 595, 2, 1, 2288.35, 1498.73, 128.414, -0.994837, 0, 0, 0, 1, -86400, 255, 1);
