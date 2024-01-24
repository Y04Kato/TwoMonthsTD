#include "Stage5Scene.h"
#include "components/utilities/globalVariables/GlobalVariables.h"

void Stage5Scene::Initialize() {
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

	const char* groupName = "Stage3Scene";
	GlobalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "Test", 90);

	// バック
	back_ = std::make_unique<Back>();
	back_->Initialize();

	// Stage3
	stage5_ = std::make_unique<Stage5>();
	stage5_->Initialize();

	// Player
	player_ = std::make_unique<Player>();
	player_->Initialize();

	player_->SetStartPoint(stage5_->GetStartPosX(), stage5_->GetStartPosY());

	numbers_.reset(new Numbers);
	numbers_->Initialize();
	numbers_->SetNum(stage5_->GetFoldCount());
	numbers_->SetInitialNum(stage5_->GetFoldCount());
	transformNumbers_.translate = { 950.0f,0.0f,0.0f };
	transformNumbers_.rotate = { 0.0f,0.0f,0.0f };
	transformNumbers_.scale = { 1.2f,0.12f,1.2f };
	numbers_->SetTransform(transformNumbers_);
}

void Stage5Scene::Update() {
	ApplyGlobalVariables();

	collisionManager_->ClearColliders();
	collisionManager_->CheckAllCollision();

	debugCamera_->Update();

	viewProjection_.translation_ = debugCamera_->GetViewProjection()->translation_;
	viewProjection_.rotation_ = debugCamera_->GetViewProjection()->rotation_;
	viewProjection_.UpdateMatrix();

	if (isParticleDraw_) {
		particle_->Update();
	}

	stage5_->Update();
	player_->Update();
	player_->SetNowMapState(stage5_->GetNowMapState(player_->GetPos()));
	player_->SetNowMapStatePos(stage5_->GetNowMapStatePosX(), stage5_->GetNowMapStatePosY());
	player_->SetPanelSize(stage5_->GetPanelSize());

	if (isGameStart == true) {
		stage5_->Reset();
		player_->ResetPlayer();
		player_->SetIsReset(false);
		isGameStart = false;
	}

	if (player_->GetIsReset() == true) {
		stage5_->Reset();
		player_->SetIsReset(false);
	}

	if (stage5_->GetClearFlag() == true) {
		isGameStart = true;
		player_->ResetPlayer();
		player_->SetIsReset(false);
		sceneNo = CLEAR_SCENE;
	}

	numbers_->SetNum(stage5_->GetFoldCount());
}

void Stage5Scene::Draw() {
#pragma region 背景スプライト描画
	CJEngine_->PreDraw2D();

	back_->Draw();
	stage5_->Draw();
	player_->Draw();
#pragma endregion

#pragma region 3Dオブジェクト描画
	CJEngine_->PreDraw3D();

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

void Stage5Scene::Finalize() {
	audio_->SoundUnload(&soundData1_);
}

void Stage5Scene::ApplyGlobalVariables() {
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "GamePlayScene";
}