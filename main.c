#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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
                system("mysqldump -P <your port> -h <yourip> -u <your user> -p<your pword> admin_db > /home/webadmin/backup.sql");
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
