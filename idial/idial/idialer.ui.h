/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <fstream>

#include <kmessagebox.h>

void idialer::init()
{
	// Fill with connections

	// which is the default connection?
	int ret = system("internet --defaultshow > /tmp/.def");
	std::ifstream hws("/tmp/.def");
	if (!hws || ret != 0)
    {
		KMessageBox::error(parentWidget(), tr2i18n("Cannot query default connection"));
		exit(-1);
    }

	// Listing Hardwares:
	char szBuffer[0xFF];
	hws.getline(szBuffer, 0xFF);
	hws.close();

	QString qDefault = QString(szBuffer);
	
	ret = system("internet -C > /tmp/.cons");

	hws.open("/tmp/.cons");
	if (!hws || ret != 0)
    {
		KMessageBox::error(parentWidget(), tr2i18n("Cannot query connections list"));
		exit(-1);
    }

	// Listing Hardwares:
	hws.getline(szBuffer, 0xFF);

	// clear-n'-fill the combo-box
	while (comboConnections->count())
		comboConnections->removeItem(0);		// clear

	while (!hws.eof())
	{
		hws.getline(szBuffer, 0xFF);

		if (strlen(szBuffer))
		{
			// We don't want a 'default' entry
			if (strcmp(szBuffer, "default"))
			{
				if (QString(szBuffer) == qDefault)
					comboConnections->insertItem(QString(szBuffer), 0);

				else comboConnections->insertItem(szBuffer);
			}
		}
	}

	hws.close();
	comboConnections->setCurrentItem(0);
}

void idialer::onGo()
{	
	textStdout->setText(tr2i18n("Exectuing..."));
	// Disable all
	setWorking(true);

	// Do your thing..
	QString qTab = tabWidget2->label(tabWidget2->currentPageIndex());
	if (qTab == tr2i18n("Connect"))
	{
		// It's easy..
		if (checkInit->isChecked())
		{
			textStdout->setText(textStdout->text() + tr2i18n("\nInitializing..."));
			QString qCmd = "internet --init=\"" + comboConnections->currentText() + QString("\"");
			if (system(qCmd))
			{
				// YES! That's a GOTO!
				// I'm too lazy to create a function for it... maybe l8er...
				KMessageBox::error(parentWidget(), tr2i18n("Cannot initialize connection!"));
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nFailed."));
			}
		}

		if (checkBoot->isChecked())
		{
			textStdout->setText(textStdout->text() + tr2i18n("\nBooting..."));
			QString qCmd = "internet --boot=\"" + comboConnections->currentText() + QString("\"");
			if (system(qCmd))
			{
				// YES! That's a GOTO!
				// I'm too lazy to create a function for it... maybe l8er...
				KMessageBox::error(parentWidget(), tr2i18n("Cannot boot connection!"));
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nFailed."));
			}
		}

		if (checkConnect->isChecked())
		{
			textStdout->setText(textStdout->text() + tr2i18n("\nConnecting..."));
			QString qCmd = "internet --connect=\"" + comboConnections->currentText() + QString("\"");
			if (system(qCmd))
			{
				// YES! That's a GOTO!
				// I'm too lazy to create a function for it... maybe l8er...
				KMessageBox::error(parentWidget(), tr2i18n("Cannot connect!"));
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nFailed."));
			}
		}

		if (checkDisconnect->isChecked())
		{
			textStdout->setText(textStdout->text() + tr2i18n("\nDisconnecting..."));
			QString qCmd = "internet --kill=\"" + comboConnections->currentText() + QString("\"");
			if (system(qCmd))
			{
				// YES! That's a GOTO!
				// I'm too lazy to create a function for it... maybe l8er...
				KMessageBox::error(parentWidget(), tr2i18n("Cannot disconnect!"));
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nFailed."));
			}
		}
	}

	else if (qTab == tr2i18n("Advanced"))
	{
	}

	// Enable all
	setWorking(false);
	textStdout->setText(textStdout->text() + tr2i18n("\nDone."));
}


void idialer::onNewConnection(const QString &qs)
{
	if (0) { qs.find(""); }
	textStdout->setText("");
}


void idialer::onNewAction(const QString &qs)
{
	if (0) { qs.find(""); }
}


void idialer::setWorking( bool b )
{
	pushGo->setEnabled(!b);
	comboConnections->setEnabled(!b);
	checkInit->setEnabled(!b);
	checkBoot->setEnabled(!b);
	checkConnect->setEnabled(!b);
	checkDisconnect->setEnabled(!b);
	comboActions->setEnabled(!b);
	tabWidget2->setEnabled(!b);
	comboParam1->setEnabled(!b);
	lineParam2->setEnabled(!b);
}
