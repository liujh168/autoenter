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
       ShowMessage("��һ�����У����ֹ������û���������Ȳ�����");
       begin=true;
    }

    Application->Initialize();
    if(begin)Application->Tag=0;
    Application->CreateForm(__classid(TForm1), &Form1);
    Application->ShowMainForm = true ;
    Application->Title = "���������Զ���";
    Application->Run();
    Registry->WriteBool("alreadyrun",false);
    }
    catch (Exception &exception)
    {
         ShowMessage("��һ�����У����ֹ������û���������Ȳ�����");
    }
    return 0;
}
//---------------------------------------------------------------------------
