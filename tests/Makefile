CXX = clang++
INCLUDES= -I./
CXXFLAGS = -g $(INCLUDES)
SRCM= TestTrivial.cpp
OBJM = $(SRCM:.cpp=.o)
LINKFLAGS= -lcppunit

testtrivial: TestTrivial.cpp $(OBJM)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJM) $(LINKFLAGS) $(LINKFLAGSLOG4) $(LIBLOG)

# Default compile

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
