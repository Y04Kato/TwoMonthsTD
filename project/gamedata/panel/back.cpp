#include "back.h"

void Back::Initialize() {
	textureManager_ = TextureManager::GetInstance();

	//backModel_.reset(Model::CreateModelFromObj("project/gamedata/resources/back", "back.obj"));
	backTexture_ = textureManager_->Load("project/gamedata/resources/page.png");

	sprite_ = std::make_unique <CreateSprite>();
	sprite_->Initialize(Vector2{ 100.0f,100.0f }, backTexture_, false, false);
	sprite_->SetTextureInitialSize();

	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };
	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };

	/*worldTransform_.Initialize();
	worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
	worldTransform_.scale_ = { 0.0f,0.0f,0.0f };
	worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };*/
}

void Back::Update() {
	//worldTransform_.UpdateMatrix();
}

void Back::Draw() {
	//backModel_->Draw(worldTransform_, viewProjection, { 1.0f,1.0f,1.0f,1.0 });
	sprite_->Draw(spriteTransform_, spriteUvTransform_, spriteMaterial_);
}