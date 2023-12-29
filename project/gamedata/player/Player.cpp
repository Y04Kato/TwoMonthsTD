#include "Player.h"

void Player::Initialize() {
	input_ = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	spriteTexture_[0] = textureManager_->Load("project/gamedata/resources/player/PlayerRun1.png");
	spriteTexture_[1] = textureManager_->Load("project/gamedata/resources/player/PlayerRun2.png");
	spriteTexture_[2] = textureManager_->Load("project/gamedata/resources/player/PlayerRun3.png");
	spriteTexture_[3] = textureManager_->Load("project/gamedata/resources/player/PlayerRun4.png");
	spriteTexture_[4] = textureManager_->Load("project/gamedata/resources/player/PlayerRun5.png");
	spriteTexture_[5] = textureManager_->Load("project/gamedata/resources/player/PlayerRun6.png");
	
	for (int i = 0; i < 6; i++) {
		sprite_[i] = std::make_unique<CreateSprite>();
		sprite_[i]->Initialize(Vector2{48.0f,48.0f}, spriteTexture_[i], true, false);
		sprite_[i]->SetAnchor(Vector2{ 0.5f,1.0f });
	}

	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{180.0f,380.0f,0.1f} };
	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };
	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
}

void Player::Update() {
	spriteTimer_++;
	if (spriteTimer_ >= 60) {
		spriteTimer_ = 0;
	}
	if (input_->PressKey(DIK_W)) {
		spriteTransform_.translate.num[1] -= 2.0f;
	}
	if (input_->PressKey(DIK_S)) {
		spriteTransform_.translate.num[1] += 2.0f;
	}
	if (input_->PressKey(DIK_A)) {
		spriteTransform_.translate.num[0] -= 2.0f;
		for (int i = 0; i < 6; i++) {
			sprite_[i]->SetFlip(false, false);
		}
	}
	if (input_->PressKey(DIK_D)) {
		spriteTransform_.translate.num[0] += 2.0f;
		for (int i = 0; i < 6; i++) {
			sprite_[i]->SetFlip(true, false);
		}
	}
}

void Player::Draw() {
	if (spriteTimer_ >= 0 && spriteTimer_ < 10) {
		sprite_[0]->Draw(spriteTransform_, spriteUvTransform_, spriteMaterial_);
	}
	if (spriteTimer_ >= 10 && spriteTimer_ < 20) {
		sprite_[1]->Draw(spriteTransform_, spriteUvTransform_, spriteMaterial_);
	}
	if (spriteTimer_ >= 20 && spriteTimer_ < 30) {
		sprite_[2]->Draw(spriteTransform_, spriteUvTransform_, spriteMaterial_);
	}
	if (spriteTimer_ >= 30 && spriteTimer_ < 40) {
		sprite_[3]->Draw(spriteTransform_, spriteUvTransform_, spriteMaterial_);
	}
	if (spriteTimer_ >= 40 && spriteTimer_ < 50) {
		sprite_[4]->Draw(spriteTransform_, spriteUvTransform_, spriteMaterial_);
	}
	if (spriteTimer_ >= 50 && spriteTimer_ < 60) {
		sprite_[5]->Draw(spriteTransform_, spriteUvTransform_, spriteMaterial_);
	}
}