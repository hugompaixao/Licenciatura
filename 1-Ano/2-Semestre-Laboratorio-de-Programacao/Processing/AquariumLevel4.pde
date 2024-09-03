// COLOR
final color white = color(255, 255, 255);
final color red = color(255, 0, 0);
final color purple = color(211, 59, 216);
final color black = color(0, 0, 0);
final color aqua = color(0, 255, 255);
final color green = color(0, 128, 0);
final color silver = color(100, 100, 100);

// DIMENSIONS
final int horizontalSide = 1300;
final int verticalSide = 700;
final int nBubbles = 40;
final int nSardines = 16;
final float xc = random(horizontalSide * 0.05, horizontalSide * 0.95);
final float yc = random(verticalSide * 0.1, verticalSide * 0.9);
final float sardineDirection = random(-4, 4);


/********************************************************************************/
class Fish {

  	float x, y, xFishSize, yFishSize, v; 
  	color c;
  
  	Fish(float x, float y, float xFishSize, float yFishSize, float v, color c) {
    	this.x = x;
    	this.y = y;
    	this.xFishSize = xFishSize;
    	this.yFishSize = yFishSize;
    	this.v = v;
    	this.c = c;    
  	}
  
  	void draw() {
    	noStroke();
    	fill(c);
    	rect(x, y, xFishSize, yFishSize);
    
    	if(v < 0) {
      		stroke(black);
      		strokeWeight(2);
      		line(x, y + (yFishSize * 0.75), x + (xFishSize * 0.15), y+ (yFishSize * 0.75));
      		fill(black);
      		circle(x + (xFishSize * 0.10), y + (yFishSize * 0.20), (yFishSize/10));
      		noStroke();
      		fill(c);
      		triangle(x + (xFishSize), y + (yFishSize*0.50), x + (xFishSize * 1.13), y, x + (xFishSize * 1.13), y + (yFishSize));

    	} else{
      		stroke(black);
    		strokeWeight(2);
    		line(x+ xFishSize, y + (yFishSize * 0.75), x + (xFishSize * 0.85), y+ (yFishSize * 0.75));
      		noStroke();
      		fill(black);
      		circle((x+(xFishSize * 0.85)), y + (yFishSize * 0.20), yFishSize/10);
      		fill(c);
      		triangle(x, y + (yFishSize * 0.50), x - (xFishSize * 0.30), y, x - (xFishSize * 0.30), y + (yFishSize));
    	}
  	}

}


class Bubble {
  
  	float x, y, diameter, speed;
  	int nBubbles;

  	Bubble(float var) {
    	x = random(horizontalSide);
    	y = verticalSide;
    	diameter = var%50;
    	speed = (50 - diameter)/6; 
  	}
  
  	void changeHeight() {
   		y = y - speed;
     	if(y < -diameter/2)
       		y = (verticalSide + diameter/2);
  	}
  
  	void draw() {
    	stroke(white);
    	noFill();
    	circle(x, y, diameter);
  	}

}


class Sardine extends Fish {
  
  	Sardine(float x, float y, float xFishSize, float yFishSize, float v, color c) {
    super(x, y, xFishSize, yFishSize, v, c);
  	}

}


Fish f1 = new Fish(horizontalSide * 0.20, verticalSide * 0.20, horizontalSide * 0.15, verticalSide * 0.05, -2, red);
Fish f2 = new Fish(horizontalSide * 0.30, verticalSide * 0.40, horizontalSide * 0.05, verticalSide * 0.15, 0.5, purple);
Fish f3 = new Fish(horizontalSide * 0.60, verticalSide * 0.60, horizontalSide * 0.05, verticalSide * 0.05, 3.5, green);
Fish f4 = new Fish(horizontalSide * 0.20, verticalSide * 0.80, horizontalSide * 0.15, verticalSide * 0.15, -4, red);


Fish fishes[] = {f1, f2, f3, f4};

Bubble bubbles[] = new Bubble[nBubbles];

Sardine sardines[] = new Sardine[nSardines];


void fishDraw(Fish a[]) {
  	for(int i = 0; i < a.length; i++)
    	a[i].draw();
}

void bubllesDraw(Bubble a[]) {
  	for(int i = 0; i < a.length; i++){
    	a[i].changeHeight();
    	a[i].draw();
	}
}

void changePosition(Fish a[]) {
  	for(int i = 0; i < a.length; i++){
    	a[i].x += a[i].v;

    	if(a[i].x < (-a[i].xFishSize))
    	  	a[i].x = horizontalSide;

    	if(a[i].x > horizontalSide)
      		a[i].x = (-a[i].xFishSize);
	}
}

void bubbleCreate(Bubble a[], int n) {
  	for(int i = 0; i < n; i++)
    	a[i] = new Bubble((1+i)*4);
}

void sardineCreate(Sardine a[], int n) {
  	float x;
  	float y;
  	float r = horizontalSide * 0.05;
  	for(int i = 0; i < n; i++) {
    	x = random(xc-r, xc+r);
    	y = random(yc-r, yc+r);
    	if(sqrt(pow(x - xc, 2) + pow(y- yc, 2)) <= r)  
      		a[i] = new Sardine(x, y, horizontalSide * 0.01, verticalSide * 0.005 , sardineDirection, silver);
    	else
      		i--;
	}
}

void update() {
  	changePosition(fishes);
  	changePosition(sardines);
}

void settings() {
	size(horizontalSide, verticalSide);
}

void setup() {
  	bubbleCreate(bubbles, nBubbles);
  	sardineCreate(sardines, nSardines);
}

void draw() {
  	update();
  	background(aqua);
  	fishDraw(fishes);
  	bubllesDraw(bubbles);
  	fishDraw(sardines);
}