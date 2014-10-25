/*
 * tool.h
 *
 *  Created on: Oct 25, 2014
 *      Author: weldeborn
 */

#ifndef INC_TOOL_H_
#define INC_TOOL_H_

void TOOL_editTextLayer(TextLayer * text_layer, char text[] , GColor color, GTextAlignment align );
void TOOL_voDrawTimeline(GContext *ctx, int16_t minutes , char project[]);

#endif /* INC_TOOL_H_ */
