#!/usr/bin/python3

import pymongo
import datetime

from pymongo import MongoClient

client = MongoClient('localhost', 27017)
db = client.rover;

# insert
loc = [
       {"dt": datetime.datetime.utcnow(),
        "gps": [1.234,2.345],
        "alt": 100 
        },
       {"dt": datetime.datetime.utcnow(),
        "gps": [1.234,2.345],
        "alt": 100
        }
       ];
db.location.insert(loc)

for location in db.location.find():
    print location

for location in db.location.find():
    print("dt: " + location["dt"].strftime("%m-%d-%Y %H:%M:%S") + ", gps: [" + str(location["gps"][0]) + ", " + str(location["gps"][1]) + "], alt: " + location["alt"])