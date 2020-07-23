#ifndef _GAME_OBJECT_2D_H_
#define _GAME_OBJECT_2D_H_

//=================================================================
//the base Game Object 2D
//=================================================================

#include <d3d11_1.h>
#include "SimpleMath.h"
#include <string>
#include "PhysicsComp.h"
#include "CollisionComp.h"

using namespace DirectX;
using namespace SimpleMath;
using namespace std;

struct GameData;
struct DrawData2D;

class GameObject2D
{
public:
	GameObject2D();
	virtual ~GameObject2D() {};

	virtual void Tick(GameData* _GD) = 0;
	virtual void Draw(DrawData2D* _DD) = 0;

	//setters

	void SetPos(Vector2 _pos) { m_pos = _pos; }
	void SetRot(float _rot) { m_rotation = _rot; }
	void SetColour(Color _colour) { m_colour = _colour; }
	void SetScale(Vector2 _scale) { m_scale = _scale; }
	void SetScale(float _scale) { m_scale = _scale * Vector2::One; }
	void SetOrigin(Vector2 _origin) { m_origin = _origin; }
	
	bool Delete() { return m_delete; }
	PhysicsComp* GetPhysComp();
	Vector2 GetPos() { return m_pos; }
	CollisionComp* GetCollider() { return c_collider; }
	int Direction() { return m_dir; }

	virtual void OnCollision(GameData* _GD, GameObject2D* _other) = 0;
	
protected:
	Vector2 m_pos;
	float m_rotation;
	Vector2 m_scale;
	Color m_colour;
	Vector2 m_origin;

	int m_dir = 1;

	PhysicsComp *c_phys = nullptr;
	CollisionComp* c_collider = nullptr;
	bool m_delete = false;
};


#endif