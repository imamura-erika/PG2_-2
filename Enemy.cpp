#include <Enemy.h>
#include <Novice.h>

void Enemy::Initialize() //初期化処理
{
	x = 300;
	y = 300;
	r = 16;
	speed = 4;
	isAlive = 1;
	respawnTimer = 0;

    enemyTex = Novice::LoadTexture("./Resources/enemy.png");
}

void Enemy::Update() //更新処理
{
    if (isAlive) {
        x += speed;
        if (x <= r || x >= 1280 - r) {
            speed *= -1;
        }
    }
    if (!isAlive) {
        respawnTimer--;
        if (respawnTimer <= 0) {
            Respawn();
        }
        return;
    }
}

void Enemy::Draw() //描画処理
{
	if (isAlive == 1) { //生きてる場合描画
		//Novice::DrawEllipse(x, y, r, r, 0.0f, WHITE, kFillModeSolid);
        Novice::DrawSprite(x-r, y-r, enemyTex, 1, 1, 0.0f, WHITE);
	}
}
