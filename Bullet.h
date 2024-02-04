#pragma once

class Bullet
{
public:
	int x; //座標
	int y;
	int speed; //速度
	int r; //半径
	int isShot; //発射状態の判別フラグ

public:
	Bullet(); //コンストラクタ
	~Bullet();
	void Update();
	void Draw();
	int GetPosX() { return x; }
	int GetPosY() { return y; }
	int GetRad() { return r; }
};
