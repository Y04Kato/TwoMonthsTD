#include "stage1.h"

void Stage1::Initialize() {
	input_ = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	for (int i = 0; i < 2; i++) {
		isSpriteMove_[i] = false;
		spriteRotate_[i] = 0.0f;
	}

	for (int i = 0; i < 6; i++) {
		isSpriteDraw[i] = true;
	}

	spriteTexture_[0] = textureManager_->Load("project/gamedata/resources/panel/panel0.png");
	spriteTexture_[1] = textureManager_->Load("project/gamedata/resources/panel/panel1.png");
	spriteTexture_[2] = textureManager_->Load("project/gamedata/resources/panel/panel2.png");
	spriteTexture_[3] = textureManager_->Load("project/gamedata/resources/panel/panel3.png");

	sprite_[0] = std::make_unique<CreateSprite>();
	sprite_[0]->Initialize(Vector2{100.0f,100.0f},spriteTexture_[2],false,false);
	sprite_[0]->SetTextureInitialSize();

	sprite_[1] = std::make_unique<CreateSprite>();
	sprite_[1]->Initialize(Vector2{ 100.0f,100.0f }, spriteTexture_[1], false, false);
	sprite_[1]->SetTextureInitialSize();

	sprite_[2] = std::make_unique<CreateSprite>();
	sprite_[2]->Initialize(Vector2{ 100.0f,100.0f }, spriteTexture_[1], false, false);
	sprite_[2]->SetTextureInitialSize();

	sprite_[3] = std::make_unique<CreateSprite>();
	sprite_[3]->Initialize(Vector2{ 100.0f,100.0f }, spriteTexture_[3], false, true);
	sprite_[3]->SetTextureInitialSize();

	sprite_[4] = std::make_unique<CreateSprite>();
	sprite_[4]->Initialize(Vector2{ 100.0f,100.0f }, spriteTexture_[3], false, false);
	sprite_[4]->SetTextureInitialSize();

	sprite_[5] = std::make_unique<CreateSprite>();
	sprite_[5]->Initialize(Vector2{ 100.0f,100.0f }, spriteTexture_[1], false, false);
	sprite_[5]->SetTextureInitialSize();

	spriteTransform_[0] = {{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{550.0f,280.0f,0.0f}};
	spriteTransform_[1] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{350.0f,280.0f,0.0f} };
	spriteTransform_[2] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{150.0f,280.0f,0.0f} };
	spriteTransform_[3] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{550.0f,280.0f,0.0f}};
	spriteTransform_[4] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{550.0f,480.0f,0.0f} };
	spriteTransform_[5] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{750.0f,280.0f,0.0f} };

	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };
	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
}

void Stage1::Update() {
	if (input_->TriggerKey(DIK_1)) {
		isSpriteMove_[0] = true;
	}
	if (isSpriteMove_[0] == true) {
		//spriteTransform_[3].rotate.num += {1.0f, 0.0f, 0.0f};
	}
	if (spriteRotate_[0] > 3.0f) {
		isSpriteDraw[0] = false;
		//isSpriteMove_[0] = false;
	}

	ImGui::Begin("Stage1");
	ImGui::DragFloat("Rotate", spriteTransform_[3].rotate.num, 0.05f);
	ImGui::End();
}

void Stage1::Draw() {
	for (int i = 0; i < 6; i++) {
		if (isSpriteDraw[i] == true) {
			sprite_[i]->Draw(spriteTransform_[i], spriteUvTransform_, spriteMaterial_);
		}
	}
}