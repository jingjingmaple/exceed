#!/usr/bin/env python
# -*- coding: utf-8 -*-
import urllib2
import urllib
import httplib
import socket
import json
import sys
import sqlite3 as lite
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

while(True):
	print "loop"
	val1 = getExceed("count")
	if val1 != "-":
		con = lite.connect('cat.db')
		with con:
			if val1 == "plus":
				print "plus"
				con.execute("UPDATE cat_count SET count=count + 1")
				cur = con.cursor()
				cur.execute("SELECT * FROM cat_count")
				x = cur.fetchone()[0]
				print x
				print setExceed("amount",str(x))
			elif val1 == "minus":
				print "minus"
				cur = con.cursor()
				cur.execute("SELECT * FROM cat_count")
				x = cur.fetchone()[0]
				if (x>0):
					con.execute("UPDATE cat_count SET count=count - 1")
				print x-1
				print setExceed("amount",str(x-1))
		con.close()
		time.sleep(2)
	time.sleep(1)
