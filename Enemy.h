#pragma once

class Enemy
{
private:
	//ここから
	int x;
	int y;
	int speed;
	int r;
	int isAlive;
	int respawnTimer; //リスポーン用

	int enemyTex;
	//ここまでメンバ変数

public:
	//ここから
	void Initialize(); //初期化関数
	void Update(); //更新処理
	void Draw(); //描画処理
	int GetPosX() { return x; }
	int GetPosY() { return y; }
	int GetRad() { return r; }

	int IsAlive() { return isAlive; }
	void SetIsAlive(bool value) { isAlive = value; }

	int GetRespawnTimer() { return respawnTimer; }
	void DecreaseRespawnTimer() { respawnTimer--; }
	void Respawn() { isAlive = 1; respawnTimer = 120; }
	//ここまでメンバ関数
};

