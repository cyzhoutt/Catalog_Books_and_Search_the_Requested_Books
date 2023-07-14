SearchNewBooks : SearchNewBooks.cc
	g++ -Wall -Werror --std=c++11 -o $@ $^

clean:
	rm -f SearchNewBooks