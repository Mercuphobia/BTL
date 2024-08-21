#include <stdio.h>
#include <stdlib.h>
#include "parsers_option.h"
#include "hello.h"


int main(int argc, char *argv[]){
	parsers_option(argc,argv);
	if(!stop_execution){
		printHello();
	}
	return 0;
}
