#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

/*  This is the script created for checking status of wonky full stack web applcations
 *  
 *
 *  Author: Aaron Cowley
 *  Date: 04/16/18
 *  
 *
 */



#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

int main(void){
    int command;
    int run = 1;

    char buf[1000];
    time_t t = time(NULL);
    // options menu
    printf(RED"\n\n----------------pick an option----------------\n"RESET);
    printf(CYAN"option s: show status of websites\n"RESET);
    printf(CYAN"option b: backup\n"RESET);
    printf(CYAN"option q: exit the program\n"RESET);
    printf(CYAN"use sbq to show status backup db's and then quit\n"RESET);
    printf(RED"----------------------------------------------\n\n"RESET);
    

    do{
        printf(GREEN"# enter your command >>> "RESET);
        command = getchar(); //grabs character, allows for multiple to be passed in at once 
        // menu 
        switch(command){
            case 's':
                //store your status script in your home dir
                system("/home/webadmin/site_status.sh");
                break;
            case 'b':
                //change port number, IP, uname, and pword
                snprintf(buf, sizeof(buf), "mysqldump -P 3306 -h 192.168.50.19 -u webadmin -p admin_db > /home/webadmin/backup-%ld.sql", t/3600);
                system(buf);
                //redis backup
                snprintf(buf, sizeof(buf), "sudo cp /var/lib/redis/dump.rdb /home/webadmin/redis-backup-%ld", t/3600);
                system(buf);
                system("curl -XPUT 192.168.50.19:9200/_snapshot/my_backup -H \"Content-Type: application/json\" -d \'{\"type\": \"fs\",\"settings\": {\"location\": \"/home/webadmin/esearch\",\"compress\": true}}\'");
                system("curl -XGET '192.168.50.19:9200/_snapshot/my_backup/_all?pretty'");
                printf("TIME IS: %s", asctime(localtime(&t)));
                break;
            case 'q':
                //exits
                run = 0;
                break;
            default:
                break;
        }
        printf("\n");
        fflush(stdin);
        
    }while(run == 1);
}
