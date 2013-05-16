#  @author     Stephan Bourgeois <stephanb2@hotmail.com>
#  @version    0.1
#  @since      2013-05-15
#  @license    MIT License

CC      = g++
CFLAGS  = -I./include


PRODIR = src/json
DYNDIR = src/dynamic-cpp
TESTDIR = src/test
OBJDIR = obj
BINDIR = bin

protoc = $(addprefix $(OBJDIR)/, decoder.o parser.o)
dynamic = $(addprefix $(OBJDIR)/, assign.o ctor.o dynamic.o iterator.o types.o)


test : $(protoc) $(dynamic) $(TESTDIR)/test02.cpp
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/%.o: $(PRODIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(DYNDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: test clean

clean:
	rm $(protoc) $(dynamic)

