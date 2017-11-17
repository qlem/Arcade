# Arcade

Play arcade games and change graphics library or game dynamically. Developed in C++.


## Screenshots

![alt text](https://raw.githubusercontent.com/qlem/Arcade/master/screenshots/menu_caca.png)
![alt text](https://raw.githubusercontent.com/qlem/Arcade/master/screenshots/pacman_caca.png)
![alt text](https://raw.githubusercontent.com/qlem/Arcade/master/screenshots/snake_caca.png)
![alt text](https://raw.githubusercontent.com/qlem/Arcade/master/screenshots/solar_caca.png)

## Add your own graphics library or game

The IGame and IGraphic interface in 'inc' directory allows you to make your own game or graphics library.
Your game / graphics library must be a shared library :

* game.so in 'games' directory
* graphics.so in 'lib' directory

## Compile

You need to install :

* [SFML](https://www.sfml-dev.org/index-fr.php)
* [libcaca](http://caca.zoy.org/wiki/libcaca)

Then :

```
./make
```

## Run

```
./arcade
```