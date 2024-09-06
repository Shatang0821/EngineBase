#include "stdafx.h"
#include "Player.h"
#include "../Engine/InputManager.h"
#include "../Engine/RigidBody.h"
#include "../Engine/Debug.h"
#include "StateMachine.h"
#include "PlayerStates.h"
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

	InitStateMachine();
}

Player::~Player()
{
	if(stateMachine)
		delete stateMachine;
	stateMachine = nullptr;
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
	stateMachine->LogicUpdate(DeltaTime);
	
}

void Player::FixedUpdate(float fixedDeltaTime)
{
	StaticMesh::FixedUpdate(fixedDeltaTime);
	stateMachine->PhysicsUpdate(fixedDeltaTime);
}

void Player::DrawDebug()
{
	auto pos = GetWorldPosition() - mainWorld.GetMainCamera()->GetCameraPosition() + Vector2(WIDTH / 2, HEIGHT / 2);
	wchar_t text[50];
	swprintf(text, 50, L" %.1f,%.1f", GetWorldPosition().x, GetWorldPosition().y); // 数値を文字列に変換
	//Debug::RenderText(MyApp::Instance()->GetDevice(), pos.x + 16, pos.y + 16, text);
	Debug::RenderText(MyApp::Instance()->GetDevice(), 0, 60, text);
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

void Player::SetGravityScale(float scale)
{
	rigidBody->SetGravity(scale);
}

void Player::InitStateMachine()
{
	stateMachine = new StateMachine();

	stateMachine->RegisterState(PlayerStateType::IDLE, new PlayerIdleState(stateMachine,this,"idle"));
	stateMachine->RegisterState(PlayerStateType::RUN, new PlayerRunState(stateMachine,this,"run"));
	stateMachine->RegisterState(PlayerStateType::JUMP, new PlayerJumpState(stateMachine,this,"jump"));
	stateMachine->RegisterState(PlayerStateType::FALL, new PlayerFallState(stateMachine,this,"fall"));

	stateMachine->ChangeState(PlayerStateType::IDLE);
}

void Player::InitAnimation()
{
	// アニメーターの生成と設定
	animator = ConstructComponent<Animator>();
	animation[0].Load(ResID::Tex_Player_Idle, { 16,-10 });
	animation[0].Bind();
	animation[0].SetInterVal(0.1f);
	
	animation[1].Load(ResID::Tex_Player_Run, { 16,-10 });
	animation[1].Bind();
	animation[1].SetInterVal(0.15f);
	
	animation[2].Load(ResID::Tex_Player_Jump);
	animation[2].Bind();
	animation[2].SetInterVal(0.02f);
	
	animation[3].Load(ResID::Tex_Player_Fall);
	animation[3].Bind(false);
	animation[3].SetInterVal(0.15f);
	

	animator->Insert("idle", animation[0]);
	animator->Insert("run", animation[1]);
	animator->Insert("jump", animation[2]);
	animator->Insert("fall", animation[3]);
	animator->SetNode("idle");
}

void Player::SetAnimation(const std::string& name)
{
	animator->SetNode(name);
}

void Player::SetVelocity(const Vector2& velocity)
{
	rigidBody->SetVelocity(velocity);
}

void Player::SetVelocityX(float x)
{
	if (x < 0) {
		renderer->SetFlipX(true);
	}
	else if(x > 0)
		{
		renderer->SetFlipX(false);
	}
		
	rigidBody->SetVelocity(Vector2(x,rigidBody->GetVelocity().y));
}

void Player::SetVelocityY(float y)
{
	rigidBody->SetVelocity(Vector2(rigidBody->GetVelocity().x,y));
}

Vector2 Player::GetVelocity()
{
	return rigidBody->GetVelocity();
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




