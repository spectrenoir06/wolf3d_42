import json
import sys
import struct
from   decimal import *


if len(sys.argv) == 2:
	f = open(sys.argv[1])
	str = f.read()
	tab = json.loads(str)
	ret = struct.pack("IIIIIII",
		tab['width'], tab['height'],
		len(tab['layers'][3]["objects"]),
		tab['tilesets'][0]['imagewidth'] / tab['tilesets'][0]['tilewidth'],
		int(tab['properties']['nbSprites']),
		int(tab['properties']['startX']),
		int(tab['properties']['startY'])
	)
	for c in tab['layers'][0]['data']:
		ret = ret + unichr(c - 1)
	for c in tab['layers'][1]['data']:
		ret = ret + unichr(c - 1)
	for c in tab['layers'][2]['data']:
		ret = ret + unichr(c - 1)
	sys.stdout.write(ret)
	for obj in tab['layers'][3]['objects']:
		x = Decimal((obj["x"]) + (obj["width"] / 2)) / Decimal(tab["tilewidth"])
		y = Decimal((obj["y"]) + (obj["height"] / 2)) / Decimal(tab["tileheight"])
		sys.stdout.write(struct.pack("ff", x, y))
		tmp = int(obj["properties"]["type"])
		tmp2 = int((obj["properties"]["text"]))
		sys.stdout.write(struct.pack("II" ,tmp, tmp2))
