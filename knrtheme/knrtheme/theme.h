/***************************************************************************
 *   Copyright (C) 2003 by nir misgav                                      *
 *   nirro@linux@linux-kinneret.org                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <qvaluelist.h>
#include <kconfig.h>
#include <qsettings.h>

struct DecorationInfo
{
	QString name;
	QString libraryName;
};

class theme
{
	public:
	void load(QString filename);
	void apply();
	void save(QString pt,QString fn,QString nm,QString vr,QString ds);
	const QString getname() {return name;};
	const QString getversion() {return version;};
	const QString getdescription() {return description;};
	const QString getimagefile() {return path+file.left(file.length()-5)+".png";};
	const QString getfilename() {return path+file;};

	private:
	void findDecorations();
	void copyStyle(KConfig *from, KConfig *to,int action, bool *styleChanged,
			bool *effectChanged, bool *macStyleChanged, bool *toolbarChanged);
	void applyStyle(bool styleChanged, bool effectChanged, bool macStyleChanged, bool toolbarChanged);
	bool copyIcons(KConfig *from, KConfig *to,int action);
	void applyIcons();
	bool copyWinDecoration(KConfig *from, KConfig *to);
	void applyWinDecoration();
	bool copyBackground(KConfig *from,KConfig *to);
	void applyBackground();
	void applyFonts();
	void applyKonq();
	bool copyColors(KConfig *from, KConfig *to, int action);
	void applyColors();

	bool copyEntry(KConfig *from,QString fromEntry, KConfig *to, QString toEntry);
	bool copyEntry(QSettings *from,QString fromEntry, KConfig *to, QString toEntry);
	bool copyEntry(KConfig *from,QString fromEntry, QSettings *to, QString toEntry);
	bool copyEntry(KConfig *from, KConfig *to, QString entry)
		{return copyEntry(from,entry,to,entry);};

	bool copyDesktop(int desktop,  KConfig *from, KConfig *to);
	bool copyAllDesktops(KConfig *from, KConfig *to);
	bool copyBackgroundCommon(KConfig *from, KConfig *to);
	bool copyFMSettings(KConfig *from, QString fromGroup, KConfig *to,QString toGroup);
	QCString desktopAppName();
	QCString desktopFileName() {return desktopAppName()+"rc";}

	QString path, file, name, description, version;
	QValueList<DecorationInfo> decorations;
};
