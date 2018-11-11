FLAGS= -std=c++17 -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Weffc++ \
-Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy \
-Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant \
-Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
CXX= g++
MAIN= main.cpp
OUT= file

all: $(OUT)

$(OUT): min_max.o CircBidirLinkedList.o tableau.o $(MAIN)
	$(CXX) $(FLAGS) $(MAIN) min_max.o CircBidirLinkedList.o tableau.o -o $(OUT)

min_max.o: min_max.cpp min_max.hpp
	$(CXX) $(FLAGS) -c min_max.cpp

CircBidirLinkedList.o: CircBidirLinkedList.cpp CircBidirLinkedList.hpp
	$(CXX) $(FLAGS) -c CircBidirLinkedList.cpp

tableau.o: tableau.cpp tableau.hpp
	$(CXX) $(FLAGS) -c tableau.cpp

.PHONY : clean
clean:
	rm *.o *.out;

mrproper: clean
	rm -rf $(OUT)
