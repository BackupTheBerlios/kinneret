/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
#include <fstream>

void pleasewait::onTimer()
{
	// update leds
	nLed++;
	if (nLed == 5) nLed = 0;	// warp

	static KLed *leds[] = {
		kLed1, kLed2, kLed3, kLed4, kLed5
	};

	for (int i = 0 ; i < 5 ; i++)
	{
		if (i == nLed) leds[i]->on();
		else leds[i]->off();
	}

	// update text
	QString qMsg;
	std::ifstream f("/tmp/.progress");
	char szLine[0x300];
	f.getline(szLine, 0x300);
	f.close();

	QString qLine = QString(szLine);
	if (qLine == QString("DIR_CREATE"))
		qMsg = QString(tr2i18n("Creating directory... [1/13]"));
	
	else if (qLine == QString("SWAP_FILE"))
		qMsg = QString(tr2i18n("Allocating swap file... [2/13]"));

	else if (qLine == QString("CREATE_SWAP"))
		qMsg = QString(tr2i18n("Creating swap file system... [3/13]"));

	else if (qLine == QString("SWAP_ON"))
		qMsg = QString(tr2i18n("Activating swap file... [4/13]"));

	else if (qLine == QString("HOME_FILE"))
		qMsg = QString(tr2i18n("Allocating home file... [5/13]"));

	else if (qLine == QString("DEVICE_SEARCH"))
		qMsg = QString(tr2i18n("Searching for a free device... [6/13]"));

	else if (qLine == QString("CREATE_HOME"))
		qMsg = QString(tr2i18n("Creating home file system... [7/13]"));

	else if (qLine == QString("TUNE_HOME"))
		qMsg = QString(tr2i18n("Tunning home gile system... [8/13]"));

	else if (qLine == QString("OWN_CHANGE"))
		qMsg = QString(tr2i18n("Changing ownership... [9/13]"));

	else if (qLine == QString("COPY_HOME"))
		qMsg = QString(tr2i18n("Copying home... [10/13]"));

	else if (qLine == QString("RELEASE_HOME"))
		qMsg = QString(tr2i18n("Releasing home device... [11/13]"));

	else if (qLine == QString("ACTIVATE_HOME"))
		qMsg = QString(tr2i18n("Activating home... [12/13]"));

	else if (qLine == QString("FINISH"))
		qMsg = QString(tr2i18n("Finishing... [13/13]"));

	else qMsg = QString(tr2i18n("Working... [N/A]"));

	status->setText(qMsg);
}
