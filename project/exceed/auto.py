#!/usr/bin/env python
# -*- coding: utf-8 -*-
import urllib2
import urllib
import httplib
import socket
import json
import sys
import re
import time
import os
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
	print getExceed("temp")
	print getJingjing("cat")
	temp1 = float(getExceed("temp"))
	
	if (temp1 >= 28 and float(getJingjing("cat")) != 0):
		print setExceed("aircon","true")
		print "airon"
	if (int(getJingjing("cat")) == 0):
		print "airoff"
		print setExceed("aircon","false")
while(True):
	print "loop"
	airauto()
	time.sleep(2)
