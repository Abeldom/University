int c=20;
int db;
int x;
int y;
color[] szin;
color[] szinx;

boolean letsgo=false;

void setup() {
  size(800, 800);
  background(0);
  frameRate(15);
  db=width/c;
  szin=new color[db*db];
  szinx=new color[db*db];


  for (int i=0; i<db; i++) {
    for (int j=0; j<db; j++) {
      szin[i*j+j]=color(0);
      stroke(23, 134, 144);
      fill(szin[i*db+j]);
      square(i*c, j*c, c);
    }
  }
}

void life(int xpos, int ypos) {
  int poz=xpos*db+ypos;
  int szaml=0;
  for (int i=-1; i<2; i++) {
    for (int j=-1; j<2; j++) {
      if (i==0 && j==0) {
      } else {
        int dx=xpos+i;
        int dy=ypos+j;
        if (dx<0 || dy<0 || dx>db-1 || dy>db-1) {
        } else if (szin[dx*db+dy]==color(255)) {
          szaml++;
        }
      }
    }
  }

  if (szin[poz]==color(255)) {//elo
    if (szaml<2 || szaml>3) {//under or overpopulation
      //println("kutya");
      szinx[poz]=color(0);
      return;
    }
  } else {
    if (szaml==3) {
      //println("kutya");
      szinx[poz]=color(255);
      return;
    }
  }
  szinx[poz]=szin[poz];
}


void draw() {
  if (letsgo==true) {
    background(0);
    for (int i=1; i<db-1; i++) {
      for (int j=1; j<db-1; j++) {
        life(i, j);
      }
    }
    for (int i=0; i<db*db; i++) {
      szin[i]=szinx[i];
    }

    drawing();
  }
}

void drawing(){
  for (int i=0; i<db; i++) {
      for (int j=0; j<db; j++) {
        stroke(23, 134, 144);
        fill(szin[i*db+j]);
        square(i*c, j*c, c);
      }
    }
}

void mouseClicked() {
  x=mouseX/c;
  y=mouseY/c;
  if (szin[x*db+y]==color(255)) {
    szin[x*db+y]=color(0);
  } else {
    szin[x*db+y]=color(255);
  }
  stroke(23, 134, 144);
  fill(szin[x*db+y]);
  square(x*c, y*c, c);
}

void keyPressed() {
  if (key==ENTER) {
    for (int i=0; i<db*db; i++) {
      szin[i]=color(0);
    }
    drawing();
    letsgo=false;
    return;
  } 
  letsgo=!letsgo;
  
}
