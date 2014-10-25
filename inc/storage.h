/*
 * storage.h
 *
 *  Created on: Oct 25, 2014
 *      Author: weldeborn
 */

#ifndef INC_STORAGE_H_
#define INC_STORAGE_H_

void STORE_setProjectName_1(const char name[]);
char* STORE_getProjectName_1(void);

void STORE_setProjectName_2(const char name[20]);
char* STORE_getProjectName_2(void);

void STORE_setProjectName_3(const char name[20]);
char* STORE_getProjectName_3(void);

bool STORE_boGetVibrate7MinBeforeWork(void);
void STORE_voSetVibrate7MinBeforeWork(bool value);

bool STORE_boGetVibrate7MinBeforeHome(void);
void STORE_voSetVibrate7MinBeforeHome(bool value);

int8_t STORE_boGetActiveProject();
void STORE_voSetActiveProject(bool value);

#endif /* INC_STORAGE_H_ */
