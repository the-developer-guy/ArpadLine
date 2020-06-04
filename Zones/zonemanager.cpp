#include <Arduino.h>
#include "ZoneManager.h"

zone_t zones[MAX_NUMBER_OF_ZONES];

typedef union{ 
   uint32_t value;
   uin lo, hi; } _intchars;

void zone_Manager_init(){
  /*
   * Állapot betöltése az eepromból (megszakítás)
   * zoneManager_initZone() egyenként az össze zónára
   */
}
void zoneManager_reset() {
  for(int zoneIndex = 0; zoneIndex < MAX_NUMBER_OF_ZONES; zoneIndex++){
    zoneManager_resetZone(zoneIndex);
  }  
}
void zoneManager_resetZone(unsigned int zoneIndex){
  zones[zoneIndex].state = ZONE_STATE_UNUSED;
  zones[zoneIndex].type = ZONE_TYPE_NULL;
  zones[zoneIndex].state_to_change = ZONE_STATE_UNUSED;
  zones[zoneIndex].state_change_delay = ZONE_STATE_CHANGE_DELAY;
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
void zoneManager_update(){
  ZoneState state;
  
  /*
   * if(system manager -> rendszer nincs élesítve) return;
   */

  for(int zoneIndex = 0; zoneIndex < MAX_NUMBER_OF_ZONES; zoneIndex++){
    if(zones[zoneIndex].state == ZONE_STATE_UNUSED){
      continue;
    }

    /*
     * ZoneState state = deviceManager_getState[zoneIndex];
     */
    
    if(state == zones[zoneIndex].state){
      continue;
    }
    if(state == zones[zoneIndex].state_to_change){
      if(zones[zoneIndex].state_change_delay > 0){
        zones[zoneIndex].state_change_delay -= 1;
      }
      else{
        zones[zoneIndex].state = state;
        /*
         * megváltozott az állapot, system managert értesíteni
         */
      }
    }
    else{
      zones[zoneIndex].state_to_change = state;
      zones[zoneIndex].state_change_delay = ZONE_STATE_CHANGE_DELAY;    
    }
  }
}
void zoneManager_initZone(unsigned int zoneIndex, uint32_t serializedData){
  zoneManager_resetZone(zoneIndex);
  
  unsigned int* partition_value_ptr = (unsigned int*)&serializedData;
  zones[zoneIndex].partitionFlag = *partition_value_ptr;
  
  byte* type_value_ptr = (byte*)&serializedData + 2;
  zones[zoneIndex].type = *type_value_ptr;
}
uint32_t zoneManager_serializeZone(unsigned int zoneIndex){
  uint32_t serializedData;

  unsigned int* partition_value_ptr = (unsigned int*)&serializedData;
  *partition_value_ptr = zones[zoneIndex].partitionFlag;
  
  byte* type_value_ptr = (byte*)&serializedData + 2;
   *type_value_ptr = zones[zoneIndex].type;

  return serializedData;
}

/*
B Terv

//a headerbe
struct zone_serialized_t{
  uint16_t partitionFlag;  
  byte type;
}

//akkor csak 3 byte kell
EEPROM.get(address, zone_serialized_t)
 
void zoneManager_initZone(unsigned int zoneIndex, zone_serialized_t& serializedData){
  zoneManager_resetZone(zoneIndex);
  zones[zoneIndex].partitionFlag = serializedData.partitionFlag;
  zones[zoneIndex].type = serializedData.type;
}
void zoneManager_serializeZone(unsigned int zoneIndex, zone_serialized_t& serializedData){
  serializedData.partitionFlag =  zones[zoneIndex].partitionFlag;
  serializedData.type =  zones[zoneIndex].type;
}
*/
