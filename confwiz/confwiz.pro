unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}
FORMS	= confwiz/configwizard.ui \
	confwiz/pleasewait.ui \
	confwiz/help.ui
IMAGES	= images/small_kinneret_tux.png
TEMPLATE	=app
CONFIG	+= qt warn_on release
LANGUAGE	= C++
