#ifndef __PAVE_SERPENT_SAIM_H__
#define __PAVE_SERPENT_SAIM_H__

typedef struct {

    int x, y;

} Point;



typedef struct {

    Point *body;

    int length;

    int dir_x, dir_y;

} Snake;

void init_snake(Snake *);
void move_snake(Snake *);

#endif