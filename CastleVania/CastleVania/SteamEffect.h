#pragma once

#ifndef __STEAM_H__
#define __STEAM_H__

#define STEAM_GRAVITY 0.0015f 
#define STEAM_MODEL_1 1
#define STEAM_MODEL_2 2
#define STEAM_MODEL_3 3 

#include "Effect.h"

class SteamEffect : public Effect
{
private:
	int _model;
	DWORD dt;
	float dx;
	float dy;
	float vx;
	float vy;

public:

	SteamEffect(float X, float Y, int Model);
	virtual ~SteamEffect();

	void Update(DWORD dt);

};

#endif

#ifndef STEAM_ADD_EFFECT
#define STEAM_ADD_EFFECT(listEffect, vtx, vty) \
listEffect.push_back(new SteamEffect(vtx, vty, STEAM_MODEL_1));\
listEffect.push_back(new SteamEffect(vtx, vty, STEAM_MODEL_2));\
listEffect.push_back(new SteamEffect(vtx, vty, STEAM_MODEL_3));\

#endif
