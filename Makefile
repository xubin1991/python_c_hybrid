

libcos_doubles.so : cos_doubles.cpp
	g++ -shared -fPIC -o libcos_doubles.so cos_doubles.cpp


# libcos_doubles.so : cos_doubles.o
# 	g++ -shared -Wl,-soname,libcos_doubles.so -o libcos_doubles.so cos_doubles.o

# cos_doubles.o : cos_doubles.c
# 	g++ -c -fPIC cos_doubles.c -o cos_doubles.o

clean :
	rm -vf libcos_doubles.so cos_doubles.o cos_doubles.pyc
run : 
	python3 test_run.py