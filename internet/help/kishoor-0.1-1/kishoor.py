#!/usr/bin/env python2

from qt import *
import sys,re
from KishoorUI import KishoorUI
from KishoorPolicy import KishPre,KishCon,KishPost
from xml.sax import make_parser,handler

class KishoorContentHandler(handler.ContentHandler):
    def startDocument(self):
        print "started doc"
        self.kishoorConf={}
        self.indent=""
        pass
    def startElement(self,name,attrs):
        self.currkey=name
        self.indent += "  "
        pass
    def endElement(self, name):
        self.indent=self.indent[:2]
        pass
    def characters(self,data):
        emptyline=re.search("^\s*$",data)
        if not emptyline:
            self.kishoorConf[self.currkey]=data
    def endDocument(self):
        pass

class kishoor(KishoorUI):
    def __init__(self):
        KishoorUI.__init__(self)
        file=sys.argv[1]
        self.parse_configuration(file)


    def parse_configuration(self,file):
        parser=make_parser()
        parser.setContentHandler(KishoorContentHandler())
        parser.parse(file)
        self.kishoconf=parser._cont_handler.kishoorConf

    def print_dict(self):
        for i in self.kishoconf.keys():
            print "%s->%s]"%(i,self.kishoconf[i])

    def setup(self):
        pass

    def titkasher(self):
        if self.kishoconf['type'] == 'cable':
            self.pre_actions()
            self.connection()
            self.post_actions()
        else:
            self.connection()

    def pre_actions(self):
        pre = KishPre()
        pre.setDhcpdns(self.kishoconf['dhcpdns'])
        if self.kishoconf['addstatic_route']:
            pre.route('static',self.kishoconf['pptp_server'])

    def connection(self):
        con = KishCon()
        con.Connect(self.kishoconf['dev'],self.kishoconf['pptp_server'],\
        self.kishoconf['pptp_location'],  self.kishoconf['pptp_args'], \
        self.kishoconf['pppd_args'],"user %s"%self.userLine.text())

    def authenticate(self):
        print "user:", self.userLine.text()
        print "user:", self.passLine.text()

    def post_actions(self):
        post=KishPost()
        post.route("del",self.kishoconf['route_del'])
        post.route("add",self.kishoconf['route_add1'])
        post.route("add",self.kishoconf['route_add2']) #yeah yeah ...
        post.setPeerdns()

a = QApplication(sys.argv)
k = kishoor()
k.print_dict()
QObject.connect(a,SIGNAL('lastWindowClosed()'),a,SLOT('quit()'))
a.setMainWidget(k)
k.show()
a.exec_loop()

