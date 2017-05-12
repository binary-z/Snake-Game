#include<winbgim.h>
#include<windows.h>
#include<time.h>

#define grid 50
#define gridsize 10

int image1[10][10]={{-1,-1,-1,-1, 5, 5,-1,-1,-1,-1},
                    {-1,-1,-1, 5,15, 5, 5,-1,-1,-1},
                    {-1,-1, 5, 5, 5, 5,15, 5,-1,-1},
                    {-1, 5, 5,15, 5, 5, 5, 5, 5,-1},
                    { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
                    {-1,-1,-1,-1, 8, 8,-1,-1,-1,-1},
                    {-1,-1,-1,-1, 8, 8,-1,-1,-1,-1},
                    {-1,-1,-1,-1, 8, 8,-1,-1,-1,-1},
                    {-1,-1,-1,-1, 8, 8,-1,-1,-1,-1},
                    {-1,-1,-1,-1, 8, 8,-1,-1,-1,-1}};

int image2[10][10]={{-1,-1,-1,-1,-1,11,11,-1,-1,-1},
                    {-1,-1,-1,-1,11,-1,-1,11,-1,-1},
                    {-1,-1,-1,11,-1,-1, 5, 5,-1,-1},
                    {-1,-1,-1,11,-1, 5,13,13, 5,-1},
                    {-1,-1, 5, 5, 5,13,13,13,13, 5},
                    {-1, 5,13,13, 5,13,13,13,13, 5},
                    { 5,13,13,13,13, 5,13,13, 5,-1},
                    { 5,13,13,13,13, 5, 5, 5,-1,-1},
                    {-1, 5,13,13, 5,-1,-1,-1,-1,-1},
                    {-1,-1, 5, 5,-1,-1,-1,-1,-1,-1}};

int image3[10][10]={{-1,-1,-1,-1,-1, 4,-1,-1,-1,-1},
                    {-1,-1,-1,-1, 4,-1,-1,-1,-1,-1},
                    {-1,-1,-1,10,10,10,10,-1,-1,-1},
                    {-1,-1,10,10,10,10,15,10,-1,-1},
                    {-1,10,10,10,10,10,15,15,10,-1},
                    {-1,10,10,10,10,10,10,10,10,-1},
                    {-1,10,10,10,10,10,10,10,10,-1},
                    {-1,10,10,10,10,10,10,10,10,-1},
                    {-1,-1,10,10,10,10,10,10,-1,-1},
                    {-1,-1,-1,10,10,10,10,-1,-1,-1}};

int image4[10][10]={{-1,-1,-1,-1,-1, 4,-1,-1,-1,-1},
                    {-1,-1,-1,-1, 4,-1,-1,-1,-1,-1},
                    {-1,-1,-1,14,14,14,14,-1,-1,-1},
                    {-1,-1,14,14,14,14,15,14,-1,-1},
                    {-1,14,14,14,14,14,15,15,14,-1},
                    {-1,14,14,14,14,14,14,14,14,-1},
                    {-1,14,14,14,14,14,14,14,14,-1},
                    {-1,14,14,14,14,14,14,14,14,-1},
                    {-1,-1,14,14,14,14,14,14,-1,-1},
                    {-1,-1,-1,14,14,14,14,-1,-1,-1}};

int image5[10][10]={{-1,-1, 3,-1,-1,-1,-1, 3,-1,-1},
                    {-1,-1,-1, 3,-1,-1, 3,-1,-1,-1},
                    {-1,-1,-1,-1, 3, 3,-1,-1,-1,-1},
                    {-1,-1,-1,-1, 3, 3,-1,-1,-1,-1},
                    {-1, 3,-1, 3, 3, 3, 3,-1, 3,-1},
                    {-1,-1, 3, 3, 3, 3, 3, 3,-1,-1},
                    {-1,-1,-1, 3, 3, 3, 3,-1,-1,-1},
                    {-1,-1, 3, 3, 3, 3, 3, 3,-1,-1},
                    {-1, 3,-1, 3, 3, 3, 3,-1, 3,-1},
                    {-1,-1,-1,-1, 3, 3,-1,-1,-1,-1}};

int image6[10][10]={{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                    {-1,-1,14,14,14,14,14,14,-1,-1},
                    {14,14,14,14,14,14,14,14,14,14},
                    {15,15,14,14,14,14,14,14,15,15},
                    {14,14,15,15,15,15,15,15,14,14},
                    {15,15,14,14,14,14,14,14,15,15},
                    {14,14,15,15,15,15,15,15,14,14},
                    {15,15,14,14,14,14,14,14,15,15},
                    {-1,-1,15,15,15,15,15,15,-1,-1}};

struct misp{
    bool active;
    bool isend;
    int px,py;
    int type;
};

void drawimage(int image[10][10],int x,int y){
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(image[i][j]!=-1) putpixel(x+j,y+i,image[i][j]);
        }
    }
}

class snake{
    private:
      misp map[grid][grid];
      misp eat;
      misp bonus;
      int x,y;
      int dirx,diry;
      int ssize;
    public:
      bool rotate;
      int score;
      char scorestr[30];
      snake();
      void goup();
      void godown();
      void goleft();
      void goright();
      void draw();
      bool tick();
      void geneat();
      void noteplay();
};

snake::snake(){
  for(int i=0; i<grid; i++){
    for(int j=0; j<grid; j++){
        map[i][j].active=false;
    }
  }
  srand(time(NULL));
  x=grid/2;
  y=grid/2;
  dirx=0;
  diry=1;
  rotate=false;
  map[x][y].active=true;
  map[x][y].isend=true;
  ssize=1;
  geneat();
  bonus.active=false;
  score=0;
  itoa(score,snake::scorestr,10);
}

void snake::goup(){
  if(diry==0){
    diry=-1;
    dirx=0;
    rotate=true;
  }
}

void snake::godown(){
  if(diry==0){
    diry=1;
    dirx=0;
    rotate=true;
  }
}

void snake::goleft(){
  if(dirx==0){
    dirx=-1;
    diry=0;
    rotate=true;
  }
}

void snake::goright(){
  if(dirx==0){
    dirx=1;
    diry=0;
    rotate=true;
  }
}

void snake::draw(){
  setfillstyle(9,LIGHTGREEN);
  for(int i=0; i<grid; i++){
    for(int j=0; j<grid; j++){
      if(map[i][j].active) bar(i*gridsize,j*gridsize,(i+1)*gridsize,(j+1)*gridsize);
    }
  }
  switch (eat.type){
    case 1: drawimage(image1,eat.px*gridsize,eat.py*gridsize); break;
    case 2: drawimage(image2,eat.px*gridsize,eat.py*gridsize); break;
    case 3: drawimage(image3,eat.px*gridsize,eat.py*gridsize); break;
    case 4: drawimage(image4,eat.px*gridsize,eat.py*gridsize); break;
    case 5: drawimage(image5,eat.px*gridsize,eat.py*gridsize); break;
  }
  if(bonus.active) drawimage(image6,bonus.px*gridsize,bonus.py*gridsize);
  setcolor(15);
  line(0,grid*gridsize,grid*gridsize,grid*gridsize);
  outtextxy(10,grid*gridsize+(30-textheight(snake::scorestr))/2,snake::scorestr);
}

bool snake::tick(){
  if(!rotate){
    if(dirx==1){
        int tmpx=x;
        x++;
        if(x>=grid){ x=0; }
        if(map[x][y].active==true){ return false; }
        map[x][y].active=true;
        map[x][y].px=tmpx;
        map[x][y].py=y;
        int m=x;
        int k=y;
        for(int i=0; i<ssize; i++){
            map[m][k].isend=false;
            int tmpm=map[m][k].px;
            int tmpk=map[m][k].py;
            m=tmpm;
            k=tmpk;
        }
        map[m][k].active=false;
    }
    if(dirx==-1){
        int tmpx=x;
        x--;
        if(x<0){ x=grid-1; }
        if(map[x][y].active==true){ return false; }
        map[x][y].active=true;
        map[x][y].px=tmpx;
        map[x][y].py=y;

        int m=x;
        int k=y;
        for(int i=0; i<ssize; i++){
            map[m][k].isend=false;
            int tmpm=map[m][k].px;
            int tmpk=map[m][k].py;
            m=tmpm;
            k=tmpk;
        }
        map[m][k].active=false;
    }
    if(diry==1){
        int tmpy=y;
        y++;
        if(y>=grid){ y=0; }
        if(map[x][y].active==true){ return false; }
        map[x][y].active=true;
        map[x][y].px=x;
        map[x][y].py=tmpy;

        int m=x;
        int k=y;
        for(int i=0; i<ssize; i++){
            map[m][k].isend=false;
            int tmpm=map[m][k].px;
            int tmpk=map[m][k].py;
            m=tmpm;
            k=tmpk;
        }
        map[m][k].active=false;
    }
    if(diry==-1){
        int tmpy=y;
        y--;
        if(y<0){ y=grid-1; }
        if(map[x][y].active==true){ return false; }
        map[x][y].active=true;
        map[x][y].px=x;
        map[x][y].py=tmpy;

        int m=x;
        int k=y;
        for(int i=0; i<ssize; i++){
            map[m][k].isend=false;
            int tmpm=map[m][k].px;
            int tmpk=map[m][k].py;
            m=tmpm;
            k=tmpk;
        }
        map[m][k].active=false;
    }
  }
    if((eat.px==x+dirx)&&(eat.py==y+diry)){
      ssize++;
      if(ssize>=ssize*ssize){ return false; }
      map[eat.px][eat.py].active=true;
      map[eat.px][eat.py].isend=false;
      map[eat.px][eat.py].px=x;
      map[eat.px][eat.py].py=y;
      x=eat.px;
      y=eat.py;
      score+=eat.type;
      itoa(score,snake::scorestr,10);
      noteplay();
      geneat();
    }
    if((bonus.active)&&(bonus.px==x+dirx)&&(bonus.py==y+diry)){
      score+=150;
      itoa(score,snake::scorestr,10);
      noteplay();
      bonus.active=false;
    }
    if(bonus.active){
      bonus.type--;
      if(bonus.type<0) bonus.active=false;
    }
    return true;
}

void snake::geneat(){
    eat.px=1+rand()%(grid-2);
    eat.py=1+rand()%(grid-2);
    eat.type=1+rand()%5;
    bool afl=map[eat.px][eat.py].active;
    while(afl){
       eat.px++;
       if(eat.px>grid-1){
           eat.py++;
           eat.px=1;
       }
       afl=map[eat.px][eat.py].active;
    }
    if((!bonus.active)&&(rand()%15==0)){
        bonus.px=1+rand()%(grid-2);
        bonus.py=1+rand()%(grid-2);
        bool afl=(map[bonus.px][bonus.py].active)&&(!(eat.px==bonus.px)&&(eat.py==bonus.py));
        while(afl){
            bonus.px++;
            if(bonus.px>grid-1){
                bonus.py++;
                bonus.px=1;
            }
            afl=(map[bonus.px][bonus.py].active)&&(!(eat.px==bonus.px)&&(eat.py==bonus.py));
        }
        bonus.type=20+rand()%70;
        bonus.active=true;
    }
}

void snake::noteplay(){
    Beep(1000,30);
    Beep(1500,30);
    Beep(2000,30);
}

int main(){
    initwindow(grid*gridsize,grid*gridsize+30);
    snake m;
    bool flag=true;
    while((GetAsyncKeyState(27)==0)&&flag){
        if(GetAsyncKeyState(VK_LEFT)!=0){
            m.goleft();
        }
        if(GetAsyncKeyState(VK_RIGHT)!=0){
            m.goright();
        }
        if(GetAsyncKeyState(VK_UP)!=0){
            m.goup();
        }
        if(GetAsyncKeyState(VK_DOWN)!=0){
            m.godown();
        }
        flag=m.tick();
        if(!m.rotate){
          cleardevice();
          m.draw();
          delay(100);
          swapbuffers();
        } else {
          m.rotate=false;
        }
    }
    closegraph();
    char str[100]="Game over. You score: ";
    strcat(str, m.scorestr);
    MessageBox(0,str,"Silver Snake",64);
    return 0;
}
