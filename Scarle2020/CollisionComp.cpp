#include "pch.h"
#include "CollisionComp.h"

CollisionComp::CollisionComp(float _width, float _height)
{
	hitbox.top = -(_height / 2);
	hitbox.bottom = _height / 2;
	hitbox.left = -(_width / 2);
	hitbox.right = _width / 2;
}

//Test if pixel has collided with visible stage
bool CollisionComp::TerrainCollision(RenderTarget* _render_target, ID3D11DeviceContext* _context, GameData* _GD, Vector2 _pixel)
{
	//_render_target->Map(_context);
	auto alpha = _render_target->GetPixel(_pixel.x, (-_pixel.y) + collision_offset, _GD)->A();
	
	if (alpha > 0.0f)
	{
		//_render_target->Unmap(_context);
		return true;
	}
	//_render_target->Unmap(_context);
	return false;
}

/*
//Test is side of object has collided with the stage
bool CollisionComp::TerrainCollision(RenderTarget* _render_target, ID3D11DeviceContext* _context, GameData* _GD, Vector2 _pos, Side _side)
{
	Vector2 pixel = _pos;

	switch (_side)
	{
	case Side::Top:
		pixel.y += hitbox.top;
		break;
	case Side::Bottom:
		pixel.y += hitbox.bottom;
		break;
	case Side::Right:
		pixel.x += hitbox.right;
		break;
	case Side::Left:
		pixel.x += hitbox.left;
		break;
	}

	return TerrainCollision(_render_target, _context, _GD, pixel);
}
*/

bool CollisionComp::TerrainCollision(RenderTarget* _render_target, ID3D11DeviceContext* _context, GameData* _GD, Vector2 _pos, Side _vert, Side _hori)
{
	switch (_vert)
	{
	case Side::Positive:
		_pos.y += hitbox.bottom;
		break;
	case Side::Negative:
		_pos.y += hitbox.top;
		break;
	}

	switch (_hori)
	{
	case Side::Positive:
		_pos.x += hitbox.right;
		break;
	case Side::Negative:
		_pos.x += hitbox.left;
	}

	return TerrainCollision(_render_target, _context, _GD, _pos);
}

/*
Count the amount of pixels collided with on each side of the hitbox
{ TOP, BOTTOM, LEFT, RIGHT }
*/
std::array<int, 4> CollisionComp::TerrainCollsionV(RenderTarget* _render_target, ID3D11DeviceContext* _context, GameData* _GD, Vector2 _pos)
{
	//Amount pixels collided with on each side
	std::array<int, 4> pixels = { 0,0,0,0 };
	
	//Flip y coord as y=0 is bottom instead of top
	_pos.y *= -1;

	//for (int x = _pos.x + hitbox.left; x++; x < )
	for (int x = _pos.x + hitbox.left; x < _pos.x + hitbox.right; x++)
	{
		auto alpha = _render_target->GetPixel(x, _pos.y + hitbox.top + collision_offset, _GD)->A();
		if (alpha > 0.0f)
		{
			pixels[0] ++;
		}
	
		alpha = _render_target->GetPixel(x, _pos.y + hitbox.bottom + collision_offset, _GD)->A();
		if (alpha > 0.0f)
		{
			pixels[1] ++;
		}
	}

	for (int y = _pos.y + hitbox.top; y < _pos.y + hitbox.bottom; y++)
	{
		auto alpha = _render_target->GetPixel(_pos.x + hitbox.left, y + collision_offset, _GD)->A();
		if (alpha > 0.0f)
		{
			pixels[2] ++;
		}
	
		alpha = _render_target->GetPixel(_pos.x + hitbox.right, y + collision_offset, _GD)->A();
		if (alpha > 0.0f)
		{
			pixels[3] ++;
		}
	}

	return pixels;
	
}

//void CollisionComp::UpdateHitbox(Vector2 _pos)
//{
//	float half_width = (hitbox.right - hitbox.left) / 2;
//	float half_height = (hitbox.bottom - hitbox.top) / 2;
//
//	hitbox.left = _pos.x - half_width;
//	hitbox.right = _pos.x + half_width;
//	hitbox.top = _pos.y + half_height;
//	hitbox.bottom = _pos.y - half_height;
//}