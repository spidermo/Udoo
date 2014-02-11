#!/usr/bin/python3

import serial
import time

import utils.config

from utils.config import Config

class ArduinoSerialReader(object):
	def __init__(self, main):
		self._main = main
		self._config_section = "arduino_serial"
		self._ser = serial.Serial(main.config.get(self._config_section, "serial_path"), main.config.getInt(self._config_section, "serial_baud"))
		self._ser.timeout = main.config.getFloat(self._config_section, "serial_timeout")
		
		try:
			self._ser.open()
			print("Initializing")
		except Exception:
			print("Error opening serial port")
		time.sleep(1) #Wait for initialization

	def test(self):
		for x in range(0, 5000):
			line = self._ser.readline().decode(self._main.config.get(self._config_section, "serial_encoding"))
			print("line: " + line, end="")
