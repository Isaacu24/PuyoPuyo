#include "InGame.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngine.h>
#include "FadeInOutBackground.h"
#include "InGameActor.h"
#include "PuyoPair.h"
#include "Puyo.h"
#include "FSM.h"

InGame::InGame() 
	: Stages_{ }
	, Player_(nullptr)
	, FSM_(nullptr)
	, EnemyProfile_(nullptr)
	, Stage_(nullptr)
	, RandomColor_{}
	, StageClear_(0)
	, LevelCount_(15.f)
	, IsStart_(false) //�ϴ� Ʈ��
{ 
} 

InGame::~InGame()
{ 

}

void InGame::Loading()
{
	PuyoAnimationInit();

	FadeBackground_ = CreateActor<FadeInOutBackground>();

	Stages_[0] = CreateActor<Stage>();
	 
	Stages_[0]->SetPosition(GameEngineWindow::GetScale().Half());
	Stages_[0]->CreateRenderer("IG_STAGE1.bmp", 2);
	Stages_[0]->CreateRenderer("IG_STAGE1_BACK.bmp", 0);

	GameEngineActor* ActorNext = CreateActor<Stage>(3);
	ActorNext->CreateRenderer("IG_NEXT.bmp")->SetPivot({GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 360.f });
	
	GameEngineActor* PlayerName_ = CreateActor<Stage>(1);
	PlayerName_->CreateRenderer("IG_ARLENAME.bmp")->SetPivot({ GameEngineWindow::GetScale().Half().x - 96.f, GameEngineWindow::GetScale().Half().y - 290.f });


	Player_ = CreateActor<Player>();
	FSM_ = CreateActor<FSM>();

	Player_->SetCurrentPair(CreatePuyoPair());
	Player_->SetNextPair(CreatePuyoPair());
	Player_->SetNextNextPair(CreatePuyoPair());

	Player_->CurrentPairInit();

	Carbuncle_ = CreateActor<InGameActor>(6);
	Carbuncle_->SetPosition({ GameEngineWindow::GetScale().Half().x - 160.f, GameEngineWindow::GetScale().Half().y + 300.f });
	GameEngineRenderer* CarbuncleRenderer = Carbuncle_->CreateRenderer();
	Carbuncle_->SetMyRenderer(CarbuncleRenderer);

	//FSM_->CurrentPair_ = CreatePuyoPair();
	//FSM_->NextPair_ = CreatePuyoPair();
	//FSM_->NextNextPair_ = CreatePuyoPair();


	CarbuncleAnimationInit();
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
		LandImage->CutCount(2, 1);
		
		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_RED_IDLE.bmp");
		IdleImage->CutCount(3, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_RED_IDLE1.bmp");
		IdleImage1->CutCount(3, 1);

		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_RED_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_RED_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_RED_DOWN.bmp");
		DownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LAND.bmp");
		LandImage->CutCount(2, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_IDLE.bmp");
		IdleImage->CutCount(3, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_BLUE_IDLE1.bmp");
		IdleImage1->CutCount(3, 1);

		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_DOWN.bmp");
		DownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LAND.bmp");
		LandImage->CutCount(2, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_IDLE.bmp");
		IdleImage->CutCount(4, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_GREEN_IDLE1.bmp");
		IdleImage1->CutCount(4, 1);

		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_DOWN.bmp");
		DownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LAND.bmp");
		LandImage->CutCount(2, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_IDLE.bmp");
		IdleImage->CutCount(4, 1);

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
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LAND.bmp");
		LandImage->CutCount(2, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_IDLE.bmp");
		IdleImage->CutCount(5, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_PURPLE_IDLE1.bmp");
		IdleImage1->CutCount(3, 1);

		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_DOWN.bmp");
		DownImage->CutCount(1, 1);
	}

}

void InGame::CarbuncleAnimationInit()
{
	GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_CARBUNCLE_IDLE.bmp");
	IdleImage->CutCount(2, 1);

	GameEngineImage* StartImage = GameEngineImageManager::GetInst()->Find("IG_CARBUNCLE_START.bmp");
	StartImage->CutCount(9, 1);

	Carbuncle_->GetMyRenderer()->CreateAnimation("IG_CARBUNCLE_IDLE.bmp", "IG_CARBUNCLE_IDLE", 0, 1, 0.1f, true);
	Carbuncle_->GetMyRenderer()->CreateAnimation("IG_CARBUNCLE_START.bmp", "IG_CARBUNCLE_START", 0, 8, 0.2f, false);
	Carbuncle_->GetMyRenderer()->ChangeAnimation("IG_CARBUNCLE_IDLE");


	for (size_t i = 0; i < 36; i++)
	{
		Stars_[i] = CreateActor<InGameActor>(0);
		Stars_[i]->SetPosition(Carbuncle_->GetPosition());
		Stars_[i]->SetMyRenderer(Stars_[i]->CreateRenderer("IG_CARBUNCLE_STAR.bmp"));
	}
}



void InGame::Update()
{
	LevelCount_ -= GameEngineTime::GetDeltaTime();

	if (true == IsStart_ && true == Player_->GetAllLanding() && false == Player_->GetLose())
	{
		Player_->AddPuyoPair(CreatePuyoPair());
	}

	else if (true == Player_->GetAllLanding() && true == Player_->GetLose() && 0 >= LevelCount_)
	{
		FadeBackground_->FadeOn();
		FadeBackground_->GetMyRenderer()->SetOrder(20);
		FadeBackground_->SetFadeSpeed(500.f);

		if (true == FadeBackground_->GetIsChage())
		{
			GameEngine::GetInst().ChangeLevel("GameOver");
			InGameBgm_.Stop();
		}
	}

	CarbuncleUpdate();

	if (true == IsStart_)
	{
		SpewStar();
	}
}

void InGame::CarbuncleUpdate()
{
	if (false == IsStart_)
	{
		Carbuncle_->GetMyRenderer()->ChangeAnimation("IG_CARBUNCLE_START");
	}

	if (true == Carbuncle_->GetMyRenderer()->IsAnimationName("IG_CARBUNCLE_START")
		&& true == Carbuncle_->GetMyRenderer()->IsEndAnimation())
	{
		IsStart_ = true;

		for (int i = 0; i < 36; ++i)
		{
			Stars_[i]->GetMyRenderer()->SetOrder(10);
		}
		Carbuncle_->GetMyRenderer()->ChangeAnimation("IG_CARBUNCLE_IDLE");
	}
}

void InGame::SpewStar()
{
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

	for (int i = 0; i < 35; ++i)
	{
		if (GameEngineWindow::GetScale().x < Stars_[i]->GetPosition().x 
			&& GameEngineWindow::GetScale().y < Stars_[i]->GetPosition().y)
		{
			Stars_[i]->Death();
		}
	}
}


PuyoPair* InGame::CreatePuyoPair()
{
	PuyoPair* NewPuyoPair = CreateActor<PuyoPair>();

	Puyo* CenterPuyo = NewPuyoPair->GetCenterPuyo();
	CenterPuyo = CreateActor<Puyo>(1);
	NewPuyoPair->SetCenterPuyo(CenterPuyo);

	Puyo* ScecondPuyo = NewPuyoPair->GetSecondPuyo();
	ScecondPuyo = CreateActor<Puyo>(1);
	NewPuyoPair->SetSecondPuyo(ScecondPuyo);

	int number = RandomColor_.RandomInt(0, 4);

	switch (number)
	{
	case static_cast<int>(PuyoColor::RED):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer();
			CenterPuyo->SetColor(PuyoColor::RED);
			CenterPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, CenterPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_RED_PUYO");
		}
		break;
	case static_cast<int>(PuyoColor::BLUE):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer();
			CenterPuyo->SetColor(PuyoColor::BLUE);
			CenterPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, CenterPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_BLUE_PUYO");
		}
		break;
	case static_cast<int>(PuyoColor::GREEN):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer();
			CenterPuyo->SetColor(PuyoColor::GREEN);
			CenterPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, CenterPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_GREEN_PUYO");
		}
		break;
	case static_cast<int>(PuyoColor::YELLOW):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer();
			CenterPuyo->SetColor(PuyoColor::YELLOW);
			CenterPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, CenterPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_YELLOW_PUYO");
		}
		break;
	case static_cast<int>(PuyoColor::PURPLE):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer();
			CenterPuyo->SetColor(PuyoColor::PURPLE);
			CenterPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, CenterPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_PURPLE_PUYO");
		}
		break;
	}

	number = RandomColor_.RandomInt(0, 4);

	switch (number)
	{
	case static_cast<int>(PuyoColor::RED):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer();
			ScecondPuyo->SetColor(PuyoColor::RED);
			ScecondPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, ScecondPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_RED_PUYO");
		}
		break;
	case static_cast<int>(PuyoColor::BLUE):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer();
			ScecondPuyo->SetColor(PuyoColor::BLUE);
			ScecondPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, ScecondPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_BLUE_PUYO");
		}
		break;
	case static_cast<int>(PuyoColor::GREEN):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer();
			ScecondPuyo->SetColor(PuyoColor::GREEN);
			ScecondPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, ScecondPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_GREEN_PUYO");
		}
		break;
	case static_cast<int>(PuyoColor::YELLOW):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer();
			ScecondPuyo->SetColor(PuyoColor::YELLOW);
			ScecondPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, ScecondPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_YELLOW_PUYO");
		}
		break;
	case static_cast<int>(PuyoColor::PURPLE):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer();
			ScecondPuyo->SetColor(PuyoColor::PURPLE);
			ScecondPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, ScecondPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_PURPLE_PUYO");
		}
		break;
	}

	if (nullptr == NewPuyoPair)
	{
		return nullptr;
	}

	return NewPuyoPair;
}

Puyo* InGame::CreateHindrancePuyo(GameEngineActor* _FromActor, GameEngineActor* _ToActor)
{
	return nullptr;
}

void InGame::CreatePuyoAnimation(GameEngineRenderer* _Renderer, PuyoColor _Color)
{
	switch (_Color)
	{
	case PuyoColor::RED:
		_Renderer->CreateAnimation("IG_RED_PUYO.bmp", "IG_RED_PUYO", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_CENTER.bmp", "IG_RED_CENTER", 0, 1, 0.1f, true);
		_Renderer->CreateAnimation("IG_RED_LAND.bmp", "IG_RED_LAND", 0, 1, 0.1f, false);
		_Renderer->CreateAnimation("IG_RED_DESTROY.bmp", "IG_RED_DESTROY", 0, 5, 0.1f, false);

		_Renderer->CreateAnimation("IG_RED_LEFT.bmp", "IG_RED_LEFT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_RIGHT.bmp", "IG_RED_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_UP.bmp", "IG_RED_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_DOWN.bmp", "IG_RED_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_RED_LEFT_RIGHT.bmp", "IG_RED_LEFT_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_LEFT_RIGHT_UP.bmp", "IG_RED_LEFT_RIGHT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_LEFT_RIGHT_DOWN.bmp", "IG_RED_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_LEFT_RIGHT_UP_DOWN.bmp", "IG_RED_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_LEFT_UP.bmp", "IG_RED_LEFT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_LEFT_UP_DOWN.bmp", "IG_RED_LEFT_UP_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_LEFT_DOWN.bmp", "IG_RED_LEFT_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_RED_RIGHT_UP.bmp", "IG_RED_RIGHT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_RIGHT_DOWN.bmp", "IG_RED_RIGHT_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_RIGHT_UP_DOW.bmp", "IG_RED_RIGHT_UP_DOW", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_RED_UP_DOWN.bmp", "IG_RED_UP_DOWN", 0, 0, 0.f, false);
		break;
	case PuyoColor::BLUE:
		_Renderer->CreateAnimation("IG_BLUE_PUYO.bmp", "IG_BLUE_PUYO", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_CENTER.bmp", "IG_BLUE_CENTER", 0, 1, 0.1f, true);
		_Renderer->CreateAnimation("IG_BLUE_LAND.bmp", "IG_BLUE_LAND", 0, 1, 0.1f, false);
		_Renderer->CreateAnimation("IG_BLUE_DESTROY.bmp", "IG_BLUE_DESTROY", 0, 5, 0.1f, false);

		_Renderer->CreateAnimation("IG_BLUE_LEFT.bmp", "IG_BLUE_LEFT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_RIGHT.bmp", "IG_BLUE_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_UP.bmp", "IG_BLUE_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_DOWN.bmp", "IG_BLUE_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_BLUE_LEFT_RIGHT.bmp", "IG_BLUE_LEFT_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_LEFT_RIGHT_UP.bmp", "IG_BLUE_LEFT_RIGHT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_LEFT_RIGHT_DOWN.bmp", "IG_BLUE_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_LEFT_RIGHT_UP_DOWN.bmp", "IG_BLUE_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_LEFT_UP.bmp", "IG_BLUE_LEFT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_LEFT_UP_DOWN.bmp", "IG_BLUE_LEFT_UP_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_LEFT_DOWN.bmp", "IG_BLUE_LEFT_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_BLUE_RIGHT_UP.bmp", "IG_BLUE_RIGHT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_RIGHT_DOWN.bmp", "IG_BLUE_RIGHT_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_RIGHT_UP_DOWN.bmp", "IG_BLUE_RIGHT_UP_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_BLUE_UP_DOWN.bmp", "IG_BLUE_UP_DOWN", 0, 0, 0.f, false);
		break;
	case PuyoColor::GREEN:
		_Renderer->CreateAnimation("IG_GREEN_PUYO.bmp", "IG_GREEN_PUYO", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_CENTER.bmp", "IG_GREEN_CENTER", 0, 1, 0.1f, true);
		_Renderer->CreateAnimation("IG_GREEN_LAND.bmp", "IG_GREEN_LAND", 0, 1, 0.1f, false);
		_Renderer->CreateAnimation("IG_GREEN_DESTROY.bmp", "IG_GREEN_DESTROY", 0, 5, 0.1f, false);

		_Renderer->CreateAnimation("IG_GREEN_LEFT.bmp", "IG_GREEN_LEFT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_RIGHT.bmp", "IG_GREEN_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_UP.bmp", "IG_GREEN_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_DOWN.bmp", "IG_GREEN_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_GREEN_LEFT_RIGHT.bmp", "IG_GREEN_LEFT_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_LFET_RIGHT_UP.bmp", "IG_GREEN_LFET_RIGHT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_LEFT_RIGHT_DOWN.bmp", "IG_GREEN_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_LEFT_RIGHT_UP_DOWN.bmp", "IG_GREEN_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_LEFT_UP.bmp", "IG_GREEN_LEFT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_LEFT_UP_DOWN.bmp", "IG_GREEN_LEFT_UP_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_LEFT_DOWN.bmp", "IG_GREEN_LEFT_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_GREEN_RIGHT_UP.bmp", "IG_GREEN_RIGHT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_RIGHT_DOWN.bmp", "IG_GREEN_RIGHT_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_RIGHT_UP_DOWN.bmp", "IG_GREEN_RIGHT_UP_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_GREEN_UP_DOWN.bmp", "IG_GREEN_UP_DOWN", 0, 0, 0.f, false);
		break;
	case PuyoColor::YELLOW:
		_Renderer->CreateAnimation("IG_YELLOW_PUYO.bmp", "IG_YELLOW_PUYO", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_CENTER.bmp", "IG_YELLOW_CENTER", 0, 1, 0.1f, true);
		_Renderer->CreateAnimation("IG_YELLOW_LAND.bmp", "IG_YELLOW_LAND", 0, 1, 0.1f, false);
		_Renderer->CreateAnimation("IG_YELLOW_DESTROY.bmp", "IG_YELLOW_DESTROY", 0, 5, 0.1f, false);

		_Renderer->CreateAnimation("IG_YELLOW_LEFT.bmp", "IG_YELLOW_LEFT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_RIGHT.bmp", "IG_YELLOW_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_UP.bmp", "IG_YELLOW_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_DOWN.bmp", "IG_YELLOW_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_YELLOW_LEFT_RIGHT.bmp", "IG_YELLOW_LEFT_RIGHT", 0, 0, 0.f, false);		
		_Renderer->CreateAnimation("IG_YELLOW_LEFT_RIGHT_DOWN.bmp", "IG_YELLOW_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_LEFT_RIGHT_UP_DOWN.bmp", "IG_YELLOW_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_LEFT_UP.bmp", "IG_YELLOW_LEFT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_LEFT_UP_DOWN.bmp", "IG_YELLOW_LEFT_UP_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_LEFT_DOWN.bmp", "IG_YELLOW_LEFT_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_YELLOW_RIGHT_UP.bmp", "IG_YELLOW_RIGHT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_RIGHT_DOWN.bmp", "IG_YELLOW_RIGHT_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_RIGHT_UP_DOWN.bmp", "IG_YELLOW_RIGHT_UP_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_YELLOW_UP_DOWN.bmp", "IG_YELLOW_UP_DOWN", 0, 0, 0.f, false);

		break;
	case PuyoColor::PURPLE:
		_Renderer->CreateAnimation("IG_PURPLE_PUYO.bmp", "IG_PURPLE_PUYO", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_CENTER.bmp", "IG_PURPLE_CENTER", 0, 1, 0.1f, true);
		_Renderer->CreateAnimation("IG_PURPLE_LAND.bmp", "IG_PURPLE_LAND", 0, 1, 0.1f, false);
		_Renderer->CreateAnimation("IG_PURPLE_DESTROY.bmp", "IG_PURPLE_DESTROY", 0, 5, 0.1f, false);

		_Renderer->CreateAnimation("IG_PURPLE_LEFT.bmp", "IG_PURPLE_LEFT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_RIGHT.bmp", "IG_PURPLE_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_UP.bmp", "IG_PURPLE_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_DOWN.bmp", "IG_PURPLE_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_PURPLE_LEFT_RIGHT.bmp", "IG_PURPLE_LEFT_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_LEFT_RIGHT_UP.bmp", "IG_PURPLE_LEFT_RIGHT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_LEFT_RIGHT_DOWN.bmp", "IG_PURPLE_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_LEFT_RIGHT_UP_DOWN.bmp", "IG_PURPLE_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_LEFT_UP.bmp", "IG_PURPLE_LEFT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_LEFT_UP_DOWN.bmp", "IG_PURPLE_LEFT_UP_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_LEFT_DOWN.bmp", "IG_PURPLE_LEFT_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_PURPLE_RIGHT_DOWN.bmp", "IG_PURPLE_RIGHT_DOWN", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_RIGHT_UP.bmp", "IG_PURPLE_RIGHT_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_RIGHT_UP_DOWN.bmp", "IG_PURPLE_RIGHT_UP_DOWN", 0, 0, 0.f, false);

		_Renderer->CreateAnimation("IG_PURPLE_UP_DOWN.bmp", "IG_PURPLE_UP_DOWN", 0, 0, 0.f, false);
		break;
	}
}

void InGame::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	InGameBgm_ = GameEngineSound::SoundPlayControl("InGame.mp3");

	if (nullptr != EnemyProfile_)
	{
		GameEngineActor* Profile = CreateActor<Stage>(4);
		GameEngineRenderer* Renderer = Profile->CreateRenderer();
		Renderer->SetImage(EnemyProfile_->GetImage());

		Renderer->SetImageScale();
		Renderer->SetPivot({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y + 70.f });
	}
}

void InGame::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{

}