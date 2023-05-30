class Bala
{
private:
    /* data */
public:
    // variables
    int x;
    int y;
    int type;
    ALLEGRO_BITMAP *sprite;
    // funciones
    void mov();
    Bala(int x, int y,int type);
    ~Bala();
};
std::list<Bala*> balas;
std::list<Bala *> toDelete;

void Bala::mov()
{
    al_draw_bitmap(sprite,x,y,0);

    	//Movimiento
	switch(this->type){
		case 0:
			if(y > 0)			y-=5;
			else				toDelete.push_back(this);
		break;
		case 1:
			if(y < 640)			y+=5;
			else				toDelete.push_back(this);
		break;
	}
}

Bala::Bala(int x, int y,int type)
{
    this->x = x;
	this->y = y;
	this->sprite = type == 0? al_load_bitmap("bala.png") : al_load_bitmap("bala_enemiga.png");
	this->type = type;
}

Bala::~Bala()
{
    al_destroy_bitmap(this->sprite);
	balas.remove(this);
}


static bool alarm(int secons){
	static int cont = 0;
	
	if(secons == 0){
		return false;
	}
	
	if(cont >= secons){
		cont = 0;
		return true;
	}
	
	cont++;
	
	return false;
}