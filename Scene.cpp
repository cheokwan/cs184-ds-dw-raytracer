#include <fstream>
#include <sstream>
#include <stdio.h>
#include "algebra3.h"
#include "Sampler.h"
#include "Camera.h"
#include "Film.h"

#include "bmp/EasyBMP.h"
#include "Sphere.h"

#define DEFAULT_SAMPLINGS 1
#define DEFAULT_TRACE_DEPTH 5
#define DEFAULT_OUTPUT_FILE_NAME "raytrace.txt"

class Scene {
  Sampler sampler;
  Camera camera;
  Film film;

  int width;
  int height;
  int tracedepth;
  string outputfilename;

  void parseScene(const char* inputfilename);
  bool parseCommand(string line);

public:
  Scene();
  ~Scene() {};
  void bootstrap(const char* inputfilename);
  void render();
  void outputImage();
  void debugmsg();
};

Scene::Scene() {
  tracedepth = DEFAULT_TRACE_DEPTH;
  outputfilename = DEFAULT_OUTPUT_FILE_NAME;
}

void Scene::parseScene(const char* inputfilename) {
  ifstream inputfile(inputfilename);
  if (!inputfile) {
    printf("ERROR: failed to open file %s\n", inputfilename);
    exit(1);
  }
  const int linesize = 256;
  char line[linesize];
  int linecount = 1;
  while (inputfile.good()) {
    inputfile.getline(line, linesize);
    if (!parseCommand(string(line))) {
      printf("ERROR: invalid command at line %d\n", linecount);
      exit(1);
    }
    linecount++;
  }
  inputfile.close();
}

bool Scene::parseCommand(string line) {
  if (line.empty()) {
    return true;
  }
  string op;
  stringstream ss(stringstream::in | stringstream::out);
  ss.str(line);
  ss >> op;
  if (op == "#") {  // comment
    return true;
  } else if (op == "size") {
    ss >> width >> height;
    sampler = Sampler(width, height, DEFAULT_SAMPLINGS);
    film = Film(width, height, DEFAULT_SAMPLINGS);
  } else if (op == "camera") {
    float lookfromx, lookfromy, lookfromz, lookatx, lookaty, lookatz, upx, upy, upz, fov;
    ss >> lookfromx >> lookfromy >> lookfromz >> lookatx >> lookaty >> lookatz >> upx >> upy >> upz >> fov;
    camera = Camera(vec3(lookfromx, lookfromy, lookfromz), vec3(lookatx, lookaty, lookatz), vec3(upx, upy, upz),
                    fov, width/(float)height, 1.0, 10.0);
  } else if (op == "maxdepth") {
    ss >> tracedepth;
  } else if (op == "output") {
    ss >> outputfilename;
  } else {
    return false;  // unknown command
  }
  return true;
}


void Scene::bootstrap(const char* inputfilename) {
  parseScene(inputfilename);
}

void Scene::render() {
}

void Scene::outputImage() {
  ofstream outputfile(outputfilename.c_str());
  outputfile.write("testing output data", 20);
  outputfile.close();
}

void Scene::debugmsg() {
  printf("Scene.sampler: {\n");
  sampler.debugmsg();
  printf("}\n");
  printf("Scene.camera: {\n");
  camera.debugmsg();
  printf("}\n");
}





int main(int argc, char** argv) {
  if (argc < 2) {
    printf("usage: raytracer inputfile\n");
    exit(1);
  }
  Scene scene;
  scene.bootstrap(argv[1]);  // bootstrap by parsing inputfile
  scene.outputImage();

  //scene.debugmsg();
}


/*
void milestone() {
  int size_x = 640;
  int size_y = 480;
  vec3 cam_lookfrom(0.0, 0.0, 10.0);
  vec3 cam_lookat(0.0, 0.0, -1.0);
  vec3 cam_up(0.0, 1.0, 0.0);
  float fov = 60.0;


  Sphere sphere = Sphere();
  sphere.setRadius(2.0);
  sphere.setCenter(vec3(0.0, 0.0, -16.0));

  RGBApixel *red, *black;
  red = (RGBApixel*) malloc (sizeof(RGBApixel));
  red->Red = 255; red->Blue = 0; red->Green = 0; red->Alpha = 0;
  black = (RGBApixel*) malloc (sizeof(RGBApixel));
  black->Red = 0; black->Blue = 0; black->Green = 0; black->Alpha = 0;
  BMP *myPic = new BMP();
  myPic->SetSize(size_x, size_y);
  int x = 0; int y = 0;


  Sampler test_sampler(size_x, size_y, 1);
  Camera camera(cam_lookfrom, cam_lookat, cam_up, fov, size_x / float(size_y), 1.0, 10.0);
  vec2 sample;
  vec3 ray;
  while (test_sampler.getSample(sample)) {
    //printf("sample x: %.2f,  y: %.2f\n", sample[0], sample[1]);
    camera.generateRay(sample, ray);
    //printf("ray (%.2f, %.2f, %.2f)\n", ray[0], ray[1], ray[2]);

    if (x == size_x) {
      y++;
      x = 0;
    }
    if (sphere.intersect(camera.position(), ray)) {
      myPic->SetPixel(x, y, *red);
    }
    else {
      myPic->SetPixel(x, y, *black);
    }
    x++;
  }

  myPic->WriteToFile("milestone.bmp");
  delete myPic;
  free(red);
  free(black);
}
*/
