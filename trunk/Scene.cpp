#include <fstream>
#include <sstream>
#include <stack>
#include <stdio.h>
#include "algebra3.h"
#include "Sampler.h"
#include "Camera.h"
#include "Film.h"
#include "Color.h"
#include "Sphere.h"
#include "bmp/EasyBMP.h"
#include "util.h"


#define DEFAULT_SAMPLINGS 1
#define DEFAULT_TRACE_DEPTH 5
#define DEFAULT_OUTPUT_FILE_NAME "raytrace.bmp"

class Scene {
  Sampler* sampler;
  Camera* camera;
  Film* film;

  stack<mat4> modelview;
  mat4 toptransform;
  vec4* verts;
  vec4* vertnorm_verts;
  vec4* vertnorm_norms;
  int totalverts;
  int totalvertnorms;
  int currentvert;
  int currentvertnorm;

  int width;
  int height;
  int samplings;
  int tracedepth;
  string outputfilename;

  void parseScene(const char* inputfilename);
  bool parseCommand(string line);

public:
  Scene();
  ~Scene();
  void bootstrap(const char* inputfilename);
  void render();
  void outputImage();
  void debugmsg();
};

Scene::Scene() {
  samplings = DEFAULT_SAMPLINGS;
  tracedepth = DEFAULT_TRACE_DEPTH;
  outputfilename = DEFAULT_OUTPUT_FILE_NAME;
  toptransform = identity3D();
  totalverts = 0;
  totalvertnorms = 0;
  currentvert = 0;
  currentvertnorm = 0;
}

Scene::~Scene() {
  delete sampler;
  delete camera;
  delete film;
  delete verts;
  delete vertnorm_verts;
  delete vertnorm_norms;
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
  }
  else if (op == "size") {
    ss >> width >> height >> samplings;
    sampler = new Sampler(width, height, samplings);
    film = new Film(width, height, samplings*samplings); // samplings^2 samples per pixel
  }
  else if (op == "maxdepth") {
    ss >> tracedepth;
  }
  else if (op == "output") {
    ss >> outputfilename;
  }
  else if (op == "camera") {
    vec3 lookfrom, lookat, up;
    float fov;
    ss >> lookfrom[0] >> lookfrom[1] >> lookfrom[2] >> lookat[0] >> lookat[1] >> lookat[2] >> up[0] >> up[1] >> up[2] >> fov;
    camera = new Camera(lookfrom, lookat, up, fov, height/(float)width, 1.0, 10.0);
  }
  else if (op == "sphere") {
  }
  else if (op == "maxverts") {
    ss >> totalverts;
    verts = new vec4[totalverts];
  }
  else if (op == "maxvertnorms") {
    ss >> totalvertnorms;
    vertnorm_verts = new vec4[totalvertnorms];
    vertnorm_norms = new vec4[totalvertnorms];
  }
  else if (op == "vertex") {
    if (currentvert >= totalverts) {
      return false;
    }
    vec3 vert;
    ss >> vert[0] >> vert[1] >> vert[2];
    vert[3] = 1;
    verts[currentvert++] = vert;
  }
  else if (op == "vertexnormal") {
    if (currentvertnorm >= totalvertnorms) {
      return false;
    }
    vec3 vert, norm;
    ss >> vert[0] >> vert[1] >> vert[2] >> norm[0] >> norm[1] >> norm[2];
    vert[3] = 1;
    norm[3] = 0;
    vertnorm_verts[currentvertnorm] = vert;
    vertnorm_norms[currentvertnorm++] = norm;
  }
  else if (op == "tri") {
  }
  else if (op == "trinormal") {
  }
  else if (op == "translate") {
    vec3 tran;
    ss >> tran[0] >> tran[1] >> tran[2];
    toptransform = toptransform * translation3D(tran);

    printf("translate, toptransform:\n");  // DEBUG
    printMat(toptransform);                // DEBUG
  }
  else if (op == "rotate") {
    vec3 axis;
    float degree;
    ss >> axis[0] >> axis[1] >> axis[2] >> degree;
    toptransform = toptransform * rotation3D(axis, degree);

    printf("rotate, toptransform:\n");  // DEBUG
    printMat(toptransform);             // DEBUG
  }
  else if (op == "scale") {
    vec3 scale;
    ss >> scale[0] >> scale[1] >> scale[2];
    toptransform = toptransform * scaling3D(scale);

    printf("scale, toptransform:\n");  // DEBUG
    printMat(toptransform);            // DEBUG
  }
  else if (op == "pushTransform") {
    modelview.push(mat4(toptransform));

    printf("pushTransform, modelview.top():\n");  // DEBUG
    printMat(modelview.top());                    // DEBUG
  }
  else if (op == "popTransform") {
    if (modelview.empty()) {
      return false;
    }
    toptransform = modelview.top();
    modelview.pop();

    printf("popTransform, toptransform:\n");  // DEBUG
    printMat(toptransform);                   // DEBUG
  }
  else if (op == "directional") {
  }
  else if (op == "point") {
  }
  else if (op == "attenuation") {
  }
  else if (op == "ambient") {
  }
  else if (op == "diffuse") {
  }
  else if (op == "specular") {
  }
  else if (op == "shininess") {
  }
  else if (op == "emission") {
  }
  else {
    return false;  // unknown command
  }
  return true;
}

void Scene::bootstrap(const char* inputfilename) {
  parseScene(inputfilename);
}

void Scene::render() {
  vec2 sample;
  vec4 ray_ori;
  vec4 ray_dir;

  // TESTING
  Color red(1.0, 0.0, 0.0);
  Color black(0.0, 0.0, 0.0);

  Sphere sphere;
  sphere.setRadius(2.0);
  sphere.setCenter(vec3(0.0, 0.0, -16.0));

  double t;
  int count = 0;

  while (sampler->getSample(sample)) {
    camera->generateRay(sample, ray_ori, ray_dir);
    if (sphere.intersect(ray_ori, ray_dir, &t, 100.0)) {
      film->commit(red);
    }
    else {
      film->commit(black);
    }
  }
}

void Scene::outputImage() {
  BMP* image = film->generateImage();
  image->WriteToFile(outputfilename.c_str());
}

void Scene::debugmsg() {
  printf("Scene.sampler: {\n");
  sampler->debugmsg();
  printf("}\n");
  printf("Scene.camera: {\n");
  camera->debugmsg();
  printf("}\n");
}





int main(int argc, char** argv) {
  if (argc < 2) {
    printf("usage: raytracer inputfile\n");
    exit(1);
  }
  Scene scene;
  scene.bootstrap(argv[1]);  // bootstrap by parsing inputfile
  scene.render();
  scene.outputImage();
  //  scene.debugmsg();
}
