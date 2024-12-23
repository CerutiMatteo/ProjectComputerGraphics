void Game::BorderHandler(glm::vec3 &pos, glm::vec3 &nextPos) {
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
		if (HouseVisible[i] == 0.0f) {
			continue;
		}
		if (nextPos.x > HousePositions[i].x - 2.1f && nextPos.x < HousePositions[i].x + 2.1f &&
			nextPos.z > HousePositions[i].y - 1.5f && nextPos.z < HousePositions[i].y + 1.5f) {
			collision = true;
			break;
		}
	}

	//...
}