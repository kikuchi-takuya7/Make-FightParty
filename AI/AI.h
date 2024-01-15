#pragma once



/// <summary>
/// AIを管理する基底クラス
/// </summary>
class AI
{

public:

	//コンストラクタ
	AI();

	//デストラクタ
	~AI();//virtual付けたほうがいい？後で調べよう

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() {};

	/// <summary>
	/// 解放
	/// </summary>
	virtual void Release() {};

private:

	

};

