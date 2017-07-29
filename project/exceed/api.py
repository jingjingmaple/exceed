#!/usr/bin/env python
# -*- coding: utf-8 -*-
import web
import sqlite3 as lite

urls = (
	'/', 'index',
	'/cat', 'cat',
	'/cat/add', 'cat_add',
	'/cat/minus', 'cat_minus'
)

class index:
    def GET(self):
        return "Hello, world!"
class cat:
	def GET(self):
		con = lite.connect('cat.db')
		x = 0;
                with con:
			cur = con.cursor()
			cur.execute("SELECT * FROM cat_count")
			x = cur.fetchone()[0]
                con.close()
		web.header('Access-Control-Allow-Origin',      '*')
		web.header('Access-Control-Allow-Credentials', 'true')
                return x
class cat_add:
	def GET(self):
		con = lite.connect('cat.db')
                with con:
                        con.execute("UPDATE cat_count SET count=count + 1")
			con.execute("INSERT INTO log (name,value,time) VALUES ('count','add',datetime('now', 'localtime'))")
		con.close()
		return "OK"
class cat_minus:
        def GET(self):
                con = lite.connect('cat.db')
		with con:
			cur = con.cursor()
                        cur.execute("SELECT * FROM cat_count")
			con.execute("INSERT INTO log (name,value,time) VALUES ('count','minus',datetime('now', 'localtime'))")
                        #cursor = con.execute("SELECT * FROM cat_count")
                        #for row in cursor:
                        #       x = row[0]
                        x = cur.fetchone()[0]
			if (x>0):
				con.execute("UPDATE cat_count SET count=count - 1")
		con.close()
                return "OK"
if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()
