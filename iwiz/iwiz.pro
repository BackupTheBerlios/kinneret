unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}
FORMS	= iwiz/iwizard.ui \
	iwiz/rename.ui
TEMPLATE	=app
CONFIG	+= qt warn_on release
LANGUAGE	= C++
