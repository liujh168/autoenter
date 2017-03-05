//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BmpToWindow.h"

//---------------------------------------------------------------------------
HRGN BmpToRgn(TImage* Image,COLORREF ClearLowColor,COLORREF ClearHighColor,int LinesPerRect)
{
    try
    {
        HRGN hRgnMain=CreateRectRgn(0,0,Image->Width,Image->Height);
        CombineRgn(hRgnMain,hRgnMain,hRgnMain,RGN_XOR);
        HRGN hRgnTemp;
        TPoint Left_Top,Right_Bottom;
        int Row=0,Array=0;
        int WhichPoint =TOP_LEFT_POINT;
        while(Row<Image->Picture->Bitmap->Height)
        {
                Left_Top.x=Image->Left+1;
                Left_Top.y=Row+Image->Top;
                Right_Bottom.x=Image->Left+Image->Width-1;
                Right_Bottom.y=Row+Image->Top;
                while(Array<Image->Picture->Bitmap->Width-1)
                {
                        switch(WhichPoint)
                        {
                                case TOP_LEFT_POINT:
                                if(!IfInTheColorScope(ClearLowColor,ClearHighColor,Image->Picture->Bitmap->Canvas->Pixels[Array][Row]))
                                {
                                        Left_Top.x=Array+Image->Left+1;
                                        Left_Top.y=Row+Image->Top;
                                        WhichPoint=BOTTOM_RIGHT_POINT;
                                }
                                break;
                                case BOTTOM_RIGHT_POINT:
                                if(IfInTheColorScope(ClearLowColor,ClearHighColor,Image->Picture->Bitmap->Canvas->Pixels[Array][Row]))
                                {
                                        Right_Bottom.x=Array+Image->Left-1;
                                        Right_Bottom.y=Row+Image->Top;
                                        WhichPoint=TOP_LEFT_POINT;
                                        hRgnTemp=CreateRectRgn(Left_Top.x,Left_Top.y,Right_Bottom.x,Right_Bottom.y+LinesPerRect);
                                        if(hRgnTemp!=NULL)
                                        {
                                                if(CombineRgn(hRgnMain,hRgnMain,hRgnTemp,RGN_OR)==ERROR)
                                                {
                                                ShowMessage("Combine region fail~");
                                                return hRgnMain;
                                                }
                                                if(DeleteObject(hRgnTemp)==0)ShowMessage("DeleteObject error!");
                                        }
                                        else
                                        {
                                                ShowMessage("Create rgion fail!");
                                                return hRgnMain;
                                        }
                                }
                                break;
                        }
              Array++;
        }
        if(WhichPoint==BOTTOM_RIGHT_POINT)
        {
                Right_Bottom.x=Image->Left+Image->Width-1;
                Right_Bottom.y=Row+Image->Top;
                hRgnTemp=CreateRectRgn(Left_Top.x,Left_Top.y,Right_Bottom.x,Right_Bottom.y+LinesPerRect);
                if(hRgnTemp!=NULL)
                {
                        CombineRgn(hRgnMain,hRgnMain,hRgnTemp,RGN_OR);
                        if(DeleteObject(hRgnTemp)==0)ShowMessage("DeleteObject error!");
                }
                else
                {
                        ShowMessage("Create rgion fail!");
                        return hRgnMain;
                }
                WhichPoint=TOP_LEFT_POINT;
        }
        Row=Row+LinesPerRect;
        Array=0;
        }
        return hRgnMain;
    }
    catch(Exception &exception)
    {
        ShowMessage("Create rgion fail!");
        return 0;
    }
}

#pragma package(smart_init)
