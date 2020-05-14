#ifndef ZONEMANAGER_H_INCLUDED
#define ZONEMANAGER_H_INCLUDED

#define MAX_NUMBER_OF_ZONES       128
#define MAX_NUMBER_OF_PARTITIONS  16

enum ZoneState {
  ZONE_STATE_UNUSED,
  ZONE_STATE_INACTIVE,
  ZONE_STATE_DISARMED,
  ZONE_STATE_SABOTAGE,
  ZONE_STATE_ARMED
};

enum ZoneType {
  ZONE_TYPE_NULL,
  ZONE_TYPE_NORMAL,
  ZONE_TYPE_DELAYED,
  ZONE_TYPE_SABOTAGE,
  ZONE_TYPE_KEY,
  ZONE_TYPE_FIRE,
  ZONE_TYPE_WATER,
  ZONE_TYPE_ICE,
  ZONE_TYPE_SMOG
};

struct checkresult_t {
  int data1;
  int data2;
  /* 
   * Nem tudom, hány adatot kell majd visszakapni 
   * lehet,hogy nincs is szükség rá.
   */
};

typedef int (*deviceHandler_t)(int, checkresult_t*);

struct zone_t {
  byte state;
  byte type;
  deviceHandler_t deviceHandler;
  uint16_t partitionFlag;
};

void zoneManager_resetZone(unsigned int zoneIndex);
void zoneManager_setZoneState(unsigned int zoneIndex, ZoneState zoneState);
byte zoneManager_getZoneState(unsigned int zoneIndex);
void zoneManager_setZoneType(unsigned int zoneIndex, ZoneType zoneType);
byte zoneManager_getZoneType(unsigned int zoneIndex);
void zoneManager_addZoneToPartition(unsigned int zoneIndex, unsigned int partitionIndex);
void zoneManager_removeZoneFromPartition(unsigned int zoneIndex, unsigned int partitionIndex);
bool zoneManager_isZoneInpartition(unsigned int zoneIndex, unsigned int partitionIndex);
int zoneManager_bindDeviceToZone(unsigned int zoneIndex, ZoneType zoneType, deviceHandler_t deviceHandler);
void zoneManager_checkBoundedDevices();

#endif //ZONEMANAGER_H_INCLUDED
