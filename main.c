#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define screen_width 80
#define screen_height 22
#define TWO_PI (2.0f * M_PI)

// Rendering parameters
const float theta_spacing = 0.05f;
const float phi_spacing   = 0.015f;

// Torus geometry
const float R1 = 1.0f;
const float R2 = 2.0f;
const float K2 = 5.0f;
const float K1 = screen_width * K2 * 3.0f / (8.0f * (R1 + R2));

// Luminance characters (12 levels)
const char *luminance_chars = ".,-~:;=!*#$@";
const int num_luminance = 12;

// Global flag for graceful exit
volatile int should_exit = 0;

void handle_signal(int sig) {
    should_exit = 1;
}

void render_frame(float A, float B) {
    float cosA = cosf(A), sinA = sinf(A);
    float cosB = cosf(B), sinB = sinf(B);

    // Use static buffers to avoid stack overflow on some systems
    static char output[screen_height][screen_width];
    static float zbuffer[screen_height][screen_width];

    // Fast initialization using memset
    memset(output, ' ', sizeof(output));
    memset(zbuffer, 0, sizeof(zbuffer));

    // Render the torus
    for (float theta = 0; theta < TWO_PI; theta += theta_spacing) {
        float costheta = cosf(theta), sintheta = sinf(theta);

        for (float phi = 0; phi < TWO_PI; phi += phi_spacing) {
            float cosphi = cosf(phi), sinphi = sinf(phi);

            // Calculate circle coordinates
            float circlex = R2 + R1 * costheta;
            float circley = R1 * sintheta;

            // 3D rotation and projection
            float x = circlex * (cosB * cosphi + sinA * sinB * sinphi) - circley * cosA * sinB;
            float y = circlex * (sinB * cosphi - sinA * cosB * sinphi) + circley * cosA * cosB;
            float z = K2 + cosA * circlex * sinphi + circley * sinA;

            // Check for valid depth (avoid division by zero)
            if (z <= 0.0f) continue;

            float ooz = 1.0f / z;

            // Project to screen coordinates
            int xp = (int)(screen_width / 2 + K1 * ooz * x);
            int yp = (int)(screen_height / 2 - K1 * ooz * y);

            // Calculate lighting
            float L = cosphi * costheta * sinB - cosA * costheta * sinphi -
                      sinA * sintheta + cosB * (cosA * sintheta - costheta * sinA * sinphi);

            // Check bounds and visibility
            if (L > 0 && xp >= 0 && xp < screen_width && yp >= 0 && yp < screen_height) {
                if (ooz > zbuffer[yp][xp]) {
                    zbuffer[yp][xp] = ooz;
                    
                    // Clamp luminance index to valid range
                    int luminance_index = (int)(L * num_luminance);
                    if (luminance_index < 0) luminance_index = 0;
                    if (luminance_index >= num_luminance) luminance_index = num_luminance - 1;
                    
                    output[yp][xp] = luminance_chars[luminance_index];
                }
            }
        }
    }

    // Clear screen and move cursor home
    printf("\x1b[2J\x1b[H");

    // Render frame to stdout (fast batch write)
    for (int j = 0; j < screen_height; j++) {
        fwrite(output[j], sizeof(char), screen_width, stdout);
        putchar('\n');
    }

    fflush(stdout);
}

int main(int argc, char *argv[]) {
    float A = 0.0f, B = 0.0f;
    float A_speed = 0.04f;
    float B_speed = 0.02f;

    // Parse command-line arguments
    if (argc > 1) {
        A_speed = strtof(argv[1], NULL);
    }
    if (argc > 2) {
        B_speed = strtof(argv[2], NULL);
    }

    // Set up signal handler for graceful exit (Ctrl+C)
    signal(SIGINT, handle_signal);

    // Hide cursor
    printf("\x1b[?25l");
    fflush(stdout);

    // Main animation loop
    while (!should_exit) {
        render_frame(A, B);
        A += A_speed;
        B += B_speed;
        usleep(16667);  // ~60 FPS
    }

    // Show cursor and clear screen on exit
    printf("\x1b[?25h\x1b[2J");
    fflush(stdout);

    return 0;
}
