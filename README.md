# so_long
![So Long](https://img.shields.io/badge/42-solong-blue)
![C](https://img.shields.io/badge/Language-C-brightgreen)
![Graphics](https://img.shields.io/badge/Graphics-2D%20Game-red)

A small 2D tile-based game built in C using MiniLibX, made as part of the 42 curriculum. Navigate a hipster character around a grid, collect all kebabs, and reach the exit door.

## Gameplay

- Collect every kebab on the map
- Reach the exit door (only opens once all kebabs are collected)
- Each move is counted and printed to the console

**Controls:**

| Key | Action |
|-----|--------|
| `W` | Move up |
| `A` | Move left |
| `S` | Move down |
| `D` | Move right |
| `ESC` | Quit |

## Map Format

Maps use `.ber` text files with the following characters:

| Character | Meaning |
|-----------|---------|
| `1` | Wall |
| `0` | Empty floor |
| `P` | Player start (exactly 1) |
| `E` | Exit (exactly 1) |
| `C` | Collectible / kebab (at least 1) |

Example map:
```
1111111111111111111111111111111111
1E1000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
```

Maps are validated on load: they must be rectangular, fully enclosed by walls, contain exactly one player and one exit, at least one collectible, and every collectible and the exit must be reachable from the player's starting position (checked via flood fill).

## Build

```bash
make        # build the game (auto-clones MiniLibX if needed)
make clean  # remove object files
make fclean # remove all compiled output including MiniLibX
make re     # clean rebuild
```

**Dependencies:** GCC, Make, X11 development libraries (`libx11-dev`, `libxext-dev`).

## Run

```bash
./solong maps/map.ber
```

Pass any valid `.ber` map file as the sole argument.

## Project Structure

```
solong/
├── src/
│   ├── main.c          # Entry point, game loop, key handling, player movement
│   ├── read_map.c      # Load map from .ber file into a 2D array
│   ├── valid_map.c     # Validate entity counts (P, E, C)
│   ├── valid_map2.c    # Validate shape, borders, and characters
│   ├── flood_fill.c    # DFS reachability check from player spawn
│   ├── render_game.c   # Texture loading and per-frame rendering
│   └── free_memory.c   # Cleanup for map and validation arrays
├── includes/
│   └── solong.h        # Structs (t_game, t_sprite), constants, prototypes
├── textures/           # XPM sprites (player, walls, kebab, door, floor)
├── maps/               # Sample .ber map files
├── libft/              # Custom C standard library
└── Makefile
```

## Validation Pipeline

Every map file goes through five checks before the game starts:

1. **Rectangle check** — all rows have the same length
2. **Character check** — only `0`, `1`, `P`, `E`, `C` are allowed
3. **Border check** — all edges must be walls (`1`)
4. **Entity count** — exactly one `P`, one `E`, one or more `C`
5. **Flood fill** — DFS from `P` confirms every `C` and `E` is reachable
