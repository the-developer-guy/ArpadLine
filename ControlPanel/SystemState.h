#include "Arduino.h"
typedef enum SystemState{/*eseményeket felvinni*/
  SYSTEMSTATE_INIT, /*Alapállapot közvetlen indulás után. A systemEventHandler_init() függvény lefutása után vált át, ha ebben a függvényben bármi történik akkor SYSTEMSTATE_INIT állapotban marad..*/
  SYSTEMSTATE_DISARMED,
  SYSTEMSTATE_ALARM,
  SYSTEMSTATE_ARMING_DELAYED,
  SYSTEMSTATE_ARMED,
  SYSTEMSTATE_SILENT_ALARM,
  SYSTEMSTATE_TAMPER,
  SYSTEMSTATE_SILENT_TAMPER,
  SYSTEMSTATE_SILENT_PANIC,
  SYSTEMSTATE_PANIC,
  SYSTEMSTATE_MAINTANANCE
};

void systemEventHandler_sabotage(int zoneNumber, int userLevel);
/*
 Zóna szabotázs esetén hívjuk meg. A "zóna szabotázs" függvény hívja meg, átadja a szabotázsban lévő zóna számát.
 Ha az authUser = 0, akkor meghívjuk a "riasztás" függvényt. Különben:
   - Ha a SystemState:
     - SYSTEMSTATE_INIT: Ha a korábbi SystemState nem SYSTEMSTATE_INIT vagy SYSTEMSTATE_MAINTANANCE. Akkor meghívjuk a "riasztás" függvényt. Különben nem történik semmi.
     - SYSTEMSTATE_DISARMED: Ha az userLevel:
                             - 0 (Nincs belépve senki): Akkor meghívjuk a "riasztás" függvényt.
                             - 1 (Telepítő): Nem történik semmi.
                             - 2 (Admin): Meghívjuk a "zonePermissionLevel" függvényt a zonaNumber-rel és a userLevel-lel, ez visszaad egy boolean-t. 
                                         Ha a "zonePermissionLevel" függvény igaz, akkor nem történik semmi. Különben meghívjuk a "riasztás" függvényt.
                             - 3 (Emelt szintű user): Akkor meghívjuk a "riasztás" függvényt.
                             - 4 (User): Akkor meghívjuk a "riasztás" függvényt.
     - SYSTEMSTATE_ARMED: Akkor meghívjuk a "riasztás" függvényt. 
     - SYSTEMSTATE_SILENT_ALARM: Akkor meghívjuk a "riasztás" függvényt. 
     SystemState = SYSTEMSTATE_TAMPER
 */
void systemEventHandler_auth(int userLevel);/*Ez minek is kell????*/
/*
    - Ha a SystemState:
     - SYSTEMSTATE_DISARMED: Ha az userLevel:
                             - 0 (Nincs belépve senki, élesítő kód): 
                             - 1 (Telepítő): Nem történik semmi.
                             - 2 (Admin): Meghívjuk a "zonePermissionLevel" függvényt a zonaNumber-rel és a userLevel-lel, ez visszaad egy boolean-t. 
                                         Ha a "zonePermissionLevel" függvény igaz, akkor nem történik semmi. Különben meghívjuk a "riasztás" függvényt.
                             - 3 (Emelt szintű user): Akkor meghívjuk a "riasztás" függvényt.
                             - 4 (User): Akkor meghívjuk a "riasztás" függvényt.
     - SYSTEMSTATE_ARMED: Akkor meghívjuk a "riasztás" függvényt. 
     - SYSTEMSTATE_SILENT_ALARM: Akkor meghívjuk a "riasztás" függvényt. 
     - SYSTEMSTATE_ALARM: 
     - SYSTEMSTATE_SILENT_TAMPER:
     - SYSTEMSTATE_PANIC: 
     - SYSTEMSTATE_ARMING_DELAYED:
 */
void systemEventHandler_alarm();
/*
    - Ha a SystemState:
     - SYSTEMSTATE_DISARMED, SYSTEMSTATE_INIT, SYSTEMSTATE_MAINTANANCE, SYSTEMSTATE_SILENT_PANIC, SYSTEMSTATE_ALARM: figyelmen kívül hagyjuk.
     - SYSTEMSTATE_ARMING_DELAYED: propertyben meghatározott delayTime elteltére vár NTC szerin
     - Minden más esetben "riasztás"
     SystemState = SYSTEMSTATE_ALARM
     Amíg az RTC nem éri el a property-ben meghatározott silent időt, addíg riaszt, 
     utánna meghívni a systemEventHandler_silentAlarm() függvényt.
 */
void systemEventHandler_silentAlarm(); /*Kell ez nekünk? Vagy saját maga vizsgálja a sileenthez szükséges időt*/
/*
  - Propertyben meghatározott silentAlarmDelay eltelte után a riasztást néma állapotra teszi.
  SystemState = SYSTEMSTATE_SILENT_ALARM
 */
void systemEventHandler_panicAlarm();/*param: user level*/
/*  
  SystemState = SYSTEMSTATE_PANIC
  meghívni a systemEventHandler_alarm() függvényt
 */
void systemEventHandler_silentTamper();/*param: user level*/
/*
  
 */
byte systemEventHandler_arm();
/*
 Ezt az autentikáció után hívjuk meg. 
 Hiba kóddal térünk vissza:
 - 0: Ha minden rendben ment és élesedett
 - 1: Ha élesítve volt és újra élesíteni akartuk. Ettől függetlenül "újra" élesítjük.
 - 2: Ha a "sértett zóna" függvény nem 0-val tér vissza. Ez esetben nem élesítünk.
 - 3: Ha a "zóna szabotázs" függvény nem 0-val tér vissza. Ez esetben nem élesítünk.
 SystemState változik SYSTEMSTATE_ARMED.  
 */
void systemEventHandler_init();
void systemEventHandler_disarm();
