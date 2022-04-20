#pragma once
#include "GameEngine/GameEngineActor.h"
#include <list>

class Puyo;
class PuyoPair;
class GameEngineRenderer;
class EnemyProfile : public GameEngineActor //AI
{
public:
	EnemyProfile();
	~EnemyProfile();

	EnemyProfile(const EnemyProfile& _Other) = delete;
	EnemyProfile(EnemyProfile&& _Other) noexcept = delete;
	EnemyProfile& operator=(const EnemyProfile& _Other) = delete;
	EnemyProfile& operator=(EnemyProfile&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;

	GameEngineRenderer* GetProfile()
	{
   		return MyProfile_;
	}

	GameEngineRenderer* GetIcon()
	{
		return MyIcon_;
	}
	
	void SetProfile(GameEngineRenderer* _Profile)
	{
		MyProfile_ = _Profile;
	}

	void SetIcon(GameEngineRenderer* _Icon)
	{
		MyIcon_ = _Icon;
	}

protected:

private:
	GameEngineRenderer* MyProfile_;
	GameEngineRenderer* MyAnimation_;
	GameEngineRenderer* MyIcon_;
	GameEngineRenderer* MyName_;


};
