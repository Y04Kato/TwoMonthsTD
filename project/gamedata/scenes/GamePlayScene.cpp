#include "GamePlayScene.h"
#include "components/utilities/globalVariables/GlobalVariables.h"

void GamePlayScene::Initialize() {
	CJEngine_ = CitrusJunosEngine::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	//テクスチャ
	texture_ = 0;
	uvResourceNum_ = textureManager_->Load("project/gamedata/resources/uvChecker.png");

	monsterBallResourceNum_ = textureManager_->Load("project/gamedata/resources/monsterBall.png");

	particleResourceNum_ = textureManager_->Load("project/gamedata/resources/circle.png");

	//三角形
	for (int i = 0; i < 2; i++) {
		triangle_[i] = std::make_unique <CreateTriangle>();
		triangle_[i]->Initialize();
		worldTransformTriangle_[i].Initialize();
		triangleMaterial_[i] = { 1.0f,1.0f,1.0f,1.0f };
		isTriangleDraw_[i] = false;
	}

	worldTransformTriangle_[1].rotation_.num[1] = 0.7f;

	//スプライト
	for (int i = 0; i < 2; i++) {
		spriteMaterial_[i] = { 1.0f,1.0f,1.0f,1.0f };
		spriteTransform_[i] = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
		SpriteuvTransform_[i] = {
			{1.0f,1.0f,1.0f},
			{0.0f,0.0f,0.0f},
			{0.0f,0.0f,0.0f},
		};
		sprite_[i] = std::make_unique <CreateSprite>();
		sprite_[i]->Initialize(Vector2{ 100.0f,100.0f }, uvResourceNum_, true, true);

		isSpriteDraw_[i] = false;
	}
	sprite_[0]->SetTextureLTSize(Vector2{ 0.0f,0.0f }, Vector2{ 50.0f,50.0f });
	sprite_[0]->SetAnchor(Vector2{ 0.5f,0.5f });
	sprite_[1]->SetTextureInitialSize();

	//パーティクル
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
	particle_->Initialize(100,testEmitter_,accelerationField, particleResourceNum_);

	//球体
	sphere_ = std::make_unique <CreateSphere>();
	sphere_->Initialize();
	worldTransformSphere_.Initialize();
	sphereMaterial_ = { 1.0f,1.0f,1.0f,1.0f };

	isSphereDraw_ = false;
	
	//objモデル
	model_.reset(Model::CreateModelFromObj("project/gamedata/resources/fence", "fence.obj"));
	worldTransformModel_.Initialize();
	modelMaterial_ = { 1.0f,1.0f,1.0f,1.0f };

	//Input
	input_ = Input::GetInstance();

	//Audio
	audio_ = Audio::GetInstance();
	soundData1_ = audio_->SoundLoadWave("project/gamedata/resources/task.wav");
	//音声再生
	audio_->SoundPlayWave(soundData1_, 0.1f, false);

	// デバッグカメラの初期化
	debugCamera_ = DebugCamera::GetInstance();
	debugCamera_->initialize();

	viewProjection_.Initialize();

	//CollisionManager
	collisionManager_ = CollisionManager::GetInstance();

	GlobalVariables* globalVariables{};
	globalVariables = GlobalVariables::GetInstance();

	const char* groupName = "GamePlayScene";
	GlobalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "Test", 90);

	// バック
	back_ = std::make_unique<Back>();
	back_->Initialize();

	// Player
	player_ = std::make_unique<Player>();
	player_->Initialize();

	// Stage1
	stage1_ = std::make_unique<Stage1>();
	stage1_->Initialize();

	// Stage2
	stage2_ = std::make_unique<Stage2>();
	stage2_->Initialize();

	// Stage3
	stage3_ = std::make_unique<Stage3>();
	stage3_->Initialize();

	// Stage4
	stage4_ = std::make_unique<Stage4>();
	stage4_->Initialize();

	// Stage5
	stage5_ = std::make_unique<Stage5>();
	stage5_->Initialize();
}

void GamePlayScene::Update() {

	ApplyGlobalVariables();

	collisionManager_->ClearColliders();
	collisionManager_->CheckAllCollision();

	debugCamera_->Update();

	viewProjection_.translation_ = debugCamera_->GetViewProjection()->translation_;
	viewProjection_.rotation_ = debugCamera_->GetViewProjection()->rotation_;
	viewProjection_.UpdateMatrix();

	for (int i = 0; i < 2; i++) {
		worldTransformTriangle_[i].UpdateMatrix();
	}
	worldTransformSphere_.UpdateMatrix();
	worldTransformModel_.UpdateMatrix();

	if (isParticleDraw_) {
		particle_->Update();
	}

	// ステージ更新処理
	stage4_->Update();
	player_->Update();
	player_->SetNowMapState(stage4_->GetNowMapState(player_->GetPos()));
	player_->SetNowMapStatePos(stage4_->GetNowMapStatePosX(), stage4_->GetNowMapStatePosY());
	player_->SetPanelSize(stage4_->GetPanelSize());
}

void GamePlayScene::Draw() {
#pragma region 背景スプライト描画
	CJEngine_->PreDraw2D();

	for (int i = 0; i < 2; i++) {
		if (isSpriteDraw_[i]) {//Sprite描画
			sprite_[i]->Draw(spriteTransform_[i], SpriteuvTransform_[i], spriteMaterial_[i]);
		}
	}

	// 背景描画
	back_->Draw();

	// ステージ描画
	stage4_->Draw();

	// プレイヤー描画
	player_->Draw();

#pragma endregion

#pragma region 3Dオブジェクト描画
	CJEngine_->PreDraw3D();

	if (isTriangleDraw_[0]) {//Triangle描画
		triangle_[0]->Draw(worldTransformTriangle_[0], viewProjection_, triangleMaterial_[0], uvResourceNum_);
	}
	if (isTriangleDraw_[1]) {//Triangle描画
		triangle_[1]->Draw(worldTransformTriangle_[1], viewProjection_, triangleMaterial_[1], uvResourceNum_);
	}

	if (isSphereDraw_) {
		sphere_->Draw(worldTransformSphere_, viewProjection_, sphereMaterial_, texture_);
	}

	if (isModelDraw_) {
		model_->Draw(worldTransformModel_, viewProjection_, modelMaterial_);
	}
#pragma endregion

#pragma region パーティクル描画
	CJEngine_->PreDrawParticle();

	if (isParticleDraw_) {
		particle_->Draw(viewProjection_);
	}

#pragma endregion

#pragma region 前景スプライト描画
	CJEngine_->PreDraw2D();

#pragma endregion
}

void GamePlayScene::Finalize() {
	audio_->SoundUnload(&soundData1_);
}

void GamePlayScene::ApplyGlobalVariables() {
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "GamePlayScene";
}