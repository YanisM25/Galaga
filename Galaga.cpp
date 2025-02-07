
#include "mbed.h"
#include "C12832.h"

C12832 lcd(p5, p7, p6, p8, p11);

DigitalIn up(p15);
DigitalIn down(p12);
DigitalIn left(p13);
DigitalIn right(p16);
DigitalIn center(p14);

PwmOut speaker(p26);

int x0 = 4;
int y0 = lcd.height() / 2 + 1;
int x1 = 13;
int y1 = lcd.height() / 2 - 1;
int score = 0;
int xs0=x1;
int xs1=x1+1;
int ys1=0;
int ys2=lcd.height();

struct Balle {
    int xb;
    int yb;
    bool active;
};

struct Mechant {
    int xc;
    int yc;
    bool active;
};

const int limite_balles = 100;
const int limite_mechants = 100;
const int max_mechants_actifs = 5;

Balle balles[limite_balles] = {};
Mechant mechants[limite_mechants] = {};

Timer inter_tir;
Timer inter_cible;
Timer inter_cheat;
Timer inter_score;

void PlayNote(float frequency, float temps) {
    speaker.period(1.0 / frequency);
    speaker = 0.5;  
    wait(temps);
    speaker = 0.0; 
}

void mvt() { 
    if (up == 1 and y0>0) {
        y0 = y0- 2;
        y1 =y1 - 2;
    } else if (down == 1) {
        y0 = y0+2;
        y1 =y1+2;
    }
  
    if (y0 == 1  and up==1 ){
     y0 = y0+2;
     y1 = y1+2;}
     
    if (y1 == lcd.height()-1 and down ==1 ){
     y0 = y0-2;
     y1 = y1-2;}

   
}

void ajouterBalle() {
    for (int i = 0; i < limite_balles; i++) {
        if (balles[i].active==false) {
            balles[i].xb = x1 + 1;
            balles[i].yb = (y0 + y1) / 2;
            balles[i].active = true;
            PlayNote(1000.0, 0.1);
            break;
        }
    }
}

void ajouterMechant() {
    for (int i = 0; i < limite_mechants; i++) {
        if (!mechants[i].active) {
            mechants[i].xc = lcd.width() - 1;
            mechants[i].yc = rand() % (lcd.height() - 2);
            mechants[i].active = true;
            break;
        }
    }
}

void modif_Balles() {
    for (int i = 0; i < limite_balles; i++) {
        if (balles[i].active) {
            balles[i].xb += 1;
            if (balles[i].xb >= lcd.width()) {
                balles[i].active = false;
            }
        }
    }
}



void afficheBalles() {
    for (int i = 0; i < limite_balles; i++) {
        if (balles[i].active==true) {
            lcd.fillcircle(balles[i].xb, balles[i].yb, 1, 1);
        }
    }
}

void afficheMechants() {
    for (int i = 0; i < limite_mechants; i++) {
        if (mechants[i].active) {
            lcd.fillrect(mechants[i].xc, mechants[i].yc, mechants[i].xc - 2, mechants[i].yc + 2, 1);
        }
    }
}

void Score()///
 {
    lcd.locate(82, 0);
    lcd.printf("Score: %d", score);
    for (int i = 0; i < limite_balles; i++) {
        if (balles[i].active==1) {
            for (int j = 0; j < limite_mechants; j++) {
                if (mechants[j].active==true) {
                    if (balles[i].xb >= mechants[j].xc - 2 and balles[i].yb >= mechants[j].yc and balles[i].yb <= mechants[j].yc + 2) 
                    {
                        balles[i].active = false;
                        mechants[j].active = false;
                        score += 10;
                        PlayNote(1500.0, 0.1);
                        break;
                    }
                }
            }
        }
    }
}

int compterMechantsActifs() {
    int n = 0;
    for (int i = 0; i < limite_mechants; i++) {
        if (mechants[i].active) {
            n++;
        }
    }
    return n;
}

void perdu(){
    for (int i = 0; i < limite_mechants; i++) {
        if (mechants[i].active) {
            if(x1 >= mechants[i].xc){
                if(y0 >= mechants[i].yc or y1>= mechants[i].yc){
                    lcd.cls();
                    lcd.locate((lcd.width()/2)-20, (lcd.height()/2)-15);
                    lcd.printf("Game Over !");
                    lcd.locate(0, (lcd.height()/2)+4);
                    lcd.printf("reset pour rejouer");
                    PlayNote(1500.0,0.5);
                    wait(3);
                }
            }
        }
    }
}


void Cheat() {
    static int step = 0;
    static float start_time = 0;

    if (step == 0 and left == 1) {
        step = 1;
        start_time = inter_score.read();
    } 
    else if (step == 1 and left == 1) {
        step = 2;
    } 
    else if (step == 2 and left == 1) {
        step = 3;
    } 
    else if (step == 3 and up == 1) {
        step = 4;
    } 
    else if (step == 3 and down == 1) {
        step = 4;
    } 
    else if (step == 4 and right == 1) {
        if (inter_score.read() - start_time < 7) {
           lcd.cls();
        lcd.locate((lcd.width()/2)-20, (lcd.height()/2));
        lcd.printf("Ultimate attack !!!");
        PlayNote(500.0,0.5);
        wait(2);
        while(xs1<=lcd.width()){
            xs1=xs1+1;
            lcd.fillrect(x0, y0, x1, y1, 1);
            lcd.fillrect(xs1,ys2,xs0,ys1,1);
        }
        lcd.cls();
        lcd.locate((lcd.width()/2)-20, (lcd.height()/2));
        lcd.printf("Vous avez gagnez");
        PlayNote(2000.0,0.5);
        wait(3);
            
        }
        step = 0;
    } 
    else if (step > 0 and (right != 1 and up != 1 and left != 1 and down != 1)) {
        if (inter_score.read() - start_time > 7) {
            step = 0;
        }
    }
}
void Cheat_score() {
    static int step = 0;
    static float start_time = 0;

    if (step == 0 and right == 1) {
        step = 1;
        start_time = inter_score.read();
    } 
    else if (step == 1 and right == 1) {
        step = 2;
    } 
    else if (step == 2 and up == 1) {
        step = 3;
    } 
    else if (step == 3 and left == 1) {
        step = 4;
    } 
    else if (step == 4 and down == 1) {
        if (inter_score.read() - start_time < 7) {
            score += 30;
            lcd.locate(0, 0);
            lcd.printf("Cheat Activated! +30");
        }
        step = 0;
    } 
    else if (step > 0 and (right != 1 and up != 1 and left != 1 and down != 1)) {
        if (inter_score.read() - start_time > 7) {
            step = 0;
        }
    }
}




int afficherCommandes()///
 {
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("droit -> tirer");
    lcd.locate(0,lcd.height()/5);
    lcd.printf("haut -> monter");
    lcd.locate(0, 2*lcd.height()/5);
    lcd.printf("bas -> descendre");
    lcd.locate(0, 3*lcd.height()/5);
    lcd.printf("gauche -> attack speciale");
    lcd.locate(0, 4*lcd.height()/5);
    lcd.printf("retour->reset");
    wait(5);
    
     

}
int afficherMenu() ///
{
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("GALAGA");
    lcd.locate(0, lcd.height()/3);
    lcd.printf("droit->commencer");
    if (right==1){
        return 0;
    }
    lcd.locate(0, 2*lcd.height()/3);
    lcd.printf("gauche->commandes");
    if(left==1){
        afficherCommandes();
    }
}



void modif_Mechants() {
    for (int i = 0; i < limite_mechants; i++) {
        if (mechants[i].active==true) {
            mechants[i].xc -= 1;
            if (mechants[i].xc <= 0) {
                mechants[i].active = false;
                lcd.cls();
                lcd.locate((lcd.width()/2)-20, (lcd.height()/2)-15);
                lcd.printf("Game Over !");
                lcd.locate(0, (lcd.height()/2)+4);
                lcd.printf("reset pour rejouer");
                wait(999);
                PlayNote(1500.0,0.5);
 
            }
        }
    }
}
void Menu()
 {
    while (1) {
        afficherMenu();
        if (right == 1) {
            break;
        }
        if (left == 1) {
            afficherCommandes();
             if(right==1){
                wait(0.2);
                break;
             }
        
        }
    }
}

int main() {
    lcd.cls();

    

    inter_tir.start();
    inter_cible.start();
    Menu();
    while (1) {
        lcd.cls();
        
        mvt();
        lcd.fillrect(x0, y0, x1, y1, 1);
        
        if (right == 1 and inter_tir.read() >= 0.3) {
            ajouterBalle();
            inter_tir.reset();
        }
        if (inter_cible.read() >= 2) {
            if (compterMechantsActifs() < max_mechants_actifs) {
                ajouterMechant();
            }
            inter_cible.reset();
        }
        
        modif_Balles();
        modif_Mechants();
        afficheBalles();
        afficheMechants();
        Score();
        perdu();
        Cheat_score();
       

        if (score>=20) {
            Cheat();
        }

        wait(0.05);
    }
}