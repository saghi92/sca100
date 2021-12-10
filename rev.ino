



/*DRDY: 
 CSB:  pin 14
 MOSI: pin 15
 MISO: pin 16
 SCK:  pin 17
 SCL:  pin 28
 SDL:  pin 27
 */

// the sensor communicates using SPI, so include the library:
#include <SPI.h>

/*
MEAS 00000000 Measure mode (normal operation mode after power on)
RWTR 00001000 Read and write temperature data register
RDSR 00001010 Read status register
RLOAD 00001011 Reload NV data to memory output register
STX 00001110 Activate Self test for X-channel
STY 00001111 Activate Self test for Y-channel
RDAX 00010000 Read X-channel acceleration through SPI
RDAY 00010001 Read Y-channel acceleration through SPI
*/

const byte MEAS=0;
const byte RWTR=8;
const byte RDSR=10;
const byte RLOAD=11;
const byte STX=14;
const byte STY=15;
const byte RDAX=16;
const byte RDAY=17;

byte m=0; 
byte a=0; 
int x,y;
byte am[]={1,2,3,4,100},ak[]={0,0,0};

void setup() {
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    Serial.begin(9600);
    byte v=0;
    DDRD |=0xF8;
    DDRB |=0x03;
    DDRC |=0x3f;
    DDRB |= (1<<2);
    PORTB |= (1<<2);
    
    byte akk[60]={31,32};
    for(v=1;v<60;v++){
      akk[v]=30+v;
    }
    delay(100);

}

void loop() {
  
        x=read_SCA100TX();
        y=read_SCA100TY();  
         
       if(Serial.available()>0){   
        if(0x55==Serial.read()) {
             delay(8);
             if(0xAA==Serial.read()){
               delay(8);
               ak[0]=Serial.read();
               delay(8);
               ak[1]=Serial.read();
               ak[2]=0x55^0xAA^ak[0];
               if(ak[1]==ak[2]){
                   switch(ak[0]){
                     case 01:
                       zuihuo(x,y);
                       break;
                    case 02:
                       SerialcomtT(x,y);
                       break;
                   case 03:
                       SerialcomtT(x,y);
                       break;
                  default:
                         break;
                   }
              }
            }
        }
     }
        
    ledalloff();
    delay(1);   
    leddisplay(x,y);
    delay(100);
}

void Serialcompg(byte m,int x,byte n,int y){
        byte kx,kkx,ky,kky,chkdata,xx,wa[10]={0};
        xx=197-read_SCA100TT(RWTR);
        kx=x;
        kkx=(x>>8); 
        ky=y;
        kky=(y>>8);
        chkdata =xx^m^n^kx^kkx^ky^kky^0x55^0xAA;
        wa[0]=0x55;
        wa[1]=0xaa;
        wa[2]=m;
        wa[3]=kkx;
        wa[4]=kx;
        wa[5]=n;
        wa[6]=kky;
        wa[7]=ky;
        wa[8]=xx;
        wa[9]=chkdata;
        Serial.write(wa,10);
}

void xxxx(int x,int y){
      byte m,n;
      if(x>1024)
         m=0x00;
      else{
         m=0xFF;
         x=2048-x;
      }
      if(y>1024)
         n=0x00;
      else{
         n=0xFF;y=2048-y;
      }
      
    Serialcompg(m,jdzh(x),n,jdzh(y));
}

void zuihuo(int x,int y) {
     byte m,n,s;
     byte kx,kkx,ky,kky,chkdata,xx,wa[10]={0};
     xx=197-read_SCA100TT(RWTR);
           
     if(x>1024)
        m=0x00;
     else {
        m=0xFF;
        x=2048-x;
     }
    
     if(y>1024)
        n=0x00;
     else{
        n=0xFF;
        y=2048-y;
     }
    
    if(y>=1433){
         ky=jin(y);
         kky=0x00;  
      }else {
         s=jim(y);
         ky=s/10;
         kky=(s-ky*10);
      }
      
    if(x>=1433){
        kx=jin(x);
        kkx=0x00;  
     }else {
        s=jim(x);
        kx=s/10;
        kkx=(s-kx*10);
      }

    chkdata =xx^m^n^kx^kkx^ky^kky^0x55^0xAA; 
    wa[0]=0x55;
    wa[1]=0xaa;
    wa[2]=m;
    wa[3]=kx;
    wa[4]=kkx;
    wa[5]=n;
    wa[6]=(byte)ky;
    wa[7]=(byte)kky;
    wa[8]=xx;
    wa[9]=chkdata;
    Serial.write(wa,10);

}

int jdzh(int x)
{
    if(x>=1433)
        return jin(x);
    else
        return jim(x);
}

byte jin(int x)
{
    byte y=0;
    switch(x){
      case 1434: y=30;break;
      case 1435: y=30;break;
      case 1436: y=30;break;
      case 1437: y=30;break;
      case 1438: y=31;break;
      case 1439: y=31;break;
      case 1440: y=31;break;
      case 1441: y=31;break;
      case 1442: y=31;break;
      case 1443: y=31;break;
      case 1444: y=31;break;
      case 1445: y=31;break;
      case 1446: y=31;break;
      case 1447: y=31;break;
      case 1448: y=31;break;
      case 1449: y=31;break;
      case 1450: y=31;break;
      case 1451: y=31;break;
      case 1452: y=32;break;
      case 1453: y=32;break;
      case 1454: y=32;break;
      case 1455: y=32;break;
      case 1456: y=32;break;
      case 1457: y=32;break;
      case 1458: y=32;break;
      case 1459: y=32;break;
      case 1460: y=32;break;
      case 1461: y=32;break;
      case 1462: y=32;break;
      case 1463: y=32;break;
      case 1464: y=32;break;
      case 1465: y=33;break;
      case 1466: y=33;break;
      case 1467: y=33;break;
      case 1468: y=33;break;
      case 1469: y=33;break;
      case 1470: y=33;break;
      case 1471: y=33;break;
      case 1472: y=33;break;
      case 1473: y=33;break;
      case 1474: y=33;break;
      case 1475: y=33;break;
      case 1476: y=34;break;
      case 1477: y=34;break;
      case 1478: y=34;break;
      case 1479: y=34;break;
      case 1480: y=34;break;
      case 1481: y=34;break;
      case 1482: y=34;break;
      case 1483: y=34;break;
      case 1484: y=34;break;
      case 1485: y=34;break;
      case 1486: y=34;break;
      case 1487: y=34;break;
      case 1488: y=35;break;
      case 1489: y=35;break;
      case 1490: y=35;break;
      case 1491: y=35;break;
      case 1492: y=35;break;
      case 1493: y=35;break;
      case 1494: y=35;break;
      case 1495: y=35;break;
      case 1496: y=35;break;
      case 1497: y=35;break;
      case 1498: y=35;break;
      case 1499: y=35;break;
      case 1500: y=36;break;
      case 1501: y=36;break;
      case 1502: y=36;break;
      case 1503: y=36;break;
      case 1504: y=36;break;
      case 1505: y=36;break;
      case 1506: y=36;break;
      case 1507: y=36;break;
      case 1508: y=36;break;
      case 1509: y=36;break;
      case 1510: y=36;break;
      case 1511: y=37;break;
      case 1512: y=37;break;
      case 1513: y=37;break;
      case 1514: y=37;break;
      case 1515: y=37;break;
      case 1516: y=37;break;
      case 1517: y=37;break;
      case 1518: y=37;break;
      case 1519: y=37;break;
      case 1520: y=37;break;
      case 1521: y=37;break;
      case 1522: y=37;break;
      case 1523: y=38;break;
      case 1524: y=38;break;
      case 1525: y=38;break;
      case 1526: y=38;break;
      case 1527: y=38;break;
      case 1528: y=38;break;
      case 1529: y=38;break;
      case 1530: y=38;break;
      case 1531: y=38;break;
      case 1532: y=38;break;
      case 1533: y=38;break;
      case 1534: y=39;break;
      case 1535: y=39;break;
      case 1536: y=39;break;
      case 1537: y=39;break;
      case 1538: y=39;break;
      case 1539: y=39;break;
      case 1540: y=39;break;
      case 1541: y=39;break;
      case 1542: y=39;break;
      case 1543: y=39;break;
      case 1544: y=39;break;
      case 1545: y=40;break;
      case 1546: y=40;break;
      case 1547: y=40;break;
      case 1548: y=40;break;
      case 1549: y=40;break;
      case 1550: y=40;break;
      case 1551: y=40;break;
      case 1552: y=40;break;
      case 1553: y=40;break;
      case 1554: y=40;break;
      case 1555: y=40;break;
      case 1556: y=41;break;
      case 1557: y=41;break;
      case 1558: y=41;break;
      case 1559: y=41;break;
      case 1560: y=41;break;
      case 1561: y=41;break;
      case 1562: y=41;break;
      case 1563: y=41;break;
      case 1564: y=41;break;
      case 1565: y=41;break;
      case 1566: y=41;break;
      case 1567: y=42;break;
      case 1568: y=42;break;
      case 1569: y=42;break;
      case 1570: y=42;break;
      case 1571: y=42;break;
      case 1572: y=42;break;
      case 1573: y=42;break;
      case 1574: y=42;break;
      case 1575: y=42;break;
      case 1576: y=42;break;
      case 1577: y=42;break;
      case 1578: y=43;break;
      case 1579: y=43;break;
      case 1580: y=43;break;
      case 1581: y=43;break;
      case 1582: y=43;break;
      case 1583: y=43;break;
      case 1584: y=43;break;
      case 1585: y=43;break;
      case 1586: y=43;break;
      case 1587: y=43;break;
      case 1588: y=44;break;
      case 1589: y=44;break;
      case 1590: y=44;break;
      case 1591: y=44;break;
      case 1592: y=44;break;
      case 1593: y=44;break;
      case 1594: y=44;break;
      case 1595: y=44;break;
      case 1596: y=44;break;
      case 1597: y=44;break;
      case 1598: y=45;break;
      case 1599: y=45;break;
      case 1600: y=45;break;
      case 1601: y=45;break;
      case 1602: y=45;break;
      case 1603: y=45;break;
      case 1604: y=45;break;
      case 1605: y=45;break;
      case 1606: y=45;break;
      case 1607: y=45;break;
      case 1608: y=45;break;
      case 1609: y=46;break;
      case 1610: y=46;break;
      case 1611: y=46;break;
      case 1612: y=46;break;
      case 1613: y=46;break;
      case 1614: y=46;break;
      case 1615: y=46;break;
      case 1616: y=46;break;
      case 1617: y=46;break;
      case 1618: y=47;break;
      case 1619: y=47;break;
      case 1620: y=47;break;
      case 1621: y=47;break;
      case 1622: y=47;break;
      case 1623: y=47;break;
      case 1624: y=47;break;
      case 1625: y=47;break;
      case 1626: y=47;break;
      case 1627: y=47;break;
      case 1628: y=48;break;
      case 1629: y=48;break;
      case 1630: y=48;break;
      case 1631: y=48;break;
      case 1632: y=48;break;
      case 1633: y=48;break;
      case 1634: y=48;break;
      case 1635: y=48;break;
      case 1636: y=48;break;
      case 1637: y=48;break;
      case 1638: y=49;break;
      case 1639: y=49;break;
      case 1640: y=49;break;
      case 1641: y=49;break;
      case 1642: y=49;break;
      case 1643: y=49;break;
      case 1644: y=49;break;
      case 1645: y=49;break;
      case 1646: y=49;break;
      case 1647: y=50;break;
      case 1648: y=50;break;
      case 1649: y=50;break;
      case 1650: y=50;break;
      case 1651: y=50;break;
      case 1652: y=50;break;
      case 1653: y=50;break;
      case 1654: y=50;break;
      case 1655: y=50;break;
      case 1656: y=51;break;
      case 1657: y=51;break;
      case 1658: y=51;break;
      case 1659: y=51;break;
      case 1660: y=51;break;
      case 1661: y=51;break;
      case 1662: y=51;break;
      case 1663: y=51;break;
      case 1664: y=51;break;
      case 1665: y=52;break;
      case 1666: y=52;break;
      case 1667: y=52;break;
      case 1668: y=52;break;
      case 1669: y=52;break;
      case 1670: y=52;break;
      case 1671: y=52;break;
      case 1672: y=52;break;
      case 1673: y=52;break;
      case 1674: y=53;break;
      case 1675: y=53;break;
      case 1676: y=53;break;
      case 1677: y=53;break;
      case 1678: y=53;break;
      case 1679: y=53;break;
      case 1680: y=53;break;
      case 1681: y=53;break;
      case 1682: y=53;break;
      case 1683: y=54;break;
      case 1684: y=54;break;
      case 1685: y=54;break;
      case 1686: y=54;break;
      case 1687: y=54;break;
      case 1688: y=54;break;
      case 1689: y=54;break;
      case 1690: y=54;break;
      case 1691: y=55;break;
      case 1692: y=55;break;
      case 1693: y=55;break;
      case 1694: y=55;break;
      case 1695: y=55;break;
      case 1696: y=55;break;
      case 1697: y=55;break;
      case 1698: y=55;break;
      case 1699: y=56;break;
      case 1700: y=56;break;
      case 1701: y=56;break;
      case 1702: y=56;break;
      case 1703: y=56;break;
      case 1704: y=56;break;
      case 1705: y=56;break;
      case 1706: y=56;break;
      case 1707: y=57;break;
      case 1708: y=57;break;
      case 1709: y=57;break;
      case 1710: y=57;break;
      case 1711: y=57;break;
      case 1712: y=57;break;
      case 1713: y=57;break;
      case 1714: y=57;break;
      case 1715: y=58;break;
      case 1716: y=58;break;
      case 1717: y=58;break;
      case 1718: y=58;break;
      case 1719: y=58;break;
      case 1720: y=58;break;
      case 1721: y=58;break;
      case 1722: y=58;break;
      case 1723: y=59;break;
      case 1724: y=59;break;
      case 1725: y=59;break;
      case 1726: y=59;break;
      case 1727: y=59;break;
      case 1728: y=59;break;
      case 1729: y=59;break;
      case 1730: y=60;break;
      case 1731: y=60;break;
      case 1732: y=60;break;
      case 1733: y=60;break;
      case 1734: y=60;break;
      case 1735: y=60;break;
      case 1736: y=60;break;
      case 1737: y=61;break;
      case 1738: y=61;break;
      case 1739: y=61;break;
      case 1740: y=61;break;
      case 1741: y=61;break;
      case 1742: y=61;break;
      case 1743: y=61;break;
      case 1744: y=62;break;
      case 1745: y=62;break;
      case 1746: y=62;break;
      case 1747: y=62;break;
      case 1748: y=62;break;
      case 1749: y=62;break;
      case 1750: y=62;break;
      case 1751: y=63;break;
      case 1752: y=63;break;
      case 1753: y=63;break;
      case 1754: y=63;break;
      case 1755: y=63;break;
      case 1756: y=63;break;
      case 1757: y=64;break;
      case 1758: y=64;break;
      case 1759: y=64;break;
      case 1760: y=64;break;
      case 1761: y=64;break;
      case 1762: y=64;break;
      case 1763: y=64;break;
      case 1764: y=65;break;
      case 1765: y=65;break;
      case 1766: y=65;break;
      case 1767: y=65;break;
      case 1768: y=65;break;
      case 1769: y=65;break;
      case 1770: y=66;break;
      case 1771: y=66;break;
      case 1772: y=66;break;
      case 1773: y=66;break;
      case 1774: y=66;break;
      case 1775: y=67;break;
      case 1776: y=67;break;
      case 1777: y=67;break;
      case 1778: y=67;break;
      case 1779: y=67;break;
      case 1780: y=67;break;
      case 1781: y=68;break;
      case 1782: y=68;break;
      case 1783: y=68;break;
      case 1784: y=68;break;
      case 1785: y=68;break;
      case 1786: y=69;break;
      case 1787: y=69;break;
      case 1788: y=69;break;
      case 1789: y=69;break;
      case 1790: y=69;break;
      case 1791: y=70;break;
      case 1792: y=70;break;
      case 1793: y=70;break;
      case 1794: y=70;break;
      case 1795: y=70;break;
      case 1796: y=71;break;
      case 1797: y=71;break;
      case 1798: y=71;break;
      case 1799: y=71;break;
      case 1800: y=71;break;
      case 1801: y=72;break;
      case 1802: y=72;break;
      case 1803: y=72;break;
      case 1804: y=72;break;
      case 1805: y=73;break;
      case 1806: y=73;break;
      case 1807: y=73;break;
      case 1808: y=73;break;
      case 1809: y=73;break;
      case 1810: y=74;break;
      case 1811: y=74;break;
      case 1812: y=74;break;
      case 1813: y=74;break;
      case 1814: y=75;break;
      case 1815: y=75;break;
      case 1816: y=75;break;
      case 1817: y=76;break;
      case 1818: y=76;break;
      case 1819: y=76;break;
      case 1820: y=76;break;
      case 1821: y=77;break;
      case 1822: y=77;break;
      case 1823: y=77;break;
      case 1824: y=78;break;
      case 1825: y=78;break;
      case 1826: y=78;break;
      case 1827: y=79;break;
      case 1828: y=79;break;
      case 1829: y=80;break;
      case 1830: y=80;break;
      case 1831: y=80;break;
      case 1832: y=81;break;
      case 1833: y=81;break;
      case 1834: y=82;break;
      case 1835: y=82;break;
      case 1836: y=83;break;
      case 1837: y=83;break;
      case 1838: y=84;break;
      case 1839: y=85;break;
      case 1840: y=85;break;
      case 1841: y=86;break;
      case 1842: y=88;break;
      case 1843: y=90;break;
      default:y=-1;break;
      }
      return y;
}

int jim(int x)
{
  int y=0;
  switch(x){
    case 1023: y=0;break;
    case 1024: y=0;break;
    case 1025: y=0;break;
    case 1026: y=1;break;
    case 1027: y=1;break;
    case 1028: y=2;break;
    case 1029: y=3;break;
    case 1030: y=3;break;
    case 1031: y=4;break;
    case 1032: y=5;break;
    case 1033: y=5;break;
    case 1034: y=6;break;
    case 1035: y=7;break;
    case 1036: y=8;break;
    case 1037: y=8;break;
    case 1038: y=9;break;
    case 1039: y=10;break;
    case 1040: y=10;break;
    case 1041: y=11;break;
    case 1042: y=12;break;
    case 1043: y=12;break;
    case 1044: y=13;break;
    case 1045: y=14;break;
    case 1046: y=15;break;
    case 1047: y=15;break;
    case 1048: y=16;break;
    case 1049: y=17;break;
    case 1050: y=17;break;
    case 1051: y=18;break;
    case 1052: y=19;break;
    case 1053: y=19;break;
    case 1054: y=20;break;
    case 1055: y=21;break;
    case 1056: y=22;break;
    case 1057: y=22;break;
    case 1058: y=23;break;
    case 1059: y=24;break;
    case 1060: y=24;break;
    case 1061: y=25;break;
    case 1062: y=26;break;
    case 1063: y=26;break;
    case 1064: y=27;break;
    case 1065: y=28;break;
    case 1066: y=29;break;
    case 1067: y=29;break;
    case 1068: y=30;break;
    case 1069: y=31;break;
    case 1070: y=31;break;
    case 1071: y=32;break;
    case 1072: y=33;break;
    case 1073: y=34;break;
    case 1074: y=34;break;
    case 1075: y=35;break;
    case 1076: y=36;break;
    case 1077: y=36;break;
    case 1078: y=37;break;
    case 1079: y=38;break;
    case 1080: y=38;break;
    case 1081: y=39;break;
    case 1082: y=40;break;
    case 1083: y=41;break;
    case 1084: y=41;break;
    case 1085: y=42;break;
    case 1086: y=43;break;
    case 1087: y=43;break;
    case 1088: y=44;break;
    case 1089: y=45;break;
    case 1090: y=45;break;
    case 1091: y=46;break;
    case 1092: y=47;break;
    case 1093: y=48;break;
    case 1094: y=48;break;
    case 1095: y=49;break;
    case 1096: y=50;break;
    case 1097: y=50;break;
    case 1098: y=51;break;
    case 1099: y=52;break;
    case 1100: y=52;break;
    case 1101: y=53;break;
    case 1102: y=54;break;
    case 1103: y=55;break;
    case 1104: y=55;break;
    case 1105: y=56;break;
    case 1106: y=57;break;
    case 1107: y=57;break;
    case 1108: y=58;break;
    case 1109: y=59;break;
    case 1110: y=59;break;
    case 1111: y=60;break;
    case 1112: y=61;break;
    case 1113: y=62;break;
    case 1114: y=62;break;
    case 1115: y=63;break;
    case 1116: y=64;break;
    case 1117: y=64;break;
    case 1118: y=65;break;
    case 1119: y=66;break;
    case 1120: y=67;break;
    case 1121: y=67;break;
    case 1122: y=68;break;
    case 1123: y=69;break;
    case 1124: y=69;break;
    case 1125: y=70;break;
    case 1126: y=71;break;
    case 1127: y=71;break;
    case 1128: y=72;break;
    case 1129: y=73;break;
    case 1130: y=74;break;
    case 1131: y=74;break;
    case 1132: y=75;break;
    case 1133: y=76;break;
    case 1134: y=76;break;
    case 1135: y=77;break;
    case 1136: y=78;break;
    case 1137: y=79;break;
    case 1138: y=79;break;
    case 1139: y=80;break;
    case 1140: y=81;break;
    case 1141: y=81;break;
    case 1142: y=82;break;
    case 1143: y=83;break;
    case 1144: y=83;break;
    case 1145: y=84;break;
    case 1146: y=85;break;
    case 1147: y=86;break;
    case 1148: y=86;break;
    case 1149: y=87;break;
    case 1150: y=88;break;
    case 1151: y=88;break;
    case 1152: y=89;break;
    case 1153: y=90;break;
    case 1154: y=91;break;
    case 1155: y=91;break;
    case 1156: y=92;break;
    case 1157: y=93;break;
    case 1158: y=93;break;
    case 1159: y=94;break;
    case 1160: y=95;break;
    case 1161: y=96;break;
    case 1162: y=96;break;
    case 1163: y=97;break;
    case 1164: y=98;break;
    case 1165: y=98;break;
    case 1166: y=99;break;
    case 1167: y=100;break;
    case 1168: y=100;break;
    case 1169: y=101;break;
    case 1170: y=102;break;
    case 1171: y=103;break;
    case 1172: y=103;break;
    case 1173: y=104;break;
    case 1174: y=105;break;
    case 1175: y=105;break;
    case 1176: y=106;break;
    case 1177: y=107;break;
    case 1178: y=108;break;
    case 1179: y=108;break;
    case 1180: y=110;break;
    case 1181: y=111;break;
    case 1182: y=111;break;
    case 1183: y=112;break;
    case 1184: y=113;break;
    case 1185: y=114;break;
    case 1186: y=114;break;
    case 1187: y=115;break;
    case 1188: y=116;break;
    case 1189: y=116;break;
    case 1190: y=117;break;
    case 1191: y=118;break;
    case 1192: y=119;break;
    case 1193: y=119;break;
    case 1194: y=120;break;
    case 1195: y=121;break;
    case 1196: y=121;break;
    case 1197: y=122;break;
    case 1198: y=123;break;
    case 1199: y=124;break;
    case 1200: y=124;break;
    case 1201: y=125;break;
    case 1202: y=126;break;
    case 1203: y=126;break;
    case 1204: y=127;break;
    case 1205: y=128;break;
    case 1206: y=129;break;
    case 1207: y=129;break;
    case 1208: y=130;break;
    case 1209: y=131;break;
    case 1210: y=131;break;
    case 1211: y=132;break;
    case 1212: y=133;break;
    case 1213: y=134;break;
    case 1214: y=134;break;
    case 1215: y=135;break;
    case 1216: y=136;break;
    case 1217: y=137;break;
    case 1218: y=137;break;
    case 1219: y=138;break;
    case 1220: y=139;break;
    case 1221: y=139;break;
    case 1222: y=140;break;
    case 1223: y=141;break;
    case 1224: y=142;break;
    case 1225: y=142;break;
    case 1226: y=143;break;
    case 1227: y=144;break;
    case 1228: y=144;break;
    case 1229: y=145;break;
    case 1230: y=146;break;
    case 1231: y=147;break;
    case 1232: y=147;break;
    case 1233: y=148;break;
    case 1234: y=149;break;
    case 1235: y=150;break;
    case 1236: y=150;break;
    case 1237: y=151;break;
    case 1238: y=152;break;
    case 1239: y=152;break;
    case 1240: y=153;break;
    case 1241: y=154;break;
    case 1242: y=155;break;
    case 1243: y=155;break;
    case 1244: y=156;break;
    case 1245: y=157;break;
    case 1246: y=158;break;
    case 1247: y=158;break;
    case 1248: y=159;break;
    case 1249: y=160;break;
    case 1250: y=160;break;
    case 1251: y=161;break;
    case 1252: y=162;break;
    case 1253: y=163;break;
    case 1254: y=163;break;
    case 1255: y=164;break;
    case 1256: y=165;break;
    case 1257: y=166;break;
    case 1258: y=166;break;
    case 1259: y=167;break;
    case 1260: y=168;break;
    case 1261: y=168;break;
    case 1262: y=169;break;
    case 1263: y=170;break;
    case 1264: y=171;break;
    case 1265: y=171;break;
    case 1266: y=172;break;
    case 1267: y=173;break;
    case 1268: y=174;break;
    case 1269: y=174;break;
    case 1270: y=175;break;
    case 1271: y=176;break;
    case 1272: y=176;break;
    case 1273: y=177;break;
    case 1274: y=178;break;
    case 1275: y=179;break;
    case 1276: y=179;break;
    case 1277: y=180;break;
    case 1278: y=181;break;
    case 1279: y=182;break;
    case 1280: y=182;break;
    case 1281: y=183;break;
    case 1282: y=184;break;
    case 1283: y=185;break;
    case 1284: y=185;break;
    case 1285: y=186;break;
    case 1286: y=187;break;
    case 1287: y=188;break;
    case 1288: y=188;break;
    case 1289: y=189;break;
    case 1290: y=190;break;
    case 1291: y=191;break;
    case 1292: y=191;break;
    case 1293: y=192;break;
    case 1294: y=193;break;
    case 1295: y=193;break;
    case 1296: y=194;break;
    case 1297: y=195;break;
    case 1298: y=196;break;
    case 1299: y=196;break;
    case 1300: y=197;break;
    case 1301: y=198;break;
    case 1302: y=199;break;
    case 1303: y=199;break;
    case 1304: y=200;break;
    case 1305: y=201;break;
    case 1306: y=202;break;
    case 1307: y=202;break;
    case 1308: y=203;break;
    case 1309: y=204;break;
    case 1310: y=205;break;
    case 1311: y=205;break;
    case 1312: y=206;break;
    case 1313: y=207;break;
    case 1314: y=208;break;
    case 1315: y=208;break;
    case 1316: y=209;break;
    case 1317: y=210;break;
    case 1318: y=211;break;
    case 1319: y=211;break;
    case 1320: y=212;break;
    case 1321: y=213;break;
    case 1322: y=214;break;
    case 1323: y=214;break;
    case 1324: y=215;break;
    case 1325: y=216;break;
    case 1326: y=217;break;
    case 1327: y=217;break;
    case 1328: y=218;break;
    case 1329: y=219;break;
    case 1330: y=220;break;
    case 1331: y=220;break;
    case 1332: y=221;break;
    case 1333: y=222;break;
    case 1334: y=223;break;
    case 1335: y=223;break;
    case 1336: y=224;break;
    case 1337: y=225;break;
    case 1338: y=226;break;
    case 1339: y=226;break;
    case 1340: y=227;break;
    case 1341: y=228;break;
    case 1342: y=229;break;
    case 1343: y=229;break;
    case 1344: y=230;break;
    case 1345: y=231;break;
    case 1346: y=232;break;
    case 1347: y=233;break;
    case 1348: y=233;break;
    case 1349: y=234;break;
    case 1350: y=235;break;
    case 1351: y=236;break;
    case 1352: y=236;break;
    case 1353: y=237;break;
    case 1354: y=238;break;
    case 1355: y=239;break;
    case 1356: y=239;break;
    case 1357: y=240;break;
    case 1358: y=241;break;
    case 1359: y=242;break;
    case 1360: y=242;break;
    case 1361: y=243;break;
    case 1362: y=244;break;
    case 1363: y=245;break;
    case 1364: y=246;break;
    case 1365: y=246;break;
    case 1366: y=247;break;
    case 1367: y=248;break;
    case 1368: y=249;break;
    case 1369: y=249;break;
    case 1370: y=250;break;
    case 1371: y=251;break;
    case 1372: y=252;break;
    case 1373: y=252;break;
    case 1374: y=253;break;
    case 1375: y=254;break;
    case 1376: y=255;break;
    case 1377: y=256;break;
    case 1378: y=256;break;
    case 1379: y=257;break;
    case 1380: y=258;break;
    case 1381: y=259;break;
    case 1382: y=259;break;
    case 1383: y=260;break;
    case 1384: y=261;break;
    case 1385: y=262;break;
    case 1386: y=263;break;
    case 1387: y=263;break;
    case 1388: y=264;break;
    case 1389: y=265;break;
    case 1390: y=266;break;
    case 1391: y=267;break;
    case 1392: y=267;break;
    case 1393: y=268;break;
    case 1394: y=269;break;
    case 1395: y=270;break;
    case 1396: y=270;break;
    case 1397: y=271;break;
    case 1398: y=272;break;
    case 1399: y=273;break;
    case 1400: y=274;break;
    case 1401: y=274;break;
    case 1402: y=275;break;
    case 1403: y=276;break;
    case 1404: y=277;break;
    case 1405: y=278;break;
    case 1406: y=278;break;
    case 1407: y=279;break;
    case 1408: y=280;break;
    case 1409: y=281;break;
    case 1410: y=281;break;
    case 1411: y=282;break;
    case 1412: y=283;break;
    case 1413: y=284;break;
    case 1414: y=285;break;
    case 1415: y=285;break;
    case 1416: y=286;break;
    case 1417: y=287;break;
    case 1418: y=288;break;
    case 1419: y=289;break;
    case 1420: y=289;break;
    case 1421: y=290;break;
    case 1422: y=291;break;
    case 1423: y=292;break;
    case 1424: y=293;break;
    case 1425: y=293;break;
    case 1426: y=294;break;
    case 1427: y=295;break;
    case 1428: y=296;break;
    case 1429: y=297;break;
    case 1430: y=297;break;
    case 1431: y=298;break;
    case 1432: y=299;break;
    case 1433: y=300;break;
    default:y=255;break;
  }
  return y;
}

void SerialcomT(void){  
      byte kx,chkdata;
      kx=read_SCA100TT(RWTR);
      chkdata =kx^0x55^0xAA;
      Serial.write(0x55);
      Serial.write(0xaa);  
      Serial.write(kx);         
      Serial.write(chkdata); 
}

void SerialcomtT(int x,int y){
     byte kx,kkx,ky,kky,chkdata,xx;
      xx=read_SCA100TT(RWTR);
      kx=x;
      kkx=(x>>8); 
      ky=y;
      kky=(y>>8);
      chkdata =xx^kx^kkx^ky^kky^0x55^0xAA;
      Serial.write(0x55);
      Serial.write(0xaa);  
      Serial.write(kkx); 
      Serial.write(kx); 
      Serial.write(kky); 
      Serial.write(ky); 
      Serial.write(xx);       
      Serial.write(chkdata); 
}


void Serialcomjd(int x){
     byte kx,kkx,ky,kky,chkdata;
     kx=x;
     kkx=(x>>8); 
       
     chkdata =kx^kkx^0x55^0xAA;
     Serial.write(0x55);
     Serial.write(0xaa);  
     Serial.write(kkx); 
     Serial.write(kx);       
     Serial.write(chkdata); 
}

void Serialcom(int x,int y)
{
     byte kx,kkx,ky,kky,chkdata;
         kx=x;
         kkx=(x>>8); 
         ky=y;
         kky=(y>>8);
      chkdata =kx^kkx^ky^kky^0x55^0xAA;
      Serial.write(0x55);
      Serial.write(0xaa);  
      Serial.write(kkx); 
      Serial.write(kx); 
      Serial.write(kky); 
      Serial.write(ky);         
      Serial.write(chkdata); 

}

void ledshow(int x,int y){
    if(x>1052)
    PORTD |=0x10;//PD4+
    else if(x<995)
    PORTC |=(0x01);//PC0-
    else
     PORTB |=(0x02);//PB1//00
    if(y>1052)
     PORTC |=(0x02);//PC1+
    else if(y<995)
     PORTD |=(0x80);  //PD7-
    else
    PORTB|=(0x02);//PB1//00
}

void ledalloff(void){
     ///Y
     PORTC &=(~0x04);//PC2
     PORTC &=(~0x02);//PC1
     PORTC &=(~0x08);//PC3
     PORTB &=(~0x01);//PB0
     PORTD &=(~0x80);  //PD7
     PORTD &=(~0x40); //PD6
     //
     PORTB &=(~0x02);//PB1
     //X
     
     PORTC &=(~0x10);//PC4
     PORTC &=(~0x01);//PC0
     PORTC &=(~0x20);//PC5
     PORTD &=(~0x20);//PD5
     PORTD &=(~0x10);//PD4
     PORTD &=(~0x08);//PD3
}


void ledallon(void){
     PORTD |=0x80;
     PORTD |=0x40;
     PORTD |=0x20;
     PORTD |=0x10;
     PORTD |=0x08;
     PORTB |=0x01;
     PORTB |=0x02;
     PORTC |=0x01;
     PORTC |=0x02;
     PORTC |=0x04;
     PORTC |=0x08;
     PORTC |=0x10;
     PORTC |=0x20;
}

void leddisplay(int x,int y){
  
    if(x>1601){
        PORTD |=0x08;//PD3
    }else if((1365<x)&(x<=1601)) { 
        PORTD |=0x10;//PD4
     }else if((1052<x)&(x<=1365)){
         PORTD |=0x20;//PD5
      }else if((995<=x)&(x<=1052)){
          PORTB |=0x02;//PB1
       }else if((683<x)&(x<995)){
          PORTC |=0x20;//PC5 
        }else if((491<x)&(x<=683)){
            PORTC |=0x01;//PC0
         }else{
            PORTC |=0x10;//PC4
          }
     
   if(y>1601){
        PORTD |=0x40; //PD6 
   }else if((1365<y)&(y<=1601)){ 
         PORTD |=0x80;  //PD7
    }else if((1052<y)&(y<=1365)){
          PORTB |=0x01;//PB0 
     }else if((995<=y)&(y<=1052)){
           PORTB |=0x02;//PB1
      }else if((683<y)&(y<995)){
            PORTC |=0x08;//PC3  
       }else if((491<y)&(y<=683)){
             PORTC |=0x02;//PC1 
        }else{
             PORTC |=0x04;//PC2
         }
   
}

unsigned int read_SCA100TX(void){
  unsigned int result = 0;
  result=read_SCA100TXY(RDAX);
}

unsigned int read_SCA100TY(void){
  unsigned int result = 0;
  result=read_SCA100TXY(RDAY);
}

//Read SCA100TXY from the SCA100T
unsigned int read_SCA100TXY(byte thisValue){
    byte inByte = 0;           // incoming byte from the SPI
    unsigned int result = 0;   // result to return
      // digitalWrite(chipSelectPin, LOW);
      PORTB &= ~(1<<2);
    SPI.transfer(thisValue);  
    // delay(100);
    result = SPI.transfer(0x00);
    inByte = SPI.transfer(0x00);
    //digitalWrite(chipSelectPin, HIGH);
    PORTB |= (1<<2);
    result = result << 8;
    result = result | inByte;
    result = result >> 5;
    return(result);

}

byte read_SCA100TT(byte thisValue){
  byte result = 0;   // result to return
  PORTB &= ~(1<<2);
  SPI.transfer(thisValue); 
  result = SPI.transfer(0x00);
  PORTB |= (1<<2);
  return(result);
}

//Read from the SCA100T
unsigned int read_SCA100T(void ) {
  byte inByte = 0;           // incoming byte from the SPI
  unsigned int result = 0;   // result to return
  //digitalWrite(chipSelectPin, LOW);
     PORTB &= ~(1<<2);
  result = SPI.transfer(0x00);
  result = result << 8;
  inByte = SPI.transfer(0x00);
  //digitalWrite(chipSelectPin, HIGH);
   PORTB |= (1<<2);
   result = result | inByte;
   result = result >> 5;
   return(result);
}

//Sends a write command to SCP1000
void write_SCA100T(byte thisValue) {
  //digitalWrite(chipSelectPin, LOW);
  PORTB &= ~(1<<2);
  SPI.transfer(thisValue);  
  //digitalWrite(chipSelectPin, HIGH);
   PORTB |= (1<<2);
}

