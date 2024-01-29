#pragma once

//シーン一覧、シーン追加時はここに追加する
enum SCENE {
	TITLE_SCENE,
	GAME_SCENE,
	//STAGE1_SCENE,
	//STAGE2_SCENE,
	//STAGE3_SCENE,
	//STAGE4_SCENE,
	//STAGE5_SCENE,
	CLEAR_SCENE,
	SCENE_MAX
};

class Iscene{
public:
	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Finalize() = 0;

	static int sceneNo;

	virtual ~Iscene() {};
};
