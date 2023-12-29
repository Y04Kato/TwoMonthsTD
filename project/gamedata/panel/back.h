#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "components/2d/CreateSprite.h"

#include <memory>

class Back {
public:
	void Initialize();
	void Update();
	void Draw();

	/*WorldTransform& GetWorldTransform() { return worldTransform_; }
	void SetTranslate(const Vector3& translate) { worldTransform_.translation_ = translate; }*/

private:
	TextureManager* textureManager_;
	//WorldTransform worldTransform_;
	uint32_t backTexture_;

	std::unique_ptr<CreateSprite> sprite_;
	//std::unique_ptr<Model> backModel_;

	Transform spriteTransform_;
	Transform spriteUvTransform_;
	Vector4 spriteMaterial_;
};