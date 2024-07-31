#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "RigidBody.h"
#include "Debug.h"
#include "StateMachine.h"

/**
 * @brief Playerのコンストラクタ。
 *
 * プレイヤーの初期設定を行います。
 */
Player::Player()
	: animator(nullptr)
	, boxCollider(nullptr)
	//, circleCollider(nullptr)
	, rigidBody(nullptr)
{
	// レイヤーの設定
	auto spriteRenderer = GetComponentByClass<SpriteRenderer>();
	spriteRenderer->SetLayer(1);
	
	InitAnimation();

	InitPhysics();

}

void Player::InitPhysics()
{
	// ボックスコライダーの設定
	boxCollider = ConstructComponent<BoxCollider>();
	boxCollider->AttachTo(root);
	boxCollider->SetSize(Vector2(32, 64));

	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &Player::BeginOverlap);
	boxCollider->OnComponentEndOverlap.AddDynamic(this, &Player::EndOverlap);
	boxCollider->OnComponentHit.AddDynamic(this, &Player::OnHit);
	boxCollider->SetType(CollisionType::Default);

	// 剛体コンポーネントの設定
	rigidBody = ConstructComponent<RigidBody>();
	rigidBody->SetGravity(100.0f);
	//rigidBody->SetGravityEnabled(false);
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
	
}

void Player::FixedUpdate(float fixedDeltaTime)
{
	StaticMesh::FixedUpdate(fixedDeltaTime);
	if (InputManager::Instance()->IsPushKeyOne(DIK_SPACE))
	{
		rigidBody->SetVelocity({ rigidBody->GetVelocity().x,-100 });
	}
	// Aキーで左に移動
	if (InputManager::Instance()->IsPushKey(DIK_A))
	{
		//anchorPoint += Vector2(-100, 0) * DeltaTime;
		rigidBody->SetVelocity(Vector2(-100, rigidBody->GetVelocity().y));
		animator->SetNode("run");
	}
	// Dキーで右に移動
	else if (InputManager::Instance()->IsPushKey(DIK_D))
	{
		//anchorPoint += Vector2(100, 0) * DeltaTime;
		rigidBody->SetVelocity(Vector2(100, rigidBody->GetVelocity().y));
		animator->SetNode("run");
	}
	else
	{
		rigidBody->SetVelocity({ 0, rigidBody->GetVelocity().y });
		animator->SetNode("idle");
	}
	
	
}

void Player::DrawDebug()
{
	auto pos = GetWorldPosition() - mainWorld.GetMainCamera()->GetCameraPosition() + Vector2(WIDTH / 2, HEIGHT / 2);
	wchar_t text[50];
	swprintf(text, 50, L" %.1f,%.1f", GetWorldPosition().x, GetWorldPosition().y); // 数値を文字列に変換
	//Debug::RenderText(MyApp::Instance()->GetDevice(), pos.x + 16, pos.y + 16, text);
	Debug::RenderText(MyApp::Instance()->GetDevice(), 0, 60, text);
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

void Player::OnHit(Collider* hitComp, Collider* otherComp, Object* otherActor, Vector2 hitNormal, const HitResult& hitResult)
{
	std::cout << "Hit" << std::endl;
}

void Player::InitAnimation()
{
	// アニメーターの生成と設定
	animator = ConstructComponent<Animator>();
	animation[0].Load(ResID::Tex_Player_Idle);
	animation[0].SetInterVal(0.02f);
	animation[1].Load(ResID::Tex_Player_Run);
	animation[1].SetInterVal(0.02f);

	animator->Insert("idle", animation[0]);
	animator->Insert("run", animation[1]);
	animator->SetNode("run");
}


