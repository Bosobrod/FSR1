#define STBI_NO_SIMD
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>


void DFS(int width, int height, int i, int k,  int* color, unsigned char* Image){
color[i] = k;
if (i + width + 1 < width * height){
  int R = Image[i + width + 1];
  if ((abs(Image[i] - R) <= 13) && (color[i + width + 1] == 0)) 
    DFS(width, height, i + width + 1, k, color, Image);}
if (i - width - 1 > 0){
  int L = Image[i - width - 1];
  if ((abs(Image[i] - L) <= 13) && (color[i - width - 1] == 0)) 
    DFS(width, height, i - width - 1, k, color, Image);}
if (i - width + 1 > 0){
  int A = Image[i - width + 1];
  if ((abs(Image[i] - A) <= 13) && (color[i - width + 1] == 0)) 
    DFS(width, height, i-width+1, k, color, Image);}
if (i + width - 1 < height * width){
  int B = Image[i + width - 1];
  if ((abs(Image[i] - B) <= 13) && (color[i + width - 1] == 0)) 
    DFS(width, height, i+width-1, k, color, Image);}
return;
}


int main(){

int width, height, n;
char* inputPath = "IMG_1894.PNG";
unsigned char* rawImage = stbi_load(inputPath, &width, &height, &n, 0);
if (rawImage == NULL){
  printf("Unable to read file");
  return 1;}

int k;
unsigned char* Image = (unsigned char*)malloc((width * height)*sizeof(unsigned char));
if (Image == NULL){
  printf("Unable to allocate memory");
  return 1;}
for (int i = 0; i < (width * height * n); i = i+n) {
  Image[k] = rawImage[i]*0.34375 + rawImage[i+1]*0.5 + rawImage[i+2]*0.15625;
  k++;
}

for (int i = 2; i < height - 1; i++) {
  for (int j = 2; j < width - 1; j++) {
    if (Image[width*i + j] < 92) 
      Image[width*i + j] = 0;
    if ((Image[width*i + j] >= 133) && (Image[width*i + j] <= 146)) 
      Image[width*i + j] = 255;
    if (Image[width*i + j] > 149) 
      Image[width*i + j] = 255;
    if (((Image[width*i + j] >= 92) && (Image[width*i + j] < 133)) || ((Image[width*i + j] > 146) && (Image[width*i + j] <= 149)))
      Image[width*i + j] = 127;
}}

unsigned char* finalImage = (unsigned char*)malloc((width * height * n)*sizeof(unsigned char));
int* color = (int*)malloc((width * height)*sizeof(int));
for (int i = 0; i < width * height; i++) 
  color[i] = 0;
k = 55;
for (int i = 0; i < width*height; i++){
  if (color[i] == 0) {
    DFS(width, height, i, k, color, Image);
     k = k + 50;
}}
for (int i = 0; i < width*height; i++){
  finalImage[i*n] = 0.8 * color[i-1] + color[i] + 10;
  finalImage[i*n + 1] = 0.8 * color[i-1] + color[i] + 95;
  finalImage[i*n + 2] = 0 * color[i-1] + color[i] + 150;
  finalImage[i*n + 3] = 255;}

char* outputPath = "output.png";
stbi_write_png(outputPath, width, height, n, finalImage, 0);

stbi_image_free(rawImage);
stbi_image_free(Image);
stbi_image_free(finalImage);
return 0;}



