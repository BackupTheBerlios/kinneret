/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/


void pleasewait::onTimer()
{
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
}
