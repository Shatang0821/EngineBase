#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "RigidBody.h"
#include "Debug.h"
/**
 * @brief Playerのコンストラクタ。
 *
 * プレイヤーの初期設定を行います。
 */
Player::Player()
	: anchorPoint({ 0,0 })
	, length(100)
	, angle(D3DX_PI / 2)
	, angularVelocity(0)
	, angularAcceleration(0)
	, animator(nullptr)
	, boxCollider(nullptr)
	, circleCollider(nullptr)
	, rigidBody(nullptr)
{
	// レイヤーの設定
	auto spriteRenderer = GetComponentByClass<SpriteRenderer>();
	spriteRenderer->SetLayer(1);

	// アニメーターの生成と設定
	animator = ConstructComponent<Animator>();
	ani.Load(ResID::Tex_Player);
	ani.SetInterVal(0.02f);

	animator->Insert("idle", ani);
	animator->SetNode("idle");

	// ボックスコライダーの設定
	boxCollider = ConstructComponent<BoxCollider>();
	boxCollider->AttachTo(root);
	boxCollider->SetSize(Vector2(32, 32));

	// サークルコライダーの設定
	circleCollider = ConstructComponent<CircleCollider>();
	circleCollider->AttachTo(root);
	circleCollider->SetRadius(16);

	// 剛体コンポーネントの設定
	rigidBody = ConstructComponent<RigidBody>();
	rigidBody->SetGravity(9.8f);
	//rigidBody->SetGravityEnabled(false);

	//初期位置の設定
	//固定点から長さと角度を使って初期位置を計算
	auto newPos = anchorPoint + Vector2(0, length);
	SetLocalPosition(newPos);
}


/**
 * @brief プレイヤーの更新処理。
 *
 * キー入力に応じてプレイヤーを移動させます。
 * @param DeltaTime 前フレームからの経過時間
 */
void Player::Update(float DeltaTime)
{
	StaticMesh::Update(DeltaTime);

	// Wキーで上に移動
	if (InputManager::Instance()->IsPushKey(DIK_W))
	{
		anchorPoint += Vector2(0, -100) * DeltaTime;
	}
	// Sキーで下に移動
	if (InputManager::Instance()->IsPushKey(DIK_S))
	{
		anchorPoint += Vector2(0, 100) * DeltaTime;
	}
	// Aキーで左に移動
	if (InputManager::Instance()->IsPushKey(DIK_A))
	{
		anchorPoint += Vector2(-100, 0) * DeltaTime;
	}
	// Dキーで右に移動
	if (InputManager::Instance()->IsPushKey(DIK_D))
	{
		anchorPoint += Vector2(100, 0) * DeltaTime;
	}
}

void Player::FixedUpdate(float fixedDeltaTime)
{
	//重力の取得
	auto g = rigidBody->GetGravity();

	//固定点とのなす角の計算
	Vector2 gravity = { 0,rigidBody->GetGravity() };
	Vector2 direction = GetLocalPosition() - anchorPoint;
	direction = direction.normalized();

	angle = acos(gravity.dot(direction) / (gravity.Length() * direction.Length()));

	auto xForce = (g * sin(angle) * -1) * direction.x;
	auto yForce = (g * cos(angle) * -1) * direction.y;

	if (gravity.cross(direction) > 0)
	{
		rigidBody->AddForce({ xForce,yForce });
	}
	else
	{
		rigidBody->AddForce({ xForce,yForce });
	}
	

	std::cout << yForce << std::endl;
	//anchorPoint.angleBetween(GetLocalPosition());
	//std::cout << angle << std::endl;
	//std::cout << gravity.cross(direction) << std::endl;

	StaticMesh::FixedUpdate(fixedDeltaTime);

	
}

void Player::DrawDebug()
{
	auto pos = GetWorldPosition() - mainWorld.GetMainCamera()->GetCameraPosition() + Vector2(WIDTH / 2, HEIGHT / 2);
	wchar_t text[50];
	swprintf(text, 50, L" %.1f,%.1f", GetLocalPosition().x, GetLocalPosition().y); // 数値を文字列に変換
	Debug::RenderText(MyApp::Instance()->GetDevice(), pos.x, pos.y, text);
	
	auto startPos= anchorPoint - mainWorld.GetMainCamera()->GetCameraPosition() + Vector2(WIDTH / 2, HEIGHT / 2);
	auto endPos = GetWorldPosition() - mainWorld.GetMainCamera()->GetCameraPosition() + Vector2(WIDTH / 2, HEIGHT / 2);
	
	Debug::DrawLine(startPos, endPos, D3DCOLOR_XRGB(0, 255, 0));
}


