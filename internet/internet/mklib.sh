#!/bin/bash
ar rc libinternet.a db.o isp.o ethernet.o xml.o usb.o dialer.o connection.o authentication.o parse.o hardware.o
ranlib libinternet.a

exit 0
