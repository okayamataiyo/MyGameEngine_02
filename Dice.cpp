#include "Dice.h"
#include "Camera.h"

void Dice::InitVertexData()
{

	VERTEX vertices[] =
	{
		//面１
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 正面四角形の頂点（左上)	0
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 正面四角形の頂点（左下）	1
		{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 正面四角形の頂点（右上)	2
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 正面四角形の頂点（右下）	3

		//面2
		{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 左面四角形の頂点（左上）	4
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 左面四角形の頂点（左下）	5
		{XMVectorSet( 1.0f,  1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 左面四角形の頂点（右上）	6
		{XMVectorSet( 1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f,  0.5f, 0.f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 左面四角形の頂点（右下）	7

		//面3
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 右面四角形の頂点（左上）	8
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 右面四角形の頂点（左下）	9
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 右面四角形の頂点（右上）	10
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.75f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 右面四角形の頂点（右下）	11

		//面4
		{XMVectorSet( 1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 下面四角形の頂点（左上）	12
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 下面四角形の頂点（左下）	13
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 下面四角形の頂点（右上）	14
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  1.0f, 0.5f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 下面四角形の頂点（右下）	15

		//面5
		{XMVectorSet( 1.0f, 1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 上面四角形の頂点（左上）	16
		{XMVectorSet( 1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 上面四角形の頂点（左下）	17
		{XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 上面四角形の頂点（右上）	18
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 上面四角形の頂点（右下）	19

		//面6
		{XMVectorSet( 1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 裏面四角形の頂点（左上）	20
		{XMVectorSet( 1.0f,-1.0f, 2.0f, 0.0f),	XMVectorSet(1.0f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 裏面四角形の頂点（左下）	21
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 裏面四角形の頂点（右上）	22
		{XMVectorSet(-1.0f,-1.0f, 2.0f, 0.0f),	XMVectorSet(1.0f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// 裏面四角形の頂点（右下）	23
	};

	//頂点の数
	vertexNum_ = vertices_.size();
}

//インデックス情報を準備
void Dice::InitIndexData()
{
	index_ = { 0,1,2, 0,2,3, 4,5,6, 4,6,7, 8,9,10, 8,10,11, 12,13,14, 12,14,15, 16,17,18, 16,18,19, 20,21,22, 20,22,23, };

	//インデックス数
	indexNum_ = index_.size();
}