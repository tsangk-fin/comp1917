# Lab Week 2 - Linked Lists, Performance

*Submission by Kenneth Tsang (z5075419)*

### Testing shell script

The table found in this submission was generated using the following bash script.

N.B. `sort -R` was not available on the environment I was running this on.  Thus, perl's `shuffle()` was used.

```
#!/bin/bash
attempts=10
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
          USELC=`(time ./usel < $initial.txt > /dev/null) 2>&1 | grep user | sed 's/.*\([0-9]\)m\([0-9]*\.[0-9]*\)s.*/(\1*60)+\2/'`
          SORTC=`(time sort -n < $initial.txt > /dev/null) 2>&1 | grep user | sed 's/.*\([0-9]\)m\([0-9]*\.[0-9]*\)s.*/(\1*60)+\2/'`

          USEL_MATH="$USEL_MATH $USELC + ";
          SORT_MATH="$SORT_MATH $SORTC + ";
        done
      USEL_MATH="$USEL_MATH 0) / $attempts";
      USEL_MATH=`echo "$USEL_MATH" | bc -l`;
      SORT_MATH="$SORT_MATH 0) / $attempts";
      SORT_MATH=`echo "$SORT_MATH" | bc -l`;

      echo "$i,$initial,$1,$attempts,$USEL_MATH,$SORT_MATH" >> timings.txt
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
```

### Findings

In most cases tested, the sorting implemented on `./usel` is slower or equivalent to the GNU `sort`.
It is evident that the sorting algorithm implemented in `sort` is different, and can be more efficient to that implemented in `./usel`.

### Input size

It goes without saying that the larger the input size, the longer it will take to sort.  This is true for both `./usel` and `sort`.

However, the time difference between `./usel` and `sort` grow exponentially as the input size increases.

As an example, a randomly sorted list of 1000 numbers (with duplicates) takes 0.0003s to sort using `./usel` compared to 0.0002s with `sort` (i.e. 1.5 times longer on `./usel`).  At 10,000 numbers with the same criteria, it takes 0.0186s for `./usel` and 0.0009s for `sort` (i.e. 20 times longer).  At 100,000 numbers, it takes 4.8270s for `./usel` and 0.0206s for `sort` (234x longer).

| Input | usel (s) | sort (s) | x longer |
|-------|----------|----------|----------|
| 1k    | 0.0003   | 0.0002   | 1.5      |
| 10k   | 0.0186   | 0.0009   | 20       |
| 100k  | 4.8270   | 0.0206   | 234      |

In fact, based on the averages above, for every 10x increase in input -- `usel` is ~20x slower than `sort`.

### Random, sorted, reverse

Sorted lists take the shortest amount of time to complete the "sort".  This makes sense for my implementation of `IntListInsertInOrder` as it does a check early on to check if the integer being added is larger than the last number in the existing list.  If it finds this, it simply appends to the list:

```
if(curr == NULL || L->last->data <= v){
    IntListInsert(L, v);
}
```

Similarly, reverse sorted lists take minimal time as the code will exit out of the while loop as soon as the number is added:

```
while(curr != NULL && !added){
    if(curr->data >= v){
        ....
        added = 1
    }
}
```

Randomly ordered lists take the longest to sort, which is also logical.  For the majority of `IntListInsertInOrder` function calls, the integer being added (especially as the list grows) will be further and further in the while loop.  Thus, it takes more time to complete the sort.

Notably, `sort` completes the sort far quicker than `usel` for randomly ordered lists:

| Input Size | Initial Order | Has Duplicates | Number of runs | Avg Time for usel | Avg Time for sort |
|------------|---------------|----------------|----------------|-------------------|-------------------|
|     100000 | random        | no             |             10 | 4.7037            | 0.0073            |
|     100000 | random        | yes            |             10 | 4.8270            | 0.0206            |

#### With or without duplicates
Interestingly, the sorting algorithm implemented in GNU's `sort` performed significantly faster on lists without duplicates where as `./usel` had a negligible difference.

For example, using `sort`, ordering a 80,000 randomly sorted list with no duplicates was on-average completed in 0.0046s vs 0.0150s for a list with duplicates.

However, using `./usel`, the same lists performed with negligible difference at 0.0053s vs 0.0042s respectively.

| Input Size | Initial Order | Has Duplicates | Avg Time for usel | Avg Time for sort |
|------------|---------------|----------------|-------------------|-------------------|
|      80000 | sorted        | yes            | 0.0043            | 0.0162            |
|      80000 | reversed      | yes            | 0.0042            | 0.0150            |
|      80000 | sorted        | no             | 0.0039            | 0.0030            |
|      80000 | reversed      | no             | 0.0053            | 0.0046            |


### Results Table

The results table is also presented in comma-separated value format at the end:


| Input Size | Initial Order | Has Duplicates | Number of runs | Avg Time for usel | Avg Time for sort |
|------------|---------------|----------------|----------------|-------------------|-------------------|
|       1000 | random        | yes            |             10 | 0.0003            | 0.0002            |
|       1000 | sorted        | yes            |             10 | 0.0001            | 0.0002            |
|       1000 | reversed      | yes            |             10 | 0.0002            | 0.0002            |
|       1000 | random        | no             |             10 | 0.0003            | 0.0002            |
|       1000 | sorted        | no             |             10 | 0.0002            | 0.0001            |
|       1000 | reversed      | no             |             10 | 0.0002            | 0.0001            |
|       5000 | random        | yes            |             10 | 0.0044            | 0.0005            |
|       5000 | sorted        | yes            |             10 | 0.0004            | 0.0003            |
|       5000 | reversed      | yes            |             10 | 0.0005            | 0.0005            |
|       5000 | random        | no             |             10 | 0.0039            | 0.0005            |
|       5000 | sorted        | no             |             10 | 0.0005            | 0.0003            |
|       5000 | reversed      | no             |             10 | 0.0003            | 0.0003            |
|      10000 | random        | yes            |             10 | 0.0186            | 0.0009            |
|      10000 | sorted        | yes            |             10 | 0.0004            | 0.0008            |
|      10000 | reversed      | yes            |             10 | 0.0005            | 0.0008            |
|      10000 | random        | no             |             10 | 0.0170            | 0.0005            |
|      10000 | sorted        | no             |             10 | 0.0007            | 0.0004            |
|      10000 | reversed      | no             |             10 | 0.0008            | 0.0005            |
|      20000 | random        | yes            |             10 | 0.0847            | 0.0023            |
|      20000 | sorted        | yes            |             10 | 0.0009            | 0.0016            |
|      20000 | reversed      | yes            |             10 | 0.0011            | 0.0021            |
|      20000 | random        | no             |             10 | 0.0835            | 0.0011            |
|      20000 | sorted        | no             |             10 | 0.0008            | 0.0006            |
|      20000 | reversed      | no             |             10 | 0.0010            | 0.0007            |
|      50000 | random        | yes            |             10 | 0.8510            | 0.0086            |
|      50000 | sorted        | yes            |             10 | 0.0021            | 0.0079            |
|      50000 | reversed      | yes            |             10 | 0.0028            | 0.0091            |
|      50000 | random        | no             |             10 | 0.8466            | 0.0036            |
|      50000 | sorted        | no             |             10 | 0.0030            | 0.0018            |
|      50000 | reversed      | no             |             10 | 0.0028            | 0.0016            |
|      80000 | random        | yes            |             10 | 2.7310            | 0.0203            |
|      80000 | sorted        | yes            |             10 | 0.0043            | 0.0162            |
|      80000 | reversed      | yes            |             10 | 0.0042            | 0.0150            |
|      80000 | random        | no             |             10 | 2.7882            | 0.0080            |
|      80000 | sorted        | no             |             10 | 0.0039            | 0.0030            |
|      80000 | reversed      | no             |             10 | 0.0053            | 0.0046            |
|     100000 | random        | yes            |             10 | 4.8270            | 0.0206            |
|     100000 | sorted        | yes            |             10 | 0.0046            | 0.0162            |
|     100000 | reversed      | yes            |             10 | 0.0052            | 0.0218            |
|     100000 | random        | no             |             10 | 4.7037            | 0.0073            |
|     100000 | sorted        | no             |             10 | 0.0041            | 0.0034            |
|     100000 | reversed      | no             |             10 | 0.0046            | 0.0038            |


```
Input Size,Initial Order,Has Duplicates,Number of runs,Avg Time for usel,Avg Time for sort
1000,random,yes,10,.0003,.0002
1000,sorted,yes,10,.0001,.0002
1000,reversed,yes,10,.0002,.0002
1000,random,no,10,.0003,.0002
1000,sorted,no,10,.0002,.0001
1000,reversed,no,10,.0002,.0001
5000,random,yes,10,.0044,.0005
5000,sorted,yes,10,.0004,.0003
5000,reversed,yes,10,.0005,.0005
5000,random,no,10,.0039,.0005
5000,sorted,no,10,.0005,.0003
5000,reversed,no,10,.0003,.0003
10000,random,yes,10,.0186,.0009
10000,sorted,yes,10,.0004,.0008
10000,reversed,yes,10,.0005,.0008
10000,random,no,10,.0170,.0005
10000,sorted,no,10,.0007,.0004
10000,reversed,no,10,.0008,.0005
20000,random,yes,10,.0847,.0023
20000,sorted,yes,10,.0009,.0016
20000,reversed,yes,10,.0011,.0021
20000,random,no,10,.0835,.0011
20000,sorted,no,10,.0008,.0006
20000,reversed,no,10,.0010,.0007
50000,random,yes,10,.8510,.0086
50000,sorted,yes,10,.0021,.0079
50000,reversed,yes,10,.0028,.0091
50000,random,no,10,.8466,.0036
50000,sorted,no,10,.0030,.0018
50000,reversed,no,10,.0028,.0016
80000,random,yes,10,2.7310,.0203
80000,sorted,yes,10,.0043,.0162
80000,reversed,yes,10,.0042,.0150
80000,random,no,10,2.7882,.0080
80000,sorted,no,10,.0039,.0030
80000,reversed,no,10,.0053,.0046
100000,random,yes,10,4.8270,.0206
100000,sorted,yes,10,.0046,.0162
100000,reversed,yes,10,.0052,.0218
100000,random,no,10,4.7037,.0073
100000,sorted,no,10,.0041,.0034
100000,reversed,no,10,.0046,.0038
```