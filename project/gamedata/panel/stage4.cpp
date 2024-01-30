#include "stage4.h"

void Stage4::Initialize() {
	input_ = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	spriteTexture_[0] = textureManager_->Load("project/gamedata/resources/panel/none.png");
	spriteTexture_[1] = textureManager_->Load("project/gamedata/resources/panel/panel0.png");
	spriteTexture_[2] = textureManager_->Load("project/gamedata/resources/panel/panel1.png");
	spriteTexture_[3] = textureManager_->Load("project/gamedata/resources/panel/panel2.png");
	spriteTexture_[4] = textureManager_->Load("project/gamedata/resources/panel/panel3.png");
	spriteTexture_[5] = textureManager_->Load("project/gamedata/resources/panel/panel4.png");
	spriteTexture_[6] = textureManager_->Load("project/gamedata/resources/panel/panel5.png");
	spriteTexture_[7] = textureManager_->Load("project/gamedata/resources/panel/panel6.png");

	spriteTextureE_[0] = textureManager_->Load("project/gamedata/resources/panel/startPoint.png");
	spriteTextureE_[1] = textureManager_->Load("project/gamedata/resources/panel/goalPoint.png");
	spriteTextureE_[2] = textureManager_->Load("project/gamedata/resources/panel/passedGoalPoint.png");

	for (int i = 0; i < kMapHeight * kMapWidth; i++) {
		sprite_[i].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[0], false, false));
		sprite_[i]->SetTextureInitialSize();

		sprite1_[i].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[1], false, false));
		sprite1_[i]->SetTextureInitialSize();

		sprite2_[i].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[2], false, false));
		sprite2_[i]->SetTextureInitialSize();

		sprite3_[i].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[3], false, false));
		sprite3_[i]->SetTextureInitialSize();

		sprite4_[i].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[4], false, false));
		sprite4_[i]->SetTextureInitialSize();

		sprite5_[i].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[5], false, false));
		sprite5_[i]->SetTextureInitialSize();

		sprite6_[i].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[6], false, false));
		sprite6_[i]->SetTextureInitialSize();

		sprite7_[i].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[7], false, false));
		sprite7_[i]->SetTextureInitialSize();

		spriteStart_[i].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTextureE_[0], false, false));
		spriteStart_[i]->SetTextureInitialSize();

		spriteGoal_[i].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTextureE_[1], false, false));
		spriteGoal_[i]->SetTextureInitialSize();

		spriteCheckGoal_[i].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTextureE_[2], false, false));
		spriteCheckGoal_[i]->SetTextureInitialSize();
	}

	for (int i = 0; i < 7; i++) {
		spriteTest_[i].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[i + 1], false, false));
		spriteTest_[i]->SetTextureInitialSize();
	}

	texture_ = textureManager_->Load("project/gamedata/resources/panel/select.png");
	selectSprite_.reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, texture_, false, false));
	selectSprite_->SetTextureInitialSize();
	transform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	spriteTextureD_[0] = textureManager_->Load("project/gamedata/resources/panel/directionUp.png");
	spriteTextureD_[1] = textureManager_->Load("project/gamedata/resources/panel/directionDown.png");
	spriteTextureD_[2] = textureManager_->Load("project/gamedata/resources/panel/directionLeft.png");
	spriteTextureD_[3] = textureManager_->Load("project/gamedata/resources/panel/directionRight.png");

	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };
	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
	for (int i = 0; i < kMapHeight; i++) {
		for (int j = 0; j < kMapWidth; j++) {
			map[i][j].spriteMaterial = { 1.0f,1.0f,1.0f,1.0f };
		}
	}
}

void Stage4::Update() {
	Select();
	Fold();

	if (map[playerStatePosY_][playerStatePosX_].event == Event::Goal) {
		map[playerStatePosY_][playerStatePosX_].event = Event::CheckGoal;
		CheckGoalCount_++;
	}

	if (goalCount_ == CheckGoalCount_) {
		isGameClear_ = true;
	}

	ImGui::Begin("stage");
	ImGui::Text("GoalCount : %d / %d", CheckGoalCount_, goalCount_);
	ImGui::End();

	transform_.translate = { selectPoint_.num[0] * panelSize_.num[0],selectPoint_.num[1] * panelSize_.num[1] ,0.0f };
}

void Stage4::Draw() {
	int test = 0;
	for (int i = 0; i < kMapHeight; i++) {
		for (int j = 0; j < kMapWidth; j++) {
			//パネル描画
			if (map[i][j].mapstate == MapState::None && map[i][j].isFold_ == true) {

			}
			if (map[i][j].mapstate == MapState::Vertical) {
				sprite1_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}
			if (map[i][j].mapstate == MapState::Side) {
				sprite2_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}
			if (map[i][j].mapstate == MapState::Cross) {
				sprite3_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}
			if (map[i][j].mapstate == MapState::TShapedTop) {
				sprite4_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}
			if (map[i][j].mapstate == MapState::TShapedDown) {
				sprite5_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}
			if (map[i][j].mapstate == MapState::TShapedLeft) {
				sprite6_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}
			if (map[i][j].mapstate == MapState::TShapedRight) {
				sprite7_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}

			test++;
		}
	}

	test = 0;
	for (int i = 0; i < kMapHeight; i++) {
		for (int j = 0; j < kMapWidth; j++) {
			if (map[i][j].event == Event::None) {

			}
			if (map[i][j].event == Event::Start) {
				spriteStart_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}
			if (map[i][j].event == Event::Goal) {
				spriteGoal_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}
			if (map[i][j].event == Event::CheckGoal) {
				spriteCheckGoal_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}

			test++;
		}
	}

	//折る演出用
	if (drawTest_ == true) {
		if (mapstate_ == MapState::None) {

		}
		if (mapstate_ == MapState::Vertical) {
			spriteTest_[0]->Draw(Transform{ transformTest_.scale,transformTest_.rotate,{transformTest_.translate.num[0] + playerPos_.num[0],transformTest_.translate.num[1] + playerPos_.num[1] ,transformTest_.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
		}
		if (mapstate_ == MapState::Side) {
			spriteTest_[1]->Draw(Transform{ transformTest_.scale,transformTest_.rotate,{transformTest_.translate.num[0] + playerPos_.num[0],transformTest_.translate.num[1] + playerPos_.num[1] ,transformTest_.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
		}
		if (mapstate_ == MapState::Cross) {
			spriteTest_[2]->Draw(Transform{ transformTest_.scale,transformTest_.rotate,{transformTest_.translate.num[0] + playerPos_.num[0],transformTest_.translate.num[1] + playerPos_.num[1] ,transformTest_.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
		}
		if (mapstate_ == MapState::TShapedTop) {
			spriteTest_[3]->Draw(Transform{ transformTest_.scale,transformTest_.rotate,{transformTest_.translate.num[0] + playerPos_.num[0],transformTest_.translate.num[1] + playerPos_.num[1] ,transformTest_.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
		}
		if (mapstate_ == MapState::TShapedDown) {
			spriteTest_[4]->Draw(Transform{ transformTest_.scale,transformTest_.rotate,{transformTest_.translate.num[0] + playerPos_.num[0],transformTest_.translate.num[1] + playerPos_.num[1] ,transformTest_.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
		}
		if (mapstate_ == MapState::TShapedLeft) {
			spriteTest_[5]->Draw(Transform{ transformTest_.scale,transformTest_.rotate,{transformTest_.translate.num[0] + playerPos_.num[0],transformTest_.translate.num[1] + playerPos_.num[1] ,transformTest_.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
		}
		if (mapstate_ == MapState::TShapedRight) {
			spriteTest_[6]->Draw(Transform{ transformTest_.scale,transformTest_.rotate,{transformTest_.translate.num[0] + playerPos_.num[0],transformTest_.translate.num[1] + playerPos_.num[1] ,transformTest_.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
		}
	}

	test = 0;
	for (int i = 0; i < kMapHeight; i++) {
		for (int j = 0; j < kMapWidth; j++) {
			//折り矢印描画
			if (map[i][j].direction == Direction::None) {

			}
			if (map[i][j].direction == Direction::Up) {
				spriteD1_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}
			if (map[i][j].direction == Direction::Down) {
				spriteD2_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}
			if (map[i][j].direction == Direction::Left) {
				spriteD3_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}
			if (map[i][j].direction == Direction::Right) {
				spriteD4_[test]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, map[i][j].spriteMaterial);
			}

			test++;
		}
	}

	//パネル選択カーソル描画
	selectSprite_->Draw(Transform{ transform_.scale,transform_.rotate,{transform_.translate.num[0] + playerPos_.num[0],transform_.translate.num[1] + playerPos_.num[1] ,transform_.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
}

void Stage4::LoadMap() {
	FILE* fp = nullptr;

	std::string fullPath = "project/gamedata/resources/csv/Map" + std::string(stageNum_) + "Panel.csv";
	auto&& stringPath = ConvertString(fullPath);
	size_t len = stringPath.length() + 1;
	std::vector<char> testPath;
	testPath.resize(len);

	std::size_t convertedChars = 0;
	wcstombs_s(&convertedChars, testPath.data(), len, stringPath.c_str(), _TRUNCATE);
	const std::string& testResult = testPath.data();
	const char* fname[] = { testResult.c_str() };

	errno_t err;
	err = fopen_s(&fp, *fname, "r");
	for (int i = 0; i < kMapHeight; i++) {
		for (int j = 0; j < kMapWidth; j++) {
			fscanf_s(fp, "%d,", &map[i][j].mapstate);//パネル情報読み込み
			map[i][j].transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{j * panelSize_.num[0],i * panelSize_.num[1],0.0f} };
			map[i][j].isFold_ = false;
			map[i][j].previousFoldChack = false;
			map[i][j].previousMapstate = MapState::None;
			map[i][j].previousMapstateUp = MapState::None;
			map[i][j].previousMapstateDown = MapState::None;
			map[i][j].previousMapstateLeft = MapState::None;
			map[i][j].previousMapstateRight = MapState::None;
		}
	}

	fclose(fp);

	LoadDirection();
}

void Stage4::LoadDirection() {
	int test = 0;
	FILE* fp = nullptr;

	std::string fullPath = "project/gamedata/resources/csv/Map" + std::string(stageNum_) + "Direction.csv";
	auto&& stringPath = ConvertString(fullPath);
	size_t len = stringPath.length() + 1;
	std::vector<char> testPath;
	testPath.resize(len);

	std::size_t convertedChars = 0;
	wcstombs_s(&convertedChars, testPath.data(), len, stringPath.c_str(), _TRUNCATE);
	const std::string& testResult = testPath.data();
	const char* fname[] = { testResult.c_str() };

	errno_t err;
	err = fopen_s(&fp, *fname, "r");
	for (int i = 0; i < kMapHeight; i++) {
		for (int j = 0; j < kMapWidth; j++) {
			fscanf_s(fp, "%d,", &map[i][j].direction);
			if (map[i][j].direction == Direction::None) {
				sprite1_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite2_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite3_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite4_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite5_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite6_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite7_[test]->SetAnchor(Vector2{ 0.0f,0.0f });

				spriteStart_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				spriteGoal_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				spriteCheckGoal_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
			}

			if (map[i][j].direction == Direction::Up) {
				spriteD1_[test].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTextureD_[0], false, false));
				spriteD1_[test]->SetTextureInitialSize();
				sprite_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite1_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite2_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite3_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite4_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite5_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite6_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite7_[test]->SetAnchor(Vector2{ 0.0f,0.0f });

				spriteStart_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				spriteGoal_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				spriteCheckGoal_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
			}

			if (map[i][j].direction == Direction::Down) {
				spriteD2_[test].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTextureD_[1], false, false));
				spriteD2_[test]->SetTextureInitialSize();
				spriteD2_[test]->SetAnchor(Vector2{ 0.0f,1.0f });
				map[i][j].transform.translate.num[1] += panelSize_.num[1];
				//下方向に折る為にパネルのアンカーを設定
				sprite_[test]->SetAnchor(Vector2{ 0.0f,1.0f });
				sprite1_[test]->SetAnchor(Vector2{ 0.0f,1.0f });
				sprite2_[test]->SetAnchor(Vector2{ 0.0f,1.0f });
				sprite3_[test]->SetAnchor(Vector2{ 0.0f,1.0f });
				sprite4_[test]->SetAnchor(Vector2{ 0.0f,1.0f });
				sprite5_[test]->SetAnchor(Vector2{ 0.0f,1.0f });
				sprite6_[test]->SetAnchor(Vector2{ 0.0f,1.0f });
				sprite7_[test]->SetAnchor(Vector2{ 0.0f,1.0f });

				spriteStart_[test]->SetAnchor(Vector2{ 0.0f,1.0f });
				spriteGoal_[test]->SetAnchor(Vector2{ 0.0f,1.0f });
				spriteCheckGoal_[test]->SetAnchor(Vector2{ 0.0f,1.0f });
			}

			if (map[i][j].direction == Direction::Left) {
				spriteD3_[test].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTextureD_[2], false, false));
				spriteD3_[test]->SetTextureInitialSize();
				sprite_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite1_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite2_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite3_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite4_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite5_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite6_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				sprite7_[test]->SetAnchor(Vector2{ 0.0f,0.0f });

				spriteStart_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				spriteGoal_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
				spriteCheckGoal_[test]->SetAnchor(Vector2{ 0.0f,0.0f });
			}

			if (map[i][j].direction == Direction::Right) {
				spriteD4_[test].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTextureD_[3], false, false));
				spriteD4_[test]->SetTextureInitialSize();
				spriteD4_[test]->SetAnchor(Vector2{ 1.0f,0.0f });
				map[i][j].transform.translate.num[0] += panelSize_.num[0];
				//右方向に折る為にパネルのアンカーを設定
				sprite_[test]->SetAnchor(Vector2{ 1.0f,0.0f });
				sprite1_[test]->SetAnchor(Vector2{ 1.0f,0.0f });
				sprite2_[test]->SetAnchor(Vector2{ 1.0f,0.0f });
				sprite3_[test]->SetAnchor(Vector2{ 1.0f,0.0f });
				sprite4_[test]->SetAnchor(Vector2{ 1.0f,0.0f });
				sprite5_[test]->SetAnchor(Vector2{ 1.0f,0.0f });
				sprite6_[test]->SetAnchor(Vector2{ 1.0f,0.0f });
				sprite7_[test]->SetAnchor(Vector2{ 1.0f,0.0f });

				spriteStart_[test]->SetAnchor(Vector2{ 1.0f,0.0f });
				spriteGoal_[test]->SetAnchor(Vector2{ 1.0f,0.0f });
				spriteCheckGoal_[test]->SetAnchor(Vector2{ 1.0f,0.0f });
			}

			test++;
		}
	}

	fclose(fp);

	LoadEvent();
}

void Stage4::LoadEvent() {
	FILE* fp = nullptr;

	std::string fullPath = "project/gamedata/resources/csv/Map" + std::string(stageNum_) + "Event.csv";
	auto&& stringPath = ConvertString(fullPath);
	size_t len = stringPath.length() + 1;
	std::vector<char> testPath;
	testPath.resize(len);

	std::size_t convertedChars = 0;
	wcstombs_s(&convertedChars, testPath.data(), len, stringPath.c_str(), _TRUNCATE);
	const std::string& testResult = testPath.data();
	const char* fname[] = { testResult.c_str() };

	errno_t err;
	err = fopen_s(&fp, *fname, "r");
	for (int i = 0; i < kMapHeight; i++) {
		for (int j = 0; j < kMapWidth; j++) {
			fscanf_s(fp, "%d,", &map[i][j].event);
			if (map[i][j].event == Event::Start) {
				startPointX_ = j;
				startPointY_ = i;
			}
			if (map[i][j].event == Event::Goal) {
				goalCount_++;
			}
		}
	}

	//delete[] testPath;

	fclose(fp);
}

void Stage4::Select() {
	if (input_->TriggerKey(DIK_RIGHT) && isFoldMove_ == false) {
		selectPoint_.num[0] += 1;
		if (selectPoint_.num[0] >= MapSelectSizeX_) {
			selectPoint_.num[0] = 0;
		}
	}
	if (input_->TriggerKey(DIK_LEFT) && isFoldMove_ == false) {
		selectPoint_.num[0] -= 1;
		if (selectPoint_.num[0] < 0) {
			selectPoint_.num[0] = MapSelectSizeX_ - 1;
		}
	}
	if (input_->TriggerKey(DIK_UP) && isFoldMove_ == false) {
		selectPoint_.num[1] -= 1;
		if (selectPoint_.num[1] < 0) {
			selectPoint_.num[1] = MapSelectSizeY_ - 1;
		}
	}
	if (input_->TriggerKey(DIK_DOWN) && isFoldMove_ == false) {
		selectPoint_.num[1] += 1;
		if (selectPoint_.num[1] >= MapSelectSizeY_) {
			selectPoint_.num[1] = 0;
		}
	}

	if (input_->TriggerKey(DIK_SPACE)) {//折る
		if (playerStatePosX_ == (int)selectPoint_.num[0] && playerStatePosY_ == (int)selectPoint_.num[1]) {

		}
		else {//自機が折るパネルの上に居なければ
			if (0 < foldCount_ && isFoldMove_ == false) {//折った回数が上限に満たなければ
				isFoldMove_ = true;
				setPlayerStatePosX_ = playerStatePosX_;
				setPlayerStatePosY_ = playerStatePosY_;
			}
		}
	}
}

void Stage4::Fold() {
	if (isFoldMove_ == true) {
		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::None) {//折れない
			isFoldMove_ = false;
		}

		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::Up) {//上に折る
			if (setPlayerStatePosX_ == (int)selectPoint_.num[0] && setPlayerStatePosY_ == (int)selectPoint_.num[1] - 1) {
				isFoldMove_ = false;
			}
			else {//自機が折るパネルの先に居なければ
				if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ == false) {//折り
					FoldDirecting(1, false);//折る演出

					if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack == false) {//今のパネルを記憶する
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate;
						map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].previousMapstateUp = map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].mapstate;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack = true;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate = MapState::None;
						foldCount_--;
					}

					if (drawTest_ == false) {
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::Vertical) {
							map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].mapstate = MapState::Vertical;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::Side) {
							map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].mapstate = MapState::Side;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::Cross) {
							map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].mapstate = MapState::Cross;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedTop) {
							map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].mapstate = MapState::TShapedDown;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedDown) {
							map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].mapstate = MapState::TShapedTop;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedLeft) {
							map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].mapstate = MapState::TShapedLeft;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedRight) {
							map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].mapstate = MapState::TShapedRight;
						}
					}
				}

				if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ == true && isFoldMove_ == true) {//折り返し
					FoldDirecting(1, true);//折る演出
					map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].mapstate = map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].previousMapstateUp;

					if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack == true) {
						foldCount_--;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack = false;
					}

					if (drawTest_ == false) {
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate;

						isFoldMove_ = false;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = false;

						//記憶したパネル情報の初期化
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate = MapState::None;
						map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].previousMapstateUp = MapState::None;
					}
				}
			}
		}

		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::Down) {//下に折る
			if (setPlayerStatePosX_ == (int)selectPoint_.num[0] && setPlayerStatePosY_ == (int)selectPoint_.num[1] + 1) {
				isFoldMove_ = false;
			}
			else {//自機が折るパネルの先に居なければ
				if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ == false) {//折り
					FoldDirecting(2, false);//折る演出

					if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack == false) {//今のパネルを記憶する
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate;
						map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].previousMapstateDown = map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].mapstate;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack = true;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate = MapState::None;
						foldCount_--;
					}

					if (drawTest_ == false) {
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::Vertical) {
							map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].mapstate = MapState::Vertical;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::Side) {
							map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].mapstate = MapState::Side;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::Cross) {
							map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].mapstate = MapState::Cross;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedTop) {
							map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].mapstate = MapState::TShapedDown;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedDown) {
							map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].mapstate = MapState::TShapedTop;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedLeft) {
							map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].mapstate = MapState::TShapedLeft;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedRight) {
							map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].mapstate = MapState::TShapedRight;
						}
					}
				}

				if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ == true && isFoldMove_ == true) {//折り返し
					FoldDirecting(2, true);//折る演出
					map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].mapstate = map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].previousMapstateDown;

					if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack == true) {
						foldCount_--;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack = false;
					}

					if (drawTest_ == false) {
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate;

						isFoldMove_ = false;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = false;

						//記憶したパネル情報の初期化
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate = MapState::None;
						map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].previousMapstateDown = MapState::None;
					}
				}
			}
		}

		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::Left) {//左に折る
			if (setPlayerStatePosX_ == (int)selectPoint_.num[0] - 1 && setPlayerStatePosY_ == (int)selectPoint_.num[1]) {
				isFoldMove_ = false;
			}
			else {//自機が折るパネルの先に居なければ
				if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ == false) {//折り
					FoldDirecting(3, false);//折る演出
					if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack == false) {//今のパネルを記憶する
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].previousMapstateLeft = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].mapstate;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack = true;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate = MapState::None;
						foldCount_--;
					}

					if (drawTest_ == false) {
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::Vertical) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].mapstate = MapState::Vertical;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::Side) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].mapstate = MapState::Side;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::Cross) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].mapstate = MapState::Cross;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedTop) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].mapstate = MapState::TShapedTop;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedDown) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].mapstate = MapState::TShapedDown;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedLeft) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].mapstate = MapState::TShapedRight;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedRight) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].mapstate = MapState::TShapedLeft;
						}
					}
				}

				if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ == true && isFoldMove_ == true) {//折り返し
					FoldDirecting(3, true);//折る演出
					map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].mapstate = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].previousMapstateLeft;

					if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack == true) {
						foldCount_--;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack = false;
					}

					if (drawTest_ == false) {
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate;

						isFoldMove_ = false;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = false;

						//記憶したパネル情報の初期化
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate = MapState::None;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].previousMapstateDown = MapState::None;
					}
				}
			}
		}

		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::Right) {//右に折る
			if (setPlayerStatePosX_ == (int)selectPoint_.num[0] + 1 && setPlayerStatePosY_ == (int)selectPoint_.num[1]) {
				isFoldMove_ = false;
			}
			else {//自機が折るパネルの先に居なければ
				if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ == false) {//折り
					FoldDirecting(4, false);//折る演出
					if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack == false) {//今のパネルを記憶する
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].previousMapstateRight = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].mapstate;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack = true;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate = MapState::None;
						foldCount_--;
					}

					if (drawTest_ == false) {
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::Vertical) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].mapstate = MapState::Vertical;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::Side) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].mapstate = MapState::Side;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::Cross) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].mapstate = MapState::Cross;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedTop) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].mapstate = MapState::TShapedTop;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedDown) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].mapstate = MapState::TShapedDown;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedLeft) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].mapstate = MapState::TShapedRight;
						}
						if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate == MapState::TShapedRight) {
							map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].mapstate = MapState::TShapedLeft;
						}
					}
				}

				if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ == true && isFoldMove_ == true) {//折り返し
					FoldDirecting(4, true);//折る演出
					map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].mapstate = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].previousMapstateRight;

					if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack == true) {
						foldCount_--;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousFoldChack = false;
					}

					if (drawTest_ == false) {
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate;

						isFoldMove_ = false;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = false;

						//記憶したパネル情報の初期化
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].previousMapstate = MapState::None;
						map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].previousMapstateDown = MapState::None;
					}
				}
			}
		}
	}
}

void Stage4::FoldDirecting(int direction, bool isLapel) {
	drawTest_ = true;
	if (isLapel == false) {//折る時
		if (direction == 1) {//上に折る
			//アンカーを設定
			if (setTest_ == false) {
				for (int i = 0; i < 7; i++) {
					spriteTest_[i]->SetAnchor(Vector2{ 0.0f,0.0f });
				}
				transformTest_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform;
				mapstate_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate;
				mapstate2_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate;
				setTest_ = true;
			}
			transformTest_.rotate.num[0] += 0.05f;

			if (transformTest_.rotate.num[0] >= 3.18f / 2) {//半分折ったら
				if (mapstate2_ == MapState::Vertical) {
					mapstate_ = MapState::Vertical;
				}
				if (mapstate2_ == MapState::Side) {
					mapstate_ = MapState::Side;
				}
				if (mapstate2_ == MapState::Cross) {
					mapstate_ = MapState::Cross;
				}
				if (mapstate2_ == MapState::TShapedLeft) {
					mapstate_ = MapState::TShapedLeft;
				}
				if (mapstate2_ == MapState::TShapedRight) {
					mapstate_ = MapState::TShapedRight;
				}
			}

			if (transformTest_.rotate.num[0] >= 3.18f) {//折り終わり
				if (mapstate2_ == MapState::TShapedTop) {
					mapstate_ = MapState::TShapedDown;
				}
				if (mapstate2_ == MapState::TShapedDown) {
					mapstate_ = MapState::TShapedTop;
				}

				transformTest_.rotate.num[0] = 3.18f;

				drawTest_ = false;
				isFoldMove_ = false;
				setTest_ = false;
				map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = true;
			}
		}

		if (direction == 2) {//下に折る
			//アンカーを設定
			if (setTest_ == false) {
				for (int i = 0; i < 7; i++) {
					spriteTest_[i]->SetAnchor(Vector2{ 0.0f,1.0f });
				}
				transformTest_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform;
				mapstate_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate;
				mapstate2_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate;
				setTest_ = true;
			}
			transformTest_.rotate.num[0] += 0.05f;

			if (transformTest_.rotate.num[0] >= 3.18f / 2) {//半分折ったら
				if (mapstate2_ == MapState::Vertical) {
					mapstate_ = MapState::Vertical;
				}
				if (mapstate2_ == MapState::Side) {
					mapstate_ = MapState::Side;
				}
				if (mapstate2_ == MapState::Cross) {
					mapstate_ = MapState::Cross;
				}
				if (mapstate2_ == MapState::TShapedLeft) {
					mapstate_ = MapState::TShapedLeft;
				}
				if (mapstate2_ == MapState::TShapedRight) {
					mapstate_ = MapState::TShapedRight;
				}
			}

			if (transformTest_.rotate.num[0] >= 3.18f) {//折り終わり
				if (mapstate2_ == MapState::TShapedTop) {
					mapstate_ = MapState::TShapedDown;
				}
				if (mapstate2_ == MapState::TShapedDown) {
					mapstate_ = MapState::TShapedTop;
				}

				transformTest_.rotate.num[0] = 3.18f;

				drawTest_ = false;
				isFoldMove_ = false;
				setTest_ = false;
				map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = true;
			}
		}

		if (direction == 3) {//左に折る
			//アンカーを設定
			if (setTest_ == false) {
				for (int i = 0; i < 7; i++) {
					spriteTest_[i]->SetAnchor(Vector2{ 0.0f,0.0f });
				}
				transformTest_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform;
				mapstate_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate;
				mapstate2_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate;
				setTest_ = true;
			}
			transformTest_.rotate.num[1] += 0.05f;

			if (transformTest_.rotate.num[1] >= 3.18f / 2) {//半分折ったら
				if (mapstate2_ == MapState::Vertical) {
					mapstate_ = MapState::Vertical;
				}
				if (mapstate2_ == MapState::Side) {
					mapstate_ = MapState::Side;
				}
				if (mapstate2_ == MapState::Cross) {
					mapstate_ = MapState::Cross;
				}
				if (mapstate2_ == MapState::TShapedTop) {
					mapstate_ = MapState::TShapedTop;
				}
				if (mapstate2_ == MapState::TShapedDown) {
					mapstate_ = MapState::TShapedDown;
				}
			}

			if (transformTest_.rotate.num[1] >= 3.18f) {//折り終わり
				if (mapstate2_ == MapState::TShapedLeft) {
					mapstate_ = MapState::TShapedLeft;
				}
				if (mapstate2_ == MapState::TShapedRight) {
					mapstate_ = MapState::TShapedRight;
				}

				transformTest_.rotate.num[1] = 3.18f;

				drawTest_ = false;
				isFoldMove_ = false;
				setTest_ = false;
				map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = true;
			}
		}
		if (direction == 4) {//右に折る
			//アンカーを設定
			if (setTest_ == false) {
				for (int i = 0; i < 7; i++) {
					spriteTest_[i]->SetAnchor(Vector2{ 1.0f,0.0f });
				}
				transformTest_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform;
				mapstate_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate;
				mapstate2_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].mapstate;
				setTest_ = true;
			}
			transformTest_.rotate.num[1] += 0.05f;

			if (transformTest_.rotate.num[1] >= 3.18f / 2) {//半分折ったら
				if (mapstate2_ == MapState::Vertical) {
					mapstate_ = MapState::Vertical;
				}
				if (mapstate2_ == MapState::Side) {
					mapstate_ = MapState::Side;
				}
				if (mapstate2_ == MapState::Cross) {
					mapstate_ = MapState::Cross;
				}
				if (mapstate2_ == MapState::TShapedTop) {
					mapstate_ = MapState::TShapedTop;
				}
				if (mapstate2_ == MapState::TShapedDown) {
					mapstate_ = MapState::TShapedDown;
				}
			}

			if (transformTest_.rotate.num[1] >= 3.18f) {//折り終わり
				if (mapstate2_ == MapState::TShapedLeft) {
					mapstate_ = MapState::TShapedLeft;
				}
				if (mapstate2_ == MapState::TShapedRight) {
					mapstate_ = MapState::TShapedRight;
				}

				transformTest_.rotate.num[1] = 3.18f;

				drawTest_ = false;
				isFoldMove_ = false;
				setTest_ = false;
				map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = true;
			}
		}
	}
	else {//折り返し
		if (direction == 1) {//上
			//アンカーを設定
			if (setTest_ == false) {
				for (int i = 0; i < 7; i++) {
					spriteTest_[i]->SetAnchor(Vector2{ 0.0f,0.0f });
				}
				transformTest_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform;
				mapstate_ = map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].mapstate;
				mapstate2_ = map[(int)selectPoint_.num[1] - 1][(int)selectPoint_.num[0]].mapstate;
				setTest_ = true;
				transformTest_.rotate.num[0] = 3.18f;
			}
			transformTest_.rotate.num[0] -= 0.05f;

			if (transformTest_.rotate.num[0] <= 3.18f / 2) {//半分折ったら
				if (mapstate2_ == MapState::Vertical) {
					mapstate_ = MapState::Vertical;
				}
				if (mapstate2_ == MapState::Side) {
					mapstate_ = MapState::Side;
				}
				if (mapstate2_ == MapState::Cross) {
					mapstate_ = MapState::Cross;
				}
				if (mapstate2_ == MapState::TShapedLeft) {
					mapstate_ = MapState::TShapedLeft;
				}
				if (mapstate2_ == MapState::TShapedRight) {
					mapstate_ = MapState::TShapedRight;
				}
			}

			if (transformTest_.rotate.num[0] <= 0.0f) {//折り終わり
				if (mapstate2_ == MapState::TShapedTop) {
					mapstate_ = MapState::TShapedDown;
				}
				if (mapstate2_ == MapState::TShapedDown) {
					mapstate_ = MapState::TShapedTop;
				}

				transformTest_.rotate.num[0] = 0.0f;

				drawTest_ = false;
				isFoldMove_ = false;
				setTest_ = false;
				map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = true;
			}
		}

		if (direction == 2) {//下
			//アンカーを設定
			if (setTest_ == false) {
				for (int i = 0; i < 7; i++) {
					spriteTest_[i]->SetAnchor(Vector2{ 0.0f,1.0f });
				}
				transformTest_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform;
				mapstate_ = map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].mapstate;
				mapstate2_ = map[(int)selectPoint_.num[1] + 1][(int)selectPoint_.num[0]].mapstate;
				setTest_ = true;
				transformTest_.rotate.num[0] = 3.18f;
			}
			transformTest_.rotate.num[0] -= 0.05f;

			if (transformTest_.rotate.num[0] <= 3.18f / 2) {//半分折ったら
				if (mapstate2_ == MapState::Vertical) {
					mapstate_ = MapState::Vertical;
				}
				if (mapstate2_ == MapState::Side) {
					mapstate_ = MapState::Side;
				}
				if (mapstate2_ == MapState::Cross) {
					mapstate_ = MapState::Cross;
				}
				if (mapstate2_ == MapState::TShapedLeft) {
					mapstate_ = MapState::TShapedLeft;
				}
				if (mapstate2_ == MapState::TShapedRight) {
					mapstate_ = MapState::TShapedRight;
				}
			}

			if (transformTest_.rotate.num[0] <= 0.0f) {//折り終わり
				if (mapstate2_ == MapState::TShapedTop) {
					mapstate_ = MapState::TShapedDown;
				}
				if (mapstate2_ == MapState::TShapedDown) {
					mapstate_ = MapState::TShapedTop;
				}

				transformTest_.rotate.num[0] = 0.0f;

				drawTest_ = false;
				isFoldMove_ = false;
				setTest_ = false;
				map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = true;
			}
		}

		if (direction == 3) {//左
			//アンカーを設定
			if (setTest_ == false) {
				for (int i = 0; i < 7; i++) {
					spriteTest_[i]->SetAnchor(Vector2{ 0.0f,0.0f });
				}
				transformTest_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform;
				mapstate_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].mapstate;
				mapstate2_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] - 1].mapstate;
				setTest_ = true;
				transformTest_.rotate.num[1] = 3.18f;
			}
			transformTest_.rotate.num[1] -= 0.05f;

			if (mapstate2_ == MapState::TShapedLeft) {
				mapstate_ = MapState::TShapedRight;
			}
			if (mapstate2_ == MapState::TShapedRight) {
				mapstate_ = MapState::TShapedLeft;
			}

			if (transformTest_.rotate.num[1] <= 3.18f / 2) {//半分折ったら
				if (mapstate2_ == MapState::Vertical) {
					mapstate_ = MapState::Vertical;
				}
				if (mapstate2_ == MapState::Side) {
					mapstate_ = MapState::Side;
				}
				if (mapstate2_ == MapState::Cross) {
					mapstate_ = MapState::Cross;
				}
				if (mapstate2_ == MapState::TShapedTop) {
					mapstate_ = MapState::TShapedTop;
				}
				if (mapstate2_ == MapState::TShapedDown) {
					mapstate_ = MapState::TShapedDown;
				}
			}

			if (transformTest_.rotate.num[1] <= 0.0f) {//折り終わり

				transformTest_.rotate.num[1] = 0.0f;

				drawTest_ = false;
				isFoldMove_ = false;
				setTest_ = false;
				map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = true;
			}
		}
		if (direction == 4) {//右
			//アンカーを設定
			if (setTest_ == false) {
				for (int i = 0; i < 7; i++) {
					spriteTest_[i]->SetAnchor(Vector2{ 1.0f,0.0f });
				}
				transformTest_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform;
				mapstate_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].mapstate;
				mapstate2_ = map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0] + 1].mapstate;
				setTest_ = true;
				transformTest_.rotate.num[1] = 3.18f;
			}
			transformTest_.rotate.num[1] -= 0.05f;

			if (mapstate2_ == MapState::TShapedLeft) {
				mapstate_ = MapState::TShapedRight;
			}
			if (mapstate2_ == MapState::TShapedRight) {
				mapstate_ = MapState::TShapedLeft;
			}

			if (transformTest_.rotate.num[1] <= 3.18f / 2) {//半分折ったら
				if (mapstate2_ == MapState::Vertical) {
					mapstate_ = MapState::Vertical;
				}
				if (mapstate2_ == MapState::Side) {
					mapstate_ = MapState::Side;
				}
				if (mapstate2_ == MapState::Cross) {
					mapstate_ = MapState::Cross;
				}
				if (mapstate2_ == MapState::TShapedTop) {
					mapstate_ = MapState::TShapedTop;
				}
				if (mapstate2_ == MapState::TShapedDown) {
					mapstate_ = MapState::TShapedDown;
				}
			}

			if (transformTest_.rotate.num[1] <= 0.0f) {//折り終わり

				transformTest_.rotate.num[1] = 0.0f;

				drawTest_ = false;
				isFoldMove_ = false;
				setTest_ = false;
				map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = true;
			}
		}
	}
}

int Stage4::GetNowMapState(Vector2 pos) {
	int i = 0;
	int j = 0;
	int state = 0;
	//現在の-(プレイヤー座標-プレイ画面/2)を計算
	playerPos_.num[0] = pos.num[0] - 1280 / 2;
	playerPos_.num[1] = pos.num[1] - 720 / 2;
	playerPos_.num[0] = -playerPos_.num[0];
	playerPos_.num[1] = -playerPos_.num[1];

	while (true) {//計算した座標を元に、合致するパネルを探す
		if (panelSize_.num[0] * i <= pos.num[0] && panelSize_.num[0] * i + panelSize_.num[0] >= pos.num[0]) {
			if (panelSize_.num[1] * j <= pos.num[1] && panelSize_.num[1] * j + panelSize_.num[1] >= pos.num[1]) {
				if (map[j][i].mapstate == MapState::None) {
					state = 0;
				}
				else if (map[j][i].mapstate == MapState::Vertical) {
					state = 1;
				}
				else if (map[j][i].mapstate == MapState::Side) {
					state = 2;
				}
				else if (map[j][i].mapstate == MapState::Cross) {
					state = 3;
				}
				else if (map[j][i].mapstate == MapState::TShapedTop) {
					state = 4;
				}
				else if (map[j][i].mapstate == MapState::TShapedDown) {
					state = 5;
				}
				else if (map[j][i].mapstate == MapState::TShapedLeft) {
					state = 6;
				}
				else if (map[j][i].mapstate == MapState::TShapedRight) {
					state = 7;
				}
				break;
			}
			else {
				j++;
			}
		}
		else {
			i++;
		}
	}

	//プレイヤーの現在のパネル情報を記録しておく
	playerStatePosX_ = i;
	playerStatePosY_ = j;
	return state;
}

int Stage4::GetNowMapStatePosX() {
	return playerStatePosX_;
}

int Stage4::GetNowMapStatePosY() {
	return playerStatePosY_;
}

int Stage4::GetStartPosX() {
	return startPointX_;
}

int Stage4::GetStartPosY() {
	return startPointY_;
}

void Stage4::Reset() {
	goalCount_ = 0;
	LoadMap();
	CheckGoalCount_ = 0;
	foldCount_ = foldCountMax_;
	isGameClear_ = false;
}

void Stage4::SetAllSetting(const char* stageNum, int foldCountMax, float MapSelectWidth, float MapSelectHeight) {
	stageNum_ = stageNum;

	foldCountMax_ = foldCountMax;
	foldCount_ = foldCountMax_;

	MapSelectSizeX_ = MapSelectWidth + 2;
	MapSelectSizeY_ = MapSelectHeight + 2;

	LoadMap();
}