#include "WatchLayer.h"
#include "MultiResolution.h"

bool WatchLayer::init()
{
	if (!Layer::init()) return false;

	circleNum = WATCH_NUMBER;
	breakNumCheck = 0;
	breakNum = 3;           //�󂷐����̐�  11�ȏ�ɂ��Ȃ��悤��

	for (int t = 0; t < circleNum; t++)
	{
		breakCheck[t] = true;        //���������Ă邩�ǂ����̏�����
	}
	//���v�̈ʒu
	Vec2 watchPos = designResolutionSize * 0.5f;

	//���v
	_watchSprite = Sprite::create("GameScene/clockOne.png");
	_watchSprite->setPosition(watchPos);
	_watchSprite->setScale(0.6f);
	this->addChild(_watchSprite,1);

	radius = (_watchSprite->getContentSize().width*0.5f)*0.6f;

	//�d�������n�_�ݒ�&�Q�[�g�摜�z�u
	for (int i = 0; i < circleNum; i++)
	{
		fairyGate.push_back(Sprite::create("GameScene/EnemySprite.png"));
		fairyGate.at(i)->setPosition(Vec2(designResolutionSize.width*0.5f + radius*cos(M_PI / 180 * (90 - 360 * i / circleNum)),
			                              designResolutionSize.height*0.5f + radius*sin(M_PI / 180 * (90 - 360 * i / circleNum))));
		fairyGate.at(i)->setScale(0.3f);
		this->addChild(fairyGate.at(i),5);
	}
	//������\��
	for (int j = 0; j < circleNum; j++)
	{
		String* noNum = String::createWithFormat("GameScene/clockTwo-%d.png", j + 1);
		numSpr.push_back(Sprite::create(noNum->getCString()));
		numSpr.at(j)->setPosition(watchPos);
		numSpr.at(j)->setScale(0.6f);
		this->addChild(numSpr.at(j), 2);
	}
	
	ramdomBreak();            //breakNum�̐����������_���Ő�������

	//����
	dirtWatch = Sprite::create("GameScene/clockThree.png");
	dirtWatch->setPosition(watchPos);
	dirtWatch->setScale(0.6f);
	this->addChild(dirtWatch, 3);


	//�܂�
	_knob = Knob::create();
	_knob->setPosition(Vec2(designResolutionSize.width * 0.96f, watchPos.y));
	_knob->setScale(0.5f);
	this->addChild(_knob,0);

	//�Z�j
	_shortHand = ShortHand::create();
	_shortHand->setPosition(watchPos);
	this->addChild(_shortHand,4);

	//���j
	_longHand = LongHand::create();
	_longHand->setPosition(watchPos);
	this->addChild(_longHand,5);

	//�b�j
	_secondHand = SecondHand::create();
	_secondHand->setPosition(watchPos);
	this->addChild(_secondHand, 8);

	//���̔���
	glassShine = Sprite::create("GameScene/clockFour.png");
	glassShine->setPosition(watchPos);
	glassShine->setScale(0.6f);
	this->addChild(glassShine,9);

	//Player�N���X
	_player = Player::create();
	this->addChild(_player);

	//EnemyManager�N���X
	_enemyManager = EnemyManager::create(circleNum - 1);
	this->addChild(_enemyManager,9);

	this->scheduleUpdate();

	return true;
}

void WatchLayer::update(float delta)
{
	_secondHand->setRotation(_secondHand->getRotation() + 0.1f);
	if (_secondHand->getRotation() >= 360.0f)
	{
		_secondHand->setRotation(_secondHand->getRotation() - 360.0f);
	}
}

//������breakNum�̐�����
void WatchLayer::ramdomBreak()
{
	//Ramdom
	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<int> breakPosNum(0, 11);

	for (int t = 0; t < 12; t++)
	{
		numberHP[t] = 10;        //������HP������
	}

	while (true)
	{
		actingBreak = breakPosNum(mt);
		if (breakCheck[actingBreak] == true)
		{
			breakCheck[actingBreak] = false;
			numberHP[actingBreak] = 0;
			String* breakNoNum = String::createWithFormat("GameScene/clockTwo-%dbreak.png", actingBreak + 1);
			numSpr.at(actingBreak)->setTexture(breakNoNum->getCString());
			breakNumCheck++;
		}
		if (breakNum == breakNumCheck) break;
	}
}

//�����C��
void WatchLayer::repairNumber(int num)
{
	numberHP[num] += 1;
	if (numberHP[num] >= 10)
	{
		breakCheck[num] = true;
		String* repairNum = String::createWithFormat("GameScene/clockTwo-%d.png", num + 1);
		numSpr.at(num)->setTexture(repairNum->getCString());
	}

}