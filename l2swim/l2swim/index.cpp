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

// Generic function to read from a file (stream)
// pass empty lines, # lines, and spaces at start line.

enum lineType{tText,tKey,tError,tEof};

lineType getline(QTextStream* stream, QString *key, QString *value)
{                                    
  QString temp=stream->readLine();
  *key="";
  *value="";
  if (temp.isNull()) return tEof;
  temp = temp.stripWhiteSpace();
  while ( (temp.isEmpty()) || (temp[0]=='#')  )
  {
    temp = stream->readLine();
    if (temp.isNull()) return tEof;
    temp = temp.stripWhiteSpace();
  }
  // case of <key=value>
  if ((temp[0]=='<')&&(temp[temp.length()-1]=='>')&&
            (temp.contains('>')==1)&&(temp.contains('<')==1)&&
            (temp.contains('=')<=1))
  {
    temp=temp.mid(1,temp.length()-2);
    if (temp.contains('=')==0)
    {
       *key=temp;
//       cout<<"only key="<<*key<<endl;
       return tKey;
    }
    else
    {
      *key=temp.left(temp.find('='));
      *value=temp.right(temp.length()-temp.find('=')-1);
//      cout<<"key="<<*key<<" value="<<*value<<endl;
      return tKey;
    }
  }
  // case of plain text;
  *value=temp;
//  cout<<"text="<<*value<<endl;
  return tText;
}

// initialize the menu
void cmenu::initialize(QString filename)
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
  // Read from file and initialize
  QIODevice* fp = new QFile(filename);
  fp->open(IO_ReadOnly);
  QTextStream* filereader = new QTextStream(fp);
  filereader->setEncoding(QTextStream::UnicodeUTF8);

  // Reading initial settings docspath and image and language!!
  while(((lType=getline(filereader,&key,&name))==tKey)&&(key.compare("menu")!=0))
  {
    if (key.compare("docspath")==0) docspath=name;
    else if (key.compare("defaultimage")==0) defaultimage=name;
    else if (key.compare("imagepath")==0) imagepath=name;
    else if (key.compare("menulanguage")==0) menulanguage=name;
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
      page="<table width=""90%""><tr><td>";
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
        else
        {
          linkname=QString("swim://")+linkname;
          addSection(new csection(linkname,type,image));
          page+="<a href="""+linkname+""">"+linktext+"</A><BR><BR>";
        }
        lType=getline(filereader,&key,&linkname);
      }
      // Adding "go back" or "Exit"
      if (menuname.compare(name)!=0) page+="<a href=""swit://goback"">"+i18n("Go back")+"</a><BR><BR>";
      else page+="<a href=""swit://exit"">"+i18n("Exit")+"</a><BR><BR>";
      page+="</P></td></tr></table>";
      addTextToSection(name,page);
      lType=getline(filereader,&key,&name);
      name=QString("swim://")+name;
    }
  }
  // menu file probably does't exist
  else
  {
    menuname="swim://notexist";
    addSection(new csection(menuname,"name",defaultimage));
    addTextToSection(menuname,i18n("ERROR - Menu file %1 not found.").arg(filename));
  }
  delete filereader;                 
  fp->close();
  delete fp;
}

// Adds information about a section in a linked list.
void cmenu::addSection(pcsection what)
{
  if (first==NULL) first=what;
  else

  {
    pcsection where;
    for(where=first;where->next!=NULL;where=where->next)
    if (where->linkname.compare(what->linkname)==0)
    {
      delete what;
      return;
    }
    // after the for
    where->next=what;
  }
//  cout<<what->linkname<<" , "<<what->stype<<endl;
}

// Gets the type of the link (currently: name, play, exec, http)    
void cmenu::getLink(QString linkname, QString *text, QString *type, QString *imagefile)
{
  pcsection where;
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
  }
}

void cmenu::addTextToSection(QString name, QString page)
{
  pcsection where;
  for(where=first;(where!=NULL)&&(name.compare(where->linkname)!=0);where=where->next);
  if(where!=NULL) where->htmltext=page;
}
    
