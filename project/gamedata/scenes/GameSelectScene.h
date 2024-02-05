#pragma once
#include "components/manager/Iscene.h"
#include "CJEngine.h"
#include "components/input/Input.h"
#include "components/manager/TextureManager.h"
#include "components/2d/CreateSprite.h"
#include "components/audio/Audio.h"

class GameSelectScene :public Iscene {
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:
	CitrusJunosEngine* CJEngine_;

	Input* input_ = nullptr;

	TextureManager* textureManager_;

	std::unique_ptr <CreateSprite> sprite_[4];
	Transform spriteTransform_;
	Transform spriteTransform2_;
	Transform SpriteuvTransform_;
	Vector4 spriteMaterial_;

	float spriteAlpha_ = 256.0f;

	uint32_t pageL_;
	uint32_t pageR_;
	uint32_t pageAll_;
	uint32_t start_;

	bool changeAlpha_ = false;

	int count = 0;

	bool pageChangeR_ = false;
	bool pageChangeL_ = false;

	Audio* audio_;
	SoundData soundData1_;

	bool startGameScene1 = false;
	bool startGameScene2 = false;
	bool startGameScene3 = false;
	bool startGameScene4 = false;
	bool startGameScene5 = false;
	bool startGameScene6 = false;
	bool startGameScene7 = false;
	bool startGameScene8 = false;
	bool startGameScene9 = false;
	bool startGameScene10 = false;
};

