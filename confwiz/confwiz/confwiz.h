/***************************************************************************
                          confwiz.h  -  description
                             -------------------
    begin                : Wed Mar 19 22:58:54 IST 2003
    copyright            : (C) 2003 by Itay 'z9u2K' Duvdevani
    email                : z9u2K@linux-kinneret.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CONFWIZ_H
#define CONFWIZ_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kapp.h>
#include <qwidget.h>

/** Confwiz is the base class of the project */
class Confwiz : public QWidget
{
	Q_OBJECT 
	public:
	/** construtor */
	Confwiz(QWidget* parent=0, const char *name=0);
	/** destructor */
	~Confwiz();
};

#endif
