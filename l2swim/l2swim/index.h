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
 ***********************************l****************************************/
 
#include <qstring.h>
#include <qmime.h>
#include <qfile.h>
#include <qtextstream.h>
#include <klocale.h>

class csection
{
  public:
    csection(QString name, QString tp, QString im) {linkname=name; ; image=im; stype=tp; next=NULL;};
    ~csection() {delete next;};
    QString image;
    QString stype;
    QString htmltext;
    QString linkname;
    csection* next;
} ;
typedef csection* pcsection;

class cmenu
{
public:

    ~cmenu() {delete first;};
    cmenu() {first=NULL;};
    void getLink(QString linkname, QString *text, QString *type, QString *imagefile);
    void addSection(pcsection what);
    void addTextToSection(QString name, QString page);
    void initialize(QString filename);
    QString getMenuName() {return menuname;};
    QString getLanguage() {return menulanguage;};
    QString getDocsPath() {return docspath;};
    QString getDefaultImage() {return imagepath+defaultimage;};  
    
private:
    csection* first;
    QString menuname, docspath, defaultimage, imagepath, menulanguage;
};
