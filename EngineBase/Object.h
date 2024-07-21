/**
 * @file Object.h
 * @brief オブジェクトの基底クラスとなる
 *
 * このファイルには、ゲーム内すべてのオブジェクトの基底クラスが定義されています。
 *
 * @author サトウ
 * @date 2024/06/19
 */
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Base.h"
#include "SceneComponent.h"

/**
 * @class Object
 * @brief ゲームオブジェクトの基底クラス
 *
 * このクラスは、ゲーム内のオブジェクトを表し、複数のコンポーネントを保持します。
 */
class Object : public Base
{
	friend void Component::Destruct();
protected:

	//! オブジェクトの子要素を管理します。頻繁に削除や追加が行われるため、setを使用しています。
	std::unordered_set<Object*>children;
	//! オブジェクトの親要素を指します。削除追加しやすいため
	Object* parent = nullptr;

	//! オブジェクトのルートとなるTransformを示すシーンコンポーネントを指します
	SceneComponent * const root = new SceneComponent;
	//! オブジェクトに所属するコンポーネントを管理します。
	std::unordered_set<Component*>components;
	//! コンポーネントのイテレータ 追加削除予定のコンポーネントを管理します。
	std::unordered_set<Component*>::iterator components_iter;
public:
	/**
	 * @brief コンストラクタ
	 *
	 * ルートコンポーネント所有者設定
	 */
	Object() { root->SetOwner(this); }
	/**
	 * @brief デストラクタ
	 *
	 * コンポーネントをすべて削除する
	 */
	virtual ~Object() {

		components_iter = components.begin();
		while (components_iter != components.end()) {
			(*components_iter)->Destruct();
			//endを超えないように制御する
			if (components_iter == components.end()) break;
		}

		components.clear();

		delete root;
	}

	/**
	 * @brief コンポーネントの生成
	 *
	 * 指定された新しいコンポーネントを生成し、オブジェクトに追加します。
	 *
	 * @tparam T 生成するコンポーネントの型
	 * @return T* 生成されたコンポーネントへのポインタ
	 */
	template<typename T>
	T* ConstructComponent();

	/**
	 * @brief コンポーネントの取得
	 *
	 * 指定されたコンポーネントをオブジェクトから取得する。
	 *
	 * @tparam T 取得したいコンポーネントの型
	 * @return T* 取得されたコンポーネントへのポインタ
	 */
	template<typename T>
	T* GetComponentByClass();

	/**
	 * @brief コンポーネントの登録
	 *
	 * 指定されたコンポーネントをコンテナに登録します。
	 *
	 * @param pCom 登録するコンポーネントのポインタ
	 */
	void RegisterComponent(Component* pCom);
	/**
	 * @brief コンポーネントの登録解除
	 *
	 * 指定されたコンポーネントをコンテナから解除します。
	 *
	 * @param pCom 解除するコンポーネントのポインタ
	 */
	void UnregisterComponent(Component* pCom);
	/**
	 * @brief ゲームプレイの開始時に呼び出される純粋仮想関数
	 *
	 * この関数は、ゲームプレイが開始されるときに初期化処理を行うために呼び出されます。
	 * 各派生クラスは、この関数をオーバーライドして独自の初期化処理を実装する必要があります。
	 */
	virtual void BeginPlay() = 0;
	/**
	* @brief 親オブジェクトの設定関数
	*
	* この関数は、オブジェクトの親要素を設定します。
	*
	* @param par 設定する親オブジェクトへのポインタ
	*/
	void AttachTo(Object* par);
	/**
	* @brief 親オブジェクトの設定する関数
	*
	* この関数は、オブジェクトの親要素を解除します。
	*
	* @param par 設定する親オブジェクトへのポインタ
	*/
	void DetachFrom(Object* par);


	/**
	 * @brief オブジェクトの更新処理
	 *
	 * この関数は、オブジェクトの状態を更新します。
	 *
	 * @param DeltaTime 前フレームからの経過時間
	 */
	virtual void Update(float DeltaTime) override;

	/**
	 * @brief 物理演算更新処理
	 *
	 * この関数は、オブジェクトの物理演算を更新します。
	 *
	 * @param fixedDeltaTime 固定フレーム時間
	 */
	virtual void FixedUpdate(float fixedDeltaTime) override;
public:

	/**
	 * @brief ワールドから自身を削除する
	 *
	 */
	void Destroy();

	/**
	 * @brief ローカル位置情報を取得する関数
	 *
	 * @return Vector2 ローカル位置
	 */
	Vector2 GetLocalPosition() const { return root->GetLocalPosition(); }
	/**
	 * @brief 回転情報を取得する関数
	 *
	 * @return float 回転(度数法)
	 */
	float GetLocalRotation() const { return root->GetLocalRotation(); }
	/**
	 * @brief スケール情報を取得する関数
	 *
	 * @return Vector2 スケール
	 */
	Vector2 GetLocalScale() const { return root->GetLocalScale(); }
	/**
	 * @brief ワールド位置情報を取得する関数
	 *
	 * @return Vector2 ワールド位置(絶対位置)
	 */
	Vector2 GetWorldPosition() const;
	/**
	 * @brief ワールド回転情報を取得する関数
	 *
	 * @return float ワールド回転(度数法)
	 */
	float GetWorldRotation() const;
	/**
	 * @brief ワールドスケール情報を取得する関数
	 *
	 * @return Vector2 ワールドスケール
	 */
	Vector2 GetWorldScale() const;
	/**
	 * @brief ローカル位置を設定する関数
	 * @param[in] pos 位置情報
	*/
	void SetLocalPosition(const Vector2& pos) { root->SetLocalPosition(pos); }
	/**
	 * @brief ローカル回転を設定する関数
	 * @param[in] rot 回転情報
	*/
	void SetLocalRotation(float rot) { root->SetLocalRotation(rot); }
	/**
	 * @brief ローカルスケールを設定する関数
	 * @param[in] scale スケール情報
	*/
	void SetLocalScale(const Vector2& scale) { root->SetLocalScale(scale); }
	/**
	 * @brief ローカル位置を加算する関数
	 * @param[in] pos 位置情報
	*/
	void AddPosition(const Vector2& pos) { root->AddPosition(pos); }
	/**
	 * @brief ローカル回転を加算する関数
	 * @param[in] rot 回転情報
	*/
	void AddRotation(float rot) { root->AddRotation(rot); }
};

template<typename T>
inline T* Object::ConstructComponent() {
	T* pCom = new T();
	//派生クラスを基底クラスにキャストするだけからstatic_castを使う
	if (pCom && static_cast<Component*>(pCom)) {
		pCom->SetOwner(this);
		RegisterComponent(pCom);
		return pCom;
	}
	//失敗したらnullを返す
	return nullptr;
}

template<typename T>
inline T* Object::GetComponentByClass()
{
	for (auto& com : components) {
		if (T* pCom = dynamic_cast<T*>(com)) return pCom;
	}
	return nullptr;
}

#endif // !_OBJECT_H_


