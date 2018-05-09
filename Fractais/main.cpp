#include <lib/pen.h>

void _triangulo(Pen &p, int lado){
    if(lado < 40)
        return;
    for(int i = 0; i < 3; i++){
        p.setColor(rand() % 255, rand() % 255, rand() % 255);
        p.walk(lado);
        p.left(120);
        _triangulo(p, lado/2);
    }
}

void _arvorefruto(Pen& p, int tamanho){
    p.setColor(255,0,0);
    p.circle(tamanho);
    p.setColor(51,204,51);
}

void _arvore(Pen& p, int lado){
    float ang = 35;
    float dec = 0.75;

    lado -= (p.rand() % 7 - 3);
    if(lado < 10)
        return;
    if(lado < 20)
        _arvorefruto(p,1);
    p.walk(lado);
    p.right(ang);
    _arvore(p, lado * dec);
    p.left(ang);
    _arvore(p, lado * dec);
    p.left(ang);
    _arvore(p, lado * dec);
    p.right(ang);
    p.walk(-lado);
}

void _circulos(Pen& p, int lado){
    if(lado < 1)
        return;
    p.circle(lado);
    for(int i = 0; i < 6; i++){
        p.setColor(rand() % 255, rand() % 255, rand() % 255);
        p.left(60);
        p.up();
        p.walk(lado);
        p.down();
        _circulos(p, lado * 0.33);
        p.up();
        p.walk(-lado);
        p.down();
    }
}


void _rotacao(Pen& p, int lado){
    if(lado < 20)
        return;

    p.setColor(rand() % 255, rand() % 255, rand() % 255);
    p.walk(lado);
    p.right(90);
    _rotacao(p, lado - 10);
}

void _gelo(Pen& p, int lado){
    if(lado < 1)
        return;
    for(int i=0;i<5;i++){
        p.walk(lado);
        p.right(72);
        if(lado < 10)
            p.circle(lado);
        p.walk(-lado);
        _gelo(p, lado * 0.3);
    }
}

void _trigo(Pen& p, int lado){
    if(lado < 1)
        return;
    for(int i=0; i<4; i++){
        p.walk(lado);
        p.right(20);
        _trigo(p, lado * 0.35);
        p.left(40);
        _trigo(p, lado * 0.35);
        p.right(20);
    }
    p.walk(-(lado * 4));
}


void arvore(Pen& p, int lado){
    p.setThickness(3);
    p.setXY(400, 590);
    p.setHeading(90);
    _arvore(p, lado);
}

void triangulo(Pen& p, int lado){
    p.setXY(200, 400);
    p.setHeading(0);
    _triangulo(p, lado);
}


void circulos(Pen& p, int lado){
    //configuração do fractal
    p.setXY(400, 300);
    p.setHeading(0);
    _circulos(p, lado);

}

void rotacao(Pen& p, int lado){
    //configuração do fractal
    p.setXY(400, 100);
    p.setHeading(0);
    _rotacao(p, lado);

}


void gelo(Pen& p, int lado){
    //configuração do fractal
    p.setXY(200, 300);
    p.setHeading(20);
    p.setColor(255, 255, 255);
    _gelo(p, lado);

}

void trigo(Pen& p, int lado){
    //configuração do fractal
    p.setXY(400, 590);
    p.setHeading(90);
    p.setColor(255, 255, 0);
    _trigo(p, lado);

}

void fractal(){

    // configuração inicial
    Pen p(800, 600);
    p.setThickness(1);
    p.setColor(rand() % 255, rand() % 255, rand() % 255);
    p.setSpeed(0);
    //fim configuração inicial

    // Fractais
    //trigo(p, 100);
    //gelo(p,250);
    rotacao(p, 600);
    //circulos(p, 200);
    //arvore(p, 100);
    //triangulo(p, 400);
    p.wait();
}

int main(){
    fractal();
    return 0;
}
