# CS410 Fall2020-a0
# $@: name of the target(lhs of the first line of each rules)
# $^: dependencies of the target(rhs of the first line of each rules)
# if you dont want make to show the command itself add a @ before the command name
# 	e.g., echo "Hello" ---output--> echo "Hello"\nHello
# 		  @echo "Hello" ---output--> Hello

#PROGS = getsyms_sects
#OJBS = libobj.o
#LIBS = libobjdata.so

#all: $(LIBS) $(PROGS)

all: ta tb tc
ta: getsections getsyms
tb: getsections_dl getsyms_dl
tc: gettext gettext_dl

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


libobjdata.a: objsect.c objsym.c objcopy.c
	gcc -c -o objsect.o objsect.c -lbfd
	gcc -c -o objsym.o objsym.c -lbfd
	gcc -c -o objcopy.o objcopy.c -lbfd
	ar rs libobjdata.a objsect.o objsym.o objcopy.o

libobjdata.so: objsect.c objsym.c objcopy.c
	gcc -c -fPIC -o objsect.pic.o objsect.c -lbfd
	gcc -c -fPIC -o objsym.pic.o objsym.c -lbfd
	gcc -c -fPIC -o objcopy.pic.o objcopy.c -lbfd
	gcc -shared -o libobjdata.so objsect.pic.o objsym.pic.o objcopy.pic.o -lbfd

getsections: getsections.c libobjdata.a
	gcc -o getsections getsections.c libobjdata.a -lbfd

getsyms: getsyms.c libobjdata.a
	gcc -o getsyms getsyms.c libobjdata.a -lbfd

getsections_dl: getsections_dl.c libobjdata.so
	gcc -I./ -L./ -o getsections_dl getsections_dl.c -lobjdata -lbfd

getsyms_dl: getsyms_dl.c libobjdata.so
	gcc -I./ -L./ -o getsyms_dl getsyms_dl.c -lobjdata -lbfd

gettext: gettext.c libobjdata.a
	gcc -o gettext gettext.c libobjdata.a -lbfd

gettext_dl: gettext.c libobjdata.so
	gcc -I./ -L./ -o gettext_dl gettext.c -lobjdata -lbfd

clean:
	rm -f *.o *.so *~ *.so *.a $(all)

