#include "Player.h"

void Player::Initialize() {
	input_ = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	spriteTexture_ = textureManager_->Load("project/gamedata/resources/player/player.png");

	sprite_ = std::make_unique<CreateSprite>();
	sprite_->Initialize(Vector2{ 100.0f,100.0f }, spriteTexture_, false, false);
	sprite_->SetTextureInitialSize();

	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{180.0f,360.0f,0.1f} };
	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };
	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
}

void Player::Update() {
	if (input_->PressKey(DIK_W)) {
		spriteTransform_.translate.num[1] -= 2.0f;
	}
	if (input_->PressKey(DIK_S)) {
		spriteTransform_.translate.num[1] += 2.0f;
	}
	if (input_->PressKey(DIK_A)) {
		spriteTransform_.translate.num[0] -= 2.0f;
	}
	if (input_->PressKey(DIK_D)) {
		spriteTransform_.translate.num[0] += 2.0f;
	}
}

void Player::Draw() {
	sprite_->Draw(spriteTransform_, spriteUvTransform_, spriteMaterial_);
}