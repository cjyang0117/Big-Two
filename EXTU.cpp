//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EXTU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TImage *AllCard[52];
TImage *ChooseCard[5];
TImage *TableCard[5];
TImage *TableCard1[5];
int Password[4],
    CardName[52],
    Card=0,
    thisnum,
    thiscolor,
    lastnum,
    lastcolor,
    lastcard,
    w,h,
    win,win1=0,win2=0,win3=0,win4=0,
    circle=0;
bool firstround=true,player1,player2,player3,player4,Anser;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StartBClick(TObject *Sender)
{
  if(firstround==true){
    StartB->Enabled=false;
    ReB->Enabled=true;
  }  

  for(int i=0;i<4;i++){
    Password[i]=StrToInt(InputBox("設定密碼",IntToStr(i+1)+"號玩家請設定密碼~~~~~~~~","123"));
  }

  TImage *temp;
  int x=0;
  w=(P1->Width/13)-6;
  h=P1->Height-15;
  for(int i=0;i<52;i++){
    temp=new TImage(Form1);
    if(i<13)temp->Parent=P1; if(i>=13&&i<26) temp->Parent=P2; if(i>=26&&i<39) temp->Parent=P3; if(i>=39) temp->Parent=P4;
    temp->Picture->LoadFromFile("pic\\"+IntToStr(CardName[i])+".jpg");
    temp->Tag=CardName[i]/10;               //數字
    temp->Hint=IntToStr(CardName[i]%10);    //花色
    temp->Stretch=true;
    temp->Width=w;
    temp->Height=h;
    temp->Left=w*(x++); if(x==13) x=0;
    temp->Top=15;
    temp->OnClick=ChooseClick;
    AllCard[i]=temp;

    if(temp->Tag==3&&temp->Hint==1){
      if(i<13){
        Password1B->Enabled=true;
        PassB1->Enabled=false;
        ShowMessage("由一號玩家開始遊戲~");
      }
      if(i>=13&&i<26){
        Password2B->Enabled=true;
        PassB2->Enabled=false;
        ShowMessage("由二號玩家開始遊戲~");
      }
      if(i>=26&&i<39){                                     
        Password3B->Enabled=true;
        PassB3->Enabled=false;
        ShowMessage("由三號玩家開始遊戲~");
      }
      if(i>=39){
        Password4B->Enabled=true;
        PassB4->Enabled=false;
        ShowMessage("由四號玩家開始遊戲~");
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  for(int i=0;i<5;i++){
    delete TableCard1[i];
    TableCard1[i]=NULL;
  }
  for(int i=0;i<52;i++){
    delete AllCard[i];
    AllCard[i]=NULL;
  }

  int x=0;
  for(int i=3;i<16;i++){
    for(int j=1;j<5;j++){
      CardName[x++]=StrToInt(IntToStr(i)+IntToStr(j));
    }
  }
  for(int i=0;i<1000;i++){
    int t,s;
    for(int j=0;j<52;j++){
      t=random(52);
      s=CardName[t];
      CardName[t]=CardName[j];
      CardName[j]=s;
    }
  }

  Password1B->Enabled=false;
  Password2B->Enabled=false;
  Password3B->Enabled=false;
  Password4B->Enabled=false;
  P1->Visible=false;
  P2->Visible=false;
  P3->Visible=false;
  P4->Visible=false;
  PassB1->Enabled=true;
  PassB2->Enabled=true;
  PassB3->Enabled=true;
  PassB4->Enabled=true;
  player1=false;
  player2=false;
  player3=false;
  player4=false;
  firstround=true;
  Card=0;
  circle=0;
  win1=0;
  win2=0;
  win3=0;
  win4=0;
  thisnum=0;
  lastnum=0;
  thiscolor=0;
  lastcolor=0;
  lastcard=0;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ChooseClick(TObject *Sender)
{
  TImage *Go=(TImage *)Sender;

  if(Go->Top==15&&Card<5){
    Go->Top=0;
    ChooseCard[Card]=Go;
    Card++;
  }else{
    if(Go->Top==0){
      Go->Top=15;
      int x;
      for(int i=0;i<Card-1;i++){
        if(ChooseCard[i]==Go) x=1;
        if(x==1) ChooseCard[i]=ChooseCard[i+1];
      }
      ChooseCard[Card-1]=NULL;
      Card--;
    }
  }
}
//---------------------------------------------------------------------------




void __fastcall TForm1::GoB1Click(TObject *Sender)
{
  if(Card==1){
    thisnum=ChooseCard[0]->Tag;
    thiscolor=StrToInt(ChooseCard[0]->Hint);
  }else{
    if(Card==2&&ChooseCard[0]->Tag==ChooseCard[1]->Tag){
      thisnum=StrToInt(IntToStr(ChooseCard[0]->Tag)+IntToStr(ChooseCard[1]->Tag));
      thiscolor=StrToInt(ChooseCard[0]->Hint)+StrToInt(ChooseCard[1]->Hint);
    }else{
      if(Card==5){
        int x=1;
        TImage *t;
        for(int i=1;i<5;i++){
          if(ChooseCard[0]->Tag==ChooseCard[i]->Tag){
            t=ChooseCard[x];
            ChooseCard[x++]=ChooseCard[i];
            ChooseCard[i]=t;
          }
        }
        //ShowMessage(IntToStr(ChooseCard[0]->Tag)+IntToStr(ChooseCard[1]->Tag)+IntToStr(ChooseCard[2]->Tag)+IntToStr(ChooseCard[3]->Tag)+IntToStr(ChooseCard[4]->Tag));
        if(ChooseCard[1]->Tag!=ChooseCard[2]->Tag){
          if(ChooseCard[0]->Tag==ChooseCard[1]->Tag&&ChooseCard[2]->Tag==ChooseCard[3]->Tag&&ChooseCard[3]->Tag==ChooseCard[4]->Tag){
            thisnum=StrToInt(IntToStr(ChooseCard[2]->Tag)+IntToStr(ChooseCard[3]->Tag)+IntToStr(ChooseCard[4]->Tag)+IntToStr(ChooseCard[0]->Tag)+IntToStr(ChooseCard[1]->Tag));
          }else{
            ShowMessage("這五張牌是不是哪裡搞錯了!?");
            return;
          }
        }else{
          if(ChooseCard[0]->Tag==ChooseCard[1]->Tag&&ChooseCard[1]->Tag==ChooseCard[2]->Tag&&ChooseCard[3]->Tag==ChooseCard[4]->Tag){
            thisnum=StrToInt(IntToStr(ChooseCard[0]->Tag)+IntToStr(ChooseCard[1]->Tag)+IntToStr(ChooseCard[2]->Tag)+IntToStr(ChooseCard[3]->Tag)+IntToStr(ChooseCard[4]->Tag));
          }else{
            if(ChooseCard[0]->Tag==ChooseCard[1]->Tag&&ChooseCard[1]->Tag==ChooseCard[2]->Tag&&ChooseCard[2]->Tag==ChooseCard[3]->Tag){
              thisnum=StrToInt(IntToStr(ChooseCard[0]->Tag)+IntToStr(ChooseCard[1]->Tag)+IntToStr(ChooseCard[2]->Tag)+IntToStr(ChooseCard[3]->Tag)+IntToStr(ChooseCard[4]->Tag));
            }else{
              if(ChooseCard[1]->Tag==ChooseCard[2]->Tag&&ChooseCard[2]->Tag==ChooseCard[3]->Tag&&ChooseCard[3]->Tag==ChooseCard[4]->Tag){
                thisnum=StrToInt(IntToStr(ChooseCard[1]->Tag)+IntToStr(ChooseCard[2]->Tag)+IntToStr(ChooseCard[3]->Tag)+IntToStr(ChooseCard[4]->Tag)+IntToStr(ChooseCard[0]->Tag));
              }
            }
          }
        }
      }else{
        ShowMessage("你不該那樣出的ˊ_>ˋ");
        return;
      }
    }
  }
  if(firstround==true||circle==3||Card==lastcard&&thisnum>lastnum||Card==lastcard&&thisnum>lastnum&&thiscolor>lastcolor){
    for(int i=0;i<5;i++){
      delete TableCard1[i];
      TableCard1[i]=NULL;
    }


    for(int i=0;i<5;i++){
      TableCard[i]=new TImage(Form1);
      TableCard[i]->Width=w;
      TableCard[i]->Height=h;
      TableCard[i]->Top=0;
      TableCard[i]->Stretch=true;
      TableCard1[i]=TableCard[i];
    }
  }

  if(firstround==true||circle==3){
    if(circle!=3){
      bool Ans;
      for(int i=0;i<Card;i++){
        if(ChooseCard[i]->Tag==3) Ans=true;
      }
      if(Ans!=true){
        ShowMessage("第一張牌要有梅花三哦~");
        return;
      }
    }  

    firstround=false;
    lastcard=Card;
    lastnum=thisnum;
    lastcolor=thiscolor;
    Anser=true;
    PassB1->Enabled=true; PassB2->Enabled=true; PassB3->Enabled=true; PassB4->Enabled=true;
    for(int i=0;i<Card;i++){
      TableCard[i]->Parent=TableP;
      TableCard[i]->Picture=ChooseCard[i]->Picture;
      TableCard[i]->Left=w*i;
      ChooseCard[i]->Visible=false;
    }
    win=Card;
    circle=0;
    Card=0;
  }else{
    if(Card==lastcard){
      if(thisnum>lastnum){
        lastcard=Card;
        lastnum=thisnum;
        lastcolor=thiscolor;
        Anser=true;
        PassB1->Enabled=true; PassB2->Enabled=true; PassB3->Enabled=true; PassB4->Enabled=true;
        for(int i=0;i<Card;i++){
          TableCard[i]->Parent=TableP;
          TableCard[i]->Picture=ChooseCard[i]->Picture;
          TableCard[i]->Left=w*i;
          ChooseCard[i]->Visible=false;
        }
        win=Card;
        circle=0;
        Card=0;
      }else{
        if(thisnum==lastnum&&thiscolor>lastcolor){
          lastcard=Card;
          lastnum=thisnum;
          lastcolor=thiscolor;
          Anser=true;
          PassB1->Enabled=true; PassB2->Enabled=true; PassB3->Enabled=true; PassB4->Enabled=true;
          for(int i=0;i<Card;i++){
            TableCard[i]->Parent=TableP;
            TableCard[i]->Picture=ChooseCard[i]->Picture;
            TableCard[i]->Left=w*i;
            ChooseCard[i]->Visible=false;
          }
          win=Card;
          circle=0;
          Card=0;
        }else{
          ShowMessage("你出的比較小欸= =");
          return;
        }
      }
    }else{
      ShowMessage("您會不會玩大老二呀!?");
      return;
    }
  }
  if(Anser==true){
    if(player1==true){
      P1->Visible=false;
      Password1B->Enabled=false;
      Password2B->Enabled=true;
      player1=false;
      win1=win1+win;
    }else{
      if(player2==true){
        P2->Visible=false;
        Password2B->Enabled=false;
        Password3B->Enabled=true;
        player2=false;
        win2=win2+win;
      }else{
        if(player3==true){
          P3->Visible=false;
          Password3B->Enabled=false;
          Password4B->Enabled=true;
          player3=false;
          win3=win3+win;
        }else{
          if(player4==true){
            P4->Visible=false;
            Password4B->Enabled=false;
            Password1B->Enabled=true;
            player4=false;
            win4=win4+win;
          }
        }
      }
    }
  }
  if(win1==13||win2==13||win3==13||win4==13){
    for(int i=0;i<5;i++){
      delete TableCard1[i];
      TableCard1[i]=NULL;
    }

    for(int i=0;i<52;i++){
      delete AllCard[i];
      AllCard[i]=NULL;
    }
  }

  if(win1==13){
    ShowMessage("WOW~恭喜一號玩家獲得勝利");
    Password2B->Enabled=false;
  }else{
    if(win2==13){
      ShowMessage("WOW~恭喜二號玩家獲得勝利");
      Password3B->Enabled=false;
    }else{
      if(win3==13){
        ShowMessage("WOW~恭喜三號玩家獲得勝利");
        Password4B->Enabled=false;
      }else{
        if(win4==13){
          ShowMessage("WOW~恭喜四號玩家獲得勝利");
          Password1B->Enabled=false;
        }
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GoB2Click(TObject *Sender)
{
  GoB1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GoB3Click(TObject *Sender)
{
  GoB1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GoB4Click(TObject *Sender)
{
  GoB1Click(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Password1BClick(TObject *Sender)
{
  if(Password1E->Text!=""){
    if(Password1E->Text.ToInt()==Password[0]){
      P1->Visible=true;
      player1=true;
      Password1E->Text="";
    }else{
      ShowMessage("密碼錯誤");
    }
  }
  if(circle==3) PassB1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Password2BClick(TObject *Sender)
{
  if(Password2E->Text!=""){
    if(Password2E->Text.ToInt()==Password[1]){
      P2->Visible=true;
      player2=true;
      Password2E->Text="";
    }else{
      ShowMessage("密碼錯誤");
    }
  }
  if(circle==3) PassB2->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Password3BClick(TObject *Sender)
{
  if(Password3E->Text!=""){
    if(Password3E->Text.ToInt()==Password[2]){
      P3->Visible=true;
      player3=true;
      Password3E->Text="";
    }else{
      ShowMessage("密碼錯誤");
    }
  }
  if(circle==3) PassB3->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Password4BClick(TObject *Sender)
{
  if(Password4E->Text!=""){
    if(Password4E->Text.ToInt()==Password[3]){
      P4->Visible=true;
      player4=true;
      Password4E->Text="";
    }else{
      ShowMessage("密碼錯誤");
    }
  }
  if(circle==3) PassB4->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PassB1Click(TObject *Sender)
{
  for(int i=0;i<Card;i++){
    ChooseCard[i]->Top=15;
    ChooseCard[i]=NULL;
  }

  circle++;
  P1->Visible=false;
  Password1B->Enabled=false;
  Password2B->Enabled=true;
  player1=false;
  Card=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PassB2Click(TObject *Sender)
{
  for(int i=0;i<Card;i++){
    ChooseCard[i]->Top=15;
    ChooseCard[i]=NULL;
  }

  circle++;
  P2->Visible=false;
  Password2B->Enabled=false;
  Password3B->Enabled=true;
  player2=false;
  Card=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PassB3Click(TObject *Sender)
{
  for(int i=0;i<Card;i++){
    ChooseCard[i]->Top=15;
    ChooseCard[i]=NULL;
  }

  circle++;
  P3->Visible=false;
  Password3B->Enabled=false;
  Password4B->Enabled=true;
  player3=false;
  Card=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PassB4Click(TObject *Sender)
{
  for(int i=0;i<Card;i++){
    ChooseCard[i]->Top=15;
    ChooseCard[i]=NULL;
  }

  circle++;
  P4->Visible=false;
  Password4B->Enabled=false;
  Password1B->Enabled=true;
  player4=false;
  Card=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ReBClick(TObject *Sender)
{
  FormCreate(Sender);
  StartBClick(Sender);
}
//---------------------------------------------------------------------------

