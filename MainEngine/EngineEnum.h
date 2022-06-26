#pragma once
#include <Basement\PreCompile.h>

enum class CollisionBodyType
{
	FRect,	//고정 사각형.
	HLine,	//가로선.
	VLine,	//세로선.
	RRect,	//회전 사각형.
	MAX
};

union CollisionBody
{
	DirectX::BoundingBox AABB;	//Axis-Aligned Bounding Box: 3축방향으로 축이 정렬된 박스. 회전 안됨.
	DirectX::BoundingOrientedBox OBB;	//Oriented Bounding Box: 자체 방향성을 가진 박스. 회전 됨.
	DirectX::BoundingSphere Sphere;	//구체.
	
	CollisionBody(): OBB()
	{
	}
};