# Makefile for installing easy paint (https://github.com/Gr1N/EasyPaint)
# only macosx at the moment

# == Environment

PLAT= macosx
OUTFILE= paint
MOC:= /usr/local/Cellar/qt/6.2.2/share/qt/libexec/moc
RCC:= /usr/local/Cellar/qt/6.2.2/share/qt/libexec/rcc
SRCS:= $(shell find src -name '*.c' -or -name '*.m' -or -name '*.cpp')

QTMOC_H:= $(shell grep -lR --include \*.h 'Q_OBJECT' src)
QTRCC_QRC:= $(shell find src -name '*.qrc')
QTMOC_GENSRCS:= $(foreach wrd, $(QTMOC_H), $(if $(strip $(patsubst %.h,,$(notdir $(wrd)))),,$(patsubst src%,dest%,$(dir $(wrd)))$(patsubst %.h,%.moc.cpp,$(notdir $(wrd)))))
QTRCC_GENSRCS:= $(foreach wrd, $(QTRCC_QRC), $(if $(strip $(patsubst %.qrc,,$(notdir $(wrd)))),,$(patsubst src%,dest%,$(dir $(wrd)))$(patsubst %.qrc,%.rcc.cpp,$(notdir $(wrd)))))

C_OBJS:= $(foreach wrd, $(SRCS), $(if $(strip $(patsubst %.c,,$(notdir $(wrd)))),,$(patsubst src%,dest%,$(dir $(wrd)))$(patsubst %.c,%.o,$(notdir $(wrd)))))
M_OBJS:= $(foreach wrd, $(SRCS), $(if $(strip $(patsubst %.m,,$(notdir $(wrd)))),,$(patsubst src%,dest%,$(dir $(wrd)))$(patsubst %.m,%.o,$(notdir $(wrd)))))
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
	INCPATH= -Isrc -I/usr/local/include/QtGui -I/usr/local/include/QtCore -I/usr/local/include/QtWidgets -I/usr/local/include/QtPrintSupport
	CFLAGS= -Wall -ggdb3 -std=c++17 -fno-strict-aliasing $(INCPATH)
	LDFLAGS= -F/usr/local/lib -F/Library/Frameworks -framework Foundation -framework QtGui -framework QtCore -framework QtWidgets -framework QtPrintSupport -lobjc -lm -lstdc++
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

$(filter %.o,$(C_OBJS)): dest%.o: src%.c
	$(MKDIR) $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

$(filter %.o,$(M_OBJS)): dest%.o: src%.m
	$(MKDIR) $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

$(filter %.cpp,$(QTMOC_GENSRCS)): dest%.moc.cpp: src%.h
	$(MKDIR) $(@D)
	$(MOC) $(INCPATH) $< -o $@

$(filter %.o,$(QTMOC_OBJS)): dest%.o: dest%.cpp
	$(MKDIR) $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

$(filter %.cpp,$(QTRCC_GENSRCS)): dest%.rcc.cpp: src%.qrc
	$(MKDIR) $(@D)
	$(RCC) -name $* $< -o $@

$(filter %.o,$(QTRCC_OBJS)): dest%.o: dest%.cpp
	$(MKDIR) $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

$(filter %.o,$(CPP_OBJS)): dest%.o: src%.cpp
	$(MKDIR) $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

$(OUTFILE): $(C_OBJS) $(M_OBJS) $(QTMOC_OBJS) $(QTRCC_OBJS) $(CPP_OBJS)
	$(RM) $(OUTFILE)
	$(WINDRES)
	$(CC) $^ $(LDFLAGS) -o $(OUTFILE)

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
