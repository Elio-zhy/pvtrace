/********************************************************************
 * File: instrument.c
 *
 * Instrumentation source -- link this with your application, and
 *  then execute to build trace data file (trace.txt).
 *
 * Author: M. Tim Jones <mtj@mtjones.com>
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* Start address of text section */
extern char __executable_start;

/* Function prototypes with attributes */
void main_constructor( void )
	__attribute__ ((no_instrument_function, constructor));

void main_destructor( void )
	__attribute__ ((no_instrument_function, destructor));

void __cyg_profile_func_enter( void *, void * ) 
	__attribute__ ((no_instrument_function));

void __cyg_profile_func_exit( void *, void * )
	__attribute__ ((no_instrument_function));


static FILE *fp;


void main_constructor( void )
{
  fp = fopen( "trace.txt", "w" );
  if (fp == NULL) exit(-1);
}


void main_deconstructor( void )
{
  fclose( fp );
}


void __cyg_profile_func_enter( void *this, void *callsite )
{
  fprintf(fp, "E0x%lx\n", (size_t)this - (size_t)&__executable_start);
}


void __cyg_profile_func_exit( void *this, void *callsite )
{
  fprintf(fp, "X0x%lx\n", (size_t)this - (size_t)&__executable_start);
}

