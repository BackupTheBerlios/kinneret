/***************************************************************************
 *   Copyright (C) 2003 by nir misgav                                      *
 *   nirro@linux-kinneret.org                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include <qlayout.h>

#include <klocale.h>
#include <kglobal.h>

#include "knrtheme.h"

#include <kmessagebox.h>
#include <kglobalsettings.h>
#include <kstandarddirs.h>
#include <qvbox.h>
#include <qlayout.h>
#include <qpixmap.h>
#include <kpixmapeffect.h>
#include "newthemedlg.h"
#include <stdlib.h>
#include <qfile.h>
#include <qfileinfo.h>

knrtheme::knrtheme(QWidget *parent, const char *name)
    : KCModule(parent, name)
{
    // place widgets here
	mThemesVector.resize(20);
	mGrid = new QGridLayout(this, 2, 3, 6, 6);
	mThemesList = new KListBox(this);
	mGrid->addMultiCellWidget(mThemesList, 0, 1, 0, 0);

	mPreview = new QLabel(this);
	mPreview->setFrameStyle(QFrame::Panel|QFrame::Sunken);
	mPreview->setMinimumSize(QSize(320,240));
	mPreview->setScaledContents(true);

	mGrid->addWidget(mPreview, 0, 1);

	mText = new QTextEdit(this);
	mText->setMinimumSize(mText->sizeHint());
	mText->setReadOnly(true);
	mGrid->addWidget(mText, 1, 1);

	bbox = new KButtonBox(this, KButtonBox::Vertical, 0, 6);
  	mGrid->addMultiCellWidget(bbox, 0, 1, 2, 2);

	mBtnCreate = bbox->addButton(i18n("&Create"));
	connect(mBtnCreate, SIGNAL(clicked()), SLOT(slotCreate()));
	mBtnDelete = bbox->addButton(i18n("&Erase"));
	connect(mBtnDelete, SIGNAL(clicked()), SLOT(slotDelete()));
	mGrid->setColStretch(0, 1);
	bbox->layout();
	mGrid->setColStretch(1, 3);
	mGrid->setRowStretch(0, 3);
	mGrid->setRowStretch(1, 1);

//	themes="/knrtheme/themes/";
	KGlobal::dirs()->addResourceDir("knrThemes", "/opt/kinneret/knrtheme/themes/");
	char* home=getenv("HOME");
	KGlobal::dirs()->addResourceDir("knrThemes", QString(home)+"/.knrthemes/");

	connect(mThemesList, SIGNAL(highlighted(int)), this, SLOT(slotUpdateTimer(int)));
//	connect(mThemesList, SIGNAL(rightButtonClicked(int)), this, SLOT(slotUpdateTimer(int)));
	connect(mThemesList, SIGNAL(selected(int)), this, SLOT(slotSave()));
	connect(&switchThemeTimer, SIGNAL(timeout()), this, SLOT(slotThemeChanged()));
//	mText->setFocus();
	load();
};

knrtheme::~knrtheme()
{
}

void knrtheme::load()
{
    // insert your loading code here...
	QStringList entryList = KGlobal::dirs()->findAllResources("knrThemes", QString::null, false, true);
	mThemesList->clear();
	mThemesVector.clear();
	uint i=2,position;
	bool defaultExist=false;
	QStringList::ConstIterator name;
	for(name = entryList.begin(); name != entryList.end(); name++)
	{
		QString tmp=*name;
		if (tmp.right(5).compare(".knrt")!=0) continue;
		theme* mt=new theme;
		mt->load(tmp);
		if ((tmp.right(13).compare("/default.knrt")==1)&&(!defaultExist))
		{
			position=1;
			defaultExist=true;
		} else position=i++;
		if (i>mThemesVector.size()) mThemesVector.resize(i+9);
		mThemesList->insertItem(mt->getname(),position);
		mThemesVector.insert( position, mt );

	}
	if (defaultExist) startIndex=1; else startIndex=2;
	mBtnDelete->setEnabled(false);
	emit changed(false);
	mChanged=false;
	hilighted=-1;
	lasthilighted=-1;
	if (mThemesList->count()==0)
	{
		mPreview->setText("");
		mText->setText("");
	}
}

void knrtheme::defaults()
{
	// insert your default settings code here...
	if (mThemesList->count()!=0)
	{
		mThemesList->setCurrentItem(mThemesList->firstItem());
		emit changed(true);
		mBtnDelete->setEnabled(true);
		mChanged=true;
	}
	else
	{
		mPreview->setText("");
		mText->setText("");
		mBtnDelete->setEnabled(false);
		emit changed(false);
		mChanged=false;
	}
}

void knrtheme::slotSave()
{
	int index=mThemesList->currentItem();
	QString name=mThemesList->text(index);
	if (KMessageBox::warningYesNo (this, i18n("Do you want to load the theme: \"%1\" ?").arg(name), i18n("Load"))==KMessageBox::No) return;
	save();
}

void knrtheme::save()
{
	if (!mChanged) return;
//	WaitDialog *dlg = new WaitDialog(this);
//	dlg->show();
	int index=mThemesList->currentItem();
//	setUpdatesEnabled(false);
	mThemesVector[index+startIndex]->apply();
//	setUpdatesEnabled(true);
//	dlg->hide();
//	delete dlg;
	emit changed(false);
	mChanged=false;
}


int knrtheme::buttons()
{
	return KCModule::Default|KCModule::Apply|KCModule::Help;
}


void knrtheme::configChanged()
{
	// insert your saving code here...
//	emit changed(false);

}


QString knrtheme::quickHelp() const
{
	return i18n("The Kinneret's theme manager,\n"
	"Written by: Nir Misgav\n"
	"Version: %1\n"
	"Date: %2").arg("0.7b1").arg("2/10/03");
}


extern "C"
{

	KCModule *create_knrtheme(QWidget *parent, const char *)
	{
		KGlobal::locale()->insertCatalogue("knrtheme");
		return new knrtheme(parent, "knrtheme");
	}
}

void knrtheme::slotThemeChanged()
{
	//KMessageBox::information(this,"SLOT");
	if (hilighted<0) return;
	mBtnDelete->setEnabled(true);
	if (hilighted==lasthilighted) return;
	int index=mThemesList->currentItem();
	QString description=mThemesVector[index+startIndex]->getdescription();
	if ((description.isNull())||(description.isEmpty())) description=i18n("No description available");
	mText->setText(description);
	QPixmap image(mThemesVector[index+startIndex]->getimagefile());
	lasthilighted=hilighted;
	if (!image.isNull()) mPreview->setPixmap(image);
	else mPreview->setText(i18n("No image available"));
	mChanged=true;
}

void knrtheme::slotUpdateTimer(int i)
{
	hilighted=i;
	emit changed(true);
	switchThemeTimer.start(400, TRUE);
}

void knrtheme::slotCreate()
{
	NewThemeDlg dlg(this);
	if (!dlg.exec()) return;

	theme newtheme;
	QString fileName;
	char* home=getenv("HOME");
	QString path = QString(home)+"/.knrthemes/";
	int i=1;
	// finding a proper name to save
	do fileName=QString("custom%1").arg(i++);
	while (QFile::exists(path+fileName+".knrt"));
	// Now saving
	newtheme.save(path,fileName,dlg.themeName(),"0.2",dlg.description());
	if(!dlg.preview().isNull()) dlg.preview().save(newtheme.getimagefile(), "PNG");
//	mThemesList->clear();
	load();
	// Changing to the new theme
	uint index=0;
	for(uint i=0;i<mThemesList->count();i++)
//	KMessageBox::error(this,mThemesVector[index+startIndex]->getfilename());
	if (mThemesVector[i+startIndex]->getfilename().compare(path+fileName+".knrt")==0)
	{
		index=i;
		break;
	}
	mThemesList->setCurrentItem(index);
	emit changed(true);
	mBtnDelete->setEnabled(true);
	mChanged=true;
}

void knrtheme::slotDelete()
{
	int index=mThemesList->currentItem();
//	KMessageBox::information(0,QString("%1").arg(index));
	QString name=mThemesList->text(index);
	QString filename=mThemesVector[index+startIndex]->getfilename();

	QString imagefile=mThemesVector[index+startIndex]->getimagefile();
	if (!QFileInfo(filename).isWritable())
	{
		KMessageBox::sorry(this,i18n("You cannot erase this theme (No write permission)"));
		return;
	}
	if (KMessageBox::warningYesNo (this, i18n("Do you want to erase the theme: \"%1\" ?").arg(name), i18n("Delete"))==KMessageBox::No) return;
	QFile::remove(imagefile);
	if(QFile::remove(filename))
	{
		load();
//		KMessageBox::information(this,i18n("Theme erased"));
	}
	else KMessageBox::error(this,i18n("Unable to erase the theme"));
}

WaitDialog::WaitDialog(QWidget *parent)
   : KDialogBase(parent, "wait", true,
         i18n("Plese wait"), 0)
{
	mLabel = new QLabel(this);
	mLabel->setText(i18n("Plese wait while applying theme"));
	setMainWidget(mLabel);
}

#include "knrtheme.moc"
