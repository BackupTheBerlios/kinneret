/***************************************************************************
                          index.cpp  -  description
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
#include <iostream>

using namespace std;

cmenu::cmenu(QString filename,bool *success)
{
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
		cout<<"Error while parsing menu :"<<endl<<errorMsg<<", Line: "<<errorLine<<" ,Column: "<<errorColumn<<endl;
		*success=false;
		return;
	}
	f.close();
	*success=true;
	//root element
	QDomElement docElem = menusDoc->documentElement();
	
	// assigning global configuration
	QDomNode globalNode = docElem.firstChild();
	if((!globalNode.isNull())&&(globalNode.nodeName().compare("global_config")==0))
	{
		QDomElement globalElement=globalNode.toElement();
		
		defaultImage=globalElement.attribute("defaultimage");
		defaultDir=globalElement.attribute("defaultdir","ltr");
		docsPath=globalElement.attribute("docspath","");
		imagePath=globalElement.attribute("imagepath","");
		firstPage=globalElement.attribute("firstpage");
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
			if (firstPage.isNull()) firstPage=menuNode.toElement().attribute("name");
			
			QDomNode linkNode=menuNode.firstChild();
			QDomElement linkElem;
			while(!linkNode.isNull())
			{
				linkElem=linkNode.toElement();
				if ((!linkElem.isNull()) && (linkElem.tagName().compare("link")==0) && (linkElem.attribute("type","menu").compare("play")==0))
				{
					QDomElement append = menusDoc->createElement("play");
					append.setAttribute("name",linkElem.attribute("name"));
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

// Gets the image file and the text for the "menu", or just  imagefile for "play".  
bool cmenu::getLink(QString linkname, QString type, QString *imagefile, QString *text)
{
	QDomElement docElem = menusDoc->documentElement();

	QDomNode node = docElem.firstChild();
	while( !node.isNull() ) 
	{
		if ((node.nodeName().compare(type)==0) 
		&& (node.isElement()) && (node.toElement().attribute("name").compare(linkname)==0)) break;
		node = node.nextSibling();
	}
	if (node.isNull()) return false;
  
	QDomElement element = node.toElement();
	
	*imagefile=imagePath+element.attribute("image",defaultImage);
	
	if (type.compare("menu")==0) //this is a menu
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
			else if ((element.tagName().compare("null")==0)) *text+="<FONT COLOR=GREY><U>"+element.text()+"</U></FONT><BR><BR>";
			else if ((element.tagName().compare("chapter")==0)) *text+="<H1>"+element.text()+"</H1><BR>";
			else if ((element.tagName().compare("link")==0)) 
				*text+="<A HREF="""+element.attribute("type","menu")+"://"+element.attribute("name")+""">"+element.text()+"</A><BR><BR>";
			node=node.nextSibling();
		}
		*text+="</body>";
	}	
	return true;
}
