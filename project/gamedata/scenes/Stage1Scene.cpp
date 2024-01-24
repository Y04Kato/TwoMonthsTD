#include "Stage1Scene.h"
#include "components/utilities/globalVariables/GlobalVariables.h"

void Stage1Scene::Initialize() {
	CJEngine_ = CitrusJunosEngine::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	// パーティクル
	testEmitter_.transform.translate = { 0.0f,0.0f,0.0f };
	testEmitter_.transform.rotate = { 0.0f,0.0f,0.0f };
	testEmitter_.transform.scale = { 1.0f,1.0f,1.0f };
	testEmitter_.count = 5;
	testEmitter_.frequency = 0.5f;//0.5秒ごとに発生
	testEmitter_.frequencyTime = 0.0f;//発生頻度の時刻

	accelerationField.acceleration = { 15.0f,0.0f,0.0f };
	accelerationField.area.min = { -1.0f,-1.0f,-1.0f };
	accelerationField.area.max = { 1.0f,1.0f,1.0f };

	particle_ = std::make_unique <CreateParticle>();
	particle_->Initialize(100, testEmitter_, accelerationField, particleResourceNum_);

	// Input
	input_ = Input::GetInstance();

	// Audio
	audio_ = Audio::GetInstance();
	soundData1_ = audio_->SoundLoadWave("project/gamedata/resources/task.wav");

	// 音声再生
	audio_->SoundPlayWave(soundData1_, 0.1f, false);

	// デバッグカメラの初期化
	debugCamera_ = DebugCamera::GetInstance();
	debugCamera_->initialize();

	viewProjection_.Initialize();

	// CollisionManager
	collisionManager_ = CollisionManager::GetInstance();

	GlobalVariables* globalVariables{};
	globalVariables = GlobalVariables::GetInstance();

	const char* groupName = "Stage1Scene";
	GlobalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "Test", 90);

	// バック
	back_ = std::make_unique<Back>();
	back_->Initialize();

	// Stage1
	stage1_ = std::make_unique<Stage1>();
	stage1_->Initialize();

	// Player
	player_ = std::make_unique<Player>();
	player_->Initialize();

	player_->SetStartPoint(stage1_->GetStartPosX(), stage1_->GetStartPosY());

	numbers_.reset(new Numbers);
	numbers_->Initialize();
	numbers_->SetNum(stage1_->GetFoldCount());
	numbers_->SetInitialNum(stage1_->GetFoldCount());
	transformNumbers_.translate = { 950.0f,0.0f,0.0f };
	transformNumbers_.rotate = { 0.0f,0.0f,0.0f };
	transformNumbers_.scale = { 1.2f,0.12f,1.2f };
	numbers_->SetTransform(transformNumbers_);
}

void Stage1Scene::Update() {
	ApplyGlobalVariables();

	collisionManager_->ClearColliders();
	collisionManager_->CheckAllCollision();

	debugCamera_->Update();

	viewProjection_.translation_ = debugCamera_->GetViewProjection()->translation_;
	viewProjection_.rotation_ = debugCamera_->GetViewProjection()->rotation_;
	viewProjection_.UpdateMatrix();

	stage1_->Update();
	player_->Update();
	player_->SetNowMapState(stage1_->GetNowMapState(player_->GetPos()));
	player_->SetNowMapStatePos(stage1_->GetNowMapStatePosX(), stage1_->GetNowMapStatePosY());
	player_->SetPanelSize(stage1_->GetPanelSize());

	if (isGameStart == true) {
		stage1_->Reset();
		player_->ResetPlayer();
		player_->SetIsReset(false);
		isGameStart = false;
	}

	if (player_->GetIsReset() == true) {
		stage1_->Reset();
		player_->SetIsReset(false);
	}

	if (stage1_->GetClearFlag() == true) {
		isGameStart = true;
		player_->ResetPlayer();
		player_->SetIsReset(false);
		sceneNo = CLEAR_SCENE;
	}

	numbers_->SetNum(stage1_->GetFoldCount());
}

void Stage1Scene::Draw() {
#pragma region 背景スプライト描画
	CJEngine_->PreDraw2D();

	back_->Draw();
	stage1_->Draw();
	player_->Draw();
#pragma endregion

#pragma region 3Dオブジェクト描画

#pragma endregion

#pragma region パーティクル描画
	CJEngine_->PreDrawParticle();

	if (isParticleDraw_) {
		particle_->Draw(viewProjection_);
	}

#pragma endregion

#pragma region 前景スプライト描画
	CJEngine_->PreDraw2D();

	numbers_->Draw();
#pragma endregion
}

void Stage1Scene::Finalize() {
	audio_->SoundUnload(&soundData1_);
}

void Stage1Scene::ApplyGlobalVariables() {
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "GamePlayScene";
}