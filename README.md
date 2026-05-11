#  ASCII Donut in Terminal

> A lightweight, high-performance C program that renders a rotating 3D donut (torus) directly in your terminal using math and ASCII shading.

---

##  Features

*  **Real-time 3D animation** - Smooth rotation at 60 FPS
*  **Optimized performance** - Uses `memset()` and batch I/O for speed
*  **Graceful exit** - Press `Ctrl+C` to exit cleanly with signal handling
*  **Customizable rotation** - Control animation speed via command-line arguments
*  **Safe rendering** - Division-by-zero checks and bounds validation
*  **No external dependencies** - Just standard C library (`math.h`, `stdio.h`)
*  **Lightweight** - Single file, ~4KB with optimizations

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

* GCC or Clang compiler (with math library support)
* Terminal (macOS, Linux, Windows with WSL, or Git Bash)
* ANSI escape sequence support

---

##  Installation & Usage

### Compile

```bash
gcc main.c -o donut -lm
```

### Run (default animation)

```bash
./donut
```

### Run with custom rotation speeds

```bash
# Faster rotation
./donut 0.06 0.03

# Slower rotation
./donut 0.02 0.01

# Custom speeds (first arg: horizontal, second arg: vertical)
./donut 0.08 0.04
```

### Exit

Press **`Ctrl + C`** to stop and exit cleanly. The terminal will be restored to normal state with cursor visible.

---

##  Performance Optimizations

The code includes several performance enhancements:

- **Fast buffer initialization** - `memset()` instead of nested loops
- **Batch output** - `fwrite()` for faster screen rendering
- **Static buffers** - Avoids repeated stack allocation per frame
- **Float math** - Uses `cosf()`, `sinf()` for better performance
- **Safety checks** - Division-by-zero protection (`z > 0` check)

**Frame rate**: ~60 FPS (16.667ms per frame)  
**CPU usage**: Minimal  
**Memory**: ~1KB per frame

---

##  Technical Details

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

Luminance is calculated using the surface normal dot product with view direction.

### Screen Buffer
Uses ANSI escape sequences for fast screen clearing:
- `\x1b[2J\x1b[H` - Clear screen and move cursor to home
- `\x1b[?25l` - Hide cursor during animation
- `\x1b[?25h` - Restore cursor on exit

---

##  Customization

### Adjust rotation speed (command-line)

```bash
./donut 0.08 0.04
```

Or modify in code:
```c
float A_speed = 0.04f;  // Horizontal rotation
float B_speed = 0.02f;  // Vertical rotation
```

### Change donut size
Modify these constants in code:
```c
const float R1 = 1.0f;    // Minor radius (thickness)
const float R2 = 2.0f;    // Major radius (overall size)
```

### Smoother/faster rendering
Change sampling intervals:
```c
const float theta_spacing = 0.05f;   // Smaller = smoother, slower
const float phi_spacing   = 0.015f;
```

### Adjust frame rate
Change `usleep()` value:
```c
usleep(16667);  // Current: ~60 FPS
usleep(33333);  // Alternative: ~30 FPS
usleep(8333);   // Alternative: ~120 FPS (very fast)
```

---

##  Troubleshooting

### Terminal looks garbled
Make sure your terminal supports ANSI escape sequences:
-  macOS Terminal, iTerm2, Alacritty
-  Linux Terminal, Konsole, Gnome Terminal, xterm
-  Windows Terminal (new), WSL, Git Bash
-  Very old terminal emulators may not work

### Performance issues
If it's slow or choppy:
1. Close other applications
2. Try reducing sampling (`theta_spacing`, `phi_spacing`)
3. Try increasing `usleep()` value for smoother rendering

### Command-line arguments not working
Make sure you compile with `-lm`:
```bash
gcc main.c -o donut -lm
```

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
- R1 is the tube radius (thickness)
- R2 is the distance from center to tube (size)

The 3D rotations are applied around both X and Y axes using matrices, then perspective projection converts 3D coordinates to 2D screen space.

---

##  Recent Improvements (v2.0)

 **Performance**
- Fast buffer initialization with `memset()`
- Batch I/O with `fwrite()` instead of per-character writes
- Float-optimized math functions (`cosf()`, `sinf()`)

 **Safety**
- Division-by-zero protection
- Proper bounds checking
- Signal handling for clean exit

 **Code Quality**
- Better constants and named values
- Improved comments and documentation
- Proper use of `M_PI` instead of hardcoded values

 **User Experience**
- Graceful exit with `Ctrl+C`
- Command-line control of rotation speeds
- Restored cursor and clean terminal on exit

---

##  Credits

Original concept inspired by the famous one-liner donut by Fabrice Bellard.

This version includes optimizations, safety improvements, and better user experience.
