####### kdevelop will overwrite this part!!! (begin)##########


EXTRA_DIST = config.sh findfonts.sh ttf.sh 

install-exec-local:
	$(mkinstalldirs) /opt/kinneret/bin/
	$(INSTALL_SCRIPT) config.sh /opt/kinneret/bin/config.sh
	$(mkinstalldirs) /opt/kinneret/bin/
	$(INSTALL_SCRIPT) findfonts.sh /opt/kinneret/bin/findfonts.sh
	$(mkinstalldirs) /opt/kinneret/bin/
	$(INSTALL_SCRIPT) ttf.sh /opt/kinneret/bin/ttf.sh

uninstall-local:
	-rm -f /opt/kinneret/bin/config.sh
	-rm -f /opt/kinneret/bin/findfonts.sh
	-rm -f /opt/kinneret/bin/ttf.sh

####### kdevelop will overwrite this part!!! (end)############
