/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Mon Jul 21 17:34:17 IDT 2003
    copyright            : (C) 2003 by Itay 'z9u2K' Duvdevani
    email                : z9u2k@linux-kinneret.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>

#include "idial.h"
#include "idialer.h"

static const char *description =
	I18N_NOOP("Idial");
// INSERT A DESCRIPTION FOR YOUR APPLICATION HERE
	
	
static KCmdLineOptions options[] =
{
  { 0, 0, 0 }
  // INSERT YOUR COMMANDLINE OPTIONS HERE
};

int main(int argc, char *argv[])
{

  KAboutData aboutData( "idial", I18N_NOOP("Idial"),
    VERSION, description, KAboutData::License_GPL,
    "(c) 2003, Itay 'z9u2K' Duvdevani", 0, 0, "z9u2k@linux-kinneret.org");
  aboutData.addAuthor("Itay 'z9u2K' Duvdevani",0, "z9u2k@linux-kinneret.org");
  KCmdLineArgs::init( argc, argv, &aboutData );
  KCmdLineArgs::addCmdLineOptions( options ); // Add our own options.

  KApplication a;
  idialer *idial = new idialer();
  a.setMainWidget(idial);
  idial->show();  

  return a.exec();
}
