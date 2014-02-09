#!/usr/bin/python3

import pymongo

from pymongo import MongoClient

class DatabaseHelper(object):
	def __init__(self, main):
		self._client = MongoClient(main.config.get("db", "db_host"), main.config.getInt("db", "db_port"))
		self._db = self._client[main.config.get("db", "db_name")]

	def test(self):
		print(self._db.collection_names(False))

		for location in self._db["location"].find().sort("dt", pymongo.DESCENDING):
			print(location)
