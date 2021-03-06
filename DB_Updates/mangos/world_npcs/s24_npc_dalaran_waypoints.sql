-- Add waypoints and quests for some creatures (by Bastek)
-- Temple of Telhamat
-- Scout Vanura
UPDATE creature SET position_x = 181.703, position_y = 4334.164, position_z = 116.413, orientation = 2.751, MovementType = 2 WHERE guid = 57800;
DELETE FROM creature_movement WHERE id = 57800;
INSERT INTO creature_movement VALUES
(57800, 1, 181.703, 4334.16, 116.413, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.75125, 0, 0),
(57800, 2, 178.169, 4334, 116.382, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.16907, 0, 0),
(57800, 3, 167.049, 4333.43, 111.666, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.19656, 0, 0),
(57800, 4, 164.379, 4333.39, 111.468, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.15816, 0, 0),
(57800, 5, 155.383, 4333.43, 107.649, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.15423, 0, 0),
(57800, 6, 127.366, 4333.13, 106.646, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.14245, 0, 0),
(57800, 7, 115.881, 4332.94, 102.223, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.1935, 0, 0),
(57800, 8, 76.8162, 4332.45, 101.533, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.16601, 0, 0),
(57800, 9, 115.881, 4332.94, 102.223, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.1935, 0, 0),
(57800, 10, 127.366, 4333.13, 106.646, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.14245, 0, 0),
(57800, 11, 155.383, 4333.43, 107.649, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.15423, 0, 0),
(57800, 12, 164.379, 4333.39, 111.468, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.15816, 0, 0),
(57800, 13, 167.049, 4333.43, 111.666, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.19656, 0, 0),
(57800, 14, 178.169, 4334, 116.382, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.16907, 0, 0),
(57800, 15, 181.703, 4334.16, 116.413, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.75125, 0, 0);

-- Dalaran
-- Stefen Cotter
UPDATE creature SET position_x = 5703.710, position_y = 698.479, position_z = 645.751, orientation = 4.607, MovementType = 2 WHERE guid = 110960;
DELETE FROM creature_movement WHERE id = 110960;
INSERT INTO creature_movement VALUES
(110960, 1, 5703.71, 698.479, 645.752, 120000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.60729, 0, 0),
(110960, 2, 5705.78, 700.849, 645.752, 120000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.201986, 0, 0);

-- Marcella Bloom
DELETE FROM creature_movement WHERE id = 111385;
INSERT INTO creature_movement VALUES
(111385, 1, 5705.61, 695.236, 645.751, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.56386, 0, 0),
(111385, 2, 5713.5, 694.724, 645.751, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6.13724, 0, 0),
(111385, 3, 5711.82, 691.049, 645.752, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.20124, 0, 0),
(111385, 4, 5719, 689.724, 645.752, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.018988, 0, 0),
(111385, 5, 5720.75, 678.059, 646.534, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.35263, 0, 0),
(111385, 6, 5713.96, 679.834, 645.751, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.47845, 0, 0),
(111385, 7, 5707.82, 684.572, 649.403, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.49416, 0, 0),
(111385, 8, 5700.23, 690.319, 653.72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.45882, 0, 0),
(111385, 9, 5698.87, 693.848, 653.727, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.9915, 0, 0),
(111385, 10, 5703.07, 699.339, 653.75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.785914, 0, 0),
(111385, 11, 5702.74, 701.387, 653.745, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.77552, 0, 0),
(111385, 12, 5706.06, 706.06, 653.744, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.38614, 0, 0),
(111385, 13, 5711.78, 706.006, 653.721, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6.0569, 0, 0),
(111385, 14, 5717.92, 701.136, 650.692, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.60568, 0, 0),
(111385, 15, 5725.03, 695.584, 646.455, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.62139, 0, 0),
(111385, 16, 5727.88, 692.299, 645.751, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.48002, 0, 0),
(111385, 17, 5721.56, 685.53, 645.751, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.94457, 0, 0),
(111385, 18, 5705.43, 694.882, 645.751, 20000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.46802, 0, 0);

-- Inzi Charmlight
DELETE FROM creature_movement WHERE id = 97343;
INSERT INTO creature_movement VALUES
(97343, 1, 5703.56, 701.598, 653.746, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.84378, 0, 0),
(97343, 2, 5709.91, 707.199, 653.707, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.902867, 0, 0),
(97343, 3, 5712.57, 705.145, 653.732, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.62311, 0, 0),
(97343, 4, 5718.66, 700.593, 650.264, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.63489, 0, 0),
(97343, 5, 5725.36, 695.017, 645.834, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.6074, 0, 0),
(97343, 6, 5727.79, 692.953, 645.751, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.57205, 0, 0),
(97343, 7, 5725.59, 684.619, 646.559, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.4293, 0, 0),
(97343, 8, 5723.58, 678.846, 646.539, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.36647, 0, 0),
(97343, 9, 5720.01, 688.536, 645.752, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.92781, 0, 0),
(97343, 10, 5717.55, 686.797, 645.752, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.75778, 0, 0),
(97343, 11, 5715.29, 692.476, 645.753, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.91995, 0, 0),
(97343, 12, 5708.11, 697.576, 645.752, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.54794, 0, 0),
(97343, 13, 5711.06, 691.193, 645.752, 20000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.91985, 0, 0),
(97343, 14, 5721.26, 686.035, 645.752, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.77593, 0, 0),
(97343, 15, 5715.44, 679.568, 645.752, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.98522, 0, 0),
(97343, 16, 5709.43, 683.739, 648.585, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.50474, 0, 0),
(97343, 17, 5700.9, 690.223, 653.58, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.45762, 0, 0),
(97343, 18, 5699.22, 693.46, 653.726, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.06492, 0, 0),
(97343, 19, 5703.24, 701.498, 653.746, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.14993, 0, 0);


-- Violet Hold Guard
UPDATE creature SET position_x = 5698.263, position_y = 499.277, position_z = 652.674, orientation = 2.411, MovementType = 2 WHERE guid = 114320;
UPDATE creature SET position_x = 5688.218, position_y = 506.963, position_z = 652.674, orientation = 5.643, MovementType = 2 WHERE guid = 114321;

DELETE FROM creature_movement WHERE id IN (114320, 114321);
INSERT INTO creature_movement VALUES
(114320, 1, 5698.26, 499.277, 652.674, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.40752, 0, 0),
(114320, 2, 5703.02, 490.666, 652.685, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.15327, 0, 0),
(114320, 3, 5703.18, 485.187, 652.676, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.74094, 0, 0),
(114320, 4, 5718.81, 472.231, 652.662, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.57739, 0, 0),
(114320, 5, 5703.18, 485.187, 652.676, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.74094, 0, 0),
(114320, 6, 5703.02, 490.666, 652.685, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.15327, 0, 0),
(114320, 7, 5698.26, 499.277, 652.674, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.40752, 0, 0);
INSERT INTO creature_movement VALUES
(114321, 1, 5688.22, 506.963, 652.674, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.74232, 0, 0),
(114321, 2, 5679.06, 509.641, 652.684, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.93845, 0, 0),
(114321, 3, 5673.53, 509.026, 652.678, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.25261, 0, 0),
(114321, 4, 5658.23, 521.541, 652.665, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.47507, 0, 0),
(114321, 5, 5673.53, 509.026, 652.678, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.25261, 0, 0),
(114321, 6, 5679.06, 509.641, 652.684, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.93845, 0, 0),
(114321, 7, 5688.22, 506.963, 652.674, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.74232, 0, 0);

-- Add questrelations for some NPC's (37776, 37780)
UPDATE quest_template SET RequiredRaces = 1101 WHERE entry = 24510;
UPDATE quest_template SET RequiredRaces = 690 WHERE entry = 24506;
DELETE FROM creature_questrelation WHERE id IN (37776, 37780);
INSERT INTO creature_questrelation VALUES
(37776, 24510),
(37780, 24506);

-- Apprentice Nelphi
UPDATE creature SET position_x = 5639.074, position_y = 670.100, position_z = 651.993, orientation = 1.118, MovementType = 2 WHERE guid = 88646;
DELETE FROM creature_movement WHERE id = 88646;
INSERT INTO creature_movement VALUES
(88646, 1, 5639.07, 670.1, 651.993, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.09517, 0, 0),
(88646, 2, 5647.42, 682.596, 651.993, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.92929, 0, 0),
(88646, 3, 5668.62, 680.558, 651.991, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6.23167, 0, 0),
(88646, 4, 5670, 682.693, 651.982, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.89944, 0, 0),
(88646, 5, 5670.48, 682.499, 651.99, 60000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.81351, 0, 0),
(88646, 6, 5678.35, 678.276, 649.352, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.81147, 0, 0),
(88646, 7, 5697.37, 669.769, 645.69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.86252, 0, 0),
(88646, 8, 5722.33, 659.464, 646.192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.89394, 0, 0),
(88646, 9, 5729.6, 668.114, 645.716, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.855611, 0, 0),
(88646, 10, 5729.94, 667.845, 645.709, 60000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.61512, 0, 0),
(88646, 11, 5720.63, 655.865, 646.212, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.02862, 0, 0),
(88646, 12, 5699.73, 663.318, 645.974, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.79555, 0, 0),
(88646, 13, 5683.75, 669.171, 646.961, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.8034, 0, 0),
(88646, 14, 5674.93, 672.714, 650.14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.76413, 0, 0),
(88646, 15, 5670.17, 674.843, 652.02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.74916, 0, 0),
(88646, 16, 5647.32, 682.26, 651.994, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.81125, 0, 0),
(88646, 17, 5638.86, 669.936, 651.994, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.27602, 0, 0),
(88646, 18, 5639.01, 670.208, 651.994, 60000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.14699, 0, 0);

-- Dark Ranger Vorel
UPDATE creature SET position_x = 5968.336, position_y = 631.156, position_z = 651.993, orientation = 4.271, MovementType = 2 WHERE guid = 88651;
DELETE FROM creature_movement WHERE id = 88651;
INSERT INTO creature_movement VALUES
(88651, 1, 5968.34, 631.156, 650.627, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.30328, 0, 0),
(88651, 2, 5961.6, 617.31, 650.627, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.9852, 0, 0),
(88651, 3, 5939.72, 620.169, 650.655, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.33331, 0, 0),
(88651, 4, 5937.96, 616.78, 650.614, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.16191, 0, 0),
(88651, 5, 5937.18, 617.153, 650.627, 60000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.68144, 0, 0),
(88651, 6, 5931.03, 619.303, 648.933, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.74034, 0, 0),
(88651, 7, 5909.79, 631.03, 645.962, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.64216, 0, 0),
(88651, 8, 5889.6, 641.637, 645.796, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.68143, 0, 0),
(88651, 9, 5871.44, 622.641, 648.95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.98651, 0, 0),
(88651, 10, 5863.34, 609.689, 650.973, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.28888, 0, 0),
(88651, 11, 5862.55, 610.172, 651.021, 60000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.12511, 0, 0),
(88651, 12, 5876.24, 630.934, 647.701, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.876325, 0, 0),
(88651, 13, 5892.45, 645.792, 645.516, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.67605, 0, 0),
(88651, 14, 5917.26, 634.142, 645.384, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.85182, 0, 0),
(88651, 15, 5926.42, 630.006, 646.115, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.88717, 0, 0),
(88651, 16, 5937.03, 625.84, 650.62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.91465, 0, 0),
(88651, 17, 5961.09, 617.522, 650.627, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5.93429, 0, 0),
(88651, 18, 5968.36, 631.455, 650.627, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.15907, 0, 0),
(88651, 19, 5968.03, 630.588, 650.627, 60000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.33836, 0, 0);
