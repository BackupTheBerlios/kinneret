/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Fri Apr  4 14:44:54 IDT 2003
    copyright          : (C) 2003 by
    email                :
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <kapplication.h>
#include "l2swim.h"
#include <klocale.h>
//#include <iostream.h>

int main( int argc, char **argv )
{
  KApplication a( argc, argv, "l2swim");
  MainWindow *window=new MainWindow( "");
  a.setMainWidget( window );
  window->resize(640,480);
  window->showMaximized();

  return a.exec();
}

