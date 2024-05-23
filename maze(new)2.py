import random
import pygame
import numpy
white = (255, 255, 255)
green = (20, 255, 20)
red = (255, 20, 20)
black = (0, 0, 0)

def draw(maze, size, orientation, start, end):
    screen.fill(black)
    pygame.draw.rect(screen, white, pygame.Rect(15, 15, size*16+2, size*16+2), 2)
    for row in range(size):
        for col in range(size):
            if maze[row][col][0] == 1:
                pygame.draw.rect(screen, white, pygame.Rect(col*16+15, row*16+15, 18, 2))
            if maze[row][col][1] == 1:
                pygame.draw.rect(screen, white, pygame.Rect(col*16+15, row*16+15, 2, 18))
    if orientation == 0:
        pygame.draw.rect(screen, black, pygame.Rect(start*16+17, 15, 14, 2))
        pygame.draw.rect(screen, black, pygame.Rect(end*16+17, size*16+15, 14, 2))
        pygame.draw.rect(screen, green, pygame.Rect(start*16+15, 0, 2, 15))
        pygame.draw.rect(screen, red, pygame.Rect(end*16+15, size*16+17, 2, 15))
        pygame.draw.rect(screen, green, pygame.Rect(start*16+31, 0, 2, 15))
        pygame.draw.rect(screen, red, pygame.Rect(end*16+31, size*16+17, 2, 15))
    if orientation == 1:
        pygame.draw.rect(screen, black, pygame.Rect(15, start*16+17, 2, 14))
        pygame.draw.rect(screen, black, pygame.Rect(size*16+15, end*16+17, 2, 14))
        pygame.draw.rect(screen, green, pygame.Rect(0, start*16+15, 15, 2))
        pygame.draw.rect(screen, red, pygame.Rect(size*16+17, end*16+15, 15, 2))
        pygame.draw.rect(screen, green, pygame.Rect(0, start*16+31, 15, 2))
        pygame.draw.rect(screen, red, pygame.Rect(size*16+17, end*16+31, 15, 2))

    pygame.display.flip()

size = int(input("Enter side length (0 to exit): "))
while size > 0:
    pygame.init()
    clock = pygame.time.Clock()
    screen = pygame.display.set_mode(((size+2)*16, (size+2)*16))
    running = True

    #makes the maze nothing but walls
    maze = numpy.ones((size, size, 2), dtype = int)

    #generates start and end
    orientation = random.randint(0, 1)
    start = random.randint(0, size-1)
    end = random.randint(0, size-1)

    #randomly removes walls until maze is fully connected
    connected = numpy.zeros((size, size), dtype = int)
    if orientation == 1:
        connected[start][0] = 1
    elif orientation == 0:
        connected[0][start] = 1
    while True:

        #finds all outer connections
        edges = []
        for i in range(size):
            for j in range(size):
                if connected[i][j] == 0:
                    if i != 0:
                        if connected[i-1][j] == 1:
                            edges.append([i, j, 0])
                    if j != 0:
                        if connected[i][j-1] == 1:
                            edges.append([i, j, 1])
                    if i != size-1:
                        if connected[i+1][j] == 1:
                            edges.append([i+1, j, 0])
                    if j != size-1:
                        if connected[i][j+1] == 1:
                            edges.append([i, j+1, 1])
        
        #breaks the loop if array 'edges' is empty (maze is fully connected)
        if len(edges) < 1:
            break

        #randomly removes one of the outer walls of the connected area
        chosen = random.randint(0, len(edges) - 1)
        maze[edges[chosen][0]][edges[chosen][1]][edges[chosen][2]] = 0

        #changes array 'connected' accordingly
        connected[edges[chosen][0]][edges[chosen][1]] = 1
        if edges[chosen][2] == 0:
            connected[edges[chosen][0]-1][edges[chosen][1]] = 1
        elif edges[chosen][2] == 1:
            connected[edges[chosen][0]][edges[chosen][1]-1] = 1
        draw(maze, size, orientation, start, end)
    
    #draws the maze in a separate window
    while running:
        draw(maze, size, orientation, start, end)
        clock.tick(60)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

    pygame.display.quit()
    pygame.quit
    size = int(input("Enter side length (0 to exit): "))