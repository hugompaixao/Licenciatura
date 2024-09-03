// Window
final int windowX = 1366;
final int windowY = 780;

// Timer
int timer = 0;

// Colours
final color white = color(255, 255, 255);

final color red = color(239, 51, 64);

final color armeniaRed = color(218, 41, 28);
final color armeniaBlue = color(0, 51, 160);
final color armeniaYellow = color(255, 158, 27);

final color maldivesRed = color(200, 16, 46);
final color maldivesGreen = color(0, 132, 61);

class Rectangle {
  float x, y, l, h;
  color c;

  Rectangle(float x, float y, float l, float h, color c) {
    this.x = x;
    this.y = y; 
    this.l = l;
    this.h = h;
    this.c = c;
  }

  void draw() {
    noStroke();
    fill(c);
    rect(x, y, l, h);
  }

}

class Circle {
  float x, y, r;
  color c;

  Circle(float x, float y, float r, color c) {
    this.x = x;
    this.y = y;
    this.r = r;
    this.c = c;
  }

  void draw(){
    noStroke();
    fill(c);
    circle(x, y, r);
  }

}

class Flag {
  Rectangle rectangles[];
  Circle circles[];

  Flag(Rectangle rectangles[], Circle circles[]) {
    this.rectangles = rectangles;
    this.circles = circles;
  }

  void changePosition() {
    for(int i = 0; i < rectangles.length; i++) {
      rectangles[i].x += 230;
      if(rectangles[i].x > 940)
        rectangles[i].x = 248;
        if(i == 1 && (rectangles[i].l != rectangles[i-1].l))
          rectangles[i].x = rectangles[i-1].x + 25;
    }
    for(int i = 0; i < circles.length; i++) {
      circles[i].x += 230;
      if(circles[i].x > 1040)
        if(circles.length == 2) {
          circles[i].x = 338 + 10;
          if(i == 1)
            circles[i].x = circles[i-1].x + 10; 
      } else 
        circles[i].x = 338;
    }
  }

  void draw() {
    for(int i = 0; i < rectangles.length; i++)
      rectangles[i].draw();
    
    for(int i = 0; i < circles.length; i++)
      circles[i].draw();
  }

}

// Circle for flags with no Circle
Circle c0 = new Circle(0, 0, 0, white);
Circle noCircle[] = {c0};

// Parts of Japan Flag
Rectangle rJapan = new Rectangle(248, 324, 180, 120, white);

Circle cJapan = new Circle(338, 384, 60, red);

// Parts of Armenia Flag
Rectangle r1Armenia = new Rectangle(478, 324, 180, 40, armeniaRed);
Rectangle r2Armenia = new Rectangle(478, 364, 180, 40, armeniaBlue);
Rectangle r3Armenia = new Rectangle(478, 404, 180, 40, armeniaYellow);

// Parts of Maldives Flag
Rectangle r1Maldives = new Rectangle(708, 324, 180, 120, maldivesRed);
Rectangle r2Maldives = new Rectangle(733, 349, 130, 70, maldivesGreen);

Circle c1Maldives = new Circle(809, 384, 50, white);
Circle c2Maldives = new Circle(819, 384, 50, maldivesGreen);

// Parts of Indonesia Flag
Rectangle r1Indonesia = new Rectangle(938, 324, 180, 60, red);
Rectangle r2Indonesia = new Rectangle(938, 384, 180, 60, white);

// Japan Flag Parts
Rectangle fRJapan[] = {rJapan};
Circle fCJapan[] = {cJapan};

// Armenia Flag Parts
Rectangle fRArmenia[] = {r1Armenia, r2Armenia, r3Armenia};

// Maldives Flag Parts
Rectangle fRMaldives[] = {r1Maldives, r2Maldives};
Circle fCMaldives[] = {c1Maldives, c2Maldives};

// Indonesia Flag Parts
Rectangle fRIndonesia[] = {r1Indonesia, r2Indonesia};

Flag japan = new Flag(fRJapan, fCJapan);
Flag armenia = new Flag(fRArmenia, noCircle);
Flag maldives = new Flag(fRMaldives, fCMaldives);
Flag indonesia = new Flag(fRIndonesia, noCircle);

Flag flags[] = {japan, armenia, maldives, indonesia};

void flagChange() {
  for(int i = 0; i < flags.length; i++)
    flags[i].changePosition();
}

void update() {
  timer++;
  if(timer == 120) {
    flagChange();
    timer = 0;
  }
}

void settings() {
  size(windowX, windowY);
}

void setup() {}

void draw() {
  background(50);
  update();
  for(int i = 0; i < flags.length; i++)
    flags[i].draw();
}
