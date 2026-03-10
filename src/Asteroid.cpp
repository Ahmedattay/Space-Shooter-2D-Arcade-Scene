// ---------------------------------------------------------------
//  Asteroid.cpp  –  Hazard asteroid rocks  (Object 4)
//  Depth: Z = -2  (between alien Z=-3 and spaceship Z=-1)
//
//  Two large asteroid rocks, one on each side of the screen.
//  Each asteroid has:
//    - Irregular rocky silhouette (layered offset circles)
//    - Dark shadow base
//    - Mid-tone grey surface
//    - Lighter face highlight
//    - Surface craters (dark + lighter rim circles)
//    - Bright specular highlight
//    - Small debris chunks floating nearby
//    - Glowing crack lines (thin bright triangles)
// ---------------------------------------------------------------

#include "Asteroid.h"
#include "Primitives.h"

static const float Z = -2.0f;
static const float Z_NEAR = Z + 0.005f;
static const float Z_FRONT = Z + 0.010f;

// ---------------------------------------------------------------
//  Helper: draw a single detailed asteroid at (cx, cy, radius)
// ---------------------------------------------------------------
static void drawRock(float cx, float cy, float r)
{
    // --- Shadow base (slightly offset, dark) ---
    drawCircle(cx + r * 0.12f, cy - r * 0.12f, Z,
        r * 1.05f,
        0.05f, 0.05f, 0.06f);

    // --- Irregular silhouette: overlapping circles to fake polygon shape ---
    // Main body
    drawCircle(cx, cy, Z_NEAR, r,
        0.38f, 0.36f, 0.34f);
    // Bulge top-left
    drawCircle(cx - r * 0.30f, cy + r * 0.35f, Z_NEAR, r * 0.72f,
        0.40f, 0.38f, 0.36f);
    // Bulge right
    drawCircle(cx + r * 0.38f, cy + r * 0.10f, Z_NEAR, r * 0.65f,
        0.36f, 0.34f, 0.32f);
    // Bulge bottom
    drawCircle(cx + r * 0.10f, cy - r * 0.38f, Z_NEAR, r * 0.68f,
        0.35f, 0.33f, 0.31f);
    // Bulge bottom-left
    drawCircle(cx - r * 0.28f, cy - r * 0.30f, Z_NEAR, r * 0.58f,
        0.37f, 0.35f, 0.33f);

    // --- Lit face (light comes from top-left) ---
    drawCircle(cx - r * 0.18f, cy + r * 0.22f, Z_NEAR, r * 0.70f,
        0.52f, 0.50f, 0.47f);

    // --- Dark shadow underside ---
    drawCircle(cx + r * 0.22f, cy - r * 0.25f, Z_NEAR, r * 0.55f,
        0.20f, 0.19f, 0.18f);

    // --- Craters ---
    // Large crater
    float c1x = cx + r * 0.12f, c1y = cy + r * 0.08f;
    drawCircle(c1x, c1y, Z_FRONT, r * 0.28f, 0.18f, 0.17f, 0.16f);
    drawCircle(c1x, c1y, Z_FRONT, r * 0.20f, 0.25f, 0.24f, 0.23f);
    // Crater rim highlight
    drawCircle(c1x - r * 0.08f, c1y + r * 0.08f, Z_FRONT, r * 0.08f,
        0.58f, 0.56f, 0.52f);

    // Medium crater
    float c2x = cx - r * 0.20f, c2y = cy - r * 0.12f;
    drawCircle(c2x, c2y, Z_FRONT, r * 0.18f, 0.16f, 0.15f, 0.14f);
    drawCircle(c2x, c2y, Z_FRONT, r * 0.12f, 0.22f, 0.21f, 0.20f);
    drawCircle(c2x - r * 0.04f, c2y + r * 0.05f, Z_FRONT, r * 0.05f,
        0.55f, 0.53f, 0.50f);

    // Small crater
    float c3x = cx + r * 0.05f, c3y = cy - r * 0.35f;
    drawCircle(c3x, c3y, Z_FRONT, r * 0.12f, 0.17f, 0.16f, 0.15f);
    drawCircle(c3x, c3y, Z_FRONT, r * 0.07f, 0.24f, 0.23f, 0.22f);

    // Tiny pock mark
    drawCircle(cx - r * 0.35f, cy + r * 0.40f, Z_FRONT, r * 0.07f,
        0.15f, 0.14f, 0.13f);

    // --- Specular highlight (bright spot, top-left) ---
    drawCircle(cx - r * 0.28f, cy + r * 0.32f, Z_FRONT, r * 0.14f,
        0.72f, 0.70f, 0.66f);
    drawCircle(cx - r * 0.30f, cy + r * 0.35f, Z_FRONT, r * 0.06f,
        0.88f, 0.86f, 0.84f);

    // --- Glowing crack (thin bright triangle streak across surface) ---
    drawTriangle(cx - r * 0.05f, cy + r * 0.15f,
        cx + r * 0.02f, cy + r * 0.13f,
        cx + r * 0.30f, cy - r * 0.20f,
        Z_FRONT,
        0.65f, 0.62f, 0.58f);

    drawTriangle(cx - r * 0.22f, cy - r * 0.05f,
        cx - r * 0.18f, cy - r * 0.08f,
        cx + r * 0.02f, cy - r * 0.28f,
        Z_FRONT,
        0.55f, 0.52f, 0.48f);
}

// ---------------------------------------------------------------
//  Helper: draw small debris chunks near a rock
// ---------------------------------------------------------------
static void drawDebris(float cx, float cy, float r, bool leftSide)
{
    float dir = leftSide ? -1.0f : 1.0f;

    // Chunk 1 – medium
    float d1x = cx + dir * r * 1.40f, d1y = cy + r * 0.60f;
    drawCircle(d1x, d1y, Z_NEAR, r * 0.28f, 0.32f, 0.30f, 0.28f);
    drawCircle(d1x - r * 0.06f, d1y + r * 0.06f, Z_FRONT, r * 0.14f,
        0.46f, 0.44f, 0.42f);
    drawCircle(d1x, d1y, Z_FRONT, r * 0.08f, 0.18f, 0.17f, 0.16f);

    // Chunk 2 – small
    float d2x = cx + dir * r * 1.20f, d2y = cy - r * 0.80f;
    drawCircle(d2x, d2y, Z_NEAR, r * 0.18f, 0.30f, 0.28f, 0.27f);
    drawCircle(d2x - r * 0.04f, d2y + r * 0.04f, Z_FRONT, r * 0.09f,
        0.44f, 0.42f, 0.40f);

    // Chunk 3 – tiny
    float d3x = cx + dir * r * 0.90f, d3y = cy + r * 1.10f;
    drawCircle(d3x, d3y, Z_NEAR, r * 0.12f, 0.33f, 0.31f, 0.29f);
    drawCircle(d3x, d3y, Z_FRONT, r * 0.06f, 0.48f, 0.46f, 0.44f);

    // Tiny pebbles (circles)
    drawCircle(cx + dir * r * 1.65f, cy + r * 0.20f, Z_FRONT, r * 0.07f,
        0.28f, 0.27f, 0.26f);
    drawCircle(cx + dir * r * 1.50f, cy - r * 0.40f, Z_FRONT, r * 0.05f,
        0.30f, 0.29f, 0.28f);
    drawCircle(cx + dir * r * 0.75f, cy + r * 1.30f, Z_FRONT, r * 0.06f,
        0.26f, 0.25f, 0.24f);
}

// ---------------------------------------------------------------
//  Public: draw both left and right asteroids
// ---------------------------------------------------------------
void drawAsteroid()
{
    // ---- LEFT ASTEROID ----
    // Positioned on the left side, vertically centred
    float lx = -0.72f, ly = 0.05f, lr = 0.18f;
    drawRock(lx, ly, lr);
    drawDebris(lx, ly, lr, true);

    // ---- RIGHT ASTEROID ----
    // Positioned on the right side, slightly higher
    float rx = 0.74f, ry = 0.20f, rr = 0.16f;
    drawRock(rx, ry, rr);
    drawDebris(rx, ry, rr, false);
}