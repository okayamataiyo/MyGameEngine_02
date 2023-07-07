#include "Rootjob.h"
#include "../PlayScene.h"

Rootjob::Rootjob()
{
}

Rootjob::~Rootjob()
{
}

void Rootjob::Initialize(void)
{
	/*PlayScene* pPlayScene;
	pPlayScene = new PlayScene(this);

	pPlayScene->Initialize();
	childList_.push_back(pPlayScene);*/
	Instantiate<PlayScene>(this);
}

void Rootjob::Update()
{
}

void Rootjob::Draw()
{
	/*for (auto& e : childList_)
		e->Draw();*/
}

void Rootjob::Release()
{
}
