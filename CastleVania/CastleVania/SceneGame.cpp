#include "SceneGame.h"
SceneGame::SceneGame()
{
	LoadResources();
}
SceneGame::~SceneGame()
{
	SAFE_DELETE(tileMap);
	SAFE_DELETE(gridGame);
}
void SceneGame::KeyState(BYTE *state)
{
	if (simon->getIsDead() || isWaitResetGame || isGameOver)
	{
		return;
	}
	//Đóng băng trạng thái của Simon
	if (simon->getFreeze())
	{
		return;
	}
	//Khi đang nhảy có vận tốc thì sẽ hoàn thành theo quán tính
	//Tạm thời không update Keystate nếu cùng 1 lúc vừa nhảy vừa đi
	if (simon->isJumping && simon->isWalking)
	{
		return;
	}
	//Không update keystate khi simon bị thương
	if (simon->isHurting)
		return;
	//Lúc tự đi không nhận phím
	if (simon->getIsAutoGoX())
		return;
	//Lúc camera tự đi thì không nhận phím
	if (camera->getIsAutoX())
		return;
	if (simon->isAttacking) // đang attack
	{
		float vx, vy;
		simon->getSpeed(vx, vy);
		simon->setSpeed(0, vy);
		
		return;
	}
	if (!simon->isJumping)
	{
		if (Game::GetInstance()->IsKeyDown(DIK_UP) && simon->isAttacking == false)
		{
			if (!simon->isOnStair) //Nếu chưa ở trên thang
			{
				for (UINT i = 0; i < listObject.size(); i++)
				{
					if (listObject[i]->getType() == objectType::STAIR_BOTTOM)
					{
						if (simon->isCollisionWithGround && simon->isColisionObjectwithObject(listObject[i])) //Nếu đang va chạm với mặt đất và va chạm với cả Stair_Bottom
						{
							GameObject* gameobj = dynamic_cast<GameObject*>(listObject[i]);
							simon->directionStair = gameobj->getDirection(); //Lưu hướng cầu thang đang đi vào Simon
							simon->directionY = -1; // Hướng cho simon đi lên
							simon->setDirection(-(simon->directionStair)); //Hướng simon đi lên là hướng của cầu thang
							simon->isOnStair = true; //Set trạng thái đang đi trên cầu thang
							simon->distancePassOnStair = 0;

							//Nếu vị trí của simon không phải là vị trí lên thang
							if (simon->getX() < gameobj->getX())
							{
								simon->setAutoGoX(1, gameobj->getDirection(), /*Khoảng cách đi là khoảng cách của gameobject trừ cho simon*/gameobj->getX() - simon->getX(), SIMON_WALKING_SPEED);

							}
							else
							{
								simon->setAutoGoX(-1, gameobj->getDirection(), /*Khoảng cách đi là khoảng cách của gameobject trừ cho simon*/-gameobj->getX() + simon->getX(), SIMON_WALKING_SPEED);
							}
							return;
						}
					}
				}
			}
			else
			{
				if (simon->isProccessingOnStair == 0 || simon->isProccessingOnStair == 3)
				{
					simon->isWalking = true;
					simon->isProccessingOnStair = 1;
					simon->directionY = -1; //hướng đi lên
					simon->setDirection(simon->directionStair); //Hướng của cầu thang
					simon->setSpeed(simon->getDirection() * SIMON_SPEED_ONSTAIR, -1 * SIMON_SPEED_ONSTAIR);
					/*float vvx, vvy;
					simon->getSpeed(vvx, vvy);*/
				}
			}
		}
		else
		{
			if (Game::GetInstance()->IsKeyDown(DIK_DOWN) && simon->isAttacking == false) //Ngược lại nếu  bấm nút xuống
			{
				if (!simon->isOnStair)//Chưa trên cầu thang
				{
					int countCollisionTop = 0;
					for (UINT i = 0; i < listObject.size(); i++)
					{
						if (listObject[i]->getType() == objectType::STAIR_TOP)
						{
							if (simon->isColisionObjectwithObject(listObject[i])&&simon->isCollisionWithGround)
							{
								GameObject* gameObj = dynamic_cast <GameObject*>(listObject[i]);
								simon->directionStair = gameObj->getDirection();
								simon->directionY = 1;
								simon->setDirection(simon->directionStair);
								simon->isOnStair = true;
								simon->distancePassOnStair = 0;

								//Tự động quay lại chỗ chuẩn bị lên cầu thang
								if (simon->getX()< gameObj->getX())
								{
									simon->setAutoGoX(1, -gameObj->getDirection(), gameObj->getX() - simon->getX(), SIMON_WALKING_SPEED);
								}
								else
								{
									simon->setAutoGoX(-1, -gameObj->getDirection(), simon->getX() - gameObj->getX(), SIMON_WALKING_SPEED);
								}
								countCollisionTop++;
								return;
							
							}
						}
					}
					if (countCollisionTop == 0) //Không đụng stair top, tức là ngồi bình thường
					{
						simon->sit();
							if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
								simon->right();
							if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
								simon->left();
							return;
					}
				}
				//Đã ở trên thang
				else
				{
					if (simon->isProccessingOnStair == 0 || simon->isProccessingOnStair == 3)
					{
						simon->isWalking = true;
						simon->isProccessingOnStair = 1;
						simon->directionY = 1;
						simon->setDirection(simon->directionStair * -1);//Hướng của simon khi đi xuống là hướng ngược của Simon
						simon->setSpeed(simon->getDirection() * SIMON_SPEED_ONSTAIR, SIMON_SPEED_ONSTAIR);
					}
				}
			}
			else
			{
				simon->stop();
			}
		}
	}
	//Khi đang ở trên cầu thang thì không xét qua trái qua phải 
	if (simon->isOnStair) 
		return;
	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
			simon->right();
			simon->walking();
	}
	else
	{ //Hoặc đi qua trái 
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
				simon->left();
				simon->walking();
		}
		else
				//Không thì đứng yên
		{
				simon->stop();
		}
	}
}

void SceneGame::OnKeyDown(int keycode)
{
	
	if (keycode == DIK_R) //Render bounding box

	{
		if (isDebug_RenderBBox == 0)
			isDebug_RenderBBox = 1;
		else
			isDebug_RenderBBox = 0;
		gridGame->reloadMapGrid();
		DebugOut(L"OnkeyDown done\n");
	}

	if (isGameOver)
	{
		switch (keycode)
		{
		case DIK_UP:
		{
			GameOverSelect = GAMEOVER_SELECT_CONTINUE;
			break;
		}
		case DIK_DOWN:
		{
			GameOverSelect = GAMEOVER_SELECT_END;
			break;
		}
		case DIK_RETURN:
		{
			if (GameOverSelect == GAMEOVER_SELECT_CONTINUE)
			{
				InitGame();
				isGameOver = false;
			}
			else
				if (GameOverSelect == GAMEOVER_SELECT_END)
				{
					DestroyWindow(Game::GetInstance()->GetWindowHandle()); // thoát
				}
			break;
		}
		}

		return;
	}

	if (simon->getFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}
	//Không update keystate khi simon bị thương
	if (simon->isHurting)
		return;
	//Simon tấn công bình thường
	if(simon->getIsAutoGoX())
	{
		return;
	}
	if (keycode == DIK_A && !simon->isAttacking&& simon->isProccessingOnStair==0) //Đứng yên trên cầu thang thì mới đánh được 
		simon->attack(objectType::MORNINGSTAR);
	if (Game::GetInstance()->IsKeyDown(DIK_S) && !simon->isAttacking&&simon->isProccessingOnStair==0)
	{
		simon->attack(simon->getTypeWeaponCollect()); //Tấn công với vũ khí phụ
	}
	if (simon->isOnStair)
		return;
	//SIMON nhảy 
	if (keycode == DIK_SPACE && simon->isOnStair==false&&simon->isJumping==false)
	{
		//Nếu vừa nhảy vừa đi thì nhảy 1 đoạn nhỏ theo vx
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT) || Game::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			simon->stop(); // Vô hiệu hoá các động tác đang thực hiện 
			simon->setSpeed(SIMON_WALKING_SPEED * simon->getDirection(), -SIMON_VJUMP);
			simon->isJumping = 1;
			simon->isWalking = 1;
		}
		else
		//Nhảy tại chỗ
		{
			simon->jump();
		}
	}
	
	
}
void SceneGame::OnKeyUp(int keycode)
{
	if (simon->getFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}
	//Không update keystate khi simon bị thương
	if (simon->isHurting)
		return;
}

void SceneGame::InitGame()
{
	loadMap(objectType::MAP2);
	simon->Init();
	//phantomBat->Start();
	gametime->setTime(0);
	replayMusic();
	DebugOut(L"InitGame done\n");
}

void SceneGame::resetResources()
{
	gridGame->reloadMapGrid(); // nạp lại lưới

	/*listItem.clear();
	listEffect.clear();
	listEnemy.clear();
	listWeaponOfEnemy.clear();*/
	camera->setAllowFollowSimon(true);

	isWalkingThroughGate1 = false; // ban đầu chưa cần xử lí qua cửa
	doneWalkingThroughGate1 = false;

	isWalkingThroughGate2 = false; // ban đầu chưa cần xử lí qua cửa
	doneWalkingThroughGate2 = false;
	/* Set Chờ hiển thị màn đen */
	isWaitResetGame = true;
	TimeWaitedResetGame = 0;
	if (phantomBat != NULL) {
		//Khởi tạo các giá trị ban đầu cho boss
		phantomBat->InitResource();
	}
	/*init gameover*/
	isGameOver = false;
	GameOverSelect = GAMEOVER_SELECT_CONTINUE;
}

void SceneGame::Update(DWORD dt)
{
	//Hàm Freeze phải đặt trước update của Simon để ngăn Simon Update
	if (simon->getFreeze() == true)
	{
		simon->updateFreeze(dt);
		if (simon->getFreeze() == true)
			return;
	}
// Xử lí vẽ màn đen trước khi bắt đầu game
	if (isWaitResetGame)
	{
		TimeWaitedResetGame += dt;
		if (TimeWaitedResetGame >= TIME_LIMIT_WAIT_RESET_GAME)
		{
			isWaitResetGame = false;
		}
		else
			return;
	}
//Xử lý liên quan đến máu và thời gian
	if (gametime->getTime() >= GAME_TIME_MAX || simon->getHealth() <= 0) // hết thời gian hoặc hết máu
	{
		if (simon->getIsDead())
		{
			simon->timeWaitAfterDeath += dt;
			if (simon->timeWaitAfterDeath >= 1500)
			{
				bool result = simon->loseLife(); // đã khôi phục x,y

				if (result == true) // còn mạng để chơi tiếp, giảm mạng reset máu xong
				{
					camera->RestorePosition(); // khôi phục vị trí camera;
					camera->RestoreBoundary(); // khôi phục biên camera

					gametime->setTime(0);
					replayMusic();

					resetResources(); // reset lại game
				}
				else
				{
					isGameOver = true;
				}
				return;
			}
		}
		else // chưa chết mà hết máu hoặc time thì set trạng thái isDeadth
		{
			simon->setDead();
		}

	}
	else
	{
		//if (isAllowProcessClearState3 == false) // đang xử lí ClearState thì không đếm time
		//{
		//	gameTime->Update(dt);
		//}
	}

	//Update trạng thái qua cửa của simon
	//Gate 1
	if (isWalkingThroughGate1)
	{
		if (doneWalkingThroughGate1 == false)
		{
			if (camera->GetXCam() >= GATE1_POSTION_CAM_BEFORE_GO) //Camera đã auto đến vị trí trước khi vào trạng thái AutoGo
			{
				simon->setAutoGoX(1, 1, abs(GATE1_POSITION_CAM_AFTER_GO + DISTANCE_AUTOGO_SIMON_GATE - simon->getX()), SIMON_WALKING_SPEED);
			}
		}
		else
		{
			if (camera->GetXCam() >= GATE1_POSITION_CAM_AFTER_GO)
			{
				camera->SetBoundary(GATE1_POSITION_CAM_AFTER_GO, camera->getBoundaryRight());
				camera->setBoundaryBackup(camera->getBoundaryLeft(), camera->getBoundaryRight());
				camera->setAllowFollowSimon(true);
				isWalkingThroughGate1 = false;
				camera->stopAutoGoX();
			}
		}
	}
	//Gate 2
	if (isWalkingThroughGate2)
	{
		if (doneWalkingThroughGate2 == false)
		{
			if (camera->GetXCam() >= GATE2_POSTION_CAM_BEFORE_GO) //Camera đã auto đến vị trí trước khi vào trạng thái AutoGo
			{
				simon->setAutoGoX(1, 1, abs(GATE2_POSITION_CAM_AFTER_GO + DISTANCE_AUTOGO_SIMON_GATE - simon->getX()), SIMON_WALKING_SPEED);
			}
		}
		else
		{
			if (camera->GetXCam() >= GATE2_POSITION_CAM_AFTER_GO)
			{
				camera->SetBoundary(GATE2_POSITION_CAM_AFTER_GO, camera->getBoundaryRight());
				camera->setBoundaryBackup(camera->getBoundaryLeft(), camera->getBoundaryRight());
				camera->setAllowFollowSimon(true);
				isWalkingThroughGate2 = false;
				camera->stopAutoGoX();
			}
		}
	}
	simon-> Update(dt, &listObject);
	
	gridGame->getListObjectFromMapGrid(listObject, camera);
	
	//Camera chạy theo Simon
	if (camera->AllowFollowSimon())
		camera->SetPosition(simon->getX() - SCREEN_WIDTH / 2 + 30, camera->GetYCam());

	camera->Update(dt);
	for (UINT i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Update(dt, &listObject);
	}
	if (!simon->isUsingWeapon(objectType::STOPWATCH))
	{
		for (UINT i = 0; i < listEnemy.size(); i++)
		{
			listEnemy[i]->Update(dt, &listObject);
		}
		for (UINT i = 0; i < listWeaponOfEnemy.size(); i++)
		{
			if (listWeaponOfEnemy[i]->getFinish() == false)
			{
				listWeaponOfEnemy[i]->Update(dt, &listObject);
			}
		}
		if (phantomBat != NULL)
			phantomBat->Update(dt, &listObject);
	}
	for (UINT i = 0; i < listEffect.size(); i++)
		if (listEffect[i]->getFinish() == false)
			listEffect[i]->Update(dt);
	for (UINT i = 0; i < listItem.size(); i++)
	{
		if (!listItem[i]->getFinish())
			listItem[i]->Update(dt, &listObject);//Chỉ kiểm tra va chạm với GROUND
	}
	
	checkCollision();
	if(!simon->getIsDead())
	gametime->Update(dt);
}

void SceneGame::Render()
{
	if (isWaitResetGame)
		return;
	if (!isGameOver)
	{
		tileMap->drawMap(camera);
		for (UINT i = 0; i < listObject.size(); i++)
		{
			listObject[i]->Render(camera);
		}
		for (UINT i = 0; i < listEnemy.size(); i++)
			listEnemy[i]->Render(camera);
		for (UINT i = 0; i < listWeaponOfEnemy.size(); i++)
			listWeaponOfEnemy[i]->Render(camera);
		for (UINT i = 0; i < listEffect.size(); i++)
			listEffect[i]->Render(camera);
		for (UINT i = 0; i < listItem.size(); i++)
		{
			if (!listItem[i]->getFinish())
				listItem[i]->Render(camera);
		}
		simon->Render(camera);
		if (phantomBat != NULL)
			phantomBat->Render(camera);
		board1->Render(simon, currentStage, GAME_TIME_MAX - gametime->getTime(), NULL);
	}
	else
	{
		Text.Draw(200, 200, "GAME OVER");
		Text.Draw(215, 250, "CONTINUE");
		Text.Draw(215, 280, "END");
		switch (GameOverSelect)
		{
			case GAMEOVER_SELECT_CONTINUE:
			{
				_spriteLagerHeart->Draw(175, 245);
				break;
			}
			case GAMEOVER_SELECT_END:
			{
			_spriteLagerHeart->Draw(175, 275);
			break;
			}
		}
	}
}

void SceneGame::LoadResources()
{
	TextureManager*_textureMangager = TextureManager::GetInstance();
	sound = Sound::GetInstance();
	gridGame = new Grid();
	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	tileMap = new Map();
	simon = new Simon(camera);
	_spriteLagerHeart = new GameSprite(TextureManager::GetInstance()->GetTexture(objectType::LARGEHEART), 100);
	board1= new Board(BOARD_DEFAULT_POSITION_X, BOARD_DEFAULT_POSITION_Y);
	gametime = new Gametime();
	InitGame();
}

//Loadmap (Background)
void SceneGame::loadMap(objectType mapCurrent)
{
	this->mapCurrent = mapCurrent;
	switch (mapCurrent)
	{
	case objectType::MAP1:
		gridGame->setObjectFilePath((char*)"Resources/Map/Map_1/readfile_object_map1.txt");
		tileMap->loadMap(objectType::MAP1);
		camera->setAllowFollowSimon(true);
		camera->SetBoundary(0.0f, (float)(tileMap->getMapWidth() - camera->GetWidth())); //set biên camera dựa vào kích thước map
		camera->setBoundaryBackup(camera->getBoundaryLeft(), camera->getBoundaryRight()); // backup lại biên
		camera->SetPosition(0, 0);
		simon->setPostion(SIMON_POSITION_DEFAULT);
		currentStage = 1;
		break;
	case objectType::MAP2:
 		gridGame->setObjectFilePath((char*)"Resources/Map/Map_2/readfile_object_map2.txt");
		tileMap->loadMap(objectType::MAP2);
		camera->setAllowFollowSimon(true);
		camera->SetPosition(0, 0);
		camera->SetBoundary(0, CAMERA_BOUNDARY_BEFORE_GO_GATE1_RIGHT); // biên camera khi chưa qua cửa
		camera->setBoundaryBackup(0, CAMERA_BOUNDARY_BEFORE_GO_GATE1_RIGHT); // biên camera khi chưa qua cửa
		//simon->setPostion(SIMON_POSITION_DEFAULT);
		simon->setPostion(4250.0f, 300.0f);
		listEnemy.push_back(new Ghost(50, 300, 1));
		listEnemy.push_back(new Panther(1398.0f, 225.0f, directionPanther, directionPanther == -1 ? 20.0f : 9.0f, simon));
		listEnemy.push_back(new Bat(200, 100, 1));
		listEnemy.push_back(new Fishmen(50, 300, 1, simon, &listWeaponOfEnemy, camera));
		
		currentStage = 2;
		break;
	}
	resetResources();
}
//Kiểm tra va chạm giữa simon với các vật thể ẩn
void SceneGame::checkCollisionSimonWithHiddenObject()
{
	for (UINT i = 0; i < listObject.size(); i++)
	{
		if (listObject[i]->getType() == objectType::OBJECT_HIDDEN)
		{
			GameObject* objectTemp = listObject[i];
			if (objectTemp->getHealth() > 0)
			{
				if (simon->isColisionObjectwithObject(objectTemp))
				{
					if (mapCurrent == objectType::MAP1)
					{
						switch (objectTemp->getID())
						{
						case 1: //hidden Object cửa
							loadMap(objectType::MAP2);
							break;
						case 8: //BONUS
							listItem.push_back(
								getNewItem(objectTemp->getID(), 
									objectTemp->getType(), 
									simon->getX(), simon->getY()));
							sound->Play(eSound::soundDisplayMonney);
							break;
						default:
							break;
						}
						objectTemp->subHealth(1);
					}
					if (mapCurrent == objectType::MAP2)
					{
						switch (objectTemp->getID())
						{
							case 77: // id 77: object ẩn -> bắt đầu xuống hồ nước trái
							{
								DebugOut(L"Di xuong ho nuoc trai");
								camera->SetPosition(camera->GetXCam(), CAMERA_POSITION_Y_LAKE);
								//Giới hạn biên camera để camera không vượt khỏi Hồ 
								camera->SetBoundary(CAMERA_BOUNDARY_LAKE_LEFT, CAMERA_BOUNDARY_LAKE_RIGHT);
								simon->setPostion(3150, 405);
								gridGame->insertObjectToGrid(GRID_INSERT_OBJECT__GETOUTFROMLAKE_LEFT);
								gridGame->insertObjectToGrid(GRID_INSERT_OBJECT__GETOUTFROMLAKE_RIGHT);

								objectTemp->setHealth(0);
								break;
							}
							case 78: // id 78: object ẩn -> bắt đầu ra khỏi hồ nước trái
							{

								camera->SetPosition(camera->GetXCam(), 0);
								simon->setPostion(3152, 345);
								gridGame->insertObjectToGrid(GRID_INSERT_OBJECT__GETINTOLAKE_LEFT);
								objectTemp->setHealth(0);
								break;
							}
							case 79: // id 79:object ẩn -> bắt đầu bước xuống hồ nước phải
							{
								camera->SetPosition(camera->GetXCam(), CAMERA_POSITION_Y_LAKE);
								simon->setPostion(3825, 450);
			
								objectTemp->setHealth(0);
								gridGame->insertObjectToGrid(GRID_INSERT_OBJECT__GETOUTFROMLAKE_RIGHT); // thêm object ẩn để có thể đi xuống sau khi đã lên lại
								gridGame->insertObjectToGrid(GRID_INSERT_OBJECT__GETOUTFROMLAKE_LEFT);
								break;
							}
							case 80: // id 80:object ẩn -> bắt đầu ra khỏi hồ nước phải
							{
								camera->SetPosition(camera->GetXCam(), 0);
								simon->setPostion(3806, 361);

								objectTemp->setHealth(0);
								camera->setAllowFollowSimon(true);
								gridGame->insertObjectToGrid(GRID_INSERT_OBJECT__GETINTOLAKE_RIGHT); // thêm object ẩn để có thể đi xuống sau khi đã lên lại
							
								break;
							}
							case 82: // đụng trúng box xác nhận simon đã qua GATE1
							{
								if (isWalkingThroughGate1)
								{
									doneWalkingThroughGate1 = true;
									camera->setAutoGoX(abs(GATE1_POSITION_CAM_AFTER_GO - camera->GetXCam()), SIMON_WALKING_SPEED);
								}
								camera->setPositionCamBackup(camera->GetXCam(), camera->GetYCam());
								objectTemp->subHealth(1);
								DebugOut(L"Xac nhan qua xong cua!\n");
								break;
							}
							case 83: // đụng trúng box xác nhận simon đã qua GATE2
							{
								if (isWalkingThroughGate2)
								{
									doneWalkingThroughGate2 = true;
									camera->setAutoGoX(abs(GATE2_POSITION_CAM_AFTER_GO - camera->GetXCam()), SIMON_WALKING_SPEED);
								}
								camera->setPositionCamBackup(camera->GetXCam(), camera->GetYCam());
								objectTemp->subHealth(1);
								DebugOut(L"Xac nhan qua xong cua!\n");
								break;
							}
							case 114: //điểm kích hoạt boss
							{
								DebugOut(L"Va cham voi diem kich hoat boss!\n");
								phantomBat->Start();
								camera->SetBoundary(camera->getBoundaryRight(), camera->getBoundaryRight());
								camera->setAllowFollowSimon(false);
								objectTemp->setHealth(0);
							}
							break;
						default:
							break;
						}
					}
				}
			}
			
		}
	}
}
//Kiểm tra va chạm toàn cục
void SceneGame::checkCollision()
{
	checkCollisionWeaponWithObject(listObject);
	checkCollisionSimonWithHiddenObject();
	checkCollionsionSimonWithItem();
	checkCollisionSimonWithGate();
	checkCollsionWithEnemy();
	checkCollisionSimonWithBoss();
}
//Kiểm tra va chạm giữa vũ khí với object
void SceneGame::checkCollisionWeaponWithObject(vector<GameObject*> listObj)
{
	for (auto& objWeapon : simon->mapWeapon)
	{
		if (objWeapon.second->getFinish() == false) //Vũ khí đang hoạt động
		{
			for (UINT i = 0; i < listObj.size(); i++)
			{
				if (objWeapon.second->getLastTimeAttack() > listObj[i]->getLastTimeAttacked())
				{
					if (objWeapon.second->isColission(listObj[i]) == true)
						{
							bool runEffectHit = false;
							GameObject* tempObject = listObj[i];
							switch (tempObject->getType())
							{
							case objectType::TORCH:
							{
								DebugOut(L"Torch has been attacked\n");
								tempObject->subHealth(1);
								listItem.push_back(getNewItem(tempObject->getID(),
									tempObject->getType(),
									tempObject->getX() + 5,
									tempObject->getY())); //Rớt đồ 
								runEffectHit = true;
								break;
							}
							case objectType::GHOST:
							{
								tempObject->subHealth(1);
								listItem.push_back(getNewItem(
									tempObject->getID(), tempObject->getType(),
									tempObject->getX() + 5, tempObject->getY()));
								runEffectHit = true;
								break;
							}
							case objectType::FISHMEN:
							{
								tempObject->subHealth(1);
								listItem.push_back(getNewItem(
									tempObject->getID(), tempObject->getType(),
									tempObject->getX() + 5, tempObject->getY()));
								runEffectHit = true;
								break;
							}
							case objectType::BAT:
							{
								tempObject->subHealth(1);
								listItem.push_back(getNewItem(
									tempObject->getID(), tempObject->getType(),
									tempObject->getX() + 5, tempObject->getY()));
								runEffectHit = true;
								break;
							}
							case objectType::PANTHER:
							{
								tempObject->subHealth(1);
								listItem.push_back(getNewItem(
									tempObject->getID(), tempObject->getType(),
									tempObject->getX() + 5, tempObject->getY()));
								runEffectHit = true;
								break;
							}
							case objectType::CANDLE:
							{
								tempObject->subHealth(1);
								listItem.push_back(getNewItem(
									tempObject->getID(), tempObject->getType(),
									tempObject->getX() + 5, tempObject->getY()));
								// hiệu ứng hit
								runEffectHit = true;
								break;
							}
							case objectType::BRICK:
							{
								if (objWeapon.second->getType() != objectType::MORNINGSTAR) // chỉ xét MorningStar
									break;

								GameObject* gameObject = listObj[i];
								if (gameObject->getHealth() > 0)
								{
									switch (gameObject->getID())
									{
										case 40: // id 39 : brick 4 ô-> chỉ hiện effect
										{
										gameObject->subHealth(1);
										listItem.push_back(getNewItem(gameObject->getID(), gameObject->getType(), gameObject->getX(), gameObject->getY()));
										HIT_ADD_EFFECT(listEffect, gameObject); // hiệu ứng hit
										BROKEN_BRICK_ADD_EFFECT(listEffect, gameObject); // hiệu ứng BrokenBrick
										sound->Play(eSound::soundBrokenBrick);
										break;
										}
										case 41: // id 40: brick 3 ô-> effect
										{
										gameObject->subHealth(1);
										listItem.push_back(getNewItem(gameObject->getID(), gameObject->getType(), gameObject->getX(), gameObject->getY()));
										HIT_ADD_EFFECT(listEffect, gameObject); // hiệu ứng hit
										BROKEN_BRICK_ADD_EFFECT(listEffect, gameObject); // hiệu ứng BrokenBrick								
										break;
										}
										case 51: // id 114: brick -> a bonus
										{
										gameObject->subHealth(1);
										sound->Play(eSound::soundDisplayMonney);
										listItem.push_back(getNewItem(gameObject->getID(), gameObject->getType(), gameObject->getX(), gameObject->getY()));
										HIT_ADD_EFFECT(listEffect, gameObject); // hiệu ứng hit
										BROKEN_BRICK_ADD_EFFECT(listEffect, gameObject); // hiệu ứng BrokenBrick							
										break;
										}
										case 49: // id 51: brick 2 -> effect
										{
										gameObject->subHealth(1);
										HIT_ADD_EFFECT(listEffect, gameObject); // hiệu ứng hit
										BROKEN_BRICK_ADD_EFFECT(listEffect, gameObject); // hiệu ứng BrokenBrick								
										break;
										}

										case 60: // id 104: double shot
										{
										gameObject->subHealth(1);

										listItem.push_back(getNewItem(gameObject->getID(), gameObject->getType(), gameObject->getX(), gameObject->getY()));

										HIT_ADD_EFFECT(listEffect, gameObject); // hiệu ứng hit
										BROKEN_BRICK_ADD_EFFECT(listEffect, gameObject); // hiệu ứng BrokenBrick								
										break;
										}

										default:
											break;
									}
							
								}
								break;
							}

							default:
								break;
							}
							if (runEffectHit)
							{
								listEffect.push_back(new EffectHit(listObj[i]->getX() + 10, listObj[i]->getY() + 14));
								listEffect.push_back(new EffectFire(tempObject->getX() - 5, tempObject->getY() + 8));
								//Nếu Dagger va chạm thì xét finish
								if (objWeapon.second->getType() == objectType::DAGGER)
								{
									objWeapon.second->setFinish(true);
								}
							}
							
							tempObject->setLastTimeAttacked(objWeapon.second->getLastTimeAttack());
						}

				}
			}
		}
		
	}
}
Item* SceneGame::getNewItem(int id, objectType ObjectType, float x, float y)
{
	if (mapCurrent == objectType::MAP1)
	{
		if (ObjectType == objectType::TORCH)
		{
			if (id == 3 /*|| id == 6*/) //Nếu id của Torch là 1 hoặc 4 thì là LargeHeart
			{
				/*return new LargeHeart(x, y);*/
				return new  BoomerangItem(x, y);
			}
			if (id == 6)
			{
				return new HolyWaterItem(x, y);
			}
			if (id == 4 /*|| id == 5*/)
			{
				/*return new UpgradeMorningStar(x, y);*/
				return new ThrowingAxeItem(x, y);
				
			}
			if (id == 5)
			{
				return new StopWatchItem(x, y);
			}
			if (id == 7)
				return new ItemDagger(x, y);
		}
		if (ObjectType == objectType::OBJECT_HIDDEN)
		{
			if (id == 8)
				return new MoneyBagExtra(1240, 305);
		}
	}
	if (mapCurrent == objectType::MAP2)
	{
		if (ObjectType == objectType::CANDLE)
		{
			switch (id)
			{
			case 2:
				return new MoneyBag(x, y, objectType::MONEY_BAG_WHITE);
				break;
			case 3:
				return new MoneyBag(x, y, objectType::MONEY_BAG_RED);
				break;
			case 4:
				return new MoneyBag(x, y, objectType::MONEY_BAG_PURPLE);
				break;
				default:
			{
				int random = rand() % 15;
					switch (random)
				{
					case 0:
						return new MoneyBag(x, y, objectType::MONEY_BAG_RED);
						break;
					case 1:
						return new MoneyBag(x, y, objectType::MONEY_BAG_WHITE);
						break;
					case 2:
						return new MoneyBag(x, y, objectType::MONEY_BAG_PURPLE);
						break;

					default:
						return new SmallHeart(x, y);
						break;
				}
				break;
			}
			}
		}
		if (ObjectType == objectType::GHOST || ObjectType == objectType::PANTHER || ObjectType == objectType::BAT || ObjectType == objectType::FISHMEN)
		{
			int random = rand() % 15;

			switch (random)
			{
			case 0:
				return new LargeHeart(x, y);
				break;
			case 1:
				return new SmallHeart(x, y);
				break;
			case 2:
				return new ItemDagger(x, y);
				break;
			case 3:
				return new MoneyBagExtra(x, y);
				break;
			case 4:
				return new MoneyBag(x, y, objectType::MONEY_BAG_RED);
				break;
			case 5:
				return new MoneyBag(x, y, objectType::MONEY_BAG_WHITE);
				break;
			case 6:
				return new MoneyBag(x, y, objectType::MONEY_BAG_PURPLE);
				break;
			default: // còn lại là SmallHeart
				return new SmallHeart(x,y);
				break;
			}
		}
		if (ObjectType == objectType::BRICK)
		{
			switch (id)
			{
			case 40:
				return new PotRoast(x, y);
				break;
			case 51:
				return new MoneyBagExtra(x, y);
				break;

			//case 104: // Double shot
			//	return new ItemDoubleShot(X, Y);
			//	break;


			default:
				return new SmallHeart(x,y);
				break;
			}

		}
	}
}
void SceneGame::checkCollionsionSimonWithItem()
{
	for (UINT i = 0; i < listItem.size(); i++)
	{
		if (listItem[i]->getFinish() == false && listItem[i]->isWaitingToDisplay()==false)
			//Chưa kết thúc và không phải trong thời gian chờ để hiển thị
		{
			if (simon->isColissionWithItem(listItem[i]) == true) //Có xảy ra va chạm
			{
				switch (listItem[i]->getType())
				{
					//Đạn của Simon
				case objectType::LARGEHEART:
					{
					simon->setHeartCollect(simon->getHeartCollect() + 5);
					sound->Play(eSound::soundCollectItem);
					listItem[i]->setFinish(true);
					break;
					}
					//Nâng cấp MorningStar
				case objectType::UPGRADEMORNINGSTAR:
					{
					MorningStar* objMorningStar = dynamic_cast<MorningStar*>(simon->mapWeapon[objectType::MORNINGSTAR]);
					objMorningStar->upgradeLevel(); //Update MorningStar
					sound->Play(eSound::soundCollectWeapon);
					listItem[i]->setFinish(true);
					simon->setFreeze(true);
					break;
					}
	
				case objectType::BONUS:
					{
					listItem[i]->setFinish(true);
					simon->setScore(simon->getScore() + 1000);
					listEffect.push_back(new EffectMoney(listItem[i]->getX(), listItem[i]->getY(), objectType::EFFECT_MONEY_1000));
					sound->Play(eSound::soundCollectItem);
					break;
					}

				case objectType::SMALLHEART:
				{	simon->setHeartCollect(simon->getHeartCollect() + 1);
					sound->Play(eSound::soundCollectItem);
					listItem[i]->setFinish(true);
					break;
				}
				/* Xử lí ăn tiền */
				case objectType::MONEY_BAG_RED:
				{
					listItem[i]->setFinish(true);
					simon->setScore(simon->getScore() + 100);
					listEffect.push_back(new EffectMoney(
						listItem[i]->getX(), 
						listItem[i]->getY(), 
						objectType::EFFECT_MONEY_100));
					sound->Play(eSound::soundCollectItem);
					break;
				}

				case objectType::MONEY_BAG_PURPLE:
				{
					listItem[i]->setFinish(true);
					simon->setScore(simon->getScore() + 400);
					listEffect.push_back(new EffectMoney(
						listItem[i]->getX(),
						listItem[i]->getY(),
						objectType::EFFECT_MONEY_400));
					sound->Play(eSound::soundCollectItem);
					break;
				}

				case objectType::MONEY_BAG_WHITE:
				{
					listItem[i]->setFinish(true);
					simon->setScore(simon->getScore() + 700);
					listEffect.push_back(new EffectMoney(
						listItem[i]->getX(),
						listItem[i]->getY(),
						objectType::EFFECT_MONEY_700));
					sound->Play(eSound::soundCollectItem);
					break;
				}
				case objectType::POTROAST:
				{
					listItem[i]->setFinish(true);
					sound->Play(eSound::soundCollectItem);
					simon->setHealth(min(simon->getHealth() + 6, SIMON_DEFAULT_HEALTH)); // tăng 6 đơn vị máu
					break;
				}
				//Vũ khí phụ của Simon
				case objectType::ITEMDAGGER:
				{
					simon->getNewWeapon(objectType::DAGGER);
					listItem[i]->setFinish(true);
					break;
				}
				case objectType::ITEMHOLYWATER:
				{
					simon->getNewWeapon(objectType::HOLYWATER);
					listItem[i]->setFinish(true);

					break;
				}
				case objectType::STOPWATCH:
				{
					simon->getNewWeapon(objectType::STOPWATCH);

					listItem[i]->setFinish(true);
					break;
				}
				case objectType::ITEMTHROWINGAXE:
				{
					simon->getNewWeapon(objectType::THROWINGAXE);

					listItem[i]->setFinish(true);
					break;
				}
				case objectType::ITEMBOOMERANG:
				{
					simon->getNewWeapon(objectType::BOOMERANG);
					listItem[i]->setFinish(true);
					break;
				}
			}
			}
		}
	}
}
void SceneGame::checkCollsionWithEnemy()
{
	checkCollisionWeaponWithObject(listEnemy);
	checkCollisionSimonWithEnemy();
}
void SceneGame::checkCollisionSimonWithEnemy()
{
	if (GetTickCount() - simon->untouchable_Start > SIMON_UNTOUCHABLE_TIME)
	{
		simon->untouchable_Start = 0;
		simon->untouchable = false;
	}
	//Va chạm với Enemy
	//Khi Simon không ở trạng thái bất tử thì có thể va chạm với Enemy hoặc Weapon của Enemy
	if (!simon->untouchable)
	{
		for (UINT i = 0; i < listEnemy.size(); i++)
		{
			GameObject* gameobj = dynamic_cast<GameObject*> (listEnemy[i]);
			if (gameobj->getHealth() > 0) // còn sống
			{
				LPCollisionEvent e = simon->sweptAABBEx(gameobj);
				bool isCollision = false;
				if (e->t > 0 && e->t <= 1) // có va chạm
				{
					simon->setHurt(e);
					isCollision = true;
				}
				if (isCollision == false && simon->checkAABB(gameobj) == true)
				{
					LPCollisionEvent e = new CollisionEvent(1.0f, (float)-simon->getDirection(), 0.0f, NULL);
					simon->setHurt(e);
					isCollision = true;
				}

				//Nếu va chạm với dơi thì dơi cũng tự chết 
				if (isCollision)
				{
					if (gameobj->getType() == objectType::BAT)
					{
						listEffect.push_back(new EffectFire(
							gameobj->getX() - 5, 
							gameobj->getY() + 8)); // hiệu ứng lửa
						gameobj->setHealth(0);
					}
					return; // giảm chi phí duyệt, vì nếu có va chạm thì cũng đang untouchable
				}
			}
		}
	}
	//Va chạm với vũ khí của Enemy
	if (simon->untouchable == false)
	{
		for (UINT i = 0; i < listWeaponOfEnemy.size(); i++)
		{
			if (listWeaponOfEnemy[i]->getFinish() == false)
			{
				LPCollisionEvent e = simon->sweptAABBEx(listWeaponOfEnemy[i]);
				if (e->t > 0 && e->t <= 1) // có va chạm
				{
					simon->setHurt(e);
					return; // giảm chi phí duyệt, vì nếu có va chạm thì cũng đang untouchable
				}

				if (simon->checkAABB(listWeaponOfEnemy[i]) == true)
				{
					LPCollisionEvent e = new CollisionEvent(
						1.0f, (float)-simon->getDirection(), 0.0f, NULL);
					simon->setHurt(e);
					return;
				}
			}
		}
	}
}

void SceneGame::checkCollisionSimonWithGate()
{
	for (UINT i = 0; i < listObject.size(); i++)
	{
		if (listObject[i]->getType() == objectType::GATE)
		{
			//Simon có va chạm với vật thể 
			if (simon->isColisionObjectwithObject(listObject[i]))
			{
				Gate* objectGate = dynamic_cast<Gate*>(listObject[i]);
				if (mapCurrent == objectType::MAP2)
				{
					switch (objectGate->getID())
					{
					case 28: //Gate 1
						if (objectGate->GetStart() == 0)
						{
							//di chuyển camera đến GATE_POSITION_CAM_BEFORE_GO
							camera->SetBoundary(camera->getBoundaryLeft(), camera->getBoundaryRight() + 9999.0f); //Mở rộng biên phải để vào trạng thái AfterGo
							camera->setAutoGoX(abs(GATE1_POSTION_CAM_BEFORE_GO) - camera->GetXCam(), SIMON_WALKING_SPEED);
							//Dừng simon lại
							simon->setSpeed(0, simon->getVy());
							simon->isWalking = 0;
							if (simon->isSitting)
							{
								simon->isSitting = 0; //Huỷ trạng thái ngồi 
								simon->setVy(simon->getVy() - PULL_UP_SIMON_AFTER_SITTING); //Kéo simon lên
		
							}
							isWalkingThroughGate1 = true;
							doneWalkingThroughGate1 = false;
							objectGate->Start(); //Bắt đầu trạng thái đóng mở cửa
							break;
						}
						break;
					case 29: //Gate 2
						if (objectGate->GetStart() == 0)
						{//di chuyển camera đến GATE1_POSITON_BEFORE_GO
							camera->SetBoundary(camera->getBoundaryLeft(), CAMERA_BOUNDARY_BOSS_RIGHT);
							camera->setAutoGoX(abs(GATE2_POSTION_CAM_BEFORE_GO - camera->GetXCam()), SIMON_WALKING_SPEED);
						//Dừng simon lại
							simon->setSpeed(0, simon->getVy());
							simon->isWalking = 0;
							if (simon->isSitting)
							{
								simon->isSitting = 0; //Huỷ trạng thái ngồi 
								simon->setVy(simon->getVy() - PULL_UP_SIMON_AFTER_SITTING); //Kéo simon lên

							}
							isWalkingThroughGate2 = true;
							doneWalkingThroughGate2 = false;
							objectGate->Start(); //Bắt đầu trạng thái đóng mở cửa
							if (phantomBat == NULL) {
								phantomBat = new PhantomBat(simon, camera, &listWeaponOfEnemy);
							}
							break;
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}
}
void SceneGame::checkCollisionSimonWithBoss() {
	if (phantomBat == NULL) return;
	if (phantomBat->getHealth() <= 0) return;
	vector<GameObject*> listObject{ phantomBat };
	checkCollisionWeaponWithObject(listObject);
	if (GetTickCount() - simon->untouchable_Start > SIMON_UNTOUCHABLE_TIME) {
		simon->untouchable_Start = 0;
		simon->untouchable = false;
	}
	if (simon->untouchable == false) {
		if (phantomBat->getHealth() > 0) {
			LPCollisionEvent e = simon->sweptAABBEx(phantomBat);
			if (e->t > 0 && e->t <= 1) {
				simon->setHurt(e);
				DebugOut(L"Simon va cham Boss");
				return;
			}
			if (simon->checkAABB(phantomBat) == true) {
				LPCollisionEvent e = new CollisionEvent(1.0f, (float)-simon->getDirection(), 0.0f, NULL);
				simon->setHurt(e);
				DebugOut(L"Simon va cham Boss 22");
				return;
			}
		}
	}
}
void SceneGame::replayMusic()
{
	sound->StopAll(); //Tắt hết nhạc
	//Bắt đầu lại từ đầu
	sound->Play(eSound::musicState1);
}