#------------------------------------------------------------------------------
#
##  Makefile for CMPS 101 pa1 
#  Compiles all .java files in the current directory and creates an executable
#  #  jar file called Lex.  See the following for a short description of makefiles
#
##       https://classes.soe.ucsc.edu/cmps012b/Summer18/lab1.pdf
#	//Mythili Karra
#	//mmkarra
#	//CS101
#	//04/15/2019
##-----------------------------------------------------------------------------
MAINCLASS  = Lex
JAVAC      = javac 
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) Makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS) 
all: $(JARFILE)
	
$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE)
submit: README List.java ListClient.java Lex.java Makefile
	submit cmps101-pt.s19 pa1 README List.java ListClient.java Lex.java Makefile 
