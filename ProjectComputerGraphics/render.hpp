#include <cstdlib>
#include <ctime>

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

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	RenderGround(currentImage);
	RenderHouses(currentImage);
	RenderAngleHouses(currentImage);
	RenderStones(currentImage);
	RenderBushes(currentImage);
	RenderCastle(currentImage);
	RenderWalls(currentImage);
	RenderLights(currentImage);
	RenderTowers(currentImage);
	RenderDoubleHouses(currentImage);
	RenderBiggerHouses(currentImage);
	RenderFlags(currentImage);
	RenderChests(currentImage);
	RenderStatue1(currentImage);
	RenderStatue2(currentImage);
	RenderWell(currentImage);
	RenderClouds(currentImage);
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
		GWorld = glm::translate(glm::mat4(1), glm::vec3(HousePositions[i].x, 0, HousePositions[i].y)) * glm::rotate(glm::mat4(1.0f), glm::radians(HouseRotationsX[i]), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(HouseRotationsZ[i]), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), glm::vec3(0.4f));
		SetUboDs(currentImage, uboHouses, DSHouses, i);
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

void Game::RenderCastle(uint32_t currentImage)
{
	for (int i = 0; i < numOfCastle; i++)
	{
		GWorld = glm::translate(glm::mat4(1), glm::vec3(CastlePositions[i].x, 0, CastlePositions[i].y)) * glm::rotate(glm::mat4(1.0f), glm::radians(CastleRotationsX[i]), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(CastleRotationsZ[i]), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), glm::vec3(0.6f, 0.4f, 0.4f));
		SetUboDs(currentImage, uboCastle, DSCastle, i);
	}
}

void Game::RenderWalls(uint32_t currentImage)
{
	for (int i = 0; i < numOfWalls; i++)
	{
		GWorld = glm::translate(glm::mat4(1), glm::vec3(WallPositions[i].x, 0, WallPositions[i].y)) * glm::rotate(glm::mat4(1.0f), glm::radians(WallRotationsX[i]), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(WallRotationsZ[i]), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), glm::vec3(3.0f, 0.5f, 0.5f));
		SetUboDs(currentImage, uboWalls, DSWalls, i);
	}
}

void Game::RenderLights(uint32_t currentImage)
{
	for (int i = 0; i < numOfLights; i++)
	{
		GWorld = glm::translate(glm::mat4(1), glm::vec3(LightPositions[i].x, 0, LightPositions[i].y)) * glm::rotate(glm::mat4(1.0f), glm::radians(LightRotationsX[i]), glm::vec3(1, 0, 0)) * glm::scale(glm::mat4(1), glm::vec3(1.0f));
		SetUboDs(currentImage, uboLights, DSLights, i);
	}
}

void Game::RenderTowers(uint32_t currentImage)
{
	for (int i = 0; i < numOfTowers; i++)
	{
		GWorld = glm::translate(glm::mat4(1), glm::vec3(TowerPositions[i].x, 0, TowerPositions[i].y)) * glm::rotate(glm::mat4(1.0f), glm::radians(TowerRotationsX[i]), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(TowerRotationsZ[i]), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), glm::vec3(0.5f));
		SetUboDs(currentImage, uboTowers, DSTowers, i);
	}
}

void Game::RenderDoubleHouses(uint32_t currentImage)
{
	for (int i = 0; i < numOfDoubleHouses; i++)
	{
		GWorld = glm::translate(glm::mat4(1), glm::vec3(DoubleHousePositions[i].x, 0, DoubleHousePositions[i].y))* glm::rotate(glm::mat4(1.0f), glm::radians(DoubleHousesRotationX[i]), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(DoubleHousesRotationZ[i]), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), glm::vec3(0.35f, 0.3f, 0.3f));
		SetUboDs(currentImage, uboDoubleHouses, DSDoubleHouses, i);
	}
}

void Game::RenderFlags(uint32_t currentImage)
{
	for (int i = 0; i < numOfFlags; i++)
	{
		GWorld = glm::translate(glm::mat4(1), glm::vec3(FlagPositions[i].x, FlagPositions[i].y, FlagPositions[i].z)) * glm::rotate(glm::mat4(1.0f), glm::radians(FlagRotationsY[i]), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(FlagRotationsX[i]), glm::vec3(1, 0, 0))  * glm::rotate(glm::mat4(1.0f), glm::radians(FlagRotationsZ[i]), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), glm::vec3(FlagScales[i]));
		SetUboDs(currentImage, uboFlags, DSFlags, i);
	}
}

void Game::RenderBiggerHouses(uint32_t currentImage)
{
	for (int i = 0; i < numOfBiggerHouses; i++)
	{
		GWorld = glm::translate(glm::mat4(1), glm::vec3(BiggerHousePositions[i].x, 0, BiggerHousePositions[i].y)) * glm::rotate(glm::mat4(1.0f), glm::radians(BiggerHouseRotationsX[i]), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(BiggerHouseRotationsZ[i]), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), glm::vec3(0.35f));
		SetUboDs(currentImage, uboBiggerHouses, DSBiggerHouses, i);
	}
}

void Game::RenderChests(uint32_t currentImage)
{
	for (int i = 0; i < numOfChests; i++)
	{	
		if (ChestVisibles[i] == 1) {
			GWorld = glm::translate(glm::mat4(1), glm::vec3(ChestPositions[i].x, 0, ChestPositions[i].y)) * glm::rotate(glm::mat4(1.0f), glm::radians(ChestRotationsX[i]), glm::vec3(1, 0, 0)) * glm::scale(glm::mat4(1), glm::vec3(ChestDimension[0]));
			SetUboDs(currentImage, uboChests, DSChests, i);
		}
		else {
			GWorld = 0;
		}
	}
}

void Game::RenderStatue1(uint32_t currentImage)
{
	for (int i = 0; i < numOfStatue1; i++)
	{
		GWorld = glm::translate(glm::mat4(1), glm::vec3(Statue1Positions[i].x, 0, Statue1Positions[i].y)) * glm::rotate(glm::mat4(1.0f), glm::radians(Statue1RotationsX[i]), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(Statue1RotationsY[i]), glm::vec3(0, 1, 0)) * glm::scale(glm::mat4(1), glm::vec3(2.0f));
		SetUboDs(currentImage, uboStatue1, DSStatue1, i);
	}
}

void Game::RenderStatue2(uint32_t currentImage)
{
	for (int i = 0; i < numOfStatue2; i++)
	{
		GWorld = glm::translate(glm::mat4(1), glm::vec3(Statue2Positions[i].x, 0, Statue2Positions[i].y)) * glm::rotate(glm::mat4(1.0f), glm::radians(Statue2RotationsX[i]), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(Statue2RotationsY[i]), glm::vec3(0, 1, 0)) * glm::scale(glm::mat4(1), glm::vec3(2.0f));
		SetUboDs(currentImage, uboStatue2, DSStatue2, i);
	}
}

void Game::RenderWell(uint32_t currentImage) {

	for (int i = 0; i < numOfWell; i++) {

		GWorld = glm::translate(glm::mat4(1), glm::vec3(WellPosition[i].x, 0, WellPosition[i].y))* glm::rotate(glm::mat4(1.0f), glm::radians(WellRotation[i]), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(WellRotation[i]), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), glm::vec3(0.6f));
		SetUboDs(currentImage, uboWell, DSWell, i);
	}
}

void Game::RenderClouds(uint32_t currentImage) {

	for (int i = 0; i < numOfClouds; i++) {

		GWorld = glm::translate(glm::mat4(1), glm::vec3(CloudsPosition[i].x, CloudsPosition[i].y, CloudsPosition[i].z)) * glm::scale(glm::mat4(1), glm::vec3(CloudsSize[i]));
		SetUboDs(currentImage, uboClouds, DSClouds, i);
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