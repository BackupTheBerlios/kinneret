/***************************************************************************
 *   Copyright (C) 2003 by nir misgav                                      *
 *   nirro@linux-kinneret.org                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef NEW_THEME_DLG_H
#define NEW_THEME_DLG_H

#include <kfiledialog.h>
#include <kdialogbase.h>
#include <qlineedit.h>
#include <qmultilineedit.h>
#include <qtimer.h>
#include <qimage.h>

class QLabel;
class QGridLayout;

class NewThemeDlg: public KDialogBase
{
	Q_OBJECT
public:
	NewThemeDlg(QWidget *parent);
	virtual ~NewThemeDlg();

//  QString fileName(void) const { return "custom1";};//mEdtFilename->text().stripWhiteSpace(); }
	QString themeName(void) const { return mEdtName->text().stripWhiteSpace(); }
//  QString version(void) const { return "0.1";};//mEdtVersion->text().stripWhiteSpace(); }
	QString description(void) const { return mEdtDetails->text(); }
	QImage preview() const { return mPreview; }

protected:
	virtual QLineEdit* newLine(const QString& lbl, int cols);
	virtual QTextEdit* newTextEdit(const QString& lbl, int rows, int cols);
	virtual void show();
protected slots:
	void slotSnapshot();
	void slotLoadImage();
	void slotCheckEmpty(const QString &);


protected:
	int mGridRow;
	QLineEdit *mEdtName;
	QTextEdit *mEdtDetails;
	QLabel *mPreviewLabel;
	QImage mPreview;
	QGridLayout* mGrid;
};

class SnapshotDlg: public KDialogBase
{
	Q_OBJECT
public:
	SnapshotDlg(QWidget *parent);
protected slots:
	void slotCountdown();

protected:
	QTimer mTimer;
	QLabel *mLabel;
	int mSeconds;
};


#endif /*NEW_THEME_DLG_H*/
