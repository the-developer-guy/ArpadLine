#include "SystemState.h"

static SystemState systemState = SYSTEMSTATE_DISARMED;

void systemEventHandler_sabotage(){
  if (systemState != SYSTEMSTATE_ALARM){
    systemState = SYSTEMSTATE_ALARM;
  }
}
void systemEventHandler_auth();/*param: user level*/
