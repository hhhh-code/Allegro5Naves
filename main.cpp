#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <string>
#include <list>
#include <math.h>
bool run = true;
ALLEGRO_EVENT_QUEUE *event_queue;
#include "Alarm.h"
#include "Background.h"
#include "Bala.h"
#include "Nave.h"
#include "Enemigo.h"
Alarm *Timer = new Alarm();

void crear();
void Enemigo_action();

int main()
{
    ALLEGRO_DISPLAY *display = NULL;

    // Initialize allegro
    if (!al_init())
    {
        // fprintf(stderr, "Failed to initialize allegro.\n");
        return 1;
    }

    al_init_image_addon();
    // Create the display
    // Create the display
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(640, 640);
    if (!display)
    {
        fprintf(stderr, "Failed to create display.\n");
        return 1;
    }

    if (!al_install_keyboard())
    {
    }
    // Create the event queue
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));

    // Display a black screen
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    Background *background = new Background("fondo.bmp");
    Nave *nave = new Nave();

    background->action(); // mostrar el fondo
    srand(time(NULL));    // hace que los numeros sean aleatorios+

    while (run)
    {
        background->action(); // mostrar el fondo
        crear();
        nave->mov();
        Enemigo_action(); // mover la nave si su vida es mayor a 0
                          // eliminar balas
        for (std::list<Bala *>::iterator it = toDelete.begin(); it != toDelete.end(); it++)
        {
            balas.remove(*it);
        }
        al_flip_display();
    }
    al_destroy_display(display);
}

void crear()
{
    static int cont = 0;          // cuenta los enemigos que se crean
    static int type = rand() % 3; // crea un numero aleatorio entre el 0 y 2

    if (cont < 5)
    {
        if (Timer->alarm(180))
        {
            Enemigos.push_back(new Enemigo(-80, 15, type)); // crear un enemigo random
            cont++;
        }
    }
    else
    {
        if (Timer->alarm(320))
        {
            cont = 0; // reinicia el contador
            type = rand() % 3;
        }
    }
}

void Enemigo_action()
{
    for (std::list<Enemigo *>::iterator it = Enemigos.begin(); it != Enemigos.end(); it++)
    {
        Enemigo *b = *it;
        b->action();
    }

    for (std::list<Enemigo *>::iterator it = EnemigosToDelete.begin(); it != EnemigosToDelete.end(); it++)
    {
        Enemigos.remove(*it);
    }
}
