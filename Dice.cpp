#include "Dice.h"
#include "Camera.h"

void Dice::InitVertexData()
{

	VERTEX vertices[] =
	{
		//�ʂP
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i����)	0
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i�����j	1
		{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i�E��)	2
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i�E���j	3

		//��2
		{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i����j	4
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i�����j	5
		{XMVectorSet( 1.0f,  1.0f, 2.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i�E��j	6
		{XMVectorSet( 1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f,  0.5f, 0.f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i�E���j	7

		//��3
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// �E�ʎl�p�`�̒��_�i����j	8
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// �E�ʎl�p�`�̒��_�i�����j	9
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.5f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// �E�ʎl�p�`�̒��_�i�E��j	10
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.75f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// �E�ʎl�p�`�̒��_�i�E���j	11

		//��4
		{XMVectorSet( 1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i����j	12
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i�����j	13
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f),	XMVectorSet(0.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i�E��j	14
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  1.0f, 0.5f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i�E���j	15

		//��5
		{XMVectorSet( 1.0f, 1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ��ʎl�p�`�̒��_�i����j	16
		{XMVectorSet( 1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ��ʎl�p�`�̒��_�i�����j	17
		{XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f),	XMVectorSet(0.25f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ��ʎl�p�`�̒��_�i�E��j	18
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.5f,  1.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ��ʎl�p�`�̒��_�i�E���j	19

		//��6
		{XMVectorSet( 1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i����j	20
		{XMVectorSet( 1.0f,-1.0f, 2.0f, 0.0f),	XMVectorSet(1.0f,  0.0f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i�����j	21
		{XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f),	XMVectorSet(0.75f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i�E��j	22
		{XMVectorSet(-1.0f,-1.0f, 2.0f, 0.0f),	XMVectorSet(1.0f,  0.5f, 0.0f, 0.0f),	XMVectorSet(0.0f,0.0f,-1.0f,0.0f)},	// ���ʎl�p�`�̒��_�i�E���j	23
	};

	//���_�̐�
	vertexNum_ = vertices_.size();
}

//�C���f�b�N�X��������
void Dice::InitIndexData()
{
	index_ = { 0,1,2, 0,2,3, 4,5,6, 4,6,7, 8,9,10, 8,10,11, 12,13,14, 12,14,15, 16,17,18, 16,18,19, 20,21,22, 20,22,23, };

	//�C���f�b�N�X��
	indexNum_ = index_.size();
}