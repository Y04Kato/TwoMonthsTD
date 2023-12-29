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

private:
	Input* input_ = nullptr;

	TextureManager* textureManager_;
	uint32_t spriteTexture_;

	std::unique_ptr<CreateSprite> sprite_;

	Transform spriteTransform_;
	Transform spriteUvTransform_;
	Vector4 spriteMaterial_;

};