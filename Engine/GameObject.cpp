#include "gameObject.h"
#include <assert.h>
#include "global.h"

//コンストラクタ（親も名前もなし）
GameObject::GameObject(void) :
	GameObject(nullptr, "")
{

}

//コンストラクタ（名前なし）
GameObject::GameObject(GameObject* parent) :
	GameObject(parent, "")
{
}

//コンストラクタ（標準）
GameObject::GameObject(GameObject* parent, const std::string& name)
	: pParent_(parent), objectName_(name), objectID_('N')
{
	childList_.clear();
	state_ = { 0, 1, 1, 0 };

	if (parent)
		transform_.pParent_ = &parent->transform_;

}

//デストラクタ
GameObject::~GameObject()
{
	for (auto it = colliderList_.begin(); it != colliderList_.end(); it++)
	{
		SAFE_DELETE(*it);
	}
	colliderList_.clear();
}

// 削除するかどうか
bool GameObject::IsDead()
{
	return (state_.dead != 0);
}

// 自分を削除する
void GameObject::KillMe()
{
	state_.dead = 1;
}

// Updateを許可
void GameObject::Enter()
{
	state_.entered = 1;
}

// Updateを拒否
void GameObject::Leave()
{
	state_.entered = 0;
}

// Drawを許可
void GameObject::Visible()
{
	state_.visible = 1;
}

// Drawを拒否
void GameObject::Invisible()
{
	state_.visible = 0;
}

// 初期化済みかどうか
bool GameObject::IsInitialized()
{
	return (state_.initialized != 0);
}

// 初期化済みにする
void GameObject::SetInitialized()
{
	state_.initialized = 1;
}

// Update実行していいか
bool GameObject::IsEntered()
{
	return (state_.entered != 0);
}

// Draw実行していいか
bool GameObject::IsVisibled()
{
	return (state_.visible != 0);
}

//子オブジェクトリストを取得
std::list<GameObject*>* GameObject::GetChildList()
{
	return &childList_;
}

//親オブジェクトを取得
GameObject* GameObject::GetParent(void)
{
	return pParent_;
}

//名前でオブジェクトを検索（対象は自分の子供以下）
GameObject* GameObject::FindChildObject(const std::string& name)
{
	//子供がいないなら終わり
	if (childList_.empty())
		return nullptr;

	//イテレータ
	auto it = childList_.begin();	//先頭
	auto end = childList_.end();	//末尾

	//子オブジェクトから探す
	while (it != end) {
		//同じ名前のオブジェクトを見つけたらそれを返す
		if ((*it)->GetObjectName() == name)
			return *it;

		//その子供（孫）以降にいないか探す
		GameObject* obj = (*it)->FindChildObject(name);
		if (obj != nullptr)
		{
			return obj;
		}

		//次の子へ
		it++;
	}

	//見つからなかった
	return nullptr;
}

//オブジェクトの名前を取得
const std::string& GameObject::GetObjectName(void) const
{
	return objectName_;
}

//子オブジェクトを追加（リストの最後へ）
void GameObject::PushBackChild(GameObject* obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_back(obj);
}

//子オブジェクトを追加（リストの先頭へ）
void GameObject::PushFrontChild(GameObject* obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_front(obj);
}

//子オブジェクトを全て削除
void GameObject::KillAllChildren(void)
{
	//子供がいないなら終わり
	if (childList_.empty())
		return;

	//イテレータ
	auto it = childList_.begin();	//先頭
	auto end = childList_.end();	//末尾

	//子オブジェクトを1個ずつ削除
	while (it != end)
	{
		KillObjectSub(*it);
		delete* it;
		it = childList_.erase(it);
	}

	//リストをクリア
	childList_.clear();
}

//オブジェクト削除（再帰）
void GameObject::KillObjectSub(GameObject* obj)
{
	if (!childList_.empty())
	{
		auto list = obj->GetChildList();
		auto it = list->begin();
		auto end = list->end();
		while (it != end)
		{
			KillObjectSub(*it);
			delete* it;
			it = list->erase(it);
		}
		list->clear();
	}
	obj->Release();
}



//コライダー（衝突判定）を追加する
void GameObject::AddCollider(Collider* collider)
{
	collider->SetGameObject(this);
	colliderList_.push_back(collider);
}

//コライダー（衝突判定）を削除
void GameObject::ClearCollider()
{
	for (auto it = colliderList_.begin(); it != colliderList_.end(); it++)
	{
		SAFE_DELETE(*it);
	}
	colliderList_.clear();
}

//衝突判定
void GameObject::Collision(GameObject* pTarget)
{
	//自分同士の当たり判定はしない
	if (pTarget == nullptr || this == pTarget)
	{
		return;
	}

	//自分とpTargetのコリジョン情報を使って当たり判定
	//1つのオブジェクトが複数のコリジョン情報を持ってる場合もあるので二重ループ
	for (auto i = this->colliderList_.begin(); i != this->colliderList_.end(); i++)
	{
		for (auto j = pTarget->colliderList_.begin(); j != pTarget->colliderList_.end(); j++)
		{
			if ((*i)->IsHit(*j))
			{
				//当たった
				this->OnCollision(pTarget);
			}
		}
	}

	//子供がいないなら終わり
	if (pTarget->childList_.empty())
		return;

	//子供も当たり判定
	for (auto i = pTarget->childList_.begin(); i != pTarget->childList_.end(); i++)
	{
		Collision(*i);
	}
}


//テスト用の衝突判定枠を表示
void GameObject::CollisionDraw()
{
	Direct3D::SetShader(Direct3D::SHADER_UNLIT);

	for (auto i = this->colliderList_.begin(); i != this->colliderList_.end(); i++)
	{
		(*i)->Draw(GetWorldPosition());
	}

	Direct3D::SetShader(Direct3D::SHADER_3D);
}

//RootJobを取得
GameObject* GameObject::GetRootJob()
{
	if (GetParent() == nullptr)
	{
		return this;
	}
	else return GetParent()->GetRootJob();
}




void GameObject::UpdateSub()
{
	Update();
	Transform();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->UpdateSub();
	}

	for (auto it = childList_.begin(); it != childList_.end();)
	{
		if ((*it)->IsDead() == true)
		{
			(*it)->ReleaseSub();
			SAFE_DELETE(*it);
			it = childList_.erase(it);
		}
		else
		{
			//当たり判定
			(*it)->Collision(GetParent());
			it++;
		}
	}
}

void GameObject::DrawSub()
{
	Draw();


	//リリース時は削除
#ifdef _DEBUG
		//コリジョンの描画
	if (Direct3D::isDrawCollision_)
	{
		CollisionDraw();
	}
#endif

	//その子オブジェクトの描画処理
	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	//コライダーを削除
	ClearCollider();


	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->ReleaseSub();
		SAFE_DELETE(*it);
	}

	Release();
}

void GameObject::Imgui_WindowSub()
{

	Imgui_Window();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->Imgui_WindowSub();
	}
}




////ローカル行列の取得（このオブジェクトの行列）
//XMMATRIX GameObject::GetLocalMatrix(void)
//{
//	return transform_.GetWorldMatrix();
//}

//ワールド行列の取得（親の影響を受けた最終的な行列）
XMMATRIX GameObject::GetWorldMatrix(void)
{
	return transform_.GetWorldMatrix();
}

void GameObject::Setting_Transform(Transform& _transform, float posmin, float posmax, float rot, float scl, std::string str)
{

	float* p[] = { &_transform.position_.x ,&_transform.position_.y, &_transform.position_.z };
	float* r[] = { &_transform.rotate_.x ,&_transform.rotate_.y, &_transform.rotate_.z };
	float s = _transform.scale_.x;

	std::string tmpString = str;
	tmpString = str + "sPosition.x";
	char* c = new char[tmpString.size() + 1];
	strcpy_s(c, tmpString.size() + 1, tmpString.c_str());
	ImGui::SliderFloat(c, p[0], posmin, posmax);

	tmpString = str + "sPosition.y";
	strcpy_s(c, tmpString.size() + 1, tmpString.c_str());
	ImGui::SliderFloat(c, p[1], posmin, posmax);

	tmpString = str + "sPosition.z";
	strcpy_s(c, tmpString.size() + 1, tmpString.c_str());
	ImGui::SliderFloat(c, p[2], posmin, posmax);

	tmpString = str + "sRotate";
	strcpy_s(c, tmpString.size() + 1, tmpString.c_str());
	ImGui::SliderFloat3(c, *r, 0.0f, rot);

	tmpString = str + "sScale";
	strcpy_s(c, tmpString.size() + 1, tmpString.c_str());
	ImGui::SliderFloat(c, &s, 0.0f, scl);

	_transform.scale_.x = s;
	_transform.scale_.y = s;
	_transform.scale_.z = s;


	delete[] c;

}

void GameObject::Save_Transform_File(Transform _transform, HANDLE hFile, LPCSTR fileName)
{
	hFile = CreateFile(
		fileName,                 //ファイル名
		GENERIC_WRITE,           //アクセスモード（書き込み用）
		0,                      //共有（なし）
		NULL,                   //セキュリティ属性（継承しない）
		CREATE_ALWAYS,           //作成方法
		FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
		NULL);                  //拡張属性（なし


	float* save[] = { &_transform.position_.x, &_transform.position_.y, &_transform.position_.z,
					  &_transform.rotate_.x, &_transform.rotate_.y, &_transform.rotate_.z,
					  &_transform.scale_.x };

	const int size = sizeof(save) / sizeof(save[0]);

	std::string s[size];

	for (int i = 0; i < size; i++) {
		s[i] = std::to_string(*save[i]) + " ";
	}

	DWORD dwBytes = 0;  //書き込み位置

	for (int i = 0; i < size; i++) {

		WriteFile(
			hFile,                   //ファイルハンドル
			s[i].c_str(),                  //保存するデータ（文字列）
			(DWORD)strlen(s[i].c_str()),   //書き込む文字数
			&dwBytes,                //書き込んだサイズを入れる変数
			NULL);                   //オーバーラップド構造体（今回は使わない）

	}

	CloseHandle(hFile);
}

void GameObject::Load_Transform_File(HANDLE hFile, LPCSTR fileName)
{
	hFile = CreateFile(
		fileName,                 //ファイル名
		GENERIC_READ,           //アクセスモード（書き込み用）
		0,                      //共有（なし）
		NULL,                   //セキュリティ属性（継承しない）
		OPEN_ALWAYS,           //作成方法
		FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
		NULL);

	//ファイルのサイズを取得
	DWORD fileSize = GetFileSize(hFile, NULL);

	//ファイルのサイズ分メモリを確保
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //読み込み位置

	ReadFile(
		hFile,     //ファイルハンドル
		data,      //データを入れる変数
		fileSize,  //読み込むサイズ
		&dwBytes,  //読み込んだサイズ
		NULL);     //オーバーラップド構造体（今回は使わない）

	//ここでファイルサイズ文繰り返して、空白が出たらそれまでの値をポジションなりに入れるとかがよさそう
	//最初はchar型のtmpに入れといて後でstringに入れなおすとかでもよさそう
	char* tmp = new char[fileSize];
	int c = 0, sw = 0;
	for (DWORD i = 0; i < fileSize; i++) {

		if (data[i] == ' ') {
			switch (sw)
			{
			case 0:
				transform_.position_.x = std::stof(tmp);
				break;
			case 1:
				transform_.position_.y = std::stof(tmp);
				break;
			case 2:
				transform_.position_.z = std::stof(tmp);
				break;
			case 3:
				transform_.rotate_.x = std::stof(tmp);
				break;
			case 4:
				transform_.rotate_.y = std::stof(tmp);
				break;
			case 5:
				transform_.rotate_.z = std::stof(tmp);
				break;
			case 6:
				transform_.scale_.x = std::stof(tmp);
				transform_.scale_.y = std::stof(tmp);
				transform_.scale_.z = std::stof(tmp);
				break;

			default:
				break;
			}
			sw++;
			c = 0;
			continue;
		}
		tmp[c] = data[i];
		c++;
	}
	delete[] tmp;
	delete[] data;

	CloseHandle(hFile);
}