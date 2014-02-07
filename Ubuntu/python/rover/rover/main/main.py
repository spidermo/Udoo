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

for location in db.location:
    print("location: " + location)