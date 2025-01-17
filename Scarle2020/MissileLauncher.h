#pragma once
#include "Weapon.h"
class MissileLauncher : public Weapon
{
public:
	MissileLauncher(ID3D11Device* _GD);
	~MissileLauncher() = default;
	MissileLauncher(const MissileLauncher& _orig);

	virtual void Tick(GameData* _GD);

	virtual void OnCollisionEnter(GameData* _GD, GameObject2D* _other) {}
	virtual void OnCollision(GameData* _GD, GameObject2D* _other) {}
	virtual void OnCollisionExit(GameData* _GD, GameObject2D* _other) {}

	virtual MissileLauncher* Clone(ID3D11Device* _GD) override;

	virtual void Aim(GameData* _GD);
	virtual void Use(GameData* _GD, Worm* _owner, float _charge);
	virtual bool Spawn(GameData* _GD, std::vector<GameObject2D*>& _objects, ID3D11Device* _DD);

	virtual void Draw(DrawData2D* _DD) {}
private:
	bool m_fired = false;
};

