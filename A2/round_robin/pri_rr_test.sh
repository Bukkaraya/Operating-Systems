#!/bin/bash

pubtest_num=(1 2 3 4 5 6 7 8 9 10)
## Start private testing
echo "Start private testing ..."
for tno in ${pubtest_num[*]}
do
cp "test_inputs/test$tno.txt" "./events.txt"

if cmp -s <(./Dispatcher 800 500 < ./events.txt) <(cat "pri_rr_test_outputs/rr_results$tno.txt"); then
   echo "Test $tno passed"
else
    echo "Test $tno failed"
fi
done
## Private testing is done!
echo "Private testing is done!"

