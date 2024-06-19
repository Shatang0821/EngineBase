#ifndef _BASE_H_
#define _BASE_H_

//ベースクラス
class Base
{
public:
    virtual void Update(float DeltaTime) = 0;   //純粋仮想更新関数
};

#endif // !_BASE_H_

