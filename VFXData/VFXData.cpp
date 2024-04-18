#include "VFXData.h"

namespace HitEffect {
	std::string FILENAME = "VFX/cloudA.png";			//画像ファイル名
	XMFLOAT3 POSITIONRND = XMFLOAT3(0.5f, 0.5f, 0.5f);	//位置の誤差
	XMFLOAT3 DIRECTIONRND = XMFLOAT3(90, 90, 90);		//移動方向の誤差（各軸の角度）
	float	 SPEED = 0.2f;			//1フレームの速度
	float	 SPEEDRND = ZERO;		//速度誤差（0～1）
	float	 ACCEL = 1.0f;			//加速度
	float	 GRAVITY = 0.0f;		//重力
	XMFLOAT4 COLOR = XMFLOAT4(1, 1, ZERO, 1);					//色（RGBA 0～1）
	XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, -0.03f, ZERO, -0.02f);	//色の変化量
	XMFLOAT3 ROTATE = ZERO_FLOAT3;		//各軸での角度
	XMFLOAT3 ROTATERND = ZERO_FLOAT3;	//角度誤差
	XMFLOAT3 SPIN = ZERO_FLOAT3;		//回転速度
	XMFLOAT2 SIZE = XMFLOAT2(0.3, 0.3f);			//サイズ
	XMFLOAT2 SIZERND = XMFLOAT2(0.4, 0.4f);			//サイズ誤差（0～1）
	XMFLOAT2 SCALE = XMFLOAT2(0.9f, 0.9f);			//1フレームの拡大率
	DWORD	 LIFETIME = 15;		//パーティクルの寿命（フレーム数）
	DWORD	 DELAY = ZERO;		//何フレームおきにパーティクルを発生させるか
	DWORD	 NUMBER = 40;		//1度に出すパーティクル量
	bool	 ISBILLBOARD = true;		//ビルボードかどうか
}

namespace DieEffect {
	namespace Explosion {
		std::string FILENAME = "VFX/cloudA.png";				//画像ファイル名	
		XMFLOAT3 POSITIONRND = ZERO_FLOAT3;						//位置の誤差
		XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1.0f, ZERO);		//移動方向
		XMFLOAT3 DIRECTIONRND = XMFLOAT3(90, 90, 90);			//移動方向の誤差（各軸の角度）
		float	 SPEED = 0.1f;			//1フレームの速度
		float	 SPEEDRND = 0.8f;		//速度誤差（0～1）
		float	 ACCEL = 1.0f;			//加速度
		float	 GRAVITY = 0.0f;		//重力
		XMFLOAT4 COLOR = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);					//色（RGBA 0～1）
		XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, -1.0 / 20, ZERO, -1.0 / 20);	//色の変化量
		XMFLOAT3 ROTATE = ZERO_FLOAT3;			//各軸での角度
		XMFLOAT3 ROTATERND = ZERO_FLOAT3;		//角度誤差
		XMFLOAT3 SPIN = ZERO_FLOAT3;			//回転速度
		XMFLOAT2 SIZE = XMFLOAT2(1.2f, 1.2f);			//サイズ
		XMFLOAT2 SIZERND = XMFLOAT2(0.4, 0.4f);			//サイズ誤差（0～1）
		XMFLOAT2 SCALE = XMFLOAT2(1.05f, 1.05f);		//1フレームの拡大率
		DWORD	 LIFETIME = 30;		//パーティクルの寿命（フレーム数）
		DWORD	 DELAY = ZERO;		//何フレームおきにパーティクルを発生させるか
		DWORD	 NUMBER = 80;		//1度に出すパーティクル量
		bool	 ISBILLBOARD = true;		//ビルボードかどうか
	}
	namespace FireSpark {
		std::string FILENAME = "VFX/cloudA.png";			//画像ファイル名
		XMFLOAT3 POSITIONRND = XMFLOAT3(0.5f, ZERO, 0.5f);	//位置の誤差
		XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1, ZERO);		//移動方向
		XMFLOAT3 DIRECTIONRND = XMFLOAT3(90, 90, 90);		//移動方向の誤差（各軸の角度）
		float	 SPEED = 0.25f;			//1フレームの速度
		float	 SPEEDRND = 1.0f;		//速度誤差（0～1）
		float	 ACCEL = 0.93f;			//加速度
		float	 GRAVITY = 0.003f;		//重力
		XMFLOAT4 COLOR = XMFLOAT4(1, 1, 0.1f, 1);					//色（RGBA 0～1）
		XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, ZERO, ZERO, ZERO);		//色の変化量
		XMFLOAT3 ROTATE = ZERO_FLOAT3;		//各軸での角度
		XMFLOAT3 ROTATERND = ZERO_FLOAT3;	//角度誤差
		XMFLOAT3 SPIN = ZERO_FLOAT3;		//回転速度
		XMFLOAT2 SIZE = XMFLOAT2(0.1f, 0.1f);				//サイズ
		XMFLOAT2 SIZERND = XMFLOAT2(0.4f, 0.4f);			//サイズ誤差（0～1）
		XMFLOAT2 SCALE = XMFLOAT2(0.99f, 0.99f);			//1フレームの拡大率
		DWORD	 LIFETIME = 100;		//パーティクルの寿命（フレーム数）
		DWORD	 DELAY = ZERO;			//何フレームおきにパーティクルを発生させるか
		DWORD	 NUMBER = 80;			//1度に出すパーティクル量
		bool	 ISBILLBOARD = true;			//ビルボードかどうか
	}
	
}

namespace VictoryEffect {
	namespace Fire {
		std::string FILENAME = "VFX/cloudA.png";			//画像ファイル名
		XMFLOAT3 POSITIONRND = XMFLOAT3(0.1f, 0, 0.1f);		//位置の誤差
		XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1, ZERO);		//移動方向
		XMFLOAT3 DIRECTIONRND = ZERO_FLOAT3;		//移動方向の誤差（各軸の角度）
		float	 SPEED = 0.01f;			//1フレームの速度
		float	 SPEEDRND = ZERO;		//速度誤差（0～1）
		float	 ACCEL = 1.0f;			//加速度
		float	 GRAVITY = -0.002f;		//重力
		XMFLOAT4 COLOR = XMFLOAT4(1, 1, ZERO, 1);					//色（RGBA 0～1）
		XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, -0.03f, ZERO, -0.02f);		//色の変化量
		XMFLOAT3 ROTATE = ZERO_FLOAT3;		//各軸での角度
		XMFLOAT3 ROTATERND = ZERO_FLOAT3;	//角度誤差
		XMFLOAT3 SPIN = ZERO_FLOAT3;		//回転速度
		XMFLOAT2 SIZE = XMFLOAT2(1.5f, 1.5f);				//サイズ
		XMFLOAT2 SIZERND = XMFLOAT2(0.4f, 0.4f);			//サイズ誤差（0～1）
		XMFLOAT2 SCALE = XMFLOAT2(1.01f, 1.01f);			//1フレームの拡大率
		DWORD	 LIFETIME = 60;		//パーティクルの寿命（フレーム数）
		DWORD	 DELAY = ZERO;			//何フレームおきにパーティクルを発生させるか
		DWORD	 NUMBER = 1;			//1度に出すパーティクル量
		bool	 ISBILLBOARD = true;			//ビルボードかどうか
	}
	namespace FireSpark {
		std::string FILENAME = "VFX/cloudA.png";			//画像ファイル名
		XMFLOAT3 POSITIONRND = XMFLOAT3(0.8f, ZERO, 0.8f);		//位置の誤差
		XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1, ZERO);		//移動方向
		XMFLOAT3 DIRECTIONRND = XMFLOAT3(10, 10, 10);		//移動方向の誤差（各軸の角度）
		float	 SPEED = 0.1f;			//1フレームの速度
		float	 SPEEDRND = ZERO;		//速度誤差（0～1）
		float	 ACCEL = 1.0f;			//加速度
		float	 GRAVITY = ZERO;		//重力
		XMFLOAT4 COLOR = XMFLOAT4(1, 1, ZERO, 1);					//色（RGBA 0～1）
		XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, -0.03f, ZERO, -0.02f);		//色の変化量
		XMFLOAT3 ROTATE = ZERO_FLOAT3;		//各軸での角度
		XMFLOAT3 ROTATERND = ZERO_FLOAT3;	//角度誤差
		XMFLOAT3 SPIN = ZERO_FLOAT3;		//回転速度
		XMFLOAT2 SIZE = XMFLOAT2(0.2f, 0.2f);				//サイズ
		XMFLOAT2 SIZERND = XMFLOAT2(0.4f, 0.4f);			//サイズ誤差（0～1）
		XMFLOAT2 SCALE = XMFLOAT2(0.95, 0.95);;			//1フレームの拡大率
		DWORD	 LIFETIME = 120;		//パーティクルの寿命（フレーム数）
		DWORD	 DELAY = ZERO;			//何フレームおきにパーティクルを発生させるか
		DWORD	 NUMBER = 3;			//1度に出すパーティクル量
		bool	 ISBILLBOARD = true;			//ビルボードかどうか
	}
}

namespace FiringEffect {
	std::string FILENAME = "VFX/cloudA.png";			//画像ファイル名
	XMFLOAT3 POSITIONRND = XMFLOAT3(0.1f, ZERO, 0.1f);		//位置の誤差
	XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1, ZERO);		//移動方向
	XMFLOAT3 DIRECTIONRND = XMFLOAT3(ZERO, ZERO, ZERO);		//移動方向の誤差（各軸の角度）
	float	 SPEED = 0.1f;			//1フレームの速度
	float	 SPEEDRND = ZERO;		//速度誤差（0～1）
	float	 ACCEL = 0.98f;			//加速度
	float	 GRAVITY = ZERO;		//重力
	XMFLOAT4 COLOR = XMFLOAT4(1, 1, 1, 0.2);					//色（RGBA 0～1）
	XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, ZERO, ZERO, -0.002f);		//色の変化量
	XMFLOAT3 ROTATE = ZERO_FLOAT3;		//各軸での角度
	XMFLOAT3 ROTATERND = ZERO_FLOAT3;	//角度誤差
	XMFLOAT3 SPIN = XMFLOAT3(ZERO, ZERO, 0.1f);		//回転速度
	XMFLOAT2 SIZE = XMFLOAT2(2, 2);				//サイズ
	XMFLOAT2 SIZERND = XMFLOAT2(0.4f, 0.4f);			//サイズ誤差（0～1）
	XMFLOAT2 SCALE = XMFLOAT2(1.01f, 1.01f);;			//1フレームの拡大率
	DWORD	 LIFETIME = 30;		//パーティクルの寿命（フレーム数）
	DWORD	 DELAY = ZERO;			//何フレームおきにパーティクルを発生させるか
	DWORD	 NUMBER = 2;			//1度に出すパーティクル量
	bool	 ISBILLBOARD = true;			//ビルボードかどうか
}