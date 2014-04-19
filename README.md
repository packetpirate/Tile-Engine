---=====---=====---=====---=====---=====---=====---=====---=====---=====---=====---=====---=====---=====---=====---

Author: Darin Beaudreau
Platform: C++ / SFML

Description: 

Tile Engine is the base engine for a game I am planning to make sometime in the future. It is a
simple random level generator that stitches together rooms based on the BSP Dungeon Generation algorithm described
in the link below.

http://www.roguebasin.com/index.php?title=Basic_BSP_Dungeon_generation

Essentially, the algorithm just recursively divides an initial grid into pieces, and then divides those pieces,
until you reach a certain "depth", or recursion levels. Randomly sized rooms are then placed within these
areas to create a rudimentary "level". Then, the "corridors" are added by connected each of the rooms to its
"sister" node (the nodes are stored in a binary tree as they are created) and then to their parent node, and
so on in this fashion until the root node is reached.

I've also added zoom functionality to the map so you can zoom in and out to get a better view of the map. The
zoom level starts out zoomed all the way in on the player. You can control the player with the WASD keys.

Right now, the algorithm is for the most part finished, except that sometimes the corridors don't reach the room
they are supposed to connect to, which can leave rooms unreachable. This can easily be solved, but it might make
things interesting to leave them disconnected and then implement "mining" into the game so the user can mine
walls in an attempt to find these "secret" rooms. It's not a bug... it's a feature!

Known Issues:
 - Sometimes corridors will not connect, and will leave rooms unreachable.

---=====---=====---=====---=====---=====---=====---=====---=====---=====---=====---=====---=====---=====---=====---
