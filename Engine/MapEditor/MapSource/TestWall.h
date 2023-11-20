#pragma once
#include "../../GameObject.h"

//◆◆◆を管理するクラス
class TestWall : public GameObject
{
    int hModel_;    //モデル番号
    //char objectID_; //どのオブジェクトかimguiが判別するためのオブジェクト
    bool isDelete_;

    bool isClose_;

public:
    //コンストラクタ
    TestWall(GameObject* parent);

    //デストラクタ
    ~TestWall();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void Imgui_Window() override;

    void Imgui_Data_Edit() override;

    bool IsKillCheck();

    void DeleteMe();

    void DeleteStop();
    
};