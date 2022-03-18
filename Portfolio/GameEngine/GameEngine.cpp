#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include "GameEngineImage.h"

std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
GameEngineLevel* GameEngine::NextLevel_ = nullptr;
GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;
GameEngineImage* GameEngine::WindowMainImage_ = nullptr;

HDC GameEngine::BackBufferDC()
{
    return BackBufferImage_->ImageDC(); //����� ����
}

GameEngine::GameEngine() 
{
}

GameEngine::~GameEngine() 
{
}

void GameEngine::GameLoop()
{

}

void GameEngine::GameInit()
{

}

void GameEngine::GameEnd()
{

}

void GameEngine::WindowCreate()
{
    GameEngineWindow::GetInst().CreateGameWindow(nullptr, "GameWindow");
    GameEngineWindow::GetInst().ShowGameWindow();
    GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}


void GameEngine::EngineInit()
{
    UserContents_->GameInit();
    BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());
}

void GameEngine::EngineLoop()
{
    //���� ���ؿ��� �� ������ üũ
    UserContents_->GameLoop();

    //update���� ȭ���� ����ϰ� �׸��� ���� �� ���� ������ �ٲ��� �ϴ��� üũ
    if (nullptr != NextLevel_)
    {
        if (nullptr != CurrentLevel_)
        {
            CurrentLevel_->LevelChangeEnd();
        }

        CurrentLevel_ = NextLevel_;
        NextLevel_ = nullptr;

        if (nullptr != CurrentLevel_)
        {
            CurrentLevel_->LevelChangeStart();
        }
    }

    if (nullptr == CurrentLevel_)
    {
        MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
    }

    //���� ����(���� ��) �� ������ üũ
    CurrentLevel_->Update();
    CurrentLevel_->ActorUpdate();
    CurrentLevel_->ActorRender();
}

void GameEngine::EngineEnd()
{
    UserContents_->GameEnd();

    std::map<std::string, GameEngineLevel*>::iterator StartIter = AllLevel_.begin();
    std::map<std::string, GameEngineLevel*>::iterator EndIter = AllLevel_.end();

    for (; StartIter != EndIter; ++StartIter)
    {
        if (nullptr == StartIter->second)
        {
            continue;
        }

        delete StartIter->second;
    }

    GameEngineImageManager::Destroy();
    GameEngineWindow::Destroy();
}

void GameEngine::ChangeLevel(const std::string& _Name)
{
    std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Name);

    if (AllLevel_.end() == FindIter)
    {
        MsgBoxAssert("Level Find Error");
        return;
    }

    NextLevel_ = FindIter->second;
}