/*
 * timer.c
 *
 *  Created on: Feb 21, 2017
 *      Author: sergo
 */
#include "timer.h"

void one_second_timer()
{
	int criteria = 1;

	clock_t start = clock();

	float currtime = 0;

	while (currtime < criteria)
		currtime = (clock() - start) / CLOCKS_PER_SEC;
}
