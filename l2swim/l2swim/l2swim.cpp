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

#include "l2swim.h"

// Showing the main widget.
MainWindow::MainWindow ( const char* name, const QString spage) : KMainWindow ( 0L, name )
{
  aboutline=i18n("<b><big><big>Learn To Swim (l2swim)</b></big></big><br><br>An interactive information center.<br>Version: %1<br>Date: %2<br>Programmed by : Nir Misgav<br>Email: %3<br>License: GPL<br>All rights reserved to <i><b>GNU/Linux Kinneret.</i></b>")
      .arg("0.6rc2").arg("14/9/03").arg("nirro@linux-kinneret.org");
  startpage=spage;
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
}

void MainWindow::firstload()
{
  KLocale locale("");
  lang=locale.language().left(2);
  bool langexist=true;
  menufile=QString("/opt/kinneret/l2swim/etc/swim_menu_"+lang+".txt");
  QString lastmenufile=menufile;
  if (!QFile(menufile).exists())
  {
    langexist=false;
    menufile=QString("/opt/kinneret/l2swim/etc/swim_menu.txt");
  }
  menu=new cmenu();
  QString orig_startpage=startpage;
  bool startpageExist=menu->initialize(menufile,&startpage);
  if (!menu->getLanguage().isNull()) lang=menu->getLanguage();
  if (!startpageExist) openURL(KURL(menu->getMenuName()),false);
  else openURL(KURL(QString(startpage)),false);
  if (!langexist) KMessageBox::information(this,i18n("Your language menu-file: %1 does not exist, using default language instead").arg(lastmenufile)
    ,i18n("Sorry"),"LangMenuFile");
  if((!startpage.isEmpty())&&(!startpageExist))
      KMessageBox::error(this,i18n("Page %1 does not exist.").arg(orig_startpage));
}

void MainWindow::show()
{
  KMainWindow::show();
  firstload();
}

void MainWindow::home()
{
  openURL(KURL(menu->getMenuName()),true);
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

void MainWindow::openURL(KURL url,bool push,bool forw)
{
  QString link;
  // this is not forward nor backward
  if (forw==false)
  {
    future.clear();
    toolbar->setItemEnabled(TOOLBAR_ID_FORW,false);
  }
  if(url.url().compare(menu->getMenuName())==0)
      toolbar->setItemEnabled(TOOLBAR_ID_HOME,false);
      else toolbar->setItemEnabled(TOOLBAR_ID_HOME,true);
  if ((url.url().left(7).compare("swim://")==0)||
      (url.url().compare("swit://startpage")==0))
  {
    //internal link
    link=url.url().right(url.url().length()-7);
    QString page,type,imagefile;
    menu->getLink(url.url(),&page,&type,&imagefile);
    putImage(imagefile);
    if (type.compare("name")==0)
    {
      if (push)
      {
        history.push(currentPage);
        toolbar->setItemEnabled(TOOLBAR_ID_BACK,true);
      }
      if ((lang=="he")||(lang=="ar"))
      page=QString("<html><head><meta http-equiv=""Content-Type"" content=""text/html; charset=utf-8""></head><body dir=""rtl"">")+page+"</body></html>";
      html->begin();
      html->write(page);
      html->end();
      visible=HTML;
      stack->raiseWidget(visible);
      currentPage=url.url();
      return;
    }
    else if (type.compare("exec")==0 )
    {
      KProcess *proc=new KProcess;
      *proc << link;
      proc->start(KProcess::DontCare);
      delete proc;
      return;
    }
    else if (type.compare("play")!=0)
    {
    // external URL
      new KRun(KURL(type+"://"+link),0);
      return;
    }

    // Internal URL
    KURL url2;
    url2.setPath(menu->getDocsPath());
    url2.setFileName(link);
    url2.setProtocol("file");
    url=url2;
  }
  QString mimetype = KMimeType::findByURL(url)->name();
  // external link
  if (mimetype.compare("application/octet-stream")==0) new KRun(url,0);
  else if(mimetype.compare("text/html")==0)
  {
    if(push)
    {
      history.push(currentPage);
      toolbar->setItemEnabled(TOOLBAR_ID_BACK,true);
    }
    html->openURL( url.url() );
    currentPage=url.url();
    visible=HTML;
    stack->raiseWidget(visible);
  }
  else
  {
    // other part
    if (part)delete part;
    part = KParts::ComponentFactory::createPartInstanceFromQuery<KParts::ReadOnlyPart>
      ( mimetype, QString::null, splitter, 0L, this, 0L );
    if ( part )
    {
      if(push)
      {
        history.push(currentPage);
        toolbar->setItemEnabled(TOOLBAR_ID_BACK,true);
      }
      part->openURL(url);
      part->widget()->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding, TRUE );
      currentPage=url.url();
      visible=PART;
      stack->raiseWidget(visible);
    }
  }
}  

void MainWindow::openURLRequest( const KURL &url, const KParts::URLArgs & )
{
  if (url.url().compare("swit://goback")==0) gotoPreviousPage();
  else if (url.url().compare("swit://exit")==0) close();
  else openURL(url);
}

// button back pressed
void MainWindow::gotoPreviousPage()
{
  future.push(currentPage);
//  cout<<currentPage<<endl;
  toolbar->setItemEnabled(TOOLBAR_ID_FORW,true);
  openURL(KURL(history.pop()),false,true);
  if (history.isEmpty()) toolbar->setItemEnabled(TOOLBAR_ID_BACK,false);
}  

void MainWindow::gotoForwardPage()
{
  QString fu=future.pop();
//  cout<<"Forward="<<fu<<endl;
  openURL(KURL(fu),true,true);
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
  delete menu;
  if (part) delete part;
}
