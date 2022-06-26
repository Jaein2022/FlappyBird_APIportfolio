#pragma once
#include <Basement\PreCompile.h>

enum class CollisionBodyType
{
	FRect,	//���� �簢��.
	HLine,	//���μ�.
	VLine,	//���μ�.
	RRect,	//ȸ�� �簢��.
	MAX
};

union CollisionBody
{
	DirectX::BoundingBox AABB;	//Axis-Aligned Bounding Box: 3��������� ���� ���ĵ� �ڽ�. ȸ�� �ȵ�.
	DirectX::BoundingOrientedBox OBB;	//Oriented Bounding Box: ��ü ���⼺�� ���� �ڽ�. ȸ�� ��.
	DirectX::BoundingSphere Sphere;	//��ü.
	
	CollisionBody(): OBB()
	{
	}
};