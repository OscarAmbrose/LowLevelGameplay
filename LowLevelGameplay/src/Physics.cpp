#include <Physics.h>
#include <Collider.h>
#include <RigidBody.h>
#include <GameObject.h>
#include <BoxCollider.h>
#include "Collider.h"

std::vector<CollisionInfo*> Physics::_collisions;
std::vector<CollisionInfo*> Physics::_oldCollisions;

std::vector<Collider*> Physics::_colliders;
std::vector<RigidBody*> Physics::_rigidBodies;

bool CollisionInfo::operator==(const CollisionInfo& other)
{
	return (*collider == *other.collider && *otherCollider == *other.otherCollider) || ((Collider)*collider == *other.otherCollider && *otherCollider == *other.collider);
}

CollisionInfo CollisionInfo::Reverse()
{
	CollisionInfo temp;
	temp.collider = otherCollider;
	temp.otherCollider = collider;

	temp.Normal = -Normal;
	temp.Impulse = -Impulse;

	return temp;
}

void Physics::ReigsterColldier(Collider* col)
{
	if (std::find_if(_colliders.begin(), _colliders.end(), [col](Collider* check) { return *col == *check; }) == _colliders.end())
	{
		_colliders.push_back(col);
	}
}

void Physics::DereigsterColldier(Collider* col)
{
	std::erase_if(_colliders, [col](Collider* check) { return *col == *check; });
}

void Physics::ReigsterRigidBody(RigidBody* rb)
{
	if (std::find_if(_rigidBodies.begin(), _rigidBodies.end(), [rb](RigidBody* check) { return *rb == *check; }) == _rigidBodies.end())
	{
		_rigidBodies.push_back(rb);
	}
}

void Physics::DereigsterRigidBody(RigidBody* rb)
{
	std::erase_if(_rigidBodies, [rb](RigidBody* check) { return *rb == *check; });
}

void Physics::CollectCollisions()
{
	for (RigidBody* rb : _rigidBodies)
	{
		std::vector<Collider*> rbCols = rb->GetGameObject()->GetComponents<Collider>();
		for (Collider* rbCol : rbCols)
		{
			for (Collider* worldCol : _colliders)
			{
				if (*rbCol == *worldCol || *rbCol->GetGameObject() == *worldCol->GetGameObject()) { continue; }

				{
					CollisionInfo* test; test->collider = rbCol; test->otherCollider = worldCol;
					if (std::find_if(_collisions.begin(), _collisions.end(), [test](CollisionInfo* check) {return *test == *check; }) == _collisions.end()) { continue; }
				}

				if (CollisionInfo* collision = rbCol->IsCollidingWith(worldCol))
				{
					_collisions.push_back(collision);
				}
			}
		}
	}
}

void Physics::DispatchCollisions()
{
	for (int newIndex = _collisions.size() - 1; newIndex >= 0; newIndex--)
	{
		bool newCollision = true;
		for (int oldIndex = (_oldCollisions.size() - 1); oldIndex >= 0; oldIndex--)
		{
			if (_collisions[newIndex] != _oldCollisions[oldIndex]) { continue; }
			//Collision Stay
			_collisions[newIndex]->collider->GetGameObject()->onCollisionStay(_collisions[newIndex]);
			if (_collisions[newIndex]->otherIsRB) { _collisions[newIndex]->otherCollider->GetGameObject()->onCollisionStay(&_collisions[newIndex]->Reverse()); }
			delete _oldCollisions[oldIndex];
			_oldCollisions.erase(std::next(_oldCollisions.begin(), oldIndex));
			newCollision = false;
			break;
		}
		if (newCollision)
		{
			//Collision Enter
			_collisions[newIndex]->collider->GetGameObject()->onCollisionEnter(_collisions[newIndex]);
			if (_collisions[newIndex]->otherIsRB) { _collisions[newIndex]->otherCollider->GetGameObject()->onCollisionEnter(&_collisions[newIndex]->Reverse()); }
		}
	}


	for (int i = _oldCollisions.size()-1; i >= 0 ; i--)
	{
		//Collision Exit
		_oldCollisions[i]->collider->GetGameObject()->onCollisionExit(_collisions[i]);
		if (_oldCollisions[i]->otherIsRB) 
		{ 
			_oldCollisions[i]->otherCollider->GetGameObject()->onCollisionExit(&_oldCollisions[i]->Reverse()); 
		}
		delete _oldCollisions[i];
	}
	_oldCollisions.clear();
	_oldCollisions = _collisions;
	_collisions.clear();
}

CollisionInfo* Physics::Collision_AABBAABB(BoxCollider* lhs, BoxCollider* rhs)
{
	return nullptr;
}
