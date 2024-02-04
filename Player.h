#pragma once
#include "Bullet.h"

class Player
{
private:
	//ここから
	int x;
	int y;
	int speed;
	int r;
	int isAlive;
	Bullet* bullet_;
	//ここまでメンバ変数

public:
	//ここから
	void Initialize(); //初期化関数
	void Update(char* keys/*, char* preKeys*/); //更新処理
	void Draw(); //描画処理
	int GetPosX() { return x; }
	int GetPosY() { return y; }
	int GetRad() { return r; }
	Bullet* GetBullet() { return bullet_; }
	//ここまでメンバ関数
};