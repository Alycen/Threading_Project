//#include "FollowEnemy.h"
//
//static const float SCALE = 30.f;
//
//FollowEnemy::FollowEnemy(b2World &world, b2Vec2 const &position, int width, int height) : Enemy(world, position, width, height) {
//	speed = 1;
//}
//
//FollowEnemy::~FollowEnemy() {
//
//}
//
//void FollowEnemy::Update(b2Vec2 target) {
//	geometry.x = boxBody->GetPosition().x * SCALE;
//	geometry.y = boxBody->GetPosition().y * SCALE;
//
//	if (target.x * SCALE > geometry.x)
//	{
//		Move(Right);
//	}
//	else if (target.x * SCALE < geometry.x)
//	{
//		Move(Left);
//	}
//	if (target.y * SCALE > geometry.y)
//	{
//		Move(Down);
//	}
//	else if (target.y * SCALE < geometry.y)
//	{
//		Move(Up);
//	}
//
//	m_sprite->SetPosition(boxBody->GetPosition().x * SCALE, boxBody->GetPosition().y * SCALE);
//}