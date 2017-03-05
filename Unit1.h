#include <vcl\Registry.hpp>
#include <AppEvnts.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include "Trayicon.h"
#include <Menus.hpp>
#include <ImgList.hpp>
#include "trayicon.h"
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
static int num=0;
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TLabel *LblAuthor;
        TLabel *LblOicq;
        TLabel *LblEmail;
        TLabel *LblHomepage;
        TEdit *password;
        TButton *BtnCopyTitle;
        TLabel *LblHelp;
        TCheckBox *chkautorun;
        TApplicationEvents *ApplEvents;
        TButton *btnStart;
        TButton *btnStop;
        TButton *btnhelp;
        TButton *BtnExit;
        TPanel *Panel1;
        TLabel *LblUsername;
        TLabel *LblPassword;
        TLabel *LblWndtitle;
        TComboBox *username;
        TComboBox *CbPrgTitle;
        TComboBox *CbWndTitle;
        TTrayIcon *ti;
        TPopupMenu *pmenu;
        TMenuItem *restore1;
        TImageList *ImageList1;
        TMenuItem *exit1;
        TCheckBox *chkautoenter;
        void __fastcall btnStartClick(TObject *Sender);
        void __fastcall btnStopClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall BtnCopyTitleClick(TObject *Sender);
        void __fastcall BtnExitClick(TObject *Sender);
        void __fastcall btnhelpClick(TObject *Sender);
        void __fastcall restore1Click(TObject *Sender);
        void __fastcall tiRestore(TObject *Sender);
        void __fastcall exit1Click(TObject *Sender);
   private:
        TRegistry *Registry;
        bool hotkey;
        virtual void __fastcall WndProc(Messages::TMessage &Message) ;
    public:
    __fastcall TForm1(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
