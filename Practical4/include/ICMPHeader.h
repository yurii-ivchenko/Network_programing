#pragma once

struct ICMPHeader {
    unsigned char type;       // тип (8 = Echo Request)
    unsigned char code;       // код
    unsigned short checksum;  // контрольна сума
    unsigned short id;        // ідентифікатор
    unsigned short seq;       // номер послідовності
};
