﻿#include "Board.h"

string Board::fillNumber(string s, UINT MaxNumber)
{
	while (s.size() < MaxNumber)
		s = "0" + s;
	return s;
}

Board::Board(float X, float Y)
{
	boardTexture = TextureManager::GetInstance()->GetTexture(objectType::BOARD);
	boardSprite = new GameSprite(boardTexture, 0);

	spriteIconDoubleShot = new GameSprite(TextureManager::GetInstance()->GetTexture(objectType::ITEMDOUBESHOT), 0);

	x = X;
	y = Y;

	_boardHealth = new BoardHealth(x + 110, y + 30);
}


void Board::Render(Simon* simon, int state, int RemainingTime, GameObject* boss)
{
	boardSprite->Draw(x, y);

	_font.Draw(x + 100, y + 15, fillNumber(std::to_string(simon->getScore()), 6));

	_font.Draw(x + 295, y + 15, fillNumber(std::to_string(RemainingTime), 4));

	_font.Draw(x + 465, y + 15, fillNumber(std::to_string(state), 2));

	_font.Draw(x + 393, y + 33, fillNumber(std::to_string(simon->getHeartCollect()), 2)); // Số lượng tim nhặt dc
	_font.Draw(x + 393, y + 51, fillNumber(std::to_string(simon->getLives()), 2)); // số mạng sông


	int BloodBoss = 16;
	if (boss != NULL)
	{
		BloodBoss = (int)(boss->getHealth() * 16 / 24);// HEALTH =24 -> 16 vạch
		if (BloodBoss == 0 && boss->getHealth() > 0)
			BloodBoss = 1;
	}
	_boardHealth->Draw(simon->getHealth(), BloodBoss);
	objectType TypeWeaponCollect = simon->getTypeWeaponCollect();
	switch (TypeWeaponCollect)
	{
	case objectType::DAGGER:
		simon->mapWeapon[TypeWeaponCollect]->renderIcon(x + 310.0f, y + 40.0f);
		break;
	case objectType::HOLYWATER:
		simon->mapWeapon[TypeWeaponCollect]->renderIcon(x + 312, y + 33);
		break;
	case objectType::STOPWATCH:
		simon->mapWeapon[TypeWeaponCollect]->renderIcon(x + 312, y + 31);
		break;
	case objectType::THROWINGAXE:
		simon->mapWeapon[TypeWeaponCollect]->renderIcon(x + 310, y + 35);
		break;
	case objectType::BOOMERANG:
		simon->mapWeapon[TypeWeaponCollect]->renderIcon(x + 310, y + 35);
		break;
	default:
		break;
	}

	if (simon->getIsUseDoubleShot())
	{
		spriteIconDoubleShot->Draw(x + 465, y + 35);
	}
}


Board::~Board()
{
	SAFE_DELETE(boardTexture);
}

void Board::SetTexture(GameTexture* tex)
{
	boardTexture = tex;
	boardSprite->texture = tex;
}
