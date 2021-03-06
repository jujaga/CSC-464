/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *	Stephen Tredger, March 2012
 *
 *	timekeeper.h
 *		Used to gather timestamps for profiling of various functions.
 *		timekeepers are structures that hold up to a set of start/stop
 *		timestamps.
 */

#ifndef TIMEKEEPER
#define TIMEKEEPER


#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define T_EXIT_FAIL -1
#define GR_HOOK_LEN 2


// structure to hold timestamps 
typedef struct _timekeeper {
	struct timeval *start;
	struct timeval *stop;
	int max_times;
	int start_t_num;
	int stop_t_num;
	char *timefile;
	char gr_hook[GR_HOOK_LEN+1]; // +1 for NULL terminator
} timekeeper;


// allocates/clears memory for a timekeeper. filename is the file to print
//	timestamps to. Prints to stdout if filename is NULL. places the first 2
//	characters of the string hook in the gr_hook field of the timekeeper struct
timekeeper * create_timekeeper(int max_times, char *filename, char *hook);


// frees memory used by the timekeeper and nulls the pointer
void destroy_timekeeper(timekeeper *tk);


// attempts to record a timestamp in the start timeval array
//	will fail if the array already has max_times start timestamps
//	or the number or start timestamps doesn't equal the number of stop
void get_start_time(timekeeper *tk);


// attempts to record a timestamp in the stop timeval array
//	will fail if the number of stop timestamps is not exactly 
//	one less than the number of start timestamps
void get_stop_time(timekeeper *tk);


// prints sets of timestamps to the file timefile
//	each set of start/stop timestamps is printed to a line
//	preceded by the two characters in gr_hook.
//	Fails if the number of timestamps are not equal or timefile
//	cannot be opened
void print_timekeeper(timekeeper *tk);

#endif
