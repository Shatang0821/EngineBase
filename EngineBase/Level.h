/**
 * @file Level.h
 * @brief オブジェクトを保持するクラス
 *
 * @author サトウ
 * @date 2024/06/21
 */

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Base.h"

 /**
  * @class Level
  * @brief シーン内のオブジェクトを管理するクラス
  *
  * このクラスは、シーン内のオブジェクトを管理する
  */
class Level : public Base
{
public:
	virtual void Update(float DeltaTime) override;
};

#endif // !_LEVEL_H_



