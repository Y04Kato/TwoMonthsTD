#include "Stage3Scene.h"
#include "components/utilities/globalVariables/GlobalVariables.h"

void Stage3Scene::Initialize() {
	CJEngine_ = CitrusJunosEngine::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	//テクスチャ
	texture_ = 0;
	uiResourceNum_ = textureManager_->Load("project/gamedata/resources/ui.png");

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
		sprite_[i]->Initialize(Vector2{ 100.0f,100.0f }, uiResourceNum_, false, false);

		isSpriteDraw_[i] = false;
	}
	sprite_[0]->SetTextureInitialSize();
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
	particle_->Initialize(100, testEmitter_, accelerationField, particleResourceNum_);

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

	const char* groupName = "Stage3Scene";
	GlobalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "Test", 90);

	// バック
	back_ = std::make_unique<Back>();
	back_->Initialize();

	// Stage1
	stage3_ = std::make_unique<Stage3>();
	stage3_->Initialize();

	// Player
	player_ = std::make_unique<Player>();
	player_->Initialize();

	player_->SetStartPoint(stage3_->GetStartPosX(), stage3_->GetStartPosY());

	numbers_.reset(new Numbers);
	numbers_->Initialize();
	numbers_->SetNum(stage3_->GetFoldCount());
	numbers_->SetInitialNum(stage3_->GetFoldCount());
	transformNumbers_.translate = { 950.0f,0.0f,0.0f };
	transformNumbers_.rotate = { 0.0f,0.0f,0.0f };
	transformNumbers_.scale = { 1.2f,0.12f,1.2f };
	numbers_->SetTransform(transformNumbers_);
}

void Stage3Scene::Update() {

	ApplyGlobalVariables();

	collisionManager_->ClearColliders();
	collisionManager_->CheckAllCollision();

	debugCamera_->Update();

	viewProjection_.translation_ = debugCamera_->GetViewProjection()->translation_;
	viewProjection_.rotation_ = debugCamera_->GetViewProjection()->rotation_;
	viewProjection_.UpdateMatrix();

	/*if (input_->PressKey(DIK_A)) {
		OutputDebugStringA("Press A\n");
	}
	if (input_->ReleaseKey(DIK_S)) {
		OutputDebugStringA("Release S\n");
	}
	if (input_->TriggerKey(DIK_D)) {
		OutputDebugStringA("Trigger D\n");
	}*/

	for (int i = 0; i < 2; i++) {
		worldTransformTriangle_[i].UpdateMatrix();
	}
	worldTransformSphere_.UpdateMatrix();
	worldTransformModel_.UpdateMatrix();

	ImGui::Begin("debug");
	ImGui::Text("Stage1Scene");
	if (ImGui::TreeNode("Triangle")) {//三角形
		if (ImGui::Button("DrawTriangle1")) {
			if (isTriangleDraw_[0] == false) {
				isTriangleDraw_[0] = true;
			}
			else {
				isTriangleDraw_[0] = false;
			}
		}
		if (ImGui::Button("DrawTriangle2")) {
			if (isTriangleDraw_[1] == false) {
				isTriangleDraw_[1] = true;
			}
			else {
				isTriangleDraw_[1] = false;
			}
		}
		if (isTriangleDraw_[0] == true) {
			if (ImGui::TreeNode("Triangle1")) {
				ImGui::DragFloat3("Translate", worldTransformTriangle_[0].translation_.num, 0.05f);
				ImGui::DragFloat3("Rotate", worldTransformTriangle_[0].rotation_.num, 0.05f);
				ImGui::DragFloat2("Scale", worldTransformTriangle_[0].scale_.num, 0.05f);
				ImGui::ColorEdit4("", triangleMaterial_[0].num, 0);
				ImGui::TreePop();
			}
		}
		if (isTriangleDraw_[1] == true) {
			if (ImGui::TreeNode("Triangle2")) {
				ImGui::DragFloat3("Translate", worldTransformTriangle_[1].translation_.num, 0.05f);
				ImGui::DragFloat3("Rotate", worldTransformTriangle_[1].rotation_.num, 0.05f);
				ImGui::DragFloat2("Scale", worldTransformTriangle_[1].scale_.num, 0.05f);
				ImGui::ColorEdit4("", triangleMaterial_[1].num, 0);
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Sphere")) {//球体
		if (ImGui::Button("DrawSphere")) {
			if (isSphereDraw_ == false) {
				isSphereDraw_ = true;
			}
			else {
				isSphereDraw_ = false;
			}
		}
		ImGui::DragFloat3("Translate", worldTransformSphere_.translation_.num, 0.05f);
		ImGui::DragFloat3("Rotate", worldTransformSphere_.rotation_.num, 0.05f);
		ImGui::DragFloat3("Scale", worldTransformSphere_.scale_.num, 0.05f);
		ImGui::ColorEdit4("", sphereMaterial_.num, 0);
		ImGui::SliderInt("ChangeTexture", &texture_, 0, 1);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Sprite")) {//スプライト
		if (ImGui::Button("DrawSprite1")) {
			if (isSpriteDraw_[0] == false) {
				isSpriteDraw_[0] = true;
			}
			else {
				isSpriteDraw_[0] = false;
			}
		}
		if (ImGui::Button("DrawSprite2")) {
			if (isSpriteDraw_[1] == false) {
				isSpriteDraw_[1] = true;
			}
			else {
				isSpriteDraw_[1] = false;
			}
		}
		if (isSpriteDraw_[0] == true) {
			if (ImGui::TreeNode("Sprite1")) {
				ImGui::DragFloat2("Translate", spriteTransform_[0].translate.num, 0.05f);
				ImGui::DragFloat3("Rotate", spriteTransform_[0].rotate.num, 0.05f);
				ImGui::DragFloat2("Scale", spriteTransform_[0].scale.num, 0.05f);
				ImGui::ColorEdit4("", spriteMaterial_[0].num, 0);
				ImGui::DragFloat2("uvScale", SpriteuvTransform_[0].scale.num, 0.1f);
				ImGui::DragFloat3("uvTranslate", SpriteuvTransform_[0].translate.num, 0.1f);
				ImGui::DragFloat("uvRotate", &SpriteuvTransform_[0].rotate.num[2], 0.1f);
				ImGui::TreePop();
			}
		}
		if (isSpriteDraw_[1] == true) {
			if (ImGui::TreeNode("Sprite2")) {
				ImGui::DragFloat2("Translate", spriteTransform_[1].translate.num, 0.05f);
				ImGui::DragFloat3("Rotate", spriteTransform_[1].rotate.num, 0.05f);
				ImGui::DragFloat2("Scale", spriteTransform_[1].scale.num, 0.05f);
				ImGui::ColorEdit4("", spriteMaterial_[1].num, 0);
				ImGui::DragFloat2("uvScale", SpriteuvTransform_[1].scale.num, 0.1f);
				ImGui::DragFloat3("uvTranslate", SpriteuvTransform_[1].translate.num, 0.1f);
				ImGui::DragFloat("uvRotate", &SpriteuvTransform_[1].rotate.num[2], 0.1f);
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Model")) {//objモデル
		if (ImGui::Button("DrawModel")) {
			if (isModelDraw_ == false) {
				isModelDraw_ = true;
			}
			else {
				isModelDraw_ = false;
			}
		}
		ImGui::DragFloat3("Translate", worldTransformModel_.translation_.num, 0.05f);
		ImGui::DragFloat3("Rotate", worldTransformModel_.rotation_.num, 0.05f);
		ImGui::DragFloat3("Scale", worldTransformModel_.scale_.num, 0.05f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Particle")) {//パーティクル
		if (ImGui::Button("DrawParticle")) {
			if (isParticleDraw_ == false) {
				isParticleDraw_ = true;
			}
			else {
				isParticleDraw_ = false;
			}
		}
		ImGui::TreePop();
	}

	ImGui::Text("%f", ImGui::GetIO().Framerate);

	ImGui::End();
	if (isParticleDraw_) {
		particle_->Update();
	}

	stage3_->Update();
	player_->Update();
	player_->SetNowMapState(stage3_->GetNowMapState(player_->GetPos()));
	player_->SetNowMapStatePos(stage3_->GetNowMapStatePosX(), stage3_->GetNowMapStatePosY());
	player_->SetPanelSize(stage3_->GetPanelSize());

	if (isGameStart == true) {
		stage3_->Reset();
		player_->ResetPlayer();
		player_->SetIsReset(false);
		isGameStart = false;
	}

	if (player_->GetIsReset() == true) {
		stage3_->Reset();
		player_->SetIsReset(false);
	}

	if (stage3_->GetClearFlag() == true) {
		isGameStart = true;
		player_->ResetPlayer();
		player_->SetIsReset(false);
		sceneNo = CLEAR_SCENE;
	}

	numbers_->SetNum(stage3_->GetFoldCount());
}

void Stage3Scene::Draw() {
#pragma region 背景スプライト描画
	CJEngine_->PreDraw2D();

	for (int i = 0; i < 2; i++) {
		if (isSpriteDraw_[i]) {//Sprite描画
			sprite_[i]->Draw(spriteTransform_[i], SpriteuvTransform_[i], spriteMaterial_[i]);
		}
	}

	back_->Draw();
	stage3_->Draw();
	player_->Draw();
#pragma endregion

#pragma region 3Dオブジェクト描画
	CJEngine_->PreDraw3D();

	if (isTriangleDraw_[0]) {//Triangle描画
		triangle_[0]->Draw(worldTransformTriangle_[0], viewProjection_, triangleMaterial_[0], uiResourceNum_);
	}
	if (isTriangleDraw_[1]) {//Triangle描画
		triangle_[1]->Draw(worldTransformTriangle_[1], viewProjection_, triangleMaterial_[1], uiResourceNum_);
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

	numbers_->Draw();
	sprite_[0]->Draw(spriteTransform_[0], SpriteuvTransform_[0], spriteMaterial_[0]);

#pragma endregion
}

void Stage3Scene::Finalize() {
	audio_->SoundUnload(&soundData1_);
}

void Stage3Scene::ApplyGlobalVariables() {
	GlobalVariables* globalVariables = GlobalVariables::GetInstance();
	const char* groupName = "Stage1Scene";
}