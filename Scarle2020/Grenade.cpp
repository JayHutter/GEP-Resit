#include "pch.h"
#include "Grenade.h"
#include "Projectile.h"
#include "GameData.h"

Grenade::Grenade(float _radius, float _bounce, float _time, float _damage, float _knockback, int _frags, string _sprite, ID3D11Device* _GD) : Weapon (_sprite, _GD)
{
	m_bounce = _bounce;

	m_explode.scale = _radius;
	m_explode.damage = _damage;
	m_explode.knockback = _knockback;

	m_active = _time;
	m_frags = _frags;	

	//Damage if the grenade hits a worm
	m_damage = 3;
	
	m_colour = Colors::Gray;
	m_chargeable = true;
}

Grenade::Grenade(const Grenade& _orig) : Weapon(_orig)
{
	m_active = _orig.m_active;
	m_explode = _orig.m_explode;
	m_frags = _orig.m_frags;
	m_bounce = _orig.m_bounce;
}

void Grenade::Tick(GameData* _GD)
{
	m_time += _GD->m_dt;
	if (m_time > m_active && m_state == State::NEUTRAL)
	{
		m_state = State::FRAGMENT;
	}

	if (m_state == State::EXPLODE)
	{
		m_explode.pos = m_pos;
		m_explode.explode = true;
		m_delete = true;
	}
}

void Grenade::OnCollisionEnter(GameData* _GD, GameObject2D* _other)
{

}

void Grenade::OnCollision(GameData* _GD, GameObject2D* _other)
{

}

void Grenade::OnCollisionExit(GameData* _GD, GameObject2D* _other)
{

}

Grenade* Grenade::Clone(ID3D11Device* _GD)
{
	Grenade* clone = new Grenade(*this);
	clone->SetSprite(m_filename, _GD);
	return clone;
}

void Grenade::Aim(GameData* _GD)
{

}

void Grenade::Use(GameData* _GD, Worm* _owner, float _charge)
{
	if (!c_phys)
	{
		c_phys = new PhysicsComp(&m_pos, 0.3f, m_bounce, true);
	}
	if (!c_collider)
	{
		c_collider = new CollisionComp(16, 16);
	}

	Vector2 force = Vector2(_GD->m_MS.x, _GD->m_MS.y);
	force -= _owner->GetPos();
	force.Normalize();

	m_pos = _owner->GetPos();
	m_pos.x += (force.x * 15);

	force.x *= _charge * 500;
	force.y *= _charge * 700;

	c_phys->AddForce(force);

	m_owner = _owner;
}

bool Grenade::Spawn(GameData* _GD, std::vector<GameObject2D*>& _objects, ID3D11Device* _DD)
{
	if (m_state == State::FRAGMENT)
	{
		for (int i = 0; i < m_frags; i++)
		{
			//Projectile* frag = new Projectile()
		}
		m_state = State::EXPLODE;
	}

	return false;
}