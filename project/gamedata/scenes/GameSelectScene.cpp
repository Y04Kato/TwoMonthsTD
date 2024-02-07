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

	select_[0] = textureManager_->Load("project/gamedata/resources/stage/stage1.png");
	select_[1] = textureManager_->Load("project/gamedata/resources/stage/stage2.png");
	select_[2] = textureManager_->Load("project/gamedata/resources/stage/stage3.png");
	select_[3] = textureManager_->Load("project/gamedata/resources/stage/stage4.png");
	select_[4] = textureManager_->Load("project/gamedata/resources/stage/stage5.png");
	select_[5] = textureManager_->Load("project/gamedata/resources/stage/stage6.png");
	select_[6] = textureManager_->Load("project/gamedata/resources/stage/stage7.png");
	select_[7] = textureManager_->Load("project/gamedata/resources/stage/stage8.png");
	select_[8] = textureManager_->Load("project/gamedata/resources/stage/stage9.png");
	select_[9] = textureManager_->Load("project/gamedata/resources/stage/stage10.png");

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

	for (int i = 0; i < 10; i++) {
		spriteSelect_[i] = std::make_unique <CreateSprite>();
		spriteSelect_[i]->Initialize(Vector2{ 100.0f,100.0f }, select_[i], false, false);
		spriteSelect_[i]->SetTextureInitialSize();
		spriteSelect_[i]->SetAnchor(Vector2{ 0.5f,0.5f });
	}

	model_[0].reset(Model::CreateModelFromObj("project/gamedata/resources/stagemodel/model1", "stage.obj"));
	model_[1].reset(Model::CreateModelFromObj("project/gamedata/resources/stagemodel/model2", "stage.obj"));
	model_[2].reset(Model::CreateModelFromObj("project/gamedata/resources/stagemodel/model3", "stage.obj"));
	model_[3].reset(Model::CreateModelFromObj("project/gamedata/resources/stagemodel/model4", "stage.obj"));
	model_[4].reset(Model::CreateModelFromObj("project/gamedata/resources/stagemodel/model5", "stage.obj"));
	model_[5].reset(Model::CreateModelFromObj("project/gamedata/resources/stagemodel/model6", "stage.obj"));
	model_[6].reset(Model::CreateModelFromObj("project/gamedata/resources/stagemodel/model7", "stage.obj"));
	model_[7].reset(Model::CreateModelFromObj("project/gamedata/resources/stagemodel/model8", "stage.obj"));
	model_[8].reset(Model::CreateModelFromObj("project/gamedata/resources/stagemodel/model9", "stage.obj"));
	model_[9].reset(Model::CreateModelFromObj("project/gamedata/resources/stagemodel/model10", "stage.obj"));
	worldTransformModel_.Initialize();
	worldTransformModel_.translation_ = { 18.25f,0.0f,0.0f };
	worldTransformModel_.scale_ = { 12.0f,12.0f,5.0f };
	modelMaterial_ = { 1.0f,1.0f,1.0f,1.0f };

	viewProjection_.Initialize();

	count = 0;
}

void GameSelectScene::Update() {
	if (input_->TriggerKey(DIK_RIGHT)) {
		if (pageChangeR_ == false) {
			count++;
			if (count > 9) {
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

	worldTransformModel_.rotation_.num[1] += 0.02f;

	worldTransformModel_.UpdateMatrix();
	viewProjection_.UpdateMatrix();

	ImGui::Begin("SelectScene");
	ImGui::Text("SelectStage : %d", count);
	ImGui::End();

	if (input_->TriggerKey(DIK_LEFT)) {
		if (pageChangeL_ == false) {
			count--;
			if (count < 0) {
				count = 9;
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
	if (count == 5) {
		if (input_->TriggerKey(DIK_SPACE)) {
			if (pageChangeR_ == false) {
				pageChangeR_ = true;
				spriteTransform2_.rotate.num[1] = 0.0f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
				startGameScene6 = true;
			}
			else {

			}
		}
	}
	if (count == 6) {
		if (input_->TriggerKey(DIK_SPACE)) {
			if (pageChangeR_ == false) {
				pageChangeR_ = true;
				spriteTransform2_.rotate.num[1] = 0.0f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
				startGameScene7 = true;
			}
			else {

			}
		}
	}
	if (count == 7) {
		if (input_->TriggerKey(DIK_SPACE)) {
			if (pageChangeR_ == false) {
				pageChangeR_ = true;
				spriteTransform2_.rotate.num[1] = 0.0f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
				startGameScene8 = true;
			}
			else {

			}
		}
	}
	if (count == 8) {
		if (input_->TriggerKey(DIK_SPACE)) {
			if (pageChangeR_ == false) {
				pageChangeR_ = true;
				spriteTransform2_.rotate.num[1] = 0.0f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
				startGameScene9 = true;
			}
			else {

			}
		}
	}
	if (count == 9) {
		if (input_->TriggerKey(DIK_SPACE)) {
			if (pageChangeR_ == false) {
				pageChangeR_ = true;
				spriteTransform2_.rotate.num[1] = 0.0f;
				audio_->SoundPlayWave(soundData1_, 0.5f, false);
				startGameScene10 = true;
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
	if (startGameScene6 == true && pageChangeR_ == false) {
		startGameScene6 = false;
		stageNo = 6;
		sceneNo = GAME_SCENE;
	}
	if (startGameScene7 == true && pageChangeR_ == false) {
		startGameScene7 = false;
		stageNo = 7;
		sceneNo = GAME_SCENE;
	}
	if (startGameScene8 == true && pageChangeR_ == false) {
		startGameScene8 = false;
		stageNo = 8;
		sceneNo = GAME_SCENE;
	}
	if (startGameScene9 == true && pageChangeR_ == false) {
		startGameScene9 = false;
		stageNo = 9;
		sceneNo = GAME_SCENE;
	}
	if (startGameScene10 == true && pageChangeR_ == false) {
		startGameScene10 = false;
		stageNo = 10;
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
		for (int i = 0; i < 10; i++) {
			if (count == i) {
				spriteSelect_[i]->Draw(spriteTransform_, SpriteuvTransform_, spriteMaterial_);
			}
		}
	}

#pragma endregion


#pragma region 3Dオブジェクト描画
	CJEngine_->PreDraw3D();
	if (pageChangeR_ == false && pageChangeL_ == false) {
		for (int i = 0; i < 10; i++) {
			if (count == i) {
				model_[i]->Draw(worldTransformModel_, viewProjection_, modelMaterial_);
			}
		}
	}
#pragma endregion
}

void GameSelectScene::Finalize() {
	audio_->SoundUnload(&soundData1_);
}
