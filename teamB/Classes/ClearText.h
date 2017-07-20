#ifndef __CLEAR_TEXT_H__
#define __CLEAR_TEXT_H__

#include "cocos2d.h"
USING_NS_CC;

class ClearText : public Node
{
public:
	static ClearText *create(int HScore,int score,int nowM,int nowS,bool highScoreC);

	bool init(int HScore, int score, int nowM, int nowS, bool highScoreC);

	Label* nowScore;           //現在のスコアラベル
	Label* bonusChar;          //ボーナス文字
	Label* timeBonus;          //タイム表示ラベル
	Label* highScore;          //ハイスコアラベル

	void skip();               //スコア加算スキップ

	void update(float delta);
	
private:
	int scorePoint;            //現在のスコアを取得
	int bonusPoint;            //ボーナス値を取得
	int highScorePoint;        //ハイスコア値を取得

	bool sCheck;               //ハイスコアを更新したかどうか
	bool bonusGate;            //trueにするとボーナスをスコアに流し込む

	void timeBonusDisplay();
	void highScoreDisplay(float delta);


};
#endif