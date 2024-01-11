#pragma once
#include "Input.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "components/2d/CreateSprite.h"

#include <memory>

class Player {
public:
	void Initialize();
	void Update();
	void Draw();

	void Moves();

	void MoveNone();
	void MoveVertical();
	void MoveSide();
	void MoveCross();
	void MoveTShapedTop();
	void MoveTShapedDown();
	void MoveTShapedLeft();
	void MoveTShapedRight();

	Vector2 GetPos() { return Vector2{ spriteTransform_.translate.num[0],spriteTransform_.translate.num[1] }; }

	void SetNowMapState(int nowMapState);
	void SetNowMapStatePos(int stateNumX, int stateNumY);

	void SetPanelSize(Vector2 panelSize);

private:
	Input* input_ = nullptr;

	TextureManager* textureManager_;
	uint32_t spriteTexture_[6];

	std::unique_ptr<CreateSprite> sprite_[6];

	int spriteTimer_ = 0;

	Transform spriteTransform_;
	Transform spriteUvTransform_;
	Vector4 spriteMaterial_;

	int nowMapState_ = 0;
	int stateNumX_;
	int stateNumY_;

	Vector2 moveSpeed_ = { 3.0f ,3.0f };

	Vector2 panelSize_ = { 200.0f,200.0f };
};