#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define screen_width 80
#define screen_height 22
#define pi 3.141592653589793

const float theta_spacing = 0.05;
const float phi_spacing   = 0.015;

const float R1 = 1;
const float R2 = 2;
const float K2 = 5;
const float K1 = screen_width*K2*3/(8*(R1+R2));

void render_frame(float A, float B) {
  float cosA = cos(A), sinA = sin(A);
  float cosB = cos(B), sinB = sin(B);

  char output[screen_height][screen_width];
  float zbuffer[screen_height][screen_width];

  for(int i=0; i<screen_height; i++) {
    for(int j=0; j<screen_width; j++) {
      output[i][j] = ' ';
      zbuffer[i][j] = 0;
    }
  }

  for (float theta=0; theta < 2*pi; theta += theta_spacing) {
    float costheta = cos(theta), sintheta = sin(theta);

    for(float phi=0; phi < 2*pi; phi += phi_spacing) {
      float cosphi = cos(phi), sinphi = sin(phi);
    
      float circlex = R2 + R1*costheta;
      float circley = R1*sintheta;

      float x = circlex*(cosB*cosphi + sinA*sinB*sinphi) - circley*cosA*sinB; 
      float y = circlex*(sinB*cosphi - sinA*cosB*sinphi) + circley*cosA*cosB;
      float z = K2 + cosA*circlex*sinphi + circley*sinA;
      float ooz = 1/z;
      
      int xp = (int) (screen_width/2 + K1*ooz*x);
      int yp = (int) (screen_height/2 - K1*ooz*y);
      
      float L = cosphi*costheta*sinB - cosA*costheta*sinphi -
        sinA*sintheta + cosB*(cosA*sintheta - costheta*sinA*sinphi);
      
      if (L > 0 && xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
        if(ooz > zbuffer[yp][xp]) {
          zbuffer[yp][xp] = ooz;
          int luminance_index = (int)(L*8);
          if (luminance_index < 0) luminance_index = 0;
          if (luminance_index > 11) luminance_index = 11;
          output[yp][xp] = ".,-~:;=!*#$@"[luminance_index];
        }
      }
    }
  }

  printf("\x1b[2J\x1b[H");
  
  for (int j = 0; j < screen_height; j++) {
    for (int i = 0; i < screen_width; i++) {
      putchar(output[j][i]);
    }
    putchar('\n');
  }
  
  fflush(stdout);
}

int main() {
  float A = 0, B = 0;
  printf("\x1b[?25l");
  
  while (1) {
    render_frame(A, B);
    A += 0.04;
    B += 0.02;
    usleep(16667);
  }
  
  return 0;
}
