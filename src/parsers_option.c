#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>


// void parsers_option(int argc, char *argv[]){
//     // int flags = 0;
//     // int nsecs = 0;
//     // int tfnd = 0;
//     int opt;

//     while((opt = getopt(argc, argv, "nt:x:")) != -1){
//         switch(opt){
//             case 'n':
//                 // flags = 1;
//                 printf("in ra n\n");
//                 break;
//             case 't':
//                 // nsecs = atoi(optarg);
//                 printf("value = %s\t",optarg);
//                 printf("in ra t\n");
//                 // tfnd = 1;
//                 break;
//             case 'x':
//                 // nsecs = atoi(optarg);
//                 printf("value = %s\t",optarg);
//                 printf("in ra x\n");
//                 // tfnd = 1;
//                 break;
//             default: /* '?' */
//                 fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
//                 exit(1);
//         }
//     }
//     // printf("flags=%d; tfnd=%d; nsecs=%d; option=%d\n",flags,tfnd,nsecs,optind);
//     // printf("v_opterr = %d; v_optopt = %d; v_optind = %d; v_optarg = %s\n",opterr,optopt,optind,optarg);

//     if(optind >= argc){
//         fprintf(stderr, "ko doi so nao thi nhay vao cai nay\n");
//         exit(1);
//     }
//     //xu ly cac doi so khong phai tuy chon
//     printf("ten doi so neu khong di voi cai nao = %s\n",argv[optind]);
//     exit(0);
// }


static int verbose_flag;

// bien kiem tra de ko chay truong trinh in ra hello
int stop_execution = 0;

void parsers_option(int argc, char *argv[])
{
    int c;

    while (1)
    {
        static struct option long_options[] =
            {
                /* These options set a flag. */
                {"verbose", no_argument, &verbose_flag, 1},
                {"brief", no_argument, &verbose_flag, 0},
                {"config", required_argument, 0, 0},
                /* These options don’t set a flag.
                   We distinguish them by their indices. */
                {"add", no_argument, 0, 'a'},
                {"append", no_argument, 0, 'b'},
                {"delete", required_argument, 0, 'd'},
                {"create", required_argument, 0, 'c'},
                {"file", required_argument, 0, 'f'},
                {"test-x", required_argument, 0, 'x'},
                {"help", no_argument, 0, 'h'},
                {0, 0, 0, 0}};
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "abc:d:f:x:h",
                        long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
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

        case 'a':
            stop_execution = 1;
            printf("lua chon a\n");
            break;

        case 'b':
            stop_execution = 1;
            printf("lua chon b\n");
            break;

        case 'c':
            stop_execution = 1;
            printf("option -c with value %s\n", optarg);
            break;

        case 'd':
            stop_execution = 1;
            printf("option -d with value = `%s'\n", optarg);
            break;

        case 'f':
            stop_execution = 1;
            printf("option -f with value =`%s'\n", optarg);
            break;

        case 'x':
            stop_execution = 1;
            printf("option -x with value = `%s'\n", optarg);
            break;

        case 'h':
            stop_execution = 1;
            printf("Usage: %s [options] [target]...\n", argv[0]);
            printf("Options:\n");
            printf("  -a, --add          Lua chon a\n");
            printf("  -b, --append       Lua chon b\n");
            printf("  -c, --create <val> Lua chon c\n");
            printf("  -f, --delete <val> Lua chon f\n");
            printf("  -x, --test-x <val> Lua chon x\n");
            printf("  -h, --help <val>   Lua chon h\n");
            break;

        case '?':
            /* getopt_long already printed an error message. */
            break;

        default:
            // abort();
            fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
        }
    }

    // In giá trị của brief_flag

    /* Instead of reporting ‘--verbose’
       and ‘--brief’ as they are encountered,
       we report the final status resulting from them. */
    if (verbose_flag)
    {
        printf("brief_flag = %d\n", verbose_flag);
        printf("verbose flag is set\n");
    }

    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        putchar('\n');
    }

    // exit(0);
}
