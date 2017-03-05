//---------------------------------------------------------------------------
#include <vcl.h>
#include <vcl\Registry.hpp>
#pragma hdrstop
USEFORM("Unit1.cpp", Form1);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    TRegistry *Registry;
    bool begin=false;
    try
    {
    try
    {
        Registry = new TRegistry;
        Registry->RootKey = HKEY_LOCAL_MACHINE;
        Registry->OpenKey("SOFTWARE\\MyCompany\\Remember", TRUE);
        bool bt=Registry->ReadBool("alreadyrun");
        Application->Tag=1;
        if(bt)
        {
                ShowMessage("already run!");
                return 0;
        }

    }
    catch (Exception &exception)
    {
       ShowMessage("第一次运行，请手工输入用户名及密码等参数！");
       begin=true;
    }

    Application->Initialize();
    if(begin)Application->Tag=0;
    Application->CreateForm(__classid(TForm1), &Form1);
    Application->ShowMainForm = true ;
    Application->Title = "网络密码自动填";
    Application->Run();
    Registry->WriteBool("alreadyrun",false);
    }
    catch (Exception &exception)
    {
         ShowMessage("第一次运行，请手工输入用户名及密码等参数！");
    }
    return 0;
}
//---------------------------------------------------------------------------
