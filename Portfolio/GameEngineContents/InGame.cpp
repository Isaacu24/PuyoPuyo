﻿#include "InGame.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "FadeInOutBackground.h"
#include "InGameActor.h"
#include "Puyo.h"
#include "EnemyFSM.h"
#include "ContentsEnum.h"
#include "EnemySelect.h"
#include "GameOver.h"
#include "Player.h"
#include "EnemyProfile.h"
#include <vector>

InGame::InGame()
	: Stages_{ }
	, StageRenderer_(nullptr)
	, StateBottoms_{nullptr}
	, GameTime_(0.f)
	, Player_(nullptr)
	, EnemyFSM_(nullptr)
	, EnemyProfile_(nullptr)
	, Stage_(nullptr)
	, StageClear_(0)
	, TwinkleCount_(0)
	, ChangeCount_(10.f)
	, BonusPoint_(0)
	, StagePoint_(0)
	, RestPoint_(0)
	, IsStart_(false)
	, IsSpewStar_(false)
	, IsStarUpdate_(false)
	, IsTwinkleOn_(false)
{
}

InGame::~InGame()
{

}

void InGame::Loading()
{	
	if (false == GameEngineInput::GetInst()->IsKey("Rest"))
	{
		GameEngineInput::GetInst()->CreateKey("Rest", VK_ESCAPE);
	}
}

void InGame::InitPlayerEndEnemy()
{
	Player_ = CreateActor<Player>(10);
	Player_->SetPosition({ 95, 748 });

	EnemyFSM_ = CreateActor<EnemyFSM>(10);
	EnemyFSM_->SetPosition({ 860, 748 });

	Player_->SetEnemyFSM(EnemyFSM_);
	EnemyFSM_->SetPlayer(Player_);
}

void InGame::PuyoAnimationInit()
{
	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_RED_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_RED_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_RED_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_RED_LAND.bmp");
		LandImage->CutCount(4, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_RED_IDLE.bmp");
		IdleImage->CutCount(3, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_RED_IDLE1.bmp");
		IdleImage1->CutCount(6, 1);



		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_RED_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_RED_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_RED_DOWN.bmp");
		DownImage->CutCount(1, 1);



		GameEngineImage* LefeDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_DOWN.bmp");
		LefeDownImage->CutCount(1, 1);

		GameEngineImage* LefeUpImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_UP.bmp");
		LefeUpImage->CutCount(1, 1);

		GameEngineImage* LefeRightImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_RIGHT.bmp");
		LefeRightImage->CutCount(1, 1);

		GameEngineImage* LeftRightDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_RIGHT_DOWN.bmp");
		LeftRightDownImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_RIGHT_UP.bmp");
		LeftRightUpImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_RIGHT_UP_DOWN.bmp");
		LeftRightUpDownImage->CutCount(1, 1);

		GameEngineImage* LeftUpDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_UP_DOWN.bmp");
		LeftUpDownImage->CutCount(1, 1);

		GameEngineImage* RightDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_RIGHT_DOWN.bmp");
		RightDownImage->CutCount(1, 1);

		GameEngineImage* RightUPDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_RIGHT_UP_DOWN.bmp");
		RightUPDownImage->CutCount(1, 1);

		GameEngineImage* RightUPImage = GameEngineImageManager::GetInst()->Find("IG_RED_RIGHT_UP.bmp");
		RightUPImage->CutCount(1, 1);

		GameEngineImage* UpDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_UP_DOWN.bmp");
		UpDownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LAND.bmp");
		LandImage->CutCount(4, 1);


		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_IDLE.bmp");
		IdleImage->CutCount(6, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_BLUE_IDLE1.bmp");
		IdleImage1->CutCount(8, 1);

		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_DOWN.bmp");
		DownImage->CutCount(1, 1);



		GameEngineImage* LefeDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_DOWN.bmp");
		LefeDownImage->CutCount(1, 1);

		GameEngineImage* LefeUpImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_UP.bmp");
		LefeUpImage->CutCount(1, 1);

		GameEngineImage* LefeRightImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_RIGHT.bmp");
		LefeRightImage->CutCount(1, 1);

		GameEngineImage* LeftRightDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_RIGHT_DOWN.bmp");
		LeftRightDownImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_RIGHT_UP.bmp");
		LeftRightUpImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_RIGHT_UP_DOWN.bmp");
		LeftRightUpDownImage->CutCount(1, 1);

		GameEngineImage* LeftUpDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_UP_DOWN.bmp");
		LeftUpDownImage->CutCount(1, 1);

		GameEngineImage* RightDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_RIGHT_DOWN.bmp");
		RightDownImage->CutCount(1, 1);

		GameEngineImage* RightUPDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_RIGHT_UP_DOWN.bmp");
		RightUPDownImage->CutCount(1, 1);

		GameEngineImage* RightUPImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_RIGHT_UP.bmp");
		RightUPImage->CutCount(1, 1);

		GameEngineImage* UpDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_UP_DOWN.bmp");
		UpDownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LAND.bmp");
		LandImage->CutCount(4, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_IDLE.bmp");
		IdleImage->CutCount(8, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_GREEN_IDLE1.bmp");
		IdleImage1->CutCount(8, 1);



		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_DOWN.bmp");
		DownImage->CutCount(1, 1);


		GameEngineImage* LefeDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_DOWN.bmp");
		LefeDownImage->CutCount(1, 1);

		GameEngineImage* LefeUpImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_UP.bmp");
		LefeUpImage->CutCount(1, 1);

		GameEngineImage* LefeRightImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_RIGHT.bmp");
		LefeRightImage->CutCount(1, 1);

		GameEngineImage* LeftRightDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_RIGHT_DOWN.bmp");
		LeftRightDownImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_RIGHT_UP.bmp");
		LeftRightUpImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_RIGHT_UP_DOWN.bmp");
		LeftRightUpDownImage->CutCount(1, 1);

		GameEngineImage* LeftUpDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_UP_DOWN.bmp");
		LeftUpDownImage->CutCount(1, 1);

		GameEngineImage* RightDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_RIGHT_DOWN.bmp");
		RightDownImage->CutCount(1, 1);

		GameEngineImage* RightUPDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_RIGHT_UP_DOWN.bmp");
		RightUPDownImage->CutCount(1, 1);

		GameEngineImage* RightUPImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_RIGHT_UP.bmp");
		RightUPImage->CutCount(1, 1);

		GameEngineImage* UpDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_UP_DOWN.bmp");
		UpDownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LAND.bmp");
		LandImage->CutCount(4, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_IDLE.bmp");
		IdleImage->CutCount(8, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_YELLOW_IDLE1.bmp");
		IdleImage1->CutCount(3, 1);



		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_DOWN.bmp");
		DownImage->CutCount(1, 1);


		GameEngineImage* LefeDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_DOWN.bmp");
		LefeDownImage->CutCount(1, 1);

		GameEngineImage* LefeUpImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_UP.bmp");
		LefeUpImage->CutCount(1, 1);

		GameEngineImage* LefeRightImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_RIGHT.bmp");
		LefeRightImage->CutCount(1, 1);

		GameEngineImage* LeftRightDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_RIGHT_DOWN.bmp");
		LeftRightDownImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_RIGHT_UP.bmp");
		LeftRightUpImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_RIGHT_UP_DOWN.bmp");
		LeftRightUpDownImage->CutCount(1, 1);

		GameEngineImage* LeftUpDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_UP_DOWN.bmp");
		LeftUpDownImage->CutCount(1, 1);

		GameEngineImage* RightDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_RIGHT_DOWN.bmp");
		RightDownImage->CutCount(1, 1);

		GameEngineImage* RightUPDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_RIGHT_UP_DOWN.bmp");
		RightUPDownImage->CutCount(1, 1);

		GameEngineImage* RightUPImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_RIGHT_UP.bmp");
		RightUPImage->CutCount(1, 1);

		GameEngineImage* UpDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_UP_DOWN.bmp");
		UpDownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LAND.bmp");
		LandImage->CutCount(4, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_IDLE.bmp");
		IdleImage->CutCount(5, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_PURPLE_IDLE1.bmp");
		IdleImage1->CutCount(5, 1);


		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_DOWN.bmp");
		DownImage->CutCount(1, 1);



		GameEngineImage* LefeDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_DOWN.bmp");
		LefeDownImage->CutCount(1, 1);

		GameEngineImage* LefeUpImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_UP.bmp");
		LefeUpImage->CutCount(1, 1);

		GameEngineImage* LefeRightImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_RIGHT.bmp");
		LefeRightImage->CutCount(1, 1);

		GameEngineImage* LeftRightDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_RIGHT_DOWN.bmp");
		LeftRightDownImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_RIGHT_UP.bmp");
		LeftRightUpImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_RIGHT_UP_DOWN.bmp");
		LeftRightUpDownImage->CutCount(1, 1);

		GameEngineImage* LeftUpDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_UP_DOWN.bmp");
		LeftUpDownImage->CutCount(1, 1);

		GameEngineImage* RightDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_RIGHT_DOWN.bmp");
		RightDownImage->CutCount(1, 1);

		GameEngineImage* RightUPDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_RIGHT_UP_DOWN.bmp");
		RightUPDownImage->CutCount(1, 1);

		GameEngineImage* RightUPImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_RIGHT_UP.bmp");
		RightUPImage->CutCount(1, 1);

		GameEngineImage* UpDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_UP_DOWN.bmp");
		UpDownImage->CutCount(1, 1);
	}

	GameEngineImage* HindrancePuyo = GameEngineImageManager::GetInst()->Find("IG_HINDRANCE_PUYO.bmp");
	HindrancePuyo->CutCount(1, 1);

	GameEngineImage* HindranceDestroy = GameEngineImageManager::GetInst()->Find("IG_HINDRANCE_PUYO_DESTROY.bmp");
	HindranceDestroy->CutCount(4, 1);

	GameEngineImage* HindranceIdle = GameEngineImageManager::GetInst()->Find("IG_HINDRANCE_PUYO_IDLE.bmp");
	HindranceIdle->CutCount(3, 1);

	GameEngineImage* OffsetStarImage = GameEngineImageManager::GetInst()->Find("IG_OffsetStar.bmp");
	OffsetStarImage->CutCount(5, 1);


	//이펙트
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_RED_EFFECT.bmp");
		Image->CutCount(6, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_BLUE_EFFECT.bmp");
		Image1->CutCount(6, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_GREEN_EFFECT.bmp");
		Image2->CutCount(6, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_YELLOW_EFFECT.bmp");
		Image3->CutCount(6, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_PURPLE_EFFECT.bmp");
		Image4->CutCount(6, 1);
	}
}

void InGame::EnemyAnimatioInit()
{
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV1_IDLE.bmp");
		Image->CutCount(4, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV1_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV1_EXCITED.bmp");
		Image2->CutCount(6, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV1_WIN.bmp");
		Image3->CutCount(1, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV1_DANGER.bmp");
		Image4->CutCount(4, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV2_IDLE.bmp");
		Image->CutCount(1, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV2_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV2_EXCITED.bmp");
		Image2->CutCount(1, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV2_WIN.bmp");
		Image3->CutCount(1, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV2_DANGER.bmp");
		Image4->CutCount(1, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV3_IDLE.bmp");
		Image->CutCount(4, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV3_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV3_EXCITED.bmp");
		Image2->CutCount(4, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV3_WIN.bmp");
		Image3->CutCount(2, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV3_DANGER.bmp");
		Image4->CutCount(4, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV4_IDLE.bmp");
		Image->CutCount(4, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV4_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV4_WIN.bmp");
		Image2->CutCount(1, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV4_EXCITED.bmp");
		Image3->CutCount(4, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV4_DANGER.bmp");
		Image4->CutCount(4, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV5_IDLE.bmp");
		Image->CutCount(4, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV5_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV5_WIN.bmp");
		Image2->CutCount(7, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV5_EXCITED.bmp");
		Image3->CutCount(5, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV5_DANGER.bmp");
		Image4->CutCount(4, 1);

	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV6_IDLE.bmp");
		Image->CutCount(4, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV6_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV6_WIN.bmp");
		Image2->CutCount(4, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV6_EXCITED.bmp");
		Image3->CutCount(4, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV6_DANGER.bmp");
		Image4->CutCount(4, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV7_IDLE.bmp");
		Image->CutCount(5, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV7_LOSE.bmp");
		Image1->CutCount(1, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV7_WIN.bmp");
		Image2->CutCount(4, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV7_DANGER.bmp");
		Image3->CutCount(4, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV7_EXCITED.bmp");
		Image4->CutCount(4, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV8_IDLE.bmp");
		Image->CutCount(4, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV8_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV8_WIN.bmp");
		Image2->CutCount(3, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV8_EXCITED.bmp");
		Image3->CutCount(3, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV8_DANGER.bmp");
		Image4->CutCount(4, 1);
	}
}

void InGame::CarbuncleAnimationInit()
{
	Carbuncle_ = CreateActor<InGameActor>(6);
	Carbuncle_->SetPosition({ GameEngineWindow::GetScale().Half().x - 160.f, GameEngineWindow::GetScale().Half().y + 300.f });
	GameEngineRenderer* CarbuncleRenderer = Carbuncle_->CreateRenderer();
	Carbuncle_->SetMyRenderer(CarbuncleRenderer);

	GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_CARBUNCLE_IDLE.bmp");
	IdleImage->CutCount(2, 1);

	GameEngineImage* StartImage = GameEngineImageManager::GetInst()->Find("IG_CARBUNCLE_START.bmp");
	StartImage->CutCount(9, 1);

	GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_CARBUNCLE_IDLE1.bmp");
	IdleImage1->CutCount(8, 1);

	GameEngineImage* IdleImage2 = GameEngineImageManager::GetInst()->Find("IG_CARBUNCLE_IDLE2.bmp");
	IdleImage2->CutCount(10, 1);


	Carbuncle_->GetMyRenderer()->CreateAnimation("IG_CARBUNCLE_IDLE.bmp", "IG_CARBUNCLE_IDLE", 0, 1, 0.1f, true);
	Carbuncle_->GetMyRenderer()->CreateAnimation("IG_CARBUNCLE_START.bmp", "IG_CARBUNCLE_START", 0, 8, 0.2f, false);
	Carbuncle_->GetMyRenderer()->CreateAnimation("IG_CARBUNCLE_IDLE1.bmp", "IG_CARBUNCLE_IDLE1", 0, 7, 0.2f, false);
	Carbuncle_->GetMyRenderer()->CreateAnimation("IG_CARBUNCLE_IDLE2.bmp", "IG_CARBUNCLE_IDLE2", 0, 9, 0.2f, false);
	Carbuncle_->GetMyRenderer()->ChangeAnimation("IG_CARBUNCLE_IDLE");

	for (size_t i = 0; i < 36; i++)
	{
		Stars_[i] = CreateActor<InGameActor>(0);
		Stars_[i]->SetPosition(Carbuncle_->GetPosition());
		Stars_[i]->SetMyRenderer(Stars_[i]->CreateRenderer("IG_CARBUNCLE_STAR.bmp"));
	}
}

void InGame::ActorsInit()
{
	FadeBackground_ = CreateActor<FadeInOutBackground>();

	Stages_[0] = CreateActor<Stage>();

	Stages_[0]->SetPosition(GameEngineWindow::GetScale().Half());
	Stages_[0]->CreateRenderer("IG_STAGE1.bmp", 3);
	Stages_[0]->CreateRenderer("IG_STAGE1_BACK.bmp", 0);

	StateBottoms_[0] = CreateActor<InGameActor>();
	StateBottoms_[1] = CreateActor<InGameActor>();
	StateBottoms_[0]->SetMyRenderer(StateBottoms_[0]->CreateRenderer("IG_STAGE1_BOTTOM_LEFT.bmp", 3));
	StateBottoms_[1]->SetMyRenderer(StateBottoms_[1]->CreateRenderer("IG_STAGE1_BOTTOM_RIGHT.bmp", 3));

	StateBottoms_[0]->SetPosition({ GameEngineWindow::GetScale().Half() + float4{-384, 389} });
	StateBottoms_[1]->SetPosition({ GameEngineWindow::GetScale().Half() + float4{384, 389} });

	GameEngineActor* NextUI = CreateActor<Stage>(3);
	NextUI->CreateRenderer("IG_NEXT.bmp")->SetPivot({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 360.f });

	StageRenderer_ = CreateActor<InGameActor>(15);
	StageRenderer_->SetPosition({ GameEngineWindow::GetScale().Half() + float4{0, 250.f } });
	StageRenderer_->SetMyRenderer(StageRenderer_->CreateRenderer("IG_STAGE_UI.bmp"));

	StageRenderStartPos_ = StageRenderer_->GetPosition();
	StageRenderEndPos_ = { GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 60.f };
}


void InGame::Update()
{
	if (false == IsRest_)
	{
		GameTime_ += GameEngineTime::GetDeltaTime();
	}

	if (false == IsStart_)
	{
		Player_->BehindPlayer();
		EnemyFSM_->BehindEnemy();

		Alpha_ += GameEngineTime::GetDeltaTime() * 2.f;

		StageRenderer_->SetPosition(float4::Lerp(StageRenderStartPos_, StageRenderEndPos_, Alpha_));

		if (1.f <= Alpha_)
		{
			Alpha_ = 0.f;

			Player_->FrontPlayer();
			EnemyFSM_->FrontEnemy();
			StageRenderer_->GetMyRenderer()->SetOrder(3);
			IsStart_ = true;
		}
	}

	if (true == IsStart_)
	{
		if (false == IsSpewStar_
			&& false == IsStarUpdate_)
		{
			CarbuncleUpdate();
		}

		if (true == IsSpewStar_
			&& false == IsStarUpdate_)
		{
			SpewStar();
		}

		GameOverCheck();
	}

	RestCheck();
}

void InGame::GameOverCheck()
{
	if (PlayerState::Lose == Player_->GetCurrentState())
	{
		PlayerLose();
		EnemyFSM_->SetCurrentState(EnemyState::Win);

		InGameBgm_.Stop();
		StateBottoms_[0]->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 300.f);
		ChangeCount_ -= GameEngineTime::GetDeltaTime();

		if (0 >= ChangeCount_)
		{
			FadeBackground_->FadeInOn();
			FadeBackground_->GetMyRenderer()->SetOrder(20);
			FadeBackground_->SetFadeSpeed(500.f);
		}

		if (true == FadeBackground_->GetIsInChange())
		{
			ChangeCount_ = 7.f;

			GameEngine::GetInst().ChangeLevel("GameOver");

			GameEngineLevel* NextLevel = GameEngine::GetNextLevel();
			GameOver* GameOver_ = dynamic_cast<GameOver*>(NextLevel);

			GameOver_->SetEnemyProfile(EnemyProfile_);
		}
	}

	else if (EnemyState::Lose == EnemyFSM_->GetCurrentState())
	{
		TwinklePlayerWin();
		ResultScore();
		Player_->SetCurrentState(PlayerState::Win);

		InGameBgm_.Stop();
		ChangeCount_ -= GameEngineTime::GetDeltaTime();
		StateBottoms_[1]->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 300.f);

		if (0 >= ChangeCount_)
		{
			FadeBackground_->FadeInOn();
			FadeBackground_->GetMyRenderer()->SetOrder(20);
			FadeBackground_->SetFadeSpeed(500.f);
		}

		if (true == FadeBackground_->GetIsInChange())
		{
			ChangeCount_ = 7.f;
			GameEngine::GetInst().ChangeLevel("EnemySelect");

			GameEngineLevel* NextLevel = GameEngine::GetNextLevel();
			EnemySelect* EnemySelect_ = dynamic_cast<EnemySelect*>(NextLevel);

			if (nullptr != EnemyProfile_)
			{
				EnemySelect_->LockLoseEnemyIcon(EnemyProfile_->GetMyLevel());

				EnemySelect_->RenderPlayerExp(Player_->GetNext());
				EnemySelect_->RenderPlayerNext(Player_->GetNext() + 1);
				EnemySelect_->RenderPlayerRest(Player_->GetRest());
			}
		}
	}
}


void InGame::TwinklePlayerWin()
{
	TwinkleTime_ += GameEngineTime::GetDeltaTime();

	if (0.5f <= TwinkleTime_ && false == IsTwinkleOn_)
	{
		IsTwinkleOn_ = true;
		PlayerWin_->GetMyRenderer()->SetOrder(10);
	}

	else if (1.5f <= TwinkleTime_ && true == IsTwinkleOn_)
	{
		TwinkleTime_ = 0.f;
		IsTwinkleOn_ = false;
		PlayerWin_->GetMyRenderer()->SetOrder(-1);
	}
}

void InGame::TwinklePlayerGameOver()
{
	TwinkleTime_ += GameEngineTime::GetDeltaTime();

	if (0.25f <= TwinkleTime_ && false == IsTwinkleOn_)
	{
		IsTwinkleOn_ = true;
		PlayerGameOver_->GetMyRenderer()->SetImage("IG_PLAYER_GAMEOVER.bmp");
	}

	else if (0.5f <= TwinkleTime_ && true == IsTwinkleOn_)
	{
		TwinkleTime_ = 0.f;
		IsTwinkleOn_ = false;
		PlayerGameOver_->GetMyRenderer()->SetImage("IG_ENEMY_GAMEOVER.bmp");
	}
}

void InGame::ResultScore()
{
	WinWaitTime_ += GameEngineTime::GetDeltaTime();

	if (0.5f <= WinWaitTime_
		&& 0 == ResultCount_)
	{
		WinWaitTime_ = 0.f;
		++ResultCount_;
		SDPlayer_->GetMyRenderer()->SetOrder(15);
	}

	if (0.5f <= WinWaitTime_
		&& 1 == ResultCount_)
	{
		WinWaitTime_ = 0.f;
		++ResultCount_;
		GameEngineRenderer* PlayTime = SDPlayer_->CreateRenderer("IG_PLAYTIME.bmp");
		GameEngineRenderer* PlayTimeSec = SDPlayer_->CreateRenderer("IG_SEC.bmp");

		PlayTime->SetPivot({ -20, -410 });
		PlayTimeSec->SetPivot({ 120, -330 });
		PlayTime->SetOrder(20);
		PlayTimeSec->SetOrder(20);

		RenderTime();
	}

	if (0.5f <= WinWaitTime_
		&& 2 == ResultCount_)
	{
		WinWaitTime_ = 0.f;
		++ResultCount_;
		GameEngineRenderer* Bonus = SDPlayer_->CreateRenderer("IG_BONUS.bmp");
		GameEngineRenderer* BonusPts = SDPlayer_->CreateRenderer("IG_PTS.bmp");

		Bonus->SetPivot({ -90, -265 });
		BonusPts->SetPivot({ 115, -175 });
		Bonus->SetOrder(20);
		BonusPts->SetOrder(20);

		BonusPoint_ = 300;
		RenderBonusPoint(BonusPoint_);
	}

	if (3 == ResultCount_ 
		&& 0 < BonusPoint_)
	{
		--BonusPoint_;
		Player_->PlusScore(2);
		RenderBonusPoint(BonusPoint_);

		Alpha_ += GameEngineTime::GetDeltaTime();

		if (0 == BonusPoint_)
		{
			++ResultCount_;
		}
	}

	if (0.5f <= WinWaitTime_
		&& 4 == ResultCount_)
	{
		++ResultCount_;
		WinWaitTime_ = 0.f;
		GameEngineRenderer* Stage = SDPlayer_->CreateRenderer("IG_STAGE.bmp");
		GameEngineRenderer* Point = SDPlayer_->CreateRenderer("IG_POINT.bmp");
		GameEngineRenderer* StagePts = SDPlayer_->CreateRenderer("IG_PTS.bmp");

		Stage->SetPivot({ 725, -530 });
		Point->SetPivot({ 850, -470 });
		StagePts->SetPivot({ 885, -390 });
		Stage->SetOrder(20);
		Point->SetOrder(20);
		StagePts->SetOrder(20);
	}

	if (5 == ResultCount_ 
		&& Player_->GetScore() > StagePoint_)
	{
		++StagePoint_;

		if (500 < Player_->GetScore())
		{
			StagePoint_ += 10;
		}

		RenderStagePoint(StagePoint_);

		if (Player_->GetScore() <= StagePoint_)
		{
			++ResultCount_;
			Player_->SetNext(Player_->GetNext() + StagePoint_);
		}
	}

	if (0.5f <= WinWaitTime_
		&& 6 == ResultCount_)
	{
		++ResultCount_;
		WinWaitTime_ = 0.f;
		GameEngineRenderer* Rest = SDPlayer_->CreateRenderer("IG_REST.bmp");
		GameEngineRenderer* Point = SDPlayer_->CreateRenderer("IG_POINT.bmp");
		GameEngineRenderer* RestPts = SDPlayer_->CreateRenderer("IG_PTS.bmp");

		Rest->SetPivot({ 705, -330 });
		Point->SetPivot({ 855, -270 });
		RestPts->SetPivot({ 885, -175 });
		Rest->SetOrder(20);
		Point->SetOrder(20);
		RestPts->SetOrder(20);
	}

	if (7 == ResultCount_
		&& 300 > RestPoint_)
	{
		++RestPoint_;
		RenderRestPoint(RestPoint_);

		if (300 <= RestPoint_)
		{
			++ResultCount_;
			Player_->SetRest(Player_->GetRest() + RestPoint_);

			RestActor_->Death();
			RestActor_ = nullptr;

			RestActor_ = CreateActor<InGameActor>();
			RestActor_->SetPosition({ 255, 670 });

			RestActor_->SetMyRenderer(RestActor_->CreateRenderer("IG_CLEAR_PLAYER.bmp"));
			RestActor_->GetMyRenderer()->SetPivot({ 740.f, -190.f });
			GameEngineRenderer* LevelUpRenderer  = RestActor_->CreateRenderer("IG_LEVELUP.bmp");
			LevelUpRenderer->SetPivot({ 780.f, 0.f });
		}
	}

	if (0.2f <= WinWaitTime_
		&& 8 == ResultCount_)
	{
		WinWaitTime_ = 0.f;
		++ResultCount_;

		RestActor_->GetMyRenderer()->SetImage("IG_CLEAR_ENEMY.bmp");
	}


	if (0.2f <= WinWaitTime_
		&& 9 == ResultCount_)
	{
		WinWaitTime_ = 0.f;
		--ResultCount_;

		RestActor_->GetMyRenderer()->SetImage("IG_CLEAR_PLAYER.bmp");
	}
}

void InGame::PlayerLose()
{
	GameOverAlpha_ += GameEngineTime::GetDeltaTime() * 0.5f;

	if (1.f <= GameOverAlpha_)
	{
		GameOverAlpha_ = 1.f;
	}

	PlayerGameOver_->GetMyRenderer()->SetOrder(10);
	PlayerGameOver_->SetPosition(float4::Lerp(GameOverStartPos_, GameOverEndPos_, GameOverAlpha_));

	TwinklePlayerGameOver();
}

void InGame::RenderTime()
{
	std::vector<int> TimeDigits_;
	int Temp = GameTime_;

	if (0 == Temp)
	{
		GameEngineRenderer* Renderer = SDPlayer_->CreateRenderer("IG_PLAYER_NUMBER_0.bmp");
		Renderer->SetPivot({ 350.f, 320.f });
		Renderer->SetOrder(20);
	}

	while (0 < Temp)
	{
		TimeDigits_.push_back(Temp % 10);
		Temp /= 10;
	}

	for (int i = 0; i < TimeDigits_.size(); i++)
	{
		switch (TimeDigits_[i])
		{
		case 0:
		{
			GameEngineRenderer* Renderer = SDPlayer_->CreateRenderer("IG_PLAYER_NUMBER_0.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -343 });
			Renderer->SetOrder(20);
		}
		break;
		case 1:
		{
			GameEngineRenderer* Renderer = SDPlayer_->CreateRenderer("IG_PLAYER_NUMBER_1.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -343 });
			Renderer->SetOrder(20);
		}
		break;
		case 2:
		{
			GameEngineRenderer* Renderer = SDPlayer_->CreateRenderer("IG_PLAYER_NUMBER_2.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -343 });
			Renderer->SetOrder(20);
		}
		break;
		case 3:
		{
			GameEngineRenderer* Renderer = SDPlayer_->CreateRenderer("IG_PLAYER_NUMBER_3.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -343 });
			Renderer->SetOrder(20);
		}
		break;
		case 4:
		{
			GameEngineRenderer* Renderer = SDPlayer_->CreateRenderer("IG_PLAYER_NUMBER_4.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -343 });
			Renderer->SetOrder(20);
		}
		break;
		case 5:
		{
			GameEngineRenderer* Renderer = SDPlayer_->CreateRenderer("IG_PLAYER_NUMBER_5.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -343 });
			Renderer->SetOrder(20);
		}

		break;
		case 6:
		{
			GameEngineRenderer* Renderer = SDPlayer_->CreateRenderer("IG_PLAYER_NUMBER_6.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -343 });
			Renderer->SetOrder(20);
		}
		break;
		case 7:
		{
			GameEngineRenderer* Renderer = SDPlayer_->CreateRenderer("IG_PLAYER_NUMBER_7.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -343 });
			Renderer->SetOrder(20);
		}
		break;
		case 8:
		{
			GameEngineRenderer* Renderer = SDPlayer_->CreateRenderer("IG_PLAYER_NUMBER_8.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -343 });
			Renderer->SetOrder(20);
		}
		break;
		case 9:
		{
			GameEngineRenderer* Renderer = SDPlayer_->CreateRenderer("IG_PLAYER_NUMBER_9.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -343 });
			Renderer->SetOrder(20);
		}
		break;
		}
	}
}

void InGame::RenderBonusPoint(int _Value)
{
	BonusActor_->Death();
	BonusActor_ = nullptr;

	BonusActor_ = CreateActor<InGameActor>();
	BonusActor_->SetPosition({ 255, 670 });

	std::vector<int> TimeDigits_;
	int Temp = _Value;

	if (0 == Temp)
	{
		GameEngineRenderer* Renderer = BonusActor_->CreateRenderer("IG_PLAYER_NUMBER_0.bmp");
		Renderer->SetPivot({ 40.f, -190 });
		Renderer->SetOrder(20);
	}

	while (0 < Temp)
	{
		TimeDigits_.push_back(Temp % 10);
		Temp /= 10;
	}

	for (int i = 0; i < TimeDigits_.size(); i++)
	{
		switch (TimeDigits_[i])
		{
		case 0:
		{
			GameEngineRenderer* Renderer = BonusActor_->CreateRenderer("IG_PLAYER_NUMBER_0.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		case 1:
		{
			GameEngineRenderer* Renderer = BonusActor_->CreateRenderer("IG_PLAYER_NUMBER_1.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		case 2:
		{
			GameEngineRenderer* Renderer = BonusActor_->CreateRenderer("IG_PLAYER_NUMBER_2.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		case 3:
		{
			GameEngineRenderer* Renderer = BonusActor_->CreateRenderer("IG_PLAYER_NUMBER_3.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		case 4:
		{
			GameEngineRenderer* Renderer = BonusActor_->CreateRenderer("IG_PLAYER_NUMBER_4.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}

		break;
		case 5:
		{
			GameEngineRenderer* Renderer = BonusActor_->CreateRenderer("IG_PLAYER_NUMBER_5.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}

		break;
		case 6:
		{
			GameEngineRenderer* Renderer = BonusActor_->CreateRenderer("IG_PLAYER_NUMBER_6.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}

		break;
		case 7:
		{
			GameEngineRenderer* Renderer = BonusActor_->CreateRenderer("IG_PLAYER_NUMBER_7.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		case 8:
		{
			GameEngineRenderer* Renderer = BonusActor_->CreateRenderer("IG_PLAYER_NUMBER_8.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		case 9:
		{
			GameEngineRenderer* Renderer = BonusActor_->CreateRenderer("IG_PLAYER_NUMBER_9.bmp");
			Renderer->SetPivot({ 40.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		}
	}
}

void InGame::RenderStagePoint(int _Value)
{
	StageActor_->Death();
	StageActor_= nullptr;

	StageActor_ = CreateActor<InGameActor>();
	StageActor_->SetPosition({ 255, 670 });

	std::vector<int> TimeDigits_;
	int Temp = _Value;

	if (0 == Temp)
	{
		GameEngineRenderer* Renderer = StageActor_->CreateRenderer("IG_PLAYER_NUMBER_0.bmp");
		Renderer->SetPivot({ 810.f, -400 });
		Renderer->SetOrder(20);
	}

	while (0 < Temp)
	{
		TimeDigits_.push_back(Temp % 10);
		Temp /= 10;
	}

	for (int i = 0; i < TimeDigits_.size(); i++)
	{
		switch (TimeDigits_[i])
		{
		case 0:
		{
			GameEngineRenderer* Renderer = StageActor_->CreateRenderer("IG_PLAYER_NUMBER_0.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -400 });
			Renderer->SetOrder(20);
		}
		break;
		case 1:
		{
			GameEngineRenderer* Renderer = StageActor_->CreateRenderer("IG_PLAYER_NUMBER_1.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -400 });
			Renderer->SetOrder(20);
		}
		break;
		case 2:
		{
			GameEngineRenderer* Renderer = StageActor_->CreateRenderer("IG_PLAYER_NUMBER_2.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -400 });
			Renderer->SetOrder(20);
		}
		break;
		case 3:
		{
			GameEngineRenderer* Renderer = StageActor_->CreateRenderer("IG_PLAYER_NUMBER_3.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -400 });
			Renderer->SetOrder(20);
		}
		break;
		case 4:
		{
			GameEngineRenderer* Renderer = StageActor_->CreateRenderer("IG_PLAYER_NUMBER_4.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -400 });
			Renderer->SetOrder(20);
		}

		break;
		case 5:
		{
			GameEngineRenderer* Renderer = StageActor_->CreateRenderer("IG_PLAYER_NUMBER_5.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -400 });
			Renderer->SetOrder(20);
		}

		break;
		case 6:
		{
			GameEngineRenderer* Renderer = StageActor_->CreateRenderer("IG_PLAYER_NUMBER_6.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -400 });
			Renderer->SetOrder(20);
		}

		break;
		case 7:
		{
			GameEngineRenderer* Renderer = StageActor_->CreateRenderer("IG_PLAYER_NUMBER_7.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -400 });
			Renderer->SetOrder(20);
		}
		break;
		case 8:
		{
			GameEngineRenderer* Renderer = StageActor_->CreateRenderer("IG_PLAYER_NUMBER_8.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -400 });
			Renderer->SetOrder(20);
		}
		break;
		case 9:
		{
			GameEngineRenderer* Renderer = StageActor_->CreateRenderer("IG_PLAYER_NUMBER_9.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -400 });
			Renderer->SetOrder(20);
		}
		break;
		}
	}
}

void InGame::RenderRestPoint(int _Value)
{
	RestActor_->Death();
	RestActor_ = nullptr;

	RestActor_ = CreateActor<InGameActor>();
	RestActor_->SetPosition({ 255, 670 });

	std::vector<int> TimeDigits_;
	int Temp = _Value;

	if (0 == Temp)
	{
		GameEngineRenderer* Renderer = RestActor_->CreateRenderer("IG_PLAYER_NUMBER_0.bmp");
		Renderer->SetPivot({ 810.f, -190 });
		Renderer->SetOrder(20);
	}

	while (0 < Temp)
	{
		TimeDigits_.push_back(Temp % 10);
		Temp /= 10;
	}

	for (int i = 0; i < TimeDigits_.size(); i++)
	{
		switch (TimeDigits_[i])
		{
		case 0:
		{
			GameEngineRenderer* Renderer = RestActor_->CreateRenderer("IG_PLAYER_NUMBER_0.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		case 1:
		{
			GameEngineRenderer* Renderer = RestActor_->CreateRenderer("IG_PLAYER_NUMBER_1.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		case 2:
		{
			GameEngineRenderer* Renderer = RestActor_->CreateRenderer("IG_PLAYER_NUMBER_2.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		case 3:
		{
			GameEngineRenderer* Renderer = RestActor_->CreateRenderer("IG_PLAYER_NUMBER_3.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		case 4:
		{
			GameEngineRenderer* Renderer = RestActor_->CreateRenderer("IG_PLAYER_NUMBER_4.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}

		break;
		case 5:
		{
			GameEngineRenderer* Renderer = RestActor_->CreateRenderer("IG_PLAYER_NUMBER_5.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}

		break;
		case 6:
		{
			GameEngineRenderer* Renderer = RestActor_->CreateRenderer("IG_PLAYER_NUMBER_6.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}

		break;
		case 7:
		{
			GameEngineRenderer* Renderer = RestActor_->CreateRenderer("IG_PLAYER_NUMBER_7.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		case 8:
		{
			GameEngineRenderer* Renderer = RestActor_->CreateRenderer("IG_PLAYER_NUMBER_8.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		case 9:
		{
			GameEngineRenderer* Renderer = RestActor_->CreateRenderer("IG_PLAYER_NUMBER_9.bmp");
			Renderer->SetPivot({ 810.f - (35.f * i), -190 });
			Renderer->SetOrder(20);
		}
		break;
		}
	}
}

void InGame::RestCheck()
{
	if (true == GameEngineInput::GetInst()->IsDown("Rest")
		&& false == IsRest_ && true == IsSpewStar_
		&& EnemyState::Lose != EnemyFSM_->GetCurrentState()
		&& PlayerState::Lose != Player_->GetCurrentState())
	{
		IsRest_ = true;

		//휴식 전 상태 기억
		Player_->SetPrevState(Player_->GetCurrentState());
		EnemyFSM_->SetPrevState(EnemyFSM_->GetCurrentState());

		Player_->SetCurrentState(PlayerState::Rest);
		EnemyFSM_->SetCurrentState(EnemyState::Rest);

		Player_->BehindPuyo();
		EnemyFSM_->BehindPuyo();

		TwinkleTime_ = 0.f;

		PlayerRestRenderer_->SetOrder(10);
		EnemyRestRenderer_->SetOrder(10);
	}

	else if (true == GameEngineInput::GetInst()->IsDown("Rest")
		&& true == IsRest_)
	{
		IsRest_ = false;

		Player_->SetCurrentState(Player_->GetPrevState());
		EnemyFSM_->SetCurrentState(EnemyFSM_->GetPrevState());

		Player_->FrontPuyo();
		EnemyFSM_->FrontPuyo();

		PlayerRestRenderer_->SetOrder(-1);
		EnemyRestRenderer_->SetOrder(-1);
	}

	if (true == IsRest_)
	{
		TwinkleRest();
	}
}

void InGame::TwinkleRest()
{
	TwinkleTime_ += GameEngineTime::GetDeltaTime();

	if (0.5f <= TwinkleTime_ && false == IsTwinkleOn_)
	{
		IsTwinkleOn_ = true;
		PlayerRestRenderer_->SetOrder(10);
		EnemyRestRenderer_->SetOrder(10);
	}

	else if (1.5f <= TwinkleTime_ && true == IsTwinkleOn_)
	{
		TwinkleTime_ = 0.f;
		IsTwinkleOn_ = false;
		PlayerRestRenderer_->SetOrder(-1);
		EnemyRestRenderer_->SetOrder(-1);
	}
}

void InGame::CarbuncleUpdate()
{
	Carbuncle_->GetMyRenderer()->ChangeAnimation("IG_CARBUNCLE_START");

	if (true == Carbuncle_->GetMyRenderer()->IsAnimationName("IG_CARBUNCLE_START")
		&& true == Carbuncle_->GetMyRenderer()->IsEndAnimation())
	{
		IsSpewStar_ = true;

		Carbuncle_->GetMyRenderer()->ChangeAnimation("IG_CARBUNCLE_IDLE");
	}
}

void InGame::SpewStar()
{
	if (false == IsStarUpdate_)
	{
		for (int i = 0; i < 36; ++i)
		{
			if (false != Stars_[i]->IsUpdate())
			{
				Stars_[i]->GetMyRenderer()->SetOrder(30);
			}
		}

		float Speed = 1000.f;

		float4 Dir = float4::RadianToDirectionFloat4(0);
		Stars_[0]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(0.2f);
		Stars_[1]->SetMove(Dir * Speed * 1.1f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(0.4f);
		Stars_[2]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(0.6f);
		Stars_[3]->SetMove(Dir * Speed * 1.14f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(GameEngineMath::PIE / 4);
		Stars_[4]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(1.0f);
		Stars_[5]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(1.2f);
		Stars_[6]->SetMove(Dir * Speed * 0.95f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(1.4f);
		Stars_[7]->SetMove(Dir * Speed * 0.99f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(GameEngineMath::PIE / 2);
		Stars_[8]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(1.8f);
		Stars_[9]->SetMove(Dir * Speed * 1.2f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(2.0f);
		Stars_[10]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(2.2f);
		Stars_[11]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4((3 * GameEngineMath::PIE) / 4);
		Stars_[12]->SetMove(Dir * Speed * 0.99f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(2.5f);
		Stars_[13]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(2.8f);
		Stars_[14]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(3.0f);
		Stars_[15]->SetMove(Dir * Speed * 1.1f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(GameEngineMath::PIE);
		Stars_[16]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(3.3f);
		Stars_[17]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(3.5f);
		Stars_[18]->SetMove(Dir * Speed * 0.9f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4((7 * GameEngineMath::PIE) / 6);
		Stars_[19]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(3.8f);
		Stars_[20]->SetMove(Dir * Speed * 0.97f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4((5 * GameEngineMath::PIE) / 4);
		Stars_[21]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(4.1f);
		Stars_[22]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4((4 * GameEngineMath::PIE) / 3);
		Stars_[23]->SetMove(Dir * Speed * 1.12f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(4.4f);
		Stars_[24]->SetMove(Dir * Speed * 0.94f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(4.6f);
		Stars_[25]->SetMove(Dir * Speed * 0.99f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4((3 * GameEngineMath::PIE) / 2);
		Stars_[26]->SetMove(Dir * Speed * 0.9f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(4.9f);
		Stars_[27]->SetMove(Dir * Speed * 1.1f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(5.1f);
		Stars_[28]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4((5 * GameEngineMath::PIE) / 3);
		Stars_[29]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(5.4f);
		Stars_[30]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4((7 * GameEngineMath::PIE) / 4);
		Stars_[31]->SetMove(Dir * Speed * 1.2f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(5.65f);
		Stars_[32]->SetMove(Dir * Speed * 0.89f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4((11 * GameEngineMath::PIE) / 6);
		Stars_[33]->SetMove(Dir * Speed * 1.15f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(5.9f);
		Stars_[34]->SetMove(Dir * Speed * 0.98f * GameEngineTime::GetDeltaTime());

		Dir = float4::RadianToDirectionFloat4(6.1f);
		Stars_[35]->SetMove(Dir * Speed * 1.1f * GameEngineTime::GetDeltaTime());

		int Count = 0;

		for (int i = 0; i < 36; ++i)
		{
			if (GameEngineWindow::GetScale().x < Stars_[i]->GetPosition().x
				&& GameEngineWindow::GetScale().y < Stars_[i]->GetPosition().y)
			{
				Count++;
				Stars_[i]->Off();
			}
		}

		if (36 <= Count)
		{
			IsStarUpdate_ = true;
		}
	}


}



void InGame::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	PuyoAnimationInit();
	InitPlayerEndEnemy();
	EnemyAnimatioInit();
	ActorsInit();
	CarbuncleAnimationInit();

	PlayerGameOver_ = CreateActor<InGameActor>();
	PlayerGameOver_->SetPosition({ 255, 1500 });
	PlayerGameOver_->SetMyRenderer(PlayerGameOver_->CreateRenderer("IG_PLAYER_GAMEOVER.bmp"));

	GameOverStartPos_ = PlayerGameOver_->GetPosition();
	GameOverEndPos_ = PlayerGameOver_->GetPosition() + float4{ 0, -1250.f };

	PlayerWin_ = CreateActor<InGameActor>(-1);
	PlayerWin_->SetPosition({ 255, 150 });
	PlayerWin_->SetMyRenderer(PlayerWin_->CreateRenderer("IG_YOUWIN.bmp"));

	SDPlayer_ = CreateActor<InGameActor>(-1);
	SDPlayer_->SetPosition({ 255, 670 });
	SDPlayer_->SetMyRenderer(SDPlayer_->CreateRenderer("BR_SD_ARLE.bmp"));

	BonusActor_ = CreateActor<InGameActor>(-1);
	BonusActor_->SetPosition({ 255, 670 });
	StageActor_ = CreateActor<InGameActor>(-1);
	StageActor_->SetPosition({ 255, 670 });
	RestActor_ = CreateActor<InGameActor>(-1);
	RestActor_->SetPosition({ 255, 670 });

	PlayerRestRenderer_ = Player_->CreateRenderer("IG_PLAER_REST.bmp");
	PlayerRestRenderer_->SetPivot({ 160, -500 });
	PlayerRestRenderer_->SetOrder(-1);
	EnemyRestRenderer_ = EnemyFSM_->CreateRenderer("IG_ENEMY_REST.bmp");
	EnemyRestRenderer_->SetPivot({ 160, -500 });
	EnemyRestRenderer_->SetOrder(-1);

	InGameBgm_ = GameEngineSound::SoundPlayControl("INGAME.mp3", -1);
	EffectSound_.SoundPlayOneShot("ARLE_START.mp3");

	EnemyFSM_->SetMyProfile(EnemyProfile_);
}

void InGame::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	for (int i = 0; i < 3; i++)
	{
		if (nullptr != Stages_[i])
		{
			Stages_[i]->Death();
			Stages_[i] = nullptr;
		}
	}

	StageRenderer_->Death();
	StageRenderer_ = nullptr;

	StateBottoms_[0]->Death();
	StateBottoms_[1]->Death();

	StateBottoms_[0] = nullptr;
	StateBottoms_[1] = nullptr;

	GameTime_ = 0.f;
	Alpha_ = 0.f;

	StageRenderStartPos_ = float4::ZERO;
	StageRenderEndPos_ = float4::ZERO;

	Carbuncle_->Death();
	Carbuncle_ = nullptr;

	BonusActor_->Death();
	BonusActor_ = nullptr;

	StageActor_->Death();
	BonusActor_ = nullptr;

	RestActor_->Death();
	RestActor_ = nullptr;

	for (int i = 0; i < 36; i++)
	{
		if (nullptr != Stars_[i])
		{
			Stars_[i]->Death();
			Stars_[i] = nullptr;
		}
	}

	FadeBackground_->Death();
	FadeBackground_ = nullptr;

	PlayerGameOver_->Death();
	PlayerGameOver_ = nullptr;
	PlayerWin_->Death();
	PlayerWin_ = nullptr;
	SDPlayer_->Death();
	SDPlayer_ = nullptr;

	GameOverEndPos_ = float4::ZERO;
	GameOverStartPos_ = float4::ZERO;

	PlayerRestRenderer_->Death();
	EnemyRestRenderer_->Death();

	Player_->DestroyPlayer();
	Player_->Death();
	Player_ = nullptr;

	EnemyFSM_->DestroyEnemy();
	EnemyFSM_->Death();
	EnemyFSM_ = nullptr;

	if (nullptr != EnemyProfile_)
	{
		EnemyProfile_->Death();
		EnemyProfile_ = nullptr;
	}

	if (nullptr != Stage_)
	{
		Stage_->Death();
		Stage_ = nullptr;
	}

	ChangeCount_ = 10.f;
	ResultCount_ = 0;

	GameOverAlpha_ = 0.f;

	WinWaitTime_ = 0.f;
	WinWaitTime_ = 0.f;

	BonusPoint_ = 0;
	StagePoint_ = 0;
	RestPoint_ = 0;

	IsStart_ = false;
	IsSpewStar_ = false;
	IsStarUpdate_ = false;
	IsTwinkleOn_ = false;
	IsRest_ = false;
}

