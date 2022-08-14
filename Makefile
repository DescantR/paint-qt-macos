# Makefile for installing easy paint (https://github.com/Gr1N/EasyPaint)
# only macosx at the moment

# == Environment

PLAT= macosx
OUTFILE= paint
MOC:= /opt/homebrew/Cellar/qt/6.3.1_1/share/qt/libexec/moc
RCC:= /opt/homebrew/Cellar/qt/6.3.1_1/share/qt/libexec/rcc
SRCS:= $(shell find src -name '*.cpp')

QTMOC_H:= $(shell grep -lR --include \*.h 'Q_OBJECT' src)
QTRCC_QRC:= $(shell find src -name '*.qrc')
QTMOC_GENSRCS:= $(foreach wrd, $(QTMOC_H), $(if $(strip $(patsubst %.h,,$(notdir $(wrd)))),,$(patsubst src%,dest%,$(dir $(wrd)))$(patsubst %.h,%.moc.cpp,$(notdir $(wrd)))))
QTRCC_GENSRCS:= $(foreach wrd, $(QTRCC_QRC), $(if $(strip $(patsubst %.qrc,,$(notdir $(wrd)))),,$(patsubst src%,dest%,$(dir $(wrd)))$(patsubst %.qrc,%.rcc.cpp,$(notdir $(wrd)))))

QTMOC_OBJS:= $(foreach wrd, $(QTMOC_H), $(if $(strip $(patsubst %.h,,$(notdir $(wrd)))),,$(patsubst src%,dest%,$(dir $(wrd)))$(patsubst %.h,%.moc.o,$(notdir $(wrd)))))
QTRCC_OBJS:= $(foreach wrd, $(QTRCC_QRC), $(if $(strip $(patsubst %.qrc,,$(notdir $(wrd)))),,$(patsubst src%,dest%,$(dir $(wrd)))$(patsubst %.qrc,%.rcc.o,$(notdir $(wrd)))))
CPP_OBJS:= $(foreach wrd, $(SRCS), $(if $(strip $(patsubst %.cpp,,$(notdir $(wrd)))),,$(patsubst src%,dest%,$(dir $(wrd)))$(patsubst %.cpp,%.o,$(notdir $(wrd)))))

# == Utilities

CC= gcc
MKDIR= mkdir -p
RM= rm -rf
WINDRES= 

# == Flags

$(info PLAT= ${PLAT})

#-03
ifeq ($(PLAT), macosx)
	CC= cc
	INCPATH= -Isrc -I/opt/homebrew/include/QtGui -I/opt/homebrew/include/QtCore -I/opt/homebrew/include/QtWidgets -I/opt/homebrew/include/QtPrintSupport 
	CFLAGS= -Wall -ggdb3 -std=c++17 -fno-strict-aliasing $(INCPATH)
	LDFLAGS= -F/opt/homebrew/Frameworks -F/Library/Frameworks -framework Foundation -framework QtGui -framework QtCore -framework QtWidgets -framework QtPrintSupport -lobjc -lm
endif

$(info OUTFILE= ${OUTFILE})
$(info CC= ${CC})
$(info CFLAGS= ${CFLAGS})
$(info LDFLAGS= ${LDFLAGS})

$(info ====)

# == Targets

all: builddir $(OUTFILE)

builddir:
	$(if $(strip $(shell command -v ccache)), ccache $(CC),)
	$(MKDIR) dest

$(filter %.cpp,$(QTMOC_GENSRCS)): dest%.moc.cpp: src%.h
	$(MKDIR) $(@D)
	$(MOC) $(INCPATH) $< -o $@

$(filter %.o,$(QTMOC_OBJS)): dest%.o: dest%.cpp
	$(MKDIR) $(@D)
	#DEBUGSTR##(CC) -c #(CFLAGS) #< -o #@
	ASAN_OPTIONS=detect_leaks=1 /opt/homebrew/opt/llvm/bin/clang++ -c -I/opt/homebrew/include -I/opt/homebrew/opt/llvm/include -fsanitize=address -fno-omit-frame-pointer $(CFLAGS) $< -o $@

$(filter %.cpp,$(QTRCC_GENSRCS)): dest%.rcc.cpp: src%.qrc
	$(MKDIR) $(@D)
	$(RCC) -name $* $< -o $@

$(filter %.o,$(QTRCC_OBJS)): dest%.o: dest%.cpp
	$(MKDIR) $(@D)
	#DEBUGSTR##(CC) -c #(CFLAGS) #< -o #@
	ASAN_OPTIONS=detect_leaks=1 /opt/homebrew/opt/llvm/bin/clang++ -c -I/opt/homebrew/include -I/opt/homebrew/opt/llvm/include -fsanitize=address -fno-omit-frame-pointer $(CFLAGS) $< -o $@

$(filter %.o,$(CPP_OBJS)): dest%.o: src%.cpp
	$(MKDIR) $(@D)
	#DEBUGSTR#-fsanitize=thread ##-fsanitize=undefined -fsanitize=nullability ###(CC) -c #(CFLAGS) #< -o #@
	ASAN_OPTIONS=detect_leaks=1 /opt/homebrew/opt/llvm/bin/clang++ -c -I/opt/homebrew/include -I/opt/homebrew/opt/llvm/include -fsanitize=address -fno-omit-frame-pointer $(CFLAGS) $< -o $@

$(OUTFILE): $(C_OBJS) $(M_OBJS) $(QTMOC_OBJS) $(QTRCC_OBJS) $(CPP_OBJS)
	$(RM) $(OUTFILE)
	$(WINDRES)
	#DEBUGSTR##(CC) #^ #(LDFLAGS) -lstdc++ -o #(OUTFILE)
	/opt/homebrew/opt/llvm/bin/clang++ $^ $(LDFLAGS) -fsanitize=address -shared-libasan -o $(OUTFILE)

macbundle: $(OUTFILE).app

$(OUTFILE).app: $(OUTFILE)
	$(MKDIR) $(OUTFILE).app/Contents/{Frameworks,MacOS,Resources}
	cp res/icon.icns $(OUTFILE).app/Contents/Resources/icon.icns
	cp res/Info.plist $(OUTFILE).app/Contents/Info.plist
	cp $(OUTFILE) $(OUTFILE).app/Contents/MacOS/$(OUTFILE)
	chmod +x $(OUTFILE).app/Contents/MacOS/$(OUTFILE)

clean:
	$(RM) dest
	$(RM) $(OUTFILE)
	$(RM) $(OUTFILE).app

.PHONY: all builddir macbundle clean
