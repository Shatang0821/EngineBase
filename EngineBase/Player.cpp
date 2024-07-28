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
	//, circleCollider(nullptr)
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
	boxCollider->SetSize(Vector2(64, 64));

	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &Player::BeginOverlap);
	boxCollider->OnComponentEndOverlap.AddDynamic(this, &Player::EndOverlap);

	// サークルコライダーの設定
	//circleCollider = ConstructComponent<CircleCollider>();
	//circleCollider->AttachTo(root);
	//circleCollider->SetRadius(16);

	// 剛体コンポーネントの設定
	rigidBody = ConstructComponent<RigidBody>();
	rigidBody->SetGravity(9.8f);
	rigidBody->SetGravityEnabled(false);

	//初期位置の設定
	//固定点から長さと角度を使って初期位置を計算
	auto newPos = anchorPoint + Vector2(0, length);
	//SetLocalPosition(newPos);
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
		//Localpo += Vector2(0, -100) * DeltaTime;
		rigidBody->SetVelocity(Vector2(0, -100));
	}
	// Sキーで下に移動
	else if (InputManager::Instance()->IsPushKey(DIK_S))
	{
		//anchorPoint += Vector2(0, 100) * DeltaTime;
		rigidBody->SetVelocity(Vector2(0, 100));
	}
	else {
		rigidBody->SetVelocity({ rigidBody->GetVelocity().x, 0 });
	}
	// Aキーで左に移動
	if (InputManager::Instance()->IsPushKey(DIK_A))
	{
		//anchorPoint += Vector2(-100, 0) * DeltaTime;
		rigidBody->SetVelocity(Vector2(-100, 0));
	}
	// Dキーで右に移動
	else if (InputManager::Instance()->IsPushKey(DIK_D))
	{
		//anchorPoint += Vector2(100, 0) * DeltaTime;
		rigidBody->SetVelocity(Vector2(100, 0));
	}
	else{
		rigidBody->SetVelocity({ 0, rigidBody->GetVelocity().y });
	}
}

void Player::FixedUpdate(float fixedDeltaTime)
{
	StaticMesh::FixedUpdate(fixedDeltaTime);
	
}

void Player::DrawDebug()
{
	auto pos = GetWorldPosition() - mainWorld.GetMainCamera()->GetCameraPosition() + Vector2(WIDTH / 2, HEIGHT / 2);
	wchar_t text[50];
	swprintf(text, 50, L" %.1f,%.1f", GetWorldPosition().x, GetWorldPosition().y); // 数値を文字列に変換
	Debug::RenderText(MyApp::Instance()->GetDevice(), pos.x + 16, pos.y + 16, text);
	
	auto startPos= anchorPoint - mainWorld.GetMainCamera()->GetCameraPosition() + Vector2(WIDTH / 2, HEIGHT / 2);
	auto endPos = GetWorldPosition() - mainWorld.GetMainCamera()->GetCameraPosition() + Vector2(WIDTH / 2, HEIGHT / 2);
	
	Debug::DrawLine(startPos, endPos, D3DCOLOR_XRGB(0, 255, 0));
}

void Player::BeginOverlap(Collider* OverlapCpm, Collider* otherCpm, Object* OverlapActor)
{
	std::cout << "hello" << std::endl;
	std::cout << OverlapCpm->GetWorldPosition() << std::endl;
}

void Player::EndOverlap(Collider* OverlapCpm, Collider* otherCpm, Object* OverlapActor)
{
	std::cout << "goodbye" << std::endl;
}


