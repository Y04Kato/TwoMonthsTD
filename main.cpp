#include "components/manager/SceneManager.h"

int Iscene::sceneNo;
int Iscene::stageNo;

//Windowsアプリでのエントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	std::unique_ptr<SceneManager> sceneManager = std::make_unique<SceneManager>();
	sceneManager->Run();
	sceneManager.release();
	return 0;
}