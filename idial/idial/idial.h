/***************************************************************************
                          idial.h  -  description
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

#ifndef IDIAL_H
#define IDIAL_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kapp.h>
#include <qwidget.h>

/** Idial is the base class of the project */
class Idial : public QWidget
{
  Q_OBJECT 
  public:
    /** construtor */
    Idial(QWidget* parent=0, const char *name=0);
    /** destructor */
    ~Idial();
};

#endif
