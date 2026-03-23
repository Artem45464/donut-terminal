# 🍩 ASCII Donut in Terminal

> A lightweight C program that renders a rotating 3D donut (torus) directly in your terminal using math and ASCII shading.

---

## 📸 Demo

```id="j3p6h9"
     k;double sin()
         ,cos();main(){float A=
       0,B=0,i,j,z[1760];char b[
     1760];printf("\x1b[2J");for(;;
  ){memset(b,32,1760);memset(z,0,7040)
  ;for(j=0;6.28>j;j+=0.07)for(i=0;6.28
 >i;i+=0.02){float c=sin(i),d=cos(j),e=
 sin(A),f=sin(j),g=cos(A),h=d+2,D=1/(c*
 h*e+f*g+5),l=cos      (i),m=cos(B),n=s\
in(B),t=c*h*g-f*        e;int x=40+30*D*
(l*h*m-t*n),y=            12+15*D*(l*h*n
+t*m),o=x+80*y,          N=8*((f*e-c*d*g
 )*m-c*d*e-f*g-l        *d*n);if(22>y&&
 y>0&&x>0&&80>x&&D>z[o]){z[o]=D;;;b[o]=
 ".,-~:;=!*#$@"[N>0?N:0];}}/*#****!!-*/
  printf("\x1b[H");for(k=0;1761>k;k++)
   putchar(k%80?b[k]:10);A+=0.04;B+=
     0.02;}}/*****####*******!!=;:~
       ~::==!!!**********!!!==::-
         .,~~;;;========;;;:~-.
             ..,--------,*/
```

*(This is the original compact version of the ASCII donut. Your program renders a cleaner and animated version in real time.)*

---

## 🧠 How It Works

This program simulates a 3D torus using:

* Trigonometry (sine & cosine)
* 3D rotation
* Perspective projection
* Z-buffering
* ASCII lighting

---

## ⚙️ Requirements

* GCC or Clang
* Terminal (macOS, Linux, or Windows with WSL)

---

## 🛠️ Setup

### Compile

```bash id="zz9w4d"
gcc main.c -o donut -lm
```

### Run

```bash id="q1x9yb"
./donut
```

---

## 🎮 Controls

* `Ctrl + C` → Stop the program

---

## 🚀 Features

* Real-time 3D animation
* Terminal-based rendering
* No external libraries
* Lightweight single-file project

---
