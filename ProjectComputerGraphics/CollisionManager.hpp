void Game::CollisionCheck(glm::vec3 &pos, glm::vec3 &nextPos) {
	if (nextPos.x > WallPositions[0].x - 1.5f) {
		nextPos.x = WallPositions[0].x - 1.6f;
	}
	if (nextPos.x < WallPositions[1].x + 1.5f) {
		nextPos.x = WallPositions[1].x + 1.6f;
	}
	if (nextPos.z > WallPositions[2].y - 1.5f) {
		nextPos.z = WallPositions[2].y - 1.6f;
	}
	if (nextPos.z < WallPositions[3].y + 1.5f) {
		nextPos.z = WallPositions[3].y + 1.6f;
	}

	//HOUSES
	for (int i = 0; i < numOfHouses; i++) {
		if (nextPos.x > HousePositions[i].x - 2.6f && nextPos.x < HousePositions[i].x + 2.6f &&
			nextPos.z > HousePositions[i].y - 1.9f && nextPos.z < HousePositions[i].y + 1.9f) {
			collision = true;
			break;
		}
	}

	//ANGLE_HOUSES
	for (int i = 0; i < numOfAngleHouses; i++) {
		if (i == 0) {//vicino sx castello
			if ((nextPos.x > AngleHousePositions[i].x - 2.7f && nextPos.x < AngleHousePositions[i].x + 2.7f &&
				nextPos.z > AngleHousePositions[i].y - 2.0f && nextPos.z < AngleHousePositions[i].y + 2.0f) ||
				(nextPos.x > AngleHousePositions[i].x - 0.5 && nextPos.x < AngleHousePositions[i].x + 2.7 &&
				nextPos.z > AngleHousePositions[i].y - 2 * 2.0f && nextPos.z < AngleHousePositions[i].y + 2.0f)) {
				collision = true;
				break;
			}
		}
		if (i == 1) {//vicino dx castello
			if ((nextPos.x > AngleHousePositions[i].x - 2.0f && nextPos.x < AngleHousePositions[i].x + 2.0f &&
				nextPos.z > AngleHousePositions[i].y - 2.7f && nextPos.z < AngleHousePositions[i].y + 2.7f)||
				(nextPos.x > AngleHousePositions[i].x - 2 * 2.0f && nextPos.x < AngleHousePositions[i].x + 2.0f &&
					nextPos.z > AngleHousePositions[i].y - 2.7f && nextPos.z < AngleHousePositions[i].y + 0.5f)) {
				collision = true;
				break;
			}
		}
		if (i == 2) {//lontano sx castello
			if ((nextPos.x > AngleHousePositions[i].x - 2.0f && nextPos.x < AngleHousePositions[i].x + 2.0f &&
				nextPos.z > AngleHousePositions[i].y - 2.7f && nextPos.z < AngleHousePositions[i].y + 2.7f) ||
				(nextPos.x > AngleHousePositions[i].x - 2.0f && nextPos.x < AngleHousePositions[i].x + 2 * 2.0f &&
					nextPos.z > AngleHousePositions[i].y - 0.5f && nextPos.z < AngleHousePositions[i].y + 2.7f)) {
				collision = true;
				break;
			}
		}
		if (i == 3) {//lontano dx castello
			if ((nextPos.x > AngleHousePositions[i].x - 2.7f && nextPos.x < AngleHousePositions[i].x + 2.7f &&
				nextPos.z > AngleHousePositions[i].y - 2.0f && nextPos.z < AngleHousePositions[i].y + 2.0f) ||
				(nextPos.x > AngleHousePositions[i].x - 2.7f && nextPos.x < AngleHousePositions[i].x + 0.5f &&
					nextPos.z > AngleHousePositions[i].y - 2.0f && nextPos.z < AngleHousePositions[i].y + 2 * 2.0f)) {
				collision = true;
				break;
			}
		}
	}

	//CASTLE
	for (int i = 0; i < numOfCastle; i++) {
		
		if (nextPos.x > CastlePositions[i].x - 4.5f && nextPos.x < CastlePositions[i].x + 4.0f &&
			nextPos.z > CastlePositions[i].y - 6.0f && nextPos.z < CastlePositions[i].y + 6.0f) {

			collision = true;
			break;
		}
	}

	//DOUBLE_HOUSES
	for (int i = 0; i < numOfDoubleHouses; i++) {
		if (nextPos.x > DoubleHousePositions[i].x + 1.0f && nextPos.x < DoubleHousePositions[i].x + 5.0f &&
			nextPos.z > DoubleHousePositions[i].y - 2.2f && nextPos.z < DoubleHousePositions[i].y + 2.2f) {
			collision = true;
			break;
		}
		if (nextPos.x > DoubleHousePositions[i].x - 5.0f && nextPos.x < DoubleHousePositions[i].x - 1.0f &&
			nextPos.z > DoubleHousePositions[i].y - 2.2f && nextPos.z < DoubleHousePositions[i].y + 2.2f) {
			collision = true;
			break;
		}
	}


	//TOWERS
	for (int i = 0; i < numOfTowers; i++) {
		if (nextPos.x > TowerPositions[i].x - 3.0f && nextPos.x < TowerPositions[i].x + 3.0f &&
			nextPos.z > TowerPositions[i].y - 3.0f && nextPos.z < TowerPositions[i].y + 3.0f) {
			collision = true;
			break;
		}
	}

	//WELL
	for (int i = 0; i < numOfWell; i++) {
		float dx = nextPos.x - WellPosition[i].x; // Distanza lungo l'asse X
		float dz = nextPos.z - WellPosition[i].y; // Distanza lungo l'asse Z
		float distanceSquared = dx * dx + dz * dz; // Distanza al quadrato

		if (distanceSquared < 1 * 1) { // Confronta con il raggio al quadrato
			collision = true;
			break;
		}
	}

	//BIGGER HOUSES

	for(int i = 0; i < numOfBiggerHouses; i++){
	
		if (nextPos.x > BiggerHousePositions[i].x - 2.0f && nextPos.x < BiggerHousePositions[i].x + 2.0f &&
			nextPos.z > BiggerHousePositions[i].y - 2.5f && nextPos.z < BiggerHousePositions[i].y + 2.65f) {

			collision = true;
			break;
		}
	}

	//STATUE

	for (int i = 0; i < numOfStatue1; i++) {

		if (nextPos.x > Statue1Positions[i].x - 1.10f && nextPos.x < Statue1Positions[i].x + 1.10f &&
			nextPos.z > Statue1Positions[i].y - 1.10f && nextPos.z < Statue1Positions[i].y + 1.10f) {

			collision = true;
			break;
		}
	}

	for (int i = 0; i < numOfStatue2; i++) {

		if (nextPos.x > Statue2Positions[i].x - 1.10f && nextPos.x < Statue2Positions[i].x + 1.10f &&
			nextPos.z > Statue2Positions[i].y - 1.10f && nextPos.z < Statue2Positions[i].y + 1.10f) {

			collision = true;
			break;
		}
	}
}