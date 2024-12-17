#include <cstdlib>
#include <ctime>

void Game::ObjectsParameters()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Houses
	float baseRotation = 90.0f; // Rotazione costante per tutte le case
	float spacing = 4.5f; // Spaziatura tra le case
	float rowSpacing = 10.0f; // Distanza tra le file

	int housesPerRow = numOfHouses / 5; // numOfHouse > 5
	for (int row = 0; row < 5; row++) // Tre file
	{
		for (int i = 0; i < housesPerRow; i++) // Case per fila
		{
			HouseVisible[row * housesPerRow + i] = 1;
			X = i * spacing - 14;             
			Y = row * rowSpacing - 2 * rowSpacing;         
			if (i == housesPerRow - 1 and row > 0 and row < 4) {
				HouseVisible[row * housesPerRow + i] = 0;
			}

			HousePositions[row * housesPerRow + i] = { X, Y }; 
			HouseRotations[row * housesPerRow + i] = baseRotation; 
		}
	}

	// Angle Houses
	for (int i = 0; i < numOfAngleHouses; i++)
	{
		switch (i)
		{
		case 0: 
			AngleHousePositions[i] = { 22.0f, 20.0f }; 
			AngleHouseRotationsX[i] = 90.0f; 
			AngleHouseRotationsZ[i] = 180.0f;
			break;
		case 1:
			AngleHousePositions[i] = { 24.0f, -19.0f }; 
			AngleHouseRotationsX[i] = 90.0f; 
			AngleHouseRotationsZ[i] = 90.0f;
			break;
		case 2: 
			AngleHousePositions[i] = { -21.0f, 19.0f }; 
			AngleHouseRotationsX[i] = 90.0f;
			AngleHouseRotationsZ[i] = -90.0f;
			break;
		case 3: 
			AngleHousePositions[i] = { -21.0f, -20.0f }; 
			AngleHouseRotationsX[i] = 90.0f; 
			AngleHouseRotationsZ[i] = 0.0f;
			break;
		}
	}

	//STONES
	for (int i = 0; i < numOfStones; i++) {
		StonePositions[i].x = -21.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (22.0f - (-21.0f))));
		StonePositions[i].y = -19.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (20.0f - (-19.0f))));
	}

	//BUSHES
	for (int i = 0; i < numOfBushes; i++) {
		BushPositions[i].x = -21.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (22.0f - (-21.0f))));
		BushPositions[i].y = -19.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (20.0f - (-19.0f))));
		BushRotationsX[i] = 90.0f;
	}
}

//void Game::CalculateItemsPosition()
//{
//	// check item position not to go under another object
//	bool overlap = false;
//	while (true)
//	{
//		/*overlap = false;
//		CalculateRandomPositionsRotations(-mapSize / 2 + mountainThreshold + 1, mapSize / 2 - mountainThreshold - 1);
//		CheckItemPositionOverlap(numOfStumps, stumpThreshold, stumpThresholdCoefficient, stumpPositions, stumpScales, overlap);
//		CheckItemPositionOverlap(numOfRocks, rockThreshold, rockThresholdCoefficient, rockPositions, rockScales, overlap);
//		CheckItemPositionOverlap(numOfTrees, treeThreshold, treeThresholdCoefficient, treePositions, treeScales, overlap);
//		CheckItemPositionOverlap(numOfTrees1, treeThreshold, treeThresholdCoefficient, tree1Positions, tree1Scales, overlap);
//		CheckItemPositionOverlap(numOfTrees2, treeThreshold, treeThresholdCoefficient, tree2Positions, tree2Scales, overlap);
//		CheckItemPositionOverlap(numOfTrees3, treeThreshold, treeThresholdCoefficient, tree3Positions, tree3Scales, overlap);
//		CheckItemPositionOverlap(numOfTrees4, treeThreshold, treeThresholdCoefficient, tree4Positions, tree4Scales, overlap);
//		CheckItemPositionOverlap(numOfSpikes, spikeThreshold, 0, spikePositions, spikeScales, overlap);
//		if (!overlap)
//			break;*/
//	}
//}

//void JungleExploration::CheckItemPositionOverlap(int numOfObjects, float objectThreshold, float objectThresholdCoefficient, glm::vec2 objectPositions[], float objectScales[], bool& overlap)
//{
//	float threshold = 0;
//	for (int i = 0; i < numOfObjects; i++)
//	{
//		threshold = objectThreshold + (objectScales[i] - 0.2f) * objectThresholdCoefficient;
//		if (overlap || ((X < objectPositions[i].x + threshold && X > objectPositions[i].x - threshold) &&
//			(Y < objectPositions[i].y + threshold && Y > objectPositions[i].y - threshold)))
//		{
//			overlap = true;
//			break;
//		}
//	}
//}

//void JungleExploration::CalculateRandomPositionsRotations(int start, int end, bool checkCenter)
//{
//	X = rand() % (end - start + 1) + start;
//	Y = rand() % (end - start + 1) + start;
//	if (checkCenter)
//	{
//		while (true)
//		{
//			if (X < 2 && X > -2 && Y < 2 && Y > -2)
//			{
//				X = rand() % (end - start + 1) + start;
//				Y = rand() % (end - start + 1) + start;
//			}
//			else
//			{
//				break;
//			}
//		}
//	}
//	Rot = rand() % (360 + 1);
//}