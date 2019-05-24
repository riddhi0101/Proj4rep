CXX = g++
  
CURDIR =$(shell pwd)
LIBDIR = ./lib
OBJDIR = ./obj
BINDIR = ./bin
INCLUDEDIR = ./include
SRCDIR = ./src
LIBCSVDIR = libcsv-3.0.3
LIBCSV_NAME = libcsv.a

INCLUDE = -I $(INCLUDEDIR)src/ -I /opt/local/include
CXXFLAGS = -std=c++14 (INCLUDE)
TESTLDFLAGS = -L /opt/local/lib -lgtest -lgtest_main -lpthread


CSV_READER_OBJ = $(OBJDIR)/CSVReader.o
CSV_WRITER_OBJ = $(OBJDIR)/CSVWriter.o
CSV_TEST_OBJ = $(OBJDIR)/testcsv.o

CSV_TEST_NAME = testcsv



all: $(LIBDIR)/$(LIBCSV_NAME) directories runtest

runtest: $(TESTBIN)/$(CSV_TEST_NAME)
	$(TESTBIN)/$(CSV_TEST_NAME)


$(CSV_READER_OBJ): $(SRCDIR)/CSVReader.cpp $(INCLUDEDIR)/CSVReader.h
	$(CXX) $(SRCDIR)/CSVReader.cpp -c $(CXXFLAGS) -o $(CSV_READER_OBJ)

$(CSV_WRITER_OBJ): $(SRCDIR)/CSVWriter.cpp $(INCLUDEDIR)/CSVReader.h $(INCLUDEDIR)/StringUtils.h
	$(CXX) $(SRCDIR)/CSVWriter.cpp -c $(CXXFLAGS) -o $(CSV_WRITER_OBJ)

$(STRING_UTILS_OBJ): $(SRCDIR)/StringUtils.cpp $(INCLUDEDIR)/StringUtils.h
	$(CXX) $(SRCDIR)/StringUtils.cpp -c $(CXXFLAGS) -o $(INCLUDEDIR)/StringUtils.h

$(CSV_TEST_OBJ): $(SRCDIR)/testcsv.cpp $(INCLUDEDIR)/CSVReader.h $(INCLUDEDIR)/CSVWriter.h
	$(CXX) $(SRCDIR)/testcsv.cpp -c $(CXXFLAGS) -o $(CSV_TEST_OBJ)

$(TESTBINDIR)/$(CSV_TEST_NAME): $(CSV_READER_OBJ) $(CSV_WRITER_OBJ) $(CSV_TEST_OBJ) $(LIBDIR)/$(LIBCSV_NAME)
	$(CXX) $(CSV_READER_OBJ) $(CSV_WRITER_OBJ) $(CSV_TEST_OBJ) $(LIBDIR)/$(LIBCSV_NAME) $(CXXFLAGS) $(TESTLDFLAGS) -o $(TESTBIN)/$(CSV_TEST_NAME)

$(LIBCSVDIR)/Makefile:
	cd $(LIBCSVDIR); ./configure --prefix=$(CURDIR); cd ..

$(LIBCSVDIR)/libcsv.la: $(LIBCSVDIR)/Makefile
	cd $(LIBCSVDIR); make; cd ..

$(LIBDIR)/$(LIBCSV_NAME): $(LIBCSVDIR)/libcsv.la
	cd $(LIBCSVDIR); make install; cd ..

directories: $(BINDIR) $(TESTBINDIR) $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(TESTBINDIR):
	mkdir -p $(TESTBIN_DIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
       

clean:
	rm -f lib/*
	rm -f include/csv.h
	cd $(LIBCSVDIR);  make clean; cd ..
	rm -f $(LIBCSVDIR)/Makefile
