CC := clang-cl
CXX := clang-cl
CFLAGS := /Ot /Wall /c /GX -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-unknown-pragmas -Wno-newline-eof -Wno-unused-macros -Wno-empty-translation-unit -Wno-comma -Wno-deprecated-declarations -Wno-gnu-binary-literal

SRCDIR := src

SRCS     := $(shell FORFILES /P $(SRCDIR) /S /M *.c /C "CMD /C ECHO @relpath")
SRCS     := $(patsubst ".\\%",$(SRCDIR)\\%,$(SRCS))

OUT := $(SRCS:.c=.o)
OUT := $(subst src\,bin\,$(OUT))

TREE  := $(sort $(patsubst %\,%,$(dir $(OUT))))
TREE := $(filter-out ./,$(TREE))
TREE := $(TREE:\=)

OUT := $(subst \,/,$(OUT))


OUTFILE := vas.exe

all: $(OUT)
	$(CXX) $(OUT) -o $(OUTFILE)

$(TREE): %:
		-mkdir $@

fix:
	call vcvarsall.bat amd64

bin/%.o : src/%.c $(TREE)
	$(CC) -Xclang -std=gnu17 $(CFLAGS) $< -o $@
