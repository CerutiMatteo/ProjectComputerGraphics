#include <cstdlib>
#include <ctime>

void Game::ObjectsParameters()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	float rowSpacing = 10.0f; // Distanza tra le file

	// Houses
	float baseRotation = 90.0f; // Rotazione costante per tutte le case
	float spacing = 4.5f; // Spaziatura tra le case

	int housesPerRow = numOfHouses / 5; // numOfHouse > 5
	for (int row = 0; row < 5; row++) // Tre file
	{	
		if (row == 2) {//lascio libero lo spazio nel mezzo
			continue;
		}
		for (int i = 0; i < housesPerRow; i++) // Case per fila
		{
			HouseVisible[row * housesPerRow + i] = 1;
			X = i * spacing - 14;
			Y = row * rowSpacing - 2 * rowSpacing;
			if ((i == housesPerRow - 1 and row > 0 and row < 4) ||  (i == housesPerRow -2 and ( row == 1 || row == 3))) {
				HouseVisible[row * housesPerRow + i] = 0;
			}

			if((i == 0 || i == 1) and row == 1)
				HouseVisible[row * housesPerRow + i] = 0;

			if((i == housesPerRow - 3 || i == housesPerRow - 4) and row == 3)
				HouseVisible[row * housesPerRow + i] = 0;

			HouseRotationsZ[row * housesPerRow + i] = 0.0f;
			if (row == 4 || row == 1) {
				HouseRotationsZ[row * housesPerRow + i] = 180.0f;
			}
			HousePositions[row * housesPerRow + i] = { X, Y };
			HouseRotationsX[row * housesPerRow + i] = baseRotation;
		}
	}

	// ANGLE_HOUSES
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
			AngleHousePositions[i] = { -21.5f, 19.0f };
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
		StonePositions[i].x = -27 + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / 54);
		StonePositions[i].y = -27 + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / 54);
	}

	//BUSHES
	for (int i = 0; i < numOfBushes; i++) {
		BushPositions[i].x = -27 + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / 54);
		BushPositions[i].y = -27 + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / 54);
		BushRotationsX[i] = 90.0f;
	}

	//CASTLE
	for (int i = 0; i < numOfCastle; i++) {
		CastlePositions[i] = { 21.0f , 0.0f };
		CastleRotationsX[i] = 90.0f;
		CastleRotationsZ[i] = 90.0f;
	}

	//WALLS
	WallPositions[0] = { 27.0f, 0.0f }; WallRotationsX[0] = 90.0f;  WallRotationsZ[0] = -90.0f;
	WallPositions[1] = { -27.0f, 0.0f }; WallRotationsX[1] = 90.0f;  WallRotationsZ[1] = 90.0f;
	WallPositions[3] = { 0.0f, -27.0f }; WallRotationsX[3] = 90.0f;  WallRotationsZ[3] = 180.0f;
	WallPositions[2] = { 0.0f, 27.0f }; WallRotationsX[2] = 90.0f;  WallRotationsZ[2] = 0.0f;

	//TOWERS
	TowerPositions[0] = { 21.0f, 10.0f }; TowerRotationsX[0] = 90.0f; TowerRotationsZ[0] = 90.0f;
	TowerPositions[1] = { 21.0f, -10.0f }; TowerRotationsX[1] = 90.0f; TowerRotationsZ[1] = 90.0f;

	//LIGHTS
	float lightsSpacing = 10.0f; // Spaziatura tra i lampioni
	int lightsPerRow = numOfLights / 4; //lampioni per riga
	for (int row = 0; row < 4; row++) 
	{
		for (int i = 0; i < lightsPerRow; i++) 
		{
			X = i * lightsSpacing - 14;
			Y = row * rowSpacing - 1.5 * rowSpacing;
			LightPositions[row * lightsPerRow + i] = {X,Y};
			LightRotationsX[row * lightsPerRow + i] = 90.0f;
		}
	}

	//BIGGER_HOUSES
	for (int i = 0; i < numOfBiggerHouses; i++) {
		BiggerHousePositions[i].x = -21.5f;
		BiggerHousePositions[i].y = i * (spacing + 1) - 11.5f;
		BiggerHouseRotationsX[i] = 90.0f;
		BiggerHouseRotationsZ[i] = -90.0f;
	}

	//FLAGS
	FlagPositions[0] = { 21.0f, 11.0f, 10.0f }; FlagRotationsX[0] = 90.0f; FlagRotationsY[0] = 0.0f; FlagRotationsZ[0] = 90.0f; FlagScales[0] = 1.0f;//torre destra
	FlagPositions[1] = { 21.0f, 11.0f, -10.0f }; FlagRotationsX[1] = 90.0f; FlagRotationsY[1] = 0.0f; FlagRotationsZ[1] = 90.0f; FlagScales[1] = 1.0f;//torre sinistra
	FlagPositions[2] = { 20.0f, 7.0f, -4.0f }; FlagRotationsX[2] = 30.0f; FlagRotationsY[2] = 90.0f; FlagRotationsZ[2] = -90.0f; FlagScales[2] = 2.0f;//castello torre sinistra
	FlagPositions[3] = { 20.0f, 7.0f, 4.0f }; FlagRotationsX[3] = 30.0f; FlagRotationsY[3] = 90.0f; FlagRotationsZ[3] = -90.0f; FlagScales[3] = 2.0f;//castello torre destra

	//CHEST
	ChestPositions[0] = { 30.0f, 0.0f }; ChestRotationsX[0] = 90.0f;//aggiungere ceste e creare gli "spawn"

	//STATUES 1,2
	Statue1Positions[0] = { 5.0f,0.0f }; Statue1RotationsX[0] = 0.0f; Statue1RotationsY[0] = -90.0f;
	Statue2Positions[0] = { -5.0f,0.0f }; Statue2RotationsX[0] = 0.0f; Statue2RotationsY[0] = 90.0f;

	//WELL
	WellPosition[0] = { -10.0f,0.0f }; WellRotation[0] = 90.0f;

	//CLOUDS
	for (int i = 0; i < numOfClouds; i++) {

		CloudsPosition[i].x = -27 + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / 54);
		CloudsPosition[i].y = 15.0f;
		CloudsPosition[i].z = -27 + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / 54);
		CloudsSize[i] =  static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

	}

	//DOUBLE HOUSE

	DoubleHousePositions[0] = { -11.75f,-10.0f }; DoubleHousesRotationX[0] = 90.0f; DoubleHousesRotationZ[0] = 180.0f;
	DoubleHousePositions[1] = { 6.25f,10.0f }; DoubleHousesRotationX[1] = 90.0f; DoubleHousesRotationZ[1] = 0.0f;


}
