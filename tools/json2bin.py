import json
import sys
import struct

if len(sys.argv) == 2:
    f = open(sys.argv[1])
    str = f.read()
    tab = json.loads(str)
    ret = struct.pack("III", tab['width'], tab['height'], len(tab['tilesets'][0]['tiles']))
    for c in tab['layers'][0]['data']:
        ##print(c)
        ret = ret + unichr(c - 1)
    print(ret)