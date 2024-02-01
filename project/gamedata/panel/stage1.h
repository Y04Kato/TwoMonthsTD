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

	static const uint32_t kMapWidth = 4;
	static const uint32_t kMapHeight = 4;

	//パネルの種類
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

	//スタート、ゴール地点などの追加データ
	enum class Event {
		None,//0
		Start,//1
		Goal,//2
		CheckGoal,//3　通過済みのゴール
		Reseal,//4 封印パネル
	};

	//MapData
	struct Map {
		MapState mapstate;//パネルの種類
		Transform transform;//座標
		Direction direction;//折る向き
		Event event;//イベントパネルのデータ
		bool isFold_ = false;//現在折っているか
		MapState previousMapstate;//折る前のmapstateデータ
		MapState previousMapstateUp;//折る前のmapstateデータ上
		MapState previousMapstateDown;//折る前のmapstateデータ下
		MapState previousMapstateLeft;//折る前のmapstateデータ左
		MapState previousMapstateRight;//折る前のmapstateデータ右
		Vector4 spriteMaterial;//スプライトのmaterialcolor
		bool previousFoldChack = false;//折る前のmapstateデータの取得フラグ
		bool isReseal = false;//封印パネルかどうか
	};

	//パネル配置のロード
	void LoadMap();
	//各パネルの折れる方向のロード
	void LoadDirection();
	//各パネルにイベントがあるかロード
	void LoadEvent();

	//各パネル選択
	void Select();

	//選択中のパネルを折る
	void Fold();
	//折る演出、directionはDirection参照
	void FoldDirecting(int direction,bool isLapel);

	//プレイヤー座標から現在居るMapStateを返す
	int GetNowMapState(Vector2 pos);

	int GetNowMapStatePosX();//プレイヤー座標を元に現在の配列座標を返すX
	int GetNowMapStatePosY();//プレイヤー座標を元に現在の配列座標を返すY

	int GetStartPosX();//プレイヤーの開始地点を渡すX
	int GetStartPosY();//プレイヤーの開始地点を渡すY

	Vector2 GetPanelSize() { return panelSize_; }

	void Reset();

	bool GetClearFlag() { return isGameClear_; }

	int GetFoldCount() { return foldCount_; }

	bool GetIsReseal() { return map[playerStatePosY_][playerStatePosX_].isReseal; }

	//マップの設定、ステージ番号、折れる回数、マップサイズX、マップサイズYを設定 2x2ならXYは2にすること
	void SetAllSetting(const char* stageNum , int foldCountMax , float MapSelectWidth, float MapSelectHeight);

private:
	Input* input_ = nullptr;
	TextureManager* textureManager_;

	Map map[kMapHeight][kMapWidth];

	std::unique_ptr<CreateSprite> selectSprite_;
	Transform transform_;
	Vector2 selectPoint_ = { 0.0f,0.0f };//折るパネルを選択している場所
	uint32_t texture_;

	Vector2 panelSize_ = { 200.0f,200.0f };//パネルリソースのサイズ

	std::unique_ptr<CreateSprite> sprite_[kMapHeight * kMapWidth];//None
	std::unique_ptr<CreateSprite> sprite1_[kMapHeight * kMapWidth];//Vertical
	std::unique_ptr<CreateSprite> sprite2_[kMapHeight * kMapWidth];//Side
	std::unique_ptr<CreateSprite> sprite3_[kMapHeight * kMapWidth];//Cross
	std::unique_ptr<CreateSprite> sprite4_[kMapHeight * kMapWidth];//TShapedTop
	std::unique_ptr<CreateSprite> sprite5_[kMapHeight * kMapWidth];//TShapedDown
	std::unique_ptr<CreateSprite> sprite6_[kMapHeight * kMapWidth];//TShapedLeft
	std::unique_ptr<CreateSprite> sprite7_[kMapHeight * kMapWidth];//TShapedRight
	uint32_t spriteTexture_[8];
	Transform spriteUvTransform_;
	Vector4 spriteMaterial_;

	bool isFoldMove_ = false;//今折っているか

	std::unique_ptr<CreateSprite> spriteD1_[kMapHeight * kMapWidth];//DirectionTop
	std::unique_ptr<CreateSprite> spriteD2_[kMapHeight * kMapWidth];//DirectionDown
	std::unique_ptr<CreateSprite> spriteD3_[kMapHeight * kMapWidth];//DirectionLeft
	std::unique_ptr<CreateSprite> spriteD4_[kMapHeight * kMapWidth];//DirectionRight
	uint32_t spriteTextureD_[4];

	std::unique_ptr<CreateSprite> spriteStart_[kMapHeight * kMapWidth];//
	std::unique_ptr<CreateSprite> spriteGoal_[kMapHeight * kMapWidth];//
	std::unique_ptr<CreateSprite> spriteCheckGoal_[kMapHeight * kMapWidth];//
	std::unique_ptr<CreateSprite> spriteReseal_[kMapHeight * kMapWidth];//
	uint32_t spriteTextureE_[4];

	int playerStatePosX_ = 0;//Playerの現在居るパネルの場所X
	int playerStatePosY_ = 0;//Playerの現在居るパネルの場所Y

	int setPlayerStatePosX_ = 0;//Playerが折る際に居たパネルの場所X
	int setPlayerStatePosY_ = 0;//Playerが折る際に居たパネルの場所Y

	Vector3 playerPos_;//プレイヤーの座標

	std::unique_ptr<CreateSprite> spriteTest_[7];//TShapedRight
	Transform transformTest_;
	MapState mapstate_;
	MapState mapstate2_;
	bool drawTest_ = false;
	bool setTest_ = false;

	int startPointX_;
	int startPointY_;

	int goalCount_;
	int CheckGoalCount_;

	bool isGameClear_ = false;

	int foldCount_ = 0;//折る残り回数
	int foldCountMax_ = 5;//折る回数上限

	const char* stageNum_;
	float MapSelectSizeX_;
	float MapSelectSizeY_;
};