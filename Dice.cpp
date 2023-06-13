#include "Dice.h"
#include "Camera.h"

Dice::Dice()
{
}

Dice::~Dice()
{
	Release();
}

HRESULT Dice::Initialize()
{

	VERTEX vertices[] =
	{
		//面１
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f)},	// 正面四角形の頂点（左上)	0
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,  0.0f, 0.0f, 0.0f)},	// 正面四角形の頂点（左下）	1
		{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f)},	// 正面四角形の頂点（右上)	2
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f)},	// 正面四角形の頂点（右下）	3

		//面2
		{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,  0.0f, 0.0f, 0.0f)},	// 左面四角形の頂点（左上）	4
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.5f,  0.0f, 0.0f, 0.0f)},	// 左面四角形の頂点（左下）	5
		{XMVectorSet( 1.0f,  1.0f, 2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},	// 左面四角形の頂点（右上）	6
		{XMVectorSet( 1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.5f,  0.5f, 0.f, 0.0f)},	// 左面四角形の頂点（右下）	7

		//面3
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f),XMVectorSet(0.5f,  0.0f, 0.0f, 0.0f)},	// 右面四角形の頂点（左上）	8
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.75f,  0.0f, 0.0f, 0.0f)},	// 右面四角形の頂点（左下）	9
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.5f,  0.5f, 0.0f, 0.0f)},	// 右面四角形の頂点（右上）	10
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.75f,  0.5f, 0.0f, 0.0f)},	// 右面四角形の頂点（右下）	11

		//面4
		{XMVectorSet( 1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f)},	// 下面四角形の頂点（左上）	12
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f)},	// 下面四角形の頂点（左下）	13
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),XMVectorSet(0.0f,  1.0f, 0.0f, 0.0f)},	// 下面四角形の頂点（右上）	14
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,  1.0f, 0.5f, 0.0f)},	// 下面四角形の頂点（右下）	15

		//面5
		{XMVectorSet( 1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f)},	// 上面四角形の頂点（左上）	16
		{XMVectorSet( 1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.5f,  0.5f, 0.0f, 0.0f)},	// 上面四角形の頂点（左下）	17
		{XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(0.25f,  1.0f, 0.0f, 0.0f)},	// 上面四角形の頂点（右上）	18
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.5f,  1.0f, 0.0f, 0.0f)},	// 上面四角形の頂点（右下）	19

		//面6
		{XMVectorSet( 1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.75f,  0.0f, 0.0f, 0.0f)},	// 裏面四角形の頂点（左上）	20
		{XMVectorSet( 1.0f,-1.0f, 2.0f, 0.0f),XMVectorSet(1.0f,  0.0f, 0.0f, 0.0f)},	// 裏面四角形の頂点（左下）	21
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),XMVectorSet(0.75f,  0.5f, 0.0f, 0.0f)},	// 裏面四角形の頂点（右上）	22
		{XMVectorSet(-1.0f,-1.0f, 2.0f, 0.0f),XMVectorSet(1.0f,  0.5f, 0.0f, 0.0f)},	// 裏面四角形の頂点（右下）	23
	};

	//インデックス情報
	int index[] ={
	 0,3,1, 0,2,3,
	 4,7,5, 4,6,7,
	 8,11,9, 8,10,11,
	 12,15,13, 12,14,15,
	 16,19,17, 16,18,19,
	 20,23,21, 20,22,23
	};

	CreateBuffers(vertices, 24, index, 36);

	return S_OK;

	
}

void Dice::Draw(XMMATRIX& worldMatrix)
{
	SetBuffers(36, worldMatrix);
}

void Dice::Release()
{
}
