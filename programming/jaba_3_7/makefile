# makefile Golubovich_3_7

.SUFFIXES: .class .java

PACK=pack
TARG=test
JC=javac -g
JM=java -ea -jar
JR=jar -cfe

OBJ=$(PACK)\Interval.class \
    $(PACK)\Main.class

.java.class:
	$(JC) $<

run: build
	$(JM) $(TARG).jar

build: 	$(OBJ)
	$(JR) $(TARG).jar $(PACK).Main $(OBJ)

clean:
	for %%f in ($(OBJ)) do del %%f
	del $(TARG).jar

$(PACK)\Interval.class: $(PACK)\Interval.java makefile

$(PACK)\Main.class: $(PACK)\Main.java makefile

# eof makefile Golubovich_3_7