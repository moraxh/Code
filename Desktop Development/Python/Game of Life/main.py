import pygame as py

def main():
    run = True
    # Some Colors
    white = (255, 255, 255)
    gray = (200, 200, 200)
    black = (0, 0, 0)

    # Initialize pygame and a screen
    py.init()
    py.display.set_caption("Game of Life[Paused]")
    ssize = (700, 500)
    screen = py.display.set_mode(ssize)
    timer = py.time.Clock()

    grid = [[0] * 50 for i in range(50)]
    grid_copy = [[0] * 50 for i in range(50)]
    vinit = int((ssize[0] - ssize[1]) / 2)
    vend = int(ssize[0] - vinit)

    paused = True

    while(run):
        
        # Background
        screen.fill(white)

        # Create vertical grid
        for i in range(vinit, vend + 1, 10):
            py.draw.line(screen, gray, (i, 0), (i, ssize[1]))
        # Create horizontal grid
        for i in range(0, ssize[1] + 1, 10):
            py.draw.line(screen, gray, (vinit, i), (vend, i))

        # Mouse input detection
        if py.mouse.get_pressed()[0] or py.mouse.get_pressed()[2]:
            mpos = py.mouse.get_pos()
            # If click was out of grid
            if (mpos[0] > vinit and mpos[0] < vend) and (mpos[1] > 0 and mpos[1] < ssize[1]):
                if py.mouse.get_pressed()[0]:
                    grid[int((mpos[0] - vinit) / 10)][int(mpos[1] / 10)] = 1
                else:
                    grid[int((mpos[0] - vinit) / 10)][int(mpos[1] / 10)] = 0


        # Draw grid
        for x in range(50):
            for y in range(50):
                if grid[x][y] == 1:
                    sx = (x * 10) + (ssize[0] - ssize[1]) / 2
                    sy = (y * 10)
                    py.draw.rect(screen, black, (sx, sy, 10, 10)) 

        # Refresh the screen
        py.display.flip()
        
        # Update the grid
        if not(paused):
            grid_copy = [x[:] for x in grid]
            # When a cell dies
            for x in range(50):
                for y in range(50):
                    if grid_copy[x][y] == 1:
                        neighbors = -1 # Counting the actual cell

                        for nx in range(-1, 2):
                            for ny in range(-1, 2):
                                # If get out of limits
                                if x+nx < 0 or x+nx >= 50 or y+ny < 0 or y+ny >= 50:
                                    grid[x][y] = 0
                                else:
                                    if grid_copy[x + nx][y + ny] == 1:
                                        neighbors+=1

                        if neighbors < 2 or neighbors > 3:
                            grid[x][y] = 0
            # When a cell borns 
            for x in range(50):
                for y in range(50):
                    if grid_copy[x][y] == 1:
                        for nx in range(-1, 2):
                            for ny in range(-1, 2):
                                neighbors = 0
                                for nx2 in range(-1, 2):
                                    for ny2 in range(-1, 2):
                                        # If cell is in the limits
                                        if x+nx+nx2 < 0 or x+nx+nx2 >= 50 or y+ny+ny2 < 0 or y+ny+ny2 >= 50:
                                            break
                                        if grid_copy[x + nx + nx2][y + ny + ny2] == 1:
                                            neighbors+=1

                                if neighbors == 3:
                                    # If is inside the limits
                                    if not(x+nx < 0 or x+nx >= 50 or y+ny < 0 or y+ny >= 50):
                                        grid[x + nx][y + ny] = 1

        # Fixed fps
        timer.tick(40)

        # If user clicks "x"
        for event in py.event.get():
            if event.type == py.QUIT:
                run = False
            if event.type == py.KEYDOWN:
                if event.key == py.K_SPACE:
                    paused = not(paused)
                    if paused:
                        py.display.set_caption("Game of Life[Paused]")
                    else:
                        py.display.set_caption("Game of Life")



if __name__ == "__main__":
    main()