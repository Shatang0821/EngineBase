#include "stdafx.h"
#include "Debug.h"
#include "MyApp.h"

void Debug::DrawLine(Vector2 start, Vector2 end, D3DCOLOR color)
{
    auto pDevice = MyApp::Instance()->GetDevice();
	Vertex vertices[] =
	{
		{start.x, start.y, 0.0f, 1.0f, color},
		{end.x, end.y, 0.0f, 1.0f, color},
	};

	pDevice->SetFVF(Vertex::FVF);
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, vertices, sizeof(Vertex));

}

void Debug::DrawBox(Vector2 pos, Vector2 size, D3DCOLOR color)
{
	auto pDevice = MyApp::Instance()->GetDevice();
    Vertex vertices[] =
    {
        //���
        {pos.x - size.x / 2, pos.y - size.y / 2, 0.0f, 1.0f, color},
        {pos.x + size.x / 2, pos.y - size.y / 2, 0.0f, 1.0f, color},
        //�E��
        {pos.x + size.x / 2, pos.y - size.y / 2, 0.0f, 1.0f, color},
        {pos.x + size.x / 2, pos.y + size.y / 2, 0.0f, 1.0f, color},
        //����
        {pos.x - size.x / 2, pos.y - size.y / 2, 0.0f, 1.0f, color},
        {pos.x - size.x / 2, pos.y + size.y / 2, 0.0f, 1.0f, color},
        //����
        {pos.x - size.x / 2, pos.y + size.y / 2, 0.0f, 1.0f, color},
        {pos.x + size.x / 2, pos.y + size.y / 2, 0.0f, 1.0f, color},
    };

    pDevice->SetFVF(Vertex::FVF);
    pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 4, vertices, sizeof(Vertex));
}

void Debug::DrawCircle(Vector2 pos, float radius,int segments, D3DCOLOR color)
{
    auto pDevice = MyApp::Instance()->GetDevice();
    std::vector<Vertex> vertices;
    float angleStep = 2 * D3DX_PI / segments;

    for (int i = 0; i <= segments; ++i)
    {
        float angle = i * angleStep;
        float x = pos.x + cos(angle) * radius;
        float y = pos.y + sin(angle) * radius;
        vertices.push_back({ x, y, 0.0f, 1.0f, color });
    }

    pDevice->SetFVF(Vertex::FVF);
    pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, segments, vertices.data(), sizeof(Vertex));

}

void Debug::RenderText(IDirect3DDevice9* pDevice, int x, int y, const wchar_t* text)
{
    RECT rect;
    SetRect(&rect, x, y, x + 300, y + 50); // �e�L�X�g��`�悷���`�͈�

    // �e�L�X�g�̕`��
    MyApp::Instance()->GetFont()->DrawTextW(
        NULL,            // �X�v���C�g�I�u�W�F�N�g�ւ̃|�C���^�i�g�p���Ȃ��̂�NULL�j
        text,            // �`�悷��e�L�X�g
        -1,              // �e�L�X�g�̒����i-1��NULL�I�[�܂Łj
        &rect,           // �`�悷���`�͈�
        DT_LEFT | DT_TOP,// �e�L�X�g�̔z�u
        D3DCOLOR_XRGB(255, 255, 255) // �e�L�X�g�̃J���[
    );
}
