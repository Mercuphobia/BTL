#include <stdio.h>
#include <stdlib.h>
#include "parsers_option.h"
#include "hello.h"

int main(int argc, char *argv[]){
	printHello();
	parsers_option(argc,argv);
	return 0;
}
