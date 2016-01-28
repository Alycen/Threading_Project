#include "Enemy.h"

using namespace std;
const int RIGHT = 1, LEFT = 2, DOWN = 3;
static const float SCALE = 30.f;

Enemy::Enemy() { }

Enemy::Enemy(SDL_Rect rect, bool flying, b2World* world, void * name) {
	mRect = rect;

	mBodyDef.position.Set((rect.x + rect.w / 2 - 17) / SCALE, (rect.y + rect.h / 2 - 15) / SCALE);
	mBodyDef.type = b2_dynamicBody;
	mBodyDef.position.Set((mRect.x + mRect.w / 2 - 17) / SCALE, (mRect.y + mRect.h / 2 - 15) / SCALE);
	
	mShape.SetAsBox((mRect.w / 2) / SCALE, (mRect.h / 2) / SCALE);
	mBodyFixtureDef.shape = &mShape;
	mBodyFixtureDef.userData = name;
	
	m_Body = world->CreateBody(&mBodyDef);
	source = { 0,0,54,40 };

	m_Body->CreateFixture(&mBodyFixtureDef);
	m_Body->SetFixedRotation(true);
	m_Body->SetUserData(this);

	if (!flying)
		m_Body->SetGravityScale(1.0f);
	else if (flying)
		m_Body->SetGravityScale(0.0f);

	m_Body->SetSleepingAllowed(false);
	direction = RIGHT;
	gright.Init("Assets/enemy_right.png", mRect, source);
	gleft.Init("Assets/enemy_left.png", mRect, source);
	sprite = gright;
	gleft.SetOffset(27, 20);
	gright.SetOffset(27, 20);
	//sprite.SetOffset(27, 20);
}

void Enemy::Update() {
	mRect.x = m_Body->GetPosition().x * SCALE;
	mRect.y = m_Body->GetPosition().y * SCALE;

	Move();
	sprite.SetPosition(m_Body->GetPosition().x * SCALE, m_Body->GetPosition().y * SCALE);


	if(!alive) {
		direction = DOWN;
		//mBodyFixtureDef.isSensor = true;
		//m_Body->SetLinearVelocity(b2Vec2(0, 20));
		//m_Body->SetGravityScale(0.0f);
	}
}

void Enemy::Move() {
	if (flying) {
		if (direction == RIGHT) {
			m_Body->SetTransform(b2Vec2(m_Body->GetPosition().x + (speed / SCALE), m_Body->GetPosition().y), 0);
			//sprite = fright;
		}
		else if (direction == LEFT) {
			m_Body->SetTransform(b2Vec2(m_Body->GetPosition().x - (speed / SCALE), m_Body->GetPosition().y), 0);
			//sprite = fleft;
		}
	}
	else {
		if (direction == RIGHT) {
			//m_Body->SetTransform(b2Vec2(0, -5),0);
			m_Body->SetTransform(b2Vec2(m_Body->GetPosition().x + speed, m_Body->GetPosition().y), 0);
			sprite = gright;
		}
		else if (direction == LEFT) {
			m_Body->SetTransform(b2Vec2(m_Body->GetPosition().x - speed, m_Body->GetPosition().y), 0);
			sprite = gleft;
		}
		else if (direction == DOWN) {
			m_Body->SetTransform(b2Vec2(m_Body->GetPosition().x , m_Body->GetPosition().y + 0.5), 0);
		}
	}
}

void Enemy::Swap() {
	if (direction == RIGHT) {
		direction = LEFT;
	}
	else if (direction == LEFT) {
		direction = RIGHT;
	}
}

void Enemy::Die() {
	alive = false;
}

void Enemy::Draw() {
	sprite.Draw();
}

Enemy::~Enemy() {

}