/****************************************************************************
** MainWindow meta object code from reading C++ file 'l2swim.h'
**
** Created: Sat Sep 13 21:44:26 2003
**      by: The Qt MOC ($Id: l2swim.moc.cpp,v 1.3 2003/09/13 21:10:09 nirro Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "l2swim.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.2.0b1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MainWindow::className() const
{
    return "MainWindow";
}

QMetaObject *MainWindow::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MainWindow( "MainWindow", &MainWindow::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MainWindow::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainWindow", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MainWindow::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainWindow", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MainWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = KMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"home", 0, 0 };
    static const QUMethod slot_1 = {"about", 0, 0 };
    static const QUMethod slot_2 = {"fzoomin", 0, 0 };
    static const QUMethod slot_3 = {"fzoomout", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ "url", &static_QUType_ptr, "KURL", QUParameter::In },
	{ 0, &static_QUType_ptr, "KParts::URLArgs", QUParameter::In }
    };
    static const QUMethod slot_4 = {"openURLRequest", 2, param_slot_4 };
    static const QUMethod slot_5 = {"gotoPreviousPage", 0, 0 };
    static const QUMethod slot_6 = {"gotoForwardPage", 0, 0 };
    static const QUMethod slot_7 = {"printpage", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "home()", &slot_0, QMetaData::Public },
	{ "about()", &slot_1, QMetaData::Public },
	{ "fzoomin()", &slot_2, QMetaData::Public },
	{ "fzoomout()", &slot_3, QMetaData::Public },
	{ "openURLRequest(const KURL&,const KParts::URLArgs&)", &slot_4, QMetaData::Public },
	{ "gotoPreviousPage()", &slot_5, QMetaData::Public },
	{ "gotoForwardPage()", &slot_6, QMetaData::Public },
	{ "printpage()", &slot_7, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MainWindow", parentObject,
	slot_tbl, 8,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MainWindow.setMetaObject( metaObj );
    return metaObj;
}

void* MainWindow::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MainWindow" ) )
	return this;
    return KMainWindow::qt_cast( clname );
}

bool MainWindow::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: home(); break;
    case 1: about(); break;
    case 2: fzoomin(); break;
    case 3: fzoomout(); break;
    case 4: openURLRequest((const KURL&)*((const KURL*)static_QUType_ptr.get(_o+1)),(const KParts::URLArgs&)*((const KParts::URLArgs*)static_QUType_ptr.get(_o+2))); break;
    case 5: gotoPreviousPage(); break;
    case 6: gotoForwardPage(); break;
    case 7: printpage(); break;
    default:
	return KMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MainWindow::qt_emit( int _id, QUObject* _o )
{
    return KMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MainWindow::qt_property( int id, int f, QVariant* v)
{
    return KMainWindow::qt_property( id, f, v);
}

bool MainWindow::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
