/***************************************************************************
                          l2swim.cpp  -  description
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

#include "l2swim.h"
#include <iostream>

using namespace std;

// Showing the main widget.
MainWindow::MainWindow ( const char* name, const QString spage, cmenu* mn) : KMainWindow ( 0L, name )
{
  aboutline=i18n("<b><big><big>Learn To Swim (l2swim)</b></big></big><br><br>An interactive information center.<br>Version: %1<br>Date: %2<br>Programmed by : Nir Misgav<br>Email: %3<br>License: GPL<br>All rights reserved to <i><b>GNU/Linux Kinneret.</i></b>")
      .arg("0.7.3-1").arg("15/5/04").arg("nirro@linux-kinneret.org");
	cmdStartpage=spage;
	menu=mn;
//	lang=locale.language().left(2);

//  cout<<"menu initialized"<<endl;
  setCaption(i18n("Learn to swim"));
  hbox = new QHBox(this);

  label=new QLabel(hbox);

  stack=new QWidgetStack(hbox);
  splitter= new QSplitter(stack);
  stack->addWidget(splitter,PART);
  part=NULL;
  splitter2= new QSplitter(stack);
  stack->addWidget(splitter2,HTML);
  stack->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding, TRUE );

  html=new KHTMLPart( splitter2 );
  htmlview=html->view();
  toolbar=new KToolBar(this);
  toolbar->setIconText(KToolBar::IconTextBottom);
  toolbar->insertButton(BarIcon("forward"), TOOLBAR_ID_BACK,
                          SIGNAL(clicked(int)),this,SLOT(gotoPreviousPage()),
                          FALSE, i18n("Backward"));
  toolbar->insertButton(BarIcon("back"), TOOLBAR_ID_FORW,
                          SIGNAL(clicked(int)),this,SLOT(gotoForwardPage()),
                          FALSE, i18n("Forward"));
  toolbar->insertButton(BarIcon("gohome"), TOOLBAR_ID_HOME,
                          SIGNAL(clicked(int)),this,SLOT(home()),FALSE,
                          i18n("Homepage"));
  toolbar->insertLineSeparator();
  toolbar->insertButton(BarIcon("viewmag+"), TOOLBAR_ID_ZOOMIN,
                          SIGNAL(clicked(int)),this,SLOT(fzoomin()),TRUE,
                          i18n("Zoom-in"));

  toolbar->insertButton(BarIcon("viewmag-"), TOOLBAR_ID_ZOOMOUT,
                          SIGNAL(clicked(int)),this,SLOT(fzoomout()),FALSE,
                          i18n("Zoom-out"));
  toolbar->insertLineSeparator();
  toolbar->insertButton(BarIcon("frameprint"), TOOLBAR_ID_PRINT,
                          SIGNAL(clicked(int)),this,SLOT(printpage()),TRUE,
                          i18n("Print page"));
  toolbar->insertButton(BarIcon("about"), TOOLBAR_ID_ABOUT,
                          SIGNAL(clicked(int)),this,SLOT(about()),TRUE,
                          i18n("About l2swim"));
	toolbar->alignItemRight(TOOLBAR_ID_ABOUT);
	addToolBar(toolbar);
  connect( html->browserExtension(),
        SIGNAL( openURLRequest( const KURL &, const KParts::URLArgs & ) ),
        this, SLOT( openURLRequest(const KURL &, const KParts::URLArgs & ) ) );

  setCentralWidget( hbox );
  resize(maximumSize());
  
	setAutoSaveSettings("MainWindow",true);
	toolbar->setIconText(KToolBar::IconTextBottom);

	openURL(KURL(menu->getFirstPage()),true);
}

void MainWindow::home()
{
	future.clear();
	toolbar->setItemEnabled(TOOLBAR_ID_FORW,FALSE);
	openURL(KURL(menu->getFirstPage()));
}

void MainWindow::fzoomin()
{
  int zoom=html->zoomFactor();
  if (zoom<200)
  {
    toolbar->setItemEnabled(TOOLBAR_ID_ZOOMOUT,TRUE);
    zoom+=20;
    html->setZoomFactor(zoom);
  }
  if (zoom>=200) toolbar->setItemEnabled(TOOLBAR_ID_ZOOMIN,FALSE);
}

void MainWindow::fzoomout()
{
  int zoom=html->zoomFactor();
  if (zoom>100)
  {
    toolbar->setItemEnabled(TOOLBAR_ID_ZOOMIN,TRUE);
    zoom-=20;
    html->setZoomFactor(zoom);
  }
  if (zoom<=100) toolbar->setItemEnabled(TOOLBAR_ID_ZOOMOUT,FALSE);
}

void MainWindow::openURL(KURL url, bool backward,bool forward)
{
	QString link,type;
	//check if it is the first page
	if(url.url().compare(menu->getFirstPage())==0)
	toolbar->setItemEnabled(TOOLBAR_ID_HOME,false);
	else toolbar->setItemEnabled(TOOLBAR_ID_HOME,true);
  
	divideURL(url.url(),&type,&link);
  
	// a menu
	if (type.compare("menu")==0)
	{
		if (!backward)
		{
			history.push(currentPage);
			toolbar->setItemEnabled(TOOLBAR_ID_BACK,true);
		} 
		if ((!forward)&&(!backward))
		{
			future.clear();
			toolbar->setItemEnabled(TOOLBAR_ID_FORW,false);
		}
		QString page,type,imagefile;
		if (!menu->getLink(link,"menu",&imagefile,&page))
		{
			cout<<"Error - page not found"<<endl;
			return;
		}
		putImage(imagefile);
		html->begin();
		html->write(page);
		html->end();
		QString title=html->htmlDocument().title().string();
		if ((title.isNull())||(title.isEmpty())) setCaption(i18n("Learn to swim"));
		else setCaption(i18n("Learn to swim - %1").arg(title));
		visible=HTML;
		stack->raiseWidget(visible);
		currentPage=url.url();
		return;
	}
	//executable from menu
	if (type.compare("exec")==0 )
	{
		KProcess *proc=new KProcess;
		*proc << link;
		proc->start(KProcess::DontCare);
		delete proc;
		return;
	}
	// internal document (play from menu)
	if (type.compare("play")==0)
	{
		QString imagefile;
		if (!menu->getLink(link,"play",&imagefile))
		{
			cout<<"Error - page not found"<<endl;
			return;
		}
		putImage(imagefile);
		KURL url2;
		url2.setPath(menu->getDocsPath());
		url2.setFileName(link);
		url2.setProtocol("file");
		url=url2;
	}
	QString mimetype = KMimeType::findByURL(url)->name();
	// executable or external link
	if (mimetype.compare("application/octet-stream")==0) new KRun(url,0,false,true);
	// internal html
	else 
	{
		if (!backward)
		{
			history.push(currentPage);
			toolbar->setItemEnabled(TOOLBAR_ID_BACK,true);
		} 
		if ((!forward)&&(!backward))
		{
			future.clear();
			toolbar->setItemEnabled(TOOLBAR_ID_FORW,false);
		}
		if(mimetype.compare("text/html")==0)
		{
			html->openURL(url);
			visible=HTML;
			QString title=html->htmlDocument().title().string();
			if ((title.isNull())||(title.isEmpty())) setCaption(i18n("Learn to swim"));
			else setCaption(i18n("Learn to swim - %1").arg(title));
			stack->raiseWidget(visible);
		}
		// other part internal
		else
		{
			if (part)delete part;
			part = KParts::ComponentFactory::createPartInstanceFromQuery<KParts::ReadOnlyPart> ( mimetype, QString::null, splitter, 0L, this, 0L );
   	 		if ( part )
			{
				part->openURL(url);
				part->widget()->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding, TRUE );
				visible=PART;
				stack->raiseWidget(visible);
			}
		}
		currentPage=url.url();
	}
}

void MainWindow::openURLRequest( const KURL &url, const KParts::URLArgs & )
{
	openURL(url);
}

// button back pressed
void MainWindow::gotoPreviousPage()
{
  future.push(currentPage);
//  cout<<currentPage<<endl;
  toolbar->setItemEnabled(TOOLBAR_ID_FORW,true);
  openURL(KURL(history.pop()),true);
  if (history.isEmpty()) toolbar->setItemEnabled(TOOLBAR_ID_BACK,false);
}  

void MainWindow::gotoForwardPage()
{
  QString fu=future.pop();
//  cout<<"Forward="<<fu<<endl;
  openURL(KURL(fu),false,true);
  if (future.isEmpty()) toolbar->setItemEnabled(TOOLBAR_ID_FORW,false);
}

void MainWindow::about()
{
  KMessageBox::about(this,aboutline,NULL,2);
}
  
void MainWindow::putImage(QString imagefile)
{
  if ((!imagefile.isNull())&&(imagefile.compare(currentimage)!=0))
  {
    currentimage=imagefile;
    QPixmap image(imagefile);
    if (!image.isNull()) label->setPixmap(image);
    else label->setText(i18n("ERROR - Image %1 not found").arg(currentimage));
  }
}

void MainWindow::printpage()
{
  htmlview->print();
}  
  
//desctuctor
MainWindow::~MainWindow()
{
//  delete menu;
  if (part) delete part;
}

// Handle the BackspaceKey for Go-Back.
void MainWindow::keyPressEvent (QKeyEvent *e)
{
  if (e->key()==0x1003)  //BackSpace Key
  {
    if (!e->isAutoRepeat())
    {
      if(!history.isEmpty())
      {
        toolbar->getButton(TOOLBAR_ID_BACK)->on(true);
        QTimer::singleShot(100, this, SLOT(backButtonOff()));
      }
      else KApplication::beep();
    }
  }
  else e->ignore();
}

void MainWindow::backButtonOff()
{
  toolbar->getButton(TOOLBAR_ID_BACK)->on(false);
  gotoPreviousPage();
}

bool divideURL(QString url, QString *type, QString *name)
{
	int div=url.find("://",0,false);
	if (div<0) return false;
	*type=url.left(div);
	*name=url.right(url.length()-div-3);
	return true;
}
