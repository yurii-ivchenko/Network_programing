#pragma once
#include <winsock2.h>
#include <windows.h>

struct IPHeader {
    unsigned char  ip_hl : 4;   // довжина заголовка
    unsigned char  ip_v : 4;    // версія
    unsigned char  ip_tos;    // тип сервісу
    unsigned short ip_len;    // довжина пакета
    unsigned short ip_id;     // ідентифікатор
    unsigned short ip_off;    // зсув фрагмента
    unsigned char  ip_ttl;    // час життя
    unsigned char  ip_p;      // протокол (1 = ICMP)
    unsigned short ip_sum;    // контрольна сума
    unsigned int   ip_src;    // адреса джерела
    unsigned int   ip_dst;    // адреса призначення
};
