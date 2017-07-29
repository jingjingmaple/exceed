#!/usr/bin/env python
# -*- coding: utf-8 -*-
import urllib2
import urllib
import httplib
import socket
import json
import sys
import re
from time import gmtime, strftime, localtime
import os
import time
def getExceed(name1):
	try:
		conn = httplib.HTTPConnection('158.108.165.223')
		header = {"User-Agent":"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.89 Safari/537.36","Accept":"text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"}
		conn.request("GET","/data/AssassinZEED/"+name1,"",header)
		conn.sock.settimeout(5.0)
		r1 = conn.getresponse()
		suck = r1.read()
		return suck
	except (httplib.HTTPException, socket.error) as ex:
		print '{"data":"","error":"%s"}' % ex
	except:
		pass
	try:
		conn.close()
	except:
		pass
def setExceed(name,value):
	try:
		conn = httplib.HTTPConnection('158.108.165.223')
		header = {"User-Agent":"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.89 Safari/537.36","Accept":"text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"}
		conn.request("GET","/data/AssassinZEED/"+name+"/set/"+value,"",header)
		conn.sock.settimeout(5.0)
		r1 = conn.getresponse()
		suck = r1.read()
		if (suck == "OK"):
			return True
		else:
			return False
	except (httplib.HTTPException, socket.error) as ex:
		print '{"data":"","error":"%s"}' % ex
	except:
		pass
	try:
		conn.close()
	except:
		pass
def getJingjing(name1):
	try:
		conn = httplib.HTTPConnection('128.199.232.240')
		header = {"User-Agent":"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2272.89 Safari/537.36","Accept":"text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"}
		conn.request("GET","/"+name1,"",header)
		conn.sock.settimeout(5.0)
		r1 = conn.getresponse()
		suck = r1.read()
		return suck
	except (httplib.HTTPException, socket.error) as ex:
		print '{"data":"","error":"%s"}' % ex
	except:
		pass
	try:
		conn.close()
	except:
		pass
def airauto():
	temp1 = float(getExceed("temp"))
	if (getExceed("airconauto") == "true"):
		if (temp1 >= 28 and int(getExceed("amount")) != 0):
			print setExceed("aircon","true")
			print "airon"
		if (int(getExceed("amount")) == 0):
			print "airoff"
			print setExceed("aircon","false")
def doorauto():
	time_ = strftime("%H:%M:%S",localtime())
	print time_
	if time_ == "10:10:00":
			print "trick"
        print time_
while(True):
	#print "loop"
	airauto()
	#doorauto()
	time.sleep(2)
