/***************************************************************************
                          swim.cpp  -  description
                             -------------------
    begin                : Fri Apr  4 14:44:54 IDT 2003
    copyright           : (C) 2003 by GNU/Linux Kinneret
    programmers     :  Nir Misgav (Nirro) & Reut Harari
        email            :   Nirro@yahoo.com

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <kmainwindow.h>
#include <klocale.h>
#include "index.h"
#include <qhbox.h>
#include <qimage.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <kparts/componentfactory.h>
#include <kurl.h>
#include <qwidgetstack.h>
#include <qsizepolicy.h>
#include <qsplitter.h>
#include <qvaluestack.h>
#include <ktoolbar.h>
#include <kiconloader.h>
#include <kprocess.h>
#include <kmimetype.h>
#include <kparts/browserextension.h>
#include <khtml_part.h>
#include <khtmlview.h>
//#include <iostream.h>
#include <krun.h>
#include <qfile.h>
#include <kmessagebox.h>
#include <qevent.h>

#define TOOLBAR_ID_BACK 1
#define TOOLBAR_ID_HOME 2
#define TOOLBAR_ID_ABOUT 3
#define TOOLBAR_ID_ZOOMIN 4
#define TOOLBAR_ID_ZOOMOUT 5
#define TOOLBAR_ID_FORW 7
#define TOOLBAR_ID_PRINT 8
#define HTML 1
#define PART 2

class MainWindow : public KMainWindow
{
  Q_OBJECT
public:
  MainWindow ( const char * name, QString spage);
  ~MainWindow();
  void putImage(QString imagefile);
  void openURL(KURL url,bool push=true,bool forw=false);
  void firstload();
  virtual void show();
  virtual void keyPressEvent (QKeyEvent *e);

public slots:

void home();
void about();
void fzoomin();
void fzoomout();
void openURLRequest(const KURL &url, const KParts::URLArgs & );
void gotoPreviousPage();
void gotoForwardPage();
void printpage();
void backButtonOff();

private:
  int visible;
  QWidgetStack* stack;
  cmenu* menu;
  QHBox* hbox;
  QLabel* label;
  QSplitter* splitter;
  QSplitter* splitter2;
  KToolBar *toolbar;
  QValueStack <QString> history;
  QValueStack <QString> future;
  QString menufile;
  KParts::ReadOnlyPart* part;
  KHTMLPart *html;
  KHTMLView *htmlview;
  QString currentimage,currentPage,cmdStartpage;
  QString aboutline;
  QString lang;
};

