unit GameForms;

{ Class, component, and published handler names are DFM serialization keys. }
interface
uses
  Windows,
  Messages,
  SysUtils,
  Classes,
  Graphics,
  Controls,
  Forms,
  Dialogs,
  StdCtrls,
  ExtCtrls,
  ComCtrls,
  Menus,
  Buttons,
  FileCtrl,
  MPlayer,
  GameState,
  GameCore;

type
{$I FormDeclarations.inc}

var
  MainForm: TTSW10;
  AboutBox: TAboutBox;
  DataHolderForm: TForm4;
  RankingForm: TForm2;

{ Layout helpers are also entry points for the comparison probes. }
procedure ApplyFontLayout(Form: TTSW10);
procedure PrepareSceneGraphics(Form: TTSW10);
procedure PushEvent(Opcode, A, B: Longint);
procedure InitializeAudio(Form: TTSW10);
procedure PlayEffect(Form: TTSW10; Index: Integer);
procedure UpdateFairyRanking(Form: TTSW10; Category: Longint);
procedure QueueEnding(Form: TTSW10);
procedure ConfigurePaths(const Assets, Saves: string);
procedure ActivatePortableInstallation(Form: TTSW10);
function BattleNeedsRefill: Boolean;
procedure QueueNextBattleTurn(Form: TTSW10);
procedure CancelBattle;

implementation
uses
  GameGraphics,
  Persistence,
  Gameplay,
  Audio,
  MMSystem,
  ShellAPI;

constructor TTSW10.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  { Windows forces disabled edit text to COLOR_GRAYTEXT. Keep the message
    line read-only and enabled so its white text remains visible. }
  Edit8.ReadOnly := True;
  Edit8.TabStop := False;
  Edit8.Enabled := True;
  Edit8.Color := clGray;
  Edit8.Font.Color := clWhite;
end;

procedure TTSW10.syokidata;
begin
  InitializeCycle;
end;
procedure TTSW10.mmmes;
begin
  ClassifyNeighbor;
end;
procedure TTSW10.mmes;
begin
  ClassifyInteraction;
end;
procedure TTSW10.kaidanupcheck;
begin
  FaceUpLanding;
end;
procedure TTSW10.kaidandowncheck;
begin
  FaceDownLanding;
end;
procedure TTSW10.damecount;
begin
  CountHeroStrikes;
end;
procedure TTSW10.damecount2;
begin
  CountDoubleHeroStrikes;
end;
procedure TTSW10.ydamecount;
begin
  CountEnemyStrikes;
end;
procedure TTSW10.ydameiji;
begin
  EnemyFirstDamage;
end;
procedure TTSW10.imagework;
begin
  SelectGraphicFrame;
end;
procedure TTSW10.ydameiji2;
begin
  DoubleEnemyFirstDamage;
end;
procedure TTSW10.damei3;
begin
  CountBattleHeroStrikes;
end;
procedure TTSW10.ydamei3;
begin
  CountBattleEnemyStrikes;
end;
procedure TTSW10.dameiji2;
begin
  BattleDamage;
end;
procedure TTSW10.doorstackin;
begin
  DoorAnimation;
end;
procedure TTSW10.matokwork;
begin
  MattockWall;
end;
procedure TTSW10.yukiwork;
begin
  CrystalLava;
end;
procedure TTSW10.doorcheck;
begin
  CheckSpecialDoors;
end;

procedure TTSW10.itemdel; { $00450758 }
begin
  InputEnabled := 0;
  if MouseControl1.Checked then
  begin
    BitBtn1.Enabled := False;
    BitBtn2.Enabled := False;
    BitBtn3.Enabled := False;
    BitBtn4.Enabled := False;
  end;
  Image4.Enabled := False;
  Image5.Enabled := False;
  Image6.Enabled := False;
  Image8.Enabled := False;
  Image9.Enabled := False;
  Image10.Enabled := False;
  Image11.Enabled := False;
  Image12.Enabled := False;
  Image13.Enabled := False;
  Image15.Enabled := False;
  Image16.Enabled := False;
  Image17.Enabled := False;
  HighScore1.Enabled := False;
  GameLoad1.Enabled := False;
  GameSave1.Enabled := False;
  Option1.Enabled := False;
end;

procedure TTSW10.itemlive; { $00450880 }
begin
  if Hero.hero_orb <> 2 then
  begin
    if MouseControl1.Checked and not Timer4.Enabled then
    begin
      BitBtn1.Enabled := True;
      BitBtn1.Visible := True;
      BitBtn2.Enabled := True;
      BitBtn2.Visible := True;
      BitBtn3.Enabled := True;
      BitBtn3.Visible := True;
      BitBtn4.Enabled := True;
      BitBtn4.Visible := True;
    end;
    if KeyboardControl1.Checked then
      KeyPreview := True;
    if Hero.hero_orb = 1 then
    begin
      Image6.Enabled := True;
      GameSave1.Enabled := True;
    end
    else
    begin
      GameSave1.Enabled := False;
      Image6.Visible := False;
    end;
    if Hero.wisdom_orb = 1 then
      Image5.Enabled := True
    else
      Image5.Visible := False;
    if Hero.flight_orb = 1 then
      Image4.Enabled := True
    else
      Image4.Visible := False;
    Image7.Visible := Hero.cross = 1;
    if Hero.elixir = 1 then
      Image8.Enabled := True
    else
      Image8.Visible := False;
    if Hero.mattock = 1 then
      Image9.Enabled := True
    else
      Image9.Visible := False;
    if Hero.bomb = 1 then
      Image10.Enabled := True
    else
      Image10.Visible := False;
    if Hero.warp_staff >= 1 then
      Image11.Enabled := True
    else
      Image11.Visible := False;
    if Hero.ascent_wing = 1 then
      Image12.Enabled := True
    else
      Image12.Visible := False;
    if Hero.descent_wing = 1 then
      Image13.Enabled := True
    else
      Image13.Visible := False;
    Image14.Visible := Hero.dragon_slayer = 1;
    if Hero.snow_crystal = 1 then
      Image15.Enabled := True
    else
      Image15.Visible := False;
    if Hero.magic_key = 1 then
      Image16.Enabled := True
    else
      Image16.Visible := False;
    if Hero.super_mattock = 1 then
      Image17.Enabled := True
    else
      Image17.Visible := False;
    Image18.Visible := Hero.lucky_gold = 1;
    InputEnabled := 1;
    HighScore1.Enabled := True;
    GameLoad1.Enabled := True;
    Option1.Enabled := True;
  end;
end;

procedure TTSW10.timer2on; { $0044BC0C }
begin
  Timer3.Enabled := False;
  itemdel;
  Timer2.Enabled := True;
end;

procedure TTSW10.Button37Click(Sender: TObject); { $00450B78 }
begin
  Button37.Visible := False;
  Button38.Visible := False;
  itemlive;
end;

procedure TAboutBox.OKButtonClick(Sender: TObject);
begin
  ModalResult := 1;
end;
procedure TAboutBox.AboutBoxonclose(Sender: TObject; var Action: TCloseAction);
begin
  ModalResult := 1;
end;
procedure TAboutBox.image1onclick(Sender: TObject);
begin
  Image1.Visible := False;
  ProgramIcon.Visible := True;
end;
procedure TAboutBox.image2onclick(Sender: TObject);
begin
  Image1.Visible := True;
  ProgramIcon.Visible := False;
  Image2.Visible := False;
end;
procedure TAboutBox.programicononclick(Sender: TObject);
begin
  Image1.Visible := True;
  ProgramIcon.Visible := False;
  Image2.Visible := False;
end;
procedure TAboutBox.Timer1Timer(Sender: TObject);
begin
  if ProgramIcon.Visible then
  begin
    Image2.Visible := True;
    ProgramIcon.Visible := False;
    Exit;
  end;
  if Image2.Visible then
  begin
    ProgramIcon.Visible := True;
    Image2.Visible := False;
  end;
end;

procedure TForm4.DriveComboBox1Change(Sender: TObject);
begin
  DirectoryListBox1.Drive := DriveComboBox1.Drive;
end;
procedure TForm4.DirectoryListBox1Change(Sender: TObject);
begin
  memo1.Text := DirectoryListBox1.Directory;
  FileListBox1.Directory := DirectoryListBox1.Directory;
end;
procedure TForm4.Button2Click(Sender: TObject);
begin
  ModalResult := 1;
end;

{$I GraphicsMethods.inc}
{$I FlightMethods.inc}
{$I StartupMethods.inc}
{$I UiMethods.inc}
{$I AudioMethods.inc}
{$I PersistenceMethods.inc}
{$I OptionsMethods.inc}
{$I EventMethods.inc}
{$I GameplayMethods.inc}
end.
