#ifndef _VAR_H_
#define _VAR_H_

//#include <pthread.h>
#include <netinet/in.h>

#define bool int
#define false 0
#define true 1

#define MAX_BUFF 1024
#define BACKLOG 10

#define mapHeight 20
#define mapWidth 10

typedef enum block
{
    Blank = 0, 
    DynSquare, 
    StatSquare, 
    Bound, 
    NextSquare, 
    TmpSquare
} block;

typedef struct CLIENT
{    
    int fd;    
    struct sockaddr_in addr;        
} CLIENT;

typedef struct Tetromino
{
    int id;
    char *name;
    int srs;
    int left[4];
    int right[4];
    int top[4];
    int buttom[4];
    int image[4][4][4];
} Tetromino;

extern Tetromino ts, tz, tl, tj, ti, to ,tt; 

#endif
