/***************************************************************************
 *   Copyright (C) 2003 by Nir Misgav                                      *
 *   nirro@linux-kinneret.org                                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <kconfig.h>
#include <ksimpleconfig.h>
#include "theme.h"
#include <kipc.h>
#include <kiconloader.h>
#include <kicontheme.h>
#include <kmessagebox.h>
#include <klocale.h>
#include <qstringlist.h>
#include <qstylefactory.h>
#include <qdir.h>
#include <kdesktopfile.h>
#include <kstandarddirs.h>
#include <kapp.h>
#include <dcopclient.h>
//#include <kdebug.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include "krdb.h"
#include <kprocess.h>

void theme::load(QString filename)
{
	path = filename.left(filename.findRev("/")+1);
	file = filename.right(filename.length()-filename.findRev("/")-1);
	KConfig config(filename);
	config.setGroup("General");
	name = config.readEntry("name");
	description = config.readEntry("description");
	version = config.readEntry("version");
}

void theme::save(QString pt, QString fn,QString nm,QString vr,QString ds)
{
	path = pt;
	KStandardDirs::makeDir(path);
	file = fn+".knrt";
	KSimpleConfig themeConfig(path+file);
	themeConfig.setGroup("General");
	themeConfig.writeEntry("name",nm);
	themeConfig.writeEntry("description",ds);
	themeConfig.writeEntry("version",vr);

	KConfig kdeglobals("kdeglobals");
	KConfig desktoprc(desktopFileName());
	KConfig kwinrc("kwinrc");
	KConfig konqrc("konquerorrc");
	copyIcons(&kdeglobals,&themeConfig,2);
	copyBackground(&desktoprc,&themeConfig);
	copyFMSettings(&desktoprc, "FMSettings", &themeConfig, "FMSettings Desktop");
	copyFMSettings(&konqrc, "FMSettings", &themeConfig, "FMSettings Konq");
	bool styleChanged,effectChanged,macStyleChanged,toolbarChanged;
	copyStyle(&kdeglobals, &themeConfig, 2,&styleChanged,&effectChanged,&macStyleChanged,&toolbarChanged);
	copyWinDecoration(&kwinrc, &themeConfig);
	copyColors(&kdeglobals, &themeConfig,2);
	themeConfig.sync();
}

void theme::apply()
{
	KConfig kdeglobals("kdeglobals");
	KSimpleConfig themeConfig(path+file);
	KConfig desktoprc(desktopFileName());
	KConfig kwinrc("kwinrc");
	KConfig konqrc("konquerorrc");

	bool iconChanged=copyIcons(&themeConfig,&kdeglobals,1);
	bool backgroundChanged=copyBackground(&themeConfig,&desktoprc);
	bool FMsettingsDTChanged=copyFMSettings(&themeConfig,"FMSettings Desktop", &desktoprc,"FMSettings");
	bool FMsettingsKNChanged=copyFMSettings(&themeConfig,"FMSettings Konq", &konqrc,"FMSettings");
	bool styleChanged,effectChanged,macStyleChanged,toolbarChanged;
	copyStyle(&themeConfig, &kdeglobals, 1, &styleChanged, &effectChanged, &macStyleChanged, &toolbarChanged);
	bool windecChanged=copyWinDecoration(&themeConfig, &kwinrc);
	bool colorsChanged=copyColors(&themeConfig, &kdeglobals,1);

	kdeglobals.sync();
	desktoprc.sync();
	kwinrc.sync();
	konqrc.sync();

	if (FMsettingsKNChanged) applyKonq();
	if (iconChanged) applyIcons();
	if (backgroundChanged) applyBackground();
	if ((FMsettingsDTChanged)&&(!iconChanged)) applyFonts();
	if (windecChanged) applyWinDecoration();
	applyStyle(styleChanged,effectChanged,macStyleChanged,toolbarChanged);
	if (colorsChanged) applyColors();
}

void theme::copyStyle(KConfig *from, KConfig *to,int action, bool *styleChanged,
			bool *effectChanged, bool *macStyleChanged, bool *toolbarChanged)
{
	// Changing Widget Style
	QStringList styles = QStyleFactory::keys();
	bool styleValid=false;
	*styleChanged=false;
	*effectChanged=false;
	*macStyleChanged=false;
	*toolbarChanged=false;
	KConfig *kdeglobals=NULL;
	KConfig *themeConfig=NULL;
	if (action==1) //apply
	{
		kdeglobals=to;
		themeConfig=from;
 	} else if (action==2) //save new
	{
		kdeglobals=from;
		themeConfig=to;
	}
	else return;

	kdeglobals->setGroup("General");
	themeConfig->setGroup("Style");

	QString widgetStyle=from->readEntry("widgetStyle");
	for (QStringList::iterator it = styles.begin(); it != styles.end(); it++)
		if (widgetStyle.compare(*it) == 0) styleValid=true;
	if (styleValid)
	{
		*styleChanged |=copyEntry(from,to,"widgetStyle");
		kdeglobals->setGroup("KDE");
		if (copyEntry(from,to,"EffectsEnabled"))
			{*styleChanged=true; *effectChanged=true;}
		static const QString effects[7]={"EffectAnimateCombo","EffectAnimateTooltip","EffectFadeTooltip",
				"EffectAnimateMenu","EffectFadeMenu","ShowIconsOnPushButtons","EffectNoTooltip"};
		for (int i=0; i<7; i++) *effectChanged |= copyEntry(from,to,effects[i]);
		*macStyleChanged |= copyEntry(from,to,"macStyle");
		themeConfig->setGroup("Style Toolbar");
		kdeglobals->setGroup("Toolbar style");
		*toolbarChanged |= copyEntry(from,to,"Highlighting");
		*toolbarChanged |= copyEntry(from,to,"TransparentMoving");
		*toolbarChanged |= copyEntry(from,to,"IconText");

		QSettings settings;
		themeConfig->setGroup("Style");
		if (action==1)
		{
			*styleChanged |= copyEntry(from, "MenuTransparencyEngine", &settings, "/KStyle/Settings/MenuTransparencyEngine");
			*styleChanged |= copyEntry(from,"MenuOpacity",&settings,"/KStyle/Settings/MenuOpacity");
			*styleChanged |= copyEntry(from,"MenuDropShadow", &settings, "/KStyle/Settings/MenuDropShadow");
		}
		else
		{
			copyEntry(&settings,"/KStyle/Settings/MenuTransparencyEngine",to,"MenuTransparencyEngine");
			copyEntry(&settings,"/KStyle/Settings/MenuOpacity",to,"MenuOpacity");
			copyEntry(&settings,"/KStyle/Settings/MenuDropShadow",to,"MenuDropShadow");
		}
	}
	else KMessageBox::error(0,i18n("Widget style %1 is not valid").arg(widgetStyle));
}

void theme::applyStyle(bool styleChanged, bool effectChanged, bool macStyleChanged, bool toolbarChanged)
{
	if (styleChanged||effectChanged)
	{
		uint flags = KRdbExportQtSettings;
		KConfig kconfig("kcmdisplayrc", true /*readonly*/, false /*no globals*/);
		kconfig.setGroup("X11");
		bool exportKDEColors = kconfig.readBoolEntry("exportKDEColors", true);
		if (exportKDEColors) flags |= KRdbExportColors;
		runRdb( flags );
	}
	if (styleChanged) KIPC::sendMessageAll(KIPC::StyleChanged);
	if (macStyleChanged) kapp->dcopClient()->send("kdesktop", "KDesktopIface", "configure()", QByteArray());
	if ( toolbarChanged || macStyleChanged )
	// ##### FIXME - Doesn't apply all settings correctly due to bugs in
	// KApplication/KToolbar
	KIPC::sendMessageAll(KIPC::ToolbarStyleChanged);
	if (effectChanged)
	{
		KIPC::sendMessageAll(KIPC::SettingsChanged);
		kapp->dcopClient()->send("kwin*", "", "reconfigure()", "");
	}
	//update kicker to re-used tooltips kicker parameter otherwise, it overwritted
	//by style tooltips parameters.
	QByteArray data;
	kapp->dcopClient()->send( "kicker", "kicker", "configure()", data );
}

bool theme::copyIcons(KConfig *from, KConfig *to,int action)
{
	KConfig *kdeglobals=NULL;
	KConfig *themeConfig=NULL;

	static const QString IconsEntries[] = { "ActiveColor","ActiveEffect","ActiveSemiTransparent","ActiveValue",
			"Animated","DefaultColor","DefaultEffect","DefaultSemiTransparent","DefaultValue","DisabledColor",
			"DisabledEffect","DisabledSemiTransparent","DisabledValue","DoublePixels","Size"};
	static const QString iconsGroups[] = { "Desktop", "Toolbar", "MainToolbar", "Small", 0L };

	if (action==1) //apply
	{
		kdeglobals=to;
		themeConfig=from;
 	} else if (action==2) //save new
	{
		kdeglobals=from;
		themeConfig=to;
	}
	else return false;

	from->setGroup("Icons");
	to->setGroup("Icons");
	QString iconset=from->readEntry("Theme","");
	bool changed=false;
	if ((iconset.isEmpty())||(KIconTheme(iconset).isValid()))
	{
		changed |= copyEntry(from,to,"Theme");
		for (KIcon::Group i=KIcon::FirstGroup; i<KIcon::LastGroup; i++)
		{
			if (iconsGroups[i] == 0L) break;
			kdeglobals->setGroup(iconsGroups[i] + "Icons");
			themeConfig->setGroup("Icons "+iconsGroups[i]);
			for(int j=0;j<15;j++) changed |= copyEntry(from, to, IconsEntries[j]);
		}
	}
	else KMessageBox::error(0,i18n("Iconset %1 is not valid").arg(iconset));
	return changed;
}

void theme::applyIcons()
{
	for (int i=0; i<KIcon::LastGroup; i++) KIPC::sendMessageAll(KIPC::IconChanged,i);
}

bool theme::copyWinDecoration(KConfig *from, KConfig *to)
{
	// Window decorations
	bool changed=false;
	findDecorations();
	// Check if winDecoration is valid
	bool decorationValid=false;
	QValueList<DecorationInfo>::ConstIterator it;
	// Check if decoration is valid
	to->setGroup("Style");
	from->setGroup("Style");
	QString winDecoration=from->readEntry("PluginLib");
	for (it = decorations.begin(); it != decorations.end(); it++)
	{
		DecorationInfo info = *it;
		if (info.libraryName.compare(winDecoration) == 0) decorationValid=true;
	}
	// Change decoration
	if (decorationValid) changed |= copyEntry(from,to,"PluginLib");
	else KMessageBox::error(0,i18n("Window Decoration %1 is not valid").arg(winDecoration));
	return changed;
}

void theme::applyWinDecoration()
{
	kapp->dcopClient()->send("kwin", "KWinInterface", "reconfigure()", QByteArray());
}

void theme::findDecorations()
{
	QStringList dirList = KGlobal::dirs()->findDirs("data", "kwin");
	QStringList::ConstIterator it;

	for (it = dirList.begin(); it != dirList.end(); it++)
	{
		QDir d(*it);
		if (d.exists())
			for (QFileInfoListIterator it(*d.entryInfoList()); it.current(); ++it)
			{
				QString filename(it.current()->absFilePath());
				if (KDesktopFile::isDesktopFile(filename))
				{
					KDesktopFile desktopFile(filename);
					QString libName = desktopFile.readEntry("X-KDE-Library");

					if (!libName.isEmpty())
					{
						DecorationInfo di;
						di.name = desktopFile.readName();
						di.libraryName = libName;
						decorations.append( di );
					}
				// Adding the decoration KDE1
				DecorationInfo kde1;
				kde1.name = "KDE 1";
				kde1.libraryName = "kwin_kde1";
				decorations.append( kde1 );
				}
			}
	}
}

bool theme::copyBackground(KConfig *from,KConfig *to)
{
	// copy common entries
	bool changed=false;
	changed |= copyBackgroundCommon(from, to);
	// copy desktop fonts settings
	changed |= copyAllDesktops(from, to);
	return changed;
}

void theme::applyBackground()
{
	DCOPClient *client = kapp->dcopClient();
	if (!client->isAttached()) client->attach();
	client->send(desktopAppName(), "KBackgroundIface", "configure()", "");
}

void theme::applyFonts()
{
	KIPC::sendMessageAll(KIPC::FontChanged);
}

void theme::applyKonq()
{
    QByteArray data;
    if ( !kapp->dcopClient()->isAttached() )
      kapp->dcopClient()->attach();
    kapp->dcopClient()->send( "konqueror*", "KonquerorIface", "reparseConfiguration()", data );
}

bool theme::copyColors(KConfig *from, KConfig *to, int action)
{
	static const QString colorsGeneral[]={ "background", "selectBackground", "foreground", "windowForeground",
		"windowBackground", "selectForeground", "buttonBackground", "buttonForeground", "linkColor",
		"visitedLinkColor", "alternateBackground"};
	static const QString colorsWM[]={"activeForeground", "inactiveBackground", "inactiveBlend", "activeBackground",
		"activeBlend", "inactiveForeground", "activeTitleBtnBg", "inactiveTitleBtnBg"};

	bool changed=false;
	KConfig *themeConfig=NULL;
	KConfig *kdeglobals=NULL;
	if (action==1) //Applying
	{
		themeConfig=from;
		kdeglobals=to;
	}
	else if (action==2) //Saving new
	{
		themeConfig=to;
		kdeglobals=from;
	}
	else return false;

	kdeglobals->setGroup("General");
	themeConfig->setGroup("Colors General");
	for(int j=0;j<11;j++)
	changed |= copyEntry(from,to,colorsGeneral[j]);
	kdeglobals->setGroup("WM");
	themeConfig->setGroup("Colors WM");
	for(int j=0;j<8;j++) changed |= copyEntry(from,to,colorsWM[j]);
	kdeglobals->setGroup("KDE");
	themeConfig->setGroup("Colors KDE");
	changed |= copyEntry(from,to,"contrast");
	changed |= copyEntry(from,to,"colorScheme");
	KConfig cfg2("kcmdisplayrc", true, false);
	cfg2.setGroup("X11");
	if (action==1) changed |= copyEntry(themeConfig, &cfg2, "exportKDEColors");
	else copyEntry(&cfg2, themeConfig, "exportKDEColors");
	return changed;
}

void theme::applyColors()
{
	// Apply changes to colors.
	KConfig cfg2("kcmdisplayrc", false, false);
	cfg2.setGroup("X11");
	bool exportColors = cfg2.readEntry("exportKDEColors");
	QApplication::syncX();
	uint flags = KRdbExportQtColors;
	if ( exportColors ) flags |= KRdbExportColors;
	else
	{
		// Undo the property xrdb has placed on the root window (if any),
		// i.e. remove all entries, including ours
		Atom resource_manager;
		resource_manager = XInternAtom( qt_xdisplay(), "RESOURCE_MANAGER", True);
		if (resource_manager != None)
				XDeleteProperty( qt_xdisplay(), qt_xrootwin(), resource_manager);
		// and run xrdb with ~/.Xdefaults at least to get non-KDE defaults
		KProcess proc;
		proc << "xrdb" << ( QDir::homeDirPath() + "/.Xdefaults" );
		proc.start( KProcess::Block, KProcess::Stdin );
	}
	runRdb( flags );	// Save the palette to qtrc for KStyles

	// Notify all KDE applications
	KIPC::sendMessageAll(KIPC::PaletteChanged);
	// KMessageBox::information(0,"Changed Colors");
}

bool theme::copyDesktop(int desktop,  KConfig *from, KConfig *to)
{
	QString Group=QString("Desktop%1").arg(desktop);
	from->setGroup(Group);
	to->setGroup(Group);
	bool changed=false;
	QString entries[17]={"color1","color2","Pattern","Program","BackgroundMode",
	"Wallpaper","WallpaperMode","MultiWallpaperMode","BlendMode","BlendBalance",
	"ReverseBlending","MinOptimizationDepth","UseSHM","WallpaperList",
	"ChangeInterval","LastChange","CurrentWallpaper"};
	// Copy entries
	for (int i=0;i<17;i++) changed |= copyEntry(from, to, entries[i]);
	return changed;
}

bool theme::copyAllDesktops(KConfig *from, KConfig *to)
{
	bool changed=false;
	for (int j=0;j<8;j++)
	{
		QString desktop=QString("Desktop%1").arg(j);
		if (from->hasGroup(desktop)) changed |=copyDesktop(j,from,to);
		else changed |= to->deleteGroup(desktop);
	}
	return changed;
}

bool theme::copyBackgroundCommon(KConfig *from, KConfig *to)
{
	from->setGroup("Background Common");
	to->setGroup("Background Common");
	bool changed=false;
	QString entries[5]={"CommonDesktop","Dock","Export","LimitCache","CacheSize"};
	// Copy entries
	for (int i=0;i<5;i++) changed |= copyEntry(from, to, entries[i]);
	return changed;
}

bool theme::copyFMSettings(KConfig *from, QString fromGroup, KConfig *to,QString toGroup)
{
	from->setGroup(fromGroup);
	to->setGroup(toGroup);
	bool changed=false;
	QString entries[3]={"ItemTextBackground","NormalTextColor","UnderlineLinks"};//"StandardFont"};
	// Copy entries
	for (int i=0;i<3;i++) changed |= copyEntry(from, to,entries[i]);
	return changed;
}

bool theme::copyEntry(KConfig *from,QString fromEntry, KConfig *to, QString toEntry)
{
	QString current=to->readEntry(toEntry,"");
	QString toput=from->readEntry(fromEntry,"");
	if (current.compare(toput)==0) return false;
	to->writeEntry(toEntry,toput);
	return true;
}

bool theme::copyEntry(QSettings *from,QString fromEntry, KConfig *to, QString toEntry)
{
	QString current=to->readEntry(toEntry);
	QString toput=from->readEntry(fromEntry);
	if (current.compare(toput)==0) return false;
	to->writeEntry(toEntry,toput);
	return true;
}

bool theme::copyEntry(KConfig *from,QString fromEntry, QSettings *to, QString toEntry)
{
	QString current=to->readEntry(toEntry);
	QString toput=from->readEntry(fromEntry);
	if (current.compare(toput)==0) return false;
	to->writeEntry(toEntry,toput);
	return true;
}

QCString theme::desktopAppName()
{
	int screen_number = 0;
	if (qt_xdisplay()) screen_number = DefaultScreen(qt_xdisplay());
    if (screen_number == 0) return  (QCString("kdesktop"));
    QCString appname;
	appname.sprintf("kdesktop-screen-%d",screen_number);
	return appname;
}
