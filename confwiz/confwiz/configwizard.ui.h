/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <kmessagebox.h>
#include <fstream>      // for std::i/ofstream
#include <unistd.h>     // for unlink(...)
#include <qdir.h>
#include <stdio.h>
#include <map>
#include <iostream>
#include <qfiledialog.h>
#include "dirview.h"
#include "pleasewait.h"
#include <kapplication.h>
#include <kprocess.h>
#include <qobjectlist.h>
#include "help.h"

void configwizard::onSelect()
{
	const int page_nicetomeet	= 0;
	const int page_license		= 1;
	const int page_setuptype	= 2;
	const int page_partition	= 3;
	const int page_swap			= 4;
	const int page_homedir		= 5;
	const int page_conclusion	= 6;
	const int page_fonts		= 7;
	const int page_whatsnext	= 8;
		
	// see if that's the 3rd page, if it is,
	// fill the list box with vfat and partitions.
	if (currentPage() == reinterpret_cast<QWizard*>(this)->page(page_partition))
	{
		if (par_list->childCount() == 0)
		{
			// Why oh why did the trolltech people re-wrote the standart library??
			std::ifstream fstab("/etc/fstab", std::ios::in);
			char szLine[0x300];
	
			if (!fstab.is_open())
			{
				KMessageBox::error(parentWidget(),
								   QString(tr2i18n("Cannot open /etc/fstab")));
				return;
			}
	
			par_list->addColumn(QString(tr2i18n("Device")), 150);
			par_list->addColumn(QString(tr2i18n("Size")), 150);
			par_list->addColumn(QString(tr2i18n("Free (% In Use)")), 150);
			
			char Letter[2] = { 'C', 0 };	// first drive is C
	
			while (!fstab.eof())
			{
				fstab.getline(szLine, 0x300);
				if (strstr(szLine, "vfat"))
				{
					char *dev = strstr(szLine, "/dev/");
					char device[20];
					char *devptr = device;
		
					while (isalnum(*dev) || *dev == '/') *devptr++ = *dev++;
		
					*devptr = 0;

					// Mount the device as rw
					QString qCmd = QString("sudo mount ") + QString(device) + QString(" -o defaults,rw,user");

					// Same goes as above regarding KProcess...
					system(qCmd);

					// Get size and freespace
					system("df -Th > /tmp/.df");
					std::ifstream df("/tmp/.df");

					if (!df.is_open())
					{
						KMessageBox::error(parentWidget(), 
							QString(tr2i18n("Cannot get device status, skipping")));
						continue;
					}

					QString mntpt(tr2i18n("N/A"));
					QString size(tr2i18n("N/A"));
					QString free(tr2i18n("N/A (N/A)"));

					while (!df.eof())
					{
						df.getline(szLine, 0x300);
						if (strstr(szLine, device))
						{
							QString qs(szLine);
							qs = qs.simplifyWhiteSpace();
							qs = qs.remove(0, qs.find(' ') + 1);    // device
							qs = qs.remove(0, qs.find(' ') + 1);    // fs

							size = qs.left(qs.find(' '));

							qs = qs.remove(0, qs.find(' ') + 1);    // size
							qs = qs.remove(0, qs.find(' ') + 1);    // used

							free = qs.left(qs.find(' '));

							qs = qs.remove(0, qs.find(' ') + 1);    // Avail
							free += QString(" (") + qs.left(qs.find(' ')) + QString(")");
							qs = qs.remove(0, qs.find(' ') + 1);    // Use%
							mntpt = qs.left(qs.find(' '));
						}
					}
                
					df.close();
					
					// guess the letter of the drive...
					mntpt += QString(" (") + QString(Letter) + QString(":)");
					Letter[0]++;
		
					QListViewItem *vi = new QListViewItem(par_list, mntpt, size, free);

					if (par_list->childCount() == 0) vi->setSelected(true);
					else vi->setSelected(false);
             
					par_list->insertItem(vi);
				}
			}		
			
			fstab.close();
			unlink("/tmp/.df");
		}
		
		// Okay, now we'll see what the user have choose in the previous
		// level and act accordingly...
		if (radioAuto->isChecked())
		{
			// Autodetect best configurations
			// docs_path = Home dir
			// selected item in par_list = mountpoint
			// swap_size's value = swap size
			
			// Find the partition with the largest free space
			std::map<unsigned long, QString> partitions;		// free sapce (bytes), mountpoint
			
			// Get size and freespace
			system("df -t vfat -B 1M > /tmp/.df");
			std::ifstream df("/tmp/.df");
			
			if (!df.is_open())
			{
				KMessageBox::error(parentWidget(), 
					   QString(tr2i18n("Cannot get device status")));
				return;
			}
			
			// first line...
			char szLine[0x300];
			df.getline(szLine, 0x300);

			unsigned long sz = 0;
			while (!df.eof())
			{
				df.getline(szLine, 0x300);

// Filesystem           1M-blocks      Used Available Use% Mounted on
// /dev/hda1                20462     18191      2271  89% /mnt/win

				QString qs(szLine);
				qs = qs.simplifyWhiteSpace();
					
				unsigned long size = 0;
					
				qs = qs.remove(0, qs.find(' ') + 1);    // Filesystem
				qs = qs.remove(0, qs.find(' ') + 1);    // 1M-blocks
				qs = qs.remove(0, qs.find(' ') + 1);    // Used
					
				QString qsFree = qs.left(qs.find(' '));
				size = qsFree.toULong();
					
				qs = qs.remove(0, qs.find(' ') + 1);    // Available
				qs = qs.remove(0, qs.find(' ') + 1);    // Use%
					
				partitions[size] = qs.left(qs.find(' '));

				if (size > sz) sz = size;
			}
              
			df.close();
			unlink("/tmp/.df");

			QListViewItem *vi = par_list->findItem(partitions[sz], 0, BeginsWith);
			par_list->setSelected(vi, TRUE);

			system("cat /proc/meminfo | grep MemTotal > /tmp/.meminfo");

			std::ifstream meminfo("/tmp/.meminfo");

			if (!meminfo.is_open())
			{
				KMessageBox::error(parentWidget(),
					   QString(tr2i18n("Cannot get memory status")));
				return;
			}

			meminfo.getline(szLine, 0x300);
			meminfo.close();

			QString qMem = QString(szLine);
			qMem = qMem.simplifyWhiteSpace();

// MemTotal:       516592 kB
			qMem = qMem.remove(0, qMem.find(' ') + 1);    // MemoryTotal:
			qMem = qMem.left(qMem.find(' '));

			unsigned long swap = qMem.toULong() / 1024; // To megabytes

			// home will take 100megs, while swap will take swap * 2 or 256.
			sz -= 100;      // home dir will take 100MB

			// make sure we have enough free space
			if (swap < 512 && sz < 100 + swap)
			{
				KMessageBox::error(parentWidget(),
					QString(tr2i18n("You have not have enough free space on any of your hard drives,\n"
						"You need at least 460MB free.")));
					// max home, 100Megs
					// max swap, 256Megs
					// min free, 100Megs
					// min sz >= 460Megs
				return;
            }

			// set home directory to root
			docs_path->setText(partitions[sz + 100]);

			// calculate swap size...
            
			if (swap < 512)
			{
				// can we use swap * 2 and leave at least 100Megs free?
				// if so, do it!
				if (sz > swap * 2 + 100) swap *= 2;

				// if not, we already made sure we can use at least 100 + ramsize and leave
				// 100Megs free, so we'll just set up a swap file at the size of the RAM.

				// NOTE: I have divided this to a nested if and no a single if w/ &&
				// to seperate between the case in which we have more then 512MB RAM,
				// and the case we don't.
			}

			// that's enough...
			// we're not gonna set up a render farm on Kinneret based systems :)
			if (swap >= 512) swap = 256;

			// Again, we already made sure we can use at least 356 megs and leave 100Megs
			// free.
                        
			unlink("/tmp/.meminfo");

			// So now swap holds the size of the swap size...
			swap_size->setValue(swap);
			
			// Now jump to conclusion and let it to do all the configuration...
			reinterpret_cast<QWizard*>(this)->showPage(reinterpret_cast<QWizard*>(this)->page(page_conclusion));
			return;
		}
				
		else if (radioNoConfig->isChecked())
		{
			// disable pesonal pref
			checkPrefWiz->setChecked(false);
			checkPrefWiz->setEnabled(false);

			// jump to 'what next?'
			reinterpret_cast<QWizard*>(this)->showPage(reinterpret_cast<QWizard*>(this)->page(page_whatsnext));
		}
		// for expert we don't need to do anything...
	}

	// fill the directory tree
	if (currentPage() == reinterpret_cast<QWizard*>(this)->page(page_homedir) && dir_list->childCount() == 0)
	{
	QPtrList<QListViewItem> qpl = par_list->selectedItems();
		if (qpl.isEmpty())
		{
			KMessageBox::information(parentWidget(),
				QString(tr2i18n("You have not selected a partition,\nplease go back and select one.")));
			
			// disable "next"
			nextButton()->setEnabled(false);
			
			return;
        }
		
		else nextButton()->setEnabled(true);

		QListViewItem *vi = qpl.first();
		QString qMnt = vi->text(0).left(vi->text(0).find(' ')) + QString("/");	
		docs_path->setText(qMnt);
	
		// So the custom widget thing didn't turned up as I wanted it to...
		// well, it's only my first KDE app...
		// I couldn't make the Qt Designed to connect the slots right,
		// so I'll do it manually...
		connect(dir_list, SIGNAL(folderSelected(const QString &)),
				this, SLOT(folderSelected(const QString &)));

		dir_list->addColumn(tr2i18n("Name"));
		Directory *root = new Directory(dir_list, qMnt);
		root->setOpen(true);
	}
	
	if (currentPage() == reinterpret_cast<QWizard*>(this)->page(page_conclusion))
	{
		backButton()->setEnabled(false);
		
		// okay.. now, change some stuff...
		QString qHome = docs_path->text();
		
		// Get the selected partition's mountpoint
		QPtrList<QListViewItem> qpl = par_list->selectedItems();
		QListViewItem *vi = qpl.first();
		QString qMnt = vi->text(0).left(vi->text(0).find(' '));
		
		// Run the script...
		char swapsize[5];
		sprintf(swapsize, "%d", swap_size->value());

		pleasewait *pw = new pleasewait(this);
		pw->blinker = new QTimer(pw);
		pw->blinker->start(1000);		// half a sec
		pw->nLed = 0;
		connect(pw->blinker, SIGNAL(timeout()), pw, SLOT(onTimer()));
		
		pw->show();
		nextButton()->setEnabled(false);

		KProcess p;
		p << "/usr/kinneret/bin/config.sh" << qHome << swapsize << qMnt;
		p.start();

		while (p.isRunning())
			KApplication::kApplication()->processEvents();
			
		nextButton()->setEnabled(true);
		delete pw;
    }

    if (currentPage() == reinterpret_cast<QWizard*>(this)->page(page_fonts) && FontsDirs->childCount() == 0)
	{
		// automaticlly search for fonts...
		system("/usr/kinneret/bin/findfonts.sh");

		FontsDirs->addColumn(QString(tr2i18n("Path")), 400);

		std::ifstream fonts("/tmp/.fontsdirs");

		if (fonts.is_open())
		{
			char szLine[0x300];

			while (!fonts.eof())
			{
				fonts.getline(szLine, 0x300);

				if (szLine[0])
				{
					QListViewItem *vi = new QListViewItem(FontsDirs, szLine);
					FontsDirs->insertItem(vi);
				}
			}

			fonts.close();
		}
    }
	
	if (currentPage() == reinterpret_cast<QWizard*>(this)->page(page_whatsnext))
	{
		// create ~/.fontsdirs - will be loaded by knoppix.sh at boot time
		if (FontsDirs->childCount())
		{
			QListViewItem *vi = FontsDirs->firstChild();
			int i = 1;

			std::ofstream fonts("/home/knoppix/.fontsdirs");
			
			while (vi)
			{
				fonts << vi->text(0) << std::endl;
				vi = FontsDirs->itemAtIndex(i++);
			}

			fonts.close();
		}		

		backButton()->setEnabled(false);
	}
}

void configwizard::folderSelected(const QString &qs)
{
	docs_path->setText(qs);
}


void configwizard::onCreateDir()
{
	QString qCmd = QString("sudo mkdir '") + docs_path->text() + lineCreate->text() + QString("'");
	system(qCmd);
	
	docs_path->setText(docs_path->text() + lineCreate->text());
}


void configwizard::onAddFontDir()
{
	QString qs = QFileDialog::getExistingDirectory(
			"/mnt",
			this,
			"get fonts dir",
			tr2i18n("Choose a directory the containes *.ttf files"),
			true
		);
	QListViewItem *vi = new QListViewItem(FontsDirs, qs);
	FontsDirs->insertItem(vi);
}


void configwizard::onRemoveFontDir()
{
	QPtrList<QListViewItem> qpl = FontsDirs->selectedItems();

	if (qpl.first())
	{
		QString qMsg = QString(tr2i18n("Are you sure you want to remove the directory\n")) +
			qpl.first()->text(0).left(qpl.first()->text(0).find(' ')) + QString(tr2i18n("\nFrom the list?"));

		if (KMessageBox::questionYesNo(this, qMsg, tr2i18n("Are you sure?")) == 3)
			FontsDirs->takeItem(qpl.first());
	}
}


void configwizard::onHelp()
{
	helpdlg *hlp = new helpdlg(this);

	QPalette pal = palette();
	hlp->setPalette(pal);
	QObjectList *l = hlp->queryList("QWidget");
	QObjectListIt it(*l);
	QObject *obj;
	while ((obj = it.current()) != 0)
	{
		++it;
		((QWidget*)obj)->setPalette(pal);
	}
	delete l; // delete the list, not the objects
	
	hlp->exec();
}
