/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <fstream>
#include <iostream>

#include <kmessagebox.h>
#include <klineedit.h>

void idialer::init()
{
	// Fill with connections

	// which is the default connection?
	int ret = system("internet --defaultshow > /tmp/.def");
	std::ifstream hws("/tmp/.def");
	if (!hws || ret != 0)
    	KMessageBox::error(parentWidget(), tr2i18n("Cannot query default connection"));

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
				return;
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
				return;
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
				return;
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
				return;
			}
		}
	}

	else if (qTab == tr2i18n("Advanced"))
	{
		QString qAction = comboActions->currentText();

		if (qAction == tr2i18n("List ISPs"))
		{
			kProc.clearArguments();
			disconnect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), this, SLOT(onGoStdout(KProcess*, char*, int)));
			disconnect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), this, SLOT(onStdout(KProcess*, char*, int)));
				
			kProc << "internet" << "--listisps";
			connect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)),
				SLOT(onGoStdout(KProcess*, char*, int)));

			textStdout->setText(textStdout->text() + QString("\n"));
				
			if (kProc.start(KProcess::Block, KProcess::Stdout) == false)
			{
				KMessageBox::error(parentWidget(), tr2i18n("Cannot get ISPs list!"));
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nFailed."));
				return;
			}
		}

		else if (qAction == tr2i18n("List Hardwares"))
		{
			kProc.clearArguments();
			disconnect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), this, SLOT(onGoStdout(KProcess*, char*, int)));
			disconnect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), this, SLOT(onStdout(KProcess*, char*, int)));

			kProc << "internet" << "--listhws" << comboParam1->currentText().lower();
			connect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)),
				SLOT(onGoStdout(KProcess*, char*, int)));

			textStdout->setText(textStdout->text() + QString("\n"));

			if (kProc.start(KProcess::Block, KProcess::Stdout) == false)
			{
				KMessageBox::error(parentWidget(), tr2i18n("Cannot get hardwares list!"));
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nFailed."));
				return;
			}
		}

		else if (qAction == tr2i18n("Get Info on Hardware"))
		{
			kProc.clearArguments();
			disconnect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), this, SLOT(onGoStdout(KProcess*, char*, int)));
			disconnect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), this, SLOT(onStdout(KProcess*, char*, int)));

			kProc << "internet" << "--hwinfo" << comboParam1->currentText();
			connect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)),
				SLOT(onGoStdout(KProcess*, char*, int)));

			textStdout->setText(textStdout->text() + QString("\n"));

			if (kProc.start(KProcess::Block, KProcess::Stdout) == false)
			{
				KMessageBox::error(parentWidget(), tr2i18n("Cannot get hardware info!"));
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nFailed."));
				return;
			}
		}

		else if (qAction == tr2i18n("Get Info on ISP"))
		{
			kProc.clearArguments();
			disconnect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), this, SLOT(onGoStdout(KProcess*, char*, int)));
			disconnect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), this, SLOT(onStdout(KProcess*, char*, int)));

			kProc << "internet" << "--ispinfo" << comboParam1->currentText().left(comboParam1->currentText().find(" "));
			connect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)),
				SLOT(onGoStdout(KProcess*, char*, int)));

			textStdout->setText(textStdout->text() + QString("\n"));

			if (kProc.start(KProcess::Block, KProcess::Stdout) == false)
			{
				KMessageBox::error(parentWidget(), tr2i18n("Cannot get hardware info!"));
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nFailed."));
				return;
			}
		}

		else if (qAction == tr2i18n("Delete Current Connection"))
		{
			if (KMessageBox::questionYesNo(parentWidget(), tr2i18n("Are you sure you want to delete current connection?")) == KMessageBox::No)
			{
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nCanceled by user."));
				return;
			}
			
			QString qCmd = QString("internet --force --delete \"") + comboConnections->currentText() + QString("\"");
			if (system(qCmd))
			{
				KMessageBox::error(parentWidget(), tr2i18n("Cannot delete connection!"));
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nFailed."));
				return;
			}

			comboConnections->removeItem(comboConnections->currentItem());
		}

		else if (qAction == tr2i18n("Set Current Connection as Default"))
		{
			if (KMessageBox::questionYesNo(parentWidget(), tr2i18n("Are you sure you want to set current connection to default?")) == KMessageBox::No)
			{
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nCanceled by user."));
				return;
			}

			QString qCmd = QString("internet --default \"") + comboConnections->currentText() + QString("\"");
			if (system(qCmd))
			{
				KMessageBox::error(parentWidget(), tr2i18n("Cannot set connection to default!"));
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nFailed."));
				return;
			}
		}

		else if (qAction == tr2i18n("Extract a Script from Current Connection"))
		{
			QString qCmd = QString("internet --extract=") + comboParam1->currentText() + QString(" \"") + comboConnections->currentText() + QString("\" \"") + lineParam2->lineEdit()->text() + QString("\"");
			if (system(qCmd))
			{
				KMessageBox::error(parentWidget(), tr2i18n("Cannot set connection to default!"));
				setWorking(false);
				textStdout->setText(textStdout->text() + tr2i18n("\nFailed."));
				return;
			}
		}
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
	QString qAction = comboActions->currentText();

	if (qAction == tr2i18n("List ISPs"))
	{
		textParam1Text->setText(QString::null);
		textParam2Text->setText(QString::null);

		comboParam1->setEnabled(false);
		lineParam2->setEnabled(false);
	}

	else if (qAction == tr2i18n("List Hardwares"))
	{
		textParam1Text->setText("Hardware Type");
		textParam2Text->setText(QString::null);

		comboParam1->setEnabled(true);
		lineParam2->setEnabled(false);

		comboParam1->clear();
		comboParam1->insertItem(QString("Broadband"));
		comboParam1->insertItem(QString("ISDN"));
		comboParam1->insertItem(QString("Dialup"));
	}

	else if (qAction == tr2i18n("Get Info on Hardware"))
	{
		textParam1Text->setText("Hardware Name");
		textParam2Text->setText(QString::null);

		comboParam1->setEnabled(true);
		lineParam2->setEnabled(false);

		// fill with hardware names
		comboParam1->clear();

		kProc.clearArguments();
		disconnect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), this, SLOT(onGoStdout(KProcess*, char*, int)));
		disconnect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), this, SLOT(onStdout(KProcess*, char*, int)));

		kProc << "internet" << "--listhws=broadband";
		connect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), SLOT(onStdout(KProcess*, char*, int)));
		if (kProc.start(KProcess::Block, KProcess::Stdout) == false)
		{
			KMessageBox::error(parentWidget(), tr2i18n("Cannot get hardware list!"));
			exit(-1);
		}
	}

	else if (qAction == tr2i18n("Get Info on ISP"))
	{
		textParam1Text->setText("ISP Name");
		textParam2Text->setText(QString::null);

		comboParam1->setEnabled(true);
		lineParam2->setEnabled(false);

		// fill with hardware names
		comboParam1->clear();

		kProc.clearArguments();
		disconnect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), this, SLOT(onGoStdout(KProcess*, char*, int)));
		disconnect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), this, SLOT(onStdout(KProcess*, char*, int)));

		kProc << "internet" << "--listisps";
		connect(&kProc, SIGNAL(receivedStdout(KProcess*, char*, int)), SLOT(onStdout(KProcess*, char*, int)));
		if (kProc.start(KProcess::Block, KProcess::Stdout) == false)
		{
			KMessageBox::error(parentWidget(), tr2i18n("Cannot get ISPs list!"));
			exit(-1);
		}
	}

	else if (qAction == tr2i18n("Delete Current Connection"))
	{
		textParam1Text->setText(QString::null);
		textParam2Text->setText(QString::null);

		comboParam1->setEnabled(false);
		lineParam2->setEnabled(false);
	}

	else if (qAction == tr2i18n("Set Current Connection as Default"))
	{
		textParam1Text->setText(QString::null);
		textParam2Text->setText(QString::null);

		comboParam1->setEnabled(false);
		lineParam2->setEnabled(false);
	}

	else if (qAction == tr2i18n("Extract a Script from Current Connection"))
	{
		textParam1Text->setText("Script Name");
		textParam2Text->setText("To File...");

		comboParam1->setEnabled(true);
		lineParam2->setEnabled(true);

		comboParam1->clear();
		comboParam1->insertItem(QString("init"));
		comboParam1->insertItem(QString("boot"));
		comboParam1->insertItem(QString("connect"));
		comboParam1->insertItem(QString("disconnect"));
	}
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

void idialer::onStdout( KProcess *proc, char *szBuffer, int nLen )
{
	if (0) { std::cout << nLen; proc->start(); }
	QString qAction = comboActions->currentText();

	if (qAction == tr2i18n("Get Info on Hardware"))
	{
		QString qOut = QString(szBuffer);
		QString qHW;

		while (!qOut.isEmpty())
		{
			qHW = qOut.left(qOut.find("\n"));

			if (qHW != "Listing Hardwares:")
				comboParam1->insertItem(qHW);

			qOut = qOut.remove(0, qOut.find("\n") + 1);
		}
	}

	else if (qAction == tr2i18n("Get Info on ISP"))
	{
		QString qOut = QString(szBuffer);
		QString qHW;

		while (!qOut.isEmpty())
		{
			qHW = qOut.left(qOut.find("\n"));

			if (qHW != "Listing ISPs:")
				comboParam1->insertItem(qHW);

			qOut = qOut.remove(0, qOut.find("\n") + 1);
		}
	}
}


void idialer::onGoStdout( KProcess *proc, char *buffer, int len )
{
	if (0) { std::cout << len; proc->start(); }
	textStdout->setText(textStdout->text() + QString(buffer));
}
