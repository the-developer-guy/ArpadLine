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
  SYSTEMSTATE_MAINTANANCE,
  SYSTEMSTATE_DOWNLOAD
};

void systemEventHandler_init();
/*
TO_USE: rendszer indításkor kell hívni, betölti a korábbi állapotot ha volt, vagy alapállapotot állít be.
*/

void systemEventHandler_sabotage(int zoneLevel, int userLevel);
/*
TO_USE: ha valamelyik zóna/partíció szabotázs állapotba kerül.
*/
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
TO_USE:
*/
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
int systemEventHandler_arm(int userLevel, bool delayed);
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
 User osztál hívja belépés után.
 Ha a SystemState: SYSTEMSTATE_ARMING_DELAYED, SYSTEMSTATE_ARMED, SYSTEMSTATE_MAINTANANCE, SYSTEMSTATE_DOWNLOAD akkor kiriaszt
 Ha a SystemState: SYSTEMSTATE_PANIC, SYSTEMSTATE_SILENT_PANIC, SYSTEMSTATE_SILENT_ALARM,   SYSTEMSTATE_ALARM: ha a userLevel elég magas akkor törli a riasztást, és kiriaszt.
 Ha a SystemState: SYSTEMSTATE_TAMPER, SYSTEMSTATE_SILENT_TAMPER: le kell kérni a tamperLevelt, ezt egyeztetni a user levellel. Ha feloldhatja a tamperLevelt, akkor riasztást törölni, egyéb esetben figyelmen kívül hagyni
 Ha a SystemState: SYSTEMSTATE_DISARMED, figyelmen kívül hagyni
 SystemState = SYSTEMSTATE_DISARMED
 */
void systemEventHandler_init();
/*
 Egyenlőre fogalmam sincs mit fog csinálni.
 */
void systemEventHandler_downloadeMode(int userLevel);
/*
 Későbbi letöltési módhoz előkészítés, a maintenance módból hozható elő, egy kb fél zombi állapot ahol a beállításokat, és klónozást lehet elvégezni.
 */
void systemEventHandler_maintenanceMode();
/*
 Kezelő hívja meg, hogy telepítő vagy maintenance módba kerüljön a rendszer. Ezt a userLevel dönti el, hogy mire van jogosultság. 
 */
