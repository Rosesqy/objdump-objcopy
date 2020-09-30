# CS410 Fall2020-a0
# $@: name of the target(lhs of the first line of each rules)
# $^: dependencies of the target(rhs of the first line of each rules)
# if you dont want make to show the command itself add a @ before the command name
# 	e.g., echo "Hello" ---output--> echo "Hello"\nHello
# 		  @echo "Hello" ---output--> Hello

PROGS = getsyms_sects
OJBS = libobj.o
LIBS = libobjdata.so

all: $(LIBS) $(PROGS)

# getsyms_sects: getsyms_sects.c $(OBJS) $(LIBS)
# 	gcc $< libobjdata.so -lbfd -ldl -o $@
# 	 #the target is libobjdata.so
# #== gcc getsyms_sects.c libobjdata.so /path/to/libbfd.so.some_version - ldl -o getsyms_sects

# #libobjdata.so depends on libobj.o
# libobjdata.so: libobj.o
# #== gcc -shaured -o libobjdata.so libobj.o
# 	gcc -shared -o $@ $^

# libobj.o: libobj.c
# 	gcc -fPIC -c $^

libobjdata.so:
	gcc -c -fPIC -o objsect.o objsect.c -lbfd
	gcc -c -fPIC -o objsym.o objsym.c -lbfd
	gcc -shared -o libobjdata.so objsect.o objsym.o	-lbfd

getsections_dl: getsections_dl.c libobjdata.so
	gcc -I./ -L./ -o getsections_dl getsections_dl.c -lobjdata -lbfd

getsyms_dl: getsyms_dl.c libobjdata.so
	gcc -I./ -L./ -o getsyms_dl getsyms_dl.c -lobjdata -lbfd

clean:
	rm -f *.o *.so *~ *.so $(PROGS)

