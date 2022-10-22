NAME = scheduler
ADDITIONAL_NAMES = sortedlist dlist pq task ilrd_uid

CC = gcc
GDFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
GCFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
VPATH = ./src:./include:./test:/home/noyazut/git/ds/include:/home/noyazut/git/ds/src:/home/noyazut/git/ds/tests:/home/noyazut/git/ds/utils
INCLUDE = -I ./include -I /home/noyazut/git/ds/include -I /home/noyazut/git/ds/utils


SRC = $(NAME)_test.c $(NAME).c
HEADERS = $(NAME).h cstmdef.h tests.h
OBJECTS = $(NAME).o $(NAME)_test.o

ADDITIONAL_HEADERS = $(foreach d, $(ADDITIONAL_NAMES), $d.h)
ADDITIONAL_SRCS = $(foreach d, $(ADDITIONAL_NAMES), $d.c)
ADDITIONAL_OBJECTS = $(foreach d, $(ADDITIONAL_NAMES), $d.o)

EXECUTABLE_FILES = $(NAME)_production $(NAME)_debug
PRODUCTION_EXECUTABLE = $(NAME)_production
DEBUG_EXECUTABLE = $(NAME)_debug

.PHONY : clean clean_obj obj ar

$(NAME) : $(OBJECTS) $(ADDITIONAL_OBJECTS)
	$(CC) $(GCFLAGS) -o $(PRODUCTION_EXECUTABLE) $?
	rm -f $(OBJECTS) $(ADDITIONAL_OBJECTS)

debug : $(OBJECTS) $(ADDITIONAL_OBJECTS)
	$(CC) $(GDFLAGS) -o $(DEBUG_EXECUTABLE) $?
	rm -f $(OBJECTS) $(ADDITIONAL_OBJECTS)

all : $(OBJECTS) $(ADDITIONAL_OBJECTS)
	$(CC) $(GCFLAGS) -o $(PRODUCTION_EXECUTABLE) $?
	$(CC) $(GDFLAGS) -o $(DEBUG_EXECUTABLE) $?
	rm -f $(OBJECTS) $(ADDITIONAL_OBJECTS)

clean :
	rm -f $(EXECUTABLE_FILES) $(OBJECTS) $(ADDITIONAL_OBJECTS)

cleanobj :
	rm -f $(OBJECTS) $(ADDITIONAL_OBJECTS)

cleanlib :
	rm -f $(NAME).a $(NAME).ar

obj : $(NAME).o $(NAME)_test.o

$(NAME).o : $(NAME).c $(HEADERS) $(ADDITIONAL_HEADERS) $(ADDITIONAL_SRCS)
	$(CC) $(INCLUDE) $(GDFLAGS) $? -c

$(NAME)_test.o : $(NAME)_test.c $(HEADERS)
	$(CC) $(INCLUDE) $(GDFLAGS) $? -c

ar: obj
	ar r $(NAME).ar $(OBJECTS)
	rm -f $(OBJECTS)

a: obj
	ar r $(NAME).a $(OBJECTS)
	rm -f $(OBJECTS) $(ADDITIONAL_OBJECTS)

