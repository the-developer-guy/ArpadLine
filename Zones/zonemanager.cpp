#include <Arduino.h>
#include "zonemanager.h"

static zone_t zones[MAX_NUMBER_OF_ZONES];

void zoneManager_resetZone(unsigned int zoneIndex){
  zones[zoneIndex].state = ZONE_STATE_UNUSED;
  zones[zoneIndex].type = ZONE_TYPE_NULL;
  zones[zoneIndex].deviceHandler = 0;
  zones[zoneIndex].partitionFlag = 0;
}
void zoneManager_setZoneState(unsigned int zoneIndex, ZoneState zoneState){
  zones[zoneIndex].state = zoneState;
}
byte zoneManager_getZoneState(unsigned int zoneIndex){
  return zones[zoneIndex].state;
}
void zoneManager_setZoneType(unsigned int zoneIndex, ZoneType zoneType){
  zones[zoneIndex].type = zoneType;
}
byte zoneManager_getZoneType(unsigned int zoneIndex){
  return zones[zoneIndex].type;
}
void zoneManager_addZoneToPartition(unsigned int zoneIndex, unsigned int partitionIndex){
  uint16_t mask = 1 << partitionIndex;
  zones[zoneIndex].partitionFlag |= mask; 
}
void zoneManager_removeZoneFromPartition(unsigned int zoneIndex, unsigned int partitionIndex){
  uint16_t mask = 1 << partitionIndex;
  zones[zoneIndex].partitionFlag &= ~mask;
}
bool zoneManager_isZoneInpartition(unsigned int zoneIndex, unsigned int partitionIndex){
  uint16_t mask = 1 << partitionIndex; 
  return (zones[zoneIndex].partitionFlag & mask) != 0;  
}
int zoneManager_bindDeviceToZone(unsigned int zoneIndex, ZoneType zoneType, deviceHandler_t deviceHandler, bool force){
  if(zones[zoneIndex].state != ZONE_STATE_UNUSED && !force){
    return -1;
  }
  zones[zoneIndex].state = ZONE_STATE_INACTIVE;
  zones[zoneIndex].type = zoneType;
  zones[zoneIndex].deviceHandler = 0;
  zones[zoneIndex].partitionFlag = 0;
  return 0;
}
void zoneManager_checkAllZones(){
  checkresult_t checkResult;
  
  for(int zoneIndex = 0; zoneIndex < MAX_NUMBER_OF_ZONES; zoneIndex++){
    if(zones[zoneIndex].state < ZONE_STATE_ARMED)
    {
      continue;
    }
    if(zones[zoneIndex].deviceHandler){
      if(zones[zoneIndex].deviceHandler(zoneIndex, &checkResult) == -1){
       /*
        * -1-gyel tért vissza, teendő van a checkResult alapján.
        * 
        * Itt jönnek képbe a particiók? 
        * Vagy csak csoportos zone.state állítással le van tudva?
        * 
        * VAGY:
        * Ki értesíti a SystemStatet? 
        * Az eszköz állíthatná a zóna állapotát (zoneManager_(zoneIndex) hívással)?
        * Esetleg a systemState, ha az ezköz értesíti őt?
        */
      }
      else {
        /*
         * Minden OK valószínűleg nincs teendő, nem kell ez az ág.
         */
      }
    }
    else
    {
      /*
       * A zóna élesítve van, de nincs eszköz hozzá. Lehet ilyen?
       */
    }
    
  }
}
