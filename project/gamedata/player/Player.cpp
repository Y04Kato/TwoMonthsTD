#include "Player.h"

void Player::Initialize() {
	input_ = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();

	spriteTexture_[0] = textureManager_->Load("project/gamedata/resources/player/PlayerRun1.png");
	spriteTexture_[1] = textureManager_->Load("project/gamedata/resources/player/PlayerRun2.png");
	spriteTexture_[2] = textureManager_->Load("project/gamedata/resources/player/PlayerRun3.png");
	spriteTexture_[3] = textureManager_->Load("project/gamedata/resources/player/PlayerRun4.png");
	spriteTexture_[4] = textureManager_->Load("project/gamedata/resources/player/PlayerRun5.png");
	spriteTexture_[5] = textureManager_->Load("project/gamedata/resources/player/PlayerRun6.png");

	for (int i = 0; i < 6; i++) {
		sprite_[i] = std::make_unique<CreateSprite>();
		sprite_[i]->Initialize(Vector2{ 48.0f,48.0f }, spriteTexture_[i], true, false);
		sprite_[i]->SetAnchor(Vector2{ 0.5f,1.0f });
	}

	startPointX = 1;
	startPointY = 1;

	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{1280 / 2, 720 / 2,0.0f} };
	spriteUvTransform_ = { {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };
	spriteMaterial_ = { 1.0f,1.0f,1.0f,1.0f };
}

void Player::Update() {
	spriteTimer_++;
	if (spriteTimer_ >= 60) {
		spriteTimer_ = 0;
	}

	Moves();

	ImGui::Begin("Player");
	ImGui::DragFloat3("Pos", spriteTransform_.translate.num);
	ImGui::Text("NowMapState %d", nowMapState_);
	ImGui::Text("PanelDirection %d", panelDirection_);
	ImGui::End();
}

void Player::Draw() {
	Vector3 test{ 1280 / 2, 720 /2,1.0f };
	if (spriteTimer_ >= 0 && spriteTimer_ < 10) {
		sprite_[0]->Draw(Transform{ spriteTransform_.scale ,spriteTransform_.rotate ,test }, spriteUvTransform_, spriteMaterial_);
	}
	if (spriteTimer_ >= 10 && spriteTimer_ < 20) {
		sprite_[1]->Draw(Transform{ spriteTransform_.scale ,spriteTransform_.rotate ,test }, spriteUvTransform_, spriteMaterial_);
	}
	if (spriteTimer_ >= 20 && spriteTimer_ < 30) {
		sprite_[2]->Draw(Transform{ spriteTransform_.scale ,spriteTransform_.rotate ,test }, spriteUvTransform_, spriteMaterial_);
	}
	if (spriteTimer_ >= 30 && spriteTimer_ < 40) {
		sprite_[3]->Draw(Transform{ spriteTransform_.scale ,spriteTransform_.rotate ,test }, spriteUvTransform_, spriteMaterial_);
	}
	if (spriteTimer_ >= 40 && spriteTimer_ < 50) {
		sprite_[4]->Draw(Transform{ spriteTransform_.scale ,spriteTransform_.rotate ,test }, spriteUvTransform_, spriteMaterial_);
	}
	if (spriteTimer_ >= 50 && spriteTimer_ < 60) {
		sprite_[5]->Draw(Transform{ spriteTransform_.scale ,spriteTransform_.rotate ,test }, spriteUvTransform_, spriteMaterial_);
	}
}

void Player::Moves() {
	if (nowMapState_ == 0) {//None
		MoveNone();
	}
	if (nowMapState_ == 1) {//Vertical
		MoveVertical();
	}
	if (nowMapState_ == 2) {//Side
		MoveSide();
	}
	if (nowMapState_ == 3) {//Cross
		MoveCross();
	}
	if (nowMapState_ == 4) {//TshapedTop
		MoveTShapedTop();
	}
	if (nowMapState_ == 5) {//TshapedDown
		MoveTShapedDown();
	}
	if (nowMapState_ == 6) {//TshapedLeft
		MoveTShapedLeft();
	}
	if (nowMapState_ == 7) {//TshapedRight
		MoveTShapedRight();
	}

	if (panelSize_.num[1] * stateNumY_ + 74.0f >= spriteTransform_.translate.num[1]) {
		panelDirection_ = 1;
	}
	else if (panelSize_.num[1] * stateNumY_ + panelSize_.num[1] - 74.0f <= spriteTransform_.translate.num[1]) {
		panelDirection_ = 2;
	}
	else if (panelSize_.num[0] * stateNumX_ + 74.0f >= spriteTransform_.translate.num[0]) {
		panelDirection_ = 3;
	}
	else if (panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 74.0f <= spriteTransform_.translate.num[0]) {
		panelDirection_ = 4;
	}
	else {
		panelDirection_ = 0;
	}

	//外に出たときの処理
	if (nowMapState_ == 0) {//None
		ResetPlayer();
	}
	if (nowMapState_ == 1) {//Vertical
		if (panelDirection_ == 3 || panelDirection_ == 4) {
			ResetPlayer();
		}
	}
	if (nowMapState_ == 2) {//Side
		if (panelDirection_ == 1 || panelDirection_ == 2) {
			ResetPlayer();
		}
	}
	if (nowMapState_ == 3) {//Cross

	}
	if (nowMapState_ == 4) {//TshapedTop
		if (panelDirection_ == 2) {
			ResetPlayer();
		}
	}
	if (nowMapState_ == 5) {//TshapedDown
		if (panelDirection_ == 1) {
			ResetPlayer();
		}
	}
	if (nowMapState_ == 6) {//TshapedLeft
		if (panelDirection_ == 4) {
			ResetPlayer();
		}
	}
	if (nowMapState_ == 7) {//TshapedRight
		if (panelDirection_ == 3) {
			ResetPlayer();
		}
	}

	if (input_->TriggerKey(DIK_R)) {
		ResetPlayer();
	}
}

void Player::MoveNone() {
	if (input_->PressKey(DIK_W)) {
		spriteTransform_.translate.num[1] -= moveSpeed_.num[1];
	}
	if (input_->PressKey(DIK_S)) {
		spriteTransform_.translate.num[1] += moveSpeed_.num[1];
	}
	if (input_->PressKey(DIK_A)) {
		spriteTransform_.translate.num[0] -= moveSpeed_.num[0];
		for (int i = 0; i < 6; i++) {
			sprite_[i]->SetFlip(false, false);
		}
	}
	if (input_->PressKey(DIK_D)) {
		spriteTransform_.translate.num[0] += moveSpeed_.num[0];
		for (int i = 0; i < 6; i++) {
			sprite_[i]->SetFlip(true, false);
		}
	}
}

void Player::MoveVertical() {
	if (input_->PressKey(DIK_W)) {
		spriteTransform_.translate.num[1] -= moveSpeed_.num[1];
	}
	if (input_->PressKey(DIK_S)) {
		spriteTransform_.translate.num[1] += moveSpeed_.num[1];
	}
	if (input_->PressKey(DIK_A)) {
		if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[0] -= moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(false, false);
			}
		}
	}
	if (input_->PressKey(DIK_D)) {
		if (panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[0] += moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(true, false);
			}
		}
	}
}

void Player::MoveSide() {
	if (input_->PressKey(DIK_W)) {
		if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[1] -= moveSpeed_.num[1];
		}
	}
	if (input_->PressKey(DIK_S)) {
		if (panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[1] += moveSpeed_.num[1];
		}
	}
	if (input_->PressKey(DIK_A)) {
		spriteTransform_.translate.num[0] -= moveSpeed_.num[0];
		for (int i = 0; i < 6; i++) {
			sprite_[i]->SetFlip(false, false);
		}
	}
	if (input_->PressKey(DIK_D)) {
		spriteTransform_.translate.num[0] += moveSpeed_.num[0];
		for (int i = 0; i < 6; i++) {
			sprite_[i]->SetFlip(true, false);
		}
	}
}

void Player::MoveCross() {
	if (input_->PressKey(DIK_W)) {
		if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[1] -= moveSpeed_.num[1];
		}
		else if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0] && panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[1] -= moveSpeed_.num[1];
		}
	}
	if (input_->PressKey(DIK_S)) {
		if (panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[1] += moveSpeed_.num[1];
		}
		else if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0] && panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[1] += moveSpeed_.num[1];
		}
	}
	if (input_->PressKey(DIK_A)) {
		if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[0] -= moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(false, false);
			}
		}
		else if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1] && panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[0] -= moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(false, false);
			}
		}
	}
	if (input_->PressKey(DIK_D)) {
		if (panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[0] += moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(true, false);
			}
		}
		else if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1] && panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[0] += moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(true, false);
			}
		}
	}
}

void Player::MoveTShapedTop() {
	if (input_->PressKey(DIK_W)) {
		if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[1] -= moveSpeed_.num[1];
		}
		else if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0] && panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[1] -= moveSpeed_.num[1];
		}
	}
	if (input_->PressKey(DIK_S)) {
		if (panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[1] += moveSpeed_.num[1];
		}
	}
	if (input_->PressKey(DIK_A)) {
		if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[0] -= moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(false, false);
			}
		}
		else if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1] && panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[0] -= moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(false, false);
			}
		}
	}
	if (input_->PressKey(DIK_D)) {
		if (panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[0] += moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(true, false);
			}
		}
		else if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1] && panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[0] += moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(true, false);
			}
		}
	}
}

void Player::MoveTShapedDown() {
	if (input_->PressKey(DIK_W)) {
		if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[1] -= moveSpeed_.num[1];
		}
	}
	if (input_->PressKey(DIK_S)) {
		if (panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[1] += moveSpeed_.num[1];
		}
		else if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0] && panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[1] += moveSpeed_.num[1];
		}
	}
	if (input_->PressKey(DIK_A)) {
		if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[0] -= moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(false, false);
			}
		}
		else if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1] && panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[0] -= moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(false, false);
			}
		}
	}
	if (input_->PressKey(DIK_D)) {
		if (panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[0] += moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(true, false);
			}
		}
		else if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1] && panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[0] += moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(true, false);
			}
		}
	}
}

void Player::MoveTShapedLeft() {
	if (input_->PressKey(DIK_W)) {
		if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[1] -= moveSpeed_.num[1];
		}
		else if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0] && panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[1] -= moveSpeed_.num[1];
		}
	}
	if (input_->PressKey(DIK_S)) {
		if (panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[1] += moveSpeed_.num[1];
		}
		else if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0] && panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[1] += moveSpeed_.num[1];
		}
	}
	if (input_->PressKey(DIK_A)) {
		if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[0] -= moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(false, false);
			}
		}
		else if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1] && panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[0] -= moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(false, false);
			}
		}
	}
	if (input_->PressKey(DIK_D)) {
		if (panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[0] += moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(true, false);
			}
		}
	}
}

void Player::MoveTShapedRight() {
	if (input_->PressKey(DIK_W)) {
		if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[1] -= moveSpeed_.num[1];
		}
		else if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0] && panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[1] -= moveSpeed_.num[1];
		}
	}
	if (input_->PressKey(DIK_S)) {
		if (panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[1] += moveSpeed_.num[1];
		}
		else if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0] && panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[1] += moveSpeed_.num[1];
		}
	}
	if (input_->PressKey(DIK_A)) {
		if (panelSize_.num[0] * stateNumX_ + 78.0f <= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[0] -= moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(false, false);
			}
		}
	}
	if (input_->PressKey(DIK_D)) {
		if (panelSize_.num[0] * stateNumX_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[0]) {
			spriteTransform_.translate.num[0] += moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(true, false);
			}
		}
		else if (panelSize_.num[1] * stateNumY_ + 78.0f <= spriteTransform_.translate.num[1] && panelSize_.num[1] * stateNumY_ + panelSize_.num[0] - 78.0f >= spriteTransform_.translate.num[1]) {
			spriteTransform_.translate.num[0] += moveSpeed_.num[0];
			for (int i = 0; i < 6; i++) {
				sprite_[i]->SetFlip(true, false);
			}
		}
	}
}

void Player::SetNowMapState(int nowMapState) {
	nowMapState_ = nowMapState;
}

void Player::SetNowMapStatePos(int stateNumX, int stateNumY) {
	stateNumX_ = stateNumX;
	stateNumY_ = stateNumY;
}

void Player::SetPanelSize(Vector2 panelSize) {
	panelSize_ = panelSize;
}

void Player::ResetPlayer() {
	spriteTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{panelSize_.num[0] * startPointX + panelSize_.num[0] / 2,panelSize_.num[1] * startPointY + panelSize_.num[1] / 2,0.1f} };
	isReset_ = true;
}

void Player::SetStartPoint(int panelX, int panelY) {
	startPointX = panelX;
	startPointY = panelY;
}

void Player::SetIsReset(bool isReset) {
	isReset_ = isReset;
}