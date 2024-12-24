//bool canPickItem = false;
//bool isLost = false;
glm::vec3 camPosition = glm::vec3(0.0, 1.5, 0.0);
float Alpha = 0.0f, Beta = 0.0f;
glm::vec3 realNormX = { 1, 0, 0 };
glm::vec3 realNormY = { 0, 1, 0 };
glm::vec3 realNormZ = { 0, 0, 1 };
float movementAngle = 0;
const float FOVy = glm::radians(45.0f);
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

	Alpha = Alpha - (ANGULAR_SPEED * deltaT * r.y);
	Beta = Beta - (ANGULAR_SPEED * deltaT * r.x);
	if (Beta < glm::radians(-90.0f)) {
		Beta = glm::radians(-90.0f);
	}
	else if (Beta > glm::radians(90.0f)) {
		Beta = glm::radians(90.0f);
	}
	else {
		Beta = Beta; // Non cambia
	}

	glm::vec3 ux = glm::rotate(glm::mat4(1.0f), Alpha, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 1);
	glm::vec3 uy = glm::vec3(0, 1, 0);
	glm::vec3 uz = glm::rotate(glm::mat4(1.0f), Alpha, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1);
	camPosition = camPosition + LINEAR_SPEED * m.x * ux * deltaT;
	camPosition = camPosition + LINEAR_SPEED * m.y * uy * deltaT;
	camPosition = camPosition + LINEAR_SPEED * m.z * uz * deltaT;

	glm::mat4 M = glm::perspective(FOVy, Ar, nearPlane, farPlane);
	M[1][1] *= -1;

	glm::mat4 Mv;
	Mv = glm::translate(glm::mat4(1.0), -camPosition);
	Mv = glm::rotate(glm::mat4(1.0), -Alpha, glm::vec3(0, 1, 0)) * Mv;
	Mv = glm::rotate(glm::mat4(1.0), -Beta, glm::vec3(1, 0, 0)) * Mv;
	ViewPrj = M * Mv;
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

	const float ANGULAR_SPEED = glm::radians(120.0f);
	float LINEAR_SPEED = 5.0f;

	float deltaT;
	glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
	bool fire = false;
	getSixAxis(deltaT, m, r, fire);

	static glm::vec3 pos = startingPosition;
	glm::vec3 nextPos = pos;
	static float yaw = glm::radians(90.0f),//cosi parto girato verso il centro della mappa
				 pitch = 0,
				 roll = 0;
	//static glm::quat rot = glm::quat(1, 0, 0, 0);
	static glm::mat4 ViewPrjOld = glm::mat4(1);
	static glm::mat4 camRy = glm::mat4(1);
	static glm::mat4 finalRy = glm::mat4(1);
	static float finalYaw = 0;
	static int counter = 0;



	if (m.x != 0.0)
	{
		r.y = m.x;
	}
	if (m.z == -1.0) {
		LINEAR_SPEED = 1.0f;//nel caso cammini all'indietro
		r.y = -m.x;
	}
	m.x = 0;

	glm::vec3 ux = glm::vec3(glm::rotate(glm::mat4(1), yaw, glm::vec3(0, 1, 0)) * glm::vec4(1, 0, 0, 1));
	glm::vec3 uy = glm::vec3(0, 1.0f, 0);
	glm::vec3 uz = glm::vec3(glm::rotate(glm::mat4(1), yaw, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1));
	pitch += ANGULAR_SPEED * r.x * deltaT;
	yaw += ANGULAR_SPEED * -r.y * deltaT;
	roll += ANGULAR_SPEED * r.z * deltaT;
	//std::cout << pitch << "-";
	glm::vec2 cp = { 5, 5 };
	nextPos += ux * LINEAR_SPEED * m.x * deltaT;
	nextPos += uz * LINEAR_SPEED * m.z * deltaT;

	CollisionCheck(pos, nextPos);
	if (!collision)
	{
		pos = nextPos;
	}
	collision = false;


	pos += uy * LINEAR_SPEED * m.y * deltaT;

	//std::cout << "post before: \n" << pos.y;
	//PickAnimation(deltaT, pos);
	//std::cout << "post after: \n"<< pos.y;

	/*if (pos.y < 0.0f) {
		isJumping = FALSE;
		VJump = VJumpIni;
	}
	isCollision = false;*/


	glm::mat4 T = glm::translate(glm::mat4(1.0), pos);
	if (pitch <= minPitch)
		pitch = minPitch;
	else if (pitch >= maxPitch)
		pitch = maxPitch;
	glm::mat4 Rx = glm::rotate(glm::mat4(1.0), pitch, glm::vec3(1, 0, 0));
	glm::mat4 Ry = glm::rotate(glm::mat4(1.0), yaw, glm::vec3(0, 1, 0));
	glm::mat4 Rz = glm::rotate(glm::mat4(1.0), roll, glm::vec3(0, 0, 1));
	//if (m.x == 0 && m.z == 0)//personaggio fermo
	//{
	World = T * Ry;
	finalRy = Ry;
	//}
	//else					 //personaggio in movimento
	//{
	//	World = T * Ry;
	//	finalRy = Ry;
	//}

	glm::vec3 c = glm::vec3(T * Ry * glm::vec4(0, camHeight + (camDist * sin(pitch)), camDist * cos(pitch), 1));
	glm::vec3 a = glm::vec3(T * Ry * glm::vec4(0, 0, 0, 1.0f)) + glm::vec3(0, camHeight, 0);

	glm::mat4 Mv = glm::lookAt(c, a, glm::vec3(0, 1, 0));
	glm::mat4 Mp = glm::perspective(FOVy, Ar, nearPlane, farPlane);
	Mp[1][1] *= -1;
	ViewPrj = Mp * Mv;

	// DAMPING
	float lambda = 20;
	if (ViewPrjOld == glm::mat4(1))
		ViewPrjOld = ViewPrj;
	ViewPrj = ViewPrjOld * exp(-lambda * deltaT) + ViewPrj * (1 - exp(-lambda * deltaT));
	ViewPrjOld = ViewPrj;


	FoundChest(pos);
	//ShowInteractionMessage(currentImage, pos);
	//CheckLose(pos);

}

void Game::FoundChest(glm::vec3 pos) {
	for (int i = 0; i < numOfChests; i++) {

		if (pos.x < ChestPositions[i].x + 1.0f && pos.x > ChestPositions[i].x - 1.0f &&
			pos.z < ChestPositions[i].y + 1.0f && pos.z > ChestPositions[i].y - 1.0f  && round < 5) {

			if (glfwGetKey(window, GLFW_KEY_ENTER)) {

				round++;
				ChestPositions[0] = ChestSpawn[round];
				ChestDimension[0] = ChestScale[round];
			}
		}
	}
}