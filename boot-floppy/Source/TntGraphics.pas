
{*****************************************************************************}
{                                                                             }
{    Tnt Delphi Unicode Controls                                              }
{      http://home.ccci.org/wolbrink/tnt/delphi_unicode_controls.htm          }
{                                                                             }
{    Copyright (c) 2002, 2003 Troy Wolbrink (troy.wolbrink@ccci.org)          }
{                                                                             }
{*****************************************************************************}

unit TntGraphics;

{$INCLUDE Compilers.inc}

interface

uses
  Graphics, Windows;

{TNT-WARN TextRect}
procedure WideCanvasTextRect(Canvas: TCanvas; Rect: TRect; X, Y: Integer; const Text: WideString);
{TNT-WARN TextOut}
procedure WideCanvasTextOut(Canvas: TCanvas; X, Y: Integer; const Text: WideString);
{TNT-WARN TextExtent}
function WideCanvasTextExtent(Canvas: TCanvas; const Text: WideString): TSize;
function WideDCTextExtent(hDC: THandle; const Text: WideString): TSize;
{TNT-WARN TextWidth}
function WideCanvasTextWidth(Canvas: TCanvas; const Text: WideString): Integer;
{TNT-WARN TextHeight}
function WideCanvasTextHeight(Canvas: TCanvas; const Text: WideString): Integer;

implementation

type
  TAccessCanvas = class(TCanvas);

procedure WideCanvasTextRect(Canvas: TCanvas; Rect: TRect; X, Y: Integer; const Text: WideString);
var
  Options: Longint;
begin
  with TAccessCanvas(Canvas) do begin
    Changing;
    RequiredState([csHandleValid, csFontValid, csBrushValid]);
    Options := ETO_CLIPPED or TextFlags;
    if Brush.Style <> bsClear then
      Options := Options or ETO_OPAQUE;
    if ((TextFlags and ETO_RTLREADING) <> 0) and
       (CanvasOrientation = coRightToLeft) then Inc(X, WideCanvasTextWidth(Canvas, Text) + 1);
    Windows.ExtTextOutW(Handle, X, Y, Options, @Rect, PWideChar(Text),
      Length(Text), nil);
    Changed;
  end;
end;

procedure WideCanvasTextOut(Canvas: TCanvas; X, Y: Integer; const Text: WideString);
begin
  with TAccessCanvas(Canvas) do begin
    Changing;
    RequiredState([csHandleValid, csFontValid, csBrushValid]);
    if CanvasOrientation = coRightToLeft then Inc(X, WideCanvasTextWidth(Canvas, Text) + 1);
    Windows.ExtTextOutW(Handle, X, Y, TextFlags, nil, PWideChar(Text),
     Length(Text), nil);
    MoveTo(X + WideCanvasTextWidth(Canvas, Text), Y);
    Changed;
  end;
end;

function WideDCTextExtent(hDC: THandle; const Text: WideString): TSize;
begin
  Result.cx := 0;
  Result.cy := 0;
  Windows.GetTextExtentPoint32W(hDC, PWideChar(Text), Length(Text), Result);
end;

function WideCanvasTextExtent(Canvas: TCanvas; const Text: WideString): TSize;
begin
  with TAccessCanvas(Canvas) do begin
    RequiredState([csHandleValid, csFontValid]);
    Result := WideDCTextExtent(Handle, Text);
  end;
end;

function WideCanvasTextWidth(Canvas: TCanvas; const Text: WideString): Integer;
begin
  Result := WideCanvasTextExtent(Canvas, Text).cX;
end;

function WideCanvasTextHeight(Canvas: TCanvas; const Text: WideString): Integer;
begin
  Result := WideCanvasTextExtent(Canvas, Text).cY;
end;

end.
