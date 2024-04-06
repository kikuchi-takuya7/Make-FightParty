#pragma once
#include "../Engine/Direct3D.h"
#include "../Engine/Global.h"
#include<string>

namespace HitEffect {
	extern std::string FILENAME;	//画像ファイル名
	extern XMFLOAT3 POSITIONRND;	//位置の誤差
	extern XMFLOAT3 DIRECTIONRND;	//移動方向の誤差（各軸の角度）
	extern float	SPEED;			//1フレームの速度
	extern float	SPEEDRND;		//速度誤差（0～1）
	extern float	ACCEL;			//加速度
	extern float	GRAVITY;		//重力
	extern XMFLOAT4 COLOR;			//色（RGBA 0～1）
	extern XMFLOAT4 DELTACOLOR;		//色の変化量
	extern XMFLOAT3 ROTATE;			//各軸での角度
	extern XMFLOAT3 ROTATERND;		//角度誤差
	extern XMFLOAT3 SPIN;			//回転速度
	extern XMFLOAT2 SIZE;			//サイズ
	extern XMFLOAT2 SIZERND;		//サイズ誤差（0～1）
	extern XMFLOAT2 SCALE;			//1フレームの拡大率
	extern DWORD	LIFETIME;		//パーティクルの寿命（フレーム数）
	extern DWORD	DELAY;			//何フレームおきにパーティクルを発生させるか
	extern DWORD	NUMBER;			//1度に出すパーティクル量
	extern bool	 ISBILLBOARD;		//ビルボードかどうか
}

namespace DieEffect {
	namespace Explosion {
		extern std::string FILENAME;	//画像ファイル名
		extern XMFLOAT3 POSITIONRND;	//位置の誤差
		extern XMFLOAT3 DIRECTION;		//移動方向
		extern XMFLOAT3 DIRECTIONRND;	//移動方向の誤差（各軸の角度）
		extern float	SPEED;			//1フレームの速度
		extern float	SPEEDRND;		//速度誤差（0～1）
		extern float	ACCEL;			//加速度
		extern float	GRAVITY;		//重力
		extern XMFLOAT4 COLOR;			//色（RGBA 0～1）
		extern XMFLOAT4 DELTACOLOR;		//色の変化量
		extern XMFLOAT3 ROTATE;			//各軸での角度
		extern XMFLOAT3 ROTATERND;		//角度誤差
		extern XMFLOAT3 SPIN;			//回転速度
		extern XMFLOAT2 SIZE;			//サイズ
		extern XMFLOAT2 SIZERND;		//サイズ誤差（0～1）
		extern XMFLOAT2 SCALE;			//1フレームの拡大率
		extern DWORD	LIFETIME;		//パーティクルの寿命（フレーム数）
		extern DWORD	DELAY;			//何フレームおきにパーティクルを発生させるか
		extern DWORD	NUMBER;			//1度に出すパーティクル量
		extern bool	 ISBILLBOARD;		//ビルボードかどうか
	}
	namespace FireSpark {
		extern std::string FILENAME;	//画像ファイル名
		extern XMFLOAT3 POSITIONRND;	//位置の誤差
		extern XMFLOAT3 DIRECTION;		//移動方向
		extern XMFLOAT3 DIRECTIONRND;	//移動方向の誤差（各軸の角度）
		extern float	SPEED;			//1フレームの速度
		extern float	SPEEDRND;		//速度誤差（0～1）
		extern float	ACCEL;			//加速度
		extern float	GRAVITY;		//重力
		extern XMFLOAT4 COLOR;			//色（RGBA 0～1）
		extern XMFLOAT4 DELTACOLOR;		//色の変化量
		extern XMFLOAT3 ROTATE;			//各軸での角度
		extern XMFLOAT3 ROTATERND;		//角度誤差
		extern XMFLOAT3 SPIN;			//回転速度
		extern XMFLOAT2 SIZE;			//サイズ
		extern XMFLOAT2 SIZERND;		//サイズ誤差（0～1）
		extern XMFLOAT2 SCALE;			//1フレームの拡大率
		extern DWORD	LIFETIME;		//パーティクルの寿命（フレーム数）
		extern DWORD	DELAY;			//何フレームおきにパーティクルを発生させるか
		extern DWORD	NUMBER;			//1度に出すパーティクル量
		extern bool	 ISBILLBOARD;		//ビルボードかどうか
	}

}

namespace VictoryEffect {
	namespace Fire {
		extern std::string FILENAME;	//画像ファイル名
		extern XMFLOAT3 POSITIONRND;	//位置の誤差
		extern XMFLOAT3 DIRECTION;		//移動方向
		extern XMFLOAT3 DIRECTIONRND;	//移動方向の誤差（各軸の角度）
		extern float	SPEED;			//1フレームの速度
		extern float	SPEEDRND;		//速度誤差（0～1）
		extern float	ACCEL;			//加速度
		extern float	GRAVITY;		//重力
		extern XMFLOAT4 COLOR;			//色（RGBA 0～1）
		extern XMFLOAT4 DELTACOLOR;		//色の変化量
		extern XMFLOAT3 ROTATE;			//各軸での角度
		extern XMFLOAT3 ROTATERND;		//角度誤差
		extern XMFLOAT3 SPIN;			//回転速度
		extern XMFLOAT2 SIZE;			//サイズ
		extern XMFLOAT2 SIZERND;		//サイズ誤差（0～1）
		extern XMFLOAT2 SCALE;			//1フレームの拡大率
		extern DWORD	LIFETIME;		//パーティクルの寿命（フレーム数）
		extern DWORD	DELAY;			//何フレームおきにパーティクルを発生させるか
		extern DWORD	NUMBER;			//1度に出すパーティクル量
		extern bool	 ISBILLBOARD;		//ビルボードかどうか
	}
	namespace FireSpark {
		extern std::string FILENAME;	//画像ファイル名
		extern XMFLOAT3 POSITIONRND;	//位置の誤差
		extern XMFLOAT3 DIRECTION;		//移動方向
		extern XMFLOAT3 DIRECTIONRND;	//移動方向の誤差（各軸の角度）
		extern float	SPEED;			//1フレームの速度
		extern float	SPEEDRND;		//速度誤差（0～1）
		extern float	ACCEL;			//加速度
		extern float	GRAVITY;		//重力
		extern XMFLOAT4 COLOR;			//色（RGBA 0～1）
		extern XMFLOAT4 DELTACOLOR;		//色の変化量
		extern XMFLOAT3 ROTATE;			//各軸での角度
		extern XMFLOAT3 ROTATERND;		//角度誤差
		extern XMFLOAT3 SPIN;			//回転速度
		extern XMFLOAT2 SIZE;			//サイズ
		extern XMFLOAT2 SIZERND;		//サイズ誤差（0～1）
		extern XMFLOAT2 SCALE;			//1フレームの拡大率
		extern DWORD	LIFETIME;		//パーティクルの寿命（フレーム数）
		extern DWORD	DELAY;			//何フレームおきにパーティクルを発生させるか
		extern DWORD	NUMBER;			//1度に出すパーティクル量
		extern bool	 ISBILLBOARD;		//ビルボードかどうか
	}

}