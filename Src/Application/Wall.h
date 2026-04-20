#pragma once

class Wall {
public:
	Wall() {};
	~Wall() {};

	void Initialize(float x, float y, float width, float height);

	void Draw();

	void SetTex(KdTexture* tex) { m_tex = tex; }

	RECT GetRect() const { return m_rect; }
		
private:
	KdTexture* m_tex = nullptr;
	Math::Vector2 m_pos;
	float m_width, m_height;
	RECT m_rect;
};