/***************************************************************************
 *   Copyright (C) 2003 by nir misgav                                      *
 *   nirro@linux-kinneret.org                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "config.h"
#include <kfiledialog.h>
#include <unistd.h>

#include <qlabel.h>
#include <qimage.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qvbox.h>

#include <kapplication.h>
#include <klocale.h>
#include <kwin.h>

#include "newthemedlg.h"
#include <kconfig.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <kurl.h>
#include <kmessagebox.h>

//-----------------------------------------------------------------------------
NewThemeDlg::NewThemeDlg(QWidget *parent):
  KDialogBase(parent, "newthemedlg", true,
	i18n("Create New Theme"), Ok|Cancel, Ok, true)
{
	QWidget *page = new QWidget(this);
	setMainWidget(page);

	mGrid = new QGridLayout(page, 5, 3, 0, spacingHint());
	mGridRow = 1;
	mEdtName = newLine(i18n("Detailed name:"),1);
	mEdtDetails = newTextEdit(i18n("Description:"),2,1);

	mPreviewLabel = new QLabel(page);
	mPreviewLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);
	mPreviewLabel->setMinimumSize(QSize(160,120));
	mGrid->addMultiCellWidget(mPreviewLabel, 1, 2, 2, 3);

	QPushButton *browseBut = new QPushButton(i18n("&Browse"), page);
	mGrid->addWidget(browseBut, 3, 2);
	QPushButton *snapshotBut = new QPushButton(i18n("&Snapshot"), page);
	mGrid->addWidget(snapshotBut, 3, 3);

	connect(snapshotBut, SIGNAL(clicked()), this, SLOT(slotSnapshot()));
	connect(browseBut, SIGNAL(clicked()), this, SLOT(slotLoadImage()));
	connect(mEdtName, SIGNAL(textChanged(const QString &)),this, SLOT(slotCheckEmpty(const QString &)));
	mGrid->setColStretch(1, 10);
	mGrid->setRowStretch(0,10);
	mGrid->setRowStretch(4, 10);
	mEdtName->setFocus();
	enableButtonOK(false);
	setButtonOKText(i18n("&Save"));
}


//-----------------------------------------------------------------------------
NewThemeDlg::~NewThemeDlg()
{
}

//-----------------------------------------------------------------------------

void NewThemeDlg::show()
{
	KDialogBase::show();
	KMessageBox::information(this,i18n("In order to make a new theme, first you should "
	"modify your current elements in the Control Center- Appearence and Themes, "
	"then come back here, and save it into a theme.\n"
	"You cannot modify the elements here.\n"
	"Don't forget to write decent name and description, and attach a preview image.\n"
	"Sopported elements : Background, Icons, Style, Window Decorations, Colors. "
	"Also supported : text and background colors in Konqueror and in the desktop."),
	i18n("Quick help"),"knrtCreateQuickHelp");
}

QLineEdit* NewThemeDlg::newLine(const QString& aLabelText, int cols)
{
  QLineEdit *edt = new QLineEdit(mainWidget());
  edt->setMinimumSize(edt->sizeHint());
  mGrid->addMultiCellWidget(edt, mGridRow, mGridRow, 1, 0+cols);

  QLabel *lbl = new QLabel(aLabelText, mainWidget());
  lbl->setMinimumSize(lbl->sizeHint());
  lbl->setBuddy(edt);
  mGrid->addWidget(lbl, mGridRow, 0);

  mGridRow++;
  return edt;
}

QTextEdit* NewThemeDlg::newTextEdit(const QString& aLabelText, int rows,int cols)
{
  QTextEdit *edt = new QTextEdit(mainWidget());
  edt->setMinimumSize(edt->sizeHint());
  mGrid->addMultiCellWidget(edt, mGridRow, mGridRow+rows-1, 1, 0+cols);

  QLabel *lbl = new QLabel(aLabelText, mainWidget());
  lbl->setMinimumSize(lbl->sizeHint());
  lbl->setBuddy(edt);
  mGrid->addMultiCellWidget(lbl, mGridRow, mGridRow+rows-1,0,0);

  mGridRow+=rows;
  return edt;
}

void NewThemeDlg::slotSnapshot()
{
  int desktop = KWin::currentDesktop();
  SnapshotDlg *dlg = new SnapshotDlg(this);
  int result = dlg->exec();
  delete dlg;
  if (result == SnapshotDlg::Rejected)
     return;

  kapp->processEvents();
#ifdef HAVE_USLEEP
  usleep(100000);
  kapp->processEvents();
#endif  

  mPreview = QPixmap::grabWindow( qt_xrootwin()).convertToImage().smoothScale(800,600);
  QPixmap snapshot;
  snapshot.convertFromImage(mPreview.smoothScale(160,120));
  mPreviewLabel->setPixmap(snapshot);
  KWin::setCurrentDesktop(desktop);
  KWin::deIconifyWindow(winId(), false);
}

SnapshotDlg::SnapshotDlg(QWidget *parent)
   : KDialogBase(parent, "snapshot", true,
         i18n("Make Snapshot"), Cancel, Cancel, true)
{
  QVBox *page = makeVBoxMainWidget();
  mLabel = new QLabel(page);
  mSeconds = 5;
  connect(&mTimer, SIGNAL(timeout()), this, SLOT(slotCountdown()));
  slotCountdown();
}

void SnapshotDlg::slotCountdown()
{
  if (mSeconds == 0)
  {
     accept();
     return;
  }
  kapp->beep();
  mLabel->setText(i18n("Taking snapshot in %1 seconds!").arg(mSeconds--));
  mTimer.start(1000, true);
}

void NewThemeDlg::slotCheckEmpty(const QString & name)
{
	//kapp->beep();
	enableButtonOK(!name.stripWhiteSpace().isEmpty());
}

void NewThemeDlg::slotLoadImage()
{
	KURL url = KFileDialog::getImageOpenURL();
	if (url.isEmpty()) return;
	QPixmap pixmap;
	mPreview.load(url.url().right(url.url().length()-5));
	pixmap.convertFromImage(mPreview.smoothScale(160,120));

	mPreviewLabel->setPixmap(pixmap);
}

#include "newthemedlg.moc"
