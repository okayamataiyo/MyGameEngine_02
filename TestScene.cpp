#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "TestScene.h"
#include"Stage.h"
#include"Controller.h"


TestScene::TestScene(GameObject* parent)
	:GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Controller>(this);
}

void TestScene::Update()
{

//	GameObject* dbgTest = FindObject("SceneManager");
	if (Input::IsKey(DIK_SPACE)) {

		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
