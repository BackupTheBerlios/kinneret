/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Sat Jul 12 18:10:19 IDT 2003
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

#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>

#include <qlineedit.h>
#include <qradiobutton.h>
#include <qcombobox.h>
#include <kpassdlg.h>
#include <qcheckbox.h>

#include <kmessagebox.h>

#include "iwiz.h"
#include "iwizard.h"
#include "rename.h"

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

static const char *description = I18N_NOOP("Iwiz");
static KCmdLineOptions options[] =
{
	{ 0, 0, 0 }
};

int main(int argc, char *argv[])
{
	KAboutData aboutData("iwiz", I18N_NOOP("Iwiz"),
		VERSION, description, KAboutData::License_GPL,
 		"(c) 2003, Itay 'z9u2K' Duvdevani", 0, 0, "z9u2k@linux-kinneret.org");
	aboutData.addAuthor("Itay 'z9u2K' Duvdevani",0, "z9u2k@linux-kinneret.org");

	KCmdLineArgs::init(argc, argv, &aboutData);
	KCmdLineArgs::addCmdLineOptions(options);

	KApplication a;
	iwizard *iwiz = new iwizard();
	iwiz->setFinishEnabled(iwiz->QWizard::page(6), true);
	a.setMainWidget(iwiz);
	iwiz->show();  

	a.exec();

	if (iwiz->result() != QDialog::Rejected)
	{
		// Wizard completed, run the tool and create the connection!

		// First, check to see if the name is unique.
		// if it isn't, allow to the user to rename the connection.
		vector<string>	vNames;
		int ret = system("internet -C > /tmp/.cons");

		ifstream cons("/tmp/.cons");
		if (!cons || ret != 0)
		{
			KMessageBox::error(0, tr2i18n("Cannot open /tmp/.cons"));
			return -1;
		}

		char szBuffer[0xFF];
		cons.getline(szBuffer, 0xFF);	// listing connections...
		while (!cons.eof())
		{
			cons.getline(szBuffer, 0xFF);
			if (strlen(szBuffer)) vNames.push_back(string(szBuffer));
		}

		cons.close();

		bool bOK;
		QString qName = iwiz->lineConnectionName->text();
		do
		{
			bOK = true;
			vector<string>::iterator iter;
			for (iter = vNames.begin() ; iter != vNames.end() ; iter++)
			{
				if (QString(iter->c_str()) == qName)
				{
					bOK = false;
					break;
				}
			}

			if (!bOK)
			{
				Rename *ren = new Rename();
				a.setMainWidget(ren);
				ren->show();
				a.exec();

				qName = ren->lineNewName->text();

				delete ren;
			}
		} while (!bOK);

		// assemble command line and execute
		string strCmd = "internet";

		strCmd += " ";
		strCmd += "--debian=";
		if (iwiz->radioDebian->isChecked()) strCmd += "yes";
		else if (iwiz->radioNonDebian->isChecked()) strCmd += "no";

		strCmd += " ";
		strCmd += "--isp=";
		strCmd += iwiz->mapISPs[string(iwiz->comboISPs->currentText().ascii())];

		strCmd += " ";
		strCmd += "--method=";
		if (iwiz->radioLAN->isChecked()) strCmd += "lan";
		else if (iwiz->radioADSL->isChecked()) strCmd += "adsl";
		else if (iwiz->radioCable->isChecked()) strCmd += "cable";
		else if (iwiz->radioISDN->isChecked()) strCmd += "isdn";
		else if (iwiz->radioDialup->isChecked()) strCmd += "dialup";

		strCmd += " ";
		strCmd += "--modem=\"";
		strCmd += string(iwiz->comboModems->currentText().ascii());
		strCmd += "\"";

		// iface, optional
		if (iwiz->radioEthernet->isEnabled())
		{
			// if the radio box is enabled, the modem is a dual modem
			strCmd += " ";
			strCmd += "--iface=";
			if (iwiz->radioEthernet->isChecked()) strCmd += "eth";
			else if (iwiz->radioUSB->isChecked()) strCmd += "usb";
		}

		strCmd += " ";
		strCmd += "--dev=";
		if (iwiz->radioEthernet->isChecked()) strCmd += string(iwiz->comboEth->currentText().ascii());
		else if (iwiz->radioUSB->isChecked()) strCmd += string(iwiz->lineUSBEth->text().ascii());

		strCmd += " ";
		strCmd += "--username=\"";
		strCmd += string(iwiz->lineUsername->text().ascii());
		strCmd += "\"";

		if (!iwiz->lineServer->text().isEmpty())
		{
			strCmd += " ";
			strCmd += "--server=\"";
			strCmd += string(iwiz->lineServer->text().ascii());
			strCmd += "\"";
		}

		strCmd += " ";
		strCmd += "--passwd=\"";
		strCmd += string(iwiz->linePassword->password());
		strCmd += "\"";

		strCmd += " ";
		strCmd += "--name=\"";
		strCmd += string(qName.ascii());
		strCmd += "\"";

		strCmd += " 2>&1 > /tmp/internet_dump";

		if (system(strCmd.c_str()) != 0)
		{
			KMessageBox::error(0, tr2i18n("Unable to create connection.\n"
				"/tmp/internet_dump containes the output from the tool,\n"
				"please report a bug and include this file."));
			return -1;
		}
		else KMessageBox::information(0, tr2i18n("Connection created successfuly"));

		// default connection
		if (iwiz->checkSetDefault->isChecked())
		{
			strCmd = "internet --default=\"" + string(qName.ascii()) + "\" 2>&1 > /tmp/internet_dump";
			if (system(strCmd.c_str()) != 0)
			{
				KMessageBox::error(0, tr2i18n("Unable to set connection to default."));
				return -1;
			}
			else KMessageBox::information(0, tr2i18n("Connection set to default"));
		}
	}

	return 0;
}
