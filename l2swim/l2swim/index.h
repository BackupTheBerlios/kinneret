/***************************************************************************
                          index.h  -  description
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
//#include <qmime.h>
#include <qtextstream.h>
//#include <klocale.h>
#include <qdom.h>
#include <qfile.h>

class cmenu
{
public:

    ~cmenu() {delete menusDoc;};
    cmenu(QString filename,bool *success);
    bool getLink(QString linkname,  QString type, QString *imagefile, QString *text=NULL);
//    void addSection(pcsection what);
//    void addTextToSection(QString name, QString page);
//    bool initialize(QString filename, QString cmdStartpage, QString *startpage);
    QString getFirstPage() {return QString("menu://")+firstPage;};
//    QString getLanguage() {return menulanguage;};
    QString getDocsPath() {return docsPath;};
    QString getDefaultImage() {return imagePath+defaultImage;};  
private:
     QDomDocument* menusDoc;
     QString firstPage, docsPath, defaultImage, imagePath, defaultDir, cssFile;
};
