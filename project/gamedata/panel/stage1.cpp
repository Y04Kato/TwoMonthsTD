#include "stage1.h"

void Stage1::Initialize() {
	input_ = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	for (int i = 0; i < 2; i++) {
		isSpriteMove_[i] = false;
		isSpriteReturnMove_[i] = false;
	}

	for (int i = 0; i < 8; i++) {
		isSpriteDraw_[i] = true;
	}

	spriteTexture_[0] = textureManager_->Load("project/gamedata/resources/panel/panel0.png");
	spriteTexture_[1] = textureManager_->Load("project/gamedata/resources/panel/panel1.png");
	spriteTexture_[2] = textureManager_->Load("project/gamedata/resources/panel/panel2.png");
	spriteTexture_[3] = textureManager_->Load("project/gamedata/resources/panel/panel3.png");
	spriteTexture_[4] = textureManager_->Load("project/gamedata/resources/goal/goal.png");

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

	sprite_[6] = std::make_unique<CreateSprite>();
	sprite_[6]->Initialize(Vector2{ 100.0f,100.0f }, spriteTexture_[1], false, true);
	sprite_[6]->SetTextureInitialSize();

	sprite_[7] = std::make_unique<CreateSprite>();
	sprite_[7]->Initialize(Vector2{ 100.0f,100.0f }, spriteTexture_[3], false, false);
	sprite_[7]->SetTextureInitialSize();

	sprite_[8] = std::make_unique<CreateSprite>();
	sprite_[8]->Initialize(Vector2{ 100.0f,100.0f }, spriteTexture_[4], false, false);
	sprite_[8]->SetTextureInitialSize();

	spriteTransform_[0] = {{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{550.0f,280.0f,0.0f}};
	spriteTransform_[1] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{350.0f,280.0f,0.0f} };
	spriteTransform_[2] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{150.0f,280.0f,0.0f} };
	spriteTransform_[3] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{550.0f,280.0f,0.0f}};
	spriteTransform_[4] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{550.0f,480.0f,0.0f} };
	spriteTransform_[5] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{750.0f,280.0f,0.0f} };
	spriteTransform_[6] = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f},{550.0f,280.0f,0.1f} };
	spriteTransform_[7] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{550.0f,480.0f,0.1f} };
	spriteTransform_[8] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{880.0f,360.0f,0.0f} };

	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };
	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
}

void Stage1::Update() {
	UpsidePanelMove();
	DownSidePanelMove();
}

void Stage1::Draw() {
	sprite_[6]->Draw(spriteTransform_[6], spriteUvTransform_, spriteMaterial_);
	sprite_[7]->Draw(spriteTransform_[7], spriteUvTransform_, spriteMaterial_);

	for (int i = 0; i < 6; i++) {
		if (isSpriteDraw_[i] == true) {
			sprite_[i]->Draw(spriteTransform_[i], spriteUvTransform_, spriteMaterial_);
		}
	}

	sprite_[8]->Draw(spriteTransform_[8], spriteUvTransform_, spriteMaterial_);
}

void Stage1::UpsidePanelMove() {
	// 上側パネルの折り曲げ
	if (input_->TriggerKey(DIK_1) && spriteTransform_[3].rotate.num[0] == 0.0f) {
		isSpriteMove_[0] = true;
	}
	if (isSpriteMove_[0] == true) {
		spriteTransform_[3].rotate.num[0] += 0.05f;
		spriteTransform_[6].rotate.num[0] += 0.05f;
	}
	if (spriteTransform_[3].rotate.num[0] >= 2.8f) {
		isSpriteDraw_[0] = false;
		isSpriteDraw_[3] = false;
	}
	if (spriteTransform_[3].rotate.num[0] >= 3.0f) {
		isSpriteMove_[0] = false;
		spriteTransform_[3].rotate.num[0] = 3.0f;
	}

	// 折り返し
	if (input_->TriggerKey(DIK_1) && spriteTransform_[3].rotate.num[0] == 3.0f) {
		isSpriteReturnMove_[0] = true;
	}
	if (isSpriteReturnMove_[0] == true) {
		spriteTransform_[3].rotate.num[0] -= 0.05f;
		spriteTransform_[6].rotate.num[0] -= 0.05f;
	}
	if (spriteTransform_[3].rotate.num[0] <= 2.8f) {
		isSpriteDraw_[0] = true;
		isSpriteDraw_[3] = true;
	}
	if (spriteTransform_[3].rotate.num[0] <= 0.0f) {
		isSpriteReturnMove_[0] = false;
		spriteTransform_[3].rotate.num[0] = 0.0f;
	}
}

void Stage1::DownSidePanelMove() {
	// 下側パネルの折り曲げ
	if (input_->TriggerKey(DIK_2) && spriteTransform_[4].rotate.num[0] == 0.0f) {
		isSpriteMove_[1] = true;
	}
	if (isSpriteMove_[1] == true) {
		spriteTransform_[4].rotate.num[0] -= 0.05f;
		spriteTransform_[7].rotate.num[0] -= 0.05f;
	}
	if (spriteTransform_[4].rotate.num[0] <= -2.8f) {
		isSpriteDraw_[0] = false;
		isSpriteDraw_[4] = false;
	}
	if (spriteTransform_[4].rotate.num[0] <= -3.0f) {
		isSpriteMove_[1] = false;
		spriteTransform_[4].rotate.num[0] = -3.0f;
	}

	// 折り返し
	if (input_->TriggerKey(DIK_2) && spriteTransform_[4].rotate.num[0] == -3.0f) {
		isSpriteReturnMove_[1] = true;
	}
	if (isSpriteReturnMove_[1] == true) {
		spriteTransform_[4].rotate.num[0] += 0.05f;
		spriteTransform_[7].rotate.num[0] += 0.05f;
	}
	if (spriteTransform_[4].rotate.num[0] >= -2.8f) {
		isSpriteDraw_[4] = true;
		isSpriteDraw_[7] = true;
	}
	if (spriteTransform_[4].rotate.num[0] >= 0.0f) {
		isSpriteReturnMove_[1] = false;
		spriteTransform_[4].rotate.num[0] = 0.0f;
	}
}