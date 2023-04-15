/*
** EPITECH PROJECT, 2023
** Paint
** File description:
** Graphical C Paint
*/

#include "my.h"

typedef struct player {
    sfRectangleShape *rect;
    sfVector2f pos;
    int size;
    int score;
} player;

typedef struct ball {
    sfCircleShape *ball;
    sfVector2f pos;
    sfVector2f trajec;
    int sens;
} ball;

void writext (sfRenderWindow *window, char *text, sfVector2f pos, sfVector2f scale);

void move (player *no1, player *no2)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ) && no1->pos.y > 0) {
        no1->pos.y -= 0.5;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS) && no1->pos.y + 100 < 1000) {
        no1->pos.y += 0.5;
    }
    if (sfKeyboard_isKeyPressed(sfKeyNumpad8) && no2->pos.y > 0) {
        no2->pos.y -= 0.5;
    }
    if (sfKeyboard_isKeyPressed(sfKeyNumpad2) && no2->pos.y + 100 < 1000) {
        no2->pos.y += 0.5;
    }
}

void worKeep(sfEvent event, sfRenderWindow *win)
{
    sfRenderWindow_display(win);
    
    while (sfRenderWindow_pollEvent(win, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(win);
        }
    }
    
    sfRenderWindow_clear(win, sfBlack);
}

void drawbar (sfRenderWindow *Window, player *no1, player *no2)
{
    sfFont *font = sfFont_createFromFile("SuperMario256.ttf");
    sfRectangleShape_setPosition(no1->rect, no1->pos);
    sfRectangleShape_setPosition(no2->rect, no2->pos);
    sfText *sco1 = sfText_create(); char t[2]; t[0] = no1->score + 48; t[1] = '\0';
    sfText_setString(sco1, t);
    sfText_setFont(sco1, font);
    sfText *sco2 = sfText_create(); char t2[2]; t2[0] = no2->score + 48; t2[1] = '\0';
    sfText_setString(sco2, t2);
    sfText_setFont(sco2, font);
    sfText_setPosition(sco1, (sfVector2f){240, 0});
    sfText_setPosition(sco2, (sfVector2f){740, 0});
    sfText_setScale(sco1, (sfVector2f){1.5, 1.5});
    sfText_setScale(sco2, (sfVector2f){1.5, 1.5});
    sfRenderWindow_drawText(Window, sco1, NULL); sfRenderWindow_drawText(Window, sco2, NULL);
    sfRenderWindow_drawRectangleShape(Window, no1->rect, NULL);
    sfRenderWindow_drawRectangleShape(Window, no2->rect, NULL);
    sfText_destroy(sco1); sfText_destroy(sco2); sfFont_destroy(font); 
}

void initbar (player *no, int which)
{
    sfRectangleShape_setSize(no->rect, (sfVector2f){10, no->size});
    if (which == 1) {
        no->pos = (sfVector2f){10, 300};
    } else {
        no->pos = (sfVector2f){980, 300};
    }
    no->score = 0;
    sfRectangleShape_setFillColor(no->rect, sfWhite);
}

sfCircleShape *initball (void)
{
    sfCircleShape *ball = sfCircleShape_create();
    sfCircleShape_setOutlineThickness(ball, 1);
    sfCircleShape_setFillColor(ball, sfWhite);
    sfCircleShape_setRadius(ball, 10);
    return ball;
}

void drawball (sfRenderWindow *window, ball *bal)
{
    sfCircleShape_setPosition(bal->ball, bal->pos);
    sfRenderWindow_drawCircleShape(window, bal->ball, NULL);
}

void direction (ball *bal, player *no)
{
    if (bal->pos.y > no->pos.y + 100) {
        bal->trajec.y = (bal->pos.y - (no->pos.y + no->size / 2)) / 800;
    } else {
        bal->trajec.y = -(((no->pos.y + no->size / 2) - bal->pos.y) / 800);
    }
}

void win (sfRenderWindow *window, int winner, sfEvent event)
{
    sfText *te = sfText_create();
    if (winner == 1)
        sfText_setString(te, "Player 1 Won.\n\nPress Enter to Restart");
    else
        sfText_setString(te, "Player 2 Won.\n\nPress Enter to Restart");
    sfFont *fon = sfFont_createFromFile("SuperMario256.ttf");
    sfText_setFont(te, fon);
    sfText_setPosition(te, (sfVector2f){250, 400});
    sfText_setScale(te, (sfVector2f){1.2, 1.2});
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawText(window, te, NULL);
    while (!sfKeyboard_isKeyPressed(sfKeyEnter)) {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawText(window, te, NULL);
        sfRenderWindow_display(window);
        worKeep(event, window);
    }
    sfText_destroy(te); sfFont_destroy(fon);
}

void trap (sfRenderWindow *window, sfEvent event)
{
    while (!sfKeyboard_isKeyPressed(sfKeyEnter)) {
        writext(window, "Dev never lose hahahaha...\n\nPress Enter to Restart", (sfVector2f){250, 400}, (sfVector2f){1.2, 1.2});
        sfRenderWindow_display(window);
        worKeep(event, window);
    }
}

void moveball (sfRenderWindow *window, ball *bal, player *no1, player *no2, sfEvent event)
{
    bal->pos.x += bal->trajec.x; int g = 0;
    bal->pos.y += bal->trajec.y;
    if (bal->pos.y + 20 >= no1->pos.y && bal->pos.y <= no1->pos.y + no1->size && bal->pos.x <= no1->pos.x) {
        bal->trajec.x *= -1; direction(bal, no1);
    }
    if (bal->pos.y + 20 >= no2->pos.y && bal->pos.y <= no2->pos.y + no2->size && bal->pos.x + 10 >= no2->pos.x) {
        bal->trajec.x *= -1; direction(bal, no2);
    }
    if (bal->pos.x >= 1000) {
        if (bal->trajec.x > 0) 
            bal->trajec.x = 0.1; 
        else
            bal->trajec.x = -0.1; 
        bal->pos.x = 450;
        no1->score++;
        if (no1->score == 10) win(window, 1, event), no1->score = 0,
        no2->score = 0, bal->pos = (sfVector2f){450, 450},
        no1->pos = (sfVector2f){10, 300}, no2->pos = (sfVector2f){980, 300};
    }
    if (bal->pos.x <= 0) {
        if (bal->trajec.x > 0) 
            bal->trajec.x = 0.1; 
        else
            bal->trajec.x = -0.1; 
        bal->pos.x = 450;
        no2->score++;
        if (no2->score == 10) win(window, 2, event), no1->score = 0,
        no2->score = 0, bal->pos = (sfVector2f){450, 450},
        no1->pos = (sfVector2f){10, 300}, no2->pos = (sfVector2f){980, 300};
    }
    if (bal->pos.y <= 0 || bal->pos.y + 20 >= 1000) bal->trajec.y *= -1;
    if (bal->trajec.x >= 0) {
        bal->trajec.x += 0.000005;
    } else  {
        bal->trajec.x -= 0.000005;
    }
    if (sfKeyboard_isKeyPressed(sfKeyG)) {
        no1->score = 0, no2->score = 0, bal->pos = (sfVector2f){450, 450}; 
        no1->pos = (sfVector2f){10, 300}, no2->pos = (sfVector2f){980, 300}; trap(window, event);
    }
}

void line (sfRenderWindow *window)
{
    sfRectangleShape *shape = sfRectangleShape_create();
    sfRectangleShape_setFillColor(shape, sfWhite);
    sfRectangleShape_setSize(shape, (sfVector2f){10, 50});
    for (int y = 0; y < 1000; y++) {
        sfRectangleShape_setPosition(shape, (sfVector2f){475, y});
        y += 100;
        sfRenderWindow_drawRectangleShape(window, shape, NULL);
    }
    sfRectangleShape_destroy(shape);
}

sfMusic *music (char *str)
{
    sfMusic *song = sfMusic_createFromFile(str);
    sfMusic_setLoop(song, sfTrue);
    sfMusic_play(song);
    return song;
}

void writext (sfRenderWindow *window, char *text, sfVector2f pos, sfVector2f scale)
{
    sfFont *font = sfFont_createFromFile("SuperMario256.ttf");
    sfText *sco1 = sfText_create();
    sfText_setString(sco1, text);
    sfText_setFont(sco1, font);
    sfText_setPosition(sco1, pos);
    sfText_setScale(sco1, scale);
    sfRenderWindow_drawText(window, sco1, NULL);
    sfText_destroy(sco1); sfFont_destroy(font); 
}

void paused (sfRenderWindow *window, sfEvent event)
{
    sfRectangleShape *font = sfRectangleShape_create();
    sfRectangleShape_setSize(font, (sfVector2f){1000, 1000});
    sfRectangleShape_setFillColor(font, sfColor_fromRGBA(0, 0, 0, 75));
    if (sfKeyboard_isKeyPressed(sfKeySpace)) {
        //sleep(0.5);
        while (!sfKeyboard_isKeyPressed(sfKeyEscape)) {
            //sfRenderWindow_drawRectangleShape(window, font, NULL);
            writext(window, "Paused", (sfVector2f){400, 400}, (sfVector2f){1.2, 1.2});
            sfRenderWindow_display(window);
            worKeep(event, window);
        }
    }
}

int main (int ac, char **av)
{
    sfRenderWindow *window;
    sfVideoMode mode = {1000, 1000, 32};
    sfEvent event;
    sfVector2f player1 = (sfVector2f){0, };
    player *no1 = malloc(sizeof(*no1));
    player *no2 = malloc(sizeof(*no2));
    no1->size = 100; no2->size = 100;
    no1->rect = sfRectangleShape_create();
    no2->rect = sfRectangleShape_create();
    initbar(no1, 1); initbar(no2, 2);
    ball *bal = malloc(sizeof(*bal)); bal->ball = initball();
    bal->pos = (sfVector2f){450, 450}; bal->sens = 0;
    bal->trajec = (sfVector2f){0.1, 0};
    window = sfRenderWindow_create(mode, "Window", sfDefaultStyle, NULL);
    sfMusic *theme = music("part.ogg");
    while (sfRenderWindow_isOpen(window)) {
        worKeep(event, window);
        drawbar(window, no1, no2);
        move(no1, no2);
        drawball(window, bal);
        moveball(window, bal, no1, no2, event);
        line(window); paused(window, event);
    }
    sfRectangleShape_destroy(no1->rect); free(no1);
    sfRectangleShape_destroy(no2->rect); free(no2);
    sfRenderWindow_destroy(window); sfMusic_destroy(theme);
}
