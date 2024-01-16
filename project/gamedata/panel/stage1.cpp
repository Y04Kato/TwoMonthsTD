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

	spriteTextureD_[0] = textureManager_->Load("project/gamedata/resources/panel/directionUp.png");
	spriteTextureD_[1] = textureManager_->Load("project/gamedata/resources/panel/directionDown.png");
	spriteTextureD_[2] = textureManager_->Load("project/gamedata/resources/panel/directionLeft.png");
	spriteTextureD_[3] = textureManager_->Load("project/gamedata/resources/panel/directionRight.png");

	LoadMap();
}

void Stage1::Update() {
	Select();
	Fold();
	transform_.translate = { selectPoint_.num[0] * panelSize_.num[0],selectPoint_.num[1] * panelSize_.num[1] ,0.0f };
}

void Stage1::Draw() {
	for (int i = 0; i < kMapHeight; i++) {
		for (int j = 0; j < kMapWidth; j++) {
			if (map[i][j].mapstate == MapState::None) {
				sprite_[i * j]->Draw(map[i][j].transform, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::Vertical) {
				sprite1_[i * j]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]}}, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::Side) {
				sprite2_[i * j]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::Cross) {
				sprite3_[i * j]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::TShapedTop) {
				sprite4_[i * j]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::TShapedDown) {
				sprite5_[i * j]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::TShapedLeft) {
				sprite6_[i * j]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].mapstate == MapState::TShapedRight) {
				sprite7_[i * j]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
			}

			if (map[i][j].direction == Direction::None) {

			}
			if (map[i][j].direction == Direction::Up) {
				spriteD1_[i * j]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].direction == Direction::Down) {
				spriteD2_[i * j]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].direction == Direction::Left) {
				spriteD3_[i * j]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
			}
			if (map[i][j].direction == Direction::Right) {
				spriteD4_[i * j]->Draw(Transform{ map[i][j].transform.scale,map[i][j].transform.rotate,{map[i][j].transform.translate.num[0] + playerPos_.num[0],map[i][j].transform.translate.num[1] + playerPos_.num[1] ,map[i][j].transform.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
			}
		}
	}
	selectSprite_->Draw(Transform{ transform_.scale,transform_.rotate,{transform_.translate.num[0] + playerPos_.num[0],transform_.translate.num[1] + playerPos_.num[1] ,transform_.translate.num[2]} }, spriteUvTransform_, spriteMaterial_);
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
				spriteD1_[i * j].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTextureD_[0], false, false));
				spriteD1_[i * j]->SetTextureInitialSize();
			}

			if (map[i][j].direction == Direction::Down) {
				spriteD2_[i * j].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTextureD_[1], false, false));
				spriteD2_[i * j]->SetTextureInitialSize();
				spriteD2_[i * j]->SetAnchor(Vector2{ 0.0f,1.0f });
				map[i][j].transform.translate.num[1] += panelSize_.num[1];
				if (map[i][j].mapstate == MapState::None) {
					sprite_[i * j]->SetAnchor(Vector2{ 0.0f,1.0f });
				}
				if (map[i][j].mapstate == MapState::Vertical) {
					sprite1_[i * j]->SetAnchor(Vector2{ 0.0f,1.0f });
				}
				if (map[i][j].mapstate == MapState::Side) {
					sprite2_[i * j]->SetAnchor(Vector2{ 0.0f,1.0f });
				}
				if (map[i][j].mapstate == MapState::Cross) {
					sprite3_[i * j]->SetAnchor(Vector2{ 0.0f,1.0f });
				}
				if (map[i][j].mapstate == MapState::TShapedTop) {
					sprite4_[i * j]->SetAnchor(Vector2{ 0.0f,1.0f });
				}
				if (map[i][j].mapstate == MapState::TShapedDown) {
					sprite5_[i * j]->SetAnchor(Vector2{ 0.0f,1.0f });
				}
				if (map[i][j].mapstate == MapState::TShapedLeft) {
					sprite6_[i * j]->SetAnchor(Vector2{ 0.0f,1.0f });
				}
				if (map[i][j].mapstate == MapState::TShapedRight) {
					sprite7_[i * j]->SetAnchor(Vector2{ 0.0f,1.0f });
				}
			}

			if (map[i][j].direction == Direction::Left) {
				spriteD3_[i * j].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTextureD_[2], false, false));
				spriteD3_[i * j]->SetTextureInitialSize();
			}

			if (map[i][j].direction == Direction::Right) {
				spriteD4_[i * j].reset(CreateSprite::CreateSpriteFromPng(Vector2{ 100.0f,100.0f }, spriteTextureD_[3], false, false));
				spriteD4_[i * j]->SetTextureInitialSize();
				spriteD4_[i * j]->SetAnchor(Vector2{ 1.0f,0.0f });
				map[i][j].transform.translate.num[0] += panelSize_.num[0];
				if (map[i][j].mapstate == MapState::None) {
					sprite_[i * j]->SetAnchor(Vector2{ 1.0f,0.0f });
				}
				if (map[i][j].mapstate == MapState::Vertical) {
					sprite1_[i * j]->SetAnchor(Vector2{ 1.0f,0.0f });
				}
				if (map[i][j].mapstate == MapState::Side) {
					sprite2_[i * j]->SetAnchor(Vector2{ 1.0f,0.0f });
				}
				if (map[i][j].mapstate == MapState::Cross) {
					sprite3_[i * j]->SetAnchor(Vector2{ 1.0f,0.0f });
				}
				if (map[i][j].mapstate == MapState::TShapedTop) {
					sprite4_[i * j]->SetAnchor(Vector2{ 1.0f,0.0f });
				}
				if (map[i][j].mapstate == MapState::TShapedDown) {
					sprite5_[i * j]->SetAnchor(Vector2{ 1.0f,0.0f });
				}
				if (map[i][j].mapstate == MapState::TShapedLeft) {
					sprite6_[i * j]->SetAnchor(Vector2{ 1.0f,0.0f });
				}
				if (map[i][j].mapstate == MapState::TShapedRight) {
					sprite7_[i * j]->SetAnchor(Vector2{ 1.0f,0.0f });
				}
			}
		}
	}

	fclose(fp);
}

void Stage1::Select() {
	if (input_->TriggerKey(DIK_RIGHT) && isFoldMove_ == false) {
		selectPoint_.num[0] += 1;
		if (selectPoint_.num[0] > kMapWidth) {
			selectPoint_.num[0] = 0;
		}
	}
	if (input_->TriggerKey(DIK_LEFT) && isFoldMove_ == false) {
		selectPoint_.num[0] -= 1;
		if (selectPoint_.num[0] < 0) {
			selectPoint_.num[0] = kMapWidth;
		}
	}
	if (input_->TriggerKey(DIK_UP) && isFoldMove_ == false) {
		selectPoint_.num[1] -= 1;
		if (selectPoint_.num[1] < 0) {
			selectPoint_.num[1] = kMapHeight;
		}
	}
	if (input_->TriggerKey(DIK_DOWN) && isFoldMove_ == false) {
		selectPoint_.num[1] += 1;
		if (selectPoint_.num[1] > kMapHeight) {
			selectPoint_.num[1] = 0;
		}
	}

	if (input_->TriggerKey(DIK_SPACE)) {//折る
		isFoldMove_ = true;
	}
}

void Stage1::Fold() {
	if (isFoldMove_ == true) {
		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::None) {//折れない
			isFoldMove_ = false;
		}

		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::Up) {//上に折る
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

		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::Down) {//下に折る
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

		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::Left) {//左に折る
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

		if (map[(int)selectPoint_.num[1]][(int)selectPoint_.num[0]].direction == Direction::Right) {//右に折る
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

int Stage1::GetNowMapState(Vector2 pos) {
	int i = 0;
	int j = 0;
	int state = 0;
	playerPos_.num[0] = pos.num[0] - 1280/2;
	playerPos_.num[1] = pos.num[1] - 720/2;
	playerPos_.num[0] = -playerPos_.num[0];
	playerPos_.num[1] = -playerPos_.num[1];

	while (true) {
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

	playerStatePosX_ = i;
	playerStatePosY_ = j;
	return state;
}

int Stage1::GetNowMapStatePosX() {
	return playerStatePosX_;
}

int Stage1::GetNowMapStatePosY() {
	return playerStatePosY_;
}