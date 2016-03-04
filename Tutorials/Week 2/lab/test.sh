#!/bin/bash
attempts=1
echo "Input Size,Initial Order,Has Duplicates,Number of runs,Avg Time for usel,Avg Time for sort" > timings.txt

function process {
  for initial in "random" "sorted" "reversed"
    do
      echo " - Processing $initial with duplicates flag as $1";
      USEL_MATH="scale=4;(";
      SORT_MATH="scale=4;(";
        for attempt in {1..$attempts}
        do
          # calculate time needed for random file
          USELC=`(time ./usel < $initial.txt > /dev/null) 2>&1 | grep user | sed 's/.*\([0-9]\)m\([0-9]*\.[0-9]*\)s.*/\2/'`
          SORTC=`(time sort -n < $initial.txt > /dev/null) 2>&1 | grep user | sed 's/.*\([0-9]\)m\([0-9]*\.[0-9]*\)s.*/\2/'`

          # USEL_MATH="$USEL_MATH $USELC + ";
          # SORT_MATH="$SORT_MATH $SORTC + ";
        done
      # USEL_MATH="$USEL_MATH 0) / $attempts";
      # USEL_MATH=`echo "$USEL_MATH" | bc -l`;
      # SORT_MATH="$SORT_MATH 0) / $attempts";
      # SORT_MATH=`echo "$SORT_MATH" | bc -l`;

      echo "$i,$initial,$1,$attempts,$USELC,$SORTC" >> timings.txt
    done
}

for i in 1000 5000 10000 20000 50000 80000 100000
  do
    echo "Testing sort speed for $i values"

    ./randl $i > random.txt
    sort -n < random.txt > sorted.txt
    sort -rn < random.txt > reversed.txt

    process "yes"

    seq $i | perl -MList::Util=shuffle -e 'print shuffle(<STDIN>);' > random.txt
    seq $i > sorted.txt
    seq $i | sort -nr > reversed.txt

    process "no"

    # delete the text file
    rm -f random.txt sorted.txt reversed.txt
  done