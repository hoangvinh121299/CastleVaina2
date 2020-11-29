#include "SceneGame.h"
SceneGame::SceneGame()
{
	LoadResources();
}
SceneGame::~SceneGame()
{
	SAFE_DELETE(tileMap);
}
void SceneGame::KeyState(BYTE *state)
{
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

	if (simon->isAttacking) // đang attack
	{
		float vx, vy;
		simon->getSpeed(vx, vy);
		simon->setSpeed(0, vy);
		
		return;
	}
	//Simon ngồi 
	if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		simon->sit();
		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
			simon->right();
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
			simon->left();
		return;
	}
	else
	{
		simon->stop();
	}
	//Đi qua phải
	
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
	if (simon->getFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}
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
	//Simon tấn công bình thường
	if (keycode == DIK_A&&!simon->isAttacking)
		simon->attack(objectType::MORNINGSTAR);
	if (Game::GetInstance()->IsKeyDown(DIK_S) && !simon->isAttacking)
	{
		simon->attack(simon->getTypeWeaponCollect()); //Tấn công với vũ khí phụ
	}
	
}
void SceneGame::OnKeyUp(int keycode)
{
	if (simon->getFreeze() == true) // Đang bóng băng thì không quan tâm phím
	{
		return;
	}
}

void SceneGame::InitGame()
{
	loadMap(objectType::MAP1);
	simon->Init();
	DebugOut(L"InitGame done\n");
}

void SceneGame::resetResources()
{
	gridGame->reloadMapGrid();
	listWeaponOfEnemy.clear();
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
	simon->Update(dt, &listObject);
	
	gridGame->getListObjectFromMapGrid(listObject, camera);
	
	//Camera chạy theo Simon
	if (camera->AllowFollowSimon())
		camera->SetPosition(simon->getX() - SCREEN_WIDTH / 2 + 30, camera->GetYCam());

	camera->Update(dt);
	for (UINT i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Update(dt, &listObject);
	}
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
	for (UINT i = 0; i < listEffect.size(); i++)
		if (listEffect[i]->getFinish() == false)
			listEffect[i]->Update(dt);
	for (UINT i = 0; i < listItem.size(); i++)
	{
		if (!listItem[i]->getFinish())
			listItem[i]->Update(dt, &listObject);//Chỉ kiểm tra va chạm với GROUND
	}
	
	checkCollision();
}

void SceneGame::Render()
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
}

void SceneGame::LoadResources()
{
	//TextureManager*_textureMangager = TextureManager::GetInstance();
	
	gridGame = new Grid();
	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	tileMap = new Map();
	simon = new Simon(camera);
	
	InitGame();
	DebugOut(L"SceneGame Loadresources done\n");
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
		break;
	case objectType::MAP2:
		gridGame->setObjectFilePath((char*)"Resources/Map/Map_2/readfile_object_map2.txt");
		tileMap->loadMap(objectType::MAP2);
		camera->setAllowFollowSimon(true);
		camera->SetPosition(0, 0);
		camera->SetBoundary(0, (float)(tileMap->getMapWidth() - camera->GetWidth())); // biên camera khi chưa qua cửa
		camera->setBoundaryBackup(0, (float)(tileMap->getMapWidth() - camera->GetWidth())); // biên camera khi chưa qua cửa
		simon->setPostion(SIMON_POSITION_DEFAULT);
		listEnemy.push_back(new Ghost(50, 300, 1));
		listEnemy.push_back(new Panther(500, 300, -1,simon));
		listEnemy.push_back(new Bat(200, 100, 1));
		listEnemy.push_back(new Fishmen(50, 300, 1, simon, &listWeaponOfEnemy, camera));
		break;
	default:
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
						case 8:
							listItem.push_back(
								getNewItem(objectTemp->getID(), 
									objectTemp->getType(), 
									simon->getX(), simon->getY()));
							break;
						default:
							break;
						}
						objectTemp->subHealth(1);
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
	checkCollsionWithEnemy();
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
								runEffectHit = true;
								break;
							}
							case objectType::FISHMEN:
							{
								tempObject->subHealth(1);
								runEffectHit = true;
								break;
							}
							case objectType::BAT:
							{
								tempObject->subHealth(1);
								runEffectHit = true;
								break;
							}
							case objectType::PANTHER:
							{
								tempObject->subHealth(1);
								runEffectHit = true;
								break;
							}
							default:
								break;
							}
							if (runEffectHit)
							{
								listEffect.push_back(new EffectHit(listObj[i]->getX() + 10, listObj[i]->getY() + 14));
								listEffect.push_back(new EffectFire(tempObject->getX() - 5, tempObject->getY() + 8));
							}
							//Nếu Dagger va chạm thì xét finish
							if (objWeapon.second->getType() == objectType::DAGGER)
							{
								objWeapon.second->setFinish(true);
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
			if (id == 3 || id == 6) //Nếu id của Torch là 1 hoặc 4 thì là LargeHeart
				return new LargeHeart(x, y);
			if (id == 4 || id == 5)
				return new UpgradeMorningStar(x, y);
			if (id == 7)
				return new ItemDagger(x, y);
		}
		if (ObjectType == objectType::OBJECT_HIDDEN)
		{
			if (id == 8)
				return new MoneyBagExtra(1240, 305);
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
				case objectType::LARGEHEART:
					{
					listItem[i]->setFinish(true);
					break;
					}
				case objectType::UPGRADEMORNINGSTAR:
					{
					MorningStar* objMorningStar = dynamic_cast<MorningStar*>(simon->mapWeapon[objectType::MORNINGSTAR]);
					objMorningStar->upgradeLevel(); //Update MorningStar
					listItem[i]->setFinish(true);
					simon->setFreeze(true);
					break;
					}
				case objectType::ITEMDAGGER:
					{
					simon->getNewWeapon(objectType::DAGGER);
					listItem[i]->setFinish(true);
					break;
					}
				case objectType::BONUS:
					{
					listItem[i]->setFinish(true);
					listEffect.push_back(new EffectMoney(listItem[i]->getX(), listItem[i]->getY(), objectType::EFFECT_MONEY_1000));
					}
			}
			}
		}
	}
}
void SceneGame::checkCollsionWithEnemy()
{
	checkCollisionWeaponWithObject(listEnemy);
}