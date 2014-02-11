#!/usr/bin/python3

import configparser

from configparser import SafeConfigParser

class Config(object):
	def __init__(self):
		self._configFileName = "rover.cfg"
		self._readConfig()

	def _readConfig(self):
		self._config = SafeConfigParser({
			"db_host": "localhost",
			"db_port": "27017",
			"db_name": "rover",
			"serial_path": "/dev/ttymxc3",
			"serial_baud": "115200",
			"serial_timeout": "0.5",
			"serial_encoding": "windows-1252"})
		self._config.read(self._configFileName)
		self._validateConfig()

	def _writeConfig(self):
		self._config.write(open(self._configFileName, "w"))

	def _validateConfig(self):
		changed = False
		if not self._config.has_section("db"):
			self._config.add_section("db")
			changed = True
		if not self._config.has_section("arduino_serial"):
			self._config.add_section("arduino_serial")
			changed = True
		if changed:
			self._writeConfig()

	def get(self, section, key):
		return self._config.get(section, key)

	def getInt(self, section, key):
		return self._config.getint(section, key)

	def getFloat(self, section, key):
		return self._config.getfloat(section, key)

	def getBoolean(self, section, key):
		return self._config.getboolean(section, key)

	def set(self, section, key, value):
		self._config.set(section, key, value)
		self._writeConfig()
