
glm::vec3 camPosition = glm::vec3(0.0, 1.5, 0.0);
float Alpha = 0.0f, Beta = 0.0f;
const float FOV = glm::radians(45.0f);
const float nearPlane = 0.1f;
const float farPlane = 250.f;

void Game::Spectate()
{
	float ANGULAR_SPEED = glm::radians(90.0f);
	float LINEAR_SPEED = 10.0f;
	float deltaT;
	glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
	bool fire = false;

	getSixAxis(deltaT, m, r, fire);

	Alpha -= (ANGULAR_SPEED * deltaT * r.y);
	Beta = Beta - (ANGULAR_SPEED * deltaT * r.x);
	if (Beta < glm::radians(-90.0f)) {
		Beta = glm::radians(-90.0f);
	}
	else if (Beta > glm::radians(90.0f)) {
		Beta = glm::radians(90.0f);
	}

	glm::vec3 ux = glm::rotate(glm::mat4(1.0f), Alpha, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 1);
	glm::vec3 uy = glm::vec3(0, 1, 0);
	glm::vec3 uz = glm::rotate(glm::mat4(1.0f), Alpha, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1);
	camPosition = camPosition + LINEAR_SPEED * m.x * ux * deltaT;
	camPosition = camPosition + LINEAR_SPEED * m.y * uy * deltaT;
	camPosition = camPosition + LINEAR_SPEED * m.z * uz * deltaT;

	glm::mat4 Mp = glm::perspective(FOV, Ar, nearPlane, farPlane);
	Mp[1][1] *= -1;

	glm::mat4 Mv;//look in technique
	Mv = glm::translate(glm::mat4(1.0), -camPosition);
	Mv = glm::rotate(glm::mat4(1.0), -Alpha, glm::vec3(0, 1, 0)) * Mv;
	Mv = glm::rotate(glm::mat4(1.0), -Beta, glm::vec3(1, 0, 0)) * Mv;

	Mvp = Mp * Mv;
}

void Game::PlayerController(uint32_t currentImage)
{

	// posizione di partenza personaggio
	const glm::vec3 startingPosition = glm::vec3(15.0, 0.0, 0.0);//davanti al castello

	// Camera target height and distance
	const float camHeight = 0.75;
	const float camDist = 0.25;
	// Camera Pitch limits
	const float minPitch = glm::radians(-60.0f);
	const float maxPitch = glm::radians(60.0f);

	const float ANGULAR_SPEED = glm::radians(60.0f);//sensibilità comandi
	float LINEAR_SPEED = 5.0f;

	float deltaT;
	glm::vec3 m = glm::vec3(0.0f), //Mov dir
			  r = glm::vec3(0.0f); //Rot dir
	bool fire = false;
	getSixAxis(deltaT, m, r, fire);//tasti

	static glm::vec3 pos = startingPosition;
	glm::vec3 nextPos = pos;
	static float yaw = glm::radians(90.0f),//cosi parto girato verso il centro della mappa
				 pitch = 0,
				 roll = 0;


	if (m.x != 0.0)
	{
		r.y = m.x;//segue movimento
	}
	if (m.z == -1.0) {
		LINEAR_SPEED = 1.0f;//nel caso cammini all'indietro
		
	}


	glm::vec3 ux = glm::vec3(glm::rotate(glm::mat4(1), yaw, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 1));
	glm::vec3 uy = glm::vec3(0, 1.0f, 0);
	glm::vec3 uz = glm::vec3(glm::rotate(glm::mat4(1), yaw, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1));
	pitch += ANGULAR_SPEED * r.x * deltaT;
	yaw += ANGULAR_SPEED * -r.y * deltaT;
	roll += ANGULAR_SPEED * r.z * deltaT;
	
	nextPos += uz * LINEAR_SPEED * m.z * deltaT;//dritto

	CollisionCheck(pos, nextPos);
	if (!collision)
	{
		pos = nextPos;
	}
	collision = false;


	glm::mat4 T = glm::translate(glm::mat4(1.0), pos);
	if (pitch <= minPitch)
		pitch = minPitch;
	else if (pitch >= maxPitch)
		pitch = maxPitch;
	glm::mat4 Rx = glm::rotate(glm::mat4(1.0), pitch, glm::vec3(1, 0, 0));
	glm::mat4 Ry = glm::rotate(glm::mat4(1.0), yaw, glm::vec3(0, 1, 0));
	glm::mat4 Rz = glm::rotate(glm::mat4(1.0), roll, glm::vec3(0, 0, 1));
	
	Mw_character = T * Ry;//character
	

	glm::vec3 c = glm::vec3(T * Ry * glm::vec4(0, camHeight + (camDist * sin(pitch)), camDist * cos(pitch), 1));
	glm::vec3 a = glm::vec3(T * Ry * glm::vec4(0, 0, 0, 1.0f)) + glm::vec3(0, camHeight, 0);
	glm::vec3 u = glm::vec3(0, 1, 0);
	glm::mat4 Mv = glm::lookAt(c, a, u);//look-at technique
	glm::mat4 Mp = glm::perspective(FOV, Ar, nearPlane, farPlane);
	Mp[1][1] *= -1;
	Mvp = Mp * Mv;


	FoundChest(pos);
}

void Game::FoundChest(glm::vec3 pos) {// se il gioco non è finito controlla se il personaggio è vicino ad una chest
	float chestRange = 2.0f;
	if (round < numOfHiddenChests) {
		for (int i = 0; i < numOfChests; i++) {
			if (pos.x < ChestPositions[i].x + chestRange && pos.x > ChestPositions[i].x - chestRange &&
				pos.z < ChestPositions[i].y + chestRange && pos.z > ChestPositions[i].y - chestRange) {
				isNearChest = 1;
				if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS ||
					(glfwJoystickIsGamepad(GLFW_JOYSTICK_1) &&
						glfwGetGamepadState(GLFW_JOYSTICK_1, &state) &&
						state.buttons[GLFW_GAMEPAD_BUTTON_A] == GLFW_PRESS)) {
					isNearChest = 0;
					do {
						spawnIndex = rand() % (numOfSpawns - 1) + 1;// 1 - (numOfSpawns-1) (devo evitare che sorteggi zero) 
					} while (SpawnsFound[spawnIndex] != 0);
					SpawnsFound[spawnIndex] = 1;
					round++;
					if (textIndex != 1) {
						textIndex++;
					}
					RebuildPipeline();
					ChestPositions[0] = ChestSpawn[spawnIndex];
					ChestDimension[0] -= 0.0003;//fattore scala Chest

					//controlla se il gioco è finito, sono state trovate tutte le chests
					if (round == numOfHiddenChests) {
						gameEnded = 1;
						textIndex = 11;
						round = numOfHiddenChests;
						ChestVisibles[0] = 0;
					}
				}
			}
			else {
				isNearChest = 0;
			}
		}
	}
}