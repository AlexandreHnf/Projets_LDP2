JFLAGS = -g
JC = javac
JVM= java
.SUFFIXES: .java .class
.java.class:
		$(JC) $(JFLAGS) $*.java

CLASSES = \
        vect0.java \
        Prod.java \
        Sum.java \
        Main.java 

MAIN = Main

default: classes

classes: $(CLASSES:.java=.class)

run: $(MAIN).class
	$(JVM) $(MAIN)

clean:
		$(RM) *.class