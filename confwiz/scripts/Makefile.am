####### kdevelop will overwrite this part!!! (begin)##########


EXTRA_DIST = config.sh findfonts.sh ttf.sh 

install-exec-local:
	$(mkinstalldirs) /usr/kinneret/bin/
	$(INSTALL_SCRIPT) config.sh /usr/kinneret/bin/config.sh
	$(mkinstalldirs) /usr/kinneret/bin/
	$(INSTALL_SCRIPT) findfonts.sh /usr/kinneret/bin/findfonts.sh
	$(mkinstalldirs) /usr/kinneret/bin/
	$(INSTALL_SCRIPT) ttf.sh /usr/kinneret/bin/ttf.sh

uninstall-local:
	-rm -f /usr/kinneret/bin/config.sh
	-rm -f /usr/kinneret/bin/findfonts.sh
	-rm -f /usr/kinneret/bin/ttf.sh

####### kdevelop will overwrite this part!!! (end)############
