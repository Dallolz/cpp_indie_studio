#include "Bomberman.hpp"

irr::core::stringw getStringw(std::string s)
{
  size_t size = s.size();
  wchar_t *txt = new wchar_t[size+sizeof(wchar_t)];
  const char *data = &s[0];

  mbsrtowcs(txt, &data, size, NULL);

  txt[size] = L'\0';
  return (txt);
}

void mySetSkinTransparency(s32 alpha, irr::gui::IGUISkin * skin)
{
    for (s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
    {
        video::SColor col = skin->getColor((EGUI_DEFAULT_COLOR)i);
        col.setAlpha(alpha);
        skin->setColor((EGUI_DEFAULT_COLOR)i, col);
    }
}