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

#include "index.h"
#include <qdom.h>
#include <iostream>

using namespace std;

cmenu::cmenu(QString filename,bool *success)
{
	cout<<"starting"<<endl;
	menusDoc=new QDomDocument("swim_menu");
	QFile f( filename );
	if ( !f.open( IO_ReadOnly ) ) 
	{
		*success=false;
		cout<<filename<<" not found"<<endl;
		return;
	}
	QString errorMsg;
	int errorLine, errorColumn;
	if ( !menusDoc->setContent( &f, false, &errorMsg,&errorLine,&errorColumn ) ) 
	{
		f.close();
		cout<<"Error in parsing menu"<<endl<<errorMsg<<", Line: "<<errorLine<<" ,Column: "<<errorColumn<<endl;
		*success=false;
		return;
	}
	f.close();
	*success=true;
	//root element
	QDomElement docElem = menusDoc->documentElement();
	
	cout<<docElem.tagName()<<endl;
	
	// assigning global configuration
	QDomNode globalNode = docElem.firstChild();
	cout<<globalNode.nodeName()<<endl;
	if((!globalNode.isNull())&&(globalNode.nodeName().compare("global_config")==0))
	{
		QDomElement globalElement=globalNode.toElement();
		
		defaultImage=globalElement.attribute("defaultimage");
		defaultDir=globalElement.attribute("defaultdir","ltr");
		docsPath=globalElement.attribute("docspath","");
		imagePath=globalElement.attribute("imagepath","");
		firstPage=globalElement.attribute("firstpage");
		cout<<defaultImage<<endl<<defaultDir<<endl<<docsPath<<endl<<imagePath<<endl<<firstPage<<endl;
		if (docsPath[docsPath.length()-1]!='/') docsPath.append('/');
		if (imagePath[imagePath.length()-1]!='/') imagePath.append('/');
	}
	
	// expanding the tree (add the plays to the menus level, because of the images problem)
	QDomNode menuNode = docElem.firstChild();
	while( !menuNode.isNull() ) 
	{
		if((menuNode.nodeName().compare("menu")==0)&&(menuNode.isElement()))
		{
			// if no firstpage defined, take the first menu you see.
			cout<<menuNode.nodeName()<<endl;
			if (firstPage.isNull()) firstPage=menuNode.toElement().attribute("name");
			
			QDomNode linkNode=menuNode.firstChild();
			QDomElement linkElem;
			while(!linkNode.isNull())
			{
				linkElem=linkNode.toElement();
				if ((!linkElem.isNull()) && (linkElem.tagName().compare("link")) && (linkElem.attribute("type","menu").compare("play")==0))
				{
					QDomElement append = menusDoc->createElement("play");
					if (!linkElem.attribute("image").isNull()) append.setAttribute("image", linkElem.attribute("image"));
					// add this to the menus level.
					docElem.appendChild( append );
				}
				linkNode = linkNode.nextSibling();	
			}
		}
		menuNode = menuNode.nextSibling();
	}
}

// initialize the menu
/*bool cmenu::initialize(QString filename, QString cmdStartpage, QString *startpage)
{         
// cout<<"starting menu"<<endl;
  QString name;
  QString linkname;
  QString linktext;
  QString page;
  QString title;
  QString description;
  QString type;
  QString key;
  QString image;
  lineType lType;
  bool startpageExist=false;
//  QString orig_startpage=*startpage;
  // Read from file and initialize
  QIODevice* fp = new QFile(filename);
  fp->open(IO_ReadOnly);
  QTextStream* filereader = new QTextStream(fp);
  filereader->setEncoding(QTextStream::UnicodeUTF8);

  // Reading initial settings docspath and image and language!!
  defaultdir="ltr";
  while(((lType=getline(filereader,&key,&name))==tKey)&&(key.compare("menu")!=0))
  {
    if (key.compare("docspath")==0) docspath=name;
    else if (key.compare("defaultimage")==0) defaultimage=name;
    else if (key.compare("imagepath")==0) imagepath=name;
    else if (key.compare("menulanguage")==0) menulanguage=name;
    else if ((key.compare("defaultdir")==0)
      &&((name.compare("rtl")==0)||(name.compare("ltr")==0))) defaultdir=name;
  }
  if (docspath[docspath.length()-1]!='/') docspath.append('/');
  if (imagepath[imagepath.length()-1]!='/') imagepath.append('/');

  if ((lType!=tEof)&&(lType!=tError))
  {
    // Reading mainmenu
    name=QString("swim://")+name;
    if (key.compare("menu")==0) menuname=name;
    addSection(new csection(menuname,"name",defaultimage));
    // Read menu name
    while ((lType!=tEof)&&(lType!=tError))
    {
      lType=getline(filereader,&key,&title);
      // Defining html head.
      page="<!DOCTYPE HTML PUBLIC ""-//W3C//DTD HTML 4.01 Transitional//EN"">";
      page+="<html><head><meta http-equiv=""Content-Type"" content=""text/html; charset=UTF-8""><style type=""text/css"">body {margin: 2em 5%;}</style></head>"; 
       QString menudir=defaultdir;
      if ((lType==tKey)&&(key.compare("menudir")==0))
      {
        if ((title.compare("rtl")==0)||(title.compare("ltr")==0)) menudir=title;
        lType=getline(filereader,&key,&title);
      } 
      // defining html body, including direction.
      page+="<body dir="""+menudir+""">";
      page+="<H1>"+title+"</H1></FONT><BR>";
      lType=getline(filereader,&key,&description);
      // Read description
      while(lType==tText)
      {
        page+=description+"<br>";
        lType=getline(filereader,&key,&description);
      }      
      page+="</P><P></P><P>";
      linkname=description;

      // Read sections
      while(key.compare("end")!=0)
      {
        type=key;
        lType=getline(filereader,&key,&linktext);
        // Read image if exist
        image=defaultimage;
        if ((lType==tKey)&&(key.compare("image")==0))
        {
          image=linktext;
          lType=getline(filereader,&key,&linktext);
        }
        // Writing linktext
        if (type.compare("null")==0) page+="<FONT COLOR=GREY><U>"+linktext+"</U></FONT><BR><BR>";
        else if (type.compare("text")==0)
        {
          while (type.compare("/text")!=0)
          {
            page+=linktext+"<br>";
            lType=getline(filereader,&type,&linktext);
          }
          page+="<br>";
        }          
       	else
        {
          bool isStartpage=false;
          // Check if the link is same as desired startpage.
          if ((!cmdStartpage.isEmpty())&&(linkname.compare(cmdStartpage)==0))
          {
            isStartpage=true;
            startpageExist=true;
          }
          linkname=QString("swim://")+linkname;
          addSection(new csection(linkname,type,image));
          if ((isStartpage)&&(type.compare("name")==0))
          {
            addSection(new csection(QString("swit://startpage"),type,image));
            *startpage="swit://startpage";
          }
          if ((isStartpage)&&(type.compare("play")==0)) *startpage=linkname;
          page+="<a href="""+linkname+""">"+linktext+"</A><BR><BR>";
        }
        lType=getline(filereader,&key,&linkname);
      }
      // Adding "go back" or "Exit"
      bool isStartpage=false;
      if ((name.right(name.length()-7).compare(cmdStartpage)==0)&&
          (!cmdStartpage.isEmpty())) isStartpage=true;
      QString startpage_page=page;
      if (menuname.compare(name)!=0) page+="<a href=""swit://goback"">"+i18n("Go back")+"</a><BR><BR>";
      else page+="<a href=""swit://exit"">"+i18n("Exit")+"</a><BR><BR>";
      page+="</body></html>";
      if (isStartpage)
      {
        startpage_page+="<a href=""swit://exit"">"+i18n("Exit")+"</a><BR><BR>";
        startpage_page+="</body></html>";
        addTextToSection("swit://startpage", startpage_page);
      }
      addTextToSection(name,page);
      lType=getline(filereader,&key,&name);
      name=QString("swim://")+name;
    }
  }
  // menu file probably doesn't exist
  else
  {
    menuname="swim://notexist";
    addSection(new csection(menuname,"name",defaultimage));
    addTextToSection(menuname,i18n("ERROR - Menu file %1 not found.").arg(filename));
  }
  delete filereader;                 
  fp->close();
  delete fp;
  return startpageExist;
}*/

// Gets the type of the link (currently: name, play, exec, http)    
bool cmenu::getLink(QString linkname, QString *text, QString *type, QString *imagefile)
{
	QDomElement docElem = menusDoc->documentElement();

	QDomNode node = docElem.firstChild();
	while( !node.isNull() ) 
	{
		if (((node.nodeName().compare("menu")==0) || (node.nodeName().compare("play")==0)) 
		&& ((node.isElement()) && ((node.toElement().attribute("name").compare(linkname)==0)))) break;
		node = node.nextSibling();
	}
	if (node.isNull()) return false;
  
	QDomElement element = node.toElement();
	
	*imagefile=imagePath+element.attribute("image",defaultImage);
	*type=element.attribute("type","menu");  
	
	if (element.tagName().compare("menu")==0) //this is a menu
	{
		//found the correct menu
		//initializing pagetext (html)
  
		*text=QString("<!DOCTYPE HTML PUBLIC ""-//W3C//DTD HTML 4.01 Transitional//EN"">");
		*text+=QString("<html><head><meta http-equiv=""Content-Type"" content=""text/html; charset=UTF-8"">");
		*text+=QString("<style type=""text/css"">body {margin: 2em 5%;}</style></head>");
		// menu properties
		QString menudir=element.attribute("dir",defaultDir);
		*text+="<body dir="""+menudir+""">";
  
		node=node.firstChild();
		while (!node.isNull())
		{
			element = node.toElement(); // try to convert the node to an element.
			if(element.isNull()) break;
			if ((element.tagName().compare("text")==0)) *text+=element.text()+"<BR><BR>";
			else if ((element.tagName().compare("title")==0)) *text+="<H1>"+element.text()+"</H1><BR>";
			else if ((element.tagName().compare("link")==0)) 
				*text+="<A HREF=""swim://"+element.attribute("name")+""">"+element.text()+"</A><BR><BR>";
			else if ((element.tagName().compare("null")==0)) *text+="<FONT COLOR=GREY><U>"+element.text()+"</U></FONT><BR><BR>";
			node=node.nextSibling();
		}
		*text+="</body>";
	}	
	return true;
}
/*  pcsection where;

  for(where=first;(where!=NULL)&&(linkname.compare(where->linkname)!=0);where=where->next);

  if (where!=NULL)
  {
    *type=where->stype;
    *text=where->htmltext;
    if ((type->compare("play")==0)||(type->compare("name")==0)) *imagefile=imagepath+where->image;
      else imagefile=NULL;
  }
  else
  {
    type=NULL;
    imagefile=NULL;
    text=NULL;
  }*/

    

