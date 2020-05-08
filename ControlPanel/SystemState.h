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

void systemEventHandler_sabotage(int zoneLevel, int userLevel);
/*
 Zóna szabotázs esetén hívjuk meg. A zóna kezelő osztály hívja meg, átadja a szabotázsban lévő zóna számát, és ha van a bejelentkezett felhasználó szintjét.
 Ha a userLevel = 0, akkor meghívjuk a "riasztás" függvényt. Különben:
   - Ha a SystemState:
     - SYSTEMSTATE_INIT: Ha a korábbi SystemState nem SYSTEMSTATE_INIT vagy SYSTEMSTATE_MAINTANANCE. Akkor meghívjuk a "riasztás" függvényt. Különben nem történik semmi.
     - SYSTEMSTATE_DISARMED: Ha az userLevel:
                             - 0 (Nincs belépve senki): Akkor meghívjuk a "riasztás" függvényt.
                             - 1 (Telepítő): Nem történik semmi.
                             - 2 (Admin): Ha a zoneLevel az admin szintnek megfelelő, akkor nem történik semmi, ha annál magasabb akkor hívjuk az "alarm" függvényt
                             - 3 (Emelt szintű user): Akkor meghívjuk a "riasztás" függvényt.
                             - 4 (User): Akkor meghívjuk a "riasztás" függvényt.
     - SYSTEMSTATE_ARMED: Akkor meghívjuk a "riasztás" függvényt. 
     - SYSTEMSTATE_SILENT_ALARM: Akkor meghívjuk a "riasztás" függvényt. 
     SystemState = SYSTEMSTATE_TAMPER
 */
void systemEventHandler_alarm(int zoneLevel, bool delayed);
/*
    - Ha a SystemState:
     - SYSTEMSTATE_DISARMED, SYSTEMSTATE_INIT, SYSTEMSTATE_DOWNLOAD, SYSTEMSTATE_MAINTANANCE, SYSTEMSTATE_SILENT_PANIC, SYSTEMSTATE_ALARM: figyelmen kívül hagyjuk.
     - Minden más esetben a delayed idő kivárása után "riasztás"
     SystemState = SYSTEMSTATE_ALARM
 */
void systemEventHandler_silentAlarm(bool panic, int delayToAlarm); /*Kell ez nekünk? Vagy saját maga vizsgálja a silenthez szükséges időt*/
/*
  - Propertyben meghatározott silentAlarmDelay eltelte után a riasztást néma állapotra teszi.
  SystemState = SYSTEMSTATE_SILENT_ALARM
 */
byte systemEventHandler_arm(int userLevel, bool delayed);
/*
 Ezt az autentikáció után hívjuk meg. 
 Hiba kóddal térünk vissza:
 - 0: Ha minden rendben ment és élesedett
 - 1: Ha élesítve volt és újra élesíteni akartuk. Ettől függetlenül "újra" élesítjük.
 - 2: Ha a "sértett zóna" függvény nem 0-val tér vissza. Ez esetben nem élesítünk.
 - 3: Ha a "zóna szabotázs" függvény nem 0-val tér vissza. Ez esetben nem élesítünk.
 SystemState változik SYSTEMSTATE_ARMED.  
 */
byte systemEventHandler_disarm(int userLevel);
/*
 
 */
void systemEventHandler_init();
void systemEventHandler_downloadeMode();
void systemEventHandler_maintenanceMode();
