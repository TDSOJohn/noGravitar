This game is inspired by the color vector graphics game Gravitar, released by Atari, Inc. in 1982.

#Installation
This game needs the SFML framework or libraries, check https://www.sfml-dev.org if in need.

#Game
The game opens on a new Solar System, from which one is able to enter a planet. Every planet has a number of enemies to destroy and fuel barrels to collect (collecting fuel is disabled after the last enemy of the planet is dead).
Score is increased by:
- Hitting an enemy
- Killing an enemy
- Collecting fuel

Every completed planet becomes red but is still accessible, even if empty.
Solar System is destroyed and recreated once all planets are cleared, effectively restarting everything and keeping the score gained.


spaceshipBulletArray.clear(); at Planet.cpp, 117 doesn’t work properly