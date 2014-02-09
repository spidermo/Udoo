#!/usr/bin/python3

import datetime
import utils.config
import utils.databasehelper

from utils.config import Config
from utils.databasehelper import DatabaseHelper

class Main(object):
	def __init__(self):
		self._config = Config()
		self._db = DatabaseHelper(self)
		self._db.test()

	@property
	def config(self):
		return self._config

	@property
	def db(self):
		return self._db

if __name__ == '__main__':
	main = Main()

