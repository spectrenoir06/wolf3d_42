import json
import sys
import struct
from   decimal import *


if len(sys.argv) == 2:
	f = open(sys.argv[1])
	str = f.read()
	tab = json.loads(str)
	ret = struct.pack("IIII", tab['width'], tab['height'], len(tab['layers'][3]["objects"]), len(tab['tilesets'][0]['tiles']))
	for c in tab['layers'][0]['data']:
		ret = ret + unichr(c - 1)
	for c in tab['layers'][1]['data']:
		ret = ret + unichr(c - 1)
	for c in tab['layers'][2]['data']:
		ret = ret + unichr(c - 1)
	sys.stdout.write(ret)
	for obj in tab['layers'][3]['objects']:
	##	print("type = " + obj["properties"]["type"]);
	##	print("text = " + obj["properties"]["text"]);
		x = Decimal(obj["x"]) / Decimal(tab["tilewidth"])
		y = Decimal(obj["y"]) / Decimal(tab["tileheight"])
	##print(x);
	##	print(y);
		sys.stdout.write(struct.pack("ff", x, y))
		sys.stdout.write(unichr(obj["properties"]["type"]))
		sys.stdout.write(unichr(obj["properties"]["text"]))
		#, unichr(obj["properties"]["type"]), unichr(obj["properties"]["text"])))
