/***************************************************************************
 *   Copyright (C) 2003 by nir misgav                                      *
 *   nirro@linux-kinneret.org                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

 #ifndef _KNRTHEME_H_
#define _KNRTHEME_H_

#include <kcmodule.h>
#include <kaboutdata.h>
#include <klistbox.h>
#include <qlabel.h>
#include "theme.h"
#include <qlayout.h>
#include <qvector.h>
#include <qmultilineedit.h>
#include <qtimer.h>
#include <kbuttonbox.h>
#include <kpushbutton.h>
#include <kdialogbase.h>

class knrtheme: public KCModule
{
	Q_OBJECT

public:
	knrtheme( QWidget *parent=0, const char *name=0 );
	~knrtheme();

	virtual void load();
	virtual void save();
	virtual void defaults();
	virtual int buttons();
	virtual QString quickHelp() const;
	virtual const KAboutData *aboutData()
	{ return myAboutData; };

public slots:
	void configChanged();
	void slotThemeChanged();
	void slotUpdateTimer(int);
	void slotCreate();
	void slotDelete();
	void slotSave();

private:
	KAboutData *myAboutData;
	QTimer switchThemeTimer;
	int hilighted, lasthilighted, startIndex;
	QGridLayout *mGrid;
	KListBox *mThemesList;
	QLabel *mPreview;
	QTextEdit *mText;
	QVector<theme> mThemesVector;
	KButtonBox *bbox;
	QPushButton *mBtnCreate;
	QPushButton *mBtnDelete;
	bool mChanged;
};

class WaitDialog: public KDialogBase
{
	Q_OBJECT
public:
	WaitDialog(QWidget *parent);
	QLabel *mLabel;
};

#endif
