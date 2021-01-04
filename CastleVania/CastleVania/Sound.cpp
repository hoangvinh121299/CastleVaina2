
#include "Sound.h"

Sound* Sound::__Instance = NULL;

Sound::Sound()
{
	Init();
	LoadResourceSound();
}



void Sound::LoadResourceSound()
{
	AddSound(eSound::soundWhip, L"Resources/Sound/usingwhip.wav");
	AddSound(eSound::soundHolyWater, L"Resources/Sound/holywater.wav");
	AddSound(eSound::soundHit, L"Resources/Sound/hit.wav");
	AddSound(eSound::soundCollectItem, L"Resources/Sound/collectitem.wav");
	AddSound(eSound::soundCollectWeapon, L"Resources/Sound/collectweapon.wav");
	AddSound(eSound::soundHolyCross, L"Resources/Sound/holycross.wav");
	AddSound(eSound::soundBoomerang, L"Resources/Sound/08-boomerang.wav");



	AddSound(eSound::soundStopTimer, L"Resources/Sound/stoptimer.wav");
	AddSound(eSound::soundDagger, L"Resources/Sound/usingdagger.wav");
	AddSound(eSound::soundDisplayMonney, L"Resources/Sound/display_monney.wav");
	AddSound(eSound::soundAxe, L"Resources/Sound/Axe.wav");
	AddSound(eSound::soundStopWatch, L"Resources/Sound/StopWatch.wav");
	AddSound(eSound::soundInvisibilityPotion_Begin, L"Resources/Sound/InvisibilityPotion_Begin.wav");
	AddSound(eSound::soundInvisibilityPotion_End, L"Resources/Sound/InvisibilityPotion_End.wav");


	AddSound(eSound::soundHurting, L"Resources/Sound/hurting.wav");
	AddSound(eSound::soundOpenDoor, L"Resources/Sound/opendoor.wav");
	AddSound(eSound::soundBrokenBrick, L"Resources/Sound/broken_brick.wav");
	AddSound(eSound::soundSplashwater, L"Resources/Sound/splashwater.wav");
	AddSound(eSound::soundFallingDownWaterSurface, L"Resources/Sound/fallingdownwatersurface.wav");
	AddSound(eSound::soundGetScoreTimer, L"Resources/Sound/getscoretime.wav");
	AddSound(eSound::soundGetScoreHeart, L"Resources/Sound/getscoreheart-[AudioTrimmer.com].wav");



	AddSound(eSound::musicState1, L"Resources/Music/Stage_01_Vampire_Killer.wav");
	AddSound(eSound::musicLifeLost, L"Resources/Music/Life_Lost.wav");

	AddSound(eSound::music_PhantomBat, L"Resources/Music/Boss_Battle_Poison_Mind.wav");
	AddSound(eSound::musicStateClear, L"Resources/Music/Stage_Clear.wav");
	AddSound(eSound::musicGame_Start_Prologue, L"Resources/Music/Game_Start_Prologue.wav");

}

bool Sound::isPlaying(eSound type)
{
	return _ArrSound[type]->IsSoundPlaying();
}

void Sound::StopAll()
{
	for (auto& x : _ArrSound)
	{
		if (x.second->IsSoundPlaying())
			x.second->Stop();
	}
}


void Sound::AddSound(eSound type, LPTSTR filename)
{
	CSound* wave;
	HRESULT result = dsound->Create(&wave, filename);
	if (result != DS_OK)
	{
		DebugOut(L"[SOUND] Load Sound that bai. eSound = %d \n", (int)type);
		return;
	}
	_ArrSound[type] = wave;
}

void Sound::Play(eSound type, bool isLoop, LONG lVolume)
{
	_ArrSound[type]->Play(0, isLoop, lVolume);
	//DSBPLAY_LOOPING             0x00000001 -> int = 1

}

void Sound::Stop(eSound type)
{
	_ArrSound[type]->Stop();
}



void Sound::Init()
{
	dsound = new CSoundManager();
	dsound->Initialize(Game::GetInstance()->GetWindowHandle(), DSSCL_PRIORITY);
	dsound->SetPrimaryBufferFormat(2, 22050, 16);
}

Sound* Sound::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Sound();
	return __Instance;
}