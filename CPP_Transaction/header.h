#include <iostream>
#include <list>
#include <cstdint>
#include <stdio_ext.h>
#include <stdlib.h>
#include <unistd.h>

class Cart;
class Bank;

void stall();
void menu();
bool checkout(Cart &);