#include <pebble.h>

#define  PERSIST_PROJECT_NAME_1 (uint32_t) 1
#define  PERSIST_PROJECT_NAME_2 (uint32_t) 2
#define  PERSIST_PROJECT_NAME_3 (uint32_t) 3
#define  PERSIST_CFG_VIB_7_WORK (uint32_t) 4
#define  PERSIST_CFG_VIB_7_HOME (uint32_t) 5
#define  PERSIST_INT_ACTIVE_PROJECT (uint32_t) 6


void STORE_setProjectName_1(char name[20]){
  persist_write_string(PERSIST_PROJECT_NAME_1, name);
}

char* STORE_getProjectName_1()
{
  char *retValue = malloc(sizeof(char)*20);
  persist_read_string(PERSIST_PROJECT_NAME_1, retValue, sizeof(retValue));
  return retValue;
}

void STORE_setProjectName_2(char name[20]){
  persist_write_string(PERSIST_PROJECT_NAME_2, name);
}

char* STORE_getProjectName_2()
{
  char *retValue = malloc(sizeof(char)*20);
  persist_read_string(PERSIST_PROJECT_NAME_2, retValue, sizeof(retValue));
  return retValue;
}

void STORE_setProjectName_3(char name[20]){
  persist_write_string(PERSIST_PROJECT_NAME_3, name);
}

char* STORE_getProjectName_3()
{
  char *retValue = malloc(sizeof(char)*20);
  persist_read_string(PERSIST_PROJECT_NAME_3, retValue, sizeof(retValue));
  return retValue;
}

bool STORE_boGetVibrate7MinBeforeWork()
{
  return persist_read_bool(PERSIST_CFG_VIB_7_WORK);
}

void STORE_voSetVibrate7MinBeforeWork(bool value)
{
  persist_write_bool(PERSIST_CFG_VIB_7_WORK, value);
}

bool STORE_boGetVibrate7MinBeforeHome()
{
  return persist_read_bool(PERSIST_CFG_VIB_7_HOME);
}

void STORE_voSetVibrate7MinBeforeHome(bool value)
{
  persist_write_bool(PERSIST_CFG_VIB_7_HOME, value);
}

int8_t STORE_boGetActiveProject()
{
  return persist_read_int(PERSIST_INT_ACTIVE_PROJECT);
}

void STORE_voSetActiveProject(bool value)
{
  persist_write_int(PERSIST_INT_ACTIVE_PROJECT, value);
}


