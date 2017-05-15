#
# Makefile for the Linux Simulator
#
########################################################

PROGRAM = 	Simulator

# Compilation Details
SHELL = /bin/sh
CC = cc
STDCFLAGS = -g -c -Wall 
INCLUDES = -I.
LIBRERIAS =
ACC = /var/asignaturas/ssoo/ACC/bin/acc

${PROGRAM}: Simulator.o ComputerSystem.o MainMemory.o OperatingSystem.o ProcessorAspect.o MMU.o Buses.o Aspect.o Clock.o Heap.o
	$(CC) -o ${PROGRAM} Simulator.o ComputerSystem.o MainMemory.o OperatingSystem.o ProcessorAspect.o Buses.o MMU.o Aspect.o Clock.o Heap.o $(LIBRERIAS)

Simulator.o: Simulator.c Simulator.h
	$(CC) $(STDCFLAGS) $(INCLUDES) Simulator.c

ComputerSystem.o: ComputerSystem.c ComputerSystem.h
	$(CC) $(STDCFLAGS) $(INCLUDES) ComputerSystem.c

MainMemory.o: MainMemory.c MainMemory.h
	$(CC) $(STDCFLAGS) $(INCLUDES) MainMemory.c

OperatingSystem.o: OperatingSystem.c OperatingSystem.h
	$(CC) $(STDCFLAGS) $(INCLUDES) OperatingSystem.c

ProcessorAspect.o: ProcessorAspect.mc Aspect.acc
	$(ACC) ProcessorAspect.mc Aspect.acc
	$(CC) $(STDCFLAGS) $(INCLUDES) -L /tmp/ACC/lib -lacc ProcessorAspect.c

ProcessorAspect.mc: Processor.c Processor.h
	$(CC) -E $(INCLUDES) Processor.c > ProcessorAspect.mc

Aspect.o: Aspect.acc
	$(ACC) Aspect.acc
	$(CC) $(STDCFLAGS) $(INCLUDES) -L /tmp/ACC/lib -lacc Aspect.c

Aspect.acc: Processor.h MyAspect.c
	$(CC) -E $(INCLUDES) MyAspect.c > Aspect.acc

Buses.o: Buses.c Buses.h
	$(CC) $(STDCFLAGS) $(INCLUDES) Buses.c

MMU.o: MMU.c MMU.h
	$(CC) $(STDCFLAGS) $(INCLUDES) MMU.c

Clock.o: Clock.c Clock.h
	$(CC) $(STDCFLAGS) $(INCLUDES) Clock.c
	
Heap.o: Heap.c Heap.h
	$(CC) $(STDCFLAGS) $(INCLUDES) Heap.c

clean:
	rm -f $(PROGRAM) *.o *~ *.mc *.acc core
