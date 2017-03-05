//---------------------------------------------------------------------------

#ifndef BmpToWindowH
#define BmpToWindowH
#define TOP_LEFT_POINT 0
#define BOTTOM_RIGHT_POINT 1
#include "extctrls.hpp"
//---------------------------------------------------------------------------
HRGN BmpToRgn(TImage* Image,COLORREF ClearLowColor,COLORREF ClearHighColor,int LinesPerRect);
//---------------------------------------------------------------------------
bool inline IfInTheColorScope(COLORREF LowColor,COLORREF HighColor,COLORREF SourceColor)
{
        if(SourceColor>=LowColor&&SourceColor<=HighColor)return true;
        else return false;
}
//---------------------------------------------------------------------------
#endif
