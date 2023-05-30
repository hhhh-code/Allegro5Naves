class Enemigo
{
private:
    /* data */
public:
    // variables
    float x;
    float y;
    ALLEGRO_BITMAP *sprite;
    ALLEGRO_BITMAP *b_vida;
    int type;
    int cont;
    int vida;
    // funciones
    Enemigo(int x, int y, int type);
    ~Enemigo();
    void action();
    void Movimiento();
    Alarm *alarm;
};
std::list<Enemigo *> Enemigos;
std::list<Enemigo *> EnemigosToDelete;

Enemigo::Enemigo(int x, int y, int type)
{
    this->x = x;
    this->y = y;
    this->sprite = al_load_bitmap("Enemigo.png");
    this->b_vida = al_load_bitmap("b_vida.png");
    this->alarm = new Alarm[15]();
    this->type = type;
    this->cont = 1;
    this->vida = 100;
}

Enemigo::~Enemigo()
{
}

void Enemigo::action()
{
    al_draw_bitmap(sprite, x, y, 0);

    const int spriteH = al_get_bitmap_height(sprite);
    const int spriteW = al_get_bitmap_width(sprite);
    float barraVida = ((spriteW * 70) / 100.0) * vida;

    // Dibujar el sprite escalado en una posición específica
    al_draw_scaled_bitmap(b_vida,                                // Bitmap a dibujar
                          0, 0,                                  // Origen (coordenadas x e y) del rectángulo del sprite
                          spriteW, al_get_bitmap_height(sprite), // Ancho y alto del rectángulo del sprite
                          x, y,                                  // Posición en la pantalla donde se dibujará el sprite
                          barraVida, 250,                        // Ancho y alto del sprite escalado
                          0);                                    // Bandera de dibujo (generalmente se usa 0)

    // crear disparos enemigos
    if (this->alarm[1].alarm(190))
    {
        balas.push_back(new Bala(x + (spriteW / 2) - 3, y, 1)); // agrega una bala enemiga a la lista
    }

    // colisiones
    for (std::list<Bala *>::iterator it = balas.begin(); it != balas.end(); it++)
    {
        Bala *bala = *it;
        const bool colisionHorizontal = (bala->x >= this->x) and (bala->x <= x + spriteW);
        const bool colisionVertical = (bala->y >= this->y) and (bala->y <= y + spriteH);

        if (colisionHorizontal && colisionVertical && bala->type == 0)
        {
            toDelete.push_back(bala);
            this->vida -= 3;
        }
    }

    this->Movimiento();
    if (this->vida <= 0 or this->x > 640)
    {
        EnemigosToDelete.push_back(this);
        // delete this; // Eliminar nave enemiga si ya no tiene vida o esta fuera del lienzo
    }
}

void Enemigo::Movimiento()
{
    switch (this->type)
    {
    case 0:
        if (this->alarm[0].alarm(3))
        {
            x += 5;
            y += 2;
        }
        break;
    case 1:
        if (this->alarm[0].alarm(1))
        {
            x += 1.3;
            y += cos(x / 100);
        }
        break;

    case 2:
        if (this->alarm[0].alarm(2))
        {
            x += 1.5;

            if (this->y >= 640 - (640 / 3))
            {
                cont = -1;
            }

            if (cont == -1)
            {
                y += pow((x - (this->x - 640 / 4)) / 100, 2) * cont;
            }
            else
            {
                y += pow(x / 100, 2);
            }
        }
        break;
    }
}
