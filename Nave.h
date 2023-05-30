class Nave
{
private:
    /* data */
public:
    // varibles
    int x;
    int y;
    ALLEGRO_BITMAP *sprite;
    float vel;
    int vida;
    // Funciones
    void mov();
    Nave(/* args */);
    ~Nave();
};

void Nave::mov()
{
    try
    {
        /* code */

        al_draw_bitmap(sprite, x, y, 0);

        const int spriteH = al_get_bitmap_height(sprite);
        const int spriteW = al_get_bitmap_width(sprite);

        ALLEGRO_KEYBOARD_STATE kbdstate;
        al_get_keyboard_state(&kbdstate);

        if (al_key_down(&kbdstate, ALLEGRO_KEY_D) and x + spriteW < 640)
        {
            x += vel;
        }
        if (al_key_down(&kbdstate, ALLEGRO_KEY_A) and x > 0)
        {
            x -= vel;
        }
        if (al_key_down(&kbdstate, ALLEGRO_KEY_W) and y > 0)
        {
            y -= vel;
        }
        if (al_key_down(&kbdstate, ALLEGRO_KEY_S) and y + spriteH < 640)
        {
            y += vel;
        }
        if(al_key_down(&kbdstate, ALLEGRO_KEY_ESCAPE)){
            run = false;
        }

        // acciones de la bala
        for (std::list<Bala *>::iterator it = balas.begin(); it != balas.end(); it++)
        {
            Bala *b = *it;
            b->mov();
        }

        // disparos
        if (al_key_down(&kbdstate, ALLEGRO_KEY_SPACE) and alarm(5))
            balas.push_back(new Bala(x + (spriteW / 2) - 3, y, 0)); // agrega una bala a la lista

        // colisiones
        for (std::list<Bala *>::iterator it = balas.begin(); it != balas.end(); it++)
        {
            Bala *bala = *it;
            const bool colisionHorizontal = (bala->x >= this->x) and (bala->x <= x + spriteW);
            const bool colisionVertical = (bala->y >= this->y) and (bala->y <= y + spriteH);

            if (colisionHorizontal && colisionVertical && bala->type == 1)
            {
                toDelete.push_back(bala);
                this->vida -= 3;
            }
        }

        
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

Nave::Nave(/* args */)
{
    x = 200;
    y = 400;
    sprite = al_load_bitmap("nave.png");
    vel = 6;
    vida = 100;
}

Nave::~Nave()
{
}
