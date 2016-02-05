#include "vars.h"

int thread_num = 0; 
int tetros[MAX_BUFF] = {0};
int tetros_num[MAX_BUFF] = {0};
int interval_coef = 100;
int scores[BACKLOG] = {0};
int nexts[BACKLOG] = {0};
int maptops[BACKLOG] = {0};
bool thread_begin = false;
bool crashs[BACKLOG] = {false};
bool overs[BACKLOG] = {false};
char names[BACKLOG][12];
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t crash_mutex = PTHREAD_MUTEX_INITIALIZER;
block maps[BACKLOG][mapHeight+1][mapWidth] = {Blank};

Tetromino ts = 
{
    .id     = 0,
    .name   = "ts",
    .left   = {0, 1, 0, 0},
    .right  = {2, 2, 2, 1},
    .top    = {0, 0, 1, 0},
    .buttom = {1, 2, 2, 2},

    .image = {{0, 1, 1, 0,
               1, 1, 0, 0,
               0, 0, 0, 0,
               0, 0, 0, 0},

              {0, 1, 0, 0,
               0, 1, 1, 0,
               0, 0, 1, 0,
               0, 0, 0, 0},

              {0, 0, 0, 0,
               0, 1, 1, 0,
               1, 1, 0, 0,
               0, 0, 0, 0},

              {1, 0, 0, 0,
               1, 1, 0, 0,
               0, 1, 0, 0,
               0, 0, 0, 0}}
};

Tetromino tz =
{
    .id     = 1,
    .name   = "tz",
    .left   = {0, 1, 0, 0},
    .right  = {2, 2, 2, 1},
    .top    = {0, 0, 1, 0},
    .buttom = {1, 2, 2, 2},

    .image = {{1, 1, 0, 0,
               0, 1, 1, 0,
               0, 0, 0, 0,
               0, 0, 0, 0},

              {0, 0, 1, 0,
               0, 1, 1, 0,
               0, 1, 0, 0,
               0, 0, 0, 0},

              {0, 0, 0, 0,
               1, 1, 0, 0,
               0, 1, 1, 0,
               0, 0, 0, 0},

              {0, 1, 0, 0,
               1, 1, 0, 0,
               1, 0, 0, 0,
               0, 0, 0, 0}}
};

Tetromino tl = 
{
    .id     = 2,
    .name   = "tl",
    .left   = {0, 1, 0, 0},
    .right  = {2, 2, 2, 1},
    .top    = {0, 0, 1, 0},
    .buttom = {1, 2, 2, 2},

    .image = {{0, 0, 1, 0,
               1, 1, 1, 0,
               0, 0, 0, 0,
               0, 0, 0, 0},

              {0, 1, 0, 0,
               0, 1, 0, 0,
               0, 1, 1, 0,
               0, 0, 0, 0},

              {0, 0, 0, 0,
               1, 1, 1, 0,
               1, 0, 0, 0,
               0, 0, 0, 0},

              {1, 1, 0, 0,
               0, 1, 0, 0,
               0, 1, 0, 0,
               0, 0, 0, 0}}
};

Tetromino tj =
{
    .id     = 3,
    .name   = "tj",
    .left   = {0, 1, 0, 0},
    .right  = {2, 2, 2, 1},
    .top    = {0, 0, 1, 0},
    .buttom = {1, 2, 2, 2},

    .image = {{1, 0, 0, 0,
               1, 1, 1, 0,
               0, 0, 0, 0,
               0, 0, 0, 0},

              {0, 1, 1, 0,
               0, 1, 0, 0,
               0, 1, 0, 0,
               0, 0, 0, 0},

              {0, 0, 0, 0,
               1, 1, 1, 0,
               0, 0, 1, 0,
               0, 0, 0, 0},

              {0, 1, 0, 0,
               0, 1, 0, 0,
               1, 1, 0, 0,
               0, 0, 0, 0}}
};

Tetromino ti =
{
    .id     = 4,
    .name   = "ti",
    .left   = {0, 2, 0, 1},
    .right  = {3, 2, 3, 1},
    .top    = {1, 0, 2, 0},
    .buttom = {1, 3, 2, 3},

    .image = {{0, 0, 0, 0,
               1, 1, 1, 1,
               0, 0, 0, 0,
               0, 0, 0, 0},

              {0, 0, 1, 0,
               0, 0, 1, 0,
               0, 0, 1, 0,
               0, 0, 1, 0},

              {0, 0, 0, 0,
               0, 0, 0, 0,
               1, 1, 1, 1,
               0, 0, 0, 0},

              {0, 1, 0, 0,
               0, 1, 0, 0,
               0, 1, 0, 0,
               0, 1, 0, 0}}
};

Tetromino to = 
{
    .id     = 5,
    .name   = "to",
    .left   = {1, 1, 1, 1},
    .right  = {2, 2, 2, 2},
    .top    = {0, 0, 0, 0},
    .buttom = {1, 1, 1, 1},

    .image= {{0, 1, 1, 0,
              0, 1, 1, 0,
              0, 0, 0, 0,
              0, 0, 0, 0},

             {0, 1, 1, 0,
              0, 1, 1, 0,
              0, 0, 0, 0,
              0, 0, 0, 0},

             {0, 1, 1, 0,
              0, 1, 1, 0,
              0, 0, 0, 0,
              0, 0, 0, 0},

             {0, 1, 1, 0,
              0, 1, 1, 0,
              0, 0, 0, 0,
              0, 0, 0, 0}}
};

Tetromino tt = 
{
    .id     = 6,
    .name   = "tt",
    .left   = {0, 1, 0, 0},
    .right  = {2, 2, 2, 1},
    .top    = {0, 0, 1, 0},
    .buttom = {1, 2, 2, 2},

    .image = {{0, 1, 0, 0,
               1, 1, 1, 0,
               0, 0, 0, 0,
               0, 0, 0, 0},

              {0, 1, 0, 0,
               0, 1, 1, 0,
               0, 1, 0, 0,
               0, 0, 0, 0},

              {0, 0, 0, 0,
               1, 1, 1, 0,
               0, 1, 0, 0,
               0, 0, 0, 0},

              {0, 1, 0, 0,
               1, 1, 0, 0,
               0, 1, 0, 0,
               0, 0, 0, 0}}
};
