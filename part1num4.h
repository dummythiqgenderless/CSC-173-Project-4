#ifndef _part1num4_h
#define _part1num4_h
#include <stdbool.h>
#include "HashMap.h"


extern Hashmap readCSG ();
extern void writeCSG(Hashmap csgMap);
extern Hashmap readSNAP ();
extern Hashmap readCP ();
extern Hashmap readCDH ();
extern Hashmap readCR ();
extern void writeCSG(Hashmap csgMap);
extern void writeSNAP(Hashmap snapMap);
extern void writeCP(Hashmap cpMap);
extern void writeCDH(Hashmap cdhMap);
extern void writeCR(Hashmap crMap);


#endif
