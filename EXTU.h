//---------------------------------------------------------------------------

#ifndef EXTUH
#define EXTUH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TPageControl *PlayPC;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TImage *Image1;
        TPanel *TableP;
        TToolBar *ToolBar1;
        TToolButton *StartB;
        TToolButton *ReB;
        TEdit *Password1E;
        TButton *Password1B;
        TPanel *P1;
        TButton *Password2B;
        TEdit *Password2E;
        TButton *Password3B;
        TEdit *Password3E;
        TButton *Password4B;
        TEdit *Password4E;
        TPanel *P2;
        TPanel *P3;
        TPanel *P4;
        TButton *GoB4;
        TButton *GoB1;
        TButton *GoB2;
        TButton *GoB3;
        TButton *PassB4;
        TButton *PassB3;
        TButton *PassB2;
        TButton *PassB1;
        void __fastcall StartBClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ChooseClick(TObject *Sender);
        void __fastcall GoB1Click(TObject *Sender);
        void __fastcall GoB2Click(TObject *Sender);
        void __fastcall GoB3Click(TObject *Sender);
        void __fastcall GoB4Click(TObject *Sender);
        void __fastcall Password1BClick(TObject *Sender);
        void __fastcall Password2BClick(TObject *Sender);
        void __fastcall Password3BClick(TObject *Sender);
        void __fastcall Password4BClick(TObject *Sender);
        void __fastcall PassB1Click(TObject *Sender);
        void __fastcall PassB2Click(TObject *Sender);
        void __fastcall PassB3Click(TObject *Sender);
        void __fastcall PassB4Click(TObject *Sender);
        void __fastcall ReBClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
