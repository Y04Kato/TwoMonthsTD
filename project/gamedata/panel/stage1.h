#pragma once

#include "Model.h"
#include "Input.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "components/2d/CreateSprite.h"

#include <memory>

class Stage1 {
public:
	void Initialize();
	void Update();
	void Draw();

private:
	Input* input_ = nullptr;

	TextureManager* textureManager_;
	uint32_t spriteTexture_[6];

	std::unique_ptr<CreateSprite> sprite_[6];

	Transform spriteTransform_[6];
	Transform spriteUvTransform_;
	Vector4 spriteMaterial_;

	bool isSpriteMove_[2];
	float spriteRotate_[2];

	bool isSpriteDraw[6];
};