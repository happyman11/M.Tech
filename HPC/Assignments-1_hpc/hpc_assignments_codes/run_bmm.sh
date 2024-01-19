threads_number=(2 4 6 8 10 12 14 16)
block_size=(2 4 8 16 32 64)
matrix_size=(1024 2048)
choice_user=(3 4)



#  Matrix Size Iteration
for size in "${matrix_size[@]}"; do
    # Threads Iteration
    for threads in "${threads_number[@]}";  do
        echo "  Middle loop iteration Thread  $threads"
        ./OMM_Normal $threads $size 4
        # Power Iterartion
        for ((pow = 2; pow <= 16; pow++)); do
          #Block Iteration
          for block in "${block_size[@]}";  do
            # User Choice Iteration
            for choice in "${choice_user[@]}";  do 
                ./Assignment1 $threads $size $pow $block $choice
            done
          done
        done
    done
done

