#include "Font.h"



Font::Font()
{
	fontTexture	= TextureManager::GetInstance()->GetTexture(objectType::FONT);
	fontSprite = new GameSprite(fontTexture, 0);
}


Font::~Font()
{
	SAFE_DELETE(fontSprite);
}

void Font::Draw(float x, float y, const string& s)
{
	for (UINT i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
			continue;
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			fontSprite->SelectFrame(s[i] - 'A');
		}
		else
			if (s[i] >= '0' && s[i] <= '9')
			{
				fontSprite->SelectFrame(s[i] - '0' + 26);
			}
			else
				fontSprite->SelectFrame(36);
		fontSprite->Draw(x + i * fontTexture->GetFrameWidth(), y);
	}
}
