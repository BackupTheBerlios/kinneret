import shutil,socket,os

class Action:
    def __init__(self):
        self.resolv="/etc/resolv.conf"

    def route(self,type,routeinfo):
        route_command="/sbin/route" #TODO pass to xml.
        route_str=''
        if type == 'static':
            server=routeinfo
            serverip=socket.gethostbyname(server)
            route_str="%s add %s dev eth0"%(route_command,serverip)
            #TODO generalize interface
        else:
            route_str="%s %s %s"%(route_command,type,routeinfo)
        if route_str:
            print route_str
            os.system(route_str)


class KishPre(Action):
    def setDhcpdns(self,dhcp_dns):
        #backing up original resolv.conf
        shutil.copyfile(self.resolv,"%s.orig"%self.resolv)
        ro = open(self.resolv,'w')
        print >> ro, '''#Added by kishoor original file resides in \
/etc/resolv.orig'''
        print >> ro, "nameserver %s"%dhcp_dns
        ro.close()


class KishCon(Action):
    def Connect(self,dev,server,pptp,pptp_args,pppd_args,user):
        pppd_str = "pppd %s \"%s %s %s\" %s %s"%(dev,pptp,server,pptp_args,pppd_args,user)
        print pppd_str
        os.system(pppd_str)


class KishPost(Action):
    def setPeerdns(self):
        shutil.copyfile("/etc/ppp/resolv.conf",self.resolv)

