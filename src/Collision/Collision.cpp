#include "DxLib.h"
#include "Collision.h"

//IsHitRectの定義（四角）
bool Collision::Rect(int aX, int aY, int aW, int aH, int bX, int bY, int bW, int bH)
{
	if (bX < aX + aW &&
		bX + bW > aX &&
		bY + bH > aY &&
		bY < aY + aH)
	{
		return true;
	}
	return false;
}
bool Collision::Rect(float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH)
{
	if (bX < aX + aW &&
		bX + bW > aX &&
		bY + bH > aY &&
		bY < aY + aH)
	{
		return true;
	}
	return false;
}

//IsHitRectの定義（四角）：3D
bool Collision::Rect3D(VECTOR aPos, VECTOR aSize,  VECTOR bPos, VECTOR bSize)
{
	if (bPos.x < aPos.x + aSize.x &&
		bPos.x + bSize.x > aPos.x &&

		bPos.y < aPos.y + aSize.y &&
		bPos.y + bSize.y > aPos.y &&

		bPos.z < aPos.z + aSize.z &&
		bPos.z + bSize.z > aPos.z
		)
	{
		return true;
	}
	return false;
}


//IsHitCircleの定義（円形）
bool Collision::Circlr(int aX, int aY, int aR, int bX, int bY, int bR)
{
	if ((aR + bR) * (aR + bR) > (aX - bX) * (aX - bX) + (aY - bY) * (aY - bY))
	{
		return true;
	}
	return false;
}

//IsHitCircleの定義（円形）：3D
bool Collision::Circlr3D(VECTOR aPos, float aR, VECTOR bPos, float bR)
{
	if ((aR + bR) * (aR + bR) >
		(aPos.x - bPos.x) * (aPos.x - bPos.x) + 
		(aPos.y - bPos.y) * (aPos.y - bPos.y) +
		(aPos.z - bPos.z) * (aPos.z - bPos.z))
	{
		return true;
	}
	return false;
}
