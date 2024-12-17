void Game::RenderCharacter(uint32_t currentImage)
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, 0.0f, 0.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(0.4f));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	GWorld = World * translationMatrix * rotationMatrix * scaleMatrix;

	uboCharacter.visible = 1.0f;
	uboCharacter.amb = 1.0f;
	uboCharacter.gamma = 20.0f;
	uboCharacter.sColor = glm::vec3(1.0f);
	uboCharacter.mvpMat = ViewPrj * GWorld;
	uboCharacter.mMat = GWorld;
	uboCharacter.nMat = glm::inverse(glm::transpose(GWorld));
	DSCharacter.map(currentImage, &uboCharacter, sizeof(uboCharacter), 0);
}

void Game::RenderEnvironment(uint32_t currentImage)
{
	RenderGround(currentImage);
	RenderHouses(currentImage);
	RenderAngleHouses(currentImage);
	RenderStones(currentImage);
	RenderBushes(currentImage);
}

void Game::RenderGround(uint32_t currentImage)
{
	for (int i = 0; i < 4; i++)
	{
		GWorld = glm::translate(glm::scale(glm::mat4(1), glm::vec3(mapSize / 2)), glm::vec3(groundPositions[i].x, 0, groundPositions[i].y));
		SetUboDs(currentImage, uboGround, DSGround, i);
	}
}

void Game::RenderHouses(uint32_t currentImage)
{
	for (int i = 0; i < numOfHouses; i++)
	{
		if (HouseVisible[i] == 1) {
			GWorld = glm::translate(glm::mat4(1), glm::vec3(HousePositions[i].x, 0, HousePositions[i].y)) * glm::rotate(glm::mat4(1.0f), glm::radians(HouseRotations[i]), glm::vec3(1, 0, 0)) * glm::scale(glm::mat4(1), glm::vec3(0.4f));
		}
		SetUboDs(currentImage, uboHouses, DSHouses, i, 0.7f);
	}
}

void Game::RenderAngleHouses(uint32_t currentImage)
{
	for (int i = 0; i < numOfAngleHouses; i++)
	{
		GWorld = glm::translate(glm::mat4(1), glm::vec3(AngleHousePositions[i].x, 0, AngleHousePositions[i].y)) * glm::rotate(glm::mat4(1.0f), glm::radians(AngleHouseRotationsX[i]), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(AngleHouseRotationsZ[i]), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), glm::vec3(0.3f));
		SetUboDs(currentImage, uboAngleHouses, DSAngleHouses, i);
	}
}

void Game::RenderStones(uint32_t currentImage)
{
	for (int i = 0; i < numOfStones; i++)
	{
		GWorld = glm::translate(glm::mat4(1), glm::vec3(StonePositions[i].x, 0, StonePositions[i].y)) * glm::scale(glm::mat4(1), glm::vec3(0.02f));
		SetUboDs(currentImage, uboStones, DSStones, i);
	}
}

void Game::RenderBushes(uint32_t currentImage)
{
	for (int i = 0; i < numOfBushes; i++)
	{
		GWorld = glm::translate(glm::mat4(1), glm::vec3(BushPositions[i].x, 0, BushPositions[i].y)) * glm::rotate(glm::mat4(1.0f), glm::radians(BushRotationsX[i]), glm::vec3(1, 0, 0)) * glm::scale(glm::mat4(1), glm::vec3(0.3f));
		SetUboDs(currentImage, uboBushes, DSBushes, i);
	}
}


void Game::SetUboDs(uint32_t currentImage, MeshUniformBlock ubo[], DescriptorSet DS[], int index, float visible, float amb, float gamma, glm::vec3 sColor)
{
	ubo[index].visible = visible;
	ubo[index].amb = amb;
	ubo[index].gamma = gamma;
	ubo[index].sColor = sColor;
	ubo[index].mvpMat = ViewPrj * GWorld;
	ubo[index].mMat = GWorld;
	ubo[index].nMat = glm::inverse(glm::transpose(GWorld));
	DS[index].map(currentImage, &ubo[index], sizeof(ubo[index]), 0);
}
