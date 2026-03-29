#  ASCII Donut in Terminal

> A lightweight C program that renders a rotating 3D donut (torus) directly in your terminal using math and ASCII shading.

---

##  Features

*  **Real-time 3D animation** - Smooth rotation at 60 FPS
*  **Responsive design** - Works with any terminal size
*  **Perfectly centered** - Donut stays in the middle of screen
*  **Scroll-proof** - Uses alternate screen buffer, won't break when scrolling
*  **No dependencies** - Just standard C math library
*  **Lightweight** - Single file, ~3KB

---

##  How It Works

This program simulates a 3D torus using:

* **Trigonometry** - Sine & cosine for 3D coordinates
* **3D rotation** - Rotation matrices for smooth animation
* **Perspective projection** - Convert 3D to 2D screen space
* **Z-buffering** - Depth sorting for correct occlusion
* **ASCII lighting** - 12 different ASCII characters for shading

---

##  Requirements

* GCC or Clang compiler
* Terminal (macOS, Linux, Windows with WSL)
* `math.h` library support

---

##  Installation & Usage

### Compile

```bash
gcc donut_responsive.c -o donut -lm
```

### Run

```bash
./donut
```

Press `Ctrl + C` to stop and exit cleanly.

---

##  Versions Available

### `donut_responsive.c` (Recommended)
-  Full-featured version
-  Auto-detects terminal size
-  Smooth 60 FPS animation
-  Scroll-proof (alternate screen buffer)
-  Always centered, won't break on resize

### `donut_improved.c`
- Interactive keyboard controls
- Real-time statistics display
- Adjustable rotation speeds
- Help menu

### `donut_simple.c`
- Minimal version
- No controls
- Just smooth rotating donut

---

##  Terminal Size

The donut automatically adapts to your terminal size:

- **Small terminals** (40x10) - Donut scales down
- **Large terminals** (200x50) - Donut scales up
- **Resize anytime** - Donut recalculates and stays centered
- **Scroll freely** - Won't break or freeze when scrolling

---

##  Performance

- **Frame rate**: ~60 FPS (16.667ms per frame)
- **CPU usage**: Minimal
- **Memory**: ~1KB per frame
- **No lag** - Smooth on most systems

---

##  Technical Details

### Screen Buffer
Uses ANSI alternate screen buffer (`\x1b[?1049h`) to prevent terminal scrolling issues. This creates a dedicated screen for the donut that doesn't interfere with your terminal history.

### Dynamic Sizing
Every frame, the program:
1. Detects current terminal dimensions using `ioctl()`
2. Recalculates rendering parameters (K1)
3. Renders donut centered at `(width/2, height/2)`
4. Clears screen with `\x1b[2J\x1b[H`

### 3D Math
```
circlex = R2 + R1 * cos(theta)
circley = R1 * sin(theta)

x = circlex*(cosB*cosphi + sinA*sinB*sinphi) - circley*cosA*sinB
y = circlex*(sinB*cosphi - sinA*cosB*sinphi) + circley*cosA*cosB
z = K2 + cosA*circlex*sinphi + circley*sinA

xp = width/2 + K1*(x/z)
yp = height/2 - K1*(y/z)
```

### ASCII Palette
The shading uses 12 characters from darkest to brightest:
```
. , - ~ : ; = ! * # $ @
```

Luminance is calculated using the surface normal dot product with view direction, ranging from -√2 to +√2.

---

##  Customization

### Adjust rotation speed
In `main()`, change:
```c
A += 0.04;  // Horizontal rotation speed
B += 0.02;  // Vertical rotation speed
```

### Change donut size
Modify these constants:
```c
const float R1 = 1;    // Minor radius (thickness)
const float R2 = 2;    // Major radius (overall size)
```

### Smoother/faster rendering
Change `theta_spacing` and `phi_spacing`:
```c
const float theta_spacing = 0.05;  // Smaller = smoother, slower
const float phi_spacing   = 0.015;
```

### Adjust frame rate
Change `usleep()` value in main loop:
```c
usleep(16667);  // Current: ~60 FPS
// usleep(33333);  // Alternative: ~30 FPS
```

---

##  Troubleshooting

### Donut breaks when scrolling
**This is fixed!** The responsive version uses alternate screen buffer. If you're using an older version, upgrade to `donut_responsive.c`.

### Terminal looks garbled
Make sure your terminal supports ANSI escape sequences:
-  macOS Terminal, iTerm2
-  Linux Terminal, Konsole, Gnome Terminal
-  Windows Terminal (new), WSL
-  Very old terminal emulators may not work

### Donut not centered
This shouldn't happen with the responsive version. Try:
1. Resize your terminal window
2. Run the program again
3. Press `Ctrl+C` and restart

### Performance issues
If it's slow or choppy:
1. Close other applications
2. Try increasing `usleep()` value
3. Reduce sampling (`theta_spacing`, `phi_spacing`)

---

##  How to Exit

Simply press **`Ctrl + C`** and the program will:
1. Exit cleanly
2. Restore normal terminal screen
3. Show cursor again
4. Return to your command prompt

---

##  Math Behind The Scenes

The donut is a parametric surface defined by:

```
x(θ, φ) = (R2 + R1*cos(θ)) * cos(φ)
y(θ, φ) = R1 * sin(θ)
z(θ, φ) = (R2 + R1*cos(θ)) * sin(φ)
```

Where:
- θ (theta) goes around the tube (0 to 2π)
- φ (phi) goes around the center (0 to 2π)
- R1 is the tube radius
- R2 is the distance from center to tube

The 3D rotations are applied around both X and Y axes, then perspective projection converts to 2D screen coordinates.

---

##  Credits

Original concept inspired by the famous one-liner donut by Fabrice Bellard.

This improved version adds:
- Terminal responsiveness
- Scroll-proof rendering
- Better code organization
- Multiple feature levels

---
