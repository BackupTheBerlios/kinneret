/***************************************************************************
                          config.cpp  -  description
                             -------------------
    begin                : Sat Jul 19 2003
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
#include "internet.h"

void ConfigFile::LoadConfig(string conf) throw (Error)
{
	ifstream confile(conf.c_str());
	if (!confile) throw Error404(conf);

	char szBuffer[0xFFFF];		// That's a big buffer... :)
	while (!confile.eof())
	{
		confile.getline(szBuffer, 0xFFFF);

		if (strlen(szBuffer))
		{
			// Anyone knows a good parsing lib?
			// I hate writing ugly, C-style stringed code...

			char *c = szBuffer;
			while (isspace(*c)) c++;
			if (*c == '#') continue;	// comment or empty line

			if ((c = strstr(szBuffer, "DBPATH=")) != 0)
			{
				c += 7;
				char *begin = c;

				if (*c == '"')
				{
					begin++;
					char *end = strstr(begin, "\"");
					*end = 0;
				}

				else if (*c == '\'')
				{
					begin++;
					char *end = strstr(begin, "\'");
					*end = 0;
				}

				else
				{
					char *end = begin;

					while (!isspace(*end)) end++;
					*end = 0;
				}

				strDBPath = string(begin);
			}
		}
	}

	strDBPath += string("/");

	confile.close();
}

