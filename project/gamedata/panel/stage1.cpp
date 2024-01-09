#include "stage1.h"

void Stage1::Initialize() {
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

	texture_ = textureManager_->Load("project/gamedata/resources/panel/select.png");
	selectSprite_.reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, texture_, false, false));
	selectSprite_->SetTextureInitialSize();
	transform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };
	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };

	LoadMap();
}

void Stage1::Update() {
	Select();
	Fold();
	transform_.translate = { selectPoint_.num[0] * panelSize_.num[0],selectPoint_.num[1] * panelSize_.num[1] ,0.0f};
}

void Stage1::Draw() {
	for (int i = 0; i < kMapHeight; i++) {
		for (int j = 0; j < kMapWidth; j++) {
			if (map[i][j].mapstate == MapState::None) {
				sprite_[i * j]->Draw(map[i][j].transform, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::Vertical) {
				sprite1_[i * j]->Draw(map[i][j].transform, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::Side) {
				sprite2_[i * j]->Draw(map[i][j].transform, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::Cross) {
				sprite3_[i * j]->Draw(map[i][j].transform, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::TShapedTop) {
				sprite4_[i * j]->Draw(map[i][j].transform, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::TShapedDown) {
				sprite5_[i * j]->Draw(map[i][j].transform, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::TShapedLeft) {
				sprite6_[i * j]->Draw(map[i][j].transform, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::TShapedRight) {
				sprite7_[i * j]->Draw(map[i][j].transform, spriteUvTransform_, spriteMaterial_);
			}
		}
	}
	selectSprite_->Draw(transform_, spriteUvTransform_, spriteMaterial_);
}

void Stage1::LoadMap() {
	FILE* fp = nullptr;
	char fname[] = "project/gamedata/resources/csv/Map1Panel.csv";
	errno_t err;
	err = fopen_s(&fp, fname, "r");
	for (int i = 0; i < kMapHeight; i++) {
		for (int j = 0; j < kMapWidth; j++) {
			fscanf_s(fp, "%d,", &map[i][j].mapstate);
			map[i][j].transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{j * panelSize_.num[0],i * panelSize_.num[1],0.0f} };
			if (map[i][j].mapstate == MapState::None) {
				sprite_[i * j].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[0], false, false));
				sprite_[i * j]->SetTextureInitialSize();
			}
			if (map[i][j].mapstate == MapState::Vertical) {
				sprite1_[i * j].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[1], false, false));
				sprite1_[i * j]->SetTextureInitialSize();
			}
			if (map[i][j].mapstate == MapState::Side) {
				sprite2_[i * j].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[2], false, false));
				sprite2_[i * j]->SetTextureInitialSize();
			}
			if (map[i][j].mapstate == MapState::Cross) {
				sprite3_[i * j].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[3], false, false));
				sprite3_[i * j]->SetTextureInitialSize();
			}
			if (map[i][j].mapstate == MapState::TShapedTop) {
				sprite4_[i * j].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[4], false, false));
				sprite4_[i * j]->SetTextureInitialSize();
			}
			if (map[i][j].mapstate == MapState::TShapedDown) {
				sprite5_[i * j].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[5], false, false));
				sprite5_[i * j]->SetTextureInitialSize();
			}
			if (map[i][j].mapstate == MapState::TShapedLeft) {
				sprite6_[i * j].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[6], false, false));
				sprite6_[i * j]->SetTextureInitialSize();
			}
			if (map[i][j].mapstate == MapState::TShapedRight) {
				sprite7_[i * j].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTexture_[7], false, false));
				sprite7_[i * j]->SetTextureInitialSize();
			}
		}
	}

	fclose(fp);

	LoadDirection();
}

void Stage1::LoadDirection() {
	FILE* fp = nullptr;
	char fname[] = "project/gamedata/resources/csv/Map1Direction.csv";
	errno_t err;
	err = fopen_s(&fp, fname, "r");
	for (int i = 0; i < kMapHeight; i++) {
		for (int j = 0; j < kMapWidth; j++) {
			fscanf_s(fp, "%d,", &map[i][j].direction);
			if (map[i][j].direction == Direction::None) {

			}
			if (map[i][j].direction == Direction::Up) {

			}
			if (map[i][j].direction == Direction::Left) {

			}
		}
	}

	fclose(fp);
}

void Stage1::Select() {
	if (input_->TriggerKey(DIK_RIGHT)) {
		selectPoint_.num[0] += 1;
		if (selectPoint_.num[0] > kMapWidth) {
			selectPoint_.num[0] = 0;
		}
	}
	if (input_->TriggerKey(DIK_LEFT)) {
		selectPoint_.num[0] -= 1;
		if (selectPoint_.num[0] < 0) {
			selectPoint_.num[0] = kMapWidth;
		}
	}
	if (input_->TriggerKey(DIK_UP)) {
		selectPoint_.num[1] -= 1;
		if (selectPoint_.num[1] < 0) {
			selectPoint_.num[1] = kMapHeight;
		}
	}
	if (input_->TriggerKey(DIK_DOWN)) {
		selectPoint_.num[1] += 1;
		if (selectPoint_.num[1] > kMapHeight) {
			selectPoint_.num[1] = 0;
		}
	}

	if (input_->TriggerKey(DIK_SPACE)) {
		isFoldMove_ = true;
	}
}

void Stage1::Fold() {
	if (isFoldMove_ == true) {
		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::None) {

		}
		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::Up) {
			if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ == false) {
				map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform.rotate.num[0] += 0.05f;

				if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform.rotate.num[0] >= 3.18f) {
					map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform.rotate.num[0] = 3.18f;
					isFoldMove_ = false;
					map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = true;
				}
			}

			if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ == true) {//折り返し
				map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform.rotate.num[0] -= 0.05f;

				if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform.rotate.num[0] <= 0.0f) {
					map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform.rotate.num[0] = 0.0f;
					isFoldMove_ = false;
					map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = false;
				}
			}
		}
		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::Left) {
			if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ == false) {
				map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform.rotate.num[1] += 0.05f;

				if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform.rotate.num[1] >= 3.18f) {
					map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform.rotate.num[1] = 3.18f;
					isFoldMove_ = false;
					map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = true;
				}
			}

			if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ == true) {//折り返し
				map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform.rotate.num[1] -= 0.05f;

				if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform.rotate.num[1] <= 0.0f) {
					map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].transform.rotate.num[1] = 0.0f;
					isFoldMove_ = false;
					map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].isFold_ = false;
				}
			}
		}
	}
}