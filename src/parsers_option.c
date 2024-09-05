#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "log.h"

// bien kiem tra de ko chay truong trinh in ra hello
int stop_execution = 0;
int scan_option = 0;
void print_help(){
    printf("Options:\n");
    printf("  -d, --debug <val>     Set log level (0=Disabled, 1=Error, 2=Warn, 3=Debug)\n");
    printf("  -i, --interface<val> Scan interface (None=all, 1=2G, 2=5G)\n");
    printf("  -h, --help            Print message and exit\n");
}

void scan_wifi(int scan_option) {
    if(scan_option == 0){
        printf("Scanning 2G and 5G...\n");
    }
    else if (scan_option == 1) {
        //scan 2G
        printf("Scanning 2G...\n");
    } else if (scan_option == 2) {
        //scan 5G
        printf("Scanning 5G...\n");
    }
}

void parsers_option(int argc, char *argv[])
{
    int option;
    while (1)
    {
        static struct option long_options[] =
            {
                {"help", no_argument, 0, 'h'},
                {"debug", required_argument, 0, 'd'},
                {"interface", optional_argument, 0, 'i'},
                {0, 0, 0, 0}};
        /* getopt_long stores the option index here. */
        int option_index = 0;

        option = getopt_long(argc, argv, "hd:i::",
                        long_options, &option_index);

        /* Detect the end of the options. */
        if (option == -1)
            break;

        switch (option)
        {
        case 0:
            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0)
                break;
            printf("option %s", long_options[option_index].name);
            if (optarg)
                printf(" with arg: %s", optarg);
            printf("\n");
            break;
        
        case 'd':
        {
            stop_execution = 1;
            int log_level = atoi(optarg);
            log_set_level(log_level);
            break;
        }

        case 'i':
            stop_execution = 1;
            if(optarg){
                scan_option = atoi(optarg);
            }
            else{
                scan_option = 0;
            }
            printf("scan_option = %d\n", scan_option);
            scan_wifi(scan_option);
            break;

        case 'h':
            stop_execution = 1;
            printf("Usage: %s [options] [target]...\n", argv[0]);
            print_help();
            break;

        case '?':
            /* getopt_long already printed an error message. */
            break;

        default:
            fprintf(stderr, "Usage: %s [-d loglevel] [-i interface]\n", argv[0]);
        }
    }

    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        putchar('\n');
    }
    LOG(LOG_LVL_ERROR, "%s, %d: test3\n", __func__, __LINE__);
    LOG(LOG_LVL_WARN, "%s, %d: test4\n", __func__, __LINE__);
    LOG(LOG_LVL_DEBUG, "%s, %d: test5\n", __func__, __LINE__);
}
