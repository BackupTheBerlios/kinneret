
{*****************************************************************************}
{                                                                             }
{    Tnt Delphi Unicode Controls                                              }
{      http://home.ccci.org/wolbrink/tnt/delphi_unicode_controls.htm          }
{                                                                             }
{    Copyright (c) 2002, 2003 Troy Wolbrink (troy.wolbrink@ccci.org)          }
{                                                                             }
{*****************************************************************************}

unit TntSysUtils;

{$INCLUDE Compilers.inc}

interface

{$IFDEF COMPILER_6_UP}
{$WARN SYMBOL_PLATFORM OFF} { We are going to use Win32 specific symbols! }
{$ENDIF}

uses
  {$IFDEF COMPILER_6_UP} Types, {$ENDIF} SysUtils, Windows;

//---------------------------------------------------------------------------------------------
//                                 Tnt - Types
//---------------------------------------------------------------------------------------------

{$IFNDEF COMPILER_6_UP} // Delphi 5 compatibility
type
  TWideStringDynArray = array of WideString;
{$ENDIF}

//---------------------------------------------------------------------------------------------
//                                 Tnt - System
//---------------------------------------------------------------------------------------------

// ......... compatibility .........
{$IFNDEF COMPILER_6_UP} // Delphi 5 compatibility
type UTF8String = type AnsiString;
function UTF8Encode(const WS: WideString): UTF8String;
function UTF8Decode(const S: UTF8String): WideString;
{$ENDIF}

// ................ ANSI TYPES ................
{TNT-WARN Char}
{TNT-WARN PChar}
{TNT-WARN String}

{TNT-WARN CP_ACP} // <-- use DefaultUserCodePage
var
  DefaultUserCodePage: Cardinal; // implicitly used when convering AnsiString <--> WideString.

{TNT-WARN LoadResString}
function LoadResStringW(ResStringRec: PResStringRec): WideString;
{TNT-WARN ParamCount}
function WideParamCount: Integer;
{TNT-WARN ParamStr}
function WideParamStr(Index: Integer): WideString;

// ......... introduced .........

const
  CR = WideChar(#13);
  LF = WideChar(#10);
  CRLF = WideString(#13#10);
  WideLineSeparator = WideChar($2028);

  { Each Unicode stream should begin with the code U+FEFF,  }
  {   which the standard defines as the *byte order mark*.  }
  UNICODE_BOM = WideChar($FEFF);
  UNICODE_BOM_SWAPPED = WideChar($FFFE);

function WideStringToUTF8(const S: WideString): AnsiString;
function UTF8ToWideString(const S: AnsiString): WideString;

function WideStringToUTF7(const W: WideString): AnsiString;
function UTF7ToWideString(const S: AnsiString): WideString;

function StringToWideStringEx(const S: AnsiString; CodePage: Cardinal): WideString;
function WideStringToStringEx(const WS: WideString; CodePage: Cardinal): AnsiString;

function UCS2ToWideString(const Value: AnsiString): WideString;
function WideStringToUCS2(const Value: WideString): AnsiString;

function CharSetToCodePage(ciCharset: UINT): Cardinal;
function LCIDToCodePage(ALcid: LCID): Cardinal;
function KeyboardCodePage: Cardinal;
function KeyUnicode(C: AnsiChar): WideChar;

procedure StrSwapByteOrder(Str: PWideChar);

//---------------------------------------------------------------------------------------------
//                                 Tnt - SysUtils
//---------------------------------------------------------------------------------------------

// ......... compatibility .........
{$IFNDEF COMPILER_6_UP} // Delphi 5 compatibility
const sLineBreak = #13#10;
const PathDelim = '\';
const DriveDelim = ':';
const PathSep = ';';

procedure RaiseLastOSError;
function WideFormat(const FormatStr: WideString; const Args: array of const): WideString;
function WideCompareStr(const W1, W2: WideString): Integer;
function WideSameStr(const W1, W2: WideString): Boolean;
function WideCompareText(const W1, W2: WideString): Integer;
function WideSameText(const W1, W2: WideString): Boolean;
function Supports(const Instance: TObject; const IID: TGUID): Boolean;
{$ENDIF}

// ......... SBCS and MBCS functions with WideString replacements in SysUtils.pas .........

{TNT-WARN CompareStr}                   {TNT-WARN AnsiCompareStr}
{TNT-WARN SameStr}                      {TNT-WARN AnsiSameStr}
{TNT-WARN SameText}                     {TNT-WARN AnsiSameText}
{TNT-WARN CompareText}                  {TNT-WARN AnsiCompareText}
{TNT-WARN UpperCase}                    {TNT-WARN AnsiUpperCase}
{TNT-WARN LowerCase}                    {TNT-WARN AnsiLowerCase}

{TNT-WARN AnsiPos}  { --> Pos() supports WideString. }
{TNT-WARN FmtStr}
{TNT-WARN Format}
{TNT-WARN FormatBuf}

// ......... MBCS Byte Type Procs .........

{TNT-WARN ByteType}
{TNT-WARN StrByteType}
{TNT-WARN ByteToCharIndex}
{TNT-WARN ByteToCharLen}
{TNT-WARN CharToByteIndex}
{TNT-WARN CharToByteLen}

// ........ null-terminated string functions .........

{TNT-WARN StrEnd}
function StrEndW(Str: PWideChar): PWideChar;
{TNT-WARN StrLen}
function StrLenW(Str: PWideChar): Cardinal;
{TNT-WARN StrLCopy}
function StrLCopyW(Dest, Source: PWideChar; MaxLen: Cardinal): PWideChar;
{TNT-WARN StrCopy}
function StrCopyW(Dest, Source: PWideChar): PWideChar;
{TNT-WARN StrECopy}
function StrECopyW(Dest, Source: PWideChar): PWideChar;
{TNT-WARN StrPLCopy}
{TNT-WARN StrPLCopyW}  // <-- accepts ansi string parameter
function StrPLCopyW{TNT-ALLOW StrPLCopyW}(Dest: PWideChar; const Source: AnsiString; MaxLen: Cardinal): PWideChar;
{TNT-WARN StrPCopy}
{TNT-WARN StrPCopyW}   // < -- accepts ansi string parameter
function StrPCopyW{TNT-ALLOW StrPCopyW}(Dest: PWideChar; const Source: AnsiString): PWideChar;
{TNT-WARN StrLComp}
{TNT-WARN AnsiStrLComp}
function StrLCompW(Str1, Str2: PWideChar; MaxLen: Cardinal): Integer;
{TNT-WARN StrComp}
{TNT-WARN AnsiStrComp}
function StrCompW(Str1, Str2: PWideChar): Integer;
{TNT-WARN StrLIComp}
{TNT-WARN AnsiStrLIComp}
function StrLICompW(Str1, Str2: PWideChar; MaxLen: Cardinal): Integer;
{TNT-WARN StrIComp}
{TNT-WARN AnsiStrIComp}
function StrICompW(Str1, Str2: PWideChar): Integer;
{TNT-WARN StrLower}
{TNT-WARN AnsiStrLower}
function StrLowerW(Str: PWideChar): PWideChar;
{TNT-WARN StrUpper}
{TNT-WARN AnsiStrUpper}
function StrUpperW(Str: PWideChar): PWideChar;
{TNT-WARN StrPos}
{TNT-WARN AnsiStrPos}
function StrPosW(Str, SubStr: PWideChar): PWideChar;
{TNT-WARN StrScan}
{TNT-WARN AnsiStrScan}
function StrScanW(const Str: PWideChar; Chr: WideChar): PWideChar;
{TNT-WARN StrRScan}
{TNT-WARN AnsiStrRScan}
function StrRScanW(const Str: PWideChar; Chr: WideChar): PWideChar;
{TNT-WARN StrLCat}
function StrLCatW(Dest: PWideChar; const Source: PWideChar; MaxLen: Cardinal): PWideChar;
{TNT-WARN StrCat}
function StrCatW(Dest: PWideChar; const Source: PWideChar): PWideChar;
{TNT-WARN StrMove}
function StrMoveW(Dest: PWideChar; const Source: PWideChar; Count: Cardinal): PWideChar;
{TNT-WARN StrPas}
function StrPasW(const Str: PWideChar): WideString;
{TNT-WARN StrAlloc}
function StrAllocW(Size: Cardinal): PWideChar;
{TNT-WARN StrBufSize}
function StrBufSizeW(const Str: PWideChar): Cardinal;
{TNT-WARN StrNew}
function StrNewW(const Str: PWideChar): PWideChar;
{TNT-WARN StrDispose}
procedure StrDisposeW(Str: PWideChar);

// ........ string functions .........

{TNT-WARN WideUpperCase} // SysUtils.WideUpperCase is broken on Win9x.
function Tnt_WideUpperCase(const S: WideString): WideString;

{TNT-WARN WideLowerCase} // SysUtils.WideLowerCase is broken on Win9x.
function Tnt_WideLowerCase(const S: WideString): WideString;

{TNT-WARN AnsiLastChar}
{TNT-WARN AnsiStrLastChar}
function WideLastChar(W: WideString): WideChar;

{TNT-WARN StringReplace}
function WideStringReplace(const S, OldPattern, NewPattern: WideString;
  Flags: TReplaceFlags; WholeWord: Boolean = False): WideString;

{TNT-WARN AdjustLineBreaks}
type TTntTextLineBreakStyle = (tlbsLF, tlbsCRLF, tlbsCR);
function TntAdjustLineBreaksLength(const S: WideString; Style: TTntTextLineBreakStyle = tlbsCRLF): Integer;
function TntAdjustLineBreaks(const S: WideString; Style: TTntTextLineBreakStyle = tlbsCRLF): WideString;

{TNT-WARN QuotedStr}
{TNT-WARN AnsiQuotedStr}
function WideQuotedStr(const S: WideString; Quote: WideChar = '"'): WideString;

{TNT-WARN AnsiExtractQuotedStr}
function WideExtractQuotedStr(var Src: PWideChar; Quote: WideChar = '"'): WideString;

{TNT-WARN WrapText}
function WideWrapText(const Line, BreakStr: WideString; const BreakChars: TSysCharSet;
  MaxCol: Integer): WideString; overload;
function WideWrapText(const Line: WideString; MaxCol: Integer): WideString; overload;

// ........ filename manipulation .........

{TNT-WARN SameFileName}           // doesn't apply to Unicode filenames, use WideSameText
{TNT-WARN AnsiCompareFileName}    // doesn't apply to Unicode filenames, use WideCompareText
{TNT-WARN AnsiLowerCaseFileName}  // doesn't apply to Unicode filenames, use WideLowerCase
{TNT-WARN AnsiUpperCaseFileName}  // doesn't apply to Unicode filenames, use WideUpperCase

{TNT-WARN IncludeTrailingBackslash}
function WideIncludeTrailingBackslash(const S: WideString): WideString;
{TNT-WARN ExcludeTrailingBackslash}
function WideExcludeTrailingBackslash(const S: WideString): WideString;
{TNT-WARN IsDelimiter}
function WideIsDelimiter(const Delimiters, S: WideString; Index: Integer): Boolean;
{TNT-WARN IsPathDelimiter}
function WideIsPathDelimiter(const S: WideString; Index: Integer): Boolean;
{TNT-WARN LastDelimiter}
function WideLastDelimiter(const Delimiters, S: WideString): Integer;
{TNT-WARN ChangeFileExt}
function WideChangeFileExt(const FileName, Extension: WideString): WideString;
{TNT-WARN ExtractFilePath}
function WideExtractFilePath(const FileName: WideString): WideString;
{TNT-WARN ExtractFileDir}
function WideExtractFileDir(const FileName: WideString): WideString;
{TNT-WARN ExtractFileDrive}
function WideExtractFileDrive(const FileName: WideString): WideString;
{TNT-WARN ExtractFileName}
function WideExtractFileName(const FileName: WideString): WideString;
{TNT-WARN ExtractFileExt}
function WideExtractFileExt(const FileName: WideString): WideString;
{TNT-WARN ExtractRelativePath}
function WideExtractRelativePath(const BaseName, DestName: WideString): WideString;

// ........ file management routines .........

{TNT-WARN FileCreate}
function WideFileCreate(const FileName: WideString): Integer;
{TNT-WARN FileOpen}
function WideFileOpen(const FileName: WideString; Mode: LongWord): Integer;
{TNT-WARN DirectoryExists}
function WideDirectoryExists(const Name: WideString): Boolean;
{TNT-WARN FileExists}
function WideFileExists(const Name: WideString): Boolean;
{TNT-WARN FileGetAttr}
function WideFileGetAttr(const FileName: WideString): Cardinal;
{TNT-WARN FileSetAttr}
function WideFileSetAttr(const FileName: WideString; Attr: Integer): Boolean;
{TNT-WARN ForceDirectories}
function WideForceDirectories(Dir: WideString): Boolean;
{TNT-WARN FileSearch}
function WideFileSearch(const Name, DirList: WideString): WideString;
{TNT-WARN RenameFile}
function WideRenameFile(const OldName, NewName: WideString): Boolean;
{TNT-WARN DeleteFile}
function WideDeleteFile(const FileName: WideString): Boolean;
{TNT-WARN CopyFile}
function WideCopyFile(FromFile, ToFile: WideString; FailIfExists: Boolean): Boolean;

{TNT-WARN TSearchRec} // <-- FindFile - warning on TSearchRec is all that is necessary
type
  TSearchRecW = record
    Time: Integer;
    Size: Integer;
    Attr: Integer;
    Name: WideString;
    ExcludeAttr: Integer;
    FindHandle: THandle;
    FindData: TWin32FindDataW;
  end;
function WideFindFirst(const Path: WideString; Attr: Integer; var F: TSearchRecW): Integer;
function WideFindNext(var F: TSearchRecW): Integer;
procedure WideFindClose(var F: TSearchRecW);

// ........ date/time functions .........

function ValidDateTimeStr(Str: WideString): Boolean;
function ValidDateStr(Str: WideString): Boolean;
function ValidTimeStr(Str: WideString): Boolean;

{TNT-WARN StrToDateTime}
function TntStrToDateTime(Str: WideString): TDateTime;
{TNT-WARN StrToDate}
function TntStrToDate(Str: WideString): TDateTime;
{TNT-WARN StrToTime}
function TntStrToTime(Str: WideString): TDateTime;

// ........ misc functions .........

{TNT-WARN GetLocaleStr}
function WideGetLocaleStr(LocaleID: LCID; LocaleType: Integer; Default: WideString): WideString;

// ......... introduced .........

var
  Win32PlatformIsUnicode: Boolean;
  Win32PlatformIsXP: Boolean;

function WinCheckH(RetVal: Cardinal): Cardinal;
function WinCheckFileH(RetVal: Cardinal): Cardinal;
function WinCheckP(RetVal: Pointer): Pointer;

function WideGetModuleFileName(Instance: HModule): WideString;

function IsWideCharUpper(WC: WideChar): Boolean;
function IsWideCharLower(WC: WideChar): Boolean;
function IsWideCharDigit(WC: WideChar): Boolean;
function IsWideCharSpace(WC: WideChar): Boolean;
function IsWideCharPunct(WC: WideChar): Boolean;
function IsWideCharCntrl(WC: WideChar): Boolean;
function IsWideCharBlank(WC: WideChar): Boolean;
function IsWideCharXDigit(WC: WideChar): Boolean;
function IsWideCharAlpha(WC: WideChar): Boolean;
function IsWideCharAlphaNumeric(WC: WideChar): Boolean;

function WideTextPos(const SubStr, S: WideString): Integer;

function ExtractStringArrayStr(P: PWideChar): WideString;
function ExtractStringFromStringArray(var P: PWideChar; Separator: WideChar = #0): WideString;
function ExtractStringsFromStringArray(P: PWideChar; Separator: WideChar = #0): TWideStringDynArray;

//---------------------------------------------------------------------------------------------
//                                 Tnt - Variants
//---------------------------------------------------------------------------------------------

// ......... compatibility .........
{$IFNDEF COMPILER_6_UP} // Delphi 5 compatibility
function VarToWideStr(const V: Variant): WideString;
function VarToWideStrDef(const V: Variant; const ADefault: WideString): WideString;
{$ENDIF}

// ........ Variants.pas has WideString versions of these functions .........
{TNT-WARN VarToStr}
{TNT-WARN VarToStrDef}

implementation

uses
  TntWindows, Math, {$IFDEF COMPILER_6_UP} SysConst, {$ELSE} Consts, {$ENDIF} ActiveX, ComObj;

//---------------------------------------------------------------------------------------------
//                                 Tnt - System
//---------------------------------------------------------------------------------------------

{$IFNDEF COMPILER_6_UP} // Delphi 5 compatibility
function Utf8Encode(const WS: WideString): UTF8String;

    function UnicodeToUtf8(Dest: PAnsiChar; MaxDestBytes: Cardinal;
      Source: PWideChar; SourceChars: Cardinal): Cardinal;
    var
      i, count: Cardinal;
      c: Cardinal;
    begin
      Result := 0;
      if Source = nil then Exit;
      count := 0;
      i := 0;
      if Dest <> nil then
      begin
        while (i < SourceChars) and (count < MaxDestBytes) do
        begin
          c := Cardinal(Source[i]);
          Inc(i);
          if c <= $7F then
          begin
            Dest[count] := AnsiChar(c);
            Inc(count);
          end
          else if c > $7FF then
          begin
            if count + 3 > MaxDestBytes then
              break;
            Dest[count] := AnsiChar($E0 or (c shr 12));
            Dest[count+1] := AnsiChar($80 or ((c shr 6) and $3F));
            Dest[count+2] := AnsiChar($80 or (c and $3F));
            Inc(count,3);
          end
          else //  $7F < Source[i] <= $7FF
          begin
            if count + 2 > MaxDestBytes then
              break;
            Dest[count] := AnsiChar($C0 or (c shr 6));
            Dest[count+1] := AnsiChar($80 or (c and $3F));
            Inc(count,2);
          end;
        end;
        if count >= MaxDestBytes then count := MaxDestBytes-1;
        Dest[count] := #0;
      end
      else
      begin
        while i < SourceChars do
        begin
          c := Integer(Source[i]);
          Inc(i);
          if c > $7F then
          begin
            if c > $7FF then
              Inc(count);
            Inc(count);
          end;
          Inc(count);
        end;
      end;
      Result := count+1;  // convert zero based index to byte count
    end;

var
  L: Integer;
  Temp: UTF8String;
begin
  Result := '';
  if WS = '' then Exit;
  SetLength(Temp, Length(WS) * 3); // SetLength includes space for null terminator

  L := UnicodeToUtf8(PAnsiChar(Temp), Length(Temp)+1, PWideChar(WS), Length(WS));
  if L > 0 then
    SetLength(Temp, L-1)
  else
    Temp := '';
  Result := Temp;
end;

function Utf8Decode(const S: UTF8String): WideString;

    function Utf8ToUnicode(Dest: PWideChar; MaxDestChars: Cardinal;
      Source: PAnsiChar; SourceBytes: Cardinal): Cardinal;
    var
      i, count: Cardinal;
      c: Byte;
      wc: Cardinal;
    begin
      if Source = nil then
      begin
        Result := 0;
        Exit;
      end;
      Result := Cardinal(-1);
      count := 0;
      i := 0;
      if Dest <> nil then
      begin
        while (i < SourceBytes) and (count < MaxDestChars) do
        begin
          wc := Cardinal(Source[i]);
          Inc(i);
          if (wc and $80) <> 0 then
          begin
            if i >= SourceBytes then Exit;          // incomplete multibyte char
            wc := wc and $3F;
            if (wc and $20) <> 0 then
            begin
              c := Byte(Source[i]);
              Inc(i);
              if (c and $C0) <> $80 then Exit;      // malformed trail byte or out of range char
              if i >= SourceBytes then Exit;        // incomplete multibyte char
              wc := (wc shl 6) or (c and $3F);
            end;
            c := Byte(Source[i]);
            Inc(i);
            if (c and $C0) <> $80 then Exit;       // malformed trail byte

            Dest[count] := WideChar((wc shl 6) or (c and $3F));
          end
          else
            Dest[count] := WideChar(wc);
          Inc(count);
        end;
        if count >= MaxDestChars then count := MaxDestChars-1;
        Dest[count] := #0;
      end
      else
      begin
        while (i < SourceBytes) do
        begin
          c := Byte(Source[i]);
          Inc(i);
          if (c and $80) <> 0 then
          begin
            if i >= SourceBytes then Exit;          // incomplete multibyte char
            c := c and $3F;
            if (c and $20) <> 0 then
            begin
              c := Byte(Source[i]);
              Inc(i);
              if (c and $C0) <> $80 then Exit;      // malformed trail byte or out of range char
              if i >= SourceBytes then Exit;        // incomplete multibyte char
            end;
            c := Byte(Source[i]);
            Inc(i);
            if (c and $C0) <> $80 then Exit;       // malformed trail byte
          end;
          Inc(count);
        end;
      end;
      Result := count+1;
    end;

var
  L: Integer;
  Temp: WideString;
begin
  Result := '';
  if S = '' then Exit;
  SetLength(Temp, Length(S));

  L := Utf8ToUnicode(PWideChar(Temp), Length(Temp)+1, PAnsiChar(S), Length(S));
  if L > 0 then
    SetLength(Temp, L-1)
  else
    Temp := '';
  Result := Temp;
end;
{$ENDIF}

function LoadResStringW(ResStringRec: PResStringRec): WideString;
var
  Len: Integer;
begin
  if (ResStringRec = nil)
  or (ResStringRec.Identifier >= 64*1024)
  or (not Win32PlatformIsUnicode) then
    Result := System.LoadResString{TNT-ALLOW LoadResString}(ResStringRec)
  else begin
    Result := '';
    Len := 0;
    While Len = Length(Result) do begin
      if Length(Result) = 0 then
        SetLength(Result, 1024)
      else
        SetLength(Result, Length(Result) * 2);
      Len := LoadStringW(FindResourceHInstance(ResStringRec.Module^),
        ResStringRec.Identifier, PWideChar(Result), Length(Result));
    end;
    SetLength(Result, Len);
  end;
end;

function WideGetParamStr(P: PWideChar; var Param: WideString): PWideChar;
var
  Len: Integer;
  Buffer: array[0..4095] of WideChar;
begin
  while True do
  begin
    while (P[0] <> #0) and (P[0] <= ' ') do Inc(P);
    if (P[0] = '"') and (P[1] = '"') then Inc(P, 2) else Break;
  end;
  Len := 0;
  while (P[0] > ' ') and (Len < SizeOf(Buffer)) do
    if P[0] = '"' then
    begin
      Inc(P);
      while (P[0] <> #0) and (P[0] <> '"') do
      begin
        Buffer[Len] := P[0];
        Inc(Len);
        Inc(P);
      end;
      if P[0] <> #0 then Inc(P);
    end else
    begin
      Buffer[Len] := P[0];
      Inc(Len);
      Inc(P);
    end;
  SetString(Param, Buffer, Len);
  Result := P;
end;

function WideParamCount: Integer;
var
  P: PWideChar;
  S: WideString;
begin
  P := WideGetParamStr(GetCommandLineW, S);
  Result := 0;
  while True do
  begin
    P := WideGetParamStr(P, S);
    if S = '' then Break;
    Inc(Result);
  end;
end;

function WideParamStr(Index: Integer): WideString;
var
  P: PWideChar;
begin
  if Index = 0 then
    Result := WideGetModuleFileName(0)
  else
  begin
    P := GetCommandLineW;
    while True do
    begin
      P := WideGetParamStr(P, Result);
      if (Index = 0) or (Result = '') then Break;
      Dec(Index);
    end;
  end;
end;

function WideStringToUTF8(const S: WideString): AnsiString;
begin
  Result := UTF8Encode(S);
end;

function UTF8ToWideString(const S: AnsiString): WideString;
begin
  Result := UTF8Decode(S);
end;

  { ======================================================================= }
  { Original File:   ConvertUTF7.c                                          }
  { Author: David B. Goldsmith                                              }
  { Copyright (C) 1994, 1996 Taligent, Inc. All rights reserved.            }
  {                                                                         }
  { This code is copyrighted. Under the copyright laws, this code may not   }
  { be copied, in whole or part, without prior written consent of Taligent. }
  {                                                                         }
  { Taligent grants the right to use this code as long as this ENTIRE       }
  { copyright notice is reproduced in the code.  The code is provided       }
  { AS-IS, AND TALIGENT DISCLAIMS ALL WARRANTIES, EITHER EXPRESS OR         }
  { IMPLIED, INCLUDING, BUT NOT LIMITED TO IMPLIED WARRANTIES OF            }
  { MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT      }
  { WILL TALIGENT BE LIABLE FOR ANY DAMAGES WHATSOEVER (INCLUDING,          }
  { WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS      }
  { INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY          }
  { LOSS) ARISING OUT OF THE USE OR INABILITY TO USE THIS CODE, EVEN        }
  { IF TALIGENT HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.        }
  { BECAUSE SOME STATES DO NOT ALLOW THE EXCLUSION OR LIMITATION OF         }
  { LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES, THE ABOVE            }
  { LIMITATION MAY NOT APPLY TO YOU.                                        }
  {                                                                         }
  { RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the        }
  { government is subject to restrictions as set forth in subparagraph      }
  { (c)(l)(ii) of the Rights in Technical Data and Computer Software        }
  { clause at DFARS 252.227-7013 and FAR 52.227-19.                         }
  {                                                                         }
  { This code may be protected by one or more U.S. and International        }
  { Patents.                                                                }
  {                                                                         }
  { TRADEMARKS: Taligent and the Taligent Design Mark are registered        }
  { trademarks of Taligent, Inc.                                            }
  { ======================================================================= }

type UCS2 = Word;

const
  _base64: AnsiString = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/';
  _direct: AnsiString = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789''(),-./:?';
  _optional: AnsiString = '!"#$%&*;<=>@[]^_`{|}';
  _spaces: AnsiString = #9#13#10#32;

var
  base64: PAnsiChar;
  invbase64: array[0..127] of SmallInt;
  direct: PAnsiChar;
  optional: PAnsiChar;
  spaces: PAnsiChar;
  mustshiftsafe: array[0..127] of AnsiChar;
  mustshiftopt: array[0..127] of AnsiChar;

var
  needtables: Boolean = True;

procedure Initialize_UTF7_Data;
begin
  base64 := PAnsiChar(_base64);
  direct := PAnsiChar(_direct);
  optional := PAnsiChar(_optional);
  spaces := PAnsiChar(_spaces);
end;

procedure tabinit;
var
  i: Integer;
  limit: Integer;
begin
  i := 0;
  while (i < 128) do
  begin
    mustshiftopt[i] := #1;
    mustshiftsafe[i] := #1;
    invbase64[i] := -1;
    Inc(i);
  end { For };
  limit := Length(_Direct);
  i := 0;
  while (i < limit) do
  begin
    mustshiftopt[Integer(direct[i])] := #0;
    mustshiftsafe[Integer(direct[i])] := #0;
    Inc(i);
  end { For };
  limit := Length(_Spaces);
  i := 0;
  while (i < limit) do
  begin
    mustshiftopt[Integer(spaces[i])] := #0;
    mustshiftsafe[Integer(spaces[i])] := #0;
    Inc(i);
  end { For };
  limit := Length(_Optional);
  i := 0;
  while (i < limit) do
  begin
    mustshiftopt[Integer(optional[i])] := #0;
    Inc(i);
  end { For };
  limit := Length(_Base64);
  i := 0;
  while (i < limit) do
  begin
    invbase64[Integer(base64[i])] := i;
    Inc(i);
  end { For };
  needtables := False;
end; { tabinit }

function WRITE_N_BITS(x: UCS2; n: Integer; var BITbuffer: Cardinal; var bufferbits: Integer): Integer;
begin
  BITbuffer := BITbuffer or (x and (not (-1 shl n))) shl (32 - n - bufferbits);
  bufferbits := bufferbits + n;
  Result := bufferbits;
end; { WRITE_N_BITS }

function READ_N_BITS(n: Integer; var BITbuffer: Cardinal; var bufferbits: Integer): UCS2;
var
  buffertemp: Cardinal;
begin
  buffertemp := BITbuffer shr (32 - n);
  BITbuffer := BITbuffer shl n;
  bufferbits := bufferbits - n;
  Result := UCS2(buffertemp);
end; { READ_N_BITS }

function ConvertUCS2toUTF7(var sourceStart: PWideChar; sourceEnd: PWideChar;
  var targetStart: PAnsiChar; targetEnd: PAnsiChar; optional: Boolean;
    verbose: Boolean): Integer;
var
  r: UCS2;
  target: PAnsiChar;
  source: PWideChar;
  BITbuffer: Cardinal;
  bufferbits: Integer;
  shifted: Boolean;
  needshift: Boolean;
  done: Boolean;
  mustshift: PAnsiChar;
begin
  Initialize_UTF7_Data;
  Result := 0;
  BITbuffer := 0;
  bufferbits := 0;
  shifted := False;
  source := sourceStart;
  target := targetStart;
  r := 0;
  if needtables then
    tabinit;
  if optional then
    mustshift := @mustshiftopt[0]
  else
    mustshift := @mustshiftsafe[0];
  repeat
    done := source >= sourceEnd;
    if not Done then
    begin
      r := Word(source^);
      Inc(Source);
    end { If };
    needshift := (not done) and ((r > $7F) or (mustshift[r] <> #0));
    if needshift and (not shifted) then
    begin
      if (Target >= TargetEnd) then
      begin
        Result := 2;
        break;
      end { If };
      target^ := '+';
      Inc(target);
      { Special case handling of the SHIFT_IN character }
      if (r = UCS2('+')) then
      begin
        if (target >= targetEnd) then
        begin
          Result := 2;
          break;
        end;
        target^ := '-';
        Inc(target);
      end
      else
        shifted := True;
    end { If };
    if shifted then
    begin
      { Either write the character to the bit buffer, or pad }
      { the bit buffer out to a full base64 character. }
      { }
      if needshift then
        WRITE_N_BITS(r, 16, BITbuffer, bufferbits)
      else
        WRITE_N_BITS(0, (6 - (bufferbits mod 6)) mod 6, BITbuffer,
          bufferbits);
      { Flush out as many full base64 characters as possible }
      { from the bit buffer. }
      { }
      while (target < targetEnd) and (bufferbits >= 6) do
      begin
        Target^ := base64[READ_N_BITS(6, BITbuffer, bufferbits)];
        Inc(Target);
      end { While };
      if (bufferbits >= 6) then
      begin
        if (target >= targetEnd) then
        begin
          Result := 2;
          break;
        end { If };
      end { If };
      if (not needshift) then
      begin
        { Write the explicit shift out character if }
        { 1) The caller has requested we always do it, or }
        { 2) The directly encoded character is in the }
        { base64 set, or }
        { 3) The directly encoded character is SHIFT_OUT. }
        { }
        if verbose or ((not done) and ((invbase64[r] >= 0) or (r =
          Integer('-')))) then
        begin
          if (target >= targetEnd) then
          begin
            Result := 2;
            Break;
          end { If };
          Target^ := '-';
          Inc(Target);
        end { If };
        shifted := False;
      end { If };
      { The character can be directly encoded as ASCII. }
    end { If };
    if (not needshift) and (not done) then
    begin
      if (target >= targetEnd) then
      begin
        Result := 2;
        break;
      end { If };
      Target^ := AnsiChar(r);
      Inc(Target);
    end { If };
  until (done);
  sourceStart := source;
  targetStart := target;
end; { ConvertUCS2toUTF7 }

function ConvertUTF7toUCS2(var sourceStart: PAnsiChar; sourceEnd: PAnsiChar;
  var targetStart: PWideChar; targetEnd: PWideChar): Integer;
var
  target: PWideChar { Register };
  source: PAnsiChar { Register };
  BITbuffer: Cardinal { & "Address Of" Used };
  bufferbits: Integer { & "Address Of" Used };
  shifted: Boolean { Used In Boolean Context };
  first: Boolean { Used In Boolean Context };
  wroteone: Boolean;
  base64EOF: Boolean;
  base64value: Integer;
  done: Boolean;
  c: UCS2;
  prevc: UCS2;
  junk: UCS2 { Used In Boolean Context };
begin
  Initialize_UTF7_Data;
  Result := 0;
  BITbuffer := 0;
  bufferbits := 0;
  shifted := False;
  first := False;
  wroteone := False;
  source := sourceStart;
  target := targetStart;
  c := 0;
  if needtables then
    tabinit;
  repeat
    { read an ASCII character c }
    done := Source >= SourceEnd;
    if (not done) then
    begin
      c := Word(Source^);
      Inc(Source);
    end { If };
    if shifted then
    begin
      { We're done with a base64 string if we hit EOF, it's not a valid }
      { ASCII character, or it's not in the base64 set. }
      { }
      base64value := invbase64[c];
      base64EOF := (done or (c > $7F)) or (base64value < 0);
      if base64EOF then
      begin
        shifted := False;
        { If the character causing us to drop out was SHIFT_IN or }
        { SHIFT_OUT, it may be a special escape for SHIFT_IN. The }
        { test for SHIFT_IN is not necessary, but allows an alternate }
        { form of UTF-7 where SHIFT_IN is escaped by SHIFT_IN. This }
        { only works for some values of SHIFT_IN. }
        { }
        if ((not done) and ((c = Integer('+')) or (c = Integer('-')))) then
        begin
          { get another character c }
          prevc := c;
          Done := Source >= SourceEnd;
          if (not Done) then
          begin
            c := Word(Source^);
            Inc(Source);
            { If no base64 characters were encountered, and the }
            { character terminating the shift sequence was }
            { SHIFT_OUT, then it's a special escape for SHIFT_IN. }
            { }
          end;
          if first and (prevc = Integer('-')) then
          begin
            { write SHIFT_IN unicode }
            if (target >= targetEnd) then
            begin
              Result := 2;
              break;
            end { If };
            Target^ := WideChar('+');
            Inc(Target);
          end
          else
          begin
            if (not wroteone) then
            begin
              Result := 1;
            end { If };
          end { Else };
          ;
        end { If }
        else
        begin
          if (not wroteone) then
          begin
            Result := 1;
          end { If };
        end { Else };
      end { If }
      else
      begin
        { Add another 6 bits of base64 to the bit buffer. }
        WRITE_N_BITS(base64value, 6, BITbuffer,
          bufferbits);
        first := False;
      end { Else };
      { Extract as many full 16 bit characters as possible from the }
      { bit buffer. }
      { }
      while (bufferbits >= 16) and (target < targetEnd) do
      begin
        { write a unicode }
        Target^ := WideChar(READ_N_BITS(16, BITbuffer, bufferbits));
        Inc(Target);
        wroteone := True;
      end { While };
      if (bufferbits >= 16) then
      begin
        if (target >= targetEnd) then
        begin
          Result := 2;
          Break;
        end;
      end { If };
      if (base64EOF) then
      begin
        junk := READ_N_BITS(bufferbits, BITbuffer, bufferbits);
        if (junk <> 0) then
        begin
          Result := 1;
        end { If };
      end { If };
    end { If };
    if (not shifted) and (not done) then
    begin
      if (c = Integer('+')) then
      begin
        shifted := True;
        first := True;
        wroteone := False;
      end { If }
      else
      begin
        { It must be a directly encoded character. }
        if (c > $7F) then
        begin
          Result := 1;
        end { If };
        if (target >= targetEnd) then
        begin
          Result := 2;
          break;
        end { If };
        Target^ := WideChar(c);
        Inc(Target);
      end { Else };
    end { If };
  until (done);
  sourceStart := source;
  targetStart := target;
end; { ConvertUTF7toUCS2 }

  {*****************************************************************************}
  { Thanks to Francisco Leong for providing the Pascal conversion of            }
  {   ConvertUTF7.c (by David B. Goldsmith)                                     }
  {*****************************************************************************}

resourcestring
  SBufferOverflow = 'Buffer overflow';
  SInvalidUTF7 = 'Invalid UTF7';

function WideStringToUTF7(const W: WideString): AnsiString;
var
  SourceStart, SourceEnd: PWideChar;
  TargetStart, TargetEnd: PAnsiChar;
begin
  if W = '' then
    Result := ''
  else
  begin
    SetLength(Result, Length(W) * 7); // Assume worst case
    SourceStart := PWideChar(@W[1]);
    SourceEnd := PWideChar(@W[Length(W)]) + 1;
    TargetStart := PAnsiChar(@Result[1]);
    TargetEnd := PAnsiChar(@Result[Length(Result)]) + 1;
    if ConvertUCS2toUTF7(SourceStart, SourceEnd, TargetStart,
      TargetEnd, True, False) <> 0 then
      raise Exception.Create(SBufferOverflow);
    SetLength(Result, TargetStart - PAnsiChar(@Result[1]));
  end;
end;

function UTF7ToWideString(const S: AnsiString): WideString;
var
  SourceStart, SourceEnd: PAnsiChar;
  TargetStart, TargetEnd: PWideChar;
begin
  if (S = '') then
    Result := ''
  else
  begin
    SetLength(Result, Length(S)); // Assume Worst case
    SourceStart := PAnsiChar(@S[1]);
    SourceEnd := PAnsiChar(@S[Length(S)]) + 1;
    TargetStart := PWideChar(@Result[1]);
    TargetEnd := PWideChar(@Result[Length(Result)]) + 1;
    case ConvertUTF7toUCS2(SourceStart, SourceEnd, TargetStart,
      TargetEnd) of
      1: raise Exception.Create(SInvalidUTF7);
      2: raise Exception.Create(SBufferOverflow);
    end;
    SetLength(Result, TargetStart - PWideChar(@Result[1]));
  end;
end;

function StringToWideStringEx(const S: AnsiString; CodePage: Cardinal): WideString;
var
  InputLength,
  OutputLength: Integer;
begin
  InputLength := Length(S);
  OutputLength := MultiByteToWideChar(CodePage, 0, PAnsiChar(S), InputLength, nil, 0);
  SetLength(Result, OutputLength);
  MultiByteToWideChar(CodePage, 0, PAnsiChar(S), InputLength, PWideChar(Result), OutputLength);
end;

function WideStringToStringEx(const WS: WideString; CodePage: Cardinal): AnsiString;
var
  InputLength,
  OutputLength: Integer;
begin
  InputLength := Length(WS);
  OutputLength := WideCharToMultiByte(CodePage, 0, PWideChar(WS), InputLength, nil, 0, nil, nil);
  SetLength(Result, OutputLength);
  WideCharToMultiByte(CodePage, 0, PWideChar(WS), InputLength, PAnsiChar(Result), OutputLength, nil, nil);
end;

function UCS2ToWideString(const Value: AnsiString): WideString;
begin
  if Length(Value) = 0 then
    Result := ''
  else
    SetString(Result, PWideChar(@Value[1]), Length(Value) div SizeOf(WideChar))
end;

function WideStringToUCS2(const Value: WideString): AnsiString;
begin
  if Length(Value) = 0 then
    Result := ''
  else
    SetString(Result, PAnsiChar(@Value[1]), Length(Value) * SizeOf(WideChar))
end;

{ Windows.pas doesn't declare TranslateCharsetInfo() correctly. }
function TranslateCharsetInfo(lpSrc: PDWORD; var lpCs: TCharsetInfo; dwFlags: DWORD): BOOL; stdcall; external gdi32 name 'TranslateCharsetInfo';

function CharSetToCodePage(ciCharset: UINT): Cardinal;
var
  C: TCharsetInfo;
begin
  Win32Check(TranslateCharsetInfo(PDWORD(ciCharset), C, TCI_SRCCHARSET));
  Result := C.ciACP
end;

function LCIDToCodePage(ALcid: LCID): Cardinal;
var
  Buf: array[0..6] of AnsiChar;
begin
  GetLocaleInfo(ALcid, LOCALE_IDefaultAnsiCodePage, Buf, 6);
  Result := StrToIntDef(Buf, GetACP);
end;

function KeyboardCodePage: Cardinal;
begin
  Result := LCIDToCodePage(GetKeyboardLayout(0) and $FFFF);
end;

function KeyUnicode(C: AnsiChar): WideChar;
begin
  // converts the given character (as it comes with a WM_CHAR message) into its
  // corresponding Unicode character depending on the active keyboard layout
  MultiByteToWideChar(KeyboardCodePage, MB_USEGLYPHCHARS, @C, 1, @Result, 1);
end;

procedure StrSwapByteOrder(Str: PWideChar);
var
  P: PWord;
begin
  P := PWord(Str);
  While (P^ <> 0) do begin
    P^ := MakeWord(HiByte(P^), LoByte(P^));
    Inc(P);
  end;
end;

//---------------------------------------------------------------------------------------------
//                                 Tnt - SysUtils
//---------------------------------------------------------------------------------------------

{$IFNDEF COMPILER_6_UP} // Delphi 5 compatibility
procedure RaiseLastOSError;
begin
  RaiseLastWin32Error;
end;

function WideFormat(const FormatStr: WideString; const Args: array of const): WideString;
begin
  Result := Format{TNT-ALLOW Format}(FormatStr, Args);
end;

function WideCompareStr(const W1, W2: WideString): Integer;
begin
  Result := Tnt_CompareStringW(GetThreadLocale, 0,
      PWideChar(W1), Length(W1), PWideChar(W2), Length(W2)) - 2;
end;

function WideSameStr(const W1, W2: WideString): Boolean;
begin
  Result := WideCompareStr(W1, W2) = 0;
end;

function WideCompareText(const W1, W2: WideString): Integer;
begin
  Result := Tnt_CompareStringW(GetThreadLocale, NORM_IGNORECASE,
    PWideChar(W1), Length(W1), PWideChar(W2), Length(W2)) - 2;
end;

function WideSameText(const W1, W2: WideString): Boolean;
begin
  Result := WideCompareText(W1, W2) = 0;
end;

function Supports(const Instance: TObject; const IID: TGUID): Boolean;
var
  Temp: IUnknown;
begin
  Result := Instance.GetInterface(IID, Temp);
end;
{$ENDIF}

function StrEndW(Str: PWideChar): PWideChar;
begin
  // returns a pointer to the end of a null terminated string
  Result := Str;
  While Result^ <> #0 do
    Inc(Result);
end;

function StrLenW(Str: PWideChar): Cardinal;
begin
  Result := StrEndW(Str) - Str;
end;

function StrLCopyW(Dest, Source: PWideChar; MaxLen: Cardinal): PWideChar;
var
  Count: Cardinal;
begin
  // copies a specified maximum number of characters from Source to Dest
  Result := Dest;
  Count := 0;
  While (Count < MaxLen) and (Source^ <> #0) do begin
    Dest^ := Source^;
    Inc(Source);
    Inc(Dest);
    Inc(Count);
  end;
  Dest^ := #0;
end;

function StrCopyW(Dest, Source: PWideChar): PWideChar;
begin
  Result := StrLCopyW(Dest, Source, MaxInt);
end;

function StrECopyW(Dest, Source: PWideChar): PWideChar;
begin
  Result := StrEndW(StrCopyW(Dest, Source));
end;

function StrPLCopyW{TNT-ALLOW StrPLCopyW}(Dest: PWideChar; const Source: AnsiString; MaxLen: Cardinal): PWideChar;
begin
  Result := StrLCopyW(Dest, PWideChar(WideString(Source)), MaxLen);
end;

function StrPCopyW{TNT-ALLOW StrPCopyW}(Dest: PWideChar; const Source: AnsiString): PWideChar;
begin
  Result := StrPLCopyW{TNT-ALLOW StrPLCopyW}(Dest, Source, MaxInt);
end;

function StrCompW_EX(Str1, Str2: PWideChar; MaxLen: Cardinal; dwCmpFlags: Cardinal): Integer;
var
  Len1, Len2: Integer;
begin
  if MaxLen = Cardinal(MaxInt) then begin
    Len1 := -1;
    Len2 := -1;
  end else begin
    Len1 := Min(StrLenW(Str1), MaxLen);
    Len2 := Min(StrLenW(Str2), MaxLen);
  end;
  Result := Tnt_CompareStringW(GetThreadLocale, dwCmpFlags, Str1, Len1, Str2, Len2) - 2;
end;

function StrLCompW(Str1, Str2: PWideChar; MaxLen: Cardinal): Integer;
begin
  Result := StrCompW_EX(Str1, Str2, MaxLen, 0);
end;

function StrCompW(Str1, Str2: PWideChar): Integer;
begin
  Result := StrLCompW(Str1, Str2, MaxInt);
end;

function StrLICompW(Str1, Str2: PWideChar; MaxLen: Cardinal): Integer;
begin
  Result := StrCompW_EX(Str1, Str2, MaxLen, NORM_IGNORECASE);
end;

function StrICompW(Str1, Str2: PWideChar): Integer;
begin
  Result := StrLICompW(Str1, Str2, MaxInt);
end;

function StrLowerW(Str: PWideChar): PWideChar;
begin
  Result := Str;
  Tnt_CharLowerBuffW(Str, StrLenW(Str))
end;

function StrUpperW(Str: PWideChar): PWideChar;
begin
  Result := Str;
  Tnt_CharUpperBuffW(Str, StrLenW(Str))
end;

function StrPosW(Str, SubStr: PWideChar): PWideChar;
var
  PSave: PWideChar;
  P: PWideChar;
  PSub: PWideChar;
begin
  // returns a pointer to the first occurance of SubStr in Str
  Result := nil;
  if (Str <> nil) and (Str^ <> #0) and (SubStr <> nil) and (SubStr^ <> #0) then begin
    P := Str;
    While P^ <> #0 do begin
      if P^ = SubStr^ then begin
        // investigate possibility here
        PSave := P;
        PSub := SubStr;
        While (P^ = PSub^) do begin
          Inc(P);
          Inc(PSub);
          if (PSub^ = #0) then begin
            Result := PSave;
            exit; // found a match
          end;
          if (P^ = #0) then
            exit; // no match, hit end of string
        end;
        P := PSave;
      end;
      Inc(P);
    end;
  end;
end;

function StrScanW(const Str: PWideChar; Chr: WideChar): PWideChar;
begin
  Result := Str;
  while Result^ <> Chr do
  begin
    if Result^ = #0 then
    begin
      Result := nil;
      Exit;
    end;
    Inc(Result);
  end;
end;

function StrRScanW(const Str: PWideChar; Chr: WideChar): PWideChar;
var
  MostRecentFound: PWideChar;
begin
  if Chr = #0 then
    Result := StrEndW(Str)
  else
  begin
    Result := nil;
    MostRecentFound := Str;
    while True do
    begin
      while MostRecentFound^ <> Chr do
      begin
        if MostRecentFound^ = #0 then
          Exit;
        Inc(MostRecentFound);
      end;
      Result := MostRecentFound;
      Inc(MostRecentFound);
    end;
  end;
end;

function StrLCatW(Dest: PWideChar; const Source: PWideChar; MaxLen: Cardinal): PWideChar;
begin
  Result := Dest;
  StrLCopyW(StrEndW(Dest), Source, MaxLen - StrLenW(Dest));
end;

function StrCatW(Dest: PWideChar; const Source: PWideChar): PWideChar;
begin
  Result := Dest;
  StrCopyW(StrEndW(Dest), Source);
end;

function StrMoveW(Dest: PWideChar; const Source: PWideChar; Count: Cardinal): PWideChar;
begin
  Result := Dest;
  Move(Source^, Dest^, Count * SizeOf(WideChar));
end;

function StrPasW(const Str: PWideChar): WideString;
begin
  Result := Str;
end;

function StrAllocW(Size: Cardinal): PWideChar;
begin
  Size := Size * SizeOf(WideChar);
  Inc(Size, SizeOf(Cardinal));
  GetMem(Result, Size);
  Cardinal(Pointer(Result)^) := Size;
  Inc(Result, SizeOf(Cardinal));
end;

function StrBufSizeW(const Str: PWideChar): Cardinal;
var
  P: PWideChar;
begin
  P := Str;
  Dec(P, SizeOf(Cardinal));
  Result := Cardinal(Pointer(P)^) - SizeOf(Cardinal);
  Result := Result div SizeOf(WideChar);
end;

function StrNewW(const Str: PWideChar): PWideChar;
var
  Size: Cardinal;
begin
  if Str = nil then Result := nil else
  begin
    Size := StrLenW(Str) + 1;
    Result := StrMoveW(StrAllocW(Size), Str, Size);
  end;
end;

procedure StrDisposeW(Str: PWideChar);
begin
  if Str <> nil then
  begin
    Dec(Str, SizeOf(Cardinal));
    FreeMem(Str, Cardinal(Pointer(Str)^));
  end;
end;

function Tnt_WideUpperCase(const S: WideString): WideString;
begin
  { SysUtils.WideUpperCase is broken for Win9x. }
  Result := S;
  if Length(Result) > 0 then
    Tnt_CharUpperBuffW(PWideChar(Result), Length(Result));
end;

function Tnt_WideLowerCase(const S: WideString): WideString;
begin
  { SysUtils.WideLowerCase is broken for Win9x. }
  Result := S;
  if Length(Result) > 0 then
    Tnt_CharLowerBuffW(PWideChar(Result), Length(Result));
end;

function WideLastChar(W: WideString): WideChar;
begin
  if Length(W) = 0 then
    Result := #0
  else
    Result := W[Length(W)];
end;

function WideStringReplace(const S, OldPattern, NewPattern: WideString;
  Flags: TReplaceFlags; WholeWord: Boolean = False): WideString;

  function IsWordSeparator(WC: WideChar): Boolean;
  begin
    Result := (WC = WideChar(#0))
           or IsWideCharSpace(WC)
           or IsWideCharPunct(WC);
  end;

var
  SearchStr, Patt, NewStr: WideString;
  Offset: Integer;
  PrevChar, NextChar: WideChar;
begin
  if rfIgnoreCase in Flags then
  begin
    SearchStr := Tnt_WideUpperCase(S);
    Patt := Tnt_WideUpperCase(OldPattern);
  end else
  begin
    SearchStr := S;
    Patt := OldPattern;
  end;
  NewStr := S;
  Result := '';
  while SearchStr <> '' do
  begin
    Offset := Pos(Patt, SearchStr);
    if Offset = 0 then
    begin
      Result := Result + NewStr;
      Break;
    end; // done

    if (WholeWord) then
    begin
      if (Offset = 1) then
        PrevChar := WideLastChar(Result)
      else
        PrevChar := NewStr[Offset - 1];

      if Offset + Length(OldPattern) <= Length(NewStr) then
        NextChar := NewStr[Offset + Length(OldPattern)]
      else
        NextChar := WideChar(#0);

      if (not IsWordSeparator(PrevChar))
      or (not IsWordSeparator(NextChar)) then
      begin
        Result := Result + Copy(NewStr, 1, Offset + Length(OldPattern) - 1);
        NewStr := Copy(NewStr, Offset + Length(OldPattern), MaxInt);
        SearchStr := Copy(SearchStr, Offset + Length(Patt), MaxInt);
        continue;
      end;
    end;

    Result := Result + Copy(NewStr, 1, Offset - 1) + NewPattern;
    NewStr := Copy(NewStr, Offset + Length(OldPattern), MaxInt);
    if not (rfReplaceAll in Flags) then
    begin
      Result := Result + NewStr;
      Break;
    end;
    SearchStr := Copy(SearchStr, Offset + Length(Patt), MaxInt);
  end;
end;

function TntAdjustLineBreaksLength(const S: WideString; Style: TTntTextLineBreakStyle = tlbsCRLF): Integer;
var
  Source, SourceEnd: PWideChar;
begin
  Source := Pointer(S);
  SourceEnd := Source + Length(S);
  Result := Length(S);
  while Source < SourceEnd do
  begin
    case Source^ of
      #10, WideLineSeparator:
        if Style = tlbsCRLF then
          Inc(Result);
      #13:
        if Style = tlbsCRLF then
          if Source[1] = #10 then
            Inc(Source)
          else
            Inc(Result)
        else
          if Source[1] = #10 then
            Dec(Result);
    end;
    Inc(Source);
  end;
end;

function TntAdjustLineBreaks(const S: WideString; Style: TTntTextLineBreakStyle = tlbsCRLF): WideString;
var
  Source, SourceEnd, Dest: PWideChar;
  DestLen: Integer;
begin
  Source := Pointer(S);
  SourceEnd := Source + Length(S);
  DestLen := TntAdjustLineBreaksLength(S, Style);
  SetString(Result, nil, DestLen);
  Dest := Pointer(Result);
  while Source < SourceEnd do begin
    case Source^ of
      #10, WideLineSeparator:
        begin
          if Style in [tlbsCRLF, tlbsCR] then
          begin
            Dest^ := #13;
            Inc(Dest);
          end;
          if Style in [tlbsCRLF, tlbsLF] then
          begin
            Dest^ := #10;
            Inc(Dest);
          end;
          Inc(Source);
        end;
      #13:
        begin
          if Style in [tlbsCRLF, tlbsCR] then
          begin
            Dest^ := #13;
            Inc(Dest);
          end;
          if Style in [tlbsCRLF, tlbsLF] then
          begin
            Dest^ := #10;
            Inc(Dest);
          end;
          Inc(Source);
          if Source^ = #10 then Inc(Source);
        end;
    else
      Dest^ := Source^;
      Inc(Dest);
      Inc(Source);
    end;
  end;
end;

function WideQuotedStr(const S: WideString; Quote: WideChar = '"'): WideString;
var
  P, Src,
  Dest: PWideChar;
  AddCount: Integer;
begin
  AddCount := 0;
  P := StrScanW(PWideChar(S), Quote);
  while (P <> nil) do
  begin
    Inc(P);
    Inc(AddCount);
    P := StrScanW(P, Quote);
  end;

  if AddCount = 0 then
    Result := Quote + S + Quote
  else
  begin
    SetLength(Result, Length(S) + AddCount + 2);
    Dest := PWideChar(Result);
    Dest^ := Quote;
    Inc(Dest);
    Src := PWideChar(S);
    P := StrScanW(Src, Quote);
    repeat
      Inc(P);
      Move(Src^, Dest^, 2 * (P - Src));
      Inc(Dest, P - Src);
      Dest^ := Quote;
      Inc(Dest);
      Src := P;
      P := StrScanW(Src, Quote);
    until P = nil;
    P := StrEndW(Src);
    Move(Src^, Dest^, 2 * (P - Src));
    Inc(Dest, P - Src);
    Dest^ := Quote;
  end;
end;

function WideExtractQuotedStr(var Src: PWideChar; Quote: WideChar = '"'): WideString;
var
  P, Dest: PWideChar;
  DropCount: Integer;
begin
  Result := '';
  if (Src = nil) or (Src^ <> Quote) then
    Exit;

  Inc(Src);
  DropCount := 1;
  P := Src;
  Src := StrScanW(Src, Quote);

  while Src <> nil do   // count adjacent pairs of quote chars
  begin
    Inc(Src);
    if Src^ <> Quote then
      Break;
    Inc(Src);
    Inc(DropCount);
    Src := StrScanW(Src, Quote);
  end;

  if Src = nil then
    Src := StrEndW(P);
  if (Src - P) <= 1 then
    Exit;

  if DropCount = 1 then
    SetString(Result, P, Src - P - 1)
  else
  begin
    SetLength(Result, Src - P - DropCount);
    Dest := PWideChar(Result);
    Src := StrScanW(P, Quote);
    while Src <> nil do
    begin
      Inc(Src);
      if Src^ <> Quote then
        Break;
      Move(P^, Dest^, 2 * (Src - P));
      Inc(Dest, Src - P);
      Inc(Src);
      P := Src;
      Src := StrScanW(Src, Quote);
    end;
    if Src = nil then
      Src := StrEndW(P);
    Move(P^, Dest^, 2 * (Src - P - 1));
  end;
end;

function WideWrapText(const Line, BreakStr: WideString; const BreakChars: TSysCharSet;
  MaxCol: Integer): WideString;

  function WideCharIn(C: WideChar; SysCharSet: TSysCharSet): Boolean;
  begin
    Result := (C <= High(AnsiChar)) and (AnsiChar(C) in SysCharSet);
  end;

const
  QuoteChars = ['''', '"'];
var
  Col, Pos: Integer;
  LinePos, LineLen: Integer;
  BreakLen, BreakPos: Integer;
  QuoteChar, CurChar: WideChar;
  ExistingBreak: Boolean;
begin
  Col := 1;
  Pos := 1;
  LinePos := 1;
  BreakPos := 0;
  QuoteChar := ' ';
  ExistingBreak := False;
  LineLen := Length(Line);
  BreakLen := Length(BreakStr);
  Result := '';
  while Pos <= LineLen do
  begin
    CurChar := Line[Pos];
    if CurChar = BreakStr[1] then
    begin
      if QuoteChar = ' ' then
      begin
        ExistingBreak := WideSameText(BreakStr, Copy(Line, Pos, BreakLen));
        if ExistingBreak then
        begin
          Inc(Pos, BreakLen-1);
          BreakPos := Pos;
        end;
      end
    end
    else if WideCharIn(CurChar, BreakChars) then
    begin
      if QuoteChar = ' ' then BreakPos := Pos
    end
    else if WideCharIn(CurChar, QuoteChars) then
    begin
      if CurChar = QuoteChar then
        QuoteChar := ' '
      else if QuoteChar = ' ' then
        QuoteChar := CurChar;
    end;
    Inc(Pos);
    Inc(Col);
    if not (WideCharIn(QuoteChar, QuoteChars)) and (ExistingBreak or
      ((Col > MaxCol) and (BreakPos > LinePos))) then
    begin
      Col := Pos - BreakPos;
      Result := Result + Copy(Line, LinePos, BreakPos - LinePos + 1);
      if not (WideCharIn(CurChar, QuoteChars)) then
        while Pos <= LineLen do
        begin
          if WideCharIn(Line[Pos], BreakChars) then
            Inc(Pos)
          else if Copy(Line, Pos, Length(sLineBreak)) = sLineBreak then
            Inc(Pos, Length(sLineBreak))
          else
            break;
        end;
      if not ExistingBreak and (Pos < LineLen) then
        Result := Result + BreakStr;
      Inc(BreakPos);
      LinePos := BreakPos;
      ExistingBreak := False;
    end;
  end;
  Result := Result + Copy(Line, LinePos, MaxInt);
end;

function WideWrapText(const Line: WideString; MaxCol: Integer): WideString;
begin
  Result := WideWrapText(Line, sLineBreak, [' ', '-', #9], MaxCol); { do not localize }
end;

function WideIncludeTrailingBackslash(const S: WideString): WideString;
begin
  Result := S;
  if not WideIsPathDelimiter(Result, Length(Result)) then Result := Result + PathDelim;
end;

function WideExcludeTrailingBackslash(const S: WideString): WideString;
begin
  Result := S;
  if WideIsPathDelimiter(Result, Length(Result)) then
    SetLength(Result, Length(Result)-1);
end;

function WideIsDelimiter(const Delimiters, S: WideString; Index: Integer): Boolean;
begin
  Result := False;
  if (Index <= 0) or (Index > Length(S)) then exit;
  Result := StrScanW(PWideChar(Delimiters), S[Index]) <> nil;
end;

function WideIsPathDelimiter(const S: WideString; Index: Integer): Boolean;
begin
  Result := (Index > 0) and (Index <= Length(S)) and (S[Index] = PathDelim);
end;

function WideLastDelimiter(const Delimiters, S: WideString): Integer;
var
  P: PWideChar;
begin
  Result := Length(S);
  P := PWideChar(Delimiters);
  while Result > 0 do
  begin
    if (S[Result] <> #0) and (StrScanW(P, S[Result]) <> nil) then
      Exit;
    Dec(Result);
  end;
end;

function WideChangeFileExt(const FileName, Extension: WideString): WideString;
var
  I: Integer;
begin
  I := WideLastDelimiter('.\:',Filename);
  if (I = 0) or (FileName[I] <> '.') then I := MaxInt;
  Result := Copy(FileName, 1, I - 1) + Extension;
end;

function WideExtractFilePath(const FileName: WideString): WideString;
var
  I: Integer;
begin
  I := WideLastDelimiter('\:', FileName);
  Result := Copy(FileName, 1, I);
end;

function WideExtractFileDir(const FileName: WideString): WideString;
var
  I: Integer;
begin
  I := WideLastDelimiter(DriveDelim + PathDelim,Filename);
  if (I > 1) and (FileName[I] = PathDelim) and
    (not (FileName[I - 1] in [WideChar(PathDelim), WideChar(DriveDelim)])) then Dec(I);
  Result := Copy(FileName, 1, I);
end;

function WideExtractFileDrive(const FileName: WideString): WideString;
var
  I, J: Integer;
begin
  if (Length(FileName) >= 2) and (FileName[2] = DriveDelim) then
    Result := Copy(FileName, 1, 2)
  else if (Length(FileName) >= 2) and (FileName[1] = PathDelim) and
    (FileName[2] = PathDelim) then
  begin
    J := 0;
    I := 3;
    While (I < Length(FileName)) and (J < 2) do
    begin
      if FileName[I] = PathDelim then Inc(J);
      if J < 2 then Inc(I);
    end;
    if FileName[I] = PathDelim then Dec(I);
    Result := Copy(FileName, 1, I);
  end else Result := '';
end;

function WideExtractFileName(const FileName: WideString): WideString;
var
  I: Integer;
begin
  I := WideLastDelimiter('\:', FileName);
  Result := Copy(FileName, I + 1, MaxInt);
end;

function WideExtractFileExt(const FileName: WideString): WideString;
var
  I: Integer;
begin
  I := WideLastDelimiter('.\:', FileName);
  if (I > 0) and (FileName[I] = '.') then
    Result := Copy(FileName, I, MaxInt) else
    Result := '';
end;

function WideExtractRelativePath(const BaseName, DestName: WideString): WideString;
var
  BasePath, DestPath: WideString;
  BaseLead, DestLead: PWideChar;
  BasePtr, DestPtr: PWideChar;

  function WideExtractFilePathNoDrive(const FileName: WideString): WideString;
  begin
    Result := WideExtractFilePath(FileName);
    Delete(Result, 1, Length(WideExtractFileDrive(FileName)));
  end;

  function Next(var Lead: PWideChar): PWideChar;
  begin
    Result := Lead;
    if Result = nil then Exit;
    Lead := StrScanW(Lead, PathDelim);
    if Lead <> nil then
    begin
      Lead^ := #0;
      Inc(Lead);
    end;
  end;

begin
  if WideSameText(WideExtractFileDrive(BaseName), WideExtractFileDrive(DestName)) then
  begin
    BasePath := WideExtractFilePathNoDrive(BaseName);
    DestPath := WideExtractFilePathNoDrive(DestName);
    BaseLead := Pointer(BasePath);
    BasePtr := Next(BaseLead);
    DestLead := Pointer(DestPath);
    DestPtr := Next(DestLead);
    while (BasePtr <> nil) and (DestPtr <> nil) and WideSameText(BasePtr, DestPtr) do
    begin
      BasePtr := Next(BaseLead);
      DestPtr := Next(DestLead);
    end;
    Result := '';
    while BaseLead <> nil do
    begin
      Result := Result + '..' + PathDelim;             { Do not localize }
      Next(BaseLead);
    end;
    if (DestPtr <> nil) and (DestPtr^ <> #0) then
      Result := Result + DestPtr + PathDelim;
    if DestLead <> nil then
      Result := Result + DestLead;     // destlead already has a trailing backslash
    Result := Result + WideExtractFileName(DestName);
  end
  else
    Result := DestName;
end;

function WideFileCreate(const FileName: WideString): Integer;
begin
  Result := Integer(Tnt_CreateFileW(PWideChar(FileName), GENERIC_READ or GENERIC_WRITE,
    0, nil, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0))
end;

function WideFileOpen(const FileName: WideString; Mode: LongWord): Integer;
const
  AccessMode: array[0..2] of LongWord = (
    GENERIC_READ,
    GENERIC_WRITE,
    GENERIC_READ or GENERIC_WRITE);
  ShareMode: array[0..4] of LongWord = (
    0,
    0,
    FILE_SHARE_READ,
    FILE_SHARE_WRITE,
    FILE_SHARE_READ or FILE_SHARE_WRITE);
begin
  Result := Integer(Tnt_CreateFileW(PWideChar(FileName), AccessMode[Mode and 3],
    ShareMode[(Mode and $F0) shr 4], nil, OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL, 0));
end;

function WideDirectoryExists(const Name: WideString): Boolean;
var
  Code: Cardinal;
begin
  Code := WideFileGetAttr(Name);
  Result := (Integer(Code) <> -1) and (FILE_ATTRIBUTE_DIRECTORY and Code <> 0);
end;

function WideFileExists(const Name: WideString): Boolean;
var
  Code: Cardinal;
begin
  Code := WideFileGetAttr(Name);
  Result := (Integer(Code) <> -1) and ((FILE_ATTRIBUTE_DIRECTORY and Code) = 0);
end;

function WideFileGetAttr(const FileName: WideString): Cardinal;
begin
  Result := Tnt_GetFileAttributesW(PWideChar(FileName))
end;

function WideFileSetAttr(const FileName: WideString; Attr: Integer): Boolean;
begin
  Result := Tnt_SetFileAttributesW(PWideChar(FileName), Attr)
end;

function WideForceDirectories(Dir: WideString): Boolean;
begin
  Result := True;
  if Length(Dir) = 0 then
    raise Exception.Create(SCannotCreateDir);
  Dir := WideExcludeTrailingBackslash(Dir);
  if (Length(Dir) < 3) or WideDirectoryExists(Dir)
    or (WideExtractFilePath(Dir) = Dir) then Exit; // avoid 'xyz:\' problem.
  Result := WideForceDirectories(WideExtractFilePath(Dir));
  if Result then
    Result := Tnt_CreateDirectoryW(PWideChar(Dir), nil)
end;

function WideFileSearch(const Name, DirList: WideString): WideString;
var
  I, P, L: Integer;
  C: WideChar;
begin
  Result := Name;
  P := 1;
  L := Length(DirList);
  while True do
  begin
    if WideFileExists(Result) then Exit;
    while (P <= L) and (DirList[P] = PathSep) do Inc(P);
    if P > L then Break;
    I := P;
    while (P <= L) and (DirList[P] <> PathSep) do
      Inc(P);
    Result := Copy(DirList, I, P - I);
    C := WideLastChar(Result);
    if (C <> DriveDelim) and (C <> PathDelim) then
      Result := Result + PathDelim;
    Result := Result + Name;
  end;
  Result := '';
end;

function WideRenameFile(const OldName, NewName: WideString): Boolean;
begin
  Result := Tnt_MoveFileW(PWideChar(OldName), PWideChar(NewName))
end;

function WideDeleteFile(const FileName: WideString): Boolean;
begin
  Result := Tnt_DeleteFileW(PWideChar(FileName))
end;

function WideCopyFile(FromFile, ToFile: WideString; FailIfExists: Boolean): Boolean;
begin
  Result := Tnt_CopyFileW(PWideChar(FromFile), PWideChar(ToFile), FailIfExists)
end;

function _WideFindMatchingFile(var F: TSearchRecW): Integer;
var
  LocalFileTime: TFileTime;
begin
  with F do
  begin
    while FindData.dwFileAttributes and ExcludeAttr <> 0 do
      if not Tnt_FindNextFileW(FindHandle, FindData) then
      begin
        Result := GetLastError;
        Exit;
      end;
    FileTimeToLocalFileTime(FindData.ftLastWriteTime, LocalFileTime);
    FileTimeToDosDateTime(LocalFileTime, LongRec(Time).Hi, LongRec(Time).Lo);
    Size := FindData.nFileSizeLow;
    Attr := FindData.dwFileAttributes;
    Name := FindData.cFileName;
  end;
  Result := 0;
end;

function WideFindFirst(const Path: WideString; Attr: Integer; var F: TSearchRecW): Integer;
const
  faSpecial = faHidden or faSysFile or faVolumeID or faDirectory;
begin
  F.ExcludeAttr := not Attr and faSpecial;
  F.FindHandle := Tnt_FindFirstFileW(PWideChar(Path), F.FindData);
  if F.FindHandle <> INVALID_HANDLE_VALUE then
  begin
    Result := _WideFindMatchingFile(F);
    if Result <> 0 then WideFindClose(F);
  end else
    Result := GetLastError;
end;

function WideFindNext(var F: TSearchRecW): Integer;
begin
  if Tnt_FindNextFileW(F.FindHandle, F.FindData) then
    Result := _WideFindMatchingFile(F) else
    Result := GetLastError;
end;

procedure WideFindClose(var F: TSearchRecW);
begin
  if F.FindHandle <> INVALID_HANDLE_VALUE then
  begin
    Windows.FindClose(F.FindHandle);
    F.FindHandle := INVALID_HANDLE_VALUE;
  end;
end;

function _ValidDateTimeStrEx(Str: WideString; Flags: Integer): Boolean;
var
  TheDateTime: Double;
begin
  Result := Succeeded(VarDateFromStr(Str, GetThreadLocale, Flags, TheDateTime));
end;

function ValidDateTimeStr(Str: WideString): Boolean;
begin
  Result := _ValidDateTimeStrEx(Str, 0);
end;

function ValidDateStr(Str: WideString): Boolean;
begin
  Result := _ValidDateTimeStrEx(Str, VAR_DATEVALUEONLY);
end;

function ValidTimeStr(Str: WideString): Boolean;
begin
  Result := _ValidDateTimeStrEx(Str, VAR_TIMEVALUEONLY);
end;

function IntStrToDateTime(Str: WideString; Flags: Integer; ErrorFormatStr: WideString): TDateTime;
var
  TheDateTime: Double;
begin
  try
    OleCheck(VarDateFromStr(Str, GetThreadLocale, Flags, TheDateTime));
    Result := TheDateTime;
  except
    on E: Exception do begin
      E.Message := E.Message + CRLF + WideFormat(ErrorFormatStr, [Str]);
      raise EConvertError.Create(E.Message);
    end;
  end;
end;

function TntStrToDateTime(Str: WideString): TDateTime;
begin
  Result := IntStrToDateTime(Str, 0, SInvalidDateTime);
end;

function TntStrToDate(Str: WideString): TDateTime;
begin
  Result := IntStrToDateTime(Str, VAR_DATEVALUEONLY, SInvalidDate);
end;

function TntStrToTime(Str: WideString): TDateTime;
begin
  Result := IntStrToDateTime(Str, VAR_TIMEVALUEONLY, SInvalidTime);
end;

function WideGetLocaleStr(LocaleID: LCID; LocaleType: Integer; Default: WideString): WideString;
begin
  if (not Win32PlatformIsUnicode) then
    Result := GetLocaleStr{TNT-ALLOW GetLocaleStr}(LocaleID, LocaleType, Default)
  else begin
    SetLength(Result, GetLocaleInfoW(LocaleID, LocaleType, nil, 0) + 1);
    if Length(Result) > 0 then begin
      GetLocaleInfoW(LocaleID, LocaleType, PWideChar(Result), Length(Result));
      Result := PWideChar(Result);
    end;
  end;
end;

function WinCheckH(RetVal: Cardinal): Cardinal;
begin
  if RetVal = 0 then RaiseLastOSError;
  Result := RetVal;
end;

function WinCheckFileH(RetVal: Cardinal): Cardinal;
begin
  if RetVal = INVALID_HANDLE_VALUE then RaiseLastOSError;
  Result := RetVal;
end;

function WinCheckP(RetVal: Pointer): Pointer;
begin
  if RetVal = nil then RaiseLastOSError;
  Result := RetVal;
end;

function WideGetModuleFileName(Instance: HModule): WideString;
begin
  SetLength(Result, MAX_PATH);
  WinCheckH(Tnt_GetModuleFileNameW(Instance, PWideChar(Result), Length(Result)));
  Result := PWideChar(Result)
end;

function _WideCharType(WC: WideChar; dwInfoType: Cardinal): Word;
begin
  Win32Check(Tnt_GetStringTypeExW(GetThreadLocale, dwInfoType, PWideChar(@WC), 1, Result))
end;

function IsWideCharUpper(WC: WideChar): Boolean;
begin
  Result := (_WideCharType(WC, CT_CTYPE1) and C1_UPPER) <> 0;
end;

function IsWideCharLower(WC: WideChar): Boolean;
begin
  Result := (_WideCharType(WC, CT_CTYPE1) and C1_LOWER) <> 0;
end;

function IsWideCharDigit(WC: WideChar): Boolean;
begin
  Result := (_WideCharType(WC, CT_CTYPE1) and C1_DIGIT) <> 0;
end;

function IsWideCharSpace(WC: WideChar): Boolean;
begin
  Result := (_WideCharType(WC, CT_CTYPE1) and C1_SPACE) <> 0;
end;

function IsWideCharPunct(WC: WideChar): Boolean;
begin
  Result := (_WideCharType(WC, CT_CTYPE1) and C1_PUNCT) <> 0;
end;

function IsWideCharCntrl(WC: WideChar): Boolean;
begin
  Result := (_WideCharType(WC, CT_CTYPE1) and C1_CNTRL) <> 0;
end;

function IsWideCharBlank(WC: WideChar): Boolean;
begin
  Result := (_WideCharType(WC, CT_CTYPE1) and C1_BLANK) <> 0;
end;

function IsWideCharXDigit(WC: WideChar): Boolean;
begin
  Result := (_WideCharType(WC, CT_CTYPE1) and C1_XDIGIT) <> 0;
end;

function IsWideCharAlpha(WC: WideChar): Boolean;
begin
  Result := (_WideCharType(WC, CT_CTYPE1) and C1_ALPHA) <> 0;
end;

function IsWideCharAlphaNumeric(WC: WideChar): Boolean;
begin
  Result := (_WideCharType(WC, CT_CTYPE1) and (C1_ALPHA + C1_DIGIT)) <> 0;
end;

function WideTextPos(const SubStr, S: WideString): Integer;
begin
  Result := Pos(Tnt_WideUpperCase(SubStr), Tnt_WideUpperCase(S));
end;

function FindDoubleTerminator(P: PWideChar): PWideChar;
begin
  Result := P;
  while True do begin
    Result := StrScanW(Result, #0);
    Inc(Result);
    if Result^ = #0 then begin
      Dec(Result);
      break;
    end;
  end;
end;

function ExtractStringArrayStr(P: PWideChar): WideString;
var
  PEnd: PWideChar;
begin
  PEnd := FindDoubleTerminator(P);
  Inc(PEnd, 2); // move past #0#0
  SetString(Result, P, PEnd - P);
end;

function ExtractStringFromStringArray(var P: PWideChar; Separator: WideChar = #0): WideString;
var
  Start: PWideChar;
begin
  Start := P;
  P := StrScanW(Start, Separator);
  if P = nil then begin
    Result := Start;
    P := StrEndW(Start);
  end else begin
    SetString(Result, Start, P - Start);
    Inc(P);
  end;
end;

function ExtractStringsFromStringArray(P: PWideChar; Separator: WideChar = #0): TWideStringDynArray;
const
  GROW_COUNT = 256;
var
  Count: Integer;
  Item: WideString;
begin
  Count := 0;
  SetLength(Result, GROW_COUNT);
  Item := ExtractStringFromStringArray(P, Separator);
  While Item <> '' do begin
    if Count > High(Result) then
      SetLength(Result, Length(Result) + GROW_COUNT);
    Result[Count] := Item;
    Inc(Count);
    Item := ExtractStringFromStringArray(P, Separator);
  end;
  SetLength(Result, Count);
end;

//---------------------------------------------------------------------------------------------
//                                 Tnt - Variants
//---------------------------------------------------------------------------------------------

{$IFNDEF COMPILER_6_UP} // Delphi 5 compatibility
function VarToWideStr(const V: Variant): WideString;
begin
  Result := VarToWideStrDef(V, '');
end;

function VarToWideStrDef(const V: Variant; const ADefault: WideString): WideString;
begin
  if not VarIsNull(V) then
    Result := V
  else
    Result := ADefault;
end;
{$ENDIF}

initialization
  {$IFDEF COMPILER_7_UP}
  if (Win32Platform = VER_PLATFORM_WIN32_NT) and (Win32MajorVersion >= 5) then
    DefaultUserCodePage := CP_THREAD_ACP // Win 2K/XP/...
  else
    DefaultUserCodePage := LCIDToCodePage(GetThreadLocale); // Win NT4/95/98/ME
  {$ELSE}
  DefaultUserCodePage := CP_ACP{TNT-ALLOW CP_ACP};
  {$ENDIF}

  Win32PlatformIsUnicode := (Win32Platform = VER_PLATFORM_WIN32_NT);
  Win32PlatformIsXP := ((Win32MajorVersion = 5) and (Win32MinorVersion >= 1))
                    or  (Win32MajorVersion > 5);

end.
