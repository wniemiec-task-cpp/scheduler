OBJS	= 	Scheduler.o
SOURCE	=	src/wniemiec/task/cpp/Scheduler.cpp
CC	 = g++ 
FLAGS	 = -c
LFLAGS	 =

all: $(OBJS)
	$(CC) -c $(OBJS) $(LFLAGS) -std=c++17

Scheduler.o: src/wniemiec/task/cpp/Scheduler.cpp
	$(CC) $(FLAGS) src/wniemiec/task/cpp/Scheduler.cpp -std=c++17

clean:
	rm -f $(OBJS) $(OUT)

