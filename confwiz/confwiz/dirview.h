/***************************************************************************
                          dirview.h  -  description
                             -------------------
    begin                : Wed Mar 19 2003
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
#ifndef DIRVIEW_H
#define DIRVIEW_H

#include <qlistview.h>
#include <qstring.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qtimer.h>

class QWidget;
class QDragEnterEvent;
class QDragMoveEvent;
class QDragLeaveEvent;
class QDropEvent;

class FileItem : public QListViewItem
{
public:
    FileItem( QListViewItem *parent, const QString &s1, const QString &s2 )
        : QListViewItem( parent, s1, s2 ), pix( 0 ) {}

    const QPixmap *pixmap( int i ) const;
#if !defined(Q_NO_USING_KEYWORD)
    using QListViewItem::setPixmap;
#endif
    void setPixmap( QPixmap *p );

private:
    QPixmap *pix;

};

class Directory : public QListViewItem
{
public:
    Directory( QListView * parent, const QString& filename );
    Directory( Directory * parent, const QString& filename, const QString &col2 )
        : QListViewItem( parent, filename, col2 ), pix( 0 ) {}
    Directory( Directory * parent, const QString& filename );

    QString text( int column ) const;

    QString fullName();

    void setOpen( bool );
    void setup();

    const QPixmap *pixmap( int i ) const;
#if !defined(Q_NO_USING_KEYWORD)
    using QListViewItem::setPixmap;
#endif
    void setPixmap( QPixmap *p );

private:
    QFile f;
    Directory * p;
    bool readable;
    bool showDirsOnly;
    QPixmap *pix;

};

class DirectoryView : public QListView
{
    Q_OBJECT

public:
    DirectoryView( QWidget *parent = 0, const char *name = 0, bool sdo = TRUE );
    bool showDirsOnly() { return dirsOnly; }

public slots:
    void setDir( const QString & );

signals:
    void folderSelected( const QString & );

protected slots:
    void slotFolderSelected( QListViewItem * );
    void openFolder();

protected:
    void contentsDragEnterEvent( QDragEnterEvent *e );
    void contentsDragMoveEvent( QDragMoveEvent *e );
    void contentsDragLeaveEvent( QDragLeaveEvent *e );
    void contentsDropEvent( QDropEvent *e );
    void contentsMouseMoveEvent( QMouseEvent *e );
    void contentsMousePressEvent( QMouseEvent *e );
    void contentsMouseReleaseEvent( QMouseEvent *e );

private:
    QString fullPath(QListViewItem* item);
    bool dirsOnly;
    QListViewItem *oldCurrent;
    QListViewItem *dropItem;
    QTimer* autoopen_timer;
    QPoint presspos;
    bool mousePressed;

};

#endif

