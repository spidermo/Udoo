#!/usr/bin/python3

import datetime

import utils.config
import utils.databasehelper
import arduino.serialreader

from utils.config import Config
from utils.databasehelper import DatabaseHelper
from arduino.serialreader import ArduinoSerialReader

class Main(object):
	def __init__(self):
		self._config = Config()
		self._db = DatabaseHelper(self)
		self._db.test()
		self._dueser = ArduinoSerialReader(self)
		self._dueser.test()

	@property
	def config(self):
		return self._config

	@property
	def db(self):
		return self._db

if __name__ == '__main__':
	main = Main()

