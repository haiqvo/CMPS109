#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>

#ifdef __linux
#include <GL/gl.h>
#include <GL/glut.h>
#elif __unix
#include <GL/gl.h>
#include <GL/glut.h>
#elif __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#endif

using namespace std;


//The shape superclass
class Shape{
protected:
  float xLoc;
  float yLoc;
  float scaleFactor;
virtual void specificDraw() const;

public:
  static vector<Shape *> drawList;
  static Shape* cursor;
  Shape(float x, float y, float s);
  void draw() const;
  void addMove(float x, float y){xLoc += x; yLoc += y;};
  void scale(float s){scaleFactor = s;};
};

vector<Shape*> Shape::drawList = vector<Shape*>();


//Shape constructor
Shape::Shape(float x, float y, float s): 
  xLoc(0),yLoc(0),scaleFactor(1){
  this->xLoc = x;
  this->yLoc = y;
  this->scaleFactor = s;
}

//Shape Draw:
void Shape::draw() const{
    glPushMatrix();
    glTranslatef(xLoc,yLoc,0);
    glScalef(scaleFactor,scaleFactor,1);
    
    this->specificDraw();
    glPopMatrix();
  };

//Shape Specific Draw:
void Shape::specificDraw() const{
  cout << "Virtual specific draw\n";
}

//---------------
//Triangle Class:
class Triangle : public Shape{
public:
  Triangle(float x, float y, float s);
protected:
  void specificDraw() const;

};

Triangle::Triangle(float x, float y, float s):Shape(x,y,s){
  //cout << "Creating Triangle";
}

void Triangle::specificDraw() const{
       glBegin(GL_POLYGON);
       glVertex2f(0,0);
       glVertex2f(0,1);
       glVertex2f(1,0);
       glEnd();
}

//-----------------
class Hexagon : public Shape{
public:
  Hexagon(float x, float y, float s);
protected:
  void specificDraw() const;
};

Hexagon::Hexagon(float x, float y, float s):Shape(x,y,s){

}

void Hexagon::specificDraw() const{
  //glBegin(GL_POLYGON);
  glBegin(GL_LINES);

  glVertex2d(sin(0/6.0*2*M_PI), cos(0/6.0*2*M_PI) );
  for(int i = 1; i < 6; ++i) {
    glVertex2d(sin(i/6.0*2*M_PI), cos(i/6.0*2*M_PI) );
    glVertex2d(sin(i/6.0*2*M_PI), cos(i/6.0*2*M_PI) );
  }
  glVertex2d(sin(0/6.0*2*M_PI), cos(0/6.0*2*M_PI) );

  glEnd();
}

//--------------
class Rectangle : public Shape{
public:
  Rectangle(float x, float y, float s, float c1, float c2, float c3);
protected:
  float c1;
  float c2;
  float c3;
  void specificDraw() const;
};

Rectangle::Rectangle(float x, float y, float s,float c1, float c2,
  float c3):Shape(x,y,s){
  this->c1 = c1;
  this->c2 = c2;
  this->c3 = c3;
  //cout << "Creating Rectangle";
}

void Rectangle::specificDraw() const{
       
  glColor3f(this->c1,this->c2,this->c3);
  glBegin(GL_POLYGON);
  glVertex2f(0,0);
  glVertex2f(0,1);
  glVertex2f(1,1);
  glVertex2f(1,0);
  glEnd();
}

Shape* Shape::cursor = new Rectangle(0,0,1,1,0,0);
//----------------
//Text class:
class Text : public Shape{
public:
  string text;
  Text(float x, float y, float s, string t);
  
private:
  void specificDraw() const;
};

Text::Text(float x, float y, float s, string t):Shape(x,y,s){
    this->text = t;
}

void Text::specificDraw() const{
  for(int i=0; i<this->text.length(); ++i){
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
  }
}



//Main draw callback:
void drawStuff(){
  

  //Standard initialisation stuff:
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); 

  //Viewpoint:
    //Left, right, bottom, top, near, far    
  glOrtho(-0.0, 4.0, -0.0, 4.0, -2.0, 500.0); 
  glMatrixMode(GL_MODELVIEW);
    
  for(vector<Shape *>::iterator it = Shape::drawList.begin();
      it != Shape::drawList.end(); ++it){
    (*it)->draw();
  }

  glPushMatrix();
  glTranslatef(0,0,1);
  //(Shape::cursor)->draw();
  glPopMatrix();
  //glScalef(0.5,0.5,0.5);
  //glutSolidTeapot(15);

  glutSwapBuffers(); 
}



static void idle(){
  for(vector<Shape *>::iterator it = Shape::drawList.begin();
      it != Shape::drawList.end(); ++it){
    //(*it)->addMove(0.1, 0);
  }

  glutPostRedisplay();
}


void setupDrawList(){

  bool c = false;

  for(int j = 0; j < 10; j++){
    for(int i = 0; i < 10; i++){
      if(c){
        c = !c;
        //Shape::drawList.push_back(new Rectangle(i, j, 1, 0,1,0));
      }else{
        c = !c;
        //Shape::drawList.push_back(new Rectangle(i, j, 1, 0,0,1));
      }
    }
    c = !c;
  }



  //Shape::drawList.push_back(new Triangle(0,0,1));
  //Shape::drawList.push_back(new Triangle(1,1,1));
  for(int i = 0; i<11; i++) {
    for(int j= 0; j<11; j++) {
      Shape::drawList.push_back(new Hexagon(1.5+(0.175*i)+(-0.0875)*j, 1.5+(0.15*j), 0.1));
    }
  }
  //Shape::drawList.push_back(new Text(2,2,0.005,"hello"));
  //Shape::drawList.push_back(new Rectangle(3,3,1));

}

void key(unsigned char key, int a, int b){
  cout << key << "\n";

  switch(key){
  case 'a':
    Shape::cursor->addMove(-1,0);
    break;
  case 'd':
    Shape::cursor->addMove(1,0);
    break;
  case 's':
    Shape::cursor->addMove(0,-1);
    break;
  case 'w':
    Shape::cursor->addMove(0,1);
    break;
  }


  if(key =='r'){
  for(vector<Shape *>::iterator it = Shape::drawList.begin();
      it != Shape::drawList.end(); ++it){
    (*it)->addMove(-10, 0);
  }

  }


}

void onMouseButton(int button, int state, int x, int y){
  switch(button){
    case GLUT_LEFT_BUTTON:   
      cout << "x : " << x << " y : " << y << endl;   
      break;
  }
}

int main(int argc, char **argv){
  std::cout << "OpenGL simple examples" << std::endl; 

  

  setupDrawList();

  //If there is a display, do something.
  if(getenv("DISPLAY")){
    std::string display (getenv("DISPLAY"));
    std::cout << display << std::endl;

    

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500); //Set the size you want
    glutCreateWindow("GL Primer"); //Window name
      
    glutKeyboardFunc(key);
    glutDisplayFunc(drawStuff); //Callback for the current window
    glutMouseFunc(onMouseButton);
    glutIdleFunc(idle);
    glutMainLoop();
    
  }else{ //otherwise complain
    std::cout <<"arg no display" << std::endl;
  }

  return 0;

}