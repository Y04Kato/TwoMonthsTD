#include"GameSelectScene.h"

void GameSelectScene::Initialize() {
	//CJEngine
	CJEngine_ = CitrusJunosEngine::GetInstance();

	//Input
	input_ = Input::GetInstance();

	textureManager_ = TextureManager::GetInstance();

	pageL_ = textureManager_->Load("project/gamedata/resources/pageLeft.png");
	pageR_ = textureManager_->Load("project/gamedata/resources/pageRight.png");
	pageAll_ = textureManager_->Load("project/gamedata/resources/page.png");
	start_ = textureManager_->Load("project/gamedata/resources/pressSpace.png");

	//Audio
	audio_ = Audio::GetInstance();
	soundData1_ = audio_->SoundLoadWave("project/gamedata/resources/page.wav");

	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{1280.0f / 2.0f,720.0f / 2.0f,0.0f} };
	spriteTransform2_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{1280.0f / 2.0f,720.0f / 2.0f,0.0f} };
	SpriteuvTransform_ = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
	};

	sprite_[0] = std::make_unique <CreateSprite>();
	sprite_[0]->Initialize(Vector2{ 100.0f,100.0f }, pageAll_, false, false);
	sprite_[0]->SetTextureInitialSize();
	sprite_[0]->SetAnchor(Vector2{ 0.5f,0.5f });

	sprite_[1] = std::make_unique <CreateSprite>();
	sprite_[1]->Initialize(Vector2{ 100.0f,100.0f }, pageL_, false, false);
	sprite_[1]->SetTextureInitialSize();
	sprite_[1]->SetAnchor(Vector2{ 0.5f,0.5f });

	sprite_[2] = std::make_unique <CreateSprite>();
	sprite_[2]->Initialize(Vector2{ 100.0f,100.0f }, pageR_, false, false);
	sprite_[2]->SetTextureInitialSize();
	sprite_[2]->SetAnchor(Vector2{ 0.5f,0.5f });

	sprite_[3] = std::make_unique <CreateSprite>();
	sprite_[3]->Initialize(Vector2{ 100.0f,100.0f }, start_, false, false);
	sprite_[3]->SetTextureInitialSize();
	sprite_[3]->SetAnchor(Vector2{ 0.5f,0.5f });

	count = 0;
}

void GameSelectScene::Update() {
	if (input_->TriggerKey(DIK_RIGHT)) {
		if (pageChangeR_ == false) {
			count++;
			if (count > 4) {
				count = 0;
				pageChangeL_ = true;
				spriteTransform2_.rotate.num[1] = 3.15f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
			}
			else {
				pageChangeR_ = true;
				spriteTransform2_.rotate.num[1] = 0.0f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
			}
		}
		else {

		}
	}

	ImGui::Begin("SelectScene");
	ImGui::Text("SelectStage : %d",count);
	ImGui::End();

	if (input_->TriggerKey(DIK_LEFT)) {
		if (pageChangeL_ == false) {
			count--;
			if (count < 0) {
				count = 4;
				pageChangeR_ = true;
				spriteTransform2_.rotate.num[1] = 0.0f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
			}
			else {
				pageChangeL_ = true;
				spriteTransform2_.rotate.num[1] = 3.15f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
			}
		}
		else {

		}
	}

	if (pageChangeR_ == true) {
		spriteTransform2_.rotate.num[1] += 0.05f;
		if (spriteTransform2_.rotate.num[1] >= 3.15f) {
			spriteTransform2_.rotate.num[1] = 3.15f;
			pageChangeR_ = false;
		}
	}
	if (pageChangeL_ == true) {
		spriteTransform2_.rotate.num[1] -= 0.05f;
		if (spriteTransform2_.rotate.num[1] <= 0.0f) {
			spriteTransform2_.rotate.num[1] = 0.0f;
			pageChangeL_ = false;
		}
	}

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

	if (count == 0) {
		if (input_->TriggerKey(DIK_SPACE)) {
			if (pageChangeR_ == false) {
				pageChangeR_ = true;
				spriteTransform2_.rotate.num[1] = 0.0f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
				startGameScene1 = true;
			}
			else {

			}
		}
	}
	if (count == 1) {
		if (input_->TriggerKey(DIK_SPACE)) {
			if (pageChangeR_ == false) {
				pageChangeR_ = true;
				spriteTransform2_.rotate.num[1] = 0.0f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
				startGameScene2 = true;
			}
			else {

			}
		}
	}
	if (count == 2) {
		if (input_->TriggerKey(DIK_SPACE)) {
			if (pageChangeR_ == false) {
				pageChangeR_ = true;
				spriteTransform2_.rotate.num[1] = 0.0f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
				startGameScene3 = true;
			}
			else {

			}
		}
	}
	if (count == 3) {
		if (input_->TriggerKey(DIK_SPACE)) {
			if (pageChangeR_ == false) {
				pageChangeR_ = true;
				spriteTransform2_.rotate.num[1] = 0.0f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
				startGameScene4 = true;
			}
			else {

			}
		}
	}
	if (count == 4) {
		if (input_->TriggerKey(DIK_SPACE)) {
			if (pageChangeR_ == false) {
				pageChangeR_ = true;
				spriteTransform2_.rotate.num[1] = 0.0f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
				startGameScene5 = true;
			}
			else {

			}
		}
	}

	if (startGameScene1 == true && pageChangeR_ == false) {
		startGameScene1 = false;
		stageNo = 1;
		sceneNo = GAME_SCENE;
	}
	if (startGameScene2 == true && pageChangeR_ == false) {
		startGameScene2 = false;
		stageNo = 2;
		sceneNo = GAME_SCENE;
	}
	if (startGameScene3 == true && pageChangeR_ == false) {
		startGameScene3 = false;
		stageNo = 3;
		sceneNo = GAME_SCENE;
	}
	if (startGameScene4 == true && pageChangeR_ == false) {
		startGameScene4 = false;
		stageNo = 4;
		sceneNo = GAME_SCENE;
	}
	if (startGameScene5 == true && pageChangeR_ == false) {
		startGameScene5 = false;
		stageNo = 5;
		sceneNo = GAME_SCENE;
	}

}

void GameSelectScene::Draw() {
#pragma region 前景スプライト描画
	CJEngine_->PreDraw2D();
	sprite_[0]->Draw(spriteTransform_, SpriteuvTransform_, spriteMaterial_);
	sprite_[1]->Draw(spriteTransform_, SpriteuvTransform_, spriteMaterial_);
	sprite_[2]->Draw(spriteTransform2_, SpriteuvTransform_, spriteMaterial_);
	if (pageChangeR_ == false && pageChangeL_ == false) {
		sprite_[3]->Draw(spriteTransform_, SpriteuvTransform_, Vector4{ 1.0f,1.0f,1.0f,spriteAlpha_ / 256.0f });
	}

#pragma endregion
}

void GameSelectScene::Finalize() {
	audio_->SoundUnload(&soundData1_);
}
