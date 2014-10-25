#include <pebble.h>

#define  PERSIST_PROJECT_NAME_1 (uint32_t) 1
#define  PERSIST_PROJECT_NAME_2 (uint32_t) 2
#define  PERSIST_PROJECT_NAME_3 (uint32_t) 3


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
