g++ -g -O -I ./include -c -o main.o main.cpp
g++ -g -O -I ./include -o main.exe main.o -L ./lib -lwpcap