# Makefile generator instantiated from /ENIGMAsystem/SHELL/Developer/.

echo "#Awesome Makefile generated by custom ENIGMAsystem/Developer/automake.sh" > Makefile

echo "" >> Makefile;
echo ".objs:" >> Makefile;
echo "	-mkdir .objs" >> Makefile;
echo "" >> Makefile

for file in *.c ;
  do
  {
    printf ".objs/ogg_${file%.c}.o: $file" >> Makefile;
    for i in `c_incl $file | gawk '/\/usr\/include/ { next } { print } '`;
    do
      printf " $i" >> Makefile;
    done;
    echo "" >> Makefile;
    
    echo "	gcc -c $file		-o .objs/ogg_${file%.c}.o \$(ECFLAGS)"  >> Makefile;
  };
  done;

echo "" >> Makefile;

  printf "\$(DEST)/libogg.a: .objs " >> Makefile;
  for file in *.c ;
    do printf ".objs/ogg_${file%.c}.o " >> Makefile; 
    done;
  echo "" >> Makefile;
  echo "	ar r \$(DEST)/libogg.a .objs/*.o" >> Makefile;
  echo "" >> Makefile;

echo "static: \$(DEST)/libogg.a" >> Makefile;
echo "" >> Makefile;
echo "clean:" >> Makefile;
echo "	-rm .objs/*" >> Makefile;

