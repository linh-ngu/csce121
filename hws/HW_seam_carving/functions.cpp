#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // delete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      // cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

// implement for part 1

int* createSeam(int length) {
  int* seam = new int[length]; 
  for (int i = 0; i < length; i += 1){
    seam[i] = 0;
  }
  return seam;
}

void deleteSeam(int* seam) {
  delete [] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "Error: failed to open input file - " << filename;
    return false;
  }

  string type;
  getline(file, type);
  if (toupper(type[0]) != 'P' || type[1] != '3') {
    cout << "Error: type is " << type << " instead of P3";
    return false;
  }

  int fileHeight;
  int fileWidth;
  string dims;
  getline(file, dims);
  stringstream s(dims);

  s >> fileWidth;
  if (s.fail()) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if (width != fileWidth) {
    cout << "Error: input width (" << width << ") does not match value in file (" << fileWidth << ")" << endl;
    return false;
  }

  s >> fileHeight;
  if (s.fail()) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }
  if (height != fileHeight) {
    cout << "Error: input height (" << height << ") does not match value in file (" << fileHeight << ")" << endl;
    return false;
  }

  string maxValue;
  getline(file, maxValue);
  int maxColorValue;
  try {
    maxColorValue = stoi(maxValue);
  } catch (...) {
    cout << "Error: read non-integer value" << endl;
    return false;
  }

  int r, g, b;
  for (int i = 0; i < height; i += 1) {
    for (int j = 0; j < width; j += 1) {
      file >> r;
      if (file.eof()) {
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if (file.fail()) {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if (r < 0 || r > maxColorValue) {
        cout << "Error: invalid color value " << r << endl;
        return false;
      }

      file >> g;
      if (file.eof()) {
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if (file.fail()) {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if (g < 0 || g > maxColorValue) {
        cout << "Error: invalid color value " << g << endl;
        return false;
      }

      file >> b;
      if (file.eof() && (i != height - 1 || j != width - 1)) {
        cout << "Error: not enough color values" << endl;
        return false;
      }
      if (file.fail()) {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
      if (b < 0 || b > maxColorValue) {
        cout << "Error: invalid color value " << b << endl;
        return false;
      }
      
      image[j][i].r = r;
      image[j][i].g = g;
      image[j][i].b = b;
    }
  }

  string line;
  file >> line;
  if (!file.eof()) {
    cout << "Error: too many color values" << endl;
    return false;
  }

  return true;
}

bool outputImage(string filename, const Pixel*const* image, int width, int height) {
  ofstream file(filename);
  if (!file.is_open()) {
    cout << "Error: failed to open output file - " << filename;
    return false;
  }

  file << "P3" << endl;
  file << width << " " << height << endl;
  file << "255" << endl;

  for (int i = 0; i < height; i += 1) {
    string line = "";
    for (int j = 0; j < width; j += 1) {
      line += to_string(image[i][j].r) + " " + to_string(image[i][j].g) + " " + to_string(image[i][j].b) + " ";
    }
    file << line.substr(0, line.size() - 1) << endl;
  }
  return true;
}

int energy(const Pixel*const* image, int x, int y, int width, int height) {
  int energy = 0;

  // x
  int xp = x+1;
  int xm = x-1;
  if (xp == width) xp = 0;
  if (xm == -1) xm = width - 1;
  energy += pow(abs(image[xm][y].r - image[xp][y].r), 2);
  energy += pow(abs(image[xm][y].g - image[xp][y].g), 2);
  energy += pow(abs(image[xm][y].b - image[xp][y].b), 2);

  // y
  int yp = y+1;
  int ym = y-1;
  if (yp == height) yp = 0;
  if (ym == -1) ym = height - 1;
  energy += pow(abs(image[x][ym].r - image[x][yp].r), 2);
  energy += pow(abs(image[x][ym].g - image[x][yp].g), 2);
  energy += pow(abs(image[x][ym].b - image[x][yp].b), 2);

  return energy;
}

// implement for part 2

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  int left, right, forward, totalEnergy;
  totalEnergy = energy(image, start_col, 0, width, height);
  
  seam[0] = start_col;

  if (width == 1) {
    for (int i = 1; i < height; i++) {
      forward = energy(image, start_col, i, width, height);
      totalEnergy += forward;
      seam[i] = start_col;
    }
    return totalEnergy;
  }

  for (int i = 1; i < height; i++) {
    if (start_col == 0) {
      forward = energy(image, start_col, i, width, height);
      right = energy(image, start_col + 1, i, width, height);
      left = INT32_MAX;
    } 
    else if (start_col == width - 1) {
      forward = energy(image, start_col, i, width, height);
      left = energy(image, start_col - 1, i, width, height);
      right = INT32_MAX;
    } 
    else {
      left = energy(image, start_col - 1, i, width, height);
      forward = energy(image, start_col, i, width, height);
      right = energy(image, start_col + 1, i, width, height);
    }
    if (left < forward && left < right) {
      cout << "right" << " ";
      totalEnergy += left;
      start_col -= 1;
      seam[i] = start_col;
    } 
    else if ((right < left && right < forward) || (left == right && left < forward)) {
      cout << "left" << " ";
      totalEnergy += right;
      start_col += 1;
      seam[i] = start_col;
    }
    else {
      cout << "forward" << " ";
      totalEnergy += forward;
      seam[i] = start_col;
    }
  }
  return totalEnergy;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  int* minSeam = createSeam(height);
  int* currSeam = createSeam(height);
  int minEnergy = loadVerticalSeam(image, 0, width, height, currSeam);

  for (int i = 0; i < height; i++) {
    minSeam[i] = currSeam[i];
  }

  for (int i = 1; i < width; i++) {
    int currEnergy = loadVerticalSeam(image, i, width, height, currSeam);
    if (currEnergy < minEnergy) {
      minEnergy = currEnergy;
      for (int i = 0; i < height; i++) {
        minSeam[i] = currSeam[i];
      }
    }
  }
  delete [] currSeam;
  return minSeam;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
  for (int i = 0; i < height; i++) {
    for (int j = verticalSeam[i]; j < width - 1; j++) {
      image[j][i] = image[j + 1][i];
    }
  }
}

// int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
//   return 0;
// }

// int* findMinHorizontalSeam(Pixel** image, int width, int height) {
//   return nullptr;
// }

// void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
//
// }
