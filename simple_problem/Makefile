# soruce file names
SRCS := mortal_rabits.cpp edit_distance.cpp trace_back.cpp shared_motif.cpp

TARGETS := $(SRCS:.cpp=)

CXX := g++
CXXFLAGS := -std=c++17
INCLUDE := -I ~/mylib/cpp/header
RFUNCTION := ~/mylib/cpp/build/rfunction.o


.PHONY: all
all: $(TARGETS)

# %: %.cpp
# 	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: editDist
editDist:
	$(CXX) $(CXXFLAGS) -o edit_distance 

.PHONY: trace_back
trace_back:
	$(CXX) -o trace_back $(CXXFLAGS)  $(RFUNCTION) trace_back.cpp $(INCLUDE)

shared_motif:
	$(CXX) -o shared_motif $(CXXFLAGS)  $(RFUNCTION) shared_motif.cpp $(INCLUDE)


.PHONY: clean
clean:
	rm -f $(TARGETS)