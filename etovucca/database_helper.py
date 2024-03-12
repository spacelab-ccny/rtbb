#!/usr/bin/env python3

import sqlite3
import json

FILENAME = 'rtbb.sqlite3'
SQL_ELECTIONS = "SELECT * FROM Election"
SQL_OFFICES = "SELECT * FROM Office"
SQL_ZIPS = "SELECT * FROM AllowedZip WHERE office="
SQL_CANDIDATES = "SELECT * FROM Candidate WHERE office="

c = sqlite3.connect(FILENAME)

elections = {}
dates = {}

for row in c.execute(SQL_ELECTIONS):
    date = "{}-{:02d}-{:02d}".format(row[3] + 1900, row[2], row[1])
    dates[row[0]] = date
    status = 'closed'
    if row[4] == 1:
        status = 'open'
    elif row[4] == 2:
        status = 'published'
    elections[date] = {
        "offices": [],
        "status": status
    }

for row in c.execute(SQL_OFFICES):
    if row[2] not in dates:
        continue 

    elections[dates[row[2]]]['offices'].append(
        {
            "name": row[1],
            "id": row[0],
            "zips": [],
            "candidates": []
        }
    )
    for subrow in c.execute(SQL_ZIPS + str(row[0])):
        elections[dates[row[2]]]['offices'][-1]['zips'].append(subrow[0])
    for subrow in c.execute(SQL_CANDIDATES + str(row[0])):
        elections[dates[row[2]]]['offices'][-1]['candidates'].append({
            "name": subrow[1],
            "id": subrow[0],
            "votes": subrow[2]
        })

print(json.dumps(elections), end="")
c.close()
