//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include <shellapi.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Trayicon"
#pragma link "trayicon"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnStartClick(TObject *Sender)  // 开始刷屏
{
    if (username->Text.IsEmpty()||password->Text.IsEmpty())
    {
        ShowMessage("用户名或密码不会是空的吧？请重输！");
        username->SetFocus();
        return;
    }
    ti->Minimize();
    Timer1->Enabled = true;
    btnStart->Enabled = false;
    btnStop->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnStopClick(TObject *Sender)// 停止刷屏
{
    Timer1->Enabled = false;
    btnStart->Enabled = true;
    btnStop->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    HWND hWnd;
    char buffer[100];
    AnsiString othertitle,gettitle;
    Application->Icon=Form1->Icon;
    if(Application->Tag!=0)ti->Minimize();

    hWnd = GetForegroundWindow();       // 得到当前窗口
    GetWindowText(hWnd,buffer,50);
    othertitle=buffer;
    if (hWnd == Form1->Handle)
        {
        return; // 不需要程序本身的窗口
        }
    int i =CbWndTitle->Text.AnsiCompare(othertitle);
    if(i!=0)
    {
        GetWindowText(hWnd,buffer,50);
        gettitle=buffer;
        CbPrgTitle->Text=gettitle;
        if(hotkey)
        {
           CbWndTitle->Text=gettitle;
           hotkey=false;
        }
        return;
    }
    DWORD FormThreadID = GetCurrentThreadId();
    DWORD CWndThreadID = GetWindowThreadProcessId(hWnd, NULL);
    AttachThreadInput(CWndThreadID, FormThreadID, true);// 附加输入线程
    hWnd = GetFocus();                  // 得到当前键盘光标所在的窗口
    AttachThreadInput(CWndThreadID, FormThreadID, false);   //  取消

    if (hWnd == NULL)  return;
    if (num==0)
    {
        for(int i = 1; i <= username->Text.Length(); i++)

        { // 模拟键盘输入用户名：

        PostMessage(hWnd, WM_CHAR, (WPARAM)(username->Text[i] & 0xFF), 0);
        }
        PostMessage(hWnd, WM_KEYDOWN, VK_TAB, 0);// 自动TAB
        num++;
        return;
    }
    if (num==1)
    {

    for(int i = 1; i <= password->Text.Length(); i++)

        { // 模拟键盘输入密码：
                PostMessage(hWnd, WM_CHAR, (WPARAM)(password->Text[i] & 0xFF), 0);
        }
    //PostMessage(hWnd, WM_KEYDOWN, VK_TAB, 0);// 自动TAB
    //if(chkautoenter->Checked)
    //    {
        PostMessage(hWnd, WM_KEYDOWN, VK_RETURN, 0);// 自动回车
    //    }
    num=0;
    }
}
void __fastcall TForm1::WndProc(Messages::TMessage &Message)
{
  if (Message.Msg == WM_HOTKEY)
  {
        hotkey=true;
  }
  if (Message.Msg == WM_QUERYENDSESSION)
  {
        Registry = new TRegistry;
        Registry->RootKey = HKEY_LOCAL_MACHINE;
        Registry->OpenKey("SOFTWARE\\MyCompany\\Remember", TRUE);
        Registry->WriteBool("alreadyrun",false);
        Registry->Free();
  }
  TForm::WndProc (Message) ;
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  Registry = new TRegistry;
  Registry->RootKey = HKEY_LOCAL_MACHINE;
  Registry->OpenKey("SOFTWARE\\MyCompany\\Remember", TRUE);
  try
  {
    CbWndTitle->Text=Registry->ReadString("CbWndTitle");
    username->Text= Registry->ReadString("username");
    password->Text= Registry->ReadString("password");
    char mych1[50];
    char mych2[50];
    strcpy(mych1,password->Text.c_str());
    int i ;
    for(i=0;i<password->Text.Length();i++)
    {
    mych2[i]=mych1[i]+0x3;
    }
    mych2[i+1]=0;
    //password->Text=mych2;
    Registry->WriteBool("alreadyrun",true);
  }
  catch (...)
  {
        ShowMessage("第一次运行!请在自动填之前先修改用户名及密码");
  }
  RegisterHotKey(Form1->Handle,0x065,MOD_CONTROL|MOD_ALT,0x041);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{

  Registry->WriteString("CbWndTitle", CbWndTitle->Text);
  Registry->WriteString("username", username->Text);
  char mych1[50];
  char mych2[50];
  strcpy(mych1,password->Text.c_str());
  int i ;
  for(i=0;i<password->Text.Length();i++)
  {
  mych2[i]=mych1[i]-0x3;
  }
  mych2[i+1]=0;
  //password->Text=mych2;
  Registry->WriteString("password", password->Text);
  Registry->WriteBool("alreadyrun",false);
  Registry->CloseKey();
  if(Registry->OpenKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",false))
 {
        if(chkautorun->Checked)
          {

                Registry->WriteString("liujhua",Application->ExeName);
          }
        else
          {
                password->Text="liujhua";
                //Registry->CloseKey();
                if(Registry->DeleteKey(password->Text))
                {
                 ShowMessage("delete key ok!");
                }

          }
 }
  Registry->Free();
  UnregisterHotKey(Form1->Handle,0x065);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnCopyTitleClick(TObject *Sender)
{
        CbWndTitle->Text=CbPrgTitle->Text;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnExitClick(TObject *Sender)
{
        Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnhelpClick(TObject *Sender)
{
        ShellExecute(Form1->Handle,NULL,"http://10.208.22.61/download/list.Asp?id=87",NULL,NULL,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::restore1Click(TObject *Sender)
{
        ti->Restore();
}
//---------------------------------------------------------------------------





void __fastcall TForm1::tiRestore(TObject *Sender)
{
        Application->Tag=0;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::exit1Click(TObject *Sender)
{
        Application->Terminate();
}
//---------------------------------------------------------------------------


