/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
#include <iostream>	// for cerr and cout
#include <map>
#include <string>
#include <fstream>

#include <unistd.h>
#include <stdlib.h>		// for system(...)

#include <kmessagebox.h>

void iwizard::init()
{
	// we are assuming 'internet' is in $PATH
	// first we have to fill up lists (ISPs, modems etc.)
	// for that, we will invoke the tool, and read it's output.
    
	// first list: ISPs...
	int ret = system("internet --listisps > /tmp/.isps");
    
	// the output is from the form: cname%0020%-%0020%name
	// we will fill mapISPs with the pair [name,cname]
	char szBuffer[0xFF];	// line buffer
	std::ifstream isps("/tmp/.isps");
	if (!isps || ret != 0)
	{
		KMessageBox::error(parentWidget(), tr2i18n("Cannot query ISPs"));
		exit(-1);
	}
    
	// Listing ISPs:
	isps.getline(szBuffer, 0xFF);
    
	while (!isps.eof())
	{
		isps.getline(szBuffer, 0xFF);
		QString qLine = QString(szBuffer);
	
		if (!qLine.isEmpty())
		{
		    qLine = qLine.simplifyWhiteSpace();
	
			QString qName, qCName;
			qCName = qLine.left(qLine.find(' '));

			qLine = qLine.remove(0, qLine.find(' ') + 1);	// cname
			qLine = qLine.remove(0, qLine.find(' ') + 1);	// -

			qName = qLine;
	
			mapISPs[std::string(qName.ascii())] = std::string(qCName.ascii());
		}
	}
    
	isps.close();
	unlink("/tmp/.isps");
    
	// clear-n'-fill the combo-box
	while (comboISPs->count()) comboISPs->removeItem(0);	// clear
    
	std::map<std::string, std::string>::iterator iter;
	for (iter = mapISPs.begin() ; iter != mapISPs.end() ; iter++)
		comboISPs->insertItem(QString(iter->first.c_str()));
	comboISPs->setCurrentItem(0);
    
    // now, list modems
    ret = system("internet --listhws broadband > /tmp/.hws");
    
    std::ifstream hws("/tmp/.hws");
    if (!hws || ret != 0)
    {
		KMessageBox::error(parentWidget(), tr2i18n("Cannot query hardware"));
		exit(-1);
    }
    
	// Listing Hardwares:
	hws.getline(szBuffer, 0xFF);
   
	// clear-n'-fill the combo-box
	while (comboModems->count()) comboModems->removeItem(0);		// clear
    
	bool bFirst = false;
    
	while (!hws.eof())
	{
		hws.getline(szBuffer, 0xFF);

		if (strlen(szBuffer))
		{
			comboModems->insertItem(szBuffer);

			// if this is the first modem that is readed, make sure the
			// devices settings are accordingly
			if (!bFirst)
			{
				bFirst = true;
				onModemChanged(szBuffer);
			}
		}
	}
   
	hws.close();
	unlink("/tmp/.hws");
	comboModems->setCurrentItem(0);
    
	// fill ethernet's combo box
	// count how many times the string 'eth' appears in /proc/net/dev
	ret = system("cat /proc/net/dev | grep eth > /tmp/.eths");

	while (comboEth->count()) comboEth->removeItem(0);		// clear
	while (comboLANEth->count()) comboLANEth->removeItem(0);		// clear    

	std::ifstream eths("/tmp/.eths");
	if (!eths || ret != 0)
	{
		KMessageBox::error(parentWidget(), tr2i18n("Cannot query ethernet devices"));
		//exit(-1);
	}
	
	else
	{
		while (!eths.eof())
		{
			eths.getline(szBuffer, 0xFF);
			if (strlen(szBuffer))
			{
				szBuffer[6] = 0;
				comboEth->insertItem(&szBuffer[2]);
				comboLANEth->insertItem(&szBuffer[2]);
			}
		}
	    
		eths.close();
		comboEth->setCurrentItem(0);
		comboLANEth->setCurrentItem(0);
	}

	unlink("/tmp/.eths");

	// Kinneret autodetect
	std::ifstream kinneret("/opt/kinneret/bin/config.sh", std::ios::in);
	if (!kinneret) return;		// says it all, isn't it? :)

	// It's Kinneret, remove the distro step and set to Debian based.
	kinneret.close();
	radioDebian->setChecked(true);
	radioDebian->setEnabled(false);
	radioNonDebian->setEnabled(false);
}


void iwizard::onEthClick(int stat)
{
	if (stat == QButton::On)
	{
		comboEth->setEnabled(true);
		lineUSBModule->setEnabled(false);
		lineUSBEth->setEnabled(false);
    }
    
	else if (stat == QButton::Off)
	{
		comboEth->setEnabled(false);
		lineUSBModule->setEnabled(true);
		lineUSBEth->setEnabled(true);
	}
}

void iwizard::onModemChanged(const QString &qs)
{
	// load the modem, and see it's interface.
	QString qCmd = "internet --hwinfo \"" + qs + "\" | grep Interface: > /tmp/.hwtype";
	int ret = system(qCmd);
    
	std::ifstream type("/tmp/.hwtype");
	if (!type || ret != 0)
    {
		KMessageBox::error(parentWidget(), tr2i18n("Cannot get modem type"));
		exit(-1);
	}
    
	char szBuffer[0xFF];
	type.getline(szBuffer, 0xFF);    
	type.close();
	unlink("/tmp/.hwtype");

	if (strcmp(szBuffer, "Interface: Ethernet") == 0)
	{
		onEthClick(QButton::On);
		radioEthernet->setEnabled(false);
		radioUSB->setEnabled(false);
	
		radioEthernet->setChecked(true);
		radioUSB->setChecked(false);
	}
    
	if (strcmp(szBuffer, "Interface: USB") == 0)
	{
		onEthClick(QButton::Off);
		radioEthernet->setEnabled(false);
		radioUSB->setEnabled(false);
	
		radioEthernet->setChecked(false);
		radioUSB->setChecked(true);
    }
    
	if (strcmp(szBuffer, "Interface: Dual, USB or Ethernet") == 0)
	{
		onEthClick(QButton::On);
		radioEthernet->setEnabled(true);
		radioUSB->setEnabled(true);
	
		radioEthernet->setChecked(true);
		radioUSB->setChecked(false);
    }
    
	if (strcmp(szBuffer, "Interface: Unknown") == 0)
	{
		KMessageBox::error(parentWidget(), tr2i18n("Cannot resolve modem type"));
		exit(-1);
    }
}

void iwizard::onTypeChange( int stat )
{
	if (0) { std::cout << stat << std::endl; } // I hate stupid warnings...
	AssembleUsername(comboISPs->currentText());
}


void iwizard::AssembleUsername(const QString &qs)
{
	if (0) { std::cout << qs << std::endl; } // I hate stupid warnings...
	
	// set suffix
	QString qCmd = QString("internet --ispinfo ") + QString(mapISPs[comboISPs->currentText().ascii()].c_str());
    
	// cable or ADSL ?
	if (radioADSL->isChecked()) qCmd += " | grep \"ADSL Username Suffix\" | cut -b 23-";
	else if (radioCable->isChecked()) qCmd += " | grep \"Cable Username Suffix\" | cut -b 24-";
    
	qCmd += " > /tmp/.suffix";
	int ret = system(qCmd);
    
	std::ifstream suffix("/tmp/.suffix");
	if (!suffix || ret != 0)
	{
		KMessageBox::error(parentWidget(), tr2i18n("Cannot get modem type"));
		exit(-1);
	}
    
	char szBuffer[0xFF];
	suffix.getline(szBuffer, 0xFF);
	suffix.close();
	unlink("/tmp/.suffix");

	QString qFinal = QString("(") + lineUsername->text() + QString(szBuffer) + QString(")");

//	std::cout << qFinal.ascii() << std::endl;

	// Parse it...
	std::string str = std::string(qFinal.ascii());

	while (str.find("[*") != std::string::npos)
	{
		std::string::size_type st = str.find("[*");
		std::string::size_type en = str.find("*]");

		std::string name = str.substr(st + 2, en - st - 2);

		if (name == "auth::server") name = std::string(lineServer->text().ascii());
		str.replace(st, en - st + 2, name);
	}

	// set final
	textSuffix->setText(QString(str.c_str()));
}


void iwizard::onNewPage(const QString &qs)
{
	if (0) { std::cout << qs; }

	// skip LAN
	if (currentPage() == QWizard::page(3) && !radioLAN->isChecked() && nPrevPage == 2)
	{
		QWizard::showPage(QWizard::page(4));
		return;
	}

	if (currentPage() == QWizard::page(3) && !radioLAN->isChecked() && nPrevPage == 4)
	{
		QWizard::showPage(QWizard::page(2));
		return;
	}

	// skip broadband stuff
	if (currentPage() == QWizard::page(4) && radioLAN->isChecked() && nPrevPage == 3)
	{
		QWizard::showPage(QWizard::page(5));
		return;
	}

	if (currentPage() == QWizard::page(4) && radioLAN->isChecked() && nPrevPage == 5)
	{
		QWizard::showPage(QWizard::page(3));
		return;
	}

	nPrevPage = indexOf(currentPage());
}


void iwizard::onLAN()
{
	// disable and enable stuff
	comboModems->setEnabled(false);
	lineUsername->setEnabled(false);
	linePassword->setEnabled(false);
	lineServer->setEnabled(false);
}


void iwizard::onADSL()
{
	comboModems->setEnabled(true);
	lineUsername->setEnabled(true);
	linePassword->setEnabled(true);
	lineServer->setEnabled(true);
}


void iwizard::onCables()
{
	onADSL();
}


void iwizard::onISDN()
{

}


void iwizard::onAnalog()
{

}


void iwizard::onFromDHCP()
{
	lineIP->setEnabled(false);
	lineNetmask->setEnabled(false);
	lineBroadcast->setEnabled(false);
	lineGateway->setEnabled(false);
}


void iwizard::onStaticAddress()
{
	lineIP->setEnabled(true);
	lineNetmask->setEnabled(true);
	lineBroadcast->setEnabled(true);
	lineGateway->setEnabled(true);
}
