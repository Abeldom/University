float xstart = -2.5;
float xend = 2.5;
float ystart = -2;
float yend = 2;
float maxbrightness=100;
float angle=0;
float firstx=0;
float firsty=0;

///lementi hogy kattintas pillanataban hol van az eger a komplex sikban,valos resz
float konsta=xstart;// valos resz
float konstb=ystart;// imaginarius resz

//lementi kattintas pillanataban az eger szeltol valo tavolsagat a komplex ter szerint
float hosszx=0;// x tengely
float hosszy=0;// y tengely

boolean drawornot=true;
boolean drawornot2=true;

void setup() {
  size(960, 780);     
}

void mouseWheel(MouseEvent event) {
  if(drawornot){
    konsta=konsta+ map(mouseX, 0, width, 0, xend-xstart) - hosszx;
    konstb= konstb+ map(mouseY, 0, height, 0, yend-ystart) - hosszy;
  }
  float x=mouseX;
  float y=mouseY;
  float kx = x/ width;
  float ky = y/ height;
  float dx = (xend - xstart)/10;
  float dy = (yend - ystart)/10;
  float e = event.getCount();
  dx=dx/5;
  dy=dy/5;
  if (e < 0) {
    xstart = xstart + dx  * kx;
    xend = xend - dx * (1 - kx);
    ystart = ystart + dy * ky;
    yend = yend - dy * (1 - ky); 
  } else {
    xstart = xstart - dx * (1-kx);
    xend = xend + dx * kx;
    ystart = ystart - dy * (1-ky);
    yend = yend + dy * ky; 
  }
  if(drawornot){
    hosszx=map(mouseX, 0, width, 0, xend-xstart);
    hosszy=map(mouseY, 0, height, 0, yend-ystart);
  }
}

void mousePressed(){
  if(drawornot==true){
    konsta=konsta+ map(mouseX, 0, width, 0, xend-xstart) - hosszx;
    konstb= konstb+ map(mouseY, 0, height, 0, yend-ystart) - hosszy;
  }
  if(drawornot==false){
    hosszx=map(mouseX, 0, width, 0, xend-xstart);
    hosszy=map(mouseY, 0, height, 0, yend-ystart);
  }
   drawornot=!drawornot; 
}

void keyPressed() {
  float dx = xend - xstart;
  float dy = yend - ystart;
  
  if(keyCode==LEFT){
    xstart=xstart-dx/40;
    xend=xend-dx/40;
  }else if(keyCode==RIGHT){
    xstart=xstart+dx/40;
    xend=xend+dx/40;
  }else if(keyCode==UP){
    ystart=ystart-dy/40;
    yend=yend-dy/40;
  }else if(keyCode==DOWN){
    ystart=ystart+dy/40;
    yend=yend+dy/40;
  }
}

void draw(){
  loadPixels();
  //angle=angle+0.2;
  
  if(drawornot){
    firstx =konsta+ map(mouseX, 0, width, 0, xend-xstart)-hosszx;
    firsty =konstb+ map(mouseY, 0, height, 0, yend-ystart)-hosszy;
  }
  
  //float firstx=sin(angle);
  //float firsty=cos(angle);
     
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      float a = map(i, 0, width, xstart, xend);
      float b = map(j, 0, height, ystart, yend);
      int n = 0;
      while (n < maxbrightness) { 
        float newa = a * a  - b * b ;
        float newb = 2*a * b;
        //float newa = a*a*a* - 7*a*a*b*a*b*b ;
        //float newb = 3*a*a*b - b*b*b;
        a = newa + firstx;
        b = newb + firsty;       
        if (a*a+b*b > 4) {
          break;
        }
        n++;
      }
      int pix =i + j * width;
      //egyszin(pix,n);
      szivarvany(pix,n);
    }
   }
  updatePixels();
}

void egyszin(int pix,int n){
  if (n == maxbrightness) {
      color szin = color(200, 125, 150,255);
        //color szin = color(255, 255,0,255);
        pixels[pix] = szin;
      }else{  
        float bright = map(n,0,maxbrightness,0,1);
        bright=map(sqrt(bright),0,1,0,255);
        color szin = color(bright, bright/2, bright/2,155);
        //color szin = color(0, bright/3, bright/2,155);
        pixels[pix] = szin;
      }
}

void szivarvany(int pix,int n){  
  if (n == maxbrightness) {
    color szin= color(0,0,0,255);
          pixels[pix]=szin;
  }else{ 
    float range=maxbrightness/7;
    float x=(n%range)/10;
    if(n%range==0){
      x=1;
    }
    if(n==0){
      pixels[pix]=color(0,0,0,255);
    }else if(n<range){//piros
      pixels[pix]=color(x*255,0,0,255);
    }else if(n<2*range){//narancssarga
      pixels[pix]=color(255,x*128,0,255);
    }else if(n<3*range){//sarga
      pixels[pix]=color(255,128+x*128,0,255);
    }else if(n<4*range){//zold
      pixels[pix]=color(255-x*255,255,0,255);
    }else if(n<5*range){//kek
      pixels[pix]=color(0,255,x*255,255);
    }else if(n<6*range){//indigo
      pixels[pix]=color(x*75,0,x*130,255);
    }else if(n<7*range){//ibolya
      pixels[pix]=color(75+x*73,0,x*81+130,255);
    }
  }
}

void fekete(pix,n){
  if(n==maxbrightness){
     pixels[pix + 0] = 0;
        pixels[pix + 1] = 0;
        pixels[pix + 2] = 0;
        pixels[pix + 3] = 255;
  }else{
    var bright = map(n, 0, maxbrightness, 0, 1);
    bright=map(sqrt(bright),0,1,0,255);
    pixels[pix + 1] = bright*2;
    pixels[pix + 2] = bright/2;
    pixels[pix + 0] = bright/2;
    pixels[pix + 3] = 155;
  }
}
