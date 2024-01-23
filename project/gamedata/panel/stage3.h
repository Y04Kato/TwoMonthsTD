#pragma once
#include "Model.h"
#include "Input.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "components/2d/CreateSprite.h"

#include <memory>

class Stage3 {
public:
	void Initialize();
	void Update();
	void Draw();

	static const uint32_t kMapWidth = 8;
	static const uint32_t kMapHeight = 5;

	enum class MapState {
		None,//0
		Vertical,//1
		Side,//2
		Cross,//3　
		TShapedTop,//4
		TShapedDown,//5
		TShapedLeft,//6
		TShapedRight,//7
	};

	//折る方向
	enum class Direction {
		None,//0
		Up,//1
		Down,//2
		Left,//3
		Right,//4
	};

	struct Map {
		MapState mapstate;
		Transform transform;
		Direction direction;
		bool isFold_ = false;
	};

	// パネル配置のロード
	void LoadMap();
	// 各パネルの折れる方向のロード
	void LoadDirection();

	// 各パネル選択
	void Select();

	// 選択中のパネルを折る
	void Fold();

	int GetNowMapState(Vector2 pos);

	int GetNowMapStatePosX();
	int GetNowMapStatePosY();

	Vector2 GetPanelSize() { return panelSize_; }

private:
	Input* input_ = nullptr;
	TextureManager* textureManager_;

	Map map[kMapHeight][kMapWidth];

	std::unique_ptr<CreateSprite> selectSprite_;
	Transform transform_;
	Vector2 selectPoint_ = { 0.0f,0.0f };
	uint32_t texture_;

	Vector2 panelSize_ = { 200.0f,200.0f };

	std::unique_ptr<CreateSprite> sprite_[kMapHeight * kMapWidth];
	std::unique_ptr<CreateSprite> sprite1_[kMapHeight * kMapWidth];
	std::unique_ptr<CreateSprite> sprite2_[kMapHeight * kMapWidth];
	std::unique_ptr<CreateSprite> sprite3_[kMapHeight * kMapWidth];
	std::unique_ptr<CreateSprite> sprite4_[kMapHeight * kMapWidth];
	std::unique_ptr<CreateSprite> sprite5_[kMapHeight * kMapWidth];
	std::unique_ptr<CreateSprite> sprite6_[kMapHeight * kMapWidth];
	std::unique_ptr<CreateSprite> sprite7_[kMapHeight * kMapWidth];
	uint32_t spriteTexture_[8];
	Transform spriteUvTransform_;
	Vector4 spriteMaterial_;

	bool isFoldMove_ = false;

	std::unique_ptr<CreateSprite> spriteD1_[kMapHeight * kMapWidth];
	std::unique_ptr<CreateSprite> spriteD2_[kMapHeight * kMapWidth];
	std::unique_ptr<CreateSprite> spriteD3_[kMapHeight * kMapWidth];
	std::unique_ptr<CreateSprite> spriteD4_[kMapHeight * kMapWidth];
	uint32_t spriteTextureD_[4];

	int playerStatePosX_ = 0;
	int playerStatePosY_ = 0;
};