/***************************************************************************
                          main.cpp  -  description
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

#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qobjectlist.h>
#include <ktextbrowser.h>
#include <qfile.h>
#include <qcheckbox.h>
#include <kprocess.h>
#include <khtmlview.h>

#include "confwiz.h"
#include "configwizard.h"

#include <iostream>

static const char *description =
	I18N_NOOP("Configuration Wizard");	
	
static KCmdLineOptions options[] =
{
	{ 0, 0, 0 }
};

void InitWizard(configwizard *wizard)
{
	wizard->setFinishEnabled(reinterpret_cast<QWizard*>(wizard)->page(8), true);
	wizard->showFullScreen();

	// Set the currect palette for all objects
	QPalette pal = wizard->palette();
	QObjectList *l = wizard->queryList("QWidget");
	QObjectListIt it(*l);
	QObject *obj;
	while ((obj = it.current()) != 0)
	{
		++it;
		((QWidget*)obj)->setPalette(pal);
	}
	delete l; // delete the list, not the objects

	// Set side-menus
	QString q_stage[] =
	{
		QString(tr2i18n("partition")),
		QString(tr2i18n("swap")),
		QString(tr2i18n("homedir")),
		QString(tr2i18n("conclusion")),
		QString(tr2i18n("fonts")),
		QString(tr2i18n("whatsnext?"))
	};

	QLabel *q_index[] =
	{
		wizard->side1,
		wizard->side2,
		wizard->side3,
		wizard->side4,
		wizard->side5,
		wizard->side6
	};

	const int count = 5;
	for (int i = 0 ; i < count ; i++)
	{
		QString qs("");

		for (int j = 0 ; j < count ; j++)
		{
			if (j == i) qs += QString("<b>") + q_stage[j] + QString("</b>");
			else qs += q_stage[j];

			qs += QString("<br>");
		}
		q_index[i]->setText(qs);
	}
}

int main(int argc, char *argv[])
{
	// Before doing anything, see if the wizard should run...
	// The startup script will create the file /etc/foundhome
	// and will put 0 in it if it couldn't find the home directory.
	#warning ADD NOT!!
	if (/*!*/QFile::exists(QString("/tmp/foundhome")))
	{
		system("sudo /opt/kinneret/bin/ttf.sh");	// load fonts
		return 0;
	}
	
	unlink("/tmp/foundhome");

	// Continue...

	KAboutData aboutData("confwiz", I18N_NOOP("Confwiz"),
		VERSION, description, KAboutData::License_GPL,
		"(c) 2003, Itay 'z9u2K' Duvdevani", 0, 0, "z9u2K@linux-kinneret.org");
	aboutData.addAuthor("Itay 'z9u2K' Duvdevani",0, "z9u2K@linux-kinneret.org");

	KCmdLineArgs::init(argc, argv, &aboutData);
	KCmdLineArgs::addCmdLineOptions(options); // Add our own options.

	KApplication a;
	configwizard *wizard = new configwizard();

	InitWizard(wizard);

	a.setMainWidget(wizard);
	wizard->show();

	a.exec();

	// only if wizard was completed
	if (wizard->result() != QDialog::Rejected)
	{
		system("sudo /opt/kinneret/bin/ttf.sh");	// load fonts
	}

	KProcess p;

	if (wizard->checkPrefWiz->isChecked() == true && wizard->result() != QDialog::Rejected)
	{
		// run preferance wizard...
		p.clearArguments();
		p << "/opt/kinneret/bin/prefwiz";
		p.start();

		// wait for completetion...
		while (p.isRunning());
	}

	// run swim wizard...
	p.clearArguments();
	p << "/opt/kinneret/bin/swim";
	p.start();	
	while (p.isRunning());
	
	return 0;
}
