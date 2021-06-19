CXX := g++
CXXFLAGS := -std=c++11 -pedantic-errors -Werror=pedantic -Wall -Wextra -Winline -g
ifneq ($(OS), Windows_NT)
CXXFLAGS += -fsanitize=address,leak,undefined
endif
TESTFILES := test-size-copy test-add-comp test-index test-table
VERSION := release

all: test

test: $(patsubst %,%.exe,$(TESTFILES))
ifeq ($(OS), Windows_NT)
	powershell if (-Not (Test-Path -PathType container ./output)) \
	  { New-Item -Path ./output -ItemType "Directory" -Force }
	powershell 'Write-Output $(TESTFILES) |' \
	  'ForEach-Object { & "./$$_" | Out-File "./output/$$_-output.txt" }'
  ifneq ($(VERSION), release)
	powershell New-Item -Path ./expected -ItemType "Directory" -Force
	powershell Move-Item output/* expected
  endif
else
	mkdir -p output
	for t in $(TESTFILES); do ./$${t}.exe >./output/$${t}-output.txt; done
  ifneq ($(VERSION), release)
	mkdir -p expected
	mv output/* expected
  endif
endif

test-size-copy.exe: test-size-copy.o test-data.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test-add-comp.exe: test-add-comp.o test-data.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test-index.exe: test-index.o test-data.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test-table.exe: test-table.o test-data.o table.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

depend:
	$(CXX) -MM $(CXXFLAGS) *.cpp >.depend.mk

clean:
ifeq ($(OS), Windows_NT)
	powershell Remove-Item * -Include *.o,*.out,*.exe -Exclude *.cpp, *.h, Makefile -Confirm
else
	del *.o *.out *.exe
endif

distclean: clean
ifeq ($(OS), Windows_NT)
	powershell Remove-Item .depend.mk -Include .depend.mk -Confirm
else
	del .depend.mk
endif

-include .depend.mk

