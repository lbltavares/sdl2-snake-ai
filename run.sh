#!/bin/bash

gcc ./src/*.c -o ./bin/main -I./include -lSDL2main -lSDL2 && ./bin/main