#include "Starter.hpp"
#include "TextMaker.hpp"


struct GlobalUniformBlock//luce
{
	alignas(16) glm::vec3 DlightDir;
	alignas(16) glm::vec3 DlightColor;
	alignas(16) glm::vec3 AmbLightColor;
	alignas(16) glm::vec3 eyePos;//dove punta telecamera
};

struct MeshUniformBlock
{
	alignas(4) float visible;
	alignas(4) float amb;
	alignas(4) float gamma;
	alignas(16) glm::vec3 sColor;
	alignas(16) glm::mat4 mvpMat;
	alignas(16) glm::mat4 mMat;
	alignas(16) glm::mat4 nMat;
};

struct OverlayUniformBlock
{
	alignas(4) float visible;
};

struct VertexMesh
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 uv;
};

struct VertexOverlay
{
	glm::vec2 pos;
	glm::vec2 UV;
};

class Game : public BaseProject
{
protected:
	// Constant Parameters
	static const int mapScale = 13;
	static const int objectNumScale = 10;
	static const int mapSize = 5 * mapScale;
	static const int numOfAngleHouses = 4;//fatto
	static const int numOfHouses = 18;//fatto
	static const int numOfStones = 1300;
	static const int numOfBushes = 400;
	static const int numOfCastle = 1;//fatto
	static const int numOfWalls = 4;//fatto
	static const int numOfTowers = 2;//m
	static const int numOfLights = 12;
	static const int numOfBiggerHouses = 5;//f
	static const int numOfDoubleHouses = 2;//m
	static const int numOfFlags = 4;
	static const int numOfChests = 1;
	static const int numOfStatue1 = 1;//f
	static const int numOfStatue2 = 1;//f
	static const int numOfWell = 1;//m
	static const int numOfClouds = 12;
	static const int numOfCollisions = (numOfAngleHouses + numOfHouses) * objectNumScale;

	// Descriptor Set Layouts
	DescriptorSetLayout DSLGubo, DSLToon, DSLToonPhong, DSLOverlay;

	// Vertex formats
	VertexDescriptor VMesh, VOverlay;

	// Pipelines
	Pipeline PToon, PToonPhong, POverlay;

	// Models
	Model<VertexMesh> MCharacter, MGround, MHouses, MAngleHouses, MStones, MBushes, 
		MCastle, MWalls, MTowers, MLights, MBiggerHouses, MDoubleHouses, MFlags, MChests,
		MStatue1, MStatue2,MWell, MClouds;
	Model<VertexOverlay> MStartPanel, MWinPanel, MPressEnterPanel;

	// Textures
	Texture TCharacter, TGround, TMedieval, TStone, TBush, TStartPanel, TWall, 
		TChest, TDungeon, TClouds, TWinPanel, TPressEnterPanel;

	// Descriptor sets
	DescriptorSet DSGubo, DSCharacter, DSGround[4], DSHouses[numOfHouses],
		DSAngleHouses[numOfAngleHouses], DSStones[numOfStones], DSBushes[numOfBushes],
		DSCastle[numOfCastle], DSWalls[numOfWalls], DSTowers[numOfTowers], DSLights[numOfLights],
		DSBiggerHouses[numOfBiggerHouses], DSDoubleHouses[numOfDoubleHouses],
		DSFlags[numOfFlags], DSChests[numOfChests], DSStatue1[numOfStatue1], DSStatue2[numOfStatue2],DSWell[numOfWell],DSClouds[numOfClouds],
		DSStartPanel, DSWinPanel,DSPressEnterPanel;

	// Uniform Blocks //altri ?
	GlobalUniformBlock gubo;
	MeshUniformBlock uboCharacter, uboGround[4], uboHouses[numOfHouses],
		uboAngleHouses[numOfAngleHouses], uboStones[numOfStones], uboBushes[numOfBushes], uboCastle[numOfCastle],
		uboWalls[numOfWalls], uboTowers[numOfTowers], uboLights[numOfLights], uboBiggerHouses[numOfBiggerHouses],
		uboDoubleHouses[numOfDoubleHouses], uboFlags[numOfFlags], uboChests[numOfChests], uboStatue1[numOfStatue1],
		uboStatue2[numOfStatue2],uboWell[numOfWell], uboClouds[numOfClouds];
	OverlayUniformBlock uboStartPanel, uboWinPanel, uboPressEnterPanel;

	// Environment Parameters
	float X, Y, Rot, Z;
	glm::vec2 groundPositions[4] = { {-1, -1}, {-1, 0}, {0, -1}, {0, 0} };

	glm::vec2 HousePositions[numOfHouses];
	float HouseRotationsX[numOfHouses];
	float HouseRotationsZ[numOfHouses];

	glm::vec2 AngleHousePositions[numOfAngleHouses];
	float AngleHouseRotationsX[numOfAngleHouses];
	float AngleHouseRotationsZ[numOfAngleHouses];

	glm::vec2 StonePositions[numOfStones];

	glm::vec2 BushPositions[numOfBushes];
	float BushRotationsX[numOfBushes];

	glm::vec2 CastlePositions[numOfCastle];
	float CastleRotationsX[numOfCastle];
	float CastleRotationsZ[numOfCastle];

	glm::vec2 WallPositions[numOfWalls];
	float WallRotationsX[numOfWalls];
	float WallRotationsZ[numOfWalls];

	glm::vec2 LightPositions[numOfLights];
	float LightRotationsX[numOfLights];

	glm::vec2 TowerPositions[numOfTowers];
	float TowerRotationsX[numOfWalls];
	float TowerRotationsZ[numOfWalls];

	glm::vec2 DoubleHousePositions[numOfDoubleHouses];
	float DoubleHousesRotationX[numOfDoubleHouses];
	float DoubleHousesRotationZ[numOfDoubleHouses];

	glm::vec2 BiggerHousePositions[numOfBiggerHouses];
	float BiggerHouseRotationsX[numOfBiggerHouses];
	float BiggerHouseRotationsZ[numOfBiggerHouses];

	glm::vec3 FlagPositions[numOfFlags];
	float FlagRotationsX[numOfFlags];
	float FlagRotationsY[numOfFlags];
	float FlagRotationsZ[numOfFlags];
	float FlagScales[numOfFlags];

	glm::vec2 ChestPositions[numOfChests];
	float ChestRotationsX[numOfChests];
	float ChestDimension[numOfChests];
	float ChestVisibles[numOfChests];

	int const static numOfSpawns = 10;
	glm::vec2 ChestSpawn[numOfSpawns];
	int SpawnsFound[numOfSpawns];

	glm::vec2 Statue1Positions[numOfStatue1];
	float Statue1RotationsX[numOfStatue1];
	float Statue1RotationsY[numOfStatue1];

	glm::vec2 Statue2Positions[numOfStatue2];
	float Statue2RotationsX[numOfStatue2];
	float Statue2RotationsY[numOfStatue2];

	glm::vec2 WellPosition[numOfWell];
	float WellRotation[numOfWell];

	glm::vec3 CloudsPosition[numOfClouds];
	float CloudsSize[numOfClouds];

	// Text
	TextMaker txt;
	std::vector<SingleText> text =
	{	// appare il messaggio che corrisponde al valore di gameState. (round, endGame, extraGame, spectate)
		{1, {"Freecam", "", "", ""}, 0, 0},
		{1, {"- press TAB to show", "", "", ""}, 0, 0},
		{6, {"RULES: Every chest found unlocks", "a smaller one to search for on the map.","Search for the hidden treasures on the map", "You have found : " + std::to_string(0) + " chest" ," - press TAB to hide"," - press ESC to exit"}, 0, 0},
		{4, {"Search for the hidden treasures on the map", "You have found : " + std::to_string(1) + " chests" ," - press TAB to hide"," - press ESC to exit","",""}, 0, 0},
		{4, {"Search for the hidden treasures on the map", "You have found : " + std::to_string(2) + " chests" ," - press TAB to hide"," - press ESC to exit","",""}, 0, 0},
		{4, {"Search for the hidden treasures on the map", "You have found : " + std::to_string(3) + " chests" ," - press TAB to hide"," - press ESC to exit","",""}, 0, 0},
		{4, {"Search for the hidden treasures on the map", "You have found : " + std::to_string(4) + " chests" ," - press TAB to hide"," - press ESC to exit","",""}, 0, 0},
		{4, {"Search for the hidden treasures on the map", "You have found : " + std::to_string(5) + " chests" ," - press TAB to hide"," - press ESC to exit","",""}, 0, 0},
		{4, {"Search for the hidden treasures on the map", "You have found : " + std::to_string(6) + " chests" ," - press TAB to hide"," - press ESC to exit","",""}, 0, 0},
		{4, {"Search for the hidden treasures on the map", "You have found : " + std::to_string(7) + " chests" ," - press TAB to hide"," - press ESC to exit","",""}, 0, 0},
		{4, {"Search for the hidden treasures on the map", "You have found : " + std::to_string(8) + " chests" ," - press TAB to hide"," - press ESC to exit","",""}, 0, 0},
		{4, {"You have found all the treasures, Congratulations!", " - Press ENTER to continue exploring the map", " - press ESC to exit", " - restart the game to begin again"}, 0, 0},
		{3, {"- press ESC to exit", "- restart the game to begin again", "", ""}, 0, 0},
	};

	// game Parameters
	int gameState = 2;//         0: freecam/ 1: nascondi text/ 2-10: hai trovato 0-8 chest/ 11: endGame/ 12: extraGame 
	int round = 0;//	         tiene traccia delle casse trovate
	int currentScene = 0;//      0: overlay iniziale/ 1 altrimenti
	int gameEnded = 0;//         0: partita in corso/ 1: game finito/ >1: extra game
	int isNearChest = 0;//		 1: personaggio vicinio ad una cesta/ 0: no
	int spawnIndex = 0;//		 indica in quale spawn è la chest al momento 
	int numOfHiddenChests = 0;// deve essere < numOfSpawns, per ora vien efinito dall'utente tra 1-9
	bool collision = 0;//		 1: se viene rilevata una collision/ 0: altrimenti      
	float Ar;
	glm::mat4 World, ViewPrj, GWorld;

	void setWindowParameters()
	{
		windowWidth = 1920;
		windowHeight = 1080;
		windowTitle = "LET'S FIND THE CHEST";
		windowResizable = GLFW_TRUE;
		initialBackgroundColor = { 0.5f, 0.8f, 0.9f, 1.0f };//colore cielo 

		Ar = (float)windowWidth / (float)windowHeight;
	}

	void onWindowResize(int w, int h) {
		Ar = (float)w / (float)h;
	}

	void setDescriptorPool()
	{
		uniformBlocksInPool = 2 + 4 + (numOfHouses + numOfAngleHouses + numOfStones + numOfBushes + numOfCastle + numOfWalls + numOfTowers + numOfLights + numOfDoubleHouses + numOfBiggerHouses + numOfFlags + numOfChests + numOfStatue1 +numOfStatue2 + numOfWell+ numOfClouds) * 2 + 4 + 1 + 1 ;
		texturesInPool = 12 + 1;
		setsInPool = 2 + 4 + numOfHouses + numOfAngleHouses + numOfStones + numOfBushes + numOfCastle + numOfWalls + numOfTowers + numOfLights + numOfDoubleHouses + numOfBiggerHouses + numOfFlags + numOfChests + numOfStatue1 + numOfStatue2 + numOfWell + numOfClouds + 4 + 1 + 1 ;
	}

	void localInit()
	{
		// Initializing Descriptor Set Layouts
		DSLGubo.init(this, {
			{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS}
			});
		DSLToon.init(this, {
			{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS},
			{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
			});
		DSLToonPhong.init(this, {
			{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS},
			{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
			});
		DSLOverlay.init(this, {
			{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS},
			{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
			});

		// Initializing Vertex Descriptor
		VMesh.init(this, {
			{0, sizeof(VertexMesh), VK_VERTEX_INPUT_RATE_VERTEX}
			}, {
				{0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexMesh, pos),
					   sizeof(glm::vec3), POSITION},
				{0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexMesh, norm),
					   sizeof(glm::vec3), NORMAL},
				{0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexMesh, uv),
					   sizeof(glm::vec2), UV}
			});
		VOverlay.init(this, {
					  {0, sizeof(VertexOverlay), VK_VERTEX_INPUT_RATE_VERTEX}
			}, {
				{0, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexOverlay, pos),
						sizeof(glm::vec2), OTHER},
				{0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexOverlay, UV),
						sizeof(glm::vec2), UV}
			});

				// Initializing Pipelines
				PToon.init(this, &VMesh, "shaders/ToonVert.spv", "shaders/ToonFrag.spv", { &DSLGubo, &DSLToon });
				PToonPhong.init(this, &VMesh, "shaders/ToonPhongVert.spv", "shaders/ToonPhongFrag.spv", { &DSLGubo, &DSLToonPhong });
				POverlay.init(this, &VOverlay, "shaders/OverlayVert.spv", "shaders/OverlayFrag.spv", { &DSLOverlay });
				POverlay.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL, VK_POLYGON_MODE_FILL, VK_CULL_MODE_NONE, false);

				// Initializing Models
				MCharacter.init(this, &VMesh, "Models/horse.mgcg", MGCG);
				MGround.init(this, &VMesh, "Models/ground.obj", OBJ);
				MHouses.init(this, &VMesh, "Models/house1.mgcg", MGCG);
				MAngleHouses.init(this, &VMesh, "Models/house2.mgcg", MGCG);
				MStones.init(this, &VMesh, "Models/Stone1.mgcg", MGCG);
				MBushes.init(this, &VMesh, "Models/Bush.mgcg", MGCG);
				MCastle.init(this, &VMesh, "Models/castle1.mgcg", MGCG);
				MWalls.init(this, &VMesh, "Models/CastleWall.mgcg", MGCG);
				MTowers.init(this, &VMesh, "Models/tower.mgcg", MGCG);
				MLights.init(this, &VMesh, "Models/Light.mgcg", MGCG);
				MBiggerHouses.init(this, &VMesh, "Models/house4.mgcg", MGCG);
				MDoubleHouses.init(this, &VMesh, "Models/house3.mgcg", MGCG);
				MFlags.init(this, &VMesh, "Models/flag.mgcg", MGCG);
				MChests.init(this, &VMesh, "Models/chest.mgcg", MGCG);
				MStatue1.init(this, &VMesh, "Models/statue1.mgcg", MGCG);
				MStatue2.init(this, &VMesh, "Models/statue2.mgcg", MGCG);
				MWell.init(this, &VMesh, "Models/Pozzo.mgcg", MGCG);
				MClouds.init(this, &VMesh, "Models/cloud.obj", OBJ);
				// Overlay Models
				CreateOverlayMesh(MStartPanel.vertices, MStartPanel.indices);
				MStartPanel.initMesh(this, &VOverlay);
				CreateOverlayMesh(MWinPanel.vertices, MWinPanel.indices);
				MWinPanel.initMesh(this, &VOverlay);
				CreateOverlayMesh(MPressEnterPanel.vertices, MPressEnterPanel.indices, 0.1f, 0.6f, -0.0f, -0.2f);//l,r,t,b
				MPressEnterPanel.initMesh(this, &VOverlay);

				// Initializing Textures
				TCharacter.init(this, "textures/animals.png");
				TGround.init(this, "textures/street2.png");
				TMedieval.init(this, "textures/medieval.png");
				TStartPanel.init(this, "textures/inizio2.png");
				TStone.init(this, "textures/street.png");
				TBush.init(this, "textures/bush.png");
				TWall.init(this, "textures/wall.png");
				TChest.init(this, "textures/chest.png");
				TDungeon.init(this, "textures/dungeon.png");
				TClouds.init(this, "textures/clouds.png");
				TWinPanel.init(this, "textures/fine.png");
				TPressEnterPanel.init(this, "textures/SchermataPressEnter.png");
				txt.init(this, &text, -0.95, 0.70, 1.0 / 1200.0, 1.0 / 800.0);

				ObjectsParameters();
	}

	void pipelinesAndDescriptorSetsInit()
	{
		// Creating Pipelines
		PToon.create();
		PToonPhong.create();
		POverlay.create();

		// Defining the Descriptor Sets
		DSGubo.init(this, &DSLGubo, {
					{0, UNIFORM, sizeof(GlobalUniformBlock), nullptr}
			});
		DSCharacter.init(this, &DSLToon, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TCharacter}
			});
		for (int i = 0; i < 4; i++)
		{
			DSGround[i].init(this, &DSLToonPhong, {
						{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
						{1, TEXTURE, 0, &TGround}
				});
		}
		for (int i = 0; i < numOfHouses; i++)
		{
			DSHouses[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TMedieval},
				});
		}
		for (int i = 0; i < numOfAngleHouses; i++)
		{
			DSAngleHouses[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TMedieval},
				});
		}
		for (int i = 0; i < numOfStones; i++)
		{
			DSStones[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TStone},
				});
		}
		for (int i = 0; i < numOfBushes; i++)
		{
			DSBushes[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TBush},
				});
		}
		for (int i = 0; i < numOfCastle; i++)
		{
			DSCastle[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TMedieval},
				});
		}
		for (int i = 0; i < numOfWalls; i++)
		{
			DSWalls[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TWall},
				});
		}
		for (int i = 0; i < numOfTowers; i++)
		{
			DSTowers[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TMedieval},
				});
		}
		for (int i = 0; i < numOfLights; i++)
		{
			DSLights[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TMedieval},
				});
		}
		for (int i = 0; i < numOfDoubleHouses; i++)
		{
			DSDoubleHouses[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TMedieval},
				});
		}
		for (int i = 0; i < numOfBiggerHouses; i++)
		{
			DSBiggerHouses[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TMedieval},
				});
		}
		for (int i = 0; i < numOfFlags; i++)
		{
			DSFlags[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TMedieval},
				});
		}
		for (int i = 0; i < numOfChests; i++)
		{
			DSChests[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TChest},
				});
		}
		for (int i = 0; i < numOfStatue1; i++)
		{
			DSStatue1[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TDungeon},
				});
		}
		for (int i = 0; i < numOfStatue2; i++)
		{
			DSStatue2[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TDungeon},
				});
		}
		for (int i = 0; i < numOfWell; i++)
		{
			DSWell[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TMedieval},
				});
		}
		for (int i = 0; i < numOfClouds; i++)
		{
			DSClouds[i].init(this, &DSLToon, {
					{0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
					{1, TEXTURE, 0, &TClouds},
				});
		}
		DSStartPanel.init(this, &DSLOverlay, {
					{0, UNIFORM, sizeof(OverlayUniformBlock), nullptr},
					{1, TEXTURE, 0, &TStartPanel}
			});
		DSWinPanel.init(this, &DSLOverlay, {
					{0, UNIFORM, sizeof(OverlayUniformBlock), nullptr},
					{1, TEXTURE, 0, &TWinPanel}
			});
		DSPressEnterPanel.init(this, &DSLOverlay, {
					{0, UNIFORM, sizeof(OverlayUniformBlock), nullptr},
					{1, TEXTURE, 0, &TPressEnterPanel}
			});
		txt.pipelinesAndDescriptorSetsInit();
	}

	void pipelinesAndDescriptorSetsCleanup()
	{
		// Cleanup Pipelines
		PToon.cleanup();
		PToonPhong.cleanup();

		// Cleanup Descriptor Sets
		DSGubo.cleanup();
		DSCharacter.cleanup();
		for (int i = 0; i < 4; i++)
		{
			DSGround[i].cleanup();
		}
		for (int i = 0; i < numOfHouses; i++)
			DSHouses[i].cleanup();
		for (int i = 0; i < numOfAngleHouses; i++)
			DSAngleHouses[i].cleanup();
		for (int i = 0; i < numOfStones; i++)
			DSStones[i].cleanup();
		for (int i = 0; i < numOfBushes; i++)
			DSBushes[i].cleanup();
		for (int i = 0; i < numOfCastle; i++)
			DSCastle[i].cleanup();
		for (int i = 0; i < numOfWalls; i++)
			DSWalls[i].cleanup();
		for (int i = 0; i < numOfTowers; i++)
			DSTowers[i].cleanup();
		for (int i = 0; i < numOfLights; i++)
			DSLights[i].cleanup();
		for (int i = 0; i < numOfBiggerHouses; i++)
			DSBiggerHouses[i].cleanup();
		for (int i = 0; i < numOfDoubleHouses; i++)
			DSDoubleHouses[i].cleanup();
		for (int i = 0; i < numOfFlags; i++)
			DSFlags[i].cleanup();
		for (int i = 0; i < numOfChests; i++)
			DSChests[i].cleanup();
		for (int i = 0; i < numOfStatue1; i++)
			DSStatue1[i].cleanup();
		for (int i = 0; i < numOfStatue2; i++)
			DSStatue2[i].cleanup();
		for (int i = 0; i < numOfWell; i++)
			DSWell[i].cleanup();
		for (int i = 0; i < numOfClouds; i++)
			DSClouds[i].cleanup();
		DSStartPanel.cleanup();
		DSWinPanel.cleanup();
		DSPressEnterPanel.cleanup();
	}

	void localCleanup()
	{
		// Cleanup Textures
		TCharacter.cleanup();
		TGround.cleanup();
		TMedieval.cleanup();
		TStone.cleanup();
		TBush.cleanup();
		TWall.cleanup();
		TChest.cleanup();
		TDungeon.cleanup();
		TClouds.cleanup();
		TStartPanel.cleanup();
		TWinPanel.cleanup();
		TPressEnterPanel.cleanup();

		// Cleanup Models
		MCharacter.cleanup();
		MGround.cleanup();
		MHouses.cleanup();
		MAngleHouses.cleanup();
		MStones.cleanup();
		MBushes.cleanup();
		MCastle.cleanup();
		MWalls.cleanup();
		MTowers.cleanup();
		MLights.cleanup();
		MDoubleHouses.cleanup();
		MBiggerHouses.cleanup();
		MFlags.cleanup();
		MChests.cleanup();
		MStartPanel.cleanup();
		MStatue1.cleanup();
		MStatue2.cleanup();
		MWell.cleanup();
		MClouds.cleanup();
		MPressEnterPanel.cleanup();

		// Cleanup Descriptor Set Layouts
		DSLGubo.cleanup();
		DSLToon.cleanup();
		DSLToonPhong.cleanup();
		DSLOverlay.cleanup();

		// Destroying the Pipeline
		PToon.destroy();
		PToonPhong.destroy();
		POverlay.destroy();

		txt.localCleanup();
	}

	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage)
	{
		// Set Gubo
		DSGubo.bind(commandBuffer, PToon, 0, currentImage);

		// Character
		// Binding the Pipeline
		PToon.bind(commandBuffer);
		// Binding the Model
		MCharacter.bind(commandBuffer);
		// Binding the Descriptor Set
		DSCharacter.bind(commandBuffer, PToon, 1, currentImage);
		// Record the drawing command in the command buffer
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(MCharacter.indices.size()), 1, 0, 0, 0);

		MHouses.bind(commandBuffer);
		for (int i = 0; i < numOfHouses; i++) {
			DSHouses[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MHouses.indices.size()), 1, 0, 0, 0);
		}

		MAngleHouses.bind(commandBuffer);
		for (int i = 0; i < numOfAngleHouses; i++) {
			DSAngleHouses[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MAngleHouses.indices.size()), 1, 0, 0, 0);
		}

		MStones.bind(commandBuffer);
		for (int i = 0; i < numOfStones; i++) {
			DSStones[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MStones.indices.size()), 1, 0, 0, 0);
		}

		MBushes.bind(commandBuffer);
		for (int i = 0; i < numOfBushes; i++) {
			DSBushes[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MBushes.indices.size()), 1, 0, 0, 0);
		}

		MCastle.bind(commandBuffer);
		for (int i = 0; i < numOfCastle; i++) {
			DSCastle[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MCastle.indices.size()), 1, 0, 0, 0);
		}

		MWalls.bind(commandBuffer);
		for (int i = 0; i < numOfWalls; i++) {
			DSWalls[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MWalls.indices.size()), 1, 0, 0, 0);
		}

		MLights.bind(commandBuffer);
		for (int i = 0; i < numOfLights; i++) {
			DSLights[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MLights.indices.size()), 1, 0, 0, 0);
		}

		MTowers.bind(commandBuffer);
		for (int i = 0; i < numOfTowers; i++) {
			DSTowers[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MTowers.indices.size()), 1, 0, 0, 0);
		}

		MBiggerHouses.bind(commandBuffer);
		for (int i = 0; i < numOfBiggerHouses; i++) {
			DSBiggerHouses[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MBiggerHouses.indices.size()), 1, 0, 0, 0);
		}

		MDoubleHouses.bind(commandBuffer);
		for (int i = 0; i < numOfDoubleHouses; i++) {
			DSDoubleHouses[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MDoubleHouses.indices.size()), 1, 0, 0, 0);
		}

		MFlags.bind(commandBuffer);
		for (int i = 0; i < numOfFlags; i++) {
			DSFlags[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MFlags.indices.size()), 1, 0, 0, 0);
		}

		MChests.bind(commandBuffer);
		for (int i = 0; i < numOfChests; i++) {
			DSChests[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MChests.indices.size()), 1, 0, 0, 0);
		}

		MStatue1.bind(commandBuffer);
		for (int i = 0; i < numOfStatue1; i++) {
			DSStatue1[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MStatue1.indices.size()), 1, 0, 0, 0);
		}

		MStatue2.bind(commandBuffer);
		for (int i = 0; i < numOfStatue2; i++) {
			DSStatue2[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MStatue2.indices.size()), 1, 0, 0, 0);
		}

		MWell.bind(commandBuffer);
		for (int i = 0; i < numOfWell; i++) {
			DSWell[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MWell.indices.size()), 1, 0, 0, 0);
		}

		MClouds.bind(commandBuffer);
		for (int i = 0; i < numOfClouds; i++) {
			DSClouds[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MClouds.indices.size()), 1, 0, 0, 0);
		}

		DSGubo.bind(commandBuffer, PToon, 0, currentImage);

		// Ground
		//PToonPhong.bind(commandBuffer);
		MGround.bind(commandBuffer);
		for (int i = 0; i < 4; i++)
		{
			DSGround[i].bind(commandBuffer, PToon, 1, currentImage);
			vkCmdDrawIndexed(commandBuffer,
				static_cast<uint32_t>(MGround.indices.size()), 1, 0, 0, 0);
		}

		// Overlays ??
		POverlay.bind(commandBuffer);
		MStartPanel.bind(commandBuffer);
		DSStartPanel.bind(commandBuffer, POverlay, 0, currentImage);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(MStartPanel.indices.size()), 1, 0, 0, 0);

		MWinPanel.bind(commandBuffer);
		DSWinPanel.bind(commandBuffer, POverlay, 0, currentImage);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(MWinPanel.indices.size()), 1, 0, 0, 0);

		MPressEnterPanel.bind(commandBuffer);
		DSPressEnterPanel.bind(commandBuffer, POverlay, 0, currentImage);
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(MPressEnterPanel.indices.size()), 1, 0, 0, 0);

		txt.populateCommandBuffer(commandBuffer, currentImage, gameState, currentScene);
	}

	void updateUniformBuffer(uint32_t currentImage)
	{
		static bool press = false;
		static int curPress = 0;
		static bool tabPress = true;

		//esc
		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		//overlay iniziale, scelta durata game
		if (currentScene == 0 && glfwGetKey(window, GLFW_KEY_1))
		{
			currentScene++;
			numOfHiddenChests = 1;
			RebuildPipeline();
		}
		if (currentScene == 0 && glfwGetKey(window, GLFW_KEY_2))
		{
			currentScene++;
			numOfHiddenChests = 2;
			RebuildPipeline();
		}
		if (currentScene == 0 && glfwGetKey(window, GLFW_KEY_3))
		{
			currentScene++;
			numOfHiddenChests = 3;
			RebuildPipeline();
		}
		if (currentScene == 0 && glfwGetKey(window, GLFW_KEY_3))
		{
			currentScene++;
			numOfHiddenChests = 3;
			RebuildPipeline();
		}
		if (currentScene == 0 && glfwGetKey(window, GLFW_KEY_4))
		{
			currentScene++;
			numOfHiddenChests = 4;
			RebuildPipeline();
		}
		if (currentScene == 0 && glfwGetKey(window, GLFW_KEY_5))
		{
			currentScene++;
			numOfHiddenChests = 5;
			RebuildPipeline();
		}
		if (currentScene == 0 && glfwGetKey(window, GLFW_KEY_6))
		{
			currentScene++;
			numOfHiddenChests = 6;
			RebuildPipeline();
		}
		if (currentScene == 0 && glfwGetKey(window, GLFW_KEY_7))
		{
			currentScene++;
			numOfHiddenChests = 7;
			RebuildPipeline();
		}
		if (currentScene == 0 && glfwGetKey(window, GLFW_KEY_8))
		{
			currentScene++;
			numOfHiddenChests = 8;
			RebuildPipeline();
		}
		if (currentScene == 0 && glfwGetKey(window, GLFW_KEY_9))
		{
			currentScene++;
			numOfHiddenChests = 9;
			RebuildPipeline();
		}

		//gestione mostra/nascondi menu
		if (tabPress == true) {
			if (gameState >= 2 && gameState <= 2 + numOfHiddenChests - 1 && glfwGetKey(window, GLFW_KEY_TAB))
			{
				gameState = 1;
				//round = numOfHiddenChests + 2;
				RebuildPipeline();
			}
			else {
				if (gameState == 1 && glfwGetKey(window, GLFW_KEY_TAB))
				{
					gameState = 2 + round;
					RebuildPipeline();
				}
			}
		}
		else {
			tabPress = true;
		}

		//endGame -> extraGame
		if (gameEnded == 1 && glfwGetKey(window, GLFW_KEY_ENTER))
		{
			gameState = 12;
			round++;
			gameEnded++;
			RebuildPipeline();
		}

		//overlay iniziale visibile all'inizio
		uboStartPanel.visible = (currentScene == 0) ? 1.0f : 0.0f;
		DSStartPanel.map(currentImage, &uboStartPanel, sizeof(uboStartPanel), 0);
		//overlay finale visible solo quando finisce il gioco, scompare se si decide extra game
		uboWinPanel.visible = (gameEnded == 1) ? 1.0f : 0.0f;
		DSWinPanel.map(currentImage, &uboWinPanel, sizeof(uboWinPanel), 0);
		//overlay press enter visible solo quando vicini a un tesoro 
		uboPressEnterPanel.visible = (isNearChest == 1) ? 1.0f : 0.0f;
		DSPressEnterPanel.map(currentImage, &uboPressEnterPanel, sizeof(uboPressEnterPanel), 0);

		//player <-> spectator
		if (glfwGetKey(window, GLFW_KEY_M)) {
			if (!press) {
				press = true;
				curPress = GLFW_KEY_M;
				if (gameState == 0) {
					gameState = 2 + round;
				}
				else {
					gameState = 0;
				}
				RebuildPipeline();
			}
		}
		else {
			if ((curPress == GLFW_KEY_M) && press) {
				press = false;
				curPress = 0;
			}
		}
		if (currentScene == 1)
		{
			if (gameState == 0) {
				Spectate();
			}
			else {
				PlayerController(currentImage);
			}
		}

		gubo.DlightDir = glm::vec3(cos(glm::radians(135.0f)) * cos(glm::radians(210.0f)), sin(glm::radians(135.0f)), cos(glm::radians(135.0f)) * sin(glm::radians(210.0f)));
		gubo.DlightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		gubo.AmbLightColor = glm::vec3(0.2f);
		gubo.eyePos = glm::vec3(100.0, 100.0, 100.0);

		DSGubo.map(currentImage, &gubo, sizeof(gubo), 0);

		RenderCharacter(currentImage);
		RenderEnvironment(currentImage);
	}

	void CreateOverlayMesh(std::vector<VertexOverlay>& vDef, std::vector<uint32_t>& vIdx, float left = -1.0f, float right = 1.0f, float top = 1.0f, float bottom = -1.0f);
	void RenderCharacter(uint32_t currentImage);
	void RenderEnvironment(uint32_t currentImage);
	void RenderGround(uint32_t currentImage);
	void RenderHouses(uint32_t currentImage);
	void RenderAngleHouses(uint32_t currentImage);
	void RenderStones(uint32_t currentImage);
	void RenderBushes(uint32_t currentImage);
	void RenderCastle(uint32_t currentImage);
	void RenderWalls(uint32_t currentImage);
	void RenderLights(uint32_t currentImage);
	void RenderTowers(uint32_t currentImage);
	void RenderDoubleHouses(uint32_t currentImage);
	void RenderBiggerHouses(uint32_t currentImage);
	void RenderFlags(uint32_t currentImage);
	void RenderChests(uint32_t currentImage);
	void RenderStatue1(uint32_t currentImage);
	void RenderStatue2(uint32_t currentImage);
	void RenderWell(uint32_t currentImage);
	void RenderClouds(uint32_t currentImage);
	/*cosa fa?*/void SetUboDs(uint32_t currentImage, MeshUniformBlock ubo[], DescriptorSet DS[], int index, float visible = 1.0f, float amb = 1.0f,
		float gamma = 80.0f, glm::vec3 sColor = glm::vec3(1.0f));
	void CollisionCheck(glm::vec3& pos, glm::vec3& nextPos);
	void FoundChest(glm::vec3 pos);
	void ObjectsParameters();
	void Spectate();
	void PlayerController(uint32_t currentImage);
};

#include "navigationHandler.hpp"
#include "collisionManager.hpp"
#include "render.hpp"
#include "setParameters.hpp"

void Game::CreateOverlayMesh(std::vector<VertexOverlay>& vDef, std::vector<uint32_t>& vIdx, float left, float right, float top, float bottom)
{
	vDef = { {{left, bottom}, {0.0f, 0.0f}}, {{left, top}, {0.0f,1.0f}},
			 {{right, bottom}, {1.0f,0.0f}}, {{right, top}, {1.0f,1.0f}} };
	vIdx = { 0, 1, 2,    1, 2, 3 };
}

int main() {
	Game app;
	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}