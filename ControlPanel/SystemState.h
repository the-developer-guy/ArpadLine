typedef enum SystemState{/*eseményeket felvinni*/
  SYSTEMSTATE_INIT,
  SYSTEMSTATE_DISARMED,
  SYSTEMSTATE_ALARM,
  SYSTEMSTATE_ARMING_DELAYED,
  SYSTEMSTATE_ARMED
};

void systemEventHandler_sabotage();
void systemEventHandler_auth();/*param: user level*/
void systemEventHandler_arm();
void systemEventHandler_init();
