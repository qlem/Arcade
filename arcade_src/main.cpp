/*
** main.c for arcade in /home/dommer_c/rendu/cpp_arcade
** 
** Made by dommer_c
** Login   <clement.dommerc@epitech.eu>
** 
** Started on  Thu Mar 23 14:28:15 2017 dommer_c
// Last update Tue Apr 25 17:35:36 2017 dommer_c
*/

#include "Core.h"

int	main(void)
{
  arcade::Core	core;
  
  core.init_uis("lib/sfml.so");
  core.run();
  return (0);
}
