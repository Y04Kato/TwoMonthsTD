#include"GameTitleScene.h"

void GameTitleScene::Initialize() {
	//CJEngine
	CJEngine_ = CitrusJunosEngine::GetInstance();

	//Input
	input_ = Input::GetInstance();

	textureManager_ = TextureManager::GetInstance();

	title_ = textureManager_->Load("project/gamedata/resources/Start.png");
	start_ = textureManager_->Load("project/gamedata/resources/pressSpace.png");
	tutorial_ = textureManager_->Load("project/gamedata/resources/tutorial.png");

	//Audio
	audio_ = Audio::GetInstance();
	soundData1_ = audio_->SoundLoadWave("project/gamedata/resources/click.wav");

	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	SpriteuvTransform_ = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};

	sprite_[0] = std::make_unique <CreateSprite>();
	sprite_[0]->Initialize(Vector2{ 100.0f,100.0f }, title_, false, false);
	sprite_[0]->SetTextureInitialSize();

	sprite_[1] = std::make_unique <CreateSprite>();
	sprite_[1]->Initialize(Vector2{ 100.0f,100.0f }, tutorial_, false, false);
	sprite_[1]->SetTextureInitialSize();

	sprite_[2] = std::make_unique <CreateSprite>();
	sprite_[2]->Initialize(Vector2{ 100.0f,100.0f }, start_, false, false);
	sprite_[2]->SetTextureInitialSize();

	count = 0;
}

void GameTitleScene::Update() {
	if (input_->TriggerKey(DIK_SPACE) && count < 2) {
		count++;
		audio_->SoundPlayWave(soundData1_, 0.5f, false);
	}
	if (count == 0) {
		if (changeAlpha_ == false) {
			spriteAlpha_ -= 8;
			if (spriteAlpha_ <= 0) {
				changeAlpha_ = true;
			}
		}
		if (changeAlpha_ == true) {
			spriteAlpha_ += 8;
			if (spriteAlpha_ >= 256) {
				changeAlpha_ = false;
			}
		}
	}
	if (count == 1) {

	}
	if (count == 2) {
		count = 0;
		sceneNo = GAME_SCENE;
	}
}

void GameTitleScene::Draw() {
#pragma region 前景スプライト描画
	CJEngine_->PreDraw2D();
	if (count == 0) {
		sprite_[0]->Draw(spriteTransform_, SpriteuvTransform_, spriteMaterial_);
		sprite_[2]->Draw(spriteTransform_, SpriteuvTransform_, Vector4{ 1.0f,1.0f,1.0f,spriteAlpha_ / 256.0f });
	}
	if (count == 1) {
		sprite_[1]->Draw(spriteTransform_, SpriteuvTransform_, spriteMaterial_);
	}

#pragma endregion
}

void GameTitleScene::Finalize() {
	audio_->SoundUnload(&soundData1_);
}