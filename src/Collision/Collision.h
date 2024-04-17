
#ifndef __COLLISION_H__
#define __COLLISION_H__

class Collision
{
public:

	//四角：X,Yは座標、Wが横幅、Hが縦幅
	static bool Rect(int aX, int aY, int aW, int aH, int bX, int bY, int bW, int bH);
	static bool Rect(float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH);

	//四角(3D)：それぞれの座標VECと大きさVEC
	static bool Rect3D(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize);

	//円形：それぞれの座標と半径
	static bool Circlr(int aX, int aY, int aR, int bX, int bY, int bR);

	//円形(3D)：それぞれの座標と半径
	static bool Circlr3D(VECTOR aPos, float aR, VECTOR bPos, float bR);
};

#endif
