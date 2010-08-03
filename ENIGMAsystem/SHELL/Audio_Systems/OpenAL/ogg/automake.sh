# Call this file from the directory in question if you would like a generic
# Makefile generated which invokes GCC for each individual file.

echo "#Awesome Makefile generated by ENIGMAsystem/Developer/automake.sh" > Makefile
echo "" >> Makefile;

for file in *.c ;
  do
  {
    printf "\$(DEST)/${file%.c}.o: $file" >> Makefile;
    for i in `c_incl $file | gawk '/\/usr\/include/ { next } { print } '`;
    do
      printf " $i" >> Makefile;
    done;
    echo "" >> Makefile;
    
    echo "	gcc -c $file		-o \$(DEST)/${file%.c}.o \$(FLAGS)"  >> Makefile;
  };
  done;

echo "" >> Makefile;

  printf "avail: " >> Makefile;
  for file in *.c ;
    do printf "\$(DEST)/${file%.c}.o " >> Makefile; 
    done;
  echo "" >> Makefile;

echo "" >> Makefile;
echo "clean:" >> Makefile;
echo "" >> Makefile;
