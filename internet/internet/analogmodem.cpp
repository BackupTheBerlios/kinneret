/***************************************************************************
                          analogmodem.cpp  -  description
                             -------------------
    begin                : Thu Aug 21 2003
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
#include "hardware.h"

void AnalogModem::MakeInit(ostream &stream)			const { stream << endl; }
void AnalogModem::MakeBoot(ostream &stream)			const { stream << endl; }
void AnalogModem::MakeConnect(ostream &stream)		const { stream << endl; }
void AnalogModem::MakeDisconnect(ostream &stream)	const { stream << endl; }
void AnalogModem::MakeDone(ostream &stream)			const { stream << endl; }
