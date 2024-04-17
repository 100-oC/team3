#include"DxLib.h"
#define _USE_MATH_DEFINES	//円周率
#include<math.h>

#include"MathPlus.h"

//２から１への進行方向と移動量：動かしたいものXY1  向かう場所XY2  XとYのどちらを出すか  増加量
float GetMoving(float x1, float y1, float x2, float y2, char moji,float s)
{
	float x = x2 - x1;
	float y = y2 - y1;

	float n = x * x + y * y;

	n = sqrtf(n);

	if (moji == 'x')
	{
		return x / n * s;
	}
	else if (moji == 'y')
	{
		return y / n * s;
	}
	return 0;
}

//2点間の距離：開始地点XY　終了地点XY
float GetDistance(float startX, float startY, float endX, float endY)
{
	float num = 0.0f;
	num = ((startX - endX) * (startX - endX)) + ((startY - endY) * (startY - endY));
	num = sqrtf(num);

	return num;
}

//1から2への角度(ラジアン)：向かせる場所XY　向かせたいものXY
float GetAngle(float Ax, float Ay, float Bx, float By)
{
	float num = 0.0f;
	num=atan2f(By - Ay, Bx - Ax);

	return num;
}

//ベクトルの内積を求めて正か負を返す：向かせたいものXY　向かせる場所XY
bool GetInnerProduct(float Ax, float Ay, float Bx, float By)
{
	float num = 0.0f;

	num = Bx * Ax + By * Ay;
	if (num > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//ベクターの足し算
VECTOR AddVec(VECTOR vecA, VECTOR vecB)
{
	VECTOR ret;

	ret.x = vecA.x + vecB.x;
	ret.y = vecA.y + vecB.y;
	ret.z = vecA.z + vecB.z;

	return ret;
}
VECTOR AddVec(VECTOR vecA, float x, float y, float z)
{
	VECTOR ret;

	ret.x = vecA.x + x;
	ret.y = vecA.y + y;
	ret.z = vecA.z + z;

	return ret;
}

//ベクターの引き算
VECTOR SudVec(VECTOR vecA, VECTOR vecB)
{
	VECTOR ret;

	ret.x = vecA.x - vecB.x;
	ret.y = vecA.y - vecB.y;
	ret.z = vecA.z - vecB.z;

	return ret;
}

//度をラジアンに変換（引数：度）
float ChangeDegToRad(float degree)
{
	return degree * (float)M_PI / 180.0f;
}