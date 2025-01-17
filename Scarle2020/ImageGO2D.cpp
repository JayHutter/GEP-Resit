#include "pch.h"
#include "ImageGO2D.h"
#include "DDSTextureLoader.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "helper.h"

ImageGO2D::ImageGO2D(string _fileName, ID3D11Device* _GD) :m_pTextureRV(nullptr)
{
	SetSprite(_fileName, _GD);
}

ImageGO2D::ImageGO2D(const ImageGO2D& orig)
{
	m_pos = orig.m_pos;
	m_colour = orig.m_colour;
	m_dir = orig.m_dir;
	m_health = orig.m_health;
	m_rotation = orig.m_rotation;
	m_scale = orig.m_scale;
	m_filename = orig.m_filename;
	m_explode = orig.m_explode;
	m_prevent_swap = orig.m_prevent_swap;
}

ImageGO2D::~ImageGO2D()
{
	if (m_pTextureRV)
	{
		m_pTextureRV->Release();
		m_pTextureRV = nullptr;
	}
}

void ImageGO2D::SetSprite(string _fileName, ID3D11Device* _GD)
{
	m_filename = _fileName;

	string fullfilename = "../Images/" + _fileName + ".dds";
	HRESULT hr = CreateDDSTextureFromFile(_GD, Helper::charToWChar(fullfilename.c_str()), nullptr, &m_pTextureRV);

	//Load default texture if texture fails to load
	if (!m_pTextureRV)
	{
		fullfilename = "../Images/default.dds";
		HRESULT hr = CreateDDSTextureFromFile(_GD, Helper::charToWChar(fullfilename.c_str()), nullptr, &m_pTextureRV);
	}

	//this nasty thing is required to find out the size of this image!
	ID3D11Resource* pResource;
	D3D11_TEXTURE2D_DESC Desc;
	m_pTextureRV->GetResource(&pResource);
	((ID3D11Texture2D*)pResource)->GetDesc(&Desc);

	m_origin = 0.5f * Vector2((float)Desc.Width, (float)Desc.Height);//around which rotation and scaing is done
}

void ImageGO2D::Tick(GameData* _GD)
{
}



void ImageGO2D::Draw(DrawData2D* _DD)
{
	//nullptr can be changed to a RECT* to define what area of this image to grab
	//you can also add an extra value at the end to define layer depth
	//right click and "Go to Defintion/Declaration" to see other version of this in DXTK
	_DD->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);
}