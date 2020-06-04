#ifndef ZONEMANAGER_H_INCLUDED
#define ZONEMANAGER_H_INCLUDED

#define MAX_NUMBER_OF_ZONES           64
#define MAX_NUMBER_OF_PARTITIONS      16
#define ZONE_STATE_CHANGE_DELAY       5
#define EEPROM_ZONES_START            0  // Az EEPROM managerben kellene definiálni
#define EEPROM_ZONE_STORAGE_SIZE      4

enum ZoneState {
  ZONE_STATE_UNUSED,
  ZONE_STATE_STANDBY,
  ZONE_STATE_INSULTED,
  ZONE_STATE_SABOTAGE,
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

struct zone_t {
  byte state;
  byte state_to_change;
  byte state_change_delay;
  byte type;
  uint16_t partitionFlag;
};

void zoneManager_init();
void zoneManager_reset();
void zoneManager_resetZone(unsigned int zoneIndex);
void zoneManager_setZoneState(unsigned int zoneIndex, ZoneState zoneState);
byte zoneManager_getZoneState(unsigned int zoneIndex);
void zoneManager_setZoneType(unsigned int zoneIndex, ZoneType zoneType);
byte zoneManager_getZoneType(unsigned int zoneIndex);
void zoneManager_addZoneToPartition(unsigned int zoneIndex, unsigned int partitionIndex);
void zoneManager_removeZoneFromPartition(unsigned int zoneIndex, unsigned int partitionIndex);
bool zoneManager_isZoneInPartition(unsigned int zoneIndex, unsigned int partitionIndex);
void zoneManager_update();
void zoneManager_initZone(unsigned int zoneIndex);
uint32_t zoneManager_serializeZone(unsigned int zoneIndex);

#endif //ZONEMANAGER_H_INCLUDED
